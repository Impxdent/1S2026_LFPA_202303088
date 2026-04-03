#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTabWidget>
#include "Token.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: 
    void cargarArchivo();
    void analizarTexto();
    void mostrarAcercaDe();
    void generarReporte();

private:
    QPlainTextEdit *editorCodigo;
    QPushButton *btnCargarArchivo;
    QPushButton *btnAnalizar;
    QPushButton *btnReporte;
    QPushButton *btnAcercaDe;
    QPushButton *btnSalir;
    QTabWidget *pestanasResultados;
    QTableWidget *tablaTokens;
    QTableWidget *tablaErrores;

    QString obtenerNombreToken(TokenType tipo);
};

#endif 