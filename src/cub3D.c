/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:25:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/19 17:54:56 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int main(int argc, char **argv)
{
    t_img_info minimap_img;
    void *mlx;
    void *mlx_win;
    t_player p;
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
    minimap_img.img_height =  get_map_height(map) * TILE_SIZE;
    minimap_img.img_width = get_map_width(map) * TILE_SIZE;
    printf("height = %i\nwidth = %i\n", minimap_img.img_height, minimap_img.img_width);
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
    minimap_img.img = mlx_new_image(mlx, minimap_img.img_width, minimap_img.img_height);

    minimap_img.addr = mlx_get_data_addr(minimap_img.img, &minimap_img.bits_per_pixel, &minimap_img.line_length, &minimap_img.endian);
    data.mlx = mlx;
    data.mlx_win = mlx_win;
    data.minimap_img = &minimap_img;
    data.map = map;
    data.player = p;
    p_setup(&data.player, data.map);
    mlx_hook(mlx_win, ON_DESTROY, 0, close_win, &data);
    mlx_hook(mlx_win, ON_KEYDOWN, 1L << 0, key_p, &data);
    mlx_hook(mlx_win, ON_KEYUP, 1L << 1, key_r, &data);
    mlx_loop_hook(mlx, render_next_frame, &data);
    mlx_loop(mlx);
    return (0);
}