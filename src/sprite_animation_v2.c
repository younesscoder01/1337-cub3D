/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation_v2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:15:41 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/24 23:08:48 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	take_weapon(t_data *data)
{
	t_line_cor	cor;

	cor.x = 0;
	cor.y = 0;
	cor.x1 = data->all_weapons[data->weapon_numb].weapon[0]->img_width;
	cor.y1 = data->all_weapons[data->weapon_numb].weapon[0]->img_height;
	if (data->all_weapons[data->weapon_numb].ammo_numb == 0
		&& data->weapon_numb == 2)
		copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[7],
			data->game_frame, &cor);
	else
		copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[0],
			data->game_frame, &cor);
}

int	set_up_animation_delay(int n_frame)
{
	if (n_frame >= 38)
		return (30000);
	else if (n_frame <= 25)
		return (60000);
	return (40000);
}

void	rendering(t_data *d)
{
	render_minimap(d);
	castallrays(d);
	floor_ceiling(d->game_frame, d->color[0], d->color[1]);
	render_3d_walls(d);
	create_frame(d, 0, 0, (t_line_cor){0, 0, 0, 0});
}

void	animate_weapon_shoting(t_data *d, int end)
{
	int			animation_delay;
	t_line_cor	cor;

	if (d->all_weapons[d->weapon_numb].ammo_numb == 0)
	{
		(d->animate_weapon = false);
		return ;
	}
	animation_delay = set_up_animation_delay(end);
	rendering(d);
	cor.x = 0;
	cor.y = 0;
	cor.x1 = d->all_weapons[d->weapon_numb].weapon[d->frame_index]->img_width;
	cor.y1 = d->all_weapons[d->weapon_numb].weapon[d->frame_index]->img_height;
	copy_img_sprite(d->all_weapons[d->weapon_numb].weapon[d->frame_index],
		d->game_frame, &cor);
	usleep(animation_delay);
	d->frame_index++;
	if (d->frame_index == end)
	{
		d->animate_weapon = false;
		if (d->all_weapons[d->weapon_numb].ammo_numb != -1)
			d->all_weapons[d->weapon_numb].ammo_numb--;
	}
	d->frame_index = d->frame_index % end;
}

void	animate_weapon_reload(t_data *d, int last_end)
{
	int			animation_delay;
	int			end;
	t_line_cor	cor;

	end = d->all_weapons[d->weapon_numb].frame_numb;
	if (d->all_weapons[d->weapon_numb].ammo_numb == \
	d->all_weapons[d->weapon_numb].default_ammo
		|| d->all_weapons[d->weapon_numb].ammo_numb == -1)
	{
		d->weapon_reload = false;
		return ;
	}
	animation_delay = set_up_animation_delay(end - last_end);
	rendering(d);
	cor.x = 0;
	cor.y = 0;
	cor.x1 = d->all_weapons[d->weapon_numb].weapon[d->frame_index
		+ last_end]->img_width;
	cor.y1 = d->all_weapons[d->weapon_numb].weapon[d->frame_index
		+ last_end]->img_height;
	copy_img_sprite(d->all_weapons[d->weapon_numb].weapon[d->frame_index
		+ last_end], d->game_frame, &cor);
	usleep(animation_delay);
	d->frame_index++;
	check_frame_end(d, last_end, end);
}
