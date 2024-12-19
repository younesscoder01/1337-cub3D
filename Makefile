CC = cc
CFLAGS = -I/usr/local/include -L/usr/local/lib -O3 -g3 -Wall -Wextra -Werror
LDLIBS = -lXext -lX11 -lm
LIBFT_DIR = /libft/include
LIB = libft

SRCDIR = ./src
OBJDIR = ./obj
SRC = ./src/cub3D.c ./src/mini_map.c ./src/mini_map_utils.c ./src/render_frames.c ./src/parser.c
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) libft/libft.a libmlx_Linux.a
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

	#$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -I$(LIBFT_DIR) -o $(NAME)
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@
$(LIB)/libft.a:
	$(MAKE) -C $(LIB) all

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIB) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB) fclean


re: fclean all
