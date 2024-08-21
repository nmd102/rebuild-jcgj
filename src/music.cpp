//
// Created by Ethan Lee on 8/6/24.
//

#include "music.h"
#include "game.h"
#include "engine/engine.h"
#include "engine/sound/audioutil.h"

std::vector<Sound> musicTracks{};

void initMusic() {
    musicTracks.emplace_back(vec3(0), vec3(0), "./sounds/automated-serenade.ogg", true, 3, 0.1, 2, 0.25);
    musicTracks.emplace_back(vec3(0), vec3(0), "./sounds/slep.ogg", true, 3, 0.1, 2, 0.25);

    musicTracks.emplace_back(vec3(0), vec3(0), "./sounds/real-stuff.ogg", true, 3, 0.1, 2, 0.25);
    musicTracks.emplace_back(vec3(0), vec3(0), "./sounds/numis.ogg", true, 3, 0.1, 2, 0.25);
    musicTracks.emplace_back(vec3(0), vec3(0), "./sounds/rush-hour.ogg", true, 3, 0.1, 2, 0.25);
    musicTracks.emplace_back(vec3(0), vec3(0), "./sounds/clapstrike.ogg", true, 3, 0.1, 2, 0.25);
}

void playTrack(MusicTrack track) {
    for (auto t : musicTracks) {
        if (t.isPlaying()) t.stop(); // Just in case
    }
    musicTracks[track].play();
}

void playRandomThematic() {
    if (getCurrentGameState() == PLAYING) {
        playTrack(static_cast<MusicTrack>(GAME_0 + rand() % 4));
    } else {
        playTrack(static_cast<MusicTrack>(MENU_0 + rand() % 2));
    }
}