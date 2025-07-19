# Variables
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/instructions.o $(OBJ_DIR)/status.o $(OBJ_DIR)/opcodes.o $(OBJ_DIR)/addressing.o $(OBJ_DIR)/cpu.o
TEST_OBJ = $(OBJ_DIR)/test_runner.o $(OBJ_DIR)/test_cpu.o $(OBJ_DIR)/test_status.o $(OBJ_DIR)/test_instructions.o $(OBJ_DIR)/test_addressing.o $(OBJ_DIR)/instructions.o $(OBJ_DIR)/status.o $(OBJ_DIR)/opcodes.o $(OBJ_DIR)/addressing.o $(OBJ_DIR)/cpu.o
EXE = $(BIN_DIR)/mos6502
TEST_EXE = $(BIN_DIR)/test_runner

# Targets
all: $(EXE)

test: $(TEST_EXE)
	./$(TEST_EXE)

$(EXE): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(CORE_DIR)/instructions.h $(CORE_DIR)/status.h $(CORE_DIR)/addressing.h $(CORE_DIR)/opcodes.h $(CORE_DIR)/cpu.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $@

$(OBJ_DIR)/instructions.o: $(CORE_DIR)/instructions.c $(CORE_DIR)/instructions.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(CORE_DIR)/instructions.c -o $@

$(OBJ_DIR)/opcodes.o: $(CORE_DIR)/opcodes.c $(CORE_DIR)/opcodes.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(CORE_DIR)/opcodes.c -o $@

$(OBJ_DIR)/status.o: $(CORE_DIR)/status.c $(CORE_DIR)/status.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(CORE_DIR)/status.c -o $@

$(OBJ_DIR)/addressing.o: $(CORE_DIR)/addressing.c $(CORE_DIR)/addressing.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(CORE_DIR)/addressing.c -o $@

$(OBJ_DIR)/cpu.o: $(CORE_DIR)/cpu.c $(CORE_DIR)/cpu.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(CORE_DIR)/cpu.c -o $@

$(TEST_EXE): $(TEST_OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_EXE)

$(OBJ_DIR)/test_runner.o: $(TEST_DIR)/test_runner.c $(TEST_DIR)/test_framework.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_runner.c -o $@

$(OBJ_DIR)/test_cpu.o: $(TEST_DIR)/test_cpu.c $(TEST_DIR)/test_framework.h $(CORE_DIR)/cpu.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_cpu.c -o $@

$(OBJ_DIR)/test_status.o: $(TEST_DIR)/test_status.c $(TEST_DIR)/test_framework.h $(CORE_DIR)/status.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_status.c -o $@

$(OBJ_DIR)/test_instructions.o: $(TEST_DIR)/test_instructions.c $(TEST_DIR)/test_framework.h $(CORE_DIR)/instructions.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_instructions.c -o $@

$(OBJ_DIR)/test_addressing.o: $(TEST_DIR)/test_addressing.c $(TEST_DIR)/test_framework.h $(CORE_DIR)/addressing.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_addressing.c -o $@

clean:
	$(RM) -r $(BIN_DIR) $(OBJ_DIR)