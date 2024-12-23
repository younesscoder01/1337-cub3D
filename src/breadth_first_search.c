/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:30:24 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/12/22 18:26:15 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	enqueue(t_node **queue, int x, int y)
{
	t_node	*new_t_node;

	new_t_node = malloc(sizeof(t_node));
	if (!new_t_node)
		return (1);
	new_t_node->x = x;
	new_t_node->y = y;
	if ((*queue) == NULL)
	{
		(*queue) = new_t_node;
		(*queue)->parent = 0;
		(*queue)->next = 0;
	}
	else
	{
		new_t_node->next = (*queue)->next;
		new_t_node->parent = (*queue);
		(*queue)->next = new_t_node;
	}
	return (EXIT_SUCCESS);
}

void	dequeue(t_node **list, t_node *current)
{
	t_node	*tmp;
	t_node	*previous;

	if (!list || !*list || !current)
		return ;
	if (*list == current)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		return ;
	}
	else	
	{
		previous = *list;
		while (previous->next != current && previous->next != NULL)
			previous = previous->next;
		if (previous->next == current)
			previous->next = current->next;
		else
			return ;
	}
	free(current);
	return ;
}

int	neighbors(t_node **queue, t_node *cur, t_data *d, int **vis)
{
	int	x;
	int	y;

	x = cur->x;
	y = cur->y;
	if(!x || !y || x == d->map_y -1 || y == d->map_x -1  ||d->map[x][y] == ' ')
	{
		printf("x = %d, y = %d\n", x, y);
		return(EXIT_FAILURE);
	}
	if (x + 1 <= d->map_y - 1 && (d->map[x + 1][y] != '1') && vis[x + 1][y] == 0)
		enqueue(queue, x + 1, y);
	if (x - 1 >= 0 && (d->map[x - 1][y] != '1')
		&& vis[x - 1][y] == 0)
		enqueue(queue, x - 1, y);
	if (y + 1 <= d->map_x - 1 && (d->map[x][y + 1] != '1') && vis[x][y + 1] == 0)
		enqueue(queue, x, y + 1);
	if (y - 1 >= 0 && (d->map[x][y - 1] != '1')
		&& vis[x][y - 1] == 0)
		enqueue(queue, x, y - 1);
	return (EXIT_SUCCESS);
}

int	init_row(int **arr, int i, char **map, int len_r)
{
	int	j;
	int len;
	
	j = 0;
	len = ft_strlen(map[i]); 
	(void)len;
	arr[i] = (int *)malloc(sizeof(int) * len_r);
	if (!arr[i])
	{
		//free_arr(d, (void **)arr, i, 0);
		return (1);
	}
	while (j < len_r)
	{
		// if(j > len - 1)
		// 	arr[i][j] = 5;
		// else
		arr[i][j] = 0;
		j++;
	}
	return (EXIT_SUCCESS);
}
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
void print_arr(int **arr, int max_r, int map_h)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_h)
	{
		j = 0;
		while (j < max_r)
		{
			printf("%d", arr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
//free the queue list
void free_queue(t_node *queue)
{
	t_node	*tmp;

	while (queue)
	{
		tmp = queue;
		queue = queue->next;
		free(tmp);
	}
}
int	bfs(int st_x, int st_y, t_data *d, int map_h)
{
	t_node	*queue;
	int		**arr;
	int		i;
	
	i = 0;
	arr = malloc(sizeof(int *) * (d->map_x + 1));
	if (!arr)
		return (1);
	while (i < map_h)
	{
		if (init_row(arr, i, d->map, d->map_x))
			return (1);
		i++;
	}
	arr[d->map_y] = NULL;
	queue = NULL;
	enqueue(&queue, st_x, st_y);
	while (queue)
	{
		arr[queue->x][queue->y] = 6;
		// print_arr(arr, d->map_x, map_h);
		// printf("\n\n\n");
		// sleep(1);
		if(neighbors(&queue, queue, d, arr))
		{
			free_queue(queue);
			d->check_arr = arr;
			return(EXIT_FAILURE);
		}
		dequeue(&queue, queue);
	}
	print_arr(arr, d->map_x, map_h);
	d->check_arr = arr;
	return (EXIT_SUCCESS);
}
