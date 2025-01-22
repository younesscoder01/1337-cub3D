/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:06:28 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/22 21:21:48 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	allocate_for_weapons(t_data *data)
{
	data->all_weapons = malloc(sizeof(t_weapons) * WEAPON_N);
	data->all_weapons[0] = (t_weapons){.ammo_numb = 20, .default_ammo = 20,
		.frame_numb = 38, .index_to_change = 20, .shoting_end = 8,
		.weapon = malloc(sizeof(t_img_info *) * 38)};
	data->all_weapons[1] = (t_weapons){.ammo_numb = 2, .default_ammo = 2,
		.frame_numb = 24, .index_to_change = 20, .shoting_end = 6,
		.weapon = malloc(sizeof(t_img_info *) * 24)};
	data->all_weapons[2] = (t_weapons){.ammo_numb = 1, .default_ammo = 1,
		.frame_numb = 45, .index_to_change = 19, .shoting_end = 7,
		.weapon = malloc(sizeof(t_img_info *) * 45)};
	data->all_weapons[3] = (t_weapons){.ammo_numb = -1, .default_ammo = -1,
		.frame_numb = 17, .index_to_change = 19, .shoting_end = 17,
		.weapon = malloc(sizeof(t_img_info *) * 17)};
	data->all_weapons[4] = (t_weapons){.ammo_numb = -1, .default_ammo = -1,
		.frame_numb = 8, .index_to_change = 22, .shoting_end = 8,
		.weapon = malloc(sizeof(t_img_info *) * 8)};
	data->all_weapons[5] = (t_weapons){.ammo_numb = 25, .default_ammo = 25,
		.frame_numb = 39, .index_to_change = 25, .shoting_end = 5,
		.weapon = malloc(sizeof(t_img_info *) * 39)};
	data->all_weapons[6] = (t_weapons){.ammo_numb = 20, .default_ammo = 20,
		.frame_numb = 33, .index_to_change = 21, .shoting_end = 5,
		.weapon = malloc(sizeof(t_img_info *) * 33)};
}

void	init_weapons_1(t_data *data, int i, int j, char *filename)
{
	data->all_weapons[i].weapon[j] = malloc(sizeof(t_img_info));
	data->all_weapons[i].weapon[j]->img_width = WINDOW_WIDTH;
	data->all_weapons[i].weapon[j]->img_height = WINDOW_HEIGHT;
	data->all_weapons[i].weapon[j]->img = mlx_xpm_file_to_image(data->mlx,
			filename, &data->all_weapons[i].weapon[j]->img_width,
			&data->all_weapons[i].weapon[j]->img_height);
	data->all_weapons[i].weapon[j]->addr = mlx_get_data_addr
		(data->all_weapons[i].weapon[j]->img,
			&data->all_weapons[i].weapon[j]->bits_per_pixel,
			&data->all_weapons[i].weapon[j]->line_length,
			&data->all_weapons[i].weapon[j]->endian);
	data->all_weapons[i].weapon[j]->filename = strdup(data->weapon_names[i]);
}

void	init_weapons(t_data *data, int i, int j, int k)
{
	char	*filename;

	allocate_for_weapons(data);
	while (i < WEAPON_N)
	{
		j = 0;
		k = 2;
		filename = strdup(data->weapon_names[i]);
		while (j < data->all_weapons[i].frame_numb)
		{
			init_weapons_1(data, i, j, filename);
			if (k > 9)
			{
				k = data->all_weapons[i].index_to_change;
				filename[k] = filename[data->all_weapons[i].index_to_change]
					+ 1;
				k = 0;
			}
			filename[data->all_weapons[i].index_to_change + 1] = k + 48;
			j++;
			k++;
		}
		free(filename);
		i++;
	}
}
