#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);

    private slots:
        void handleAnalyze();   
        void handleLoadFile();  

    private:
        QTextEdit *codeEditor;
        QTableWidget *tokenTable;
        QTableWidget *errorTable;
        BoardData lastParsedBoard;
        
        void setupUI();
        void updateTables(const std::vector<Token>& tokens);
};

#endif