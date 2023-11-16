/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:32:06 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/10 22:07:50 by zel-bouz         ###   ########.fr       */
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
		is_hith_or_hitv(rend, get_intersection_h(rend, start_angle), get_intersection_v(rend, start_angle));
		distance = distance * cos(start_angle - rend->player.angle);
		wall_height = TAIL * DIST_TO_WINDOW / distance;
		draw_wall(rend, wall_height, x);
		x++;
		start_angle += (FOV / WIDTH);
	}
}

bool	check_wall(t_render *rend, t_pos pos)
{
	int x = (int)(pos.x / TAIL);
	int y = (int)(pos.y / TAIL);
	if (rend->map[y][x] == '1')
		return (true);
	return (false);
}

double	get_intersection_h(t_render *rend, double ray)
{
	t_pos	pos;
	t_pos	ply;

	pos.angle = ray;
	ply = rend->player;
	pos.y = floor((ply.y / TAIL)) * TAIL + (sin(ray) < 0) * (-0.0000001) + (sin(ray) >= 0) * TAIL;
	pos.x = ply.x + (pos.y - ply.y) / tan(ray);

	double ystep = (sin(ray) < 0) * -TAIL + (sin(ray) >= 0) * TAIL;
	double xstep = ystep / tan(ray);
	while (true)
	{
		if (pos.x < 0.0 || pos.y < 0.0 || pos.x > rend->width || pos.y > rend->height)
			break;
		if (check_wall(rend, pos))
		{
			rend->inter_posX = pos.x;
			rend->inter_posY = pos.y;
			break;
		}
		pos.y += ystep;
		pos.x += xstep;
	}
	return (sqrt(pow(pos.x - ply.x, 2) + pow(pos.y - ply.y, 2)));
}

double	get_intersection_v(t_render *rend, double ray)
{
	t_pos	pos;
	t_pos	ply;

	ply = rend->player;
	pos.angle = ray;
	pos.x = floor((ply.x / TAIL)) * TAIL + (cos(ray) < 0) * (-0.0000001) + (cos(ray) >= 0) * TAIL;
	pos.y = ply.y + (pos.x - ply.x) * tan(ray);
	double xstep = (cos(ray) < 0) * -TAIL + (cos(ray) >= 0) * TAIL;
	double ystep = xstep * tan(ray);
	while (true)
	{
		if (pos.x < 0.0 || pos.y < 0.0 || pos.x > rend->width || pos.y > rend->height)
			break;
		if (check_wall(rend, pos))
		{
			rend->inter_posX = pos.x;
			rend->inter_posY = pos.y;
			break;
		}
		pos.x += xstep;
		pos.y += ystep;
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
	unsigned int color;
	int start_y = ((HEIGHT / 2) - (wall_height / 2));
	if (start_y < 0)
		start_y = 0;
	int colors = -1;
	while (++colors < start_y){
		mlx_put_pixel(render->image, x, colors, render->colors[0]);
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
		mlx_put_pixel(render->image, x, start_y, render->colors[1]);
	}
}

