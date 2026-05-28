#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : BaseWindow(parent)
{
    menuPage = new MenuPage(this);
    registerPage("Menu", menuPage);

    settingsPage = new SettingsPage(this);
    registerPage("Settings", settingsPage);

    navigateTo("Menu");

    connect(menuPage, &MenuPage::startClicked, this, [this]() {
    navigateTo("Settings");
    });

    connect(menuPage, &MenuPage::settingsClicked, this, [this]() {
    navigateTo("Settings");
    });

    connect(menuPage, &MenuPage::exitClicked, this, [this]() {
    close();
    });

    connect(settingsPage, &SettingsPage::cancelClicked, this, [this]() {
    navigateTo("Menu");
    });

    setWindowTitle("TowerDef");
}