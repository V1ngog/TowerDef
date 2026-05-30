#include "mainwindow.h"
#include "factories.h"

MainWindow::MainWindow(QWidget *parent)
    : BaseWindow(parent)
{
    m_menuPage = new MenuPage(this);
    m_settingsPage = new SettingsPage(this);
    m_gamePage = new GamePage(this);
    m_winPage = new WinPage(this);
    m_lostPage = new LostPage(this);
    
    m_gamePage->setFactory(new HardFactory());
    
    registerPage("Menu", m_menuPage);
    registerPage("Settings", m_settingsPage);
    registerPage("Game", m_gamePage);
    registerPage("Win", m_winPage);
    registerPage("Lost", m_lostPage);
    
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
    
    connect(m_gamePage, &GamePage::gameWin, this, [this]() {
    navigateTo("Win");
    });

    connect(m_gamePage, &GamePage::gameLost, this, [this]() {
    navigateTo("Lost");
    });

    connect(m_winPage, &WinPage::cancelClicked, this, [this]() {
    navigateTo("Menu"); 
    });
    
    connect(m_lostPage, &LostPage::cancelClicked, this, [this]() {
    navigateTo("Menu"); 
    });

    setWindowTitle("Tower Defense");
}