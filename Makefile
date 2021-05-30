SRC=src/term.cpp src/interpreter.cpp src/main.cpp
LIBS=-lpthread

bfuk: $(SRC)
	g++ -O3 $(SRC) -o $@ $(LIBS)

all: bfuk debug

debug: $(SRC)
	g++ -Og -g $(SRC) -o $@ $(LIBS)

clean:
	rm -f bfuk debug

.PHONY: all clean run
