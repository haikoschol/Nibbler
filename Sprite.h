#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include "SDL.h"
#include "SDL_image.h"

class Sprite
{
    public:
        Sprite(std::string image_filename, std::string name);
        ~Sprite();
        void paint(SDL_Surface* screen, SDL_Rect* position);

        const std::string getName() { return name; }
        void setName(std::string name) { this->name = name; }
        int getWidth() { return image->w; }
        int getHeight() { return image->h; }

    private:
        SDL_Surface* image;
        std::string name;
        SDL_Surface* loadImage(std::string image_filename);
};
#endif
