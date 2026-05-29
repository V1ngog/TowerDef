#include "mainwindow.h"
#include "factories.h"

MainWindow::MainWindow(QWidget *parent)
    : BaseWindow(parent)
{
    m_menuPage = new MenuPage(this);
    m_settingsPage = new SettingsPage(this);
    m_gamePage = new GamePage(this);
    
    m_gamePage->setFactory(new HardFactory());
    
    registerPage("Menu", m_menuPage);
    registerPage("Settings", m_settingsPage);
    registerPage("Game", m_gamePage);
    
    navigateTo("Menu");

    connect(m_menuPage, &MenuPage::startClicked, this, [this]() {
        navigateTo("Game");
    });

    connect(m_menuPage, &MenuPage::settingsClicked,this, [this]() {
    navigateTo("Settings");
    });

    connect(m_menuPage, &MenuPage::exitClicked, this, &MainWindow::close);

    connect(m_settingsPage, &SettingsPage::cancelClicked, this, [this]() {
    navigateTo("Menu"); 
    });
    
    connect(m_gamePage, &GamePage::gameFinished, 
            this, &MainWindow::onGameFinished);
    
    setWindowTitle("Tower Defense");
}

void MainWindow::onGameFinished()
{
    navigateTo("Menu");
}