#ifndef __N1GHTTHEF0X_KITSUNECRAFT_APP_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_APP_HPP

#include "opengl.hpp"

namespace N1ghtTheF0x::KitsuneCraft
{
    class App
    {
    private:
        OpenGL _opengl;
        void _init_sdl();
        void _create_window();

        void _loop();

        void _event();
        void _update();
        void _draw();
    public:
        App();
        ~App();
        int run();
    };
}

#endif