/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:43:00 by idryab            #+#    #+#             */
/*   Updated: 2023/11/24 05:46:52 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

uint32_t    get_color(char **map, t_mmp minimap, int x, int y)
{
	int         i;
	int         j;

	i = (minimap.start_x + x) / TAIL;
	j = (minimap.start_y + y) / TAIL;
	return ((map[j][i] == '1') * 0xFF0000FF);
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
		draw_line(rend, pos, 3, 0xFFFF00FF);
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
			if (color == 0) continue;
			mlx_put_pixel(rend->image, M_START_X + x, M_START_Y + y, color);
		}
	}
	draw_player(rend);
	t_pos	ps;

	ps.x = M_START_X;
	ps.y = M_START_Y;
	ps.angle = E;
	draw_line(rend, ps, M_WIDTH, 0);
	ps.y += M_HEIGHT;
	draw_line(rend, ps, M_HEIGHT, 0);
	ps.angle = N;
	draw_line(rend, ps, M_HEIGHT, 0);
	ps.x += M_WIDTH;
	ps.angle = N;
	draw_line(rend, ps, M_HEIGHT, 0);
}
