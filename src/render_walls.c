/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:25:31 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/25 12:03:30 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

unsigned int darken_color(unsigned int color, double factor) {
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

        alpha = 1.0 - (80.0 / correctDistance);
        // if (data->rays[i].wasHitVertical != 1)
        //     color = RED;
        // else 
        //     color = B_RED;
        if (data->map[(int)data->rays[i].hit_y / TILE_SIZE][(int)data->rays[i].hit_x / TILE_SIZE] == 'D')
            color = GREEN;
        shade_color = darken_color(color, alpha);
        wallStripHeight = ((double)TILE_SIZE / correctDistance) * distanceProjPlane;
        rect(data->game_frame, i * WALL_STRIP_WIDTH, (WINDOW_HEIGHT / 2) - ((int)wallStripHeight / 2), WALL_STRIP_WIDTH, (int)wallStripHeight, shade_color);
        i++;
    }
}