INTERFACES=src/term.cpp src/interpreter.cpp
IMPLEMENTATIONS=src/term-imp.cpp src/interpreter-imp.cpp
LIBS=-lpthread

bfuk: $(IMPLEMENTATIONS) $(HEADERS)
	g++ -fmodules-ts $(INTERFACES) $(IMPLEMENTATIONS) src/main.cpp -o $@ $(LIBS)

all: bfuk debug

debug: $(IMPLEMENTATIONS) $(HEADERS)
	g++ -g -fmodules-ts $(INTERFACES) $(IMPLEMENTATIONS) src/main.cpp -o $@ $(LIBS)

clean:
	@rm -f bfuk debug

.PHONY: all clean
