/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:27:19 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/12/25 10:08:19 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//TODO create function that calc one ray
// void cast_ray(t_data *data, int strip, float rayangle)

int	is_wall(float x, float y, char **map, t_data *data)
{
	if(x < 0 || y < 0 || y > data->minimap_img->img_height || x > data->minimap_img->img_width)
		return(1);
	int map_grid_x;
	int map_grid_y;
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);

	return(map[map_grid_y][map_grid_x] == '1');
}
void calc_rays(t_data *data)
{
	int col_id;
	int px, py;

	bool found_vert_hit = false;
	bool found_horz_hit = false;
	float horz_wall_x, horz_wall_y;
	double ray_angle = data->player.rotationAngle - (FOV / 2.0);
	col_id = 0;
	for(; col_id < NUM_RAYS; col_id++)
	{
		px = 0;
		py = 0;
		data->rays[col_id].column_id = col_id;
		found_horz_hit = false;
		found_vert_hit = false;
		data->rays[col_id].angle = normalizeAngle(ray_angle);
		data->rays[col_id].is_down = (data->rays[col_id].angle >= 0 && data->rays[col_id].angle <= 180);
		data->rays[col_id].is_up = !data->rays[col_id].is_down;
		if((data->rays[col_id].angle > 90) && (data->rays[col_id].angle < 270))
			data->rays[col_id].is_right = 0;
		else
			data->rays[col_id].is_right = 1;
		data->rays[col_id].is_left = !data->rays[col_id].is_right;
		////////////////////////////////////////////////////////////////
		/////////////////horizontal intersection////////////////////////
		////////////////////////////////////////////////////////////////
		float xstep;
		float ystep;
		float x_intercept, y_intercept;

		y_intercept = floor(data->player.y / TILE_SIZE)* TILE_SIZE;
		y_intercept += data->rays[col_id].is_down  * TILE_SIZE;
		x_intercept = data->player.x + (y_intercept - data->player.y) / tan(deg2rad(data->rays[col_id].angle));

		ystep = TILE_SIZE;
		if(data->rays[col_id].is_up)
			ystep *= -1 ;
		xstep = TILE_SIZE / tan(deg2rad(data->rays[col_id].angle));
		if((data->rays[col_id].is_left && xstep > 0) || (data->rays[col_id].is_right && xstep < 0))
			xstep *= -1;
		float check_x, check_y;
		horz_wall_x = 0;
		horz_wall_y = 0;
		float nexthorztouchx = x_intercept;
		float nexthorztouchy = y_intercept;
		if (data->rays[col_id].is_up)
			py = 1;
		while (nexthorztouchx <= data->map_x * TILE_SIZE && nexthorztouchy <= data->map_y * TILE_SIZE && nexthorztouchx >= 0 && nexthorztouchy >= 0)
		{
			check_x = nexthorztouchx ;
			check_y = nexthorztouchy ;
			if(is_wall(check_x , check_y - py, data->map, data))
			{
				horz_wall_x = nexthorztouchx;
				horz_wall_y = nexthorztouchy;
				found_horz_hit = true;
				break;
			}
			nexthorztouchx += xstep;
			nexthorztouchy += ystep;
		}
		////////////////////////////////////////////////////////////////
		/////////////////vertical intersection////////////////////////
		////////////////////////////////////////////////////////////////
		x_intercept =  floor(data->player.x / TILE_SIZE) * TILE_SIZE;
		x_intercept += data->rays[col_id].is_right * TILE_SIZE;
		y_intercept = data->player.y + (x_intercept - data->player.x) * tan(deg2rad(data->rays[col_id].angle));

		xstep = TILE_SIZE;
		if(data->rays[col_id].is_left)
			xstep *= -1;
		ystep = TILE_SIZE * tan(deg2rad(data->rays[col_id].angle));
		if((data->rays[col_id].is_up && ystep > 0) || (data->rays[col_id].is_down && ystep < 0))
			ystep *= -1;
		long vert_wall_x, vert_wall_y;
	
		float nextverttouchx = x_intercept;
		float nextverttouchy = y_intercept;
		if (data->rays[col_id].is_left)
			px = 1;
		while (nextverttouchx < data->map_x * TILE_SIZE && nextverttouchy < data->map_y * TILE_SIZE && nextverttouchx > 0 && nextverttouchy > 0)
		{
			check_x = nextverttouchx;
			check_y = nextverttouchy; 

			if(is_wall(check_x - px, check_y , data->map, data))
			{
				vert_wall_x = check_x;
				vert_wall_y = check_y;
				found_vert_hit = true;
				break;
			}
			nextverttouchx += xstep;
			nextverttouchy += ystep;
		}
		double dst_vert;
		double dst_horz;

		dst_horz = 0;
		dst_vert = 0;
		if(found_vert_hit) 
		{
			dst_vert = calc_dist(data->player.x, vert_wall_x, data->player.y, vert_wall_y);
			dst_horz = __INT_MAX__;
		}	
		if(found_horz_hit){
			dst_horz = calc_dist(data->player.x, horz_wall_x, data->player.y, horz_wall_y);
			if(!dst_vert)
				dst_vert = __INT_MAX__;
		}
		if(found_vert_hit &&  (dst_vert < dst_horz) )
		{
			draw_line(data, data->player.x ,
			data->player.y ,
			vert_wall_x ,
			vert_wall_y );
			
			data->rays[col_id].hit_y = vert_wall_y;
			data->rays[col_id].hit_x = vert_wall_x;
			data->rays[col_id].distance = dst_vert;
		
		}
		else if(found_horz_hit && dst_horz < dst_vert)
		{
			draw_line(data, data->player.x ,
			 data->player.y ,
			 horz_wall_x ,
			 horz_wall_y )
			;
			data->rays[col_id].hit_y = horz_wall_y;
			data->rays[col_id].hit_x = horz_wall_x;
			data->rays[col_id].distance = dst_horz;
		
		}
		printf("%f\n", ray_angle);
		ray_angle += (double)FOV / data->minimap_img->img_width;
	}
}