#ifndef TIMER_H
#define TIMER_H
#include "SDL.h"

class Timer {
    public:
        static const int FRAMES_PER_SECOND = 30;

        Timer();
        void start();
        void stop();
        void pause();
        void unpause();
        int getTicks();
        bool isStarted() { return started; }
        bool isPaused() { return paused; }

    private:
        int startTicks;
        int pausedTicks;
        bool paused;
        bool started;
};

#endif
