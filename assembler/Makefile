CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

SOURCE  = assembler_main.cpp assembler.cpp ../libs/Onegin.cpp
OBJECT  = assembler_main.o   assembler.o  ../libs/Onegin.o
OUTPUT  = assembler 

INCLUDE_DIR = ../../Onegin
INCLUDE     = onegin

default: valgrind

valgrind: $(OUTPUT)
	valgrind ./$(OUTPUT)"../txt files/asm"

launch: $(OUTPUT)
	./$(OUTPUT)"../txt files/asm"

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

clean:
	rm -f *.o *.a $(OUTPUT)