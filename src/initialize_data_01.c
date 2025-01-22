/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:15:13 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/22 21:22:18 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	intialize_data_1(t_data *data, char **map)
{
	data->mouse_x = 0;
	data->minimap_img = malloc(sizeof(t_img_info));
	data->frame = malloc(sizeof(t_img_info));
	data->game_frame = malloc(sizeof(t_img_info));
	data->minimap_img->img_height = get_map_height(map) * TILE_SIZE;
	data->minimap_img->img_width = get_map_width(map) * TILE_SIZE;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	data->minimap_img->img = mlx_new_image(data->mlx,
			data->minimap_img->img_width, data->minimap_img->img_height);
	data->minimap_img->addr = mlx_get_data_addr(data->minimap_img->img,
			&data->minimap_img->bits_per_pixel, &data->minimap_img->line_length,
			&data->minimap_img->endian);
}

void	intialize_data(t_data *data, char **map)
{
	intialize_data_1(data, map);
	data->frame->img_height = FRAME_HEIGHT;
	data->frame->img_width = FRAME_WIDTH;
	data->frame->img = mlx_new_image(data->mlx, data->frame->img_width,
			data->frame->img_height);
	data->frame->addr = mlx_get_data_addr(data->frame->img,
			&data->frame->bits_per_pixel, &data->frame->line_length,
			&data->frame->endian);
	data->game_frame->img_height = WINDOW_HEIGHT;
	data->game_frame->img_width = WINDOW_WIDTH;
	data->game_frame->img = mlx_new_image(data->mlx,
			data->game_frame->img_width, data->game_frame->img_height);
	data->game_frame->addr = mlx_get_data_addr(data->game_frame->img,
			&data->game_frame->bits_per_pixel, &data->game_frame->line_length,
			&data->game_frame->endian);
	data->animate_weapon = false;
	data->weapon_numb = 0;
	data->frame_index = 0;
}

void	init_weapon_names(t_data *data)
{
	data->weapon_names = malloc(sizeof(char *) * 8);
	data->weapon_names[0] = strdup("./textures/SPAR/SPAR01.xpm");
	data->weapon_names[1] = strdup("./textures/Rapr/Rapr01.xpm");
	data->weapon_names[2] = strdup("./textures/RPG7/RPG01.xpm");
	data->weapon_names[3] = strdup("./textures/Gr/Grena01.xpm");
	data->weapon_names[4] = strdup("./textures/Baton/Baton01.xpm");
	data->weapon_names[5] = strdup("./textures/SabrinMK3/3Sab01.xpm");
	data->weapon_names[6] = strdup("./textures/CA-MG/CAMG01.xpm");
	data->weapon_names[7] = NULL;
}
