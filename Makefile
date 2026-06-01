CC     = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC    = $(wildcard src/*.c)
TARGET = build/biblioteca-poe.out

# compila tudo
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# executa o binário
run:
	./$(TARGET)

# apaga o binário
clean:
	rm -f $(TARGET)
	
