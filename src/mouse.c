/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:40:44 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/23 13:45:46 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	mouse_hook(int x, int y, t_data *data)
{
	(void)y;
	data->mouse_in = 1;
	if (data->mouse_x < x)
		data->player.turnDirection = 1;
	else if (data->mouse_x > x)
		data->player.turnDirection = -1;
	data->player.rotationAngle += data->player.turnDirection * MOVE_SPEED_MOUSE;
	data->player.rotationAngle = normalizeangle(data->player.rotationAngle);
	data->mouse_x = x;
	data->player.turnDirection = 0;
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
	data->player.turnDirection = 0;
	return (0);
}
