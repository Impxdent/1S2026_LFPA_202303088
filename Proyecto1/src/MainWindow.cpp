#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    setWindowTitle("MedLexer - Analizador Léxico");
    resize(800, 600);
}

MainWindow::~MainWindow() {
}