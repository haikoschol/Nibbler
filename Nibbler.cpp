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

#include "Nibbler.h"
#include <iterator>

Nibbler::Nibbler(std::string sprite_filename)
{
    sprite      = new Sprite(sprite_filename, "nibblerSprite");
    free_sprite = true;
    init();
}

Nibbler::Nibbler(Sprite* sprite)
{
    this->sprite = sprite;
    free_sprite  = false;
    init();
}

void Nibbler::init()
{
    position    = new SDL_Rect;
    position->x = 320;
    position->y = 240;
    position->w = sprite->getWidth();
    position->h = sprite->getHeight();
    score       = 0;
    speed       = 1;
    x_direction = 1;
    y_direction = 0;
    length      = 5;

    for (unsigned int i = 0; i < length; i++) {
        SDL_Rect* tmp = new SDL_Rect;
        tmp->x = position->x - (i+1) * sprite->getWidth();
        tmp->y = position->y;
        tmp->w = position->w;
        tmp->h = position->h;
        tail.push_back(tmp);
    }
    move_delay = SDL_GetTicks();
}

Nibbler::~Nibbler()
{
    delete position;
    if (free_sprite)
        delete sprite;
}

bool Nibbler::handleInput(int direction)
{
    if (direction < 0 || direction > 3)
        return false;
    input_buffer.push_back(direction);
    return true;
}

void Nibbler::paint(SDL_Surface* screen)
{
    sprite->paint(screen, position);
    std::list<SDL_Rect*>::iterator iter;
    for (iter = tail.begin(); iter != tail.end(); iter++)
        sprite->paint(screen, *iter);
}

void Nibbler::move()
{
    if (SDL_GetTicks() - move_delay > (100-speed*10)) {
        SDL_Rect* tmp = new SDL_Rect;
        tmp->x = position->x + x_direction * position->w;
        tmp->y = position->y + y_direction * position->h;
        tmp->w = position->w;
        tmp->h = position->h;
        tail.push_front(position);
        position = tmp;
        if (tail.size()-1 == length) {
            tmp = tail.back();
            tail.pop_back();
            delete tmp;
        }
        move_delay = SDL_GetTicks();
        if (!input_buffer.empty()) {
            int tmp = input_buffer.front();
            input_buffer.pop_front();
            setDirection(tmp);
        }
    }
}

bool Nibbler::checkCollision()
{
    bool result = false;
    std::list<SDL_Rect*>::iterator iter;
    for (iter = tail.begin(); iter != tail.end(); iter++)
        if (checkCollision(*iter))
            result = true;
    return result;
}

bool Nibbler::checkCollision(Item* item)
{
    return checkCollision(item->getPosition());
}

bool Nibbler::checkCollision(const SDL_Rect* b)
{
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    left_a = position->x;
    right_a = position->x + position->w;
    top_a = position->y;
    bottom_a = position->y + position->h;

    left_b = b->x;
    right_b = b->x + b->w;
    top_b = b->y;
    bottom_b = b->y + b->h;

    if(bottom_a <= top_b) {
        return false;
    }
    if(top_a >= bottom_b) {
        return false;
    }
    if(right_a <= left_b) {
        return false;
    }
    if(left_a >= right_b) {
        return false;
    }
    return true;
}

void Nibbler::setDirection(int direction)
{
    if (DIR_LEFT == direction && 1 == x_direction)
        return;
    if (DIR_RIGHT == direction && -1 == x_direction)
        return;
    if (DIR_UP == direction && 1 == y_direction)
        return;
    if (DIR_DOWN == direction && -1 == y_direction)
        return;

    switch (direction) {
        case DIR_LEFT :
            x_direction = -1;
            y_direction = 0;
            break;
        case DIR_RIGHT :
            x_direction = 1;
            y_direction = 0;
            break;
        case DIR_UP :
            x_direction = 0;
            y_direction = -1;
            break;
        case DIR_DOWN :
            x_direction = 0;
            y_direction = 1;
            break;
        default : break;
    }
}
