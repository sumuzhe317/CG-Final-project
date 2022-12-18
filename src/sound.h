// author: Tengyang Zheng
// use to play the sound
#ifndef SOUND_H
#define SOUND_H
#include "base_func.h"
#include <irrklang/irrKlang.h>

extern irrklang::ISoundEngine* SoundEngine;

namespace sound{
    void init();

    void fire();

    void boom();
}

#endif