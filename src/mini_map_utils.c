/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:29:13 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/19 16:13:54 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

size_t get_map_width(char **map_name)
{
    return (strlen(map_name[0]));
}

size_t get_map_height(char **map_name)
{
    int i;
    
    i = 0;
    while (map_name[i])
        i++;
    return (i);
}

void render_tiles(t_img_info *img, int x, int y, int color)
{
    int i[2];

    i[0] = 0;
    i[1] = 0;
    while (i[0] < TILE_SIZE)
    {
        i[1] = 0;
        while (i[1] < TILE_SIZE)
        {
            // if (i[0] == 0 || i[1] == 0 || i[0] == img->window_height || i[1] == img->window_width)
            //    ft_put_pixel(img, x + i[1], y + i[0], BLACK);
            // else
                ft_put_pixel(img, x + i[1], y + i[0], color);
            i[1]++;
        }
        i[0]++;
    }
}

void render_wall(char **map, t_img_info *img)
{
    int i[2];

    i[0] = 0;
    i[1] = 0;
    while (map[i[0]])
    {
        i[1] = 0;
        while (map[i[0]][i[1]])
        {
            if (map[i[0]][i[1]] == '1')
                render_tiles(img, i[1] * TILE_SIZE, i[0] * TILE_SIZE, 0x000000FF);
            i[1]++;
        }
        i[0]++;
    }
}

void render_floor(char **map, t_img_info *img)
{
    int i[2];

    i[0] = 0;
    i[1] = 0;
    while (map[i[0]])
    {
        i[1] = 0;
        while (map[i[0]][i[1]])
        {
            if ( map[i[0]][i[1]] == '0' || map[i[0]][i[1]] == 'N' || map[i[0]][i[1]] == 'S' ||map[i[0]][i[1]] == 'W' || map[i[0]][i[1]] == 'E')
                render_tiles(img, i[1] * TILE_SIZE, i[0] * TILE_SIZE , 0x00FFFFFF);
            i[1]++;
        }
        i[0]++;
    }
}