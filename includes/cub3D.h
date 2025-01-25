/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:29:47 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/25 10:17:22 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*------------Libraries----------*/
# include "../libft/libft.h"
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

/*------------Macros-------------*/
# define WALL_STRIP_WIDTH 1
# define FOV 60
# define NUM_RAYS WINDOW_WIDTH / WALL_STRIP_WIDTH
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define TILE_SIZE 64
# define FRAME_WIDTH (TILE_SIZE * 4)
# define FRAME_HEIGHT (FRAME_WIDTH / 2)
# define RADIUS (TILE_SIZE / 15)
# define LINE_LENGTH (RADIUS * 3)
# define M_PI 3.14159265358979323846
# define ROTATION_SPEED 3.3
# define WEAPON_N 7
# define MOVE_SPEED 6.5
# define MOVE_SPEED_MOUSE 1.5

// colors
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define LBAR9O9I 0x00532e12
# define PINK 0x00FF69B4

/*-------------Enums------------*/
enum
{
	W = 180,
	S = 90,
	E = 0,
	N = 270,
};

// events
enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum
{
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
	NINE = 57,
	R = 114,
	SHIFT = 65505
};

/*------------Structs------------*/
// ray struct
typedef struct s_ray
{
	double		angle;
	int			column_id;
	float		hit_x;
	float		hit_y;
	double		distance;
	bool		dir_hit;
	bool		is_down;
	bool		is_up;
	bool		is_right;
	bool		is_left;
	bool		Was_hit_vertical;
} t_rays[NUM_RAYS];
// player struct
typedef struct s_player
{
	int			x;
	int			y;
	double		radius;
	double		turnDirection;
	double		walkDirection;
	double		rotationAngle;
	double		moveSpeed;
	double		rotationSpeed;
	int			is_move_side;
}				t_player;

// img struct
typedef struct s_img_info
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_height;
	int			img_width;
	char		*filename;
}				t_img_info;

typedef struct s_weapons
{
	t_img_info	**weapon;
	int			frame_numb;
	int			index_to_change;
	int			shoting_end;
	int			ammo_numb;
	int			default_ammo;
}				t_weapons;

// data struct that containing all the data
typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_rays		rays;
	t_player	player;
	int			**check_arr;
	int			map_x;
	int			map_y;
	char		*txt[4];
	int			color[2];
	t_img_info	*textures[4];
	t_img_info	*door;
	t_img_info	*minimap_img;
	t_img_info	*frame;
	t_img_info	*game_frame;
	t_img_info	*bullet;
	t_img_info	*no_bullet;
	t_weapons	*all_weapons;
	int			frame_index;
	int			weapon_numb;
	char		**weapon_names;
	bool		animate_weapon;
	bool		weapon_reload;
	char		**map;
	int			mouse_x;
	int			mouse_y;
	int			mouse_in;
}				t_data;

typedef struct s_line_cor
{
	double		x;
	double		y;
	double		x1;
	double		y1;
}				t_line_cor;

typedef struct s_hits_dist
{
	int			*foundHits;
	int			*hits;
	double		*distances;
}				t_hits_dist;

/*------------Functions Prototypes--------------*/

size_t			get_map_width(char **map_name);
size_t			get_map_height(char **map_name);
void			render_minimap(t_data *data);
void			render_tiles(t_img_info *img, int x, int y, int color);
void			render_wall(char **map, t_img_info *img);
void			render_floor(char **map, t_img_info *img);
void			ft_put_pixel(t_img_info *img, int x, int y, int color);
int				update(void *data1);
int				close_win(void *data1);
int				key_p(int keycode, void *data1);
int				key_r(int keycode, void *var);
double			deg2rad(double x);
void			p_setup(t_player *p, char **map);
int				setup(char **argv, t_data *d);
int				find_longest_row(char **map);
void			free_arr(void **arr, int i, int flag);
int				get_player_x(char **map);
int				get_player_y(char **map);
void			intialize_data(t_data *data, char **map);
void			init_weapon_names(t_data *data);
void			copy_img_sprite(t_img_info *src, t_img_info *dest,
					t_line_cor *cor);
void			copy_img(t_img_info *src, t_img_info *dest, t_line_cor *cor);
void			rect(t_img_info *img, t_line_cor *cor, int color);
void			floor_ceiling(t_img_info *img, int color1, int color2);
void			create_frame(t_data *data, int fx, int fy, t_line_cor cor);
void			init_weapons(t_data *data, int i, int j, int k);
int				render_bullets(t_data *data);
int				mouse_hook(int x, int y, t_data *data);
int				mouse_down(int button, int x, int y, t_data *data);
void			take_weapon(t_data *data);
int				set_up_animation_delay(int n_frame);
void			animate_weapon_shoting(t_data *data, int end);
void			animate_weapon_reload(t_data *data, int last_end);
double			normalizeangle(double angle);
int				mouse_hook(int x, int y, t_data *data);
int				mouse_down(int button, int x, int y, t_data *data);
void			draw_line_angle(t_data *data, double angle, int x, int y);
void			draw_line(t_data *data, int x, int y, int x1, int y1);
double			calc_dist(long x, long x1, long y, long y1);
double			rad2deg(double angle);
double			norm_angle(double angle);
void			draw_circle(t_data *data, double cx, double cy, float radius);
void			draw_line_y(t_line_cor *cor, t_img_info *img, int color);
void			render_3d_walls(t_data *data);
void			castallrays(t_data *param);
unsigned int	darken_color(unsigned int color, double factor);
unsigned int	get_px_color(t_img_info *img, int x, int y);
int				init_textures(t_data *data, char **txt, int i);
void			init_arr(char **arr, int l);
int				create_trgb(int t, int r, int g, int b);
void			get_player(char **map, int *x, int *y);
int				read_map(int fd, t_data *data, int i[4], char *s[3]);
void			advance_nl(char *str, int *i);
char			*skip_new_line(int fd);
void			free_txt(char **arr);
int				process_newline(char *line, int fd, int i);
int				check_color(int mod, char *col, t_data *data);
int				provide_config(t_data *d, char **arr, char *t, char **tp);
int				find_longest_row(char **map);
int				check_boundaries(char **map, size_t map_h);
int				line_processing(char *str, int *item, int mod);
int				check_map(char **map, size_t i, size_t j);
int				finalize_map(int fd, t_data *data, int i[2], char *full);
void			init_bullet(t_data *data);
int				mouse_out(t_data *data);
void			check_frame_end(t_data *d, int last_end, int end);
void			draw_b(t_data *d);
void			vertical_interception(t_data *param, int i, double rayAngle,
					t_hits_dist *hits_dist);
void			horizontal_interception(t_data *param, int i, double rayAngle,
					t_hits_dist *hits_dist);
int				is_wall(float x, float y, char **map, t_data *data);
void			set_0_ray_info(t_data *param, int i, double *distances,
					int *hits);
void			set_1_ray_info(t_data *param, int i, double *distances,
					int *hits);
void			set_valuse(int *foundhits, int *hits, double *distances);
int				is_wall_check(int map_grid_x, int map_grid_y, t_data *data);
#endif