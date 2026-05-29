#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "basepage.h"
#include <QGraphicsView>
#include <QVBoxLayout>

class GameScreen;
class GameFactory;

class GamePage : public BasePage
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();

    void setFactory(GameFactory* factory);
    
    void onPageEnter() override;
    void onPageExit() override;
    void updateData() override;

signals:
    void gameWin();
    void gameLost();

private slots:
    void onGameWon();
    void onGameLost();

private:
    GameScreen* m_gameScreen;
    GameFactory* m_factory;
    QVBoxLayout* m_layout;
};

#endif