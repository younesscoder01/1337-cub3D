/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:25:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/19 21:07:12 by rbenmakh         ###   ########.fr       */
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
    
    (void)argc;
    (void)p;
    (void)mlx;
    (void)mlx_win;
    (void)minimap_img;
    if (argc != 2)
        return printf("Error\n");
    else
        printf("%s\n", argv[1]);
    if(!setup(argc, argv, &data))
    {
        //free all the stuff
        return(1);
    }
    return (0);
}