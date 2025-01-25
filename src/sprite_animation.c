/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:08:50 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/24 16:27:15 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	render_bullets(t_data *data)
{
	t_line_cor	cor;

	cor.x = 0;
	cor.y = 0;
	cor.x1 = data->no_bullet->img_width;
	cor.y1 = data->no_bullet->img_height;
	if (data->all_weapons[data->weapon_numb].ammo_numb == 0)
		copy_img_sprite(data->no_bullet, data->game_frame, &cor);
	else
		copy_img_sprite(data->bullet, data->game_frame, &cor);
	return (0);
}

unsigned int	get_px_color(t_img_info *img, int x, int y)
{
	char	*pxl;

	pxl = 0;
	if (x >= 0 && x < img->img_width && y >= 0 && y < img->img_height)
	{
		pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
	}
	if (pxl == 0)
		return (6);
	return (*(unsigned int *)pxl);
}

// cor->y = = x, cor->y =  y, cor->y1 = height, cor->x1 = width
void	copy_img(t_img_info *src, t_img_info *dest, t_line_cor *cor)
{
	int	i;
	int	j;
	int	xc;

	i = 0;
	while (i < cor->y1)
	{
		j = 0;
		xc = cor->x;
		while (j < cor->x1)
		{
			ft_put_pixel(dest, j, i, get_px_color(src, xc, cor->y));
			xc++;
			j++;
		}
		cor->y++;
		i++;
	}
}

void	check_frame_end(t_data *d, int last_end, int end)
{
	if (d->frame_index + last_end == end)
	{
		d->weapon_reload = false;
		d->all_weapons[d->weapon_numb].ammo_numb = \
		d->all_weapons[d->weapon_numb].default_ammo;
		d->frame_index = 0;
	}
}

// cor->y = = x, cor->y =  y, cor->y1 = height, cor->x1 = width
void	copy_img_sprite(t_img_info *src, t_img_info *dest, t_line_cor *cor)
{
	int	i;
	int	j;
	int	xc;
	int	color;

	i = 0;
	while (i < cor->y1)
	{
		j = 0;
		xc = cor->x;
		while (j < cor->x1)
		{
			color = get_px_color(src, xc, cor->y);
			if (color != 65535 && color != 592187 && color != -16777216)
				ft_put_pixel(dest, j, i, color);
			xc++;
			j++;
		}
		cor->y++;
		i++;
	}
}
