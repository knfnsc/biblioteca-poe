CC     = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC    = $(wildcard src/*.c)
TARGET = biblioteca-poe.out

# compila tudo
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# executa o binário
run:
	./$(TARGET)

# apaga o binário
clean:
	rm -f $(TARGET) *.dat

# formata o código
format:
	clang-format -i src/*.c include/*.h
