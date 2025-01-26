/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:02:16 by rbenmakh          #+#    #+#             */
/*   Updated: 2025/01/26 19:11:20 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	find_longest_row(char **map)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	check_boundaries(char **map, size_t map_h)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0 || i == map_h - 1)
			{
				if (map[i][j] != '1' && map[i][j] != ' ')
					return (false);
			}
			if (j == 0 || j == ft_strlen(map[i]) - 1)
			{
				if (map[i][j] != '1' && map[i][j] != ' ')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	line_processing(char *str, int *item, int mod)
{
	while (*str)
	{
		if (mod && (*str != 'N' && *str != 'E' && *str != 'W' && *str != 'S'
				&& *str != '0' && *str != '1' && *str != ' ' && *str != '\n'
			))
			return (false);
		if (item && (*str == 'N' || *str == 'E' || *str == 'W' || *str == 'S'))
			*item += 1;
		if (ft_strnstr(str, "NO ", 3))
			return (2);
		else if (ft_strnstr(str, "EA ", 3))
			return (3);
		else if (ft_strnstr(str, "WE ", 3))
			return (4);
		else if (ft_strnstr(str, "SO ", 3))
			return (5);
		else if (ft_strnstr(str, "C ", 2))
			return (6);
		else if (ft_strnstr(str, "F ", 2))
			return (7);
		else if (!mod)
			return (false);
		str++;
	}
	return (true);
}

int	check_map(char **map, size_t i, size_t j)
{
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (j == 0 || (j > 0 && map[i][j - 1] == ' ') || (j > 0
						&& map[i][j + 1] == ' ') || (j > 0 && map[i][j
						+ 1] == '\0') || i == 0 || (i > 0 && map[i
						- 1][j] == ' ') || (i > 0 && map[i + 1]
						&& j <= ft_strlen(map[i + 1]) && map[i + 1][j] == ' ')
					|| (i > 0 && map[i + 1] && j <= ft_strlen(map[i + 1])
						&& map[i + 1][j] == '\0') || (i > 0
						&& j > ft_strlen(map[i - 1]) - 1) || (i > 0 && map[i
						+ 1] && j > ft_strlen(map[i + 1])))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	finalize_map(int fd, t_data *data, int i[2], char *full)
{
	int	item;
	int	j;

	item = i[0];
	j = i[1];
	if (!item || item > 1)
	{
		free(full);
		close(fd);
		return (false);
	}
	data->map = ft_split(full, '\n');
	free(full);
	data->map_y = j;
	data->map_x = find_longest_row(data->map);
	if (!check_map(data->map, 0, 0))
		return (free_arr((void **)data->map, j, 1), false);
	close(fd);
	return (true);
}
