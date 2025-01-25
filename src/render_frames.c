/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:54 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/25 09:31:31 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	floor_ceiling(t_img_info *img, int color1, int color2)
{
    int i;
    int j;
    double alpha;
    int shade_color;

    i = 0;
    while (i < img->img_height / 2)
    {
        j = 0;
        alpha = (double)i / (double)img->img_height;
        shade_color = darken_color(color1, alpha);
        while (j < img->img_width)
        {
            ft_put_pixel(img, j, i, shade_color);
            j++;
        }
        i++;
    }
    alpha = 1;
    while (i < img->img_height)
    {
        j = 0;
        alpha += j * 0.1;
        while (j < img->img_width)
        {
            shade_color = darken_color(color2, alpha);
            ft_put_pixel(img, j, i, shade_color);
            j++;
        }
        alpha = (img->img_height - (double)i) / ((double)img->img_height / 2);
        i++;

    }
}

void	movement_update(t_data *data)
{
	double	move_step;
	int		check_x;
	int		check_y;

	if (data->mouse_x > 0 && data->mouse_x <= 20 && data->mouse_in == 1)
		data->player.turnDirection = -1;
	else if (data->mouse_x <= 800 && data->mouse_x >= 780
		&& data->mouse_in == 1)
		data->player.turnDirection = 1;
	data->player.rotationAngle += data->player.turnDirection
		* data->player.rotationSpeed;
	data->player.rotationAngle = normalizeangle(data->player.rotationAngle);
	move_step = data->player.moveSpeed * data->player.walkDirection;
	check_x = round(move_step * (cos(deg2rad(data->player.rotationAngle + (90
							* data->player.is_move_side)))));
	check_y = round(move_step * (sin(deg2rad(data->player.rotationAngle + (90
							* data->player.is_move_side)))));
	if (data->map[data->player.y / TILE_SIZE][(data->player.x + check_x)
		/ TILE_SIZE] != '1')
		data->player.x += check_x;
	if ((data->map[(data->player.y + check_y) / TILE_SIZE][data->player.x
			/ TILE_SIZE] != '1'))
		data->player.y += check_y;
}

int	update(void *data1)
{
	t_data	*data;

	data = (t_data *)data1;
	if (data->animate_weapon)
		animate_weapon_shoting(data,
			data->all_weapons[data->weapon_numb].shoting_end);
	else if (data->weapon_reload)
		animate_weapon_reload(data,
			data->all_weapons[data->weapon_numb].shoting_end);
	else
	{
		render_minimap(data);
		castallrays(data);
		floor_ceiling(data->game_frame, data->color[0], data->color[1]);
		render_3d_walls(data);
		create_frame(data, 0, 0, (t_line_cor){0, 0, 0, 0});
		take_weapon(data);
	}
	render_bullets(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0,
		0);
	movement_update(data);
	return (0);
}
