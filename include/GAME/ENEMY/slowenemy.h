#ifndef SLOWENEMY_H
#define SLOWENEMY_H

#include "enemy.h"

class SlowEnemy : public Enemy
{
public:
    SlowEnemy(QPointF targetPos);

protected:
    void setupVisual() override;
};
#endif