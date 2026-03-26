#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit> 
#include <QPushButton>   

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    
    QPlainTextEdit *editorCodigo;
    QPushButton *btnCargarArchivo;
    QPushButton *btnAnalizar;
};

#endif 