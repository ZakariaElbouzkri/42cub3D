/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:32:06 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/07 21:51:49 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_square(mlx_image_t	*g_img, int x, int y, int color)
{
	int i;
	int j;

	j = -1;
	while (++j < TAIL)
	{
		i = -1;
		while (++i < TAIL)
			mlx_put_pixel(g_img, x + i, y + j, color);
	}
}

void draw_map(t_render *render)
{
	int y;
	int x;

	y = -1;
	while (render->map[++y])
	{
		x = -1;
		while(render->map[y][++x])
		{
			if (render->map[y][x] == '1')
				draw_square(render->image, x * TAIL, y * TAIL, render->colors[1]);
			else if (ft_strchr("NESW0", render->map[y][x]))
				draw_square(render->image, x * TAIL, y * TAIL, render->colors[0]);
		}
	}
	draw_player(render);
}

void	draw_ray(t_render *rend)
{
	int	lenght;
	double	end_x;
	double	end_y;

	lenght = 0;
	end_x = rend->player.x;
	end_y = rend->player.y;
	while (lenght < TAIL)
	{
		end_x = end_x + cos(rend->player.angle);
		end_y = end_y + sin(rend->player.angle);
		mlx_put_pixel(rend->image, end_x, end_y, 0xFF0000FF);
		lenght++;
	}
}
void draw_player(t_render *render)
{
	int i;
	int j;

	j = -2;
	while (j++ < 2)
	{
		i = -2;
		while (i++ < 2)
			mlx_put_pixel(render->image,render->player.x + i, render->player.y + j, 0xFF0000FF);
	}
	draw_ray(render);
}
