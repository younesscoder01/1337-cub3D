/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:06:28 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/22 12:23:27 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void intialize_data(t_data *data, char **map, void *mlx, void *mlx_win)
{
    t_img_info *minimap_img;
    t_img_info *frame;
    t_img_info *game_frame;

    minimap_img = malloc(sizeof(t_img_info));
    frame = malloc(sizeof(t_img_info));
    game_frame = malloc(sizeof(t_img_info));
    minimap_img->img_height =  get_map_height(map) * TILE_SIZE;
    minimap_img->img_width = get_map_width(map) * TILE_SIZE;
    printf("height = %i\nwidth = %i\n", minimap_img->img_height, minimap_img->img_width);
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
    minimap_img->img = mlx_new_image(mlx, minimap_img->img_width, minimap_img->img_height);
    minimap_img->addr = mlx_get_data_addr(minimap_img->img, &minimap_img->bits_per_pixel, &minimap_img->line_length, &minimap_img->endian);
    frame->img_height = FRAME_HEIGHT;
    frame->img_width = FRAME_WIDTH;
    frame->img = mlx_new_image(mlx, frame->img_width, frame->img_height);
    frame->addr = mlx_get_data_addr(frame->img, &frame->bits_per_pixel, &frame->line_length, &frame->endian);
    game_frame->img_height = WINDOW_HEIGHT;
    game_frame->img_width = WINDOW_WIDTH;
    game_frame->img = mlx_new_image(mlx, game_frame->img_width, game_frame->img_height);
    game_frame->addr = mlx_get_data_addr(game_frame->img, &game_frame->bits_per_pixel, &game_frame->line_length, &game_frame->endian);
    data->mlx = mlx;
    data->mlx_win = mlx_win;
    data->minimap_img = minimap_img;
    data->frame = frame;
    data->map = map;
    data->game_frame = game_frame;
    data->animate_weapon = false;
    data->weapon_numb = 0;
    data->frame_index = 0;
}