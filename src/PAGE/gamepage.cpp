#include "gamepage.h"
#include "gamescreen.h"
#include "gamefactory.h"
#include "factories.h"
#include <QVBoxLayout>

GamePage::GamePage(QWidget *parent)
    : BasePage(parent)
    , m_gameScreen(nullptr)
    , m_factory(nullptr)
    , m_layout(nullptr)
{
    m_layout = new QVBoxLayout(this);
    setLayout(m_layout);

    m_factory = new MediumFactory();
}

GamePage::~GamePage()
{
    if (m_gameScreen) {
        delete m_gameScreen;
        m_gameScreen = nullptr;
    }

    if (m_factory) {
        delete m_factory;
        m_factory = nullptr;
    }
}

void GamePage::setFactory(GameFactory* factory)
{
    if (m_factory) {
        delete m_factory;
        m_factory = nullptr;
    }

    m_factory = factory;
}

void GamePage::onPageEnter()
{
    if (!m_factory) return;
    
    if (!m_gameScreen) {
        m_gameScreen = new GameScreen(this);
        m_layout->addWidget(m_gameScreen);
        
        connect(m_gameScreen, &GameScreen::gameWon, 
                this, &GamePage::onGameWon);
        connect(m_gameScreen, &GameScreen::gameLost, 
                this, &GamePage::onGameLost);
    }
    
    m_gameScreen->setFactory(m_factory);
    m_gameScreen->startGame();
}

void GamePage::onPageExit()
{
    if (m_gameScreen) {
        m_gameScreen->stopGame();
    }
}

void GamePage::updateData() {}

void GamePage::onGameWon()
{
    emit gameWin();
}

void GamePage::onGameLost()
{
    emit gameLost();
}