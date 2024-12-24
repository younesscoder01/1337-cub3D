/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:11:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/24 10:11:13 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int close_win(void *data1)
{
    t_data *data;

    data = (t_data *)data1;
    mlx_destroy_window(data->mlx, data->mlx_win);
    exit(1);
}