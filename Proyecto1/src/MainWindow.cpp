#include "MainWindow.h"
#include <QProcess>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>
#include "LexicalAnalyzer.h"
#include "ReportGenerator.h"
#include "DataExtractor.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    
    setWindowTitle("MedLexer - Analizador Léxico");
    resize(1000, 600); 

    QWidget *widgetCentral = new QWidget(this);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(widgetCentral);

    QHBoxLayout *layoutBotones = new QHBoxLayout();
    btnCargarArchivo = new QPushButton("Cargar archivo .med", this);
    btnAnalizar = new QPushButton("Analizar código", this);
    btnReporte = new QPushButton("Generar reporte", this);
    btnAcercaDe = new QPushButton("Acerca de", this);
    btnSalir = new QPushButton("Salir", this);

    layoutBotones->addWidget(btnCargarArchivo);
    layoutBotones->addWidget(btnAnalizar);
    layoutBotones->addWidget(btnReporte);
    layoutBotones->addWidget(btnAcercaDe);
    layoutBotones->addWidget(btnSalir);
    layoutPrincipal->addLayout(layoutBotones);

    QHBoxLayout *layoutPantallaDividida = new QHBoxLayout();

    editorCodigo = new QPlainTextEdit(this);
    editorCodigo->setPlaceholderText("Ingrese el código");
    
    pestanasResultados = new QTabWidget(this);

    tablaTokens = new QTableWidget(0, 4, this);
    tablaTokens->setHorizontalHeaderLabels({"Token", "Lexema", "Fila", "Columna"});
    tablaTokens->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tablaErrores = new QTableWidget(0, 4, this);
    tablaErrores->setHorizontalHeaderLabels({"Carácter Desconocido", "Fila", "Columna", "Descripción"});
    tablaErrores->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    pestanasResultados->addTab(tablaTokens, "Tokens Reconocidos");
    pestanasResultados->addTab(tablaErrores, "Errores Léxicos");

    layoutPantallaDividida->addWidget(editorCodigo);
    layoutPantallaDividida->addWidget(pestanasResultados); 

    layoutPrincipal->addLayout(layoutPantallaDividida);
    setCentralWidget(widgetCentral);

    connect(btnCargarArchivo, &QPushButton::clicked, this, &MainWindow::cargarArchivo);
    connect(btnAnalizar, &QPushButton::clicked, this, &MainWindow::analizarTexto);
    connect(btnReporte, &QPushButton::clicked, this, &MainWindow::generarReporte);
    connect(btnAcercaDe, &QPushButton::clicked, this, &MainWindow::mostrarAcercaDe);
    connect(btnSalir, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow() {}

void MainWindow::cargarArchivo() {
    QString rutaArchivo = QFileDialog::getOpenFileName(this, "Abrir archivo", "", "Archivos Med (*.med);;Todos los archivos (*.*)");
    if (rutaArchivo.isEmpty()) return;

    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    QTextStream entrada(&archivo);
    editorCodigo->setPlainText(entrada.readAll()); 
    archivo.close();
}

void MainWindow::analizarTexto() {
    QString texto = editorCodigo->toPlainText();
    if (texto.isEmpty()) {
        QMessageBox::information(this, "Aviso", "No hay código para analizar.");
        return;
    }

    LexicalAnalyzer lexer;
    tokensActuales = lexer.analizar(texto);
    QList<Token> tokens = tokensActuales;

    tablaTokens->setRowCount(0);
    tablaErrores->setRowCount(0);

    int filaTokens = 0;
    int filaErrores = 0;

    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens[i].tipo == ErrorLexico) {
            tablaErrores->insertRow(filaErrores);
            tablaErrores->setItem(filaErrores, 0, new QTableWidgetItem(tokens[i].lexema));
            tablaErrores->setItem(filaErrores, 1, new QTableWidgetItem(QString::number(tokens[i].fila)));
            tablaErrores->setItem(filaErrores, 2, new QTableWidgetItem(QString::number(tokens[i].columna)));
            tablaErrores->setItem(filaErrores, 3, new QTableWidgetItem("Símbolo no pertenece al lenguaje"));
            filaErrores++;
        } else {
            tablaTokens->insertRow(filaTokens);
            tablaTokens->setItem(filaTokens, 0, new QTableWidgetItem(obtenerNombreToken(tokens[i].tipo)));
            tablaTokens->setItem(filaTokens, 1, new QTableWidgetItem(tokens[i].lexema));
            tablaTokens->setItem(filaTokens, 2, new QTableWidgetItem(QString::number(tokens[i].fila)));
            tablaTokens->setItem(filaTokens, 3, new QTableWidgetItem(QString::number(tokens[i].columna)));
            filaTokens++;
        }
    }

    QMessageBox::information(this, "Éxito", QString("Análisis completado.\nTokens válidos: %1\nErrores encontrados: %2").arg(filaTokens).arg(filaErrores));
}

void MainWindow::mostrarAcercaDe(){
    QString informacion = 
        "<h2>Analizador Léxico - MedLexer</h2>"
        "<p><b>Curso:</b> Lenguajes Formales y de Programación sección A</p>"
        "<p><b>Estudiante:</b> Eldan André Escobar Asturias</p>"
        "<p><b>Carnet:</b> 202303088</p>"
        "<hr>" 
        "<p>Universidad de San Carlos de Guatemala<br>Primer Semestre 2026</p>";

    QMessageBox::about(this, "Acerca del desarrollador", informacion);
}

void MainWindow::generarReporte() {
    if (tokensActuales.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "Error, debe analizar un archivo");
        return;
    }
    //validar ruta
    QString directorio = QFileDialog::getExistingDirectory(this, "Selecciona la carpeta para guardar los reportes");
    if (directorio.isEmpty()) return;

    //generar tabla de errores
    QString rutaLexico = directorio + "/TablaErroresLexicos.html";
    bool exitoLexico = ReportGenerator::generarReporteHTML(tablaTokens, tablaErrores, rutaLexico);

    //generar cuatro reportes
    Hospital hospital = DataExtractor::extraerDatos(tokensActuales);
    bool exito = ReportGenerator::generarReportesSemanticos(hospital, directorio);

    //generar archivo dot
    bool exitoGraphviz = ReportGenerator::generarReporteGraphviz(hospital, directorio);

    //generar imagen
    bool exitoImagen = false;
    if (exitoGraphviz) {
        QString rutaDot = directorio + "/hospital.dot";
        QString rutaPng = directorio + "/hospital.png";

        QStringList argumentos;
        argumentos << "-Tpng" << rutaDot << "-o" << rutaPng;

        QProcess procesoGraphviz;
        
        procesoGraphviz.start("dot", argumentos);
        if (procesoGraphviz.waitForFinished(5000)) {
            if (procesoGraphviz.exitCode() == 0) {
                exitoImagen = true;
            } else {
                qDebug() << "Error en dot: " << procesoGraphviz.readAllStandardError();
            }
        } else {
             qDebug() << "Tiempo";
        }
    }

    if (exito) {
        QMessageBox::information(this, "Éxito", "Se generaron todos los archivos");
    } else {
        QMessageBox::warning(this, "Error", "Error, hubo un problema al guardar los archivos");
    }
}

QString MainWindow::obtenerNombreToken(TokenType tipo) {
    switch (tipo) {
        case PalabraReservada: return "Palabra Reservada";
        case Identificador: return "Identificador";
        case Numero: return "Número";
        case Cadena: return "Cadena";
        case Fecha: return "Fecha";
        case Hora: return "Hora";
        case LlaveAbre: return "Llave {";
        case LlaveCierra: return "Llave }";
        case CorcheteAbre: return "Corchete [";
        case CorcheteCierra: return "Corchete ]";
        case DosPuntos: return "Dos Puntos :";
        case Coma: return "Coma ,";
        case PuntoYComa: return "Punto y coma";
        case ErrorLexico: return "Error léxico";
        default: return "Desconocido";
    }
}