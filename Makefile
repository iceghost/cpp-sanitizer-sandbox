CXX=clang++-17
CXXFLAGS=-g -stdlib=libc++ -nostdinc++ -Iinclude/c++/v1 -Llib -fsanitize=memory,undefined

.PHONY: run main clang++-17 libc++ install-libc++

main: knight2.cpp main.cpp
	$(CXX) $(CXXFLAGS) $? -o $@

run:
	LD_LIBRARY_PATH=lib ./main

clang++-17:
	wget https://apt.llvm.org/llvm.sh
	chmod +x llvm.sh
	sudo ./llvm.sh 17
	rm llvm.sh

libc++: clang++-17
	sudo apt-get install ninja-build -y
	mkdir -p llvm-project/build
	cmake -GNinja -Sllvm-project/runtimes -Bllvm-project/build \
		-DCMAKE_BUILD_TYPE=Release \
		-DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi" \
		-DCMAKE_C_COMPILER=clang-17 \
		-DCMAKE_CXX_COMPILER=clang++-17 \
		-DLLVM_USE_SANITIZER=MemoryWithOrigins
	cmake --build llvm-project/build -- cxx cxxabi

install-libc++:
	cp llvm-project/build/include . -r
	cp llvm-project/build/lib . -r