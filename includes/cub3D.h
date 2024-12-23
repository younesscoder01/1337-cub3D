/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:29:47 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/22 15:13:54 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/wait.h>


# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define FRAME_WIDTH (TILE_SIZE * 3)
# define FRAME_HEIGHT (FRAME_WIDTH / 2)
# define TILE_SIZE (WINDOW_WIDTH / 12)
# define RADIUS (TILE_SIZE / 12)
# define LINE_LENGTH (RADIUS * 3)
# define M_PI		3.14159265358979323846


//colors
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define lfaa5ti 0x0044b6b7

enum{
	W = 180,
	S = 90,
	E = 0,
	N = 270,
};

//events
enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum {
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	ESC = 65307,
	SPACE = 32,
	ZERO = 48,
	ONE = 49,
	TWO = 50,
	THREE = 51,
	FOUR = 52,
	FIVE = 53,
	SIX = 54,
	SEVEN = 55,
	EIGHT = 56,
	NINE = 57
};

//player struct
typedef struct s_player
{
	int x;
	int y;
	double radius;
	double turnDirection;
	double walkDirection;
	double rotationAngle;
	double moveSpeed;
	double rotationSpeed;
}				t_player;

//img struct
typedef struct	s_img_info {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int img_height;
    int img_width;
	char *filename;
}				t_img_info;

typedef struct s_weapons
{
	t_img_info **weapon;
	int frame_numb;
	int index_to_change;
}               t_weapons;

//data struct that containing all the data
typedef struct  s_data
{
    void	*mlx;
    void	*mlx_win;
	t_player player;
	t_img_info *minimap_img;
	t_img_info *frame;
    t_img_info *game_frame;
	t_weapons	*all_weapons;
	int frame_index;
	char **weapon_names;
	int weapon_numb;
	bool animate_weapon;
	char **map;
}               t_data;

//fuctions
size_t get_map_width(char **map_name);
size_t get_map_height(char **map_name);
void render_minimap(t_data *data);
void render_tiles(t_img_info *img, int x, int y, int color);
void render_wall(char **map, t_img_info *img);
void render_floor(char **map, t_img_info *img);
void ft_put_pixel(t_img_info *img, int x, int y, int color);
int render_next_frame(void *data);
int close_win(void *data1);
int key_p(int keycode, void *data1);
int key_r(int keycode, void *var);
double deg2rad(double x);
double normalizeAngle(double angle);
void p_setup(t_player *p, char **map);
int get_player_x(char **map);
int get_player_y(char **map);
void intialize_data(t_data *data, char **map, void *mlx, void *mlx_win);
void init_weapon_names(t_data *data);
void copy_img_sprite(t_img_info *src, t_img_info *dest, int x, int y, int height, int width);
void copy_img(t_img_info *src, t_img_info *dest, int x, int y, int height, int width);
void rect(t_img_info *img, int x, int y, int width, int height, int color);
void floor_ceiling(t_img_info *img, int color1, int color2);
void create_frame(t_data *data, int fx, int fy);
void init_weapons(t_data *data);
#endif