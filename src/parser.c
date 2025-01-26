/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:23:40 by rbenmakh          #+#    #+#             */
/*   Updated: 2025/01/26 01:46:09 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	process_texture_line(char *read, char **arr, int *tot, int fd)
{
	int		ret;
	char	*tmp;

	tmp = ft_strtrim(read, " ");
	ret = line_processing(tmp, NULL, 0);
	if (!ret)
	{
		free(tmp);
		free(read);
		close(fd);
		return (free_arr((void **)arr, 6, 0), false);
	}
	free(tmp);
	*tot += ret;
	arr[ret - 2] = ft_strtrim(read, "\n");
	tmp = arr[ret - 2];
	arr[ret - 2] = ft_strtrim(tmp, " ");
	free(tmp);
	free(read);
	return (true);
}

int	read_textures_colors(t_data *data, int fd, int tot)
{
	char	*read;
	char	*arr[7];

	read = gnl(fd);
	init_arr(arr, 7);
	init_arr(data->txt, 4);
	while (read)
	{
		if (read[0] == '\n')
		{
			free(read);
			read = gnl(fd);
			continue ;
		}
		if (!process_texture_line(read, arr, &tot, fd))
			return (gnl(-1), false);
		if (arr[0] && arr[1] && arr[2] && arr[3] && arr[4] && arr[5])
			break ;
		read = gnl(fd);
	}
	if (tot > 27 || !provide_config(data, arr, NULL, NULL))
		return (gnl(-1), free_arr((void **)arr, 0, 0), false);
	return (free_arr((void **)arr, 0, 0), true);
}

int	init_textures(t_data *data, char **txt, int i)
{
	while (i < 4)
	{
		data->textures[i] = (t_img_info *)malloc(sizeof(t_img_info));
		data->textures[i]->img_height = 64;
		data->textures[i]->img_width = 64;
		data->textures[i]->img = mlx_xpm_file_to_image(data->mlx, txt[i],
				&data->textures[i]->img_height, &data->textures[i]->img_width);
		if (data->textures[i]->img == NULL)
			return (false);
		data->textures[i]->addr = mlx_get_data_addr(data->textures[i]->img,
				&data->textures[i]->bits_per_pixel,
				&data->textures[i]->line_length, &data->textures[i]->endian);
		i++;
	}
	data->door = (t_img_info *)malloc(sizeof(t_img_info));
	data->door->img_height = 64;
	data->door->img_width = 64;
	data->door->img = mlx_xpm_file_to_image(data->mlx,
			"./wall_txt/Black4 copy.xpm", &data->door->img_height,
			&data->door->img_width);
	data->door->addr = mlx_get_data_addr(data->door->img,
			&data->door->bits_per_pixel, &data->door->line_length,
			&data->door->endian);
	return (free_txt(data->txt), true);
}

int	check_extension(char *file)
{
	char	*tmp;

	tmp = ft_strrchr(file, '.');
	if (*file == '.' || !tmp || ft_strncmp(tmp, ".cub", 5))
		return (false);
	return (true);
}

int	setup(char **argv, t_data *d)
{
	int		i[4];
	char	*str[3];
	int		fd;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!check_extension(argv[1]))
		return (printf("Error\nFile extension is not correct must be *.cub\n"),
			false);
	fd = open(argv[1], 0644);
	if (fd < 0)
		return (false);
	if (!read_textures_colors(d, fd, 0))
	{
		close(fd);
		return (printf("Error\nfalse textures or colors\n"), false);
	}
	if (!read_map(fd, d, i, str))
	{
		printf("Error\nfalse map\n");
		free_txt(d->txt);
		return (false);
	}
	return (true);
}
