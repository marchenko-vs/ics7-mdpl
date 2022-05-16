CC := gcc
SRC_DIR := src/
INC_DIR := inc/
OUT_DIR := out/
CFLAGS := -std=c++20 -I$(INC_DIR) -masm=intel -g3

app.exe: $(OUT_DIR)main.o $(OUT_DIR)vector.o
	$(CC) $^ -o app.exe

$(OUT_DIR)main.o: $(SRC_DIR)main.cpp $(INC_DIR)vector.hpp
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $< -c -o $(OUT_DIR)main.o

$(OUT_DIR)vector.o: $(SRC_DIR)vector.cpp $(INC_DIR)vector.hpp
	$(CC) $(CFLAGS) $< -c -o $(OUT_DIR)vector.o

.PHONY: clean

clean:
	rm -rf $(OUT_DIR) *.exe
