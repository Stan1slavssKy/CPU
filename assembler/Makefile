CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

SOURCE  = assembler_main.cpp assembler.cpp 
OBJECT  = assembler_main.o   assembler.o 
OUTPUT  = assembler 

INCLUDE_DIR = ../../Onegin
INCLUDE     = onegin

default: valgrind

valgrind: $(OUTPUT)
	valgrind ./$(OUTPUT)

launch: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -L$(INCLUDE_DIR) -l$(INCLUDE) -o $(OUTPUT)

main.o: main_cpu.cpp
	$(CXX) $(WARNINGS) $(DEBUG_MODE) main_cpu.cpp -c

stack.o: cpu.cpp
	$(CXX) $(WARNINGS) $(DEBUG_MODE) cpu.cpp -c

clean:
	rm -f *.o *.a $(OUTPUT)
