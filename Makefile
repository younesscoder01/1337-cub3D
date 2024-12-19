CC = cc
CFLAGS=-lm -I/usr/local/include -lmlx -lXext -lX11 -O3 -g3 -Wall -Wextra -Werror

SRCDIR = ./src
OBJDIR = ./obj
SRC= ./src/mini_map.c ./src/cub3D.c
OBJ=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
NAME=cub3D

all: $(cOBJ) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(NAME)

fclean: clean

re: fclean all