/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:35:43 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/25 19:33:35 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	set_valuse(int *foundhits, int *hits, double *distances)
{
	foundhits[0] = 0;
	foundhits[1] = 0;
	hits[0] = 0;
	hits[1] = 0;
	hits[2] = 0;
	hits[3] = 0;
	distances[0] = 0;
	distances[1] = 0;
}

void	set_0_ray_info(t_data *param, int i, double *distances, int *hits)
{
	param->rays[i].distance = distances[0];
	param->rays[i].hit_x = hits[0];
	param->rays[i].hit_y = hits[1];
	param->rays[i].was_hit_vertical = 0;
}

void	set_1_ray_info(t_data *param, int i, double *distances, int *hits)
{
	param->rays[i].distance = distances[1];
	param->rays[i].hit_x = hits[2];
	param->rays[i].hit_y = hits[3];
	param->rays[i].was_hit_vertical = 1;
}

int	is_wall_check(int map_grid_x, int map_grid_y, t_data *data, char **map)
{
	if (map_grid_x == data->player.x / TILE_SIZE || map_grid_y == data->player.y
		/ TILE_SIZE)
	{
		if ((map_grid_x + 1 == data->player.x / TILE_SIZE) || (map_grid_x
				- 1 == data->player.x / TILE_SIZE) || (map_grid_y
				+ 1 == data->player.y / TILE_SIZE) || (map_grid_y
				- 1 == data->player.y / TILE_SIZE))
			return (0);
	}
	else
		return (1);
	return (map[map_grid_y][map_grid_x] == '1'
		|| map[map_grid_y][map_grid_x] == 'D');
}
