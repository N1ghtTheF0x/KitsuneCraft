#include <N1ghtTheF0x/KitsuneCraft/App.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace N1ghtTheF0x::KitsuneCraft
{
    static Mesh _mesh = {
        {
            // positions          // colors                // texture coords
            {0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,1.0f,   1.0f, 1.0f},   // top right
            {0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,1.0f,   1.0f, 0.0f},   // bottom right
            {-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,1.0f,   0.0f, 0.0f},   // bottom left
            {-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,1.0f,   0.0f, 1.0f}    // top left 
        },
        {
            0,1,3,
            1,2,3
        }
    };

    static Texture _tex("test.bmp");

    Application::Application(int argc,char** argv): _argv(argv,argv + argc)
    {
        SDL::init();
    }
    Application::~Application()
    {
        SDL_DestroyWindow(_window);
        SDL::deinit();
    }
    int Application::run()
    {
        _init();
        _loop();
        return EXIT_SUCCESS;
    }
    void Application::_init()
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
#ifndef NDEBUG
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
        _window = SDL_CreateWindow(KC_WINDOW_TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,KC_WINDOW_WIDTH,KC_WINDOW_HEIGHT,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if(_window == NULL)
        {
            std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        _gl = SDL_GL_CreateContext(_window);
        if(_gl == NULL)
        {
            std::cerr << "Couldn't create context: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        if(SDL_GL_MakeCurrent(_window,_gl) < 0)
        {
            std::cerr << "Couldn't set current context: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        int glad_version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

        auto version = glGetString(GL_VERSION);
        auto renderer = glGetString(GL_RENDERER);
        auto vendor = glGetString(GL_VENDOR);
        auto glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
        std::cout << "Version: " << version <<
        std::endl << "Renderer: " << renderer <<
        std::endl << "Vendor: " << vendor <<
        std::endl << "GLSL: " << glsl << std::endl;
        glEnable(GL_DEPTH_TEST);
        _context.init();
        _tex.load();
    }
    void Application::_loop()
    {
        while(_running)
        {
            _event();
            if(!_running)
                break;
            _update();
            _draw();
        }
    }
    void Application::_event()
    {   
        SDL_Event event;
        while(SDL_PollEvent(&event))
        switch(event.type)
        {
            case SDL_QUIT:
                _running = false;
                break;
        }
    }
    void Application::_update()
    {

    }
    void Application::_draw()
    {
        int width, height;
        SDL_GetWindowSize(_window,&width,&height);
        glViewport(0,0,width,height);
        _context.clear();
        glm::mat4 view(1.0f);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f),(float)width/(float)height,0.1f,100.0f);
        glm::mat4 model(1.0f);
        model = glm::translate(model,{0,0,-5});
        //_context.setView(view);
        //_context.setProjection(proj);
        //_context.setModel(model);
        //_context.setDiffuseTexture(_tex);
        _context.prepare(_mesh);
        //_tex.bind();
        auto &i = _mesh.indices;
        _context.drawTri(i.size());
        SDL_GL_SwapWindow(_window);
    }
}