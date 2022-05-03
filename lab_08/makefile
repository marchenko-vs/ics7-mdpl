SRC_DIR := src/
BIN_DIR := out/
INC_DIR := inc/
CFLAGS := -std=c++20 -Wall -Werror -Wvla -Wextra -Iinc

app.out: $(BIN_DIR)main.o $(BIN_DIR)my_strcpy.o $(BIN_DIR)my_strlen.o $(BIN_DIR)unit_tests.o
	g++ $^ -o app.out

$(BIN_DIR)main.o: $(SRC_DIR)main.cpp $(INC_DIR)my_strlen.hpp $(INC_DIR)unit_tests.hpp
	mkdir -p out
	g++ $(CFLAGS) -c $< -o $(BIN_DIR)main.o

$(BIN_DIR)my_strcpy.o: $(SRC_DIR)my_strcpy.asm
	nasm -f elf64 $< -o $(BIN_DIR)my_strcpy.o

$(BIN_DIR)my_strlen.o: $(SRC_DIR)my_strlen.cpp $(INC_DIR)my_strlen.hpp
	g++ $(CFLAGS) $< -c -o $(BIN_DIR)my_strlen.o

$(BIN_DIR)unit_tests.o: $(SRC_DIR)unit_tests.cpp $(INC_DIR)unit_tests.hpp $(INC_DIR)my_strcpy.hpp
	g++ $(CFLAGS) $< -c -o $(BIN_DIR)unit_tests.o

clean:
	rm -f app.out
	rm -rf $(BIN_DIR)

