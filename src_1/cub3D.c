/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:25:55 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/26 01:48:20 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	loading(t_data *data)
{
	t_img_info	loading;

	loading.img_height = 800;
	loading.img_width = 600;
	loading.img = mlx_xpm_file_to_image(data->mlx, "./textures/loading.xpm",
			&loading.img_width, &loading.img_height);
	mlx_put_image_to_window(data->mlx, data->mlx_win, loading.img, 0, 0);
	mlx_destroy_image(data->mlx, loading.img);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Error There is no map\n"));
	else
		printf("Config file name : %s\n", argv[1]);
	if (!setup(argv, &data))
		return (1);
	intialize_data(&data, data.map);
	loading(&data);
	init_weapon_names(&data);
	init_weapons(&data, 0, 0, 0);
	if (!init_textures(&data, data.txt, 0))
		return (printf("mlx_xpm_to_image fails\n"), false);
	p_setup(&data.player, data.map);
	init_bullet(&data);
	mlx_hook(data.mlx_win, ON_DESTROY, 0, close_win, &data);
	mlx_hook(data.mlx_win, ON_KEYDOWN, 1L << 0, key_p, &data);
	mlx_hook(data.mlx_win, ON_KEYUP, 1L << 1, key_r, &data);
	mlx_hook(data.mlx_win, ON_MOUSEDOWN, 1L << 2, mouse_down, &data);
	mlx_hook(data.mlx_win, ON_MOUSEMOVE, 1L << 6, mouse_hook, &data);
	mlx_hook(data.mlx_win, 8, 1L << 5, mouse_out, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_loop(data.mlx);
	return (0);
}
