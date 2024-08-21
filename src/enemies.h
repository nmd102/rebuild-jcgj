//
// Created by Ethan Lee on 7/24/24.
//

#ifndef JOSHENGINE_ENEMIES_H
#define JOSHENGINE_ENEMIES_H

#include "engine/engine.h"

void enemySystemInit();
void instantiateRandomEnemyWave(int count);
void initWorldBoxColliders(std::vector<Transform> boxes);

#endif //JOSHENGINE_ENEMIES_H
