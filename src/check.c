/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:03:28 by rbenmakh          #+#    #+#             */
/*   Updated: 2025/01/23 22:12:16 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	process_newline(char *line, int fd, int i)
{
	int	j;

	if (i > 0 && line[i] == '\0')
	{
		j = 0;
		free(line);
		line = gnl(fd);
		if (!line)
			return (2);
		while (line)
		{
			while (line[j])
			{
				if (line[j] != ' ' && line[j] != '\n' && line[j] != '\t')
					return (free(line), false);
				j++;
			}
			free(line);
			line = gnl(fd);
			if (!line)
				return (2);
		}
	}
	return (true);
}

char	*skip_new_line(int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = gnl(fd);
	while (line)
	{
		while (line[i] && (line[i] == '\n' || line[i] == ' '
				|| line[i] == '\t'))
			i++;
		if (line[i] != '\0')
			break ;
		free(line);
		line = gnl(fd);
	}
	return (line);
}

void	advance_nl(char *str, int *i)
{
	*i = 0;
	while (str[*i] && (str[*i] == '\n' || str[*i] == ' ' || str[*i] == '\t'))
		*i = *i + 1;
}

int	read_map(int fd, t_data *data, int i[4], char *s[3])
{
	s[0] = skip_new_line(fd);
	if (!s[0])
		return (false);
	s[1] = ft_strdup("\n");
	while (s[0])
	{
		advance_nl(s[0], &i[2]);
		i[3] = process_newline(s[0], fd, i[2]);
		if (i[3] == 2)
			return (finalize_map(fd, data, i, s[1]));
		else if (!i[3])
			return (gnl(-1), free(s[1]), close(fd), false);
		else
		{
			if (!line_processing(s[0], &i[0], 1))
				return (free(s[0]), free(s[1]), close(fd), gnl(-1), 0);
			s[2] = s[1];
			s[1] = ft_strjoin(s[1], s[0]);
			free(s[0]);
			free(s[2]);
			s[0] = gnl(fd);
			i[1]++;
		}
	}
	return (finalize_map(fd, data, i, s[1]));
}
