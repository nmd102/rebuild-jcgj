//
// Created by Ethan Lee on 8/15/24.
//

#include "savedata.h"
#include <iostream>
#include <fstream>

// Quick n dirty
void writeSave(SaveData sd) {
    char writeArray[sizeof(SaveData)];
    memcpy(&writeArray[0], &sd, sizeof(SaveData));
    std::ofstream file("./gamedat.jsv", std::ios::binary);
    file.write(reinterpret_cast<const char *>(&writeArray[0]), sizeof(SaveData));
    file.close();
}

// Quick n very very dirty, probably a security risk somehow. Don't care, this is free game jam game
unsigned int callDepth = 0;
SaveData readSave() {
    std::ifstream file("./gamedat.jsv", std::ios::binary);
    if (!file.good() && callDepth++ < 5) { // Can't read? Just try again, but don't loop forever.
        writeSave({0, 0, 0, 0});
        return readSave();
    } else if (callDepth == 5) {
        std::cerr << "Couldn't read or write save data." << std::endl;
        exit(1);
    }
    char readArray[sizeof(SaveData)];
    for (char & i : readArray){
        file.get(i);
    }
    return *reinterpret_cast<SaveData*>(&readArray[0]);
}