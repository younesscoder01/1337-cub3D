/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:24:49 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/24 17:36:41 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

size_t	get_map_width(char **map_name)
{
	int		i;
	size_t	max;

	i = 1;
	max = strlen(map_name[0]);
	while (map_name[i])
	{
		if (strlen(map_name[i]) > max)
			max = strlen(map_name[i]);
		i++;
	}
	return (max);
}

size_t	get_map_height(char **map_name)
{
	int	i;

	i = 0;
	while (map_name[i])
		i++;
	return (i);
}

void	draw_b(t_data *d)
{
	t_line_cor	cor;

	cor.x = 0;
	cor.y = 0;
	cor.x1 = FRAME_WIDTH;
	cor.y1 = 10;
	rect(d->frame, &cor, LBAR9O9I);
	cor.x = 0;
	cor.y = 0;
	cor.x1 = 10;
	cor.y1 = FRAME_HEIGHT;
	rect(d->frame, &cor, LBAR9O9I);
	cor.x = 0;
	cor.y = FRAME_HEIGHT - 10;
	cor.x1 = FRAME_WIDTH;
	cor.y1 = 10;
	rect(d->frame, &cor, LBAR9O9I);
	cor.x = FRAME_WIDTH - 10;
	cor.y = 0;
	cor.x1 = 10;
	cor.y1 = FRAME_HEIGHT;
	rect(d->frame, &cor, LBAR9O9I);
}
