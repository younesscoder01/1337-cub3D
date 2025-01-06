/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:23:40 by rbenmakh          #+#    #+#             */
/*   Updated: 2025/01/06 10:45:08 by rbenmakh         ###   ########.fr       */
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
int check_boundaries(char **map, size_t map_h)
{
	size_t i;
	size_t j;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(i == 0 || i == map_h - 1)
			{
				if(map[i][j] != '1' && map[i][j] != ' ')
					return(false);
			}
			if(j == 0 || j == ft_strlen(map[i]) - 1)
			{
				if(map[i][j] != '1' && map[i][j] != ' ')
					return(false);
			}
			j++;
		}
		i++;
	}
	return(true);
}
int line_processing(char *str, int *item, int mod)
{
	while (*str)
	{
		if(mod &&( *str != 'N' &&  *str != 'E' &&  *str != 'W' &&  *str != 'S' && *str != '0' && *str != '1' && *str != ' ' && *str != '\n' && *str != 'D'))
			return(false);
		if(item && (*str == 'N' || *str == 'E' ||  *str == 'W' ||  *str == 'S'))
			*item += 1;
		if(ft_strnstr(str, "NO ", 3))
			return(2);
		else if(ft_strnstr(str, "EA ", 3))
			return(3);
		else if(ft_strnstr(str, "WE ", 3))
			return(4);
		else if(ft_strnstr(str, "SO ", 3))
			return(5);
		else if(ft_strnstr(str, "C ", 2))
			return(6);
		else if(ft_strnstr(str, "F ", 2))
			return(7);
		else if(!mod)
			return(false);
		str++;
	}
	return(true);
}
void print_map(char **str)
{
	for(int i =0; str[i]; i++)
	{
		printf("%s\n", str[i]);
	}
}

//make function that gets the player position
void get_player(char **map, int *x, int *y)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
			{
				*x = i;
				*y = j;
				return;
			}
			j++;
		}
		i++;
	}
	return;
}
//free the int array
void free_arr(void **arr, int i, int flag)
{
	int flag2;

	if(i)
		flag2 = 1;
	else
		flag2 = 0;
	if(!arr)
		return;
	if(!i)
		i = 0;
	while ((flag2 && i >= 0) || (!flag2 && arr[i]) )
	{
		free(arr[i]);
		if(flag2)
			i--;
		else
			i++;
	}
	if(flag)
		free(arr);
}
void free_txt(char ** arr)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if(arr[i])
			free(arr[i]);
		arr[i] = NULL;
		i++;
	}
}

//function that check each cell of the map and look in all directions if it is open
int check_map(char **map, size_t i, size_t j)
{
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if(map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if(j == 0 ||(j > 0 && map[i][j - 1] == ' ') || (j > 0 && map[i][j + 1] == ' ') \
				|| (j > 0 && map[i][j + 1] == '\0')|| i == 0 || (i > 0 && map[i - 1][j] == ' ' )\
				|| (i > 0 && map[i+1] && j<= ft_strlen(map[i+1]) && map[i + 1][j] == ' ') \
				|| (i > 0 && map[i+1] && j <= ft_strlen(map[i+1]) && map[i + 1][j] == '\0')\
				|| (i > 0 && j > ft_strlen(map[i - 1])) || (i > 0 && map[i+1] && j > ft_strlen(map[i + 1])))
					return(false);
			}
			j++;
		}
		i++;
	}
	return(true);
}
int finalize_map(int fd, t_data *data, int i[2], char *full)
{
	int item;
	int j ;
	
	item = i[0];
	j = i[1];
	if(!item || item > 1)
	{
		free(full);
		close(fd);
		return(false);
	}
	data->map = ft_split(full, '\n');
	free(full);
	data->map_y = j;
	data->map_x = find_longest_row(data->map);
	if(!check_map(data->map, 0 , 0))
		return(free_arr((void **)data->map, j, 1),false);
	close(fd);
	print_map(data->map);
	return(true);
}
int process_newline(char *line, int fd, int i)
{
	if (i > 0 && line[i] == '\0')
	{
		int j = 0;
		free(line);
		line = get_next_line(fd);
		if(!line)
			return (2);
		while (line)
		{
			while (line[j])
			{
				if (line[j] != ' ' && line[j] != '\n' && line[j] != '\t')
					return(free(line), false);
				j++;
			}
			free(line);
			line = get_next_line(fd);
			if(!line)
				return (2);
		}
	}
	return (true);
}
char *skip_new_line(int fd)
{
	int i;
	char *line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		while (line[i] && (line[i] == '\n' || line[i] == ' ' || line[i] == '\t'))
			i++;
		if(line[i] != '\0')
			break;
		free(line);
		line = get_next_line(fd);
	}
	return(line);
}
void advance_nl(char *str, int *i)
{
	*i = 0;
	while (str[*i] && (str[*i] == '\n' || str[*i] == ' ' || str[*i] == '\t'))
		*i = *i + 1;
}
int read_map(int fd, t_data *data, int i[4], char *s[3])
{
	s[0] = skip_new_line(fd);
	if(!s[0])
		return(false);
	s[1] = ft_strdup("\n");
	while (s[0])
	{
		advance_nl(s[0], &i[2]);
		i[3] = process_newline(s[0], fd, i[2]);
		if(i[3] == 2)
				return finalize_map(fd, data, i, s[1]);
		else if(!i[3])
			return(get_next_line(-1),free(s[1]),close(fd), false);
		else
		{
			if(!line_processing(s[0], &i[0], 1))	
				return(free(s[0]),free(s[1]),close(fd),get_next_line(-1), 0);
			s[2] = s[1];
			s[1] = ft_strjoin(s[1], s[0]);
			free(s[0]);
			free(s[2]);
			s[0] = get_next_line(fd);
			i[1]++;
		}
	}
	return finalize_map(fd, data, i, s[1]);
}

void print_char_arr(char **arr)
{
	for(int i = 0; arr[i]; i++)
	{
		printf("%d %s\n", i,arr[i]);
	}
}
//memset the array of textures with 0
void init_arr(char **arr, int l)
{
	for(int i = 0; i < l; i++)
	{
		arr[i] = 0;
	}
}
int create_trgb(int t, int r, int g, int b) 
{
    return (t << 24 | r << 16 | g << 8 | b);
}
int check_color(int mod, char *col, t_data *data)
{
	char **tmp;
	int check;
	int i;
	int c[3];
	char *test; 

	i = 0;
	test = ft_strrchr(col, ',');
	if(*(test + 1) == '\0')
		return(false);
	tmp =ft_split(col, ',');
	while (i < 3)
	{
		check = ft_atoi(tmp[i]);
		if(!(check >= 0  && check < 255))
			return(free_arr((void *)tmp, 0, 1), false);
		c[i] = check;
		i++;
	}
 	if(tmp[i])
		return(free_arr((void *)tmp, 0, 1), false);
	free_arr((void *)tmp, 0, 1);
	data->color[mod] = create_trgb(0, c[0], c[1], c[2]);
	return(true);
}
int provide_config(t_data *data, char **arr, char *t, char **tmp)
{
	int i[3];

	i[0] = 0;
	while (i[0] < 6)
	{
		tmp = ft_split(arr[i[0]], ' ');
		if(!tmp || !tmp[1] || (tmp[1] && tmp[2]))
			return(free_arr((void **)tmp, 0, 1), false);
		t = tmp[1];
		tmp[1] = ft_strtrim(tmp[1], "\n");
		free(t);
		i[2] = open(tmp[1], 0644);
		if(i[2] < 0 && i[0] < 4)
			return(free_txt(data->txt),free_arr((void **)tmp, 0, 1), false);
		i[1]= line_processing(arr[i[0]], NULL, 0);
		if(i[1]< 6)
			data->txt[i[1]- 2] = ft_strdup(tmp[1]);
		else
		{
			if(!check_color(i[0] - 4, tmp[1], data))				
				return(free_txt(data->txt), free_arr((void **)tmp, 0, 1), false);
		}
		free_arr((void **)tmp, 0, 1);
		i[0]++;
	}
	return(true);
}
int process_texture_line(char *read, char **arr, int *tot, int fd)
{
	int ret;

	ret = line_processing(read, NULL, 0);
	if(!ret)
	{
		free(read);
		close(fd);
		return(free_arr((void **)arr, 6, 0),false);
	}
	*tot += ret;
	arr[ret-2] = ft_strdup(read);
	free(read);
	return (true);
}
int read_textures_colors(t_data *data, int fd,	int tot)
{
	char *read;
	char *arr[7];

	read = get_next_line(fd);
	init_arr(arr, 7);
	init_arr(data->txt, 4);
	while (read)
	{
		if(read[0] == '\n')
		{
			free(read);
			read = get_next_line(fd);
			continue;
		}
		if (!process_texture_line(read, arr, &tot, fd))
			return(get_next_line(-1),false);
		if(arr[0] && arr[1] && arr[2] && arr[3] && arr[4] && arr[5])
			break;
		read = get_next_line(fd);
	}
	if(tot > 27 || !provide_config(data, arr, NULL, NULL))
		return(get_next_line(-1),free_arr((void **)arr, 0, 0),false);
	print_char_arr(arr);
	return(free_arr((void **)arr, 0, 0), true);
}

void print_config(t_data *data)
{
	for(int i = 0; i < 4; i++)
	{
		printf("%s\n", data->txt[i]);
	}
	printf("%d\n", data->color[0]);
	printf("%d\n", data->color[1]);
}
int init_textures(t_data *data,char **txt , int i)
{
	while (i < 4)
	{
		data->textures[i] = (t_img_info *)malloc(sizeof(t_img_info));
		data->textures[i]->img_height = 64;
		data->textures[i]->img_width = 64;
		data->textures[i]->img = mlx_xpm_file_to_image(data->mlx, txt[i], &data->textures[i]->img_height, &data->textures[i]->img_width);
		if(data->textures[i]->img == NULL)
			return(false);
		data->textures[i]->addr = mlx_get_data_addr(data->textures[i]->img, &data->textures[i]->bits_per_pixel, &data->textures[i]->line_length, &data->textures[i]->endian);
		i++;
	}
	data->door = (t_img_info *)malloc(sizeof(t_img_info));
	data->door->img_height = 64;
	data->door->img_width = 64;
	data->door->img = mlx_xpm_file_to_image(data->mlx, "./wall_txt/Black4 copy.xpm", &data->door->img_height, &data->door->img_width);
	if(data->door->img == NULL)
		return(false);
	data->door->addr = mlx_get_data_addr(data->door->img, &data->door->bits_per_pixel, &data->door->line_length, &data->door->endian);
	//FIX why segfault
	free_txt(data->txt);
	return(true);
}
int check_extension(char *file)
{
	char *tmp;

	tmp = ft_strrchr(file, '.');
	if (*file == '.' || !tmp || ft_strncmp(tmp, ".cub", 5))
		return(false);
	return(true);
}
int setup(char **argv, t_data *d)
{
	int i[4];
	char *str[3];	
	
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if(!check_extension(argv[1]))	
		return(printf("Error\nFile extension is not correct must be *.cub\n"), false);
	int fd = open(argv[1], 0644);
	if(fd < 0)
		return(false);

	if(!read_textures_colors(d, fd, 0))
	{
		close(fd);
		return(printf("Error\nfalse textures or colors\n"),false);
	}
	if(!read_map(fd, d, i, str))
	{
		printf("Error\nfalse map\n");
		free_txt(d->txt);
		return(false); 
	}
	return(true);
}

