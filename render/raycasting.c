/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:32:06 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/21 22:51:58 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	get_distance(t_render *rend, double ray_angle) {
	double	distance_v;
	double	distance_h;

	distance_v = get_intersection_v(rend, ray_angle);
	distance_h = get_intersection_h(rend, ray_angle);
	rend->hitv = (distance_v < distance_h);
	return (fmin(distance_h, distance_v));
}

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

bool	check_wall(t_render *rend, t_pos pos)
{
	int x = (int)(pos.x / (int)TAIL);
	int y = (int)(pos.y / (int)TAIL);
	if (rend->map[y][x] == '1')
		return (true);
	return (false);
}

double	get_intersection_h(t_render *rend, double angle)
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
	rend->inter_posX = ray.x;
	return (sqrt(pow(ray.x - ply.x, 2) + pow(ray.y - ply.y, 2)));
}

double	get_intersection_v(t_render *rend, double angle)
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
	rend->inter_posY = ray.y;
	return (sqrt(pow(ray.x - ply.x, 2) + pow(ray.y - ply.y, 2)));
}

void	draw_wall(t_render *render, double wall_height, int x)
{
	unsigned int	color;
	int start_y = ((HEIGHT / 2) - (wall_height / 2));
	if (start_y < 0)
		start_y = 0;
	int colors = -1;
	while (++colors < start_y){
		mlx_put_pixel(render->image, x, colors, render->colors[1]);
	}
	int i = 0;
	color = 0xFFFF00FF;
	while (i < wall_height && i < HEIGHT)
	{
		color = get_texture_color(render, wall_height, start_y);
		mlx_put_pixel(render->image, x, start_y, color);
		start_y++;
		i++;
	}
	while (start_y++ < HEIGHT){
		mlx_put_pixel(render->image, x, start_y, render->colors[0]);
	}
}

