CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

ASM_DIR  = assembler
CPU_DIR  = cpu
LIBS_DIR = libs

ASM_SOURCE = $(ASM_DIR)/assembler_main.cpp $(ASM_DIR)/assembler.cpp $(LIBS_DIR)/Onegin.cpp
ASM_OBJECT = $(ASM_SOURCE:.cpp=.o)

CPU_SOURCE = $(CPU_DIR)/cpu.cpp   $(CPU_DIR)/cpu_main.cpp $(LIBS_DIR)/stack.cpp $(LIBS_DIR)/protection.cpp $(LIBS_DIR)/Onegin.cpp
CPU_OBJECT = $(CPU_SOURCE:.cpp=.o)

ASM_OUTPUT = assembler 
CPU_OUTPUT = cpu

default: all

all: asm cpu 

asm: $(ASM_OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(ASM_OUTPUT)
	valgrind ./$(ASM_OUTPUT)

cpu: $(CPU_OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(ASM_OUTPUT)\
	valgrind ./$(CPU_OUTPUT)

$(ASM_DIR)/%.o: $(ASM_DIR)/%.cpp
	$(CXX) $(DEBUG_MODE) $^ -o $@

$(ASM_DIR)/assembler_main.o: $(ASM_DIR)/assembler_main.cpp 
$(ASM_DIR)/assembler.o:      $(ASM_DIR)/assembler.cpp




clean: clean_asm clean_cpu

clean_asm:
	rm -f $(ASM_DIR)/*.o $(ASM_OUTPUT)

clean_cpu:
	rm -f $(ASM_DIR)/*.o $(CPU_OUTPUT)
