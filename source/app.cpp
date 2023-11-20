#include "app.hpp"
#include "sdl.hpp"

#include <iostream>

static SDL_Window *window = NULL;
static SDL_Surface *surface = NULL;
static SDL_GLContext context = NULL;
static SDL_Event event;

static bool running = true;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define WINDOW_TITLE "KitsuneCraft"

static int width()
{
    int w;
    SDL_GetWindowSize(window,&w,NULL);
    return w;
}

static int height()
{
    int h;
    SDL_GetWindowSize(window,NULL,&h);
    return h;
}

namespace N1ghtTheF0x::KitsuneCraft
{
    App::App()
    {
        _init_sdl();   
    }
    App::~App()
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    int App::run()
    {
        _create_window();
        _loop(); 
        return 0;
    }
    void App::_create_window()
    {
        window = SDL_CreateWindow(WINDOW_TITLE,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_OPENGL);
        if(window == NULL)
        {
            std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        surface = SDL_GetWindowSurface(window);
        context = SDL_GL_CreateContext(window);
        if(context == NULL)
        {
            std::cerr << "Couldn't create context: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        glbinding::initialize(SDL_GL_GetProcAddress);
        auto version = gl::glGetString(gl::GL_VERSION);
        auto renderer = gl::glGetString(gl::GL_RENDERER);
        std::cout << "OpenGL " << version << ", " << renderer << std::endl;
        _opengl.init();
    }
    void App::_init_sdl()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "Couldn't init video: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    void App::_loop()
    {
        while(running)
        {
            _event();
            _update();
            _draw();
        }
    }
    void App::_event()
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
            }
        }
    }
    void App::_update()
    {

    }
    void App::_draw()
    {
        _opengl.clear();
        _opengl.resize(width(),height());
        float verts[] = {
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };
        float r = (float)rand()/RAND_MAX;
        float g = (float)rand()/RAND_MAX;
        float b = (float)rand()/RAND_MAX;
        _opengl.setDiffuseColor(r,g,b);
        _opengl.drawQuad(verts,sizeof(verts),4);
        SDL_GL_SwapWindow(window);
    }
}