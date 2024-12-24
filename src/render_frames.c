/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:54 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/24 10:23:35 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
    floor_ceiling(data->game_frame, BLUE, WHITE);
    create_frame(data, 0, 0);
    take_weapon(data);
    // printf("data animate weapon = %i\n", data->animate_weapon);
    if (data->animate_weapon)
        animate_weapon_shoting(data, data->all_weapons[data->weapon_numb].shoting_end);
    if (data->weapon_reload)
        animate_weapon_reload(data, data->all_weapons[data->weapon_numb].shoting_end);
    // printf("player x: %i\nplayer y: %i\n", data->player.x, data->player.y);
    render_bullets(data);
    //TODO=rays calculation

    //put the image to the window
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
    
    return 0;
}