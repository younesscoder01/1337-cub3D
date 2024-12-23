/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:25:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/23 18:34:09 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void init_bullet(t_data *data)
{
    data->bullet = malloc(sizeof(t_img_info));
    data->no_bullet = malloc(sizeof(t_img_info));
    data->no_bullet->img_width = 64;
    data->no_bullet->img_height = 64;
    data->bullet->img_width = 64;
    data->bullet->img_height = 64;
    data->bullet->img = mlx_xpm_file_to_image(data->mlx, "./textures/bullet/bullet.xpm", &data->bullet->img_width, &data->bullet->img_height);
    data->no_bullet->img = mlx_xpm_file_to_image(data->mlx, "./textures/bullet/no_bullet.xpm", &data->no_bullet->img_width, &data->no_bullet->img_height);
    data->bullet->addr = mlx_get_data_addr(data->bullet->img, &data->bullet->bits_per_pixel, &data->bullet->line_length, &data->bullet->endian);
    data->no_bullet->addr = mlx_get_data_addr(data->no_bullet->img, &data->no_bullet->bits_per_pixel, &data->no_bullet->line_length, &data->no_bullet->endian);
}

int main(int argc, char **argv)
{
    t_data data;
    if (argc != 2)
        return printf("Error\n");
    else
        printf("map name : %s\n", argv[1]);
    char **map;
    map = malloc(sizeof(char *) * 6);
    map[0] = "11111";
    map[1] = "10001";
    map[2] = "10S01";
    map[3] = "10001";
    map[4] = "11111";
    map[5] = NULL;
    data.mouse_x = 0;
    intialize_data(&data, map, 0, 0);
    init_weapon_names(&data);
    init_weapons(&data);
    p_setup(&data.player, data.map);
    init_bullet(&data);
    mlx_hook(data.mlx_win, ON_DESTROY, 0, close_win, &data);
    mlx_hook(data.mlx_win, ON_KEYDOWN, 1L << 0, key_p, &data);
    mlx_hook(data.mlx_win, ON_KEYUP, 1L << 1, key_r, &data);
    mlx_hook(data.mlx_win, ON_MOUSEDOWN, 1L << 2, mouse_down, &data);
    mlx_hook(data.mlx_win, ON_MOUSEMOVE, 1L << 6, mouse_hook, &data);
    mlx_loop_hook(data.mlx, render_next_frame, &data);
    mlx_loop(data.mlx);
    return (0);
}