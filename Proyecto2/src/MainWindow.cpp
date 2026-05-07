#include "MainWindow.h"
#include "LexicalAnalyzer.h" 
#include "SyntaxAnalyzer.h" 
#include "ErrorManager.h"
#include "ReportGenerator.h"
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("TaskScript Analyzer");
    resize(1000, 600);
    setupUI();
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QWidget *topBarWidget = new QWidget();
    QHBoxLayout *topLayout = new QHBoxLayout(topBarWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton *btnLoad = new QPushButton("Cargar Archivo");
    QPushButton *btnExec = new QPushButton("Ejecutar");
    QPushButton *btnRepo = new QPushButton("Generar Reportes");
    QPushButton *btnExit = new QPushButton("Salir");

    QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnLoad->setSizePolicy(sp); btnLoad->setMinimumHeight(40);
    btnExec->setSizePolicy(sp); btnExec->setMinimumHeight(40);
    btnRepo->setSizePolicy(sp); btnRepo->setMinimumHeight(40);
    btnExit->setSizePolicy(sp); btnExit->setMinimumHeight(40);

    topLayout->addWidget(btnLoad);
    topLayout->addWidget(btnExec);
    topLayout->addWidget(btnRepo);
    topLayout->addWidget(btnExit);

    QWidget *bottomWidget = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);
    bottomLayout->setContentsMargins(0, 0, 0, 0);

    codeEditor = new QTextEdit();
    codeEditor->setMinimumWidth(400);

    QTabWidget *tabs = new QTabWidget();
    
    tokenTable = new QTableWidget(0, 4);
    tokenTable->setHorizontalHeaderLabels({"Lexema", "Tipo", "Línea", "Columna"});
    tokenTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    errorTable = new QTableWidget(0, 5);
    errorTable->setHorizontalHeaderLabels({"Lexema", "Tipo", "Descripción", "Línea", "Columna"});
    errorTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tabs->addTab(tokenTable, "Tokens");
    tabs->addTab(errorTable, "Errores");

    bottomLayout->addWidget(codeEditor, 1);
    bottomLayout->addWidget(tabs, 1);

    mainLayout->addWidget(topBarWidget);
    mainLayout->addWidget(bottomWidget, 1);
    setCentralWidget(centralWidget);

    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::handleLoadFile);
    connect(btnExec, &QPushButton::clicked, this, &MainWindow::handleAnalyze);
    connect(btnExit, &QPushButton::clicked, this, &QWidget::close);
    connect(btnRepo, &QPushButton::clicked, [this]() {
        QString dir = QFileDialog::getExistingDirectory(this, "Seleccionar carpeta para guardar reportes");
        if (dir.isEmpty()) return;
        
        ReportGenerator::generateKanbanReport(lastParsedBoard, dir + "/1_tablero_kanban.html");
        ReportGenerator::generateWorkloadReport(lastParsedBoard, dir + "/2_carga_trabajo.html");
        ReportGenerator::generateErrorReport(dir + "/3_errores.html");
        ReportGenerator::generateDOT(lastParsedTree, dir + "/arbol.dot");

        QMessageBox::information(this, "Éxito", "Reportes HTML y árbol generados en la carpeta seleccionada.");
    });
}

void MainWindow::handleLoadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir", "", "Task (*.task)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            codeEditor->setPlainText(file.readAll());
        }
    }
}

void MainWindow::handleAnalyze() {
    QString code = codeEditor->toPlainText();
    if (code.isEmpty()) return;

    ErrorManager::clear(); 
    tokenTable->setRowCount(0);
    errorTable->setRowCount(0);

    LexicalAnalyzer lexer(code.toStdString());
    Token t;
    do {
        t = lexer.nextToken();
        
        if (t.type != TokenType::FIN_ARCHIVO) {
            int row = tokenTable->rowCount();
            tokenTable->insertRow(row);
            tokenTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(t.lexeme)));
            tokenTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(t.getTypeName()))); 
            tokenTable->setItem(row, 2, new QTableWidgetItem(QString::number(t.line)));
            tokenTable->setItem(row, 3, new QTableWidgetItem(QString::number(t.column)));
        }
    } while (t.type != TokenType::FIN_ARCHIVO);

    LexicalAnalyzer lexer2(code.toStdString()); 
    SyntaxAnalyzer parser(lexer2);
    parser.parse();
    lastParsedBoard = parser.getBoard();
    lastParsedTree = parser.getTreeRoot();

    for (const auto& err : ErrorManager::errors) { 
        int row = errorTable->rowCount();
        errorTable->insertRow(row);
        
        errorTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(err.lexeme)));
        errorTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(err.type)));
        errorTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(err.description)));
        errorTable->setItem(row, 3, new QTableWidgetItem(QString::number(err.line)));
        errorTable->setItem(row, 4, new QTableWidgetItem(QString::number(err.column)));
    }
}