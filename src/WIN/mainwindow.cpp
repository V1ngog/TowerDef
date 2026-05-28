#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : BaseWindow(parent)
{
    menuPage = new MenuPage(this);
    registerPage("Menu", menuPage);

    navigateTo("Menu");

    setWindowTitle("TowerDef");
}