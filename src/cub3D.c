/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:25:55 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/23 13:45:41 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	init_weapon_names(&data);
	init_weapons(&data, 0, 0, 0);
	if (!init_textures(&data, data.txt, 0))
	{
		printf("mlx_xpm_to_image fails\n");
		return (false);
	}
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
