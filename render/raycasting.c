/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:32:06 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/11 12:36:00 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	check_wall(t_render *rend, t_pos ray)
{
	int x = (int)(ray.x / TAIL);
	int y = (int)(ray.y / TAIL);
	if (rend->map[y][x] == '1')
		return (true);
	return (false);
}

double	get_intersection_h(t_render *rend, double angle)
{
	t_pos	ray;
	t_pos	ply;

	ply = rend->player;
	ray.y = floor((ply.y / TAIL)) * TAIL + (sin(angle) < 0) * (-0.0000001) + (sin(angle) >= 0) * TAIL;
	ray.x = ply.x + (ray.y - ply.y) / tan(angle);
	ray.ystep = (sin(angle) < 0) * -TAIL + (sin(angle) >= 0) * TAIL;
	ray.xstep = ray.ystep / tan(angle);
	while (true)
	{
		if (ray.x < 0.0 || ray.y < 0.0 || ray.x > rend->width || ray.y > rend->height)
			break;
		if (check_wall(rend, ray))
			break;
		ray.y += ray.ystep;
		ray.x += ray.xstep;
	}
	return (sqrt(pow(ray.x - ply.x, 2) + pow(ray.y - ply.y, 2)));
}

double	get_intersection_v(t_render *rend, double angle)
{
	t_pos	ray;
	t_pos	ply;

	ply = rend->player;
	ray.x = floor((ply.x / TAIL)) * TAIL + (cos(angle) < 0) * (-0.0000001) + (cos(angle) >= 0) * TAIL;
	ray.y = ply.y + (ray.x - ply.x) * tan(angle);
	ray.xstep = (cos(angle) < 0) * -TAIL + (cos(angle) >= 0) * TAIL;
	ray.ystep = ray.xstep * tan(angle);
	while (true)
	{
		if (ray.x < 0.0 || ray.y < 0.0 || ray.x > rend->width || ray.y > rend->height)
			break;
		if (check_wall(rend, ray))
			break;
		ray.x += ray.xstep;
		ray.y += ray.ystep;
	}
	return (sqrt(pow(ray.x - ply.x, 2) + pow(ray.y - ply.y, 2)));
}

void	draw_wall(t_render *render, double wall_height, int x)
{
	int	start_y;
	int	itr;

	start_y = ((HEIGHT / 2) - (wall_height / 2));
	start_y *= (start_y > 0);
	itr = -1;
	while (++itr < start_y)
		mlx_put_pixel(render->image, x, itr, render->colors[1]);
	itr = -1;
	while (++itr < wall_height && itr < HEIGHT)
		mlx_put_pixel(render->image, x, start_y++, convert_to_hex(200, 189, 29));
	while (start_y < HEIGHT)
		mlx_put_pixel(render->image, x, start_y++, render->colors[0]);
}

void	cast_rays(t_render *rend)
{
	double		start_angle;
	double		distance;
	double		wall_height;
	int			x;
	
	start_angle = rend->player.angle - (M_PI / 6);
	x = -1;
	while (++x < WIDTH)
	{
		distance = fmin(get_intersection_v(rend, start_angle),
			get_intersection_h(rend, start_angle));
		distance = distance * cos(start_angle - rend->player.angle);
		wall_height = TAIL * DIST_TO_WINDOW / distance;
		draw_wall(rend, wall_height, x);
		start_angle += (FOV / WIDTH);
	}
}

