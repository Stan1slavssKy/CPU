CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

SOURCE  = cpu.cpp cpu_main.cpp 
OBJECT  = cpu.o   cpu_main.o 
OUTPUT  = cpu
LIBRARY = libcpu.a 

default: valgrind

valgrind: $(OUTPUT)
	valgrind ./$(OUTPUT)

launch: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

main.o: main_cpu.cpp
	$(CXX) main_cpu.cpp -c

stack.o: cpu.cpp
	$(CXX) cpu.cpp -c

library: $(OBJECT)
	ar cr $(LIBRARY) $(OBJECT)

clean:
	rm -f *.o *.a $(OUTPUT)
