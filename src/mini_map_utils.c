/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:29:13 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/24 17:29:59 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render_tiles(t_img_info *img, int x, int y, int color)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (i[0] < TILE_SIZE)
	{
		i[1] = 0;
		while (i[1] < TILE_SIZE)
		{
			ft_put_pixel(img, x + i[1], y + i[0], color);
			i[1]++;
		}
		i[0]++;
	}
}

void	render_wall(char **map, t_img_info *img)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (map[i[0]])
	{
		i[1] = 0;
		while (map[i[0]][i[1]])
		{
			if (map[i[0]][i[1]] == '1' || map[i[0]][i[1]] == ' ')
				render_tiles(img, i[1] * TILE_SIZE, i[0] * TILE_SIZE, BLACK);
			if (map[i[0]][i[1]] == 'D')
				render_tiles(img, i[1] * TILE_SIZE, i[0] * TILE_SIZE, GREEN);
			i[1]++;
		}
		i[0]++;
	}
}

void	render_floor(char **map, t_img_info *img)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (map[i[0]])
	{
		i[1] = 0;
		while (map[i[0]][i[1]])
		{
			if (map[i[0]][i[1]] == '0' || map[i[0]][i[1]] == 'N'
				|| map[i[0]][i[1]] == 'S' || map[i[0]][i[1]] == 'W'
				|| map[i[0]][i[1]] == 'E')
				render_tiles(img, i[1] * TILE_SIZE, i[0] * TILE_SIZE,
					0x00FFFFFF);
			i[1]++;
		}
		i[0]++;
	}
}

//cor->x = x, cor->y = y, cor->x1 = width, cor->y1 = height
void	rect(t_img_info *img, t_line_cor *cor, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < cor->y1)
	{
		j = 0;
		while (j < cor->x1)
		{
			ft_put_pixel(img, cor->x + j, cor->y + i, color);
			j++;
		}
		i++;
	}
}
