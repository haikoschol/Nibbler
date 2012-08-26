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
#include "Item.h"

Item::Item(Sprite* sprite, std::string name)
{
    this->sprite = sprite;
    this->name   = name;
    score_delta  = 0;
    length_delta = 0;
    srand(time(NULL));
    position    = new SDL_Rect;
    position->x = 20 + rand() % 600;    // FIXME
    position->y = 20 + rand() % 440;    // FIXME
    position->w = sprite->getWidth();
    position->h = sprite->getHeight();
    free_sprite = false;

}

Item::Item(Sprite* sprite, std::string name, int score_delta, int length_delta)
{
    this->sprite       = sprite;
    this->name         = name;
    this->score_delta  = score_delta;
    this->length_delta = length_delta;
    srand(time(NULL));
    position    = new SDL_Rect;
    position->x = 20 + rand() % 600;    // FIXME
    position->y = 20 + rand() % 440;    // FIXME
    position->w = sprite->getWidth();
    position->h = sprite->getHeight();
    free_sprite = false;
}

Item::Item(Sprite* sprite, std::string name, int score_delta, int length_delta,
           int x_pos, int y_pos)
{
    this->sprite       = sprite;
    this->name         = name;
    this->score_delta  = score_delta;
    this->length_delta = length_delta;
    position    = new SDL_Rect;
    position->x = x_pos;
    position->y = y_pos;
    position->w = sprite->getWidth();
    position->h = sprite->getHeight();
    free_sprite = false;
}

Item::Item(std::string sprite_filename, std::string name)
{
    sprite       = new Sprite(sprite_filename, name);
    this->name   = name;
    score_delta  = 0;
    length_delta = 0;
    srand(time(NULL));
    position    = new SDL_Rect;
    position->x = 20 + rand() % 600;    // FIXME
    position->y = 20 + rand() % 440;    // FIXME
    position->w = sprite->getWidth();
    position->h = sprite->getHeight();
    free_sprite = true;

}

Item::Item(std::string sprite_filename, std::string name, int score_delta,
           int length_delta)
{
    sprite             = new Sprite(sprite_filename, name);
    this->name         = name;
    this->score_delta  = score_delta;
    this->length_delta = length_delta;
    srand(time(NULL));
    position    = new SDL_Rect;
    position->x = 20 + rand() % 600;    // FIXME
    position->y = 20 + rand() % 440;    // FIXME
    position->w = sprite->getWidth();
    position->h = sprite->getHeight();
    free_sprite = true;
}

Item::Item(std::string sprite_filename, std::string name, int score_delta,
           int length_delta, int x_pos, int y_pos)
{
    sprite             = new Sprite(sprite_filename, name);
    this->name         = name;
    this->score_delta  = score_delta;
    this->length_delta = length_delta;
    position    = new SDL_Rect;
    position->x = x_pos;
    position->y = y_pos;
    position->w = sprite->getWidth();
    position->h = sprite->getHeight();
    free_sprite = true;
}

Item::~Item()
{
    if (free_sprite)
        delete sprite;
}
