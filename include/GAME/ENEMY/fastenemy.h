#ifndef FASTENEMY_H
#define FASTENEMY_H

#include "enemy.h"

class FastEnemy : public Enemy
{
public:
    FastEnemy(QPointF targetPos);

protected:
    void setupVisual() override;
};
#endif