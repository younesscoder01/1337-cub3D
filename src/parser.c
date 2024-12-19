#include "../includes/cub3D.h"

int setup(int argc, char **argv, t_data * d)
{
	if(read_map(open(argv[1], 0644), &)
}
int line_porcessing(char *str)
{
	while (*str)
	{
		if(*str != 'N' &&  *str != 'E' &&  *str != 'W' &&  *str != 'S' && *str != '0' && *str != '1' && *str != ' ')
			return(false);
		str++;
	}
	return(true);
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
	printf("starting position: %d %d\n", data->st_pos[0], data->st_pos[1]);

	free(full);
	close(fd);
	return(true);
}