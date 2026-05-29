#ifndef WEAKMISSILE_H
#define WEAKMISSILE_H

#include "missile.h"

class WeakMissile : public Missile
{
public:
    WeakMissile(Enemy* target);
    
protected:
    void setupVisual() override;
};

#endif