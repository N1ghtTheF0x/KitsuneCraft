@echo off
node .\scripts\create-hpp.mjs .\shaders\default.vert .\source\shaders\vertex.hpp
node .\scripts\create-hpp.mjs .\shaders\default.frag .\source\shaders\fragment.hpp