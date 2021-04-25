CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

SOURCE  = cpu.cpp   cpu_main.cpp ../libs/stack.cpp ../libs/protection.cpp ../libs/Onegin.cpp
OBJECT  = cpu.o cpu_main.o       ../libs/stack.o   ../libs/protection.o   ../libs/Onegin.o
OUTPUT  = cpu
LIBRARY = libcpu.a 

INCLUDE_DIR = ../../Stack
INCLUDE     = stack

default: valgrind

valgrind: $(OUTPUT)
	valgrind ./$(OUTPUT) "../txt files/asm_binary"

launch: $(OUTPUT)
	./$(OUTPUT) "../txt files/asm_binary"

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -L$(INCLUDE_DIR) -l$(INCLUDE) -o $(OUTPUT)

main.o: main_cpu.cpp
	$(CXX) $(WARNINGS) $(DEBUG_MODE) main_cpu.cpp -c

stack.o: cpu.cpp
	$(CXX) $(WARNINGS) $(DEBUG_MODE) cpu.cpp -c

library: $(OBJECT)
	ar cr $(LIBRARY) $(OBJECT)

clean:
	rm -f *.o *.a $(OUTPUT)
