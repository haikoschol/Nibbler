#include <cstdlib>
#include "Sprite.h"

Sprite::Sprite(std::string image_filename, std::string name)
{
    image = loadImage(image_filename);
    this->name = name;
}

Sprite::~Sprite()
{
    SDL_FreeSurface(image);
}

void Sprite::paint(SDL_Surface* screen, SDL_Rect* position)
{
    SDL_BlitSurface(image, NULL, screen, position);
}

SDL_Surface* Sprite::loadImage(std::string image_filename)
{
    SDL_Surface* loadedImage = NULL;
    //SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load(image_filename.c_str());
/*
    if(loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        if(optimizedImage != NULL) {
            SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY,
                            0x00FFFF);
            printf("loadImage2()\n");

        }
    }
    return optimizedImage;*/
    return loadedImage;
}
