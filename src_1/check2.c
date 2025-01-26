/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:03:17 by rbenmakh          #+#    #+#             */
/*   Updated: 2025/01/26 01:30:40 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_color(int mod, char *col, t_data *data)
{
	char	**tmp;
	int		check;
	int		i;
	int		c[3];
	char	*test;

	i = 0;
	test = ft_strrchr(col, ',');
	if (*(test + 1) == '\0')
		return (false);
	tmp = ft_split(col, ',');
	while (i < 3)
	{
		check = ft_atoi(tmp[i]);
		if (!(check >= 0 && check <= 255))
			return (free_arr((void *)tmp, 0, 1), false);
		c[i] = check;
		i++;
	}
	if (tmp[i])
		return (free_arr((void *)tmp, 0, 1), false);
	free_arr((void *)tmp, 0, 1);
	data->color[mod] = create_trgb(0, c[0], c[1], c[2]);
	return (true);
}

int	provide_config(t_data *d, char **arr, char *t, char **tp)
{
	int	i[3];

	i[0] = 0;
	(void)t;
	while (i[0] < 6)
	{
		tp = ft_split(arr[i[0]], ' ');
		if (!tp || !tp[1] || (tp[1] && tp[2]))
			return (free_arr((void **)tp, 0, 1), false);
		i[2] = open(tp[1], 0644);
		if (i[2] < 0 && i[0] < 4)
			return (free_txt(d->txt), free_arr((void **)tp, 0, 1), false);
		i[1] = line_processing(arr[i[0]], NULL, 0);
		if (i[1] < 6)
			d->txt[i[1] - 2] = ft_strdup(tp[1]);
		else
			if (!check_color(i[0] - 4, tp[1], d))
				return (free_txt(d->txt), free_arr((void **)tp, 0, 1), 0);
		free_arr((void **)tp, 0, 1);
		i[0]++;
	}
	return (true);
}
