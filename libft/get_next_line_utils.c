/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:48:08 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/25 09:48:09 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, char *buffer)
{
	char	*tmp;
	int		tot;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	tot = ft_strlen(str);
	if (buffer)
		tot += ft_strlen(buffer);
	tmp = malloc(sizeof(char) * (tot + 1));
	if (!tmp)
		return (0);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	while (buffer && buffer[j])
		tmp[i++] = buffer[j++];
	tmp[i] = '\0';
	return (tmp);
}
