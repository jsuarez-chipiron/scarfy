main: main.cpp
	clang++ main.cpp -o main -std=c++20 -I/opt/homebrew/Cellar/raylib/5.0/include -L/opt/homebrew/Cellar/raylib/5.0/lib -lraylib

clean:
	rm -frv main
