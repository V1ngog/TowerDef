#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <QObject>
#include <QList>
#include "enemy.h"
#include "missile.h"
#include "build.h"

class CollisionManager : public QObject
{
    Q_OBJECT

public:
    explicit CollisionManager(QObject *parent = nullptr);

    void checkMissileEnemyCollisions(QList<Missile*>& missiles, QList<Enemy*>& enemies);
    void checkBuildEnemyCollision(Build *build, QList<Enemy*>& enemies);

signals:
    void enemyHit(Missile *missile, Enemy *enemy);
    void buildHit(Enemy *enemy);

private:
    bool checkCollision(QGraphicsItem* a, QGraphicsItem* b);
    
};
#endif