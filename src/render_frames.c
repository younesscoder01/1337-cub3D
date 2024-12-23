/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:54 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/23 13:34:22 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int close_win(void *data1)
{
    t_data *data;

    data = (t_data *)data1;
    mlx_destroy_window(data->mlx, data->mlx_win);
    exit(1);
}

double normalizeAngle(double angle)
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
    return angle;
}

int set_up_animation_delay(int n_frame)
{
    if (n_frame >= 38)
        return (40000);
    else if (n_frame <= 25)
        return (80000);
    return (60000);
}

void animate_weapon_shoting(t_data *data, int end)
{
    int animation_delay;

    if (data->all_weapons[data->weapon_numb].ammo_numb == 0)
    {
        data->animate_weapon = false;
        return;
    }
    animation_delay = set_up_animation_delay(end);
    render_minimap(data);
    floor_ceiling(data->game_frame, BLUE, WHITE);
    create_frame(data, 0, 0);
    copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[data->frame_index], data->game_frame, 0, 0, data->all_weapons[data->weapon_numb].weapon[data->frame_index]->img_height, data->all_weapons[data->weapon_numb].weapon[data->frame_index]->img_width);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
    usleep(animation_delay);
    data->frame_index++;
    if (data->frame_index == end)
    {
        data->animate_weapon = false;
        if (data->all_weapons[data->weapon_numb].ammo_numb != -1)
            data->all_weapons[data->weapon_numb].ammo_numb--;
    }
    data->frame_index = data->frame_index % end;
}



int key_p(int keycode, void *data1)
{
    t_data *data;
    double moveStep;
    int check_x;
    int check_y;

    printf("keycode = %i\n", keycode);
    data = (t_data *)data1;
    if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_A)
        data->player.walkDirection = 1;
    else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_D)
        data->player.walkDirection = -1;
    else if (keycode == KEY_LEFT)
        data->player.turnDirection = -1;
    else if (keycode == KEY_RIGHT)
        data->player.turnDirection = 1;
    else if (keycode == ESC)
        exit(1);
    else if (keycode == SPACE)
    {
        data->animate_weapon = true;
        // data->frame_index = 0;
    }
    if (keycode == ZERO)
        data->weapon_numb = 0;
    else if (keycode == ONE)
        data->weapon_numb = 1;
    else if (keycode == TWO)
        data->weapon_numb = 2;
    else if (keycode == THREE)
        data->weapon_numb = 3;
    else if (keycode == FOUR)
        data->weapon_numb = 4;
    else if (keycode == R)
        data->weapon_reload = true;
    data->player.rotationAngle += data->player.turnDirection * data->player.rotationSpeed;
    data->player.rotationAngle = normalizeAngle(data->player.rotationAngle);
    moveStep = data->player.walkDirection * data->player.moveSpeed;
    if (keycode == KEY_A || keycode == KEY_D)
    {
        check_x = data->player.x - round(cos(deg2rad(data->player.rotationAngle + 90)) * moveStep);
        check_y = data->player.y - round(sin(deg2rad(data->player.rotationAngle + 90)) * moveStep);
    }
    else
    {
        check_x = data->player.x + round(cos(deg2rad(data->player.rotationAngle)) * moveStep);
        check_y = data->player.y + round(sin(deg2rad(data->player.rotationAngle)) * moveStep);
    }
    printf("walkDirection: %f\n", data->player.walkDirection);
    printf("rotationAngle: %f\n", data->player.rotationAngle);
    if (data->map[data->player.y / TILE_SIZE][check_x / TILE_SIZE] != '1')
        data->player.x = check_x;
    if (data->map[check_y / TILE_SIZE][data->player.x / TILE_SIZE] != '1')
        data->player.y = check_y;
    return 0;
}

int key_r(int keycode, void *var)
{
    t_data *data;

    data = (t_data *)var;
    if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_A)
        data->player.walkDirection = 0;
    else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_D)
        data->player.walkDirection = 0;
    else if (keycode == KEY_LEFT)
        data->player.turnDirection = 0;
    else if (keycode == KEY_RIGHT)
        data->player.turnDirection = 0;
    // else if (keycode == SPACE)
    //     data->animate_weapon = false;
    return 0;
}


unsigned int get_px_color(t_img_info *img, int x, int y)
{
    char *pxl;

    pxl = 0;
    if (x >= 0 && x < img->img_width && y >= 0 && y < img->img_height)
    {
        pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    }
    if (pxl == 0)
        return 6;
    return *(unsigned int *)pxl;
}


void copy_img(t_img_info *src, t_img_info *dest, int x, int y, int height, int width)
{
    int i;
    int j;
    int xc;

    i = 0;
    while (i < height)
    {
        j = 0;
        xc = x;
        while (j < width)
        {
            ft_put_pixel(dest, j, i, get_px_color(src, xc, y));
            xc++;
            j++;
        }
        y++;
        i++;
    }
}

void copy_img_sprite(t_img_info *src, t_img_info *dest, int x, int y, int height, int width)
{
    int i;
    int j;
    int xc;
    int color;

    i = 0;
    while (i < height)
    {
        j = 0;
        xc = x;
        while (j < width)
        {
            color = get_px_color(src, xc, y);
            if (color != 65535 && color != 592187)
                ft_put_pixel(dest, j, i, color);
            xc++;
            j++;
        }
        y++;
        i++;
    }
}

void rect(t_img_info *img, int x, int y, int width, int height, int color)
{
    int i;
    int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            ft_put_pixel(img, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void create_frame(t_data *data, int fx, int fy)
{
    fx = data->player.x - FRAME_WIDTH / 2;
    fy = data->player.y - FRAME_HEIGHT / 2;
    
    if (fx < 0)
        fx = 0;
    else if (fx > data->minimap_img->img_width)
        fx = data->minimap_img->img_width - FRAME_WIDTH;
    if (fy < 0)
        fy = 0;
    else if (fy > data->minimap_img->img_height)
        fy = data->minimap_img->img_height - FRAME_HEIGHT;
    copy_img(data->minimap_img, data->frame, fx, fy, FRAME_HEIGHT, FRAME_WIDTH);
    rect(data->frame, 0, 0, FRAME_WIDTH, 10, lfaa5ti);
    rect(data->frame, 0, 0, 10, FRAME_WIDTH, lfaa5ti);
    rect(data->frame, 0, FRAME_HEIGHT - 10, FRAME_WIDTH, 10, lfaa5ti);
    rect(data->frame, FRAME_WIDTH - 10, 0, 10, FRAME_HEIGHT, lfaa5ti);
    // printf("frame width = %i\n", FRAME_WIDTH);
    // printf("frame height = %i\n", FRAME_HEIGHT);
    copy_img(data->frame, data->game_frame, 0, 0, FRAME_HEIGHT, FRAME_WIDTH);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
}

void floor_ceiling(t_img_info *img, int color1, int color2)
{
    int i;
    int j;

    i = 0;
    while (i < img->img_height / 2)
    {
        j = 0;
        while (j < img->img_width)
        {
            ft_put_pixel(img, j, i, color1);
            j++;
        }
        i++;
    }
    while (i < img->img_height)
    {
        j = 0;
        while (j < img->img_width)
        {
            ft_put_pixel(img, j, i, color2);
            j++;
        }
        i++;
    }
}

void init_weapon_names(t_data *data)
{
    data->weapon_names = malloc(sizeof(char *) * 6);
    data->weapon_names[0] = strdup("./textures/SPAR/SPAR01.xpm");
    data->weapon_names[1] = strdup("./textures/Rapr/Rapr01.xpm");
    data->weapon_names[2] = strdup("./textures/RPG7/RPG01.xpm");
    data->weapon_names[3] = strdup("./textures/Gr/Grena01.xpm");
    data->weapon_names[4] = strdup("./textures/Baton/Baton01.xpm");
    data->weapon_names[5] = NULL;
}

void init_weapons(t_data *data)
{
    int i;
    int j;
    int k;
    char *filename;

    data->all_weapons = malloc(sizeof(t_weapons) * 4);
    data->all_weapons[0].weapon = malloc(sizeof(t_img_info *) * 38);
    data->all_weapons[0].frame_numb = 38;
    data->all_weapons[0].index_to_change = 20;
    data->all_weapons[0].shoting_end = 8;
    data->all_weapons[0].ammo_numb = 20;
    data->all_weapons[0].default_ammo = 20;
    data->all_weapons[1].weapon = malloc(sizeof(t_img_info *) * 24);
    data->all_weapons[1].frame_numb = 20;
    data->all_weapons[1].index_to_change = 20;
    data->all_weapons[1].shoting_end = 6;
    data->all_weapons[1].ammo_numb = 2;
    data->all_weapons[1].default_ammo = 2;
    data->all_weapons[2].weapon = malloc(sizeof(t_img_info *) * 45);
    data->all_weapons[2].frame_numb = 45;
    data->all_weapons[2].index_to_change = 19;
    data->all_weapons[2].shoting_end = 7;
    data->all_weapons[2].ammo_numb = 1;
    data->all_weapons[2].default_ammo = 1;
    data->all_weapons[3].weapon = malloc(sizeof(t_img_info *) * 17);
    data->all_weapons[3].frame_numb = 17;
    data->all_weapons[3].index_to_change = 19;
    data->all_weapons[3].shoting_end = 17;
    data->all_weapons[3].ammo_numb = -1;
    data->all_weapons[3].default_ammo = -1;
    data->all_weapons[4].weapon = malloc(sizeof(t_img_info *) * 8);
    data->all_weapons[4].frame_numb = 8;
    data->all_weapons[4].index_to_change = 22;
    data->all_weapons[4].shoting_end = 8;
    data->all_weapons[4].ammo_numb = -1;
    data->all_weapons[4].default_ammo = -1;
    
    i = 0;
    while(i < 5)
    {
        j = 0;
        k = 2;
        filename = strdup(data->weapon_names[i]);
        printf("filename = %s\n", filename);
        while (j < data->all_weapons[i].frame_numb)
        {
            data->all_weapons[i].weapon[j] = malloc(sizeof(t_img_info));
            data->all_weapons[i].weapon[j]->img_width = WINDOW_WIDTH;
            data->all_weapons[i].weapon[j]->img_height = WINDOW_HEIGHT;
            data->all_weapons[i].weapon[j]->img = mlx_xpm_file_to_image(data->mlx, filename, &data->all_weapons[i].weapon[j]->img_width, &data->all_weapons[i].weapon[j]->img_height);
            if (data->all_weapons[i].weapon[j]->img == NULL)
            {
                printf("error and j = %i\n", j);
                printf("filename = %s\n", filename);
                printf("data->all_weapons[%i].index_to_change = %i\n", i, data->all_weapons[i].index_to_change);
            }
            data->all_weapons[i].weapon[j]->addr = mlx_get_data_addr(data->all_weapons[i].weapon[j]->img, &data->all_weapons[i].weapon[j]->bits_per_pixel, \
                                                                    &data->all_weapons[i].weapon[j]->line_length, &data->all_weapons[i].weapon[j]->endian);
            data->all_weapons[i].weapon[j]->filename = strdup(data->weapon_names[i]);
            if (k > 9)
            {
                k = 0;
                filename[data->all_weapons[i].index_to_change] = filename[data->all_weapons[i].index_to_change] + 1;
            }
            filename[data->all_weapons[i].index_to_change + 1] = k + 48;
            j++;
            k++;
        }
        free(filename);
        i++;
    }
}

void take_weapon(t_data *data)
{
//     int w_numb;

//     w_numb = data->weapon_numb;
    if (data->all_weapons[data->weapon_numb].ammo_numb == 0 && data->weapon_numb == 2)
        copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[7], data->game_frame, 0, 0, data->all_weapons[data->weapon_numb].weapon[7]->img_height, data->all_weapons[data->weapon_numb].weapon[7]->img_width);
    else
        copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[0], data->game_frame, 0, 0, data->all_weapons[data->weapon_numb].weapon[0]->img_height, data->all_weapons[data->weapon_numb].weapon[0]->img_width);
}

void animate_weapon_reload(t_data *data, int last_end)
{
     int animation_delay;
     int end;
    // printf("ammo_numb = %i\n", data->all_weapons[data->weapon_numb].ammo_numb);
    end = data->all_weapons[data->weapon_numb].frame_numb;
    if (data->all_weapons[data->weapon_numb].ammo_numb == data->all_weapons[data->weapon_numb].default_ammo || data->all_weapons[data->weapon_numb].ammo_numb == -1)
    {
        data->weapon_reload = false;
        return;
    }
    animation_delay = set_up_animation_delay(end - last_end);
    render_minimap(data);
    floor_ceiling(data->game_frame, BLUE, WHITE);
    create_frame(data, 0, 0);
    copy_img_sprite(data->all_weapons[data->weapon_numb].weapon[data->frame_index + last_end], data->game_frame, 0, 0,\
                     data->all_weapons[data->weapon_numb].weapon[data->frame_index + last_end]->img_height, \
                    data->all_weapons[data->weapon_numb].weapon[data->frame_index + last_end]->img_width);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
    usleep(animation_delay);
    data->frame_index++;
    if (data->frame_index + last_end == end)
    {
        data->weapon_reload = false;
        // printf("ammo_numb = %i\n", data->all_weapons[data->weapon_numb].ammo_numb);
        data->all_weapons[data->weapon_numb].ammo_numb = data->all_weapons[data->weapon_numb].default_ammo;
        // printf("ammo_numb = %i\n", data->all_weapons[data->weapon_numb].ammo_numb);
        // printf("default_ammo = %i\n", data->all_weapons[data->weapon_numb].default_ammo);
        data->frame_index = 0;
    }
}


int render_bullets(t_data *data)
{
    if (data->all_weapons[data->weapon_numb].ammo_numb == 0)
        copy_img_sprite(data->no_bullet, data->game_frame, 0, 0, data->no_bullet->img_height, data->no_bullet->img_width);
    else
        copy_img_sprite(data->bullet, data->game_frame, 0, 0, data->bullet->img_height, data->bullet->img_width);
    return 0;
}

int render_next_frame(void *data1)
{
    t_data *data;

    data = (t_data *)data1;
    render_minimap(data);
    floor_ceiling(data->game_frame, BLUE, WHITE);
    create_frame(data, 0, 0);
    take_weapon(data);
    // printf("data animate weapon = %i\n", data->animate_weapon);
    if (data->animate_weapon)
        animate_weapon_shoting(data, data->all_weapons[data->weapon_numb].shoting_end);
    if (data->weapon_reload)
        animate_weapon_reload(data, data->all_weapons[data->weapon_numb].shoting_end);
    // printf("player x: %i\nplayer y: %i\n", data->player.x, data->player.y);
    render_bullets(data);
    //TODO=rays calculation

    //put the image to the window
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->game_frame->img, 0, 0);
    
    return 0;
}