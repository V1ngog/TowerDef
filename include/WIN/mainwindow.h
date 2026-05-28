#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basewindow.h"
#include "menupage.h"
#include "settingspage.h"
#include "gamepage.h"

class MainWindow : public BaseWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onStartGame();
    void onOpenSettings();
    void onGameFinished();

private:
    MenuPage *m_menuPage;
    SettingsPage *m_settingsPage;
    GamePage *m_gamePage;
};

#endif