#ifndef STRONGMISSILE_H
#define STRONGMISSILE_H

#include "missile.h"

class StrongMissile : public Missile
{
public:
    StrongMissile(Enemy* target);
    
protected:
    void setupVisual() override;
};

#endif