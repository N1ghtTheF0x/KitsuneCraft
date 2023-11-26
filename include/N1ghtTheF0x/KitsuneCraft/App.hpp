#ifndef __N1GHTTHEF0X_KITSUNECRAFT_APP_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_APP_HPP

#include "Utils.hpp"
#include "Context.hpp"

#include <vector>
#include <string>

namespace N1ghtTheF0x::KitsuneCraft
{
    class Application
    {
    private:
        std::vector<std::string> _argv;

        SDL_Window *_window = NULL;
        SDL_GLContext _gl = NULL;

        bool _running = true;
        Context _context;

        void _init();

        void _loop();
        void _event();
        void _update();
        void _draw();
    public:
        Application(int argc,char** argv);
        ~Application();
        int run();
    };
}

#endif