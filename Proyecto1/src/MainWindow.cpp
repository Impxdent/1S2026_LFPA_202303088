#include "MainWindow.h"
#include <QVBoxLayout> 
#include <QWidget>    

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    setWindowTitle("MedLexer - Analizador Léxico");
    resize(800, 600);

    QWidget *widgetCentral = new QWidget(this);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(widgetCentral);

    btnCargarArchivo = new QPushButton("Cargar Archivo .med", this);
    btnAnalizar = new QPushButton("Analizar Código", this);
    
    editorCodigo = new QPlainTextEdit(this);
    editorCodigo->setPlaceholderText("Aquí aparecerá el código de tu archivo .med...");

    layoutPrincipal->addWidget(btnCargarArchivo);
    layoutPrincipal->addWidget(btnAnalizar);
    layoutPrincipal->addWidget(editorCodigo);

    setCentralWidget(widgetCentral);
}

MainWindow::~MainWindow() {
    
}