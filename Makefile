BUILD_DIR = ./build

$(shell mkdir -p $(BUILD_DIR))

bits: bits.cpp
	g++ -Wall -o bits bits.cpp -g -O0