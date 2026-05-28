#include "mainwindow.h"
#include "factories.h"

MainWindow::MainWindow(QWidget *parent)
    : BaseWindow(parent)
{
    // Создаём страницы
    m_menuPage = new MenuPage(this);
    m_settingsPage = new SettingsPage(this);
    m_gamePage = new GamePage(this);
    
    // Устанавливаем фабрику для игры (можно EasyFactory, MediumFactory, HardFactory)
    m_gamePage->setFactory(new HardFactory());
    
    // Регистрируем страницы
    registerPage("Menu", m_menuPage);
    registerPage("Settings", m_settingsPage);
    registerPage("Game", m_gamePage);
    
    // Начинаем с меню
    navigateTo("Menu");
    
    // Связываем сигналы меню
    connect(m_menuPage, &MenuPage::startClicked, 
            this, &MainWindow::onStartGame);
    connect(m_menuPage, &MenuPage::settingsClicked, 
            this, &MainWindow::onOpenSettings);
    connect(m_menuPage, &MenuPage::exitClicked, 
            this, &MainWindow::close);
    
    // Связываем сигналы настроек
    connect(m_settingsPage, &SettingsPage::cancelClicked, 
            this, [this]() { navigateTo("Menu"); });
    
    // Связываем сигналы игры
    connect(m_gamePage, &GamePage::gameFinished, 
            this, &MainWindow::onGameFinished);
    
    setWindowTitle("Tower Defense");
}

void MainWindow::onStartGame()
{
    navigateTo("Game");
}

void MainWindow::onOpenSettings()
{
    navigateTo("Settings");
}

void MainWindow::onGameFinished()
{
    navigateTo("Menu");
}