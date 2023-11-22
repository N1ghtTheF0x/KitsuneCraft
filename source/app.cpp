#include "app.hpp"
#include "sdl.hpp"
#include "camera.hpp"
#include "block.hpp"

#include <iostream>
#include <map>
#include <gtc/matrix_transform.hpp>

static SDL_Window *window = NULL;
static SDL_Surface *surface = NULL;
static SDL_GLContext context = NULL;
static SDL_Event event;

static bool running = true;
static std::map<int,bool> keyboard;
static Uint64 currentTime = 0;
static Uint64 lastTime = 0;

static float mouseX = 0;
static float mouseY = 0;
static float lastMouseX = 0;
static float lastMouseY = 0;
static float offsetMouseX() {return mouseX - lastMouseX;}
static float offsetMouseY() {return lastMouseY - mouseY;}

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

static void setTitle(std::string title)
{
    SDL_SetWindowTitle(window,title.c_str());
}

namespace N1ghtTheF0x::KitsuneCraft
{
    static Camera camera;
    static Block block(0,0,0);
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
        gl::glEnable(gl::GL_DEPTH_TEST);
        _opengl.init();
        proj = glm::perspective(glm::radians(70.0f),(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1f,100.0f);
        _opengl.setProjection(proj);
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
                case SDL_EVENT_KEY_DOWN:
                    keyboard.insert_or_assign(event.key.keysym.sym,true);
                    break;
                case SDL_EVENT_KEY_UP:
                    keyboard.insert_or_assign(event.key.keysym.sym,false);
                    break;
                case SDL_EVENT_MOUSE_MOTION:
                    lastMouseX = mouseX;
                    lastMouseY = mouseY;
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    break;
            }
        }
    }
    void App::_update()
    {
        lastTime = currentTime;
        currentTime = SDL_GetTicks();
        Uint64 delta = currentTime - lastTime;
        float deltaTime = (float)delta/1000;
        auto yaw = camera.yaw();
        auto pitch = camera.pitch();
        if(delta != 0)
            setTitle(
                std::string(WINDOW_TITLE).append(" ")
                .append(std::to_string(60/delta).append(" "))
                .append(std::to_string(yaw)).append(".")
                .append(std::to_string(pitch))
            );

        auto pos = camera.position();
        auto dir = camera.target();
        auto up = camera.up();
        float spd = 1.25f * deltaTime;
        if(keyboard[SDLK_w])
            pos += dir * spd;
        if(keyboard[SDLK_s])
            pos -= dir * spd;
        if(keyboard[SDLK_a])
            pos -= glm::normalize(glm::cross(dir,up)) * spd;
        if(keyboard[SDLK_d])
            pos += glm::normalize(glm::cross(dir,up)) * spd;
        if(keyboard[SDLK_SPACE])
            pos.y += spd;
        if(keyboard[SDLK_LSHIFT])
            pos.y -= spd;
        camera.setPosition(pos);

        if(keyboard[SDLK_LEFT])
            yaw -= spd * 25;
        if(keyboard[SDLK_RIGHT])
            yaw += spd * 25;
        if(keyboard[SDLK_UP])
            pitch += spd * 25;
        if(keyboard[SDLK_DOWN])
            pitch -= spd * 25;
        camera.setTarget(yaw,pitch);
    }
    void App::_draw()
    {
        _opengl.clear();
        _opengl.resize(width(),height());
        _opengl.setModel(glm::mat4(1.0f));
        _opengl.setView(camera.view());
        block.draw(_opengl);
        SDL_GL_SwapWindow(window);
    }
}