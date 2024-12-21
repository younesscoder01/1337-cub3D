#include "../includes/cub3D.h"
/*
	- CHECK THE BOUNDARIES OF THE MAP
	TODO : flood fill to check if the map is open
	-UPDATE THE STRUCT WITH 2D MAP
*/
int line_processing(char *str, int *item)
{
	while (*str)
	{
		if(*str != 'N' &&  *str != 'E' &&  *str != 'W' &&  *str != 'S' && *str != '0' && *str != '1' && *str != ' ' && *str != '\n')
			return(false);
		if(*str == 'N' || *str == 'E' ||  *str == 'W' ||  *str == 'S')
			*item = 1;
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
void free_arr(void **arr, int i)
{
	if(!arr)
		return;
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}
int read_map(int fd, t_data *data)
{
	char *full;
    char *read;
	char *tmp;
	int item;
	int j;

    j = 0;
	item = 0;
    read = get_next_line(fd);
	full = ft_strdup("\n");
	while (read)
	{
		//parse each line of the map if it contains only 1, 0, N, S, E, W
		if(!line_processing(read, &item))
		{
			free(read);
			free(full);
			close(fd);
			return(false);
		}
		//if not return 1
		tmp = full;
		full = ft_strjoin(full, read);
		free(read);
		free(tmp);
		read = get_next_line(fd);
		j++;
	}
	if(!item)
	{
		free(full);
		close(fd);
		return(false);
	}

	data->map = ft_split(full, '\n');
	free(full);
	int start_x;
	int start_y;

	start_x =0;
	start_y = 0;
	data->map_y = j;
	data->map_x = find_longest_row(data->map);
	get_player(data->map, &start_x, &start_y);
	data->check_arr = 0;
	if(bfs(start_y, start_x, data, j))
	{
		free_arr((void **)data->map, j);
		free_arr((void **)data->check_arr, j);
		return(false);
	}
	free_arr((void **)data->check_arr, j);
	close(fd);
	print_map(data->map);
	return(true);
}

int setup(int argc, char **argv, t_data *d)
{
	(void)argc;
	int fd = open(argv[1], 0644);
	if(fd < 0)
		return(false);
	if(!read_map(fd, d))
		return(false);
	return(true);
}