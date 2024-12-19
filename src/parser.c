#include "../includes/cub3D.h"
/*
	- CHECK THE BOUNDARIES OF THE MAP
	TODO : flood fill to check if the map is open
	-UPDATE THE STRUCT WITH 2D MAP
*/
int line_processing(char *str)
{
	while (*str)
	{
		if(*str != 'N' &&  *str != 'E' &&  *str != 'W' &&  *str != 'S' && *str != '0' && *str != '1' && *str != ' ')
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
int read_map(int fd, t_data *data)
{
	char *full;
    char *read;
	char *tmp;
	int j;

    j = 0;
    read = get_next_line(fd);
	full = ft_strdup("\n");
	while (read)
	{
		//parse each line of the map if it contains only 1, 0, N, S, E, W
		if(!line_processing(read))
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
	data->map = ft_split(full, '\n');
	free(full);
	close(fd);
	print_map(data->map);
	return(true);
}

int setup(int argc, char **argv, t_data *d)
{
	(void)argc;
	if(read_map(open(argv[1], 0644), d))
		return(false);
	return(true);
}