BUILD_DIR = ./build

KERNELS = kernels/a_latency_src_asimd_fmla_sp.s kernels/b_latency_src_asimd_fmul_sp.s
OBJ_FILES = $(patsubst kernels/%.s, $(BUILD_DIR)/%.o, $(KERNELS))

micro_asimd: $(OBJ_FILES) driver_asimd.cpp
	g++ -pedantic -Wall -Wextra -Werror -O2 -fopenmp $^ -o $(BUILD_DIR)/micro_asimd

$(BUILD_DIR)/%.o: kernels/%.s
	as -o $@ $<

all: micro_asimd

$(shell mkdir -p $(BUILD_DIR))