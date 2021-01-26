COMPILER_INCLUDE = -I include/ -I include/Displayed -I include/Displayed/Blocks\
					-I include/Util#-I /home/EmilyEclipse/Projects/C++/BREAKOUT/include/
COMPILER_OPTIONS = -c -Wall -std=c++14 -m64 -g

BASE_LINKER_FILES = obj/renderwindow.o obj/draw.o obj/rectangle.o \
				obj/keyboard.o obj/paddle.o obj/ball.o obj/blocks.o obj/geometry.o \
				obj/drawregistry.o

LINKER_OPTIONS =  -lSDL2main -lSDL2 -lSDL2_ttf
LINKER_FILES = $(BASE_LINKER_FILES) obj/main.o

TEST_LINKER_FILES = $(BASE_LINKER_FILES) test/main.o

TEST_LINKER_OPTIONS = $(LINKER_OPTIONS) -lpthread -lgtest

UnitTests:	$(TEST_LINKER_FILES)
	g++ $(TEST_LINKER_FILES) $(TEST_LINKER_OPTIONS) -o bin/debug/UnitTests

test/main.o: test/main.cpp
	g++ $(COMPILER_INCLUDE) test/main.cpp -o test/main.o $(COMPILER_OPTIONS)

BREAKOUT: $(LINKER_FILES)
	g++ $(LINKER_FILES) $(LINKER_OPTIONS) -o bin/debug/BREAKOUT

obj/main.o: src/main.cpp
	g++ $(COMPILER_INCLUDE) src/main.cpp -o obj/main.o $(COMPILER_OPTIONS)

obj/renderwindow.o: src/renderwindow.cpp include/RenderWindow.hpp
	g++ $(COMPILER_INCLUDE) src/renderwindow.cpp -o obj/renderwindow.o $(COMPILER_OPTIONS)

obj/draw.o: src/draw.cpp include/Draw.hpp
	g++ $(COMPILER_INCLUDE) src/draw.cpp -o obj/draw.o $(COMPILER_OPTIONS)

obj/rectangle.o: src/rectangle.cpp include/Rectangle.hpp
	g++ $(COMPILER_INCLUDE) src/rectangle.cpp -o obj/rectangle.o $(COMPILER_OPTIONS)

obj/keyboard.o: src/keyboard.cpp include/Keyboard.hpp
	g++ $(COMPILER_INCLUDE) src/keyboard.cpp -o obj/keyboard.o $(COMPILER_OPTIONS)

obj/paddle.o: src/paddle.cpp include/Displayed/Paddle.hpp
	g++ $(COMPILER_INCLUDE) src/paddle.cpp -o obj/paddle.o $(COMPILER_OPTIONS)

obj/ball.o: src/ball.cpp include/Displayed/Ball.hpp
	g++ $(COMPILER_INCLUDE) src/ball.cpp -o obj/ball.o $(COMPILER_OPTIONS)

obj/blocks.o: src/blocks.cpp include/Displayed/Blocks/*
	g++ $(COMPILER_INCLUDE) src/blocks.cpp -o obj/blocks.o $(COMPILER_OPTIONS)

obj/geometry.o: src/geometry.cpp include/Geometry.hpp
	g++ $(COMPILER_INCLUDE) src/geometry.cpp -o obj/geometry.o $(COMPILER_OPTIONS)

obj/drawregistry.o: src/drawregistry.cpp include/DrawRegistry.hpp
	g++ $(COMPILER_INCLUDE) src/drawregistry.cpp -o obj/drawregistry.o $(COMPILER_OPTIONS)