all: DFA


WARNINGS = -Wall -Weffc++ -Wextra -Wsign-conversion -pedantic-errors
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2
STANDARD = -std=c++2a

DFA: Makefile main.cpp
	$(CXX) -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE) $(STANDARD) main.cpp

clean:
	rm -f DFA

# Builder will call this to install the application before running.
install:
	echo "Installing is not supported"

# Builder uses this target to run your application.
run:
	./DFA

