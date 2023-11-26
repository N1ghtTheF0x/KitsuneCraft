#include <N1ghtTheF0x/KitsuneCraft/SDL.hpp>
#include <iostream>

namespace N1ghtTheF0x::KitsuneCraft::SDL
{
    void init()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "Couldn't init SDL Video: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    void deinit()
    {
        SDL_Quit();
    }
}