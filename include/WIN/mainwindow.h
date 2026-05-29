#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basewindow.h"
#include "menupage.h"
#include "settingspage.h"
#include "gamepage.h"
#include "winpage.h"

class MainWindow : public BaseWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    
private:
    MenuPage *m_menuPage;
    SettingsPage *m_settingsPage;
    GamePage *m_gamePage;
    WinPage *m_winPage;
};

#endif