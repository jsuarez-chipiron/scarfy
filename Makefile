all: main mac

main: main.cpp
	emcc -o ./wasm/index.html /home/javier/Tech/cpp/games/raylib/raylib/src/libraylib.a \
    main.cpp -Os -Wall \
    -I. -I/usr/include \
    -I/usr/lib/zig/libc/include/generic-glibc/ \
    -L. -L /usr/lib/ \
    -s USE_GLFW=3 \
    -s ASYNCIFY \
    --shell-file ./shell.html \
	--preload-file resources \
    -s TOTAL_STACK=64MB \
    -s INITIAL_MEMORY=128MB \
    -s ASSERTIONS \
    -DPLATFORM_WEB

mac: main.cpp
	clang++ main.cpp -o main -std=c++20 -I/opt/homebrew/Cellar/raylib/5.0/include -L/opt/homebrew/Cellar/raylib/5.0/lib -lraylib

clean:
	rm -frv main wasm/index.*
