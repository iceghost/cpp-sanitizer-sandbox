CXX=clang++
CXXFLAGS=-g -stdlib=libc++ -nostdinc++ -Iinclude/c++/v1 -Llib -fsanitize=memory,undefined

.PHONY: run main

main: knight2.cpp main.cpp
	$(CXX) $(CXXFLAGS) $? -o $@

run:
	LD_LIBRARY_PATH=lib ./main
