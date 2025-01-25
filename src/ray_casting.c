/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:27:19 by rbenmakh          #+#    #+#             */
/*   Updated: 2025/01/25 10:14:13 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	distance(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0));
}

int	is_wall(float x, float y, char **map, t_data *data)
{
	int	map_grid_x;
	int	map_grid_y;

	if (x < 0 || y < 0 || (int)y >= data->minimap_img->img_height
		|| (int)x >= data->minimap_img->img_width)
		return (1);
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	if (ft_strlen(map[map_grid_y]) < (size_t)map_grid_x)
		return (1);
	if (map[map_grid_y][map_grid_x] == 'D' && distance(data->player.x,
			data->player.y, x, y) <= TILE_SIZE * 2)
	{
		return (is_wall_check(map_grid_x, map_grid_y, data));
	}
	return (map[map_grid_y][map_grid_x] == '1'
		|| map[map_grid_y][map_grid_x] == 'D');
}

void	calculate_distances(t_data *param, int *foundHits, int *hits,
		double *distances)
{
	if (foundHits[0])
		distances[0] = distance(param->player.x, param->player.y, hits[0],
				hits[1]);
	else
		distances[0] = INT_MAX;
	if (foundHits[1])
		distances[1] = distance(param->player.x, param->player.y, hits[2],
				hits[3]);
	else
		distances[1] = INT_MAX;
	distances[0] += distances[0] == 0;
	distances[1] += distances[1] == 0;
}

void	castray(t_data *param, int i, double rayAngle)
{
	int			foundhits[2];
	int			hits[4];
	double		distances[2];
	t_hits_dist	hits_dist;

	set_valuse(foundhits, hits, distances);
	hits_dist.foundHits = foundhits;
	hits_dist.hits = hits;
	hits_dist.distances = distances;
	rayAngle = normalizeangle(rayAngle);
	param->rays[i].angle = rayAngle;
	param->rays[i].is_down = rayAngle > 0 && rayAngle < 180;
	param->rays[i].is_up = (rayAngle > 180 && rayAngle < 360);
	param->rays[i].is_right = rayAngle < 90 || rayAngle > 270;
	param->rays[i].is_left = (rayAngle > 90 && rayAngle < 270);
	param->rays[i].column_id = i;
	horizontal_interception(param, i, rayAngle, &hits_dist);
	vertical_interception(param, i, rayAngle, &hits_dist);
	calculate_distances(param, foundhits, hits, distances);
	if (distances[0] < distances[1])
		set_0_ray_info(param, i, distances, hits);
	else
		set_1_ray_info(param, i, distances, hits);
}

void	castallrays(t_data *param)
{
	int		i;
	double	rayangle;

	rayangle = param->player.rotationAngle - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		castray(param, i, rayangle);
		rayangle += (double)(FOV) / (double)(NUM_RAYS);
		i++;
	}
}
