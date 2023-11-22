/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:32:06 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/22 09:13:17 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cast_rays(t_render *rend)
{
	double	start_angle;
	double	distance;
	double	wall_height;

	int x = 0;
	start_angle = rend->player.angle - (M_PI / 6);
	while (x < WIDTH)
	{
		distance = get_distance(rend, start_angle);
		distance = distance * cos(start_angle - rend->player.angle);
		wall_height = TAIL * DIST_TO_WINDOW / distance;
		rend->ray_angle = start_angle;
		draw_wall(rend, wall_height, x);
		x++;
		start_angle += (FOV / WIDTH);
	}
}

double	distance_horizontal(t_render *rend, double angle)
{
	t_pos	ray;
	t_pos	ply;

	ply = rend->player;
	ray.y = floor((ply.y / TAIL)) * TAIL + (sin(angle) < 0) * (-0.0000001)
		+ (sin(angle) >= 0) * TAIL;
	ray.x = ply.x + (ray.y - ply.y) / tan(angle);
	ray.ystep = (sin(angle) < 0) * -TAIL + (sin(angle) >= 0) * TAIL;
	ray.xstep = ray.ystep / tan(angle);
	while (true)
	{
		if (ray.x < 0.0 || ray.y < 0.0 || ray.x >= rend->width || ray.y >= rend->height)
			break;
		if (check_wall(rend, ray))
			break;
		ray.y += ray.ystep;
		ray.x += ray.xstep;
	}
	rend->inter.x = ray.x;
	return (sqrt(pow(ray.x - ply.x, 2) + pow(ray.y - ply.y, 2)));
}

double	distance_vertival(t_render *rend, double angle)
{
	t_pos	ray;
	t_pos	ply;

	ply = rend->player;
	ray.x = floor((ply.x / TAIL)) * TAIL + (cos(angle) < 0) * (-0.0000001)
		+ (cos(angle) >= 0) * TAIL;
	ray.y = ply.y + (ray.x - ply.x) * tan(angle);
	ray.xstep = (cos(angle) < 0) * -TAIL + (cos(angle) >= 0) * TAIL;
	ray.ystep = ray.xstep * tan(angle);
	while (true)
	{
		if (ray.x < 0.0 || ray.y < 0.0 || ray.x >= rend->width || ray.y >= rend->height)
			break;
		if (check_wall(rend, ray))
			break;
		ray.x += ray.xstep;
		ray.y += ray.ystep;
	}
	rend->inter.y = ray.y;
	return (sqrt(pow(ray.x - ply.x, 2) + pow(ray.y - ply.y, 2)));
}

void	draw_wall(t_render *render, double wall_height, int x)
{
	uint32_t	color;
	int			y;
	int			itr;

	y = ft_max(0, ((HEIGHT / 2) - (wall_height / 2)));
	itr = -1;
	while (++itr < y)
		mlx_put_pixel(render->image, x, itr, render->rgba[1].hex);
	itr = -1;
	while (++itr <= wall_height && itr < HEIGHT)
	{
		color = get_texture_color(render, wall_height, y++);
		mlx_put_pixel(render->image, x, y, color);
	}
	while (y++ < HEIGHT)
		mlx_put_pixel(render->image, x, y, render->rgba[0].hex);
}

