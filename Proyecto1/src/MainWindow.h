#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTableWidget>
#include "Token.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: 
    void cargarArchivo();
    void analizarTexto();

private:
    QPlainTextEdit *editorCodigo;
    QPushButton *btnCargarArchivo;
    QPushButton *btnAnalizar;
    QPushButton *btnSalir;
    QTableWidget *tablaTokens;

    QString obtenerNombreToken(TokenType tipo);
};

#endif 