#include"sound.h"
irrklang::ISoundEngine* SoundEngine;

namespace sound{
    void init(double volume){
        // 初始化音频设备
        SoundEngine = irrklang::createIrrKlangDevice();
        SoundEngine->play2D("resources/sound/fire.wav", GL_FALSE);
        SoundEngine->play2D("resources/sound/boom.wav", GL_FALSE);
        SoundEngine->stopAllSounds();
        SoundEngine->setSoundVolume(volume);
    }

    void fire(){
        SoundEngine->play2D("resources/sound/fire.wav", GL_FALSE);
    }

    void boom(){
        SoundEngine->play2D("resources/sound/boom.wav", GL_FALSE);
    }
}