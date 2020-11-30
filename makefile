COMPILER_OPTIONS = -c -Wall -std=c++14 -m64 -g 
COMPILER_INCLUDE = #-I /home/EmilyEclipse/Projects/C++/BREAKOUT/include/
LINKER_OPTIONS =  -lSDL2main -lSDL2

LINKER_FILES = obj/renderwindow.o obj/draw.o obj/rectangle.o obj/paddle.o obj/main.o

all: LINKER_OPTIONS += -o bin/debug/main
all: compiler
all: linker

compiler: renderwindow.o
compiler: rectangle.o
compiler: paddle.o
compiler: draw.o
compiler: main.o

linker: $(LINKER_FILES)
	g++ $(LINKER_FILES) $(LINKER_OPTIONS)



main.o: src/main.cpp
	g++ $(COMPILER_INCLUDE) src/main.cpp -o obj/main.o $(COMPILER_OPTIONS)

renderwindow.o: src/renderwindow.cpp
	g++ $(COMPILER_INCLUDE) src/renderwindow.cpp -o obj/renderwindow.o $(COMPILER_OPTIONS)

draw.o: src/draw.cpp
	g++ $(COMPILER_INCLUDE) src/draw.cpp -o obj/draw.o $(COMPILER_OPTIONS)

rectangle.o: src/rectangle.cpp
	g++ $(COMPILER_INCLUDE) src/rectangle.cpp -o obj/rectangle.o $(COMPILER_OPTIONS)

paddle.o: src/paddle.cpp
	g++ $(COMPILER_INCLUDE) src/paddle.cpp -o obj/paddle.o $(COMPILER_OPTIONS)

#-O4 -> "It's joke!"; it's actually equivalent to -O3
release: COMPILER_OPTIONS += -O4
release: LINKER_OPTIONS += -s -o bin/release/BREAKOUT
release: compiler
release: linker

release-windows: COMPILER_OPTIONS += -O4
release-windows: LINKER_OPTIONS += -s -o bin/release/BREAKOUT.exe
release-windows: compiler
release-windows: linker

debug: LINKER_OPTIONS += -o bin/debug/main
debug: compiler
debug: linker