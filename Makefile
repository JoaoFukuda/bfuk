INTERFACES=src/term.cpp src/interpreter.cpp
SOURCES=src/term-imp.cpp src/interpreter-imp.cpp

all: bfuk

bfuk: $(SOURCES) $(HEADERS)
	g++ -fmodules-ts $(INTERFACES) $(SOURCES) src/main.cpp -o $@

debug: $(SOURCES) $(HEADERS)
	g++ -g -fmodules-ts $(INTERFACES) $(SOURCES) src/main.cpp -o $@

clean:
	@rm -f bfuk debug

.PHONY: all clean
