/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:00:32 by rbenmakh          #+#    #+#             */
/*   Updated: 2025/01/23 22:03:08 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_arr(void **arr, int i, int flag)
{
	int	flag2;

	if (i)
		flag2 = 1;
	else
		flag2 = 0;
	if (!arr)
		return ;
	if (!i)
		i = 0;
	while ((flag2 && i >= 0) || (!flag2 && arr[i]))
	{
		free(arr[i]);
		if (flag2)
			i--;
		else
			i++;
	}
	if (flag)
		free(arr);
}

void	free_txt(char **arr)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (arr[i])
			free(arr[i]);
		arr[i] = NULL;
		i++;
	}
}

// memset the array of textures with 0
void	init_arr(char **arr, int l)
{
	int	i;

	i = 0;
	while (i < l)
	{
		arr[i] = 0;
		i++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	get_player(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W'
				|| map[i][j] == 'S')
			{
				*x = i;
				*y = j;
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}
