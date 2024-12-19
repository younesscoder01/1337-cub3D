/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:54 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/19 17:52:40 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int close_win(void *data1)
{
    t_data *data;

    data = (t_data *)data1;
    mlx_destroy_window(data->mlx, data->mlx_win);
    exit(1);
}

double normalizeAngle(double angle)
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
    return angle;
}

int key_p(int keycode, void *data1)
{
    t_data *data;
    double moveStep;
    int check_x;
    int check_y;

    data = (t_data *)data1;
    if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_A)
        data->player.walkDirection = 1;
    else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_D)
        data->player.walkDirection = -1;
    else if (keycode == KEY_LEFT)
        data->player.turnDirection = -1;
    else if (keycode == KEY_RIGHT)
        data->player.turnDirection = 1;
    else if (keycode == ESC)
        exit(1);
    data->player.rotationAngle += data->player.turnDirection * data->player.rotationSpeed;
    data->player.rotationAngle = normalizeAngle(data->player.rotationAngle);
    moveStep = data->player.walkDirection * data->player.moveSpeed;
    if (keycode == KEY_A || keycode == KEY_D)
    {
        check_x = data->player.x - round(cos(deg2rad(data->player.rotationAngle + 90)) * moveStep);
        check_y = data->player.y - round(sin(deg2rad(data->player.rotationAngle + 90)) * moveStep);
    }
    else
    {
        check_x = data->player.x + round(cos(deg2rad(data->player.rotationAngle)) * moveStep);
        check_y = data->player.y + round(sin(deg2rad(data->player.rotationAngle)) * moveStep);
    }
    printf("walkDirection: %f\n", data->player.walkDirection);
    printf("rotationAngle: %f\n", data->player.rotationAngle);
    if (data->map[data->player.y / TILE_SIZE][check_x / TILE_SIZE] != '1')
        data->player.x = check_x;
    if (data->map[check_y / TILE_SIZE][data->player.x / TILE_SIZE] != '1')
        data->player.y = check_y;
    return 0;
}

int key_r(int keycode, void *var)
{
    t_data *data;

    data = (t_data *)var;
    if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_A)
        data->player.walkDirection = 0;
    else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_D)
        data->player.walkDirection = 0;
    else if (keycode == KEY_LEFT)
        data->player.turnDirection = 0;
    else if (keycode == KEY_RIGHT)
        data->player.turnDirection = 0;
    return 0;
}

int render_next_frame(void *data1)
{
    t_data *data;

    data = (t_data *)data1;
    render_minimap(data);
    return 0;
}