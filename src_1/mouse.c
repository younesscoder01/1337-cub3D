/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:40:44 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/25 19:35:54 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	mouse_hook(int x, int y, t_data *data)
{
	(void)y;
	data->mouse_in = 1;
	if (data->mouse_x < x)
		data->player.turndirection = 1;
	else if (data->mouse_x > x)
		data->player.turndirection = -1;
	data->player.rotationangle += data->player.turndirection * MOVE_SPEED_MOUSE;
	data->player.rotationangle = normalizeangle(data->player.rotationangle);
	data->mouse_x = x;
	data->player.turndirection = 0;
	return (0);
}

int	mouse_down(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->animate_weapon = true;
	return (0);
}

int	mouse_out(t_data *data)
{
	data->mouse_in = 0;
	data->player.turndirection = 0;
	return (0);
}
