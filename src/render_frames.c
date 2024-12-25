/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:54 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/25 09:41:54 by rbenmakh         ###   ########.fr       */
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


unsigned int get_px_color(t_img_info *img, int x, int y)
{
    char *pxl;

    pxl = 0;
    if (x >= 0 && x < img->img_width && y >= 0 && y < img->img_height)
    {
        pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    }
    if (pxl == 0)
        return 6;
    return *(unsigned int *)pxl;
}


void copy_img(t_img_info *src, t_img_info *dest, int x, int y, int height, int width)
{
    int i;
    int j;
    int xc;

    i = 0;
    while (i < height)
    {
        j = 0;
        xc = x;
        while (j < width)
        {
            ft_put_pixel(dest, j, i, get_px_color(src, xc, y));
            xc++;
            j++;
        }
        y++;
        i++;
    }
}
void rect(t_img_info *img, int x, int y, int width, int height, int color)
{
    int i;
    int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            ft_put_pixel(img, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void create_frame(t_data *data, int fx, int fy)
{
    fx = data->player.x - FRAME_WIDTH / 2;
    fy = data->player.y - FRAME_HEIGHT / 2;
    
    if (fx < 0)
        fx = 0;
    else if (fx > data->minimap_img->img_width)
        fx = data->minimap_img->img_width - FRAME_WIDTH;
    if (fy < 0)
        fy = 0;
    else if (fy > data->minimap_img->img_height)
        fy = data->minimap_img->img_height - FRAME_HEIGHT;
    copy_img(data->minimap_img, data->frame, fx, fy, FRAME_HEIGHT, FRAME_WIDTH);
    rect(data->frame, 0, 0, FRAME_WIDTH, 10, lfaa5ti);
    rect(data->frame, 0, 0, 10, FRAME_WIDTH, lfaa5ti);
    rect(data->frame, 0, FRAME_HEIGHT - 10, FRAME_WIDTH, 10, lfaa5ti);
    rect(data->frame, FRAME_WIDTH - 10, 0, 10, FRAME_HEIGHT, lfaa5ti);
    copy_img(data->frame, data->game_frame, 0, 0, FRAME_HEIGHT, FRAME_WIDTH);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
}

void floor_ceiling(t_img_info *img, int color1, int color2)
{
    int i;
    int j;

    i = 0;
    while (i < img->img_height / 2)
    {
        j = 0;
        while (j < img->img_width)
        {
            ft_put_pixel(img, j, i, color1);
            j++;
        }
        i++;
    }
    while (i < img->img_height)
    {
        j = 0;
        while (j < img->img_width)
        {
            ft_put_pixel(img, j, i, color2);
            j++;
        }
        i++;
    }
}

int render_next_frame(void *data1)
{
    t_data *data;

    data = (t_data *)data1;
    render_minimap(data);
    calc_rays(data);
    floor_ceiling(data->game_frame, BLUE, WHITE);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap_img->img, 0, 0);
    create_frame(data, 0, 0);
    // printf("player x: %i\nplayer y: %i\n", data->player.x, data->player.y);
    //TODO=rays calculation
    
    return 0;
}