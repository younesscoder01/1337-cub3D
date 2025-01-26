/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:21:38 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/25 19:35:29 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	normalizeangle(double angle)
{
	while (angle < 0.0000)
		angle += 360;
	while (angle >= 360.0)
		angle -= 360;
	return (angle);
}

void	weapon_action_keys(int keycode, t_data *data)
{
	if (keycode == ZERO)
		data->weapon_numb = 0;
	else if (keycode == ONE)
		data->weapon_numb = 1;
	else if (keycode == TWO)
		data->weapon_numb = 2;
	else if (keycode == THREE)
		data->weapon_numb = 3;
	else if (keycode == FOUR)
		data->weapon_numb = 4;
	else if (keycode == FIVE)
		data->weapon_numb = 5;
	else if (keycode == SIX)
		data->weapon_numb = 6;
	else if (keycode == R)
		data->weapon_reload = true;
}

int	key_p(int keycode, void *data1)
{
	t_data	*data;

	data = (t_data *)data1;
	if (keycode == KEY_A || keycode == KEY_D)
		data->player.is_move_side = 1;
	if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_D)
		data->player.walkdirection = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_A)
		data->player.walkdirection = -1;
	else if (keycode == KEY_LEFT)
		data->player.turndirection = -1;
	else if (keycode == KEY_RIGHT)
		data->player.turndirection = 1;
	else if (keycode == ESC)
		close_win(data);
	else if (keycode == SPACE || keycode == 1)
		data->animate_weapon = true;
	weapon_action_keys(keycode, data);
	return (0);
}

int	key_r(int keycode, void *var)
{
	t_data	*data;

	data = (t_data *)var;
	if (keycode == KEY_W)
		data->player.walkdirection = 0;
	else if (keycode == KEY_UP)
		data->player.walkdirection = 0;
	else if (keycode == KEY_A)
		data->player.walkdirection = 0;
	else if (keycode == KEY_S)
		data->player.walkdirection = 0;
	else if (keycode == KEY_DOWN)
		data->player.walkdirection = 0;
	else if (keycode == KEY_D)
		data->player.walkdirection = 0;
	else if (keycode == KEY_LEFT)
		data->player.turndirection = 0;
	else if (keycode == KEY_RIGHT)
		data->player.turndirection = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		data->player.is_move_side = 0;
	return (0);
}
