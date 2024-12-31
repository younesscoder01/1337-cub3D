/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:54 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/31 15:49:46 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void floor_ceiling(t_img_info *img, int color1, int color2)
{
    int i;
    int j;
    double alpha;
    double beta;
    int shade_color;

    i = 0;
    alpha = 1;
    beta = 0.000005;
    while (i < img->img_height / 2)
    {
        j = 0;
        alpha += beta;
        shade_color = darken_color(color1, alpha);
        while (j < img->img_width)
        {
            ft_put_pixel(img, j, i, shade_color);
            j++;
        }
        i++;
    }
    alpha = 0.05;
    while (i < img->img_height)
    {
        j = 0;
        alpha += beta;
        while (j < img->img_width)
        {
            shade_color = darken_color(color2, alpha);
            ft_put_pixel(img, j, i, shade_color);
            j++;
        }
        i++;
    }
}

void movement_update(t_data *data)
{
    int check_x, check_y;
    double move_step;

    data->player.rotationAngle += data->player.turnDirection * data->player.rotationSpeed;
    data->player.rotationAngle = normalizeAngle(data->player.rotationAngle);
    move_step = data->player.moveSpeed * data->player.walkDirection;
    check_x = round(move_step * (cos(deg2rad(data->player.rotationAngle+ (90 * data->player.is_move_side)))));
    check_y = round(move_step * (sin(deg2rad(data->player.rotationAngle+ (90 * data->player.is_move_side)))));
    if (data->map[data->player.y/TILE_SIZE][(data->player.x + check_x)/TILE_SIZE ] != '1')
        data->player.x += check_x;
    if ((data->map[(data->player.y + check_y)/TILE_SIZE ][data->player.x/TILE_SIZE] != '1'))
        data->player.y += check_y;
}

int update(void *data1)
{
    t_data *data;

    data = (t_data *)data1;
    if (data->animate_weapon)
        animate_weapon_shoting(data, data->all_weapons[data->weapon_numb].shoting_end);
    else if (data->weapon_reload)
        animate_weapon_reload(data, data->all_weapons[data->weapon_numb].shoting_end);
    else
    {
        render_minimap(data);
        castAllrays(data);
        floor_ceiling(data->game_frame, data->color[0], data->color[1]);
        render_3d_walls(data);
        create_frame(data, 0, 0);
        take_weapon(data);
    }
    render_bullets(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
    movement_update(data);
    
    return 0;
}