/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:10:37 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/23 18:11:54 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void ft_put_pixel(t_img_info *img, int x, int y, int color)
{
    char *pxl;

    if (x >= 0 && x < img->img_width && y >= 0 && y < img->img_height)
    {
        pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
        *(unsigned int *)pxl = color;
    }
}

int get_player_x(char **map)
{
    int i;
    int j;
    
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' ||map[i][j] == 'W' || map[i][j] == 'E')
                return j;
            j++;
        }
        i++;
    }
    return 1;
}

int get_player_y(char **map)
{
    int i;
    int j;
    
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' ||map[i][j] == 'W' || map[i][j] == 'E')
                return i;
            j++;
        }
        i++;
    }
    return 1;
}

int get_player_angle(char **map)
{
    int i;
    int j;
    
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'W')
                return W;
            else if (map[i][j] == 'N')
                return N;
            else if (map[i][j] == 'E')
                return E;
            else if (map[i][j] == 'S')
                return S;
            j++;
        }
        i++;
    }
    return 0;
}

void p_setup(t_player *p, char **map)
{
    p->radius = RADIUS;
    p->turnDirection = 0;
    p->walkDirection = 0;
    p->rotationAngle = get_player_angle(map);
    p->moveSpeed = 6.0;
    p->rotationSpeed = ROTATION_SPEED + 5.5;
    p->x = (get_player_x(map) * TILE_SIZE) + TILE_SIZE / 2;
    p->y = (get_player_y(map) * TILE_SIZE) + TILE_SIZE / 2;
}

void draw_line(double x, double y, double x1, double y1, t_img_info *img, int color)
{
    double dx;
    double dy;
    double xinc;
    double yinc;
    double steps;
    int i = 0;

    dx = x1 - x;
    dy = y1 - y;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else 
        steps = fabs(dy);
    xinc = dx / steps;
    yinc = dy / steps;
    while (i <= steps)
    {
        ft_put_pixel(img, x, y, color);
        x += xinc;
        y += yinc;
        i++;
    }
}

double deg2rad(double x)
{
	return (x * (M_PI / 180.0));
}

void render_p(t_img_info *img, t_player *p)
{
    int d;
    double x1;
    double y1;

    d = p->radius*2;
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            if (pow(j - p->radius, 2) + pow(i - p->radius,2) <= pow(p->radius,2))
                ft_put_pixel(img, (j+p->x-p->radius)  , (i+p->y-p->radius), 0x00FF0000);
    x1 = p->x + cos(deg2rad(p->rotationAngle)) * LINE_LENGTH;
    y1 = p->y + sin(deg2rad(p->rotationAngle)) * LINE_LENGTH;
    draw_line(p->x, p->y, x1 , y1, img, 0x00FF0000);
}


void render_minimap(t_data *data)
{
    render_wall(data->map, data->minimap_img);      
    render_floor(data->map, data->minimap_img);
    render_p(data->minimap_img, &data->player);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap_img->img, 0 , 0);
}