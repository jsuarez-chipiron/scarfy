# Scarfy

## Intro

Scarfy is a C++ simple game that uses the Raylib library. 

The resources are mosty taken from the raylib resources and the game play is very simple


## Compile

It compiles to executable (just tested at the moment on aarch64) and to webassembly. Emscripten is needed for that purpose.

```
make clean && make
```

### Compile just for aarch64

```
make clean && make mac
```

### Compile just for Webassembly

```
make clean && make main
```

## GamePlay

Scarfy jumps when the SPACE bar is pressed. Avoid the rolling stones.
