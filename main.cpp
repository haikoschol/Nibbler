/*
 * Copyright (c) Haiko Schol (http://www.haikoschol.com/)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <cstdlib>
#include <string>
#include <vector>
#include "SDL.h"
#include "Nibbler.h"
#include "Timer.h"

int main(int argc, char** argv)
{
    Nibbler* nibbler = new Nibbler("res/nibbler_sprite.png");
    Timer* fps = new Timer();
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    atexit(SDL_Quit);
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (!screen)
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
    bool done = false;
    std::vector<Item*> walls;
    Sprite* wallsprite = new Sprite("res/nibbler_sprite.png", "WallSprite");
    if (NULL == wallsprite)
        printf("wallsprite == NULL!\n");
    int num_x_walls = 640 / wallsprite->getWidth();
    int num_y_walls = 480 / wallsprite->getHeight();
    for (int y = 0; y < num_y_walls; y++) {
        for (int x = 0; x < num_x_walls; x++) {
            if ((0 == y || y == num_y_walls - 1) ||
                (0 == x || x == num_x_walls - 1)) {
                Item* tmp = new Item("res/nibbler_sprite.png", "Wall");
                if (NULL == tmp)
                    printf("tmp == NULL!\n");
                tmp->setPosition(x * wallsprite->getWidth(),
                                y * wallsprite->getHeight());
                walls.push_back(tmp);
            }
        }
    }
    Item* apple = new Item("res/nibbler_sprite.png", "Apple", 10, 3);
    while (!done)
    {
        fps->start();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_QUIT: done = true; break;
                case SDL_KEYDOWN:
                {
                    bool result;
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        done = true;
                    } else if (event.key.keysym.sym == SDLK_LEFT) {
                        result = nibbler->handleInput(Nibbler::DIR_LEFT);
                    } else if (event.key.keysym.sym == SDLK_RIGHT) {
                        result = nibbler->handleInput(Nibbler::DIR_RIGHT);
                    } else if (event.key.keysym.sym == SDLK_UP) {
                        result = nibbler->handleInput(Nibbler::DIR_UP);
                    } else if (event.key.keysym.sym == SDLK_DOWN) {
                        result = nibbler->handleInput(Nibbler::DIR_DOWN);
                    } else if (event.key.keysym.sym == SDLK_a) {
                        nibbler->setSpeed(nibbler->getSpeed()+1);
                    } else if (event.key.keysym.sym == SDLK_s) {
                        nibbler->setSpeed(nibbler->getSpeed()-1);
                    }
                    break;
                }
            }
        }
        nibbler->move();
        if (nibbler->checkCollision()) {
            done = true;   // FIXME
        }
        if (nibbler->checkCollision(apple)) {
            nibbler->consumeItem(apple);
            delete apple;
            apple = new Item(new Sprite("res/nibbler_sprite.png", "AppleSprite"),
                             "Apple", 10, 3);
        }
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        for (unsigned int i = 0; i < walls.size(); i++) {
            walls[i]->paint(screen);
            if (nibbler->checkCollision(walls[i]))
                done = true;
        }
        nibbler->paint(screen);
        apple->paint(screen);
        SDL_Flip(screen);
        while (fps->getTicks() < 1000 / Timer::FRAMES_PER_SECOND);
    }
    printf("Your Score: %d\n", nibbler->getScore());
    delete nibbler;
    return 0;
}

