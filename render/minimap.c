/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:43:00 by idryab            #+#    #+#             */
/*   Updated: 2023/11/23 00:36:44 by idryab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void draw_player(t_render *rend, t_mmp *minimp)
{
	int i;
	int j;
    int drawY;
    int drawX;
    
    drawY = HEIGHT - 210;
    drawX = WIDTH + 10;
    minimp->player_size = TAIL/6;
	i = 0;
	while (i < minimp->player_size)
	{
		j = -1;
		while (++j < minimp->player_size)
            mlx_put_pixel(rend->image, j + drawX + minimp->radius - minimp->player_size/2, i + drawY + minimp->radius - minimp->player_size/2, 0xFFFF00FF);
		i++;
	}
}

static void drawmm(t_render *rend, t_mmp *minimp, int olddrawX, int olddrawY)
{
    int drawY;
    int drawX;
    int checkY;
    int checkX;

    drawY = HEIGHT - 210;
    drawX = WIDTH + 10;
    checkY = minimp->start_y / (int)TAIL;
    checkX = minimp->start_x / (int)TAIL;
    if (rend->map[checkY][checkX] == '1')
        mlx_put_pixel(rend->image, drawX+olddrawX, drawY+olddrawY, 0x00FFFFFF);
    else
        mlx_put_pixel(rend->image, drawX+olddrawX, drawY+olddrawY, 0xEFCF0011);
}

void    draw_minimap(t_render *rend)
{
    t_mmp minimp;
    int i = 0;
    int j;

    minimp.radius  = 90;
    minimp.start_y = rend->player.y - minimp.radius;
    minimp.end_y = rend->player.y + minimp.radius;
    minimp.end_x = rend->player.x + minimp.radius;
    while(minimp.start_y < minimp.end_y)
    {
        minimp.start_x = rend->player.x - minimp.radius;
        j = 0;
        while (minimp.start_x < minimp.end_x)
        {
            drawmm(rend, &minimp, j, i);
            minimp.start_x++;
            j++;
        }
        minimp.start_y++;
        i++;
    }
    draw_player(rend, &minimp);
}
