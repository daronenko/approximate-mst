.PHONY: cmake
cmake:
	cmake -B build

build/CMakeCache.txt: cmake

.PHONY: build
build: build/CMakeCache.txt
	cmake --build build --target graph

.PHONY: run
run:
	build/src/graph

.PHONY: clean
clean:
	rm -rf build

