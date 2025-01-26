CC = cc
CFLAGS = -I/usr/local/include -g3 -Wall -Wextra -Werror -g
LDLIBS = -lXext -lX11 -lm
LIB = libft/libft.a /usr/local/lib/libmlx_Linux.a
LIB_DIR = libft
OBJDIR = ./obj
SRCDIR = ./src

ifeq ($(BONUS),1)
SOURCES := $(addprefix src_1/, $(notdir $(SRC)))
SRCDIR = ./src_1
else
SOURCES := $(addprefix src/, $(notdir $(SRC)))
SRCDIR = ./src
endif

SRC = cub3D.c mini_map.c mini_map_utils.c render_frames.c \
      initialize_data.c close_err_handling.c sprite_animation.c \
      check.c check1.c check2.c \
      check_utils.c sprite_animation_v2.c keys.c mouse.c \
      mini_map_v2.c parser.c initialize_data_01.c \
      ray_casting.c render_walls.c mini_map_utils2.c \
      ray_casting_2.c ray_casting_3.c render_walls_utils.c

OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SRC)))
NAME = cub3D

all: $(NAME)

bonus:
	$(MAKE) BONUS=1 all

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(LDLIBS) -o $(NAME)

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