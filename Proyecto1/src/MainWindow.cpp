#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>  // Para buscar el archivo en windows
#include <QFile>        // Para leer el archivo
#include <QTextStream>  // Para extraer el texto del archivo
#include <QMessageBox>  // Para mostrar ventanitas de alerta
#include <QDebug>       // Para imprimir cosas en la terminal
#include "LexicalAnalyzer.h" 

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    setWindowTitle("MedLexer");
    resize(800, 600);

    // 1. Interfaz visual 
    QWidget *widgetCentral = new QWidget(this);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(widgetCentral);

    btnCargarArchivo = new QPushButton("Cargar Archivo .med", this);
    btnAnalizar = new QPushButton("Analizar Código", this);
    editorCodigo = new QPlainTextEdit(this);
    editorCodigo->setPlaceholderText("Texto...");

    layoutPrincipal->addWidget(btnCargarArchivo);
    layoutPrincipal->addWidget(btnAnalizar);
    layoutPrincipal->addWidget(editorCodigo);
    setCentralWidget(widgetCentral);

    // 2. Ejecutar función
    connect(btnCargarArchivo, &QPushButton::clicked, this, &MainWindow::cargarArchivo);
    connect(btnAnalizar, &QPushButton::clicked, this, &MainWindow::analizarTexto);
}

MainWindow::~MainWindow() {}

// Función 1: Abre el explorador de archivos
void MainWindow::cargarArchivo() {
    // Abre la ventana de Windows buscando solo archivos .med
    QString rutaArchivo = QFileDialog::getOpenFileName(this, "Abrir archivo", "", "Archivos Med (*.med);;Todos los archivos (*.*)");
    
    if (rutaArchivo.isEmpty()) return; // Si el usuario le dio a "Cancelar"

    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    // Leemos el contenido y lo pegamos en el editor visual
    QTextStream entrada(&archivo);
    QString contenido = entrada.readAll();
    editorCodigo->setPlainText(contenido); 
    archivo.close();
}

// Función 2: Ejecutar automata manual
void MainWindow::analizarTexto() {
    QString texto = editorCodigo->toPlainText(); // Sacamos el texto del editor
    
    if (texto.isEmpty()) {
        QMessageBox::information(this, "Aviso", "No hay código para analizar.");
        return;
    }

    LexicalAnalyzer lexer;
    QList<Token> tokens = lexer.analizar(texto);

    QString mensaje = QString("Análisis completado.\nSe procesaron %1 componentes léxicos/errores.").arg(tokens.size());
    QMessageBox::information(this, "Éxito", mensaje);

    qDebug() << "\n--- RESULTADO DEL ANÁLISIS ---";
    for (const Token& t : tokens) {
        qDebug() << "Fila:" << t.fila << "Col:" << t.columna << "| Lexema:" << t.lexema;
    }
    qDebug() << "------------------------------\n";
}