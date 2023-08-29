clang++-17 -stdlib=libc++ -nostdinc++ -Illvm-project/build/include/c++/v1 -Lllvm-project/build/lib main.cpp knight2.cpp -o main -g -fsanitize=memory
LD_LIBRARY_PATH=llvm-project/build/lib ./main
