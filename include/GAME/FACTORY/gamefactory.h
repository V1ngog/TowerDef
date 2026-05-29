#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include <QPointF>

class Build;
class Enemy;
class Missile;

class GameFactory
{
public:
    virtual ~GameFactory() = default;
    
    virtual Build* createBuild() = 0;
    virtual Enemy* createEnemy(QPointF targetPos) = 0;
    virtual Missile* createMissile(Enemy* target) = 0;
};

#endif