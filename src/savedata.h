//
// Created by Ethan Lee on 8/15/24.
//

#ifndef JOSHENGINE_SAVEDATA_H
#define JOSHENGINE_SAVEDATA_H

struct SaveData {
    unsigned int maxWaveM1;
    unsigned long maxScoreM1;
    unsigned int maxWaveM2;
    unsigned long maxScoreM2;
};

void writeSave(SaveData sd);
SaveData readSave();

#endif //JOSHENGINE_SAVEDATA_H
