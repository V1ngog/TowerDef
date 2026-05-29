#include "collisionmanager.h"
#include <cmath>

CollisionManager::CollisionManager(QObject *parent) : QObject(parent) {}

bool CollisionManager::checkCollision(QGraphicsItem* a, QGraphicsItem* b)
{
    if(!a || !b) return false;

    double distance = std::sqrt( (a->x() - b->x()) * (a->x() - b->x()) + (a->y() - b->y()) * (a->y() - b->y()) );

    return distance < 15;
}

void CollisionManager::checkMissileEnemyCollisions(QList<Missile*>& missiles, QList<Enemy*>& enemies)
{
    for (Missile *missile : missiles){
        for(Enemy *enemy : enemies) {
            if (checkCollision(missile, enemy)) {
                emit enemyHit(missile, enemy);
                break;
            }
        }
    }
}

void CollisionManager::checkBuildEnemyCollision(Build *build, QList<Enemy*>& enemies)
{
    for(Enemy *enemy : enemies){
        if (checkCollision(build, enemy)) {
            emit buildHit(enemy);
        }
    }
}