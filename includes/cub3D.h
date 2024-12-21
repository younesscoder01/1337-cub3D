/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:29:47 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/21 15:20:27 by rbenmakh         ###   ########.fr       */
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
# define TILE_SIZE 22
# define WINDOW_WIDTH 720
# define WINDOW_HEIGHT 720
# define RADIUS 5
# define M_PI 3.14159265358979323846

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
//bfs sturct
typedef struct node
{
        struct node     *next;
        struct node     *parent;
        int                     x;
        int                     y;
}                               t_node;
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
	t_player	player;
	int			**check_arr;
	int 		map_x;
	int 		map_y;
	t_img_info *minimap_img;
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
#endif