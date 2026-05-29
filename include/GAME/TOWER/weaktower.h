#ifndef WEAKTOWER_H
#define WEAKTOWER_H

#include "build.h"

class WeakTower : public Build
{
public:
    WeakTower();

protected:
    void setupVisual() override;
};

#endif