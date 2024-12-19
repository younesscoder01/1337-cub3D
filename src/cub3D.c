/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:25:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/19 09:55:01 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return printf("Error\n");
    else
        printf("%s\n", argv[1]);
    return (0);
}