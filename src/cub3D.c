/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:25:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/21 17:47:27 by rbenmakh         ###   ########.fr       */
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
 
    if(!setup(argc, argv, &data))
    {
        printf("false map\n");
        return(1);
    }
    intialize_data(&data, data.map, 0, 0);
    p_setup(&data.player, data.map);
    mlx_hook(data.mlx_win, ON_DESTROY, 0, close_win, &data);
    mlx_hook(data.mlx_win, ON_KEYDOWN, 1L << 0, key_p, &data);
    mlx_hook(data.mlx_win, ON_KEYUP, 1L << 1, key_r, &data);
    mlx_loop_hook(data.mlx, render_next_frame, &data);
    mlx_loop(data.mlx);
    return (0);
}