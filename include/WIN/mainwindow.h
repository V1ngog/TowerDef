#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basewindow.h"
#include "menupage.h"
#include "settingspage.h"

class MainWindow : public BaseWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent);

private:
    MenuPage *menuPage;
    SettingsPage *settingsPage;
};
#endif