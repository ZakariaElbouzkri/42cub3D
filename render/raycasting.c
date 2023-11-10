/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:32:06 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/10 16:46:11 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cast_rays(t_render *rend)
{
	double start_angle = rend->player.angle - (M_PI / 6);
	double distance;
	double wall_height;

	int x = 0;
	while (x < WIDTH)
	{
		distance = get_closest_distance(get_intersection_v(rend, start_angle),
			get_intersection_h(rend, start_angle));
		wall_height = TAIL * DIST_TO_WINDOW / distance;
		draw_wall(rend, wall_height, x);
		x++;
		start_angle += (FOV / WIDTH);
	}
}

bool	check_wall(t_render *rend, t_pos pos, int h)
{
	double pry = (h == 1 && sin(pos.angle) < 0) * (-1);
	double prx = (h != 1 && cos(pos.angle) < 0) * (-1);
	if (rend->map[(int)((pos.y + pry) / TAIL)][(int)((pos.x + prx) / TAIL)] == '1'
		|| rend->map[(int)((pos.y + pry) / TAIL)][(int)((pos.x + prx) / TAIL)] == ' ')
		return (true);
	if (rend->map[(int)((pos.y + pry) / TAIL)][(int)((pos.x + prx) / TAIL)] == '1'
		|| rend->map[(int)((pos.y + pry) / TAIL)][(int)((pos.x + prx) / TAIL)] == '1')
		return (true);
	return (false);
}

double	get_intersection_h(t_render *rend, double ray)
{
	t_pos	pos;
	t_pos	ply;

	pos.angle = ray;
	ply = rend->player;
	pos.y = floor((ply.y / TAIL)) * TAIL + (sin(ray) < 0) * (0.0) + (sin(ray) >= 0) * TAIL;
	pos.x = ply.x + (pos.y - ply.y) / tan(ray);
	while (true)
	{
		if (pos.x < 0.0 || pos.y < 0.0 || pos.x > rend->width || pos.y > rend->height)
			return (-1.0);
		if (check_wall(rend, pos, 1))
			break;
		pos.y += (sin(ray) < 0) * -TAIL + (sin(ray) >= 0) * TAIL;
		pos.x += (pos.y - ply.y) / tan(ray);
	}
	return (sqrt(pow(pos.x - ply.x, 2) + pow(pos.y - ply.y, 2)));
}

double	get_intersection_v(t_render *rend, double ray)
{
	t_pos	pos;
	t_pos	ply;

	ply = rend->player;
	pos.angle = ray;
	pos.x = floor((ply.x / TAIL)) * TAIL + (cos(ray) < 0) * (0.0) + (cos(ray) >= 0) * TAIL;
	pos.y = ply.y + (pos.x - ply.x) * tan(ray);
	while (true)
	{
		if (pos.x < 0.0 || pos.y < 0.0 || pos.x > rend->width || pos.y > rend->height)
			return (-1.0);
		if (check_wall(rend, pos, 0))
			break;
		pos.x += (cos(ray) < 0) * -TAIL + (cos(ray) >= 0) * TAIL;
		pos.y += (pos.x - ply.x) * tan(ray);
	}
	return (sqrt(pow(pos.x - ply.x, 2) + pow(pos.y - ply.y, 2)));
}

double	get_closest_distance(double distance_h, double distance_v)
{
	if (distance_v == -1.0)
		return (distance_h);
	if (distance_h == -1.0)
		return (distance_v);
	return (fmin(distance_h, distance_v));
}

void	draw_wall(t_render *render, double wall_height, int x)
{
	int start_y = ((HEIGHT / 2) - (wall_height / 2));
	if (start_y < 0)
		start_y = 0;
	int i = 0;
	while (i < wall_height && i < HEIGHT)
	{
		mlx_put_pixel(render->image, x, start_y, 0xFFFF00FF);
		start_y++;
		i++;
	}
}

