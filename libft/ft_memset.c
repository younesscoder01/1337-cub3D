/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:06:19 by rbenmakh          #+#    #+#             */
/*   Updated: 2023/11/21 14:06:20 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	value;

	p = (unsigned char *)b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		p[i] = value;
		i++;
	}
	return (b);
}
