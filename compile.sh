clang++ -stdlib=libc++ -nostdinc++ -Iinclude/c++/v1 -Llib main.cpp knight2.cpp -o main -g -fsanitize=memory
LD_LIBRARY_PATH=lib ./main
