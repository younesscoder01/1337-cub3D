CC = cc
CFLAGS = -I/usr/local/include -g3 -Wall -Wextra -Werror -g
LDLIBS = -lXext -lX11 -lm
LIB = libft/libft.a /usr/local/lib/libmlx_Linux.a
LIB_DIR = libft
OBJDIR = ./obj
SRCDIR = ./src
###bonus
OBJDIR_1 = ./obj_1
SRCDIR_1 = ./src_1

SRC = cub3D.c mini_map.c mini_map_utils.c render_frames.c \
      initialize_data.c close_err_handling.c sprite_animation.c \
      check.c check1.c check2.c \
      check_utils.c sprite_animation_v2.c keys.c mouse.c \
      mini_map_v2.c parser.c initialize_data_01.c \
      ray_casting.c render_walls.c mini_map_utils2.c \
      ray_casting_2.c ray_casting_3.c render_walls_utils.c
###bonus
SRC_1 = cub3D.c mini_map.c mini_map_utils.c render_frames.c \
      initialize_data.c close_err_handling.c sprite_animation.c \
      check.c check1.c check2.c \
      check_utils.c sprite_animation_v2.c keys.c mouse.c \
      mini_map_v2.c parser.c initialize_data_01.c \
      ray_casting.c render_walls.c mini_map_utils2.c \
      ray_casting_2.c ray_casting_3.c render_walls_utils.c

OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SRC)))
NAME = cub3D
###bonus
OBJ_1 = $(patsubst %.c, $(OBJDIR_1)/%.o, $(notdir $(SRC_1)))
NAME_1 = cub3D_bonus

all: $(NAME)

###bonus
bonus: $(NAME_1)


$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(LDLIBS) -o $(NAME)
	@bash -c "echo -e '\\033[0;33mYour program is ready 🕹 \\033[0m'"

###bonus
$(NAME_1): $(OBJ_1) libft/libft.a
	@$(CC) $(CFLAGS) $(OBJ_1) $(LIB) $(LDLIBS) -o $(NAME_1)
	@bash -c "echo -e '\\033[0;33mYour program is ready 🕹 \\033[0m'"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@bash -c "echo -e -n '\\033[0;32mCompiling '"
	@bash -c "echo -e -n $<"
	@bash -c "echo -e '\\033[0m'"
	@$(CC) $(CFLAGS) -c $< -o $@

###bonus
$(OBJDIR_1)/%.o: $(SRCDIR_1)/%.c | $(OBJDIR_1)
	@bash -c "echo -e -n '\\033[0;32mCompiling '"
	@bash -c "echo -e -n $<"
	@bash -c "echo -e '\\033[0m'"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

###bonus
$(OBJDIR_1):
	@mkdir -p $@

libft/libft.a:
	@bash -c "echo -e '\\033[0;34mCompiling libft\\033[0m'"
	@$(MAKE) -C $(LIB_DIR) all -s

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJDIR_1)
	@$(MAKE) -C $(LIB_DIR) clean -s
	@bash -c "echo -e '\\033[0;31mRemoved object files\\033[0m'"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_1)
	@$(MAKE) -C $(LIB_DIR) fclean -s
	@bash -c "echo -e '\\033[0;31mRemoved executable\\033[0m'"

re: fclean all