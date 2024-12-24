CC = cc
CFLAGS = -I/usr/local/include -O3 -g3 -Wall -Wextra -Werror -g -fsanitize=address
LDLIBS = -lmlx -lXext -lX11 -lm

SRCDIR = ./src
OBJDIR = ./obj
SRC = ./src/cub3D.c ./src/mini_map.c ./src/mini_map_utils.c ./src/render_frames.c \
		./src/initialize_data.c ./src/close_err_handling.c ./src/sprite_animation.c \
		./src/sprite_animation_v2.c ./src/keys.c \
		./src/mini_map_v2.c
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
