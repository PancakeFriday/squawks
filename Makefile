CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_PATHS := -Llib/
LD_FLAGS := -lsfml-system -lsfml-graphics -lsfml-audio -lsfml-window
CC_FLAGS := -O0 -Wall --std=c++11 -Iincl/ -MMD

main: $(OBJ_FILES)
	clang++ $(LD_PATHS) -o $@ $^ $(LD_FLAGS)
obj/%.o: src/%.cpp
	clang++ $(CC_FLAGS) -c -o $@ $<
