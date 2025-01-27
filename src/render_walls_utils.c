/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:01:38 by rbenmakh          #+#    #+#             */
/*   Updated: 2025/01/27 13:01:04 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	calculate_wall_height_top(double wallStripHeight)
{
	double	wall_height_top;

	wall_height_top = (WINDOW_HEIGHT / 2) - ((int)wallStripHeight / 2);
	if (wall_height_top < 0)
		wall_height_top = 0;
	return (wall_height_top);
}

double	calculate_wall_height_bottom(double wallStripHeight)
{
	double	wall_height_bottom;

	wall_height_bottom = (WINDOW_HEIGHT / 2) + ((int)wallStripHeight / 2);
	if (wall_height_bottom > WINDOW_HEIGHT)
		wall_height_bottom = WINDOW_HEIGHT;
	return (wall_height_bottom);
}

int	get_texture_color(t_data *data, int i, double texture_offset_x,
		double texture_offset_y)
{
	if (data->map[(int)data->rays[i].hit_y / TILE_SIZE][(int)data->rays[i].hit_x
		/ TILE_SIZE] == 'D')
		return (get_px_color(data->door, texture_offset_x, texture_offset_y));
	else if (data->rays[i].is_down && !data->rays[i].was_hit_vertical)
		return (get_px_color(data->textures[3], texture_offset_x,
				texture_offset_y));
	else if (data->rays[i].is_up && !data->rays[i].was_hit_vertical)
		return (get_px_color(data->textures[0], texture_offset_x,
				texture_offset_y));
	else if (data->rays[i].is_right && data->rays[i].was_hit_vertical)
		return (get_px_color(data->textures[1], texture_offset_x,
				texture_offset_y));
	else if (data->rays[i].is_left && data->rays[i].was_hit_vertical)
		return (get_px_color(data->textures[2], texture_offset_x,
				texture_offset_y));
	return (0);
}
