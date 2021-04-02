all: launch

.PHONY: valgrind launch compile

valgrind: compile
	valgrind ./assembler

launch: compile
	./assembler

compile: assembler.cpp assembler_main.cpp parsing.cpp
	g++ -Wall -Wextra -g3 -O0 $^ -o assembler