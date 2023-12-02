CPPC = g++-11
CPPFLAGS = -Wall -std=c++2a -O2

all: $(patsubst %.cpp, %.exe, $(wildcard *.cpp))

%.exe: %.cpp Makefile
	$(CPPC) $(CPPFLAGS) $< -o $@

clean: 
	rm -rf *.exe