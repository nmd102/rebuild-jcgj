//
// Created by Ethan Lee on 8/3/24.
//

#include "menus.h"
#include "music.h"
#include "engine/engine.h"
#include "game.h"
#include "savedata.h"
#include "gameuiutil.h"
#include <iostream>

void exit0() { // TODO Stupid wrapper function. Bad bad bad.
    exit(0);
}

bool inMenu;
void setInMenu(bool b) {
    inMenu = b;
}

void quoteUnquoteTutorialMenu() {
    clearGameObjects();
    loadLastMap();

    uiStaticText({0, 0.3}, "CONTROLS", 0.03);
    uiStaticText({0, 0.2},"WASD TO MOVE - MOUSE TO LOOK", 0.02);
    uiStaticText({0, 0.15},"SPACE TO JUMP - SHIFT TO DASH - CLICK TO PUNCH", 0.02);
    uiStaticText({0, 0.05},"GAMEPLAY", 0.03);
    uiStaticText({0, -0.05},"PUNCH/JUMP/DASH DESTROY NEARBY ENEMIES", 0.02);
    uiStaticText({0, -0.1},"YOU ONLY HEAL WHEN GROUNDED", 0.02);
    uiStaticText({0, -0.15},"DESTROYING ENEMIES INCREASES YOUR MAX STATS", 0.02);
    uiStaticText({0, -0.2},"", 0.02);
    uiButton({0, -0.25}, "BACK", &loadMainMenu);
}

// TODO this is bad. Like, bad, bad. Can we not?
void map1Menu();
void map2Menu();

void loadMapsMenu() {
    clearGameObjects();
    loadLastMap();

    uiStaticText({0, 0.3}, "SELECT A MAP", 0.03);
    uiButton({0, 0.15},  "CRUCIBLE", &map1Menu);
    uiButton({0, 0.05}, "HIGH RISE", &map2Menu);
    uiButton({0, -0.25}, "BACK", &loadMainMenu);
}

void map1Menu() {
    (*getCurrentMapPtr()) = 0;
    clearGameObjects();
    loadLastMap();
    cameraAccess()->position = glm::vec3(30.000000, 20.000000, 50.000000);
    cameraAccess()->rotation = glm::vec3(210.000000, -10.000000, 3.000000);
    cameraAccess()->scale    = glm::vec3(1.000000, 1.000000, 1.000000);

    SaveData sd = readSave();
    uiStaticText({0, 0.25}, "CRUCIBLE");
    uiStaticText({0, 0.15}, "HIGH SCORE", 0.0125f);
    uiStaticText({0, 0.10}, std::to_string(sd.maxScoreM1), 0.033f);
    uiStaticText({0, 0.00}, "HIGHEST WAVE", 0.0125f);
    float inverseRedIntensity = max(1.0f - (sd.maxWaveM1 / 10.0f), 0.0f);
    uiStaticText({0, -0.05}, std::to_string(sd.maxWaveM1), 0.033f, {1.0f, inverseRedIntensity, inverseRedIntensity});

    uiButton({0, -0.15}, "PLAY", &loadLastMapGP);
    uiButton({0, -0.25}, "BACK", &loadMapsMenu);
}
void map2Menu() {
    (*getCurrentMapPtr()) = 1;
    clearGameObjects();
    loadLastMap();
    cameraAccess()->position = glm::vec3(30.000000, 40.000000, 50.000000);
    cameraAccess()->rotation = glm::vec3(210.000000, -10.000000, 3.000000);
    cameraAccess()->scale    = glm::vec3(1.000000, 1.000000, 1.000000);

    SaveData sd = readSave();
    uiStaticText({0, 0.25}, "HIGH RISE");
    uiStaticText({0, 0.15}, "HIGH SCORE", 0.0125f);
    uiStaticText({0, 0.10}, std::to_string(sd.maxScoreM2), 0.033f);
    uiStaticText({0, 0.00}, "HIGHEST WAVE", 0.0125f);
    float inverseRedIntensity = max(1.0f - (sd.maxWaveM2 / 10.0f), 0.0f);
    uiStaticText({0, -0.05}, std::to_string(sd.maxWaveM2), 0.033f, {1.0f, inverseRedIntensity, inverseRedIntensity});

    uiButton({0, -0.15}, "PLAY", &loadLastMapGP);
    uiButton({0, -0.25}, "BACK", &loadMapsMenu);
}

void loadMainMenu() {
    clearGameObjects();
    loadLastMap();

    //TODO this will cause funny bugs later!
    cameraAccess()->position = glm::vec3(30.000000, 20.000000 * (*getCurrentMapPtr()+1), 50.000000);
    cameraAccess()->rotation = glm::vec3(210.000000, -10.000000, 3.000000);
    cameraAccess()->scale    = glm::vec3(1.000000, 1.000000, 1.000000);
    setCurrentGameState(MAIN_MENU);
    setMouseVisible(true);
    if (!inMenu) {
        playRandomThematic();
        inMenu = true;
    }

    uiStaticText({0, 0.3},   "REBUILD", 0.03);
    uiStaticText({0, 0.255}, "joshco game jam edition", 0.015);
    uiStaticText({0, 0.225}, "written in joshengine by hotcocoancode", 0.01);

    uiButton({0, 0.05},  "ENDLESS", &loadMapsMenu);
    uiButton({0, -0.05}, "MULTIPLAYER", nullptr, {0.005, 0.005}, 0.025f, {1.0f, 1.0f, 1.0f}, true);
    uiButton({0, -0.15}, "MAP EDITOR", nullptr, {0.005, 0.005}, 0.025f, {1.0f, 1.0f, 1.0f}, true);
    uiButton({0, -0.25}, "GUIDE", &quoteUnquoteTutorialMenu);
    uiButton({0, -0.35}, "QUIT", &exit0);
}

void loadDeathMenu() {
    setCurrentGameState(DEATH_MENU);
    setMouseVisible(true);

    // Fullscreen quad. Disabled button, text size 0. Hacky but i dont want to write more code than i have to.
    //uiButton({0, 0}, "FS_QUAD", nullptr, {1, 1}, 0, {0.0f, 0.0f, 0.0f}, true); //Never mind it breaks everything
    uiStaticText({0, 0.1}, "YOU DIED", 0.06);
    uiButton({0, 0.0}, "PLAY AGAIN", &loadLastMapGP);
    uiButton({0, -0.1}, "MAIN MENU", &loadMainMenu);
}