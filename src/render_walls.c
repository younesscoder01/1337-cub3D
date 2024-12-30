/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:25:31 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/30 10:29:02 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

unsigned int darken_color(unsigned int color, double factor) 
{
    if (factor < 0.0) 
        factor = 0.0;
    if (factor > 1.0)
        return color;
    unsigned char r = (color >> 16) & 0xFF; // Extract red
    unsigned char g = (color >> 8) & 0xFF;  // Extract green
    unsigned char b = color & 0xFF;         // Extract blue

    // Apply factor and clamp to [0, 255]
    r = (unsigned char)(r * (1.0 - factor));
    g = (unsigned char)(g * (1.0 - factor));
    b = (unsigned char)(b * (1.0 - factor));

    // Combine back into ARGB format (assuming alpha remains the same)
    return (color & 0xFF000000) | (r << 16) | (g << 8) | b;
}


void render_3d_walls(t_data *data)
{
    double distanceProjPlane;
    double wallStripHeight;
    double correctDistance;
    int shade_color;
    int color;
    double alpha;

    int i;

    i = 0;
    correctDistance = 0;
    while (i < NUM_RAYS)
    {
        color = RED;
        distanceProjPlane = ((double)WINDOW_WIDTH / 2.0) / tan(deg2rad(FOV / 2));
        correctDistance = data->rays[i].distance * cos(deg2rad(data->rays[i].angle) - deg2rad(data->player.rotationAngle));

        alpha = 1.0 - (90.0 / correctDistance);
        // if (data->rays[i].wasHitVertical != 1)
        //     color = RED;
        // else 
        //     color = B_RED;
        if (data->map[(int)data->rays[i].hit_y / TILE_SIZE][(int)data->rays[i].hit_x / TILE_SIZE] == 'D')
            color = GREEN;
        shade_color = darken_color(color, alpha);
        wallStripHeight = ((double)TILE_SIZE / correctDistance) * distanceProjPlane;
        double wall_height_top = (WINDOW_HEIGHT / 2) - ((int)wallStripHeight / 2);
        //wall_height_top = wall_height_top < 0 ? 0 : wall_height_top;
        if(wall_height_top < 0)
            wall_height_top = 0;
        double wall_height_bottom = (WINDOW_HEIGHT / 2) + ((int)wallStripHeight / 2);
        //wall_height_bottom = wall_height_bottom > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_height_bottom;
        if(wall_height_bottom > WINDOW_HEIGHT)
            wall_height_bottom = WINDOW_HEIGHT;
       //calculate the offset to acess to the texture buffer
       double texture_offset_x = 0;
       double texture_offset_y = 0;
       if(data->rays[i].Was_hit_vertical)
           texture_offset_x = (int)data->rays[i].hit_y % TILE_SIZE;
       else
           texture_offset_x = (int)data->rays[i].hit_x % TILE_SIZE;

        //color the wall from wall height top to wall height bottom
       for(int j = wall_height_top; j < wall_height_bottom;j++)
       {
 
           int dst_from_top = j + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
           texture_offset_y = dst_from_top * ((double)TILE_SIZE / (double)wallStripHeight);
           //get the color based on the direction of the ray 
              if(data->rays[i].is_down && !data->rays[i].Was_hit_vertical)
              color = get_px_color(data->textures[0], texture_offset_x, texture_offset_y);
            else if (data->rays[i].is_up && !data->rays[i].Was_hit_vertical)
               color = get_px_color(data->textures[1], texture_offset_x, texture_offset_y);
            else if (data->rays[i].is_right && data->rays[i].Was_hit_vertical)
               color = get_px_color(data->textures[2], texture_offset_x, texture_offset_y);
            else if (data->rays[i].is_left && data->rays[i].Was_hit_vertical)
                color = get_px_color(data->textures[3], texture_offset_x, texture_offset_y);
            shade_color = darken_color(color, alpha);
           
           
           shade_color = darken_color(color, alpha);
           ft_put_pixel(data->game_frame, i * WALL_STRIP_WIDTH, j, shade_color);             
        }
        i++;
    }
}