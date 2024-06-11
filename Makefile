CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
LDFLAGS = -lSDL2 -lSDL2_image -lm
SRC = src/*.c
EXEC = maze

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(EXEC)

