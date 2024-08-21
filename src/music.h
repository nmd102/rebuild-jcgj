//
// Created by Ethan Lee on 8/6/24.
//

#ifndef JOSHENGINE_MUSIC_H
#define JOSHENGINE_MUSIC_H

enum MusicTrack {
    MENU_0,
    MENU_1,
    GAME_0,
    GAME_1,
    GAME_2,
    GAME_3
};

void initMusic();
void playTrack(MusicTrack track);
void playRandomThematic();

#endif //JOSHENGINE_MUSIC_H
