//
// Created by Edwin Lau Mack on 5/2/20.
//

#include "Animation.h"

Animation::Animation(int x, int y, int width, int height)
{
    for (int i = 0; i < nFrames; i++)
    {
        frames[i] = {x + i * width, y, width, height};
    }

}

void Animation::ApplyToSprite(sf::Sprite& sprite)
{
    sprite.setTextureRect(frames[iFrame]);
}

void Animation::Update()
{
    Advance();
}

void Animation::Advance()
{
    iFrame++;
}

int Animation::getiFrame()
{
    return iFrame;
}

void Animation::animatedUpdate(float dt)
{
    time += dt;
    while (time >= holdTime)
    {
        time -= holdTime;
        animatedAdvance();
    }
}

void Animation::animatedAdvance()
{
    if (++iFrame >= nFrames)
    {
        iFrame = 0;
    }
}