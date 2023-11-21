#include "app.hpp"
#include "sdl.hpp"

#include <iostream>
#include <gtc/matrix_transform.hpp>

static SDL_Window *window = NULL;
static SDL_Surface *surface = NULL;
static SDL_GLContext context = NULL;
static SDL_Event event;

static bool running = true;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define WINDOW_TITLE "KitsuneCraft"

static glm::mat4 trans(1.0f);
static glm::mat4 proj;

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
        proj = glm::perspective(glm::radians(45.0f),(float)(width()/height()),0.1f,1000.0f);
        float verts[] = {
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };
        trans = glm::rotate(trans,glm::radians(3.0f),glm::vec3(0,0,1));
        _opengl.setDiffuseColor(1,0,0);
        _opengl.setProjection(proj);
        _opengl.setModel(trans);
        _opengl.setView(glm::mat4(1.0f));
        _opengl.drawQuad(verts,sizeof(verts),4);
        SDL_GL_SwapWindow(window);
    }
}