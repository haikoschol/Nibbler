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

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "Sprite.h"

class Item
{
    public:
        Item(Sprite* sprite, std::string name);
        Item(Sprite* sprite, std::string name, int score_delta, int length_delta);
        Item(Sprite* sprite, std::string name, int score_delta, int length_delta,
             int x_pos, int y_pos);
        Item(std::string sprite_filename, std::string name);
        Item(std::string sprite_filename, std::string name, int score_delta,
             int length_delta);
        Item(std::string sprite_filename, std::string name, int score_delta,
             int length_delta, int x_pos, int y_pos);
        ~Item();
        void paint(SDL_Surface* screen) { sprite->paint(screen, position); }
        void setName(std::string name) { this->name = name; }
        std::string getName() { return name; }
        void setScoreDelta(int score_delta) { this->score_delta = score_delta; }
        int getScoreDelta() { return score_delta; }
        void setLengthDelta(int length_delta) { this->length_delta = length_delta; }
        int getLengthDelta() { return length_delta; }
        void setPosition(int x, int y) { position->x = x; position->y = y; }
        const SDL_Rect* getPosition() { return position; }

    private:
        Sprite* sprite;
        std::string name;
        int score_delta;
        int length_delta;
        SDL_Rect* position;
        bool free_sprite;
};
#endif
