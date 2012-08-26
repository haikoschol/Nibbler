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

#ifndef NIBBLER_H
#define NIBBLER_H
#include <string>
#include <list>
#include "SDL.h"
#include "Sprite.h"
#include "Timer.h"
#include "Item.h"

class Nibbler
{
    public:
        static const int DIR_LEFT  = 0;
        static const int DIR_RIGHT = 1;
        static const int DIR_UP    = 2;
        static const int DIR_DOWN  = 3;

        Nibbler(std::string sprite_filename);
        Nibbler(Sprite* sprite);
        ~Nibbler();
        bool handleInput(int direction);
        void paint(SDL_Surface* screen);
        void move();
        bool checkCollision();
        bool checkCollision(Item* item);

        const Sprite* getSprite() { return sprite; }
        void setSprite(Sprite* sprite) { this->sprite = sprite; }
        const SDL_Rect* getPosition() { return position; }
        void setPosition(int x, int y) { position->x = x; position->y = y; }
        int getScore() { return score; }
        void setScore(int score) { this->score = score; }
        int getSpeed() { return speed; }
        void setSpeed(int speed)
        {
            if (speed > 0 && speed < 10)
                this->speed = speed;
        }
        int getLength() { return length; }
        void setLength(int length) { this->length = length; }
        void consumeItem(Item* item)
        {
            score  += item->getScoreDelta();
            length += item->getLengthDelta();
        }

    private:
        struct motion {
            SDL_Rect* position;
            int speed;
            int direction;
        };
        typedef struct motion motion;

        Sprite* sprite;
        SDL_Rect* position;
        unsigned int move_delay;
        unsigned int score;
        unsigned int speed;
        unsigned int length;
        int x_direction;
        int y_direction;
        bool free_sprite;
        std::list<SDL_Rect*> tail;
        std::list<int> input_buffer;
        void init();
        void setDirection(int direction);
        bool checkCollision(const SDL_Rect* b);
};
#endif
