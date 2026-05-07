CC      = gcc
CFLAGS  = -Wall -Wextra -g $(shell sdl2-config --cflags)
LIBS    = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf

TARGET  = game
SRCS    = main.c source.c
OBJS    = $(SRCS:.c=.o)

# ── Règles ────────────────────────────────────────────────

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
