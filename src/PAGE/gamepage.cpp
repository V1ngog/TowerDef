#include "gamepage.h"
#include "gamescreen.h"
#include "gamefactory.h"
#include <QVBoxLayout>

GamePage::GamePage(QWidget *parent)
    : BasePage(parent)
    , m_gameScreen(nullptr)
    , m_factory(nullptr)
    , m_layout(nullptr)
{
    m_layout = new QVBoxLayout(this);
    setLayout(m_layout);
}

GamePage::~GamePage()
{
    if (m_gameScreen) {
        delete m_gameScreen;
        m_gameScreen = nullptr;
    }
}

void GamePage::setFactory(GameFactory* factory)
{
    m_factory = factory;
}

void GamePage::onPageEnter()
{
    if (!m_factory) return;
    
    // Создаём GameScreen, если ещё не создан
    if (!m_gameScreen) {
        m_gameScreen = new GameScreen(this);
        m_gameScreen->setFactory(m_factory);
        m_layout->addWidget(m_gameScreen);
        
        // Подключаем сигналы GameScreen
        connect(m_gameScreen, &GameScreen::gameWon, 
                this, &GamePage::onGameWon);
        connect(m_gameScreen, &GameScreen::gameLost, 
                this, &GamePage::onGameLost);
    }
    
    // Запускаем игру
    m_gameScreen->onPageEnter();
}

void GamePage::onPageExit()
{
    if (m_gameScreen) {
        m_gameScreen->onPageExit();
    }
}

void GamePage::updateData()
{
    // Можно обновлять статистику, если нужно
}

void GamePage::onGameWon()
{
    // Победа — возвращаемся в меню
    emit gameFinished();
}

void GamePage::onGameLost()
{
    // Поражение — возвращаемся в меню
    emit gameFinished();
}