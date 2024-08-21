//
// Created by Ethan Lee on 7/13/24.
//

#ifndef JOSHENGINE_GAME_H
#define JOSHENGINE_GAME_H

enum GameState {
    PLAYING,
    MAIN_MENU,
    DEATH_MENU,
    MAP_BUILDER
};

void gameSetup();
int* getHealthPtr();
int* getCurrentMapPtr();
GameState getCurrentGameState();
void setCurrentGameState(GameState g);
void loadMap1GP();
void loadMap2GP();
void loadLastMap();
void loadLastMapGP();

#endif //JOSHENGINE_GAME_H