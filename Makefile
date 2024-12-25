CC = cc
CFLAGS = -I/usr/local/include -L/usr/local/lib -O3 -g3 -Wall -Wextra -Werror
LDLIBS = -lXext -lX11 -lm
LIB = libft/libft.a libmlx_Linux.a
LIB_DIR = libft
SRCDIR = ./src
OBJDIR = ./obj
SRC = ./src/cub3D.c ./src/mini_map.c ./src/mini_map_utils.c ./src/render_frames.c ./src/parser.c  ./src/initialize_data.c ./src/ray_casting.c ./src/math_utils.c
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(LIB) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@
libft/libft.a:
	$(MAKE) -C $(LIB_DIR) all

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean


re: fclean all
