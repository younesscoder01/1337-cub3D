/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:25:31 by ysahraou          #+#    #+#             */
/*   Updated: 2025/01/01 15:11:27 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

unsigned int darken_color(unsigned int color, double factor) 
{
    if (factor < 0.0) 
        factor = 0.0;
    if (factor > 1.0)
        return color;
    unsigned char r = (color >> 16) & 0xFF; 
    unsigned char g = (color >> 8) & 0xFF;  
    unsigned char b = color & 0xFF;         

    r = (unsigned char)(r * (1.0 - factor));
    g = (unsigned char)(g * (1.0 - factor));
    b = (unsigned char)(b * (1.0 - factor));

    return (color & 0xFF000000) | (r << 16) | (g << 8) | b;
}

double calculate_wall_strip_height(double correctDistance, double distanceProjPlane) {
    return ((double)TILE_SIZE / correctDistance) * distanceProjPlane;
}

double calculate_wall_height_top(double wallStripHeight) {
    double wall_height_top = (WINDOW_HEIGHT / 2) - ((int)wallStripHeight / 2);
    if (wall_height_top < 0)
        wall_height_top = 0;
    return wall_height_top;
}

double calculate_wall_height_bottom(double wallStripHeight) {
    double wall_height_bottom = (WINDOW_HEIGHT / 2) + ((int)wallStripHeight / 2);
    if (wall_height_bottom > WINDOW_HEIGHT)
        wall_height_bottom = WINDOW_HEIGHT;
    return wall_height_bottom;
}

int get_texture_color(t_data *data, int i, double texture_offset_x, double texture_offset_y) {
    if (data->map[(int)data->rays[i].hit_y / TILE_SIZE][(int)data->rays[i].hit_x / TILE_SIZE] == 'D')
        return get_px_color(data->door, texture_offset_x, texture_offset_y);
    else if (data->rays[i].is_down && !data->rays[i].Was_hit_vertical)
        return get_px_color(data->textures[0], texture_offset_x, texture_offset_y);
    else if (data->rays[i].is_up && !data->rays[i].Was_hit_vertical)
        return get_px_color(data->textures[1], texture_offset_x, texture_offset_y);
    else if (data->rays[i].is_right && data->rays[i].Was_hit_vertical)
        return get_px_color(data->textures[2], texture_offset_x, texture_offset_y);
    else if (data->rays[i].is_left && data->rays[i].Was_hit_vertical)
        return get_px_color(data->textures[3], texture_offset_x, texture_offset_y);
    return 0;
}

/*
    ***************DONT REMOVE THIS COMMENT***********
    0: distanceProjPlane, 
    1: wallStripHeight, 
    2: correctDistance, 
    3: alpha, 
    4: wall_height_top, 
    5: wall_height_bottom
*/ 
void texture_apply(t_data *data, double *vars, int i)
{
    int color;
    int j ;
    double texture_offset_x ;
    double texture_offset_y; 
    
    texture_offset_x = 0;
    texture_offset_y= 0;
    if (data->rays[i].Was_hit_vertical)
        texture_offset_x = (int)data->rays[i].hit_y % TILE_SIZE;
    else
        texture_offset_x = (int)data->rays[i].hit_x % TILE_SIZE;
    j = vars[4];
    while (j < vars[5]) {
        int dst_from_top = j + (vars[1] / 2) - (WINDOW_HEIGHT / 2);
        texture_offset_y = dst_from_top * ((double)TILE_SIZE / (double)vars[1]);
        color = get_texture_color(data, i, texture_offset_x, texture_offset_y);
        color = darken_color(color, vars[3]);

        ft_put_pixel(data->game_frame, i * WALL_STRIP_WIDTH, j, color);
        j++;
    }
}
void render_3d_walls(t_data *data) {
    double vars[6]; 
    int i;
    
    i = 0;
    while (i < NUM_RAYS) {
        vars[0] = ((double)WINDOW_WIDTH / 2.0) / tan(deg2rad(FOV / 2));
        vars[2] = data->rays[i].distance * cos(deg2rad(data->rays[i].angle) - deg2rad(data->player.rotationAngle));
        vars[3] = 1.0 - (125.0 / vars[2]);
        vars[1] = calculate_wall_strip_height(vars[2], vars[0]);
        vars[4] = calculate_wall_height_top(vars[1]);
        vars[5] = calculate_wall_height_bottom(vars[1]);
        texture_apply(data, vars, i);

        i++;
    }
}
