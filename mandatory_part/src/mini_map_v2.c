/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:24:42 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/24 17:33:55 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	create_frame(t_data *data, int fx, int fy, t_line_cor cor)
{
	fx = data->player.x - FRAME_WIDTH / 2;
	fy = data->player.y - FRAME_HEIGHT / 2;
	if (fx < 0)
		fx = 0;
	else if (fx > data->minimap_img->img_width)
		fx = data->minimap_img->img_width - FRAME_WIDTH;
	if (fy < 0)
		fy = 0;
	else if (fy > data->minimap_img->img_height)
		fy = data->minimap_img->img_height - FRAME_HEIGHT;
	cor.x = fx;
	cor.y = fy;
	cor.x1 = FRAME_WIDTH;
	cor.y1 = FRAME_HEIGHT;
	copy_img(data->minimap_img, data->frame, &cor);
	draw_b(data);
	cor.x = 0;
	cor.y = 0;
	cor.x1 = FRAME_WIDTH;
	cor.y1 = FRAME_HEIGHT;
	copy_img(data->frame, data->game_frame, &cor);
}

int	get_player_y(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				return (i);
			j++;
		}
		i++;
	}
	return (1);
}

int	get_player_angle(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'W')
				return (W);
			else if (map[i][j] == 'N')
				return (N);
			else if (map[i][j] == 'E')
				return (E);
			else if (map[i][j] == 'S')
				return (S);
			j++;
		}
		i++;
	}
	return (0);
}

void	p_setup(t_player *p, char **map)
{
	p->radius = RADIUS;
	p->turnDirection = 0;
	p->walkDirection = 0;
	p->rotationAngle = get_player_angle(map);
	p->moveSpeed = MOVE_SPEED;
	p->rotationSpeed = ROTATION_SPEED;
	p->x = (get_player_x(map) * TILE_SIZE) + TILE_SIZE / 2;
	p->y = (get_player_y(map) * TILE_SIZE) + TILE_SIZE / 2;
	p->is_move_side = 0;
}

void	draw_line_y(t_line_cor *cor, t_img_info *img, int color)
{
	double	dx;
	double	dy;
	double	xinc;
	double	yinc;
	double	steps;

	dx = cor->x1 - cor->x;
	dy = cor->y1 - cor->y;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	xinc = dx / steps;
	yinc = dy / steps;
	dx = 0;
	while (dx <= steps)
	{
		ft_put_pixel(img, cor->x, cor->y, color);
		cor->x += xinc;
		cor->y += yinc;
		dx++;
	}
}
