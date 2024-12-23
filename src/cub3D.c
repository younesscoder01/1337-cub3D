/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:25:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/22 14:43:04 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
    intialize_data(&data, map, 0, 0);
    init_weapon_names(&data);
    init_weapons(&data);
    p_setup(&data.player, data.map);
    mlx_hook(data.mlx_win, ON_DESTROY, 0, close_win, &data);
    mlx_hook(data.mlx_win, ON_KEYDOWN, 1L << 0, key_p, &data);
    mlx_hook(data.mlx_win, ON_KEYUP, 1L << 1, key_r, &data);
    mlx_loop_hook(data.mlx, render_next_frame, &data);
    mlx_loop(data.mlx);
    return (0);
}