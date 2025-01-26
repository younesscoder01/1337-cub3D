/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 22:00:51 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/26 19:12:56 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	cal_h_steps(double steps[2], t_data *param, double rayAngle, int i)
{
	steps[1] = (double)TILE_SIZE;
	if (param->rays[i].is_up)
		steps[1] *= -1;
	steps[0] = (double)TILE_SIZE / tan(deg2rad(rayAngle));
	if (param->rays[i].is_left && steps[0] > 0)
		steps[0] *= -1;
	if (param->rays[i].is_right && steps[0] < 0)
		steps[0] *= -1;
}

void	horizontal_interception(t_data *param, int i, double rayAngle,
		t_hits_dist *hits_dist)
{
	double	intercepts[2];
	double	steps[3];

	steps[2] = 0;
	intercepts[1] = floor(param->player.y / TILE_SIZE) * TILE_SIZE;
	if (param->rays[i].is_down)
		intercepts[1] += TILE_SIZE;
	intercepts[0] = param->player.x + ((intercepts[1] - param->player.y)
			/ tan(deg2rad(rayAngle)));
	cal_h_steps(steps, param, rayAngle, i);
	if (param->rays[i].is_up)
		steps[2] = 1;
	while (intercepts[0] >= 0 && intercepts[0] < param->minimap_img->img_width
		&& intercepts[1] >= 0 && intercepts[1] < param->minimap_img->img_height)
	{
		if (is_wall(intercepts[0], intercepts[1] - steps[2], param->map, param))
		{
			hits_dist->foundhits[0] = 1;
			hits_dist->hits[0] = intercepts[0];
			hits_dist->hits[1] = intercepts[1] - steps[2];
			break ;
		}
		intercepts[1] += steps[1];
		intercepts[0] += steps[0];
	}
}

void	cal_v_steps(double steps[2], t_data *param, double rayAngle, int i)
{
	steps[0] = (double)TILE_SIZE;
	if (param->rays[i].is_left)
		steps[0] *= -1;
	steps[1] = (double)TILE_SIZE * tan(deg2rad(rayAngle));
	if (param->rays[i].is_up && steps[1] > 0)
		steps[1] *= -1;
	if (param->rays[i].is_down && steps[1] < 0)
		steps[1] *= -1;
}

void	vertical_interception(t_data *param, int i, double rayAngle,
		t_hits_dist *hits_dist)
{
	double	intercepts[2];
	double	steps[3];

	steps[2] = 0;
	intercepts[0] = floor(param->player.x / TILE_SIZE) * TILE_SIZE;
	if (param->rays[i].is_right)
		intercepts[0] += TILE_SIZE;
	intercepts[1] = param->player.y + (intercepts[0] - param->player.x)
		* tan(deg2rad(rayAngle));
	cal_v_steps(steps, param, rayAngle, i);
	if (param->rays[i].is_left)
		steps[2] = 1;
	while (intercepts[0] >= 0 && intercepts[0] < param->minimap_img->img_width
		&& intercepts[1] >= 0 && intercepts[1] < param->minimap_img->img_height)
	{
		if (is_wall(intercepts[0] - steps[2], intercepts[1], param->map, param))
		{
			hits_dist->foundhits[1] = 1;
			hits_dist->hits[2] = intercepts[0] - steps[2];
			hits_dist->hits[3] = intercepts[1];
			break ;
		}
		intercepts[1] += steps[1];
		intercepts[0] += steps[0];
	}
}
