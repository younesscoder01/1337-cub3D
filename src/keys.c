/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:21:38 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/24 10:22:23 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

    printf("keycode = %i\n", keycode);
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
    else if (keycode == SPACE || keycode == 1)
    {
        data->animate_weapon = true;
        // data->frame_index = 0;
    }
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
    // else if (keycode == SPACE)
    //     data->animate_weapon = false;
    return 0;
}

int mouse_hook(int x, int y, t_data *data)
{
    (void)y;
    if (data->mouse_x < x)
        data->player.turnDirection = 1;
    else if (data->mouse_x > x)
        data->player.turnDirection = -1;
    data->player.rotationAngle += data->player.turnDirection * ROTATION_SPEED;
    data->player.rotationAngle = normalizeAngle(data->player.rotationAngle);
    data->mouse_x = x;
    data->player.turnDirection = 0;
    return (0);
}

int mouse_down(int button, int x, int y, t_data *data)
{
    (void)x;
    (void)y;
    if (button == 1)
    {
        data->animate_weapon = true;
    }
    return (0);
}