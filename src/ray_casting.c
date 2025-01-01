/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:27:19 by rbenmakh          #+#    #+#             */
/*   Updated: 2025/01/01 15:24:39 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2)
                + pow(y2 - y1, 2) * 1.0);
}

int	is_wall(float x, float y, char **map, t_data *data, int mod)
{
	if(x < 0 || y < 0 || (int)y >= data->minimap_img->img_height  || (int)x >= data->minimap_img->img_width)
		return(1);
	int map_grid_x;
	int map_grid_y;
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	if(ft_strlen(map[map_grid_y]) < (size_t)map_grid_x)
		return(1);
    if (map[map_grid_y][map_grid_x] == 'D' && distance(data->player.x, data->player.y, x, y) <= TILE_SIZE * 2 && mod == 1)
    {
        if (map_grid_x == data->player.x / TILE_SIZE || map_grid_y == data->player.y / TILE_SIZE)
        {
            if (map_grid_x + 1 == data->player.x / TILE_SIZE)
                return(0);
            if (map_grid_x - 1 == data->player.x / TILE_SIZE)
                return(0);
            if (map_grid_y + 1 == data->player.y / TILE_SIZE)
                return(0);
            if (map_grid_y - 1 == data->player.y / TILE_SIZE)
                return(0);
        }
        else 
            return(1);
    }
    return(map[map_grid_y][map_grid_x] == '1' || map[map_grid_y][map_grid_x] == 'D');
}
void horizontal_interception(t_data *param, int i, double rayAngle, int *foundHits, int *hits)
{
    double intercepts[2];
    double steps[2];
    int p[1] = {0};

    intercepts[1] = floor(param->player.y / TILE_SIZE) * TILE_SIZE;
    if (param->rays[i].is_down)
        intercepts[1] += TILE_SIZE;
    intercepts[0] = param->player.x + ((intercepts[1] - param->player.y) / tan(deg2rad(rayAngle)));

    steps[1] = (double)TILE_SIZE;
    if (param->rays[i].is_up)
        steps[1] *= -1;
    steps[0] = (double)TILE_SIZE / tan(deg2rad(rayAngle));
    if (param->rays[i].is_left && steps[0] > 0)
        steps[0] *= -1;
    if (param->rays[i].is_right && steps[0] < 0)
        steps[0] *= -1;
    if (param->rays[i].is_up)
        p[0] = 1;

    while (intercepts[0] >= 0 && intercepts[0] < param->minimap_img->img_width \
            && intercepts[1] >= 0 && intercepts[1] < param->minimap_img->img_height)
    {
        if(is_wall(intercepts[0], intercepts[1] - p[0], param->map, param, 1))
        {
            foundHits[0] = 1;
            hits[0] = intercepts[0];
            hits[1] = intercepts[1] - p[0];
            break;
        }
        intercepts[1] += steps[1];
        intercepts[0] += steps[0];
    }
}

void vertical_interception(t_data *param, int i, double rayAngle, int *foundHits, int *hits)
{
    double intercepts[2];
    double steps[2];
    int p[1] = {0};

    intercepts[0] = floor(param->player.x / TILE_SIZE) * TILE_SIZE;
    if (param->rays[i].is_right)
        intercepts[0] += TILE_SIZE;
    intercepts[1] = param->player.y + (intercepts[0] - param->player.x) * tan(deg2rad(rayAngle));

    steps[0] = (double)TILE_SIZE;
    if (param->rays[i].is_left)
        steps[0] *= -1;
    steps[1] = (double)TILE_SIZE * tan(deg2rad(rayAngle));
    if (param->rays[i].is_up && steps[1] > 0)
        steps[1] *= -1;
    if (param->rays[i].is_down && steps[1] < 0)
        steps[1] *= -1;
    if (param->rays[i].is_left)
        p[0] = 1;

    while (intercepts[0] >= 0 && intercepts[0] < param->minimap_img->img_width \
            && intercepts[1] >= 0 && intercepts[1] < param->minimap_img->img_height)
    {
        if(is_wall(intercepts[0] - p[0], intercepts[1], param->map, param, 1))
        {
            foundHits[1] = 1;
            hits[2] = intercepts[0] - p[0];
            hits[3] = intercepts[1];
            break;
        }
        intercepts[1] += steps[1];
        intercepts[0] += steps[0];
    }
}

void calculate_distances(t_data *param, int *foundHits, int *hits, double *distances)
{
    if (foundHits[0])
        distances[0] = distance(param->player.x, param->player.y, hits[0], hits[1]);
    else 
        distances[0] = INT_MAX;
    if (foundHits[1])
        distances[1] = distance(param->player.x, param->player.y, hits[2], hits[3]);
    else 
        distances[1] = INT_MAX;
    distances[0] += distances[0] == 0;
    distances[1] += distances[1] == 0;
}

void castray(t_data *param, int i, double rayAngle)
{
    int foundHits[2] = {0, 0};
    int hits[4] = {0, 0, 0, 0};
    double distances[2] = {0, 0};

    rayAngle = normalizeAngle(rayAngle);
    param->rays[i].angle = rayAngle;
    param->rays[i].is_down = rayAngle > 0 && rayAngle < 180;
    param->rays[i].is_up = (rayAngle > 180 && rayAngle < 360);
    param->rays[i].is_right = rayAngle < 90 || rayAngle > 270;
    param->rays[i].is_left = (rayAngle > 90 && rayAngle < 270);
    param->rays[i].column_id = i;

    horizontal_interception(param, i, rayAngle, foundHits, hits);
    vertical_interception(param, i, rayAngle, foundHits, hits);
    calculate_distances(param, foundHits, hits, distances);

    if (distances[0] < distances[1])
    {
        param->rays[i].distance = distances[0];
        param->rays[i].hit_x = hits[0];
        param->rays[i].hit_y = hits[1];
        param->rays[i].Was_hit_vertical = 0;
    }
    else
    {
        param->rays[i].distance = distances[1];
        param->rays[i].hit_x = hits[2];
        param->rays[i].hit_y = hits[3];
        param->rays[i].Was_hit_vertical = 1;
    }
}
void castAllrays(t_data *param)
{
    int i;
    double rayAngle;

    rayAngle = param->player.rotationAngle - (FOV / 2);
    i = 0;
    while (i < NUM_RAYS)
    {
        castray(param, i, rayAngle);
        rayAngle += (double)(FOV) / (double)(NUM_RAYS);
        i++;
    }
}
