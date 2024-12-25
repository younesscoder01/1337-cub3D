/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:29:47 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/25 10:05:03 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*------------Libraries----------*/
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"

/*------------Macros-------------*/
# define M_PI 3.14159265358979323846
# define WALL_STRIP_WIDTH 1
# define FOV 60
# define NUM_RAYS WINDOW_WIDTH / WALL_STRIP_WIDTH
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define FRAME_WIDTH (TILE_SIZE * 3)
# define FRAME_HEIGHT (FRAME_WIDTH / 2)
# define TILE_SIZE 46//(WINDOW_WIDTH / 12)
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

/*-------------Enums------------*/
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
	ESC = 65307
};

/*------------Structs------------*/
//ray struct
typedef struct s_ray
{
	double	angle;
	int		column_id;
	float	hit_x;
	float	hit_y;
	double	distance;
	bool	dir_hit;
	bool	is_down;
	bool	is_up;
	bool	is_right;
	bool	is_left;
}				t_rays[NUM_RAYS];
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
}				t_img_info;

//data struct that containing all the data
typedef struct  s_data
{
    void		*mlx;
    void		*mlx_win;
	t_rays		rays;
	t_player	player;
	int			**check_arr;
	int 		map_x;
	int 		map_y;
	char *txt[4];
	int color[2];
	t_img_info *minimap_img;
	t_img_info *frame;
    t_img_info *game_frame;
	char **map;
}               t_data;

/*------------Functions Prototypes--------------*/

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
int setup(int argc, char **argv, t_data * d);
int	bfs(int st_x, int st_y, t_data *d, int map_h);
int	find_longest_row(char **map);
void free_arr(void **arr, int i);
void print_arr(int **arr, int max_r, int map_h);
int get_player_x(char **map);
int get_player_y(char **map);
void intialize_data(t_data *data, char **map, void *mlx, void *mlx_win);
void draw_line_angle(t_data *data, double angle, int x, int y);
void draw_line(t_data *data, int x, int y, int x1, int y1);
double calc_dist(long x, long x1, long y , long y1);
double rad2deg(double angle);
double norm_angle(double angle);
void draw_circle(t_data *data, double cx, double cy, float radius);
void draw_line_y(double x, double y, double x1, double y1, t_img_info *img, int color);
void calc_rays(t_data *data);










#endif