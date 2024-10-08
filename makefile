CXXFLAGS = -c -Wall -std=c++17 -I include/

LINKER_OPTIONS = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer

LINKER_FILES = $(BASE_LINKER_FILES) obj/main.o

TEST_LINKER_FILES = $(BASE_LINKER_FILES) test/main.o

TEST_LINKER_OPTIONS = $(LINKER_OPTIONS) -lpthread -lgtest

LINUX: src/*.cpp
	g++ src/*.cpp -I include/ $(LINKER_OPTIONS) -o breakout_game

WINDOWS: $(LINKER_FILES)
	x86_64-w64-mingw32-g++ $(LINKER_FILES) $(LINKER_OPTIONS) -o bin/release/BREAKOUT.EXE

UnitTests:	$(TEST_LINKER_FILES)
	g++ $(TEST_LINKER_FILES) $(TEST_LINKER_OPTIONS) -o bin/debug/UnitTests
