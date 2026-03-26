#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>
#include "LexicalAnalyzer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    setWindowTitle("MedLexer - Analizador Léxico");
    resize(1000, 600); 

    QWidget *widgetCentral = new QWidget(this);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(widgetCentral);

    QHBoxLayout *layoutBotones = new QHBoxLayout();
    
    btnCargarArchivo = new QPushButton("Cargar Archivo .med", this);
    btnAnalizar = new QPushButton("Analizar Código", this);
    btnSalir = new QPushButton("Salir del Programa", this); 

    layoutBotones->addWidget(btnCargarArchivo);
    layoutBotones->addWidget(btnAnalizar);
    layoutBotones->addWidget(btnSalir);

    layoutPrincipal->addLayout(layoutBotones);
    QHBoxLayout *layoutPantallaDividida = new QHBoxLayout();

    editorCodigo = new QPlainTextEdit(this);
    editorCodigo->setPlaceholderText("Aquí aparecerá el código...");
    
    tablaTokens = new QTableWidget(0, 4, this);
    tablaTokens->setHorizontalHeaderLabels({"Token", "Lexema", "Fila", "Col."});
    tablaTokens->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layoutPantallaDividida->addWidget(editorCodigo);
    layoutPantallaDividida->addWidget(tablaTokens);

    layoutPrincipal->addLayout(layoutPantallaDividida);
    setCentralWidget(widgetCentral);

    connect(btnCargarArchivo, &QPushButton::clicked, this, &MainWindow::cargarArchivo);
    connect(btnAnalizar, &QPushButton::clicked, this, &MainWindow::analizarTexto);
    
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
    QList<Token> tokens = lexer.analizar(texto);

    tablaTokens->setRowCount(0);

    for (int i = 0; i < tokens.size(); ++i) {
        tablaTokens->insertRow(i);
        tablaTokens->setItem(i, 0, new QTableWidgetItem(obtenerNombreToken(tokens[i].tipo)));
        tablaTokens->setItem(i, 1, new QTableWidgetItem(tokens[i].lexema));
        tablaTokens->setItem(i, 2, new QTableWidgetItem(QString::number(tokens[i].fila)));
        tablaTokens->setItem(i, 3, new QTableWidgetItem(QString::number(tokens[i].columna)));
    }

    QMessageBox::information(this, "Éxito", "Análisis completado.");
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
        case ErrorLexico: return "¡ERROR LÉXICO!";
        default: return "Desconocido";
    }
}