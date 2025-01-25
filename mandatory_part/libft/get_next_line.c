/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:45:52 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/25 09:45:53 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*_set_line(char **line_buffer, ssize_t nbyte)
{
	char	*line;
	size_t	i;
	char	*tmp;

	i = 0;
	if (nbyte == 0 && !(*line_buffer))
		return (0);
	if ((*line_buffer)[0] == 0)
	{
		free(*line_buffer);
		*line_buffer = NULL;
		return (0);
	}
	while ((*line_buffer)[i] && (*line_buffer)[i] != '\n')
		i++;
	i += ((*line_buffer)[i] == '\n');
	line = ft_substr(*line_buffer, 0, i);
	tmp = ft_substr((*line_buffer), i, ft_strlen((*line_buffer)));
	free((*line_buffer));
	(*line_buffer) = tmp;
	tmp = NULL;
	return (line);
}

char	*fill_line_buffer(int fd, char **leftovers, char *buffer)
{
	ssize_t	nbyte;
	char	*tmp;

	nbyte = 1;
	while (nbyte > 0)
	{
		nbyte = read(fd, buffer, BUFFER_SIZE);
		if (nbyte < 0)
		{
			free(*leftovers);
			(*leftovers) = NULL;
			return (0);
		}
		buffer[nbyte] = '\0';
		if (!(*leftovers))
			(*leftovers) = ft_realloc("", NULL);
		tmp = ft_realloc(*leftovers, buffer);
		free((*leftovers));
		(*leftovers) = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (_set_line(leftovers, nbyte));
}

char	*gnl(int fd)
{
	char		*buffer;
	char		*line;
	static char	*left;

	if (fd == -1)
		free(left);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	line = fill_line_buffer(fd, &left, buffer);
	free(buffer);
	return (line);
}
