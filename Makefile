CC     = clang
CFLAGS = -Wall -Wextra -Iinclude
SRC    = $(wildcard src/*.c)
TARGET = build/biblioteca-poe.out

# compila tudo
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

run:
	./$(TARGET)

# limpa binário
clean:
	rm -f $(TARGET)
	
