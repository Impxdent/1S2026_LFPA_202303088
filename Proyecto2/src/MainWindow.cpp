#include "MainWindow.h"
#include "ErrorManager.h"
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setWindowTitle("TaskScript IDE - Kanban Manager");
    resize(1000, 700);
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    codeEditor = new QTextEdit();
    codeEditor->setPlaceholderText("Escribe el codigo");
    
    QPushButton *btnLoad = new QPushButton("Cargar Archivo .task");
    QPushButton *btnAnalyze = new QPushButton("Ejecutar Análisis");
    
    tokenTable = new QTableWidget(0, 4);
    tokenTable->setHorizontalHeaderLabels({"Lexema", "Tipo", "Línea", "Columna"});
    
    errorTable = new QTableWidget(0, 5);
    errorTable->setHorizontalHeaderLabels({"Lexema", "Tipo", "Descripción", "Línea", "Columna"});

    mainLayout->addWidget(btnLoad);
    mainLayout->addWidget(codeEditor);
    mainLayout->addWidget(btnAnalyze);
    mainLayout->addWidget(new QLabel("Tabla de Tokens:"));
    mainLayout->addWidget(tokenTable);
    mainLayout->addWidget(new QLabel("Tabla de Errores:"));
    mainLayout->addWidget(errorTable);

    setCentralWidget(centralWidget);
    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::handleLoadFile);
    connect(btnAnalyze, &QPushButton::clicked, this, &MainWindow::handleAnalyze);
}

void MainWindow::handleLoadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir Proyecto", "", "Task Files (*.task)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            codeEditor->setPlainText(file.readAll());
        }
    }
}

void MainWindow::handleAnalyze() {
    QString content = codeEditor->toPlainText();
    if (content.isEmpty()) return;

    ErrorManager::clear();
    tokenTable->setRowCount(0);
    errorTable->setRowCount(0);

    LexicalAnalyzer lexer(content.toStdString());
    std::vector<Token> tokens;
    Token t;
    do {
        t = lexer.nextToken();
        if (t.type != TokenType::FIN_ARCHIVO) {
            tokens.push_back(t);
        }
    } while (t.type != TokenType::FIN_ARCHIVO);

    updateTables(tokens);

    QMessageBox::information(this, "Analizador", "Análisis completado con éxito.");
}

void MainWindow::updateTables(const std::vector<Token>& tokens) {
    for (const auto& t : tokens) {
        int row = tokenTable->rowCount();
        tokenTable->insertRow(row);
        tokenTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(t.lexeme)));
        tokenTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(t.getTypeName())));
        tokenTable->setItem(row, 2, new QTableWidgetItem(QString::number(t.line)));
        tokenTable->setItem(row, 3, new QTableWidgetItem(QString::number(t.column)));
    }

    for (const auto& e : ErrorManager::errors) {
        int row = errorTable->rowCount();
        errorTable->insertRow(row);
        errorTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(e.lexeme)));
        errorTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(e.type)));
        errorTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(e.description)));
        errorTable->setItem(row, 3, new QTableWidgetItem(QString::number(e.line)));
        errorTable->setItem(row, 4, new QTableWidgetItem(QString::number(e.column)));
    }
}