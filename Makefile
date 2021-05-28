INT=src/term.cpp src/interpreter.cpp
IMP=src/term-imp.cpp src/interpreter-imp.cpp
LIBS=-lpthread

bfuk: $(INT) $(IMP) src/main.cpp
	g++ -fmodules-ts $(INT) $(IMP) src/main.cpp -o $@ $(LIBS)

all: bfuk debug

debug: $(IMPLEMENTATIONS) $(HEADERS) src/main.cpp
	g++ -g -fmodules-ts $(INTERFACES) $(IMPLEMENTATIONS) src/main.cpp -o $@ $(LIBS)

clean:
	rm -f bfuk debug

.PHONY: all clean run
