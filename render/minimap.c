/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:43:00 by idryab            #+#    #+#             */
/*   Updated: 2023/11/23 06:25:48 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


// void draw_player(t_render *rend, t_mmp *minimp)
// {
	
// 	int i;
// 	int j;
//     int drawY;
//     int drawX;
	
//     drawY = HEIGHT - 210;
//     drawX = WIDTH + 10;
//     minimp->player_size = TAIL/6;
// 	i = 0;
// 	while (i < minimp->player_size)
// 	{
// 		j = -1;
// 		while (++j < minimp->player_size)
//             mlx_put_pixel(rend->image, j + drawX + minimp->radius - minimp->player_size/2, i + drawY + minimp->radius - minimp->player_size/2, 0xFFFF00FF);
// 		i++;
// 	}
// }

// void drawmm(t_render *rend, t_mmp *minimp, int olddrawX, int olddrawY)
// {
//     int drawY;
//     int drawX;
//     int checkY;
//     int checkX;

//     drawY = HEIGHT - 210;
//     drawX = WIDTH + 10;
//     checkY = minimp->start_y / (int)TAIL;
//     checkX = minimp->start_x / (int)TAIL;
//     if (rend->map[checkY][checkX] == '1')
//         mlx_put_pixel(rend->image, drawX+olddrawX, drawY+olddrawY, 0x00FFFFFF);
//     else
//         mlx_put_pixel(rend->image, drawX+olddrawX, drawY+olddrawY, 0xEFCF0011);
// }

// void    draw_minimap(t_render *rend)
// {
//     t_mmp minimp;
//     int i = 0;
//     int j;

//     minimp.radius  = 70;
//     minimp.start_y = rend->player.y - minimp.radius;
//     minimp.end_y = rend->player.y + minimp.radius;
//     minimp.end_x = rend->player.x + minimp.radius;
//     while(minimp.start_y < minimp.end_y)
//     {
//         minimp.start_x = rend->player.x - minimp.radius;
//         j = 0;
//         while (minimp.start_x < minimp.end_x)
//         {
//             drawmm(rend, &minimp, j, i);
//             minimp.start_x++;
//             j++;
//         }
//         minimp.start_y++;
//         i++;
//     }
//     draw_player(rend, &minimp);
// }

uint32_t    get_color(char **map, t_mmp minimap, int x, int y)
{
	int         i;
	int         j;
	int			is_wall;

	i = (minimap.start_x + x) / TAIL;
	j = (minimap.start_y + y) / TAIL;
	is_wall = (map[j][i] == '1');
	return (is_wall * 0x00000000 + (!is_wall) *  0xb0e0e6FF);
}

void	draw_line(t_render *rend, t_pos pos, int length, uint32_t color)
{
	int	itr;

	itr = -1;
	while (++itr < length)
	{
		pos.x += cos(pos.angle);
		pos.y += sin(pos.angle);
		mlx_put_pixel(rend->image, pos.x, pos.y, color);
	}
}

void    draw_player(t_render *rend)
{
	t_pos	pos;

	pos.angle = 0;
	pos.x = M_PLAYER_X;
	pos.y = M_PLAYER_Y;
	while (pos.angle < (2 * M_PI))
	{
		draw_line(rend, pos, 2, 0xFFFF00FF);
		pos.angle += (M_PI / 180);
	}
	pos.angle = rend->player.angle;
	draw_line(rend, pos, 10, 0xFFFF00FF);
}

void    draw_minimap(t_render *rend)
{
	t_mmp   minimap;
	uint32_t   color;
	int     y;
	int     x;

	minimap.start_y = rend->player.y - M_HALF_H;
	minimap.start_x = rend->player.x - M_HALF_W;
	y = -1;
	while (++y < M_HEIGHT)
	{
		x = -1;
		while (++x < M_WIDTH)
		{
			color = get_color(rend->map, minimap, x, y);
			mlx_put_pixel(rend->image, M_START_X + x, M_START_Y + y, color);
		}
	}
	draw_player(rend);

}
