/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:10:37 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/23 10:12:37 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_put_pixel(t_img_info *img, int x, int y, int color)
{
	char	*pxl;

	if (x >= 0 && x < img->img_width && y >= 0 && y < img->img_height)
	{
		pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)pxl = color;
	}
}

int	get_player_x(char **map)
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
				return (j);
			j++;
		}
		i++;
	}
	return (1);
}

double	deg2rad(double x)
{
	return (x * (M_PI / 180.0));
}

void	render_p(t_img_info *img, t_player *p, int i, int j)
{
	double		x1;
	double		y1;
	t_line_cor	cor;

	x1 = p->radius * 2;
	while (i < x1)
	{
		j = 0;
		while (j < x1)
		{
			if (pow(j - p->radius, 2) + pow(i - p->radius, 2) <= pow(p->radius,
					2))
				ft_put_pixel(img, (j + p->x - p->radius), (i + p->y
						- p->radius), 0x00FF0000);
			j++;
		}
		i++;
	}
	x1 = p->x + cos(deg2rad(p->rotationAngle)) * LINE_LENGTH;
	y1 = p->y + sin(deg2rad(p->rotationAngle)) * LINE_LENGTH;
	cor.x = p->x;
	cor.y = p->y;
	cor.x1 = x1;
	cor.y1 = y1;
	draw_line_y(&cor, img, 0x00FF0000);
}

void	render_minimap(t_data *data)
{
	render_wall(data->map, data->minimap_img);
	render_floor(data->map, data->minimap_img);
	render_p(data->minimap_img, &data->player, 0, 0);
}
