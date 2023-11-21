# KitsuneCraft

My dirty way of making a Minecraft clone

## I now understand OpenGL

Somehow I learned how to OpenGL:

### Init
1. after making window, create opengl context
2. initialize opengl with any loader
3. compile both shaders
4. link shaders to program
5. get uniform location
6. delete shaders
7. generate vbo, vao
### When updating uniform
1. use program
2. set uniform
### For drawing something:
1. bind vao
2. bind ARRAY_BUFFER to vbo
3. buffer vertices data into ARRAY_BUFFER
3. set vertex attr pointer of <layout>
3. enable vertex attr array <layout>
4. use program
5. bind vao
6. draw now
### Loading image as texture
1. gen texture
2. bind texture to GL_TEXTURE_2D
3. glTexParameteri anything you want
4. load image
5. glTexImage2D that data there
    - generate mip map if you want
6. if you can unload image, do it here
### Draw Loop
1. clear color | depth
2. active texture GL_TEXTURE<number> and bind GL_TEXTURE_2D to image
3. use program
4. set view/projection
5. bind vao
6. for each object:
    1. translate/rotate/scale (set model)
    2. draw now
7. swap buffers