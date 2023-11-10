/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:32:06 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/10 16:12:08 by zel-bouz         ###   ########.fr       */
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
	// int y;
	// int x;

	// y = -1;
	// while (render->map[++y])
	// {
	// 	x = -1;
	// 	while(render->map[y][++x])
	// 	{
	// 		if (render->map[y][x] == '1')
	// 			draw_square(render->image, x * TAIL, y * TAIL, render->colors[1]);
	// 		else if (ft_strchr("NESW0", render->map[y][x]))
	// 			draw_square(render->image, x * TAIL, y * TAIL, render->colors[0]);
	// 	}
	// }
	draw_player(render);
}

void	Point(t_render *rend, t_pos pos, int color)
{
	int i;
	int j;

	j = -2;
	while (j++ < 2)
	{
		i = -2;
		while (i++ < 2)
			mlx_put_pixel(rend->image, pos.x + i, pos.y + j, color);
	}
}

bool	check_wall(t_render *rend, t_pos pos, int h)
{
	int prx = (h == 1 && sin(pos.angle < 0)) * (-0.1);
	int pry = (h == 0 && cos(pos.angle) < 0) * (-0.1);
	if (rend->map[(int)((pos.y + pry) / TAIL)][(int)((pos.x + prx) / TAIL)] == '1' || 
	rend->map[(int)((pos.y + pry) / TAIL)][(int)((pos.x + prx) / TAIL)] == ' ')
		return (true);
	prx = 0;
	pry = 0;
	if (rend->map[(int)(floor(pos.y + pry) / TAIL)][(int)(floor(pos.x + prx) / TAIL)] == '1' || 
	rend->map[(int)(floor(pos.y + pry) / TAIL)][(int)(floor(pos.x + prx) / TAIL)] == ' ')
		return (true);
	return (false);
}

double	get_intersection_h(t_render *rend, double ray)
{
	t_pos	pos;
	t_pos	ply;

	pos.angle = ray;
	ply = rend->player;
	pos.y = floor((ply.y / TAIL)) * TAIL + (sin(ray) < 0) * (-1.0) + (sin(ray) >= 0) * TAIL;
	pos.x = ply.x + (pos.y - ply.y) / tan(ray);
	while (true)
	{
		if (pos.x < 0.0 || pos.y < 0.0 || pos.x > rend->width || pos.y > rend->height)
			return (-1);
		if (check_wall(rend, pos, 1))
			break;
		pos.y += (sin(ray) < 0) * -TAIL + (sin(ray) >= 0) * TAIL;
		pos.x += (pos.y - ply.y) / tan(ray);
	}
	// Point(rend, pos, 0xFFFF00FF);
	return (sqrt(pow(pos.x - ply.x, 2) + pow(pos.y - ply.y, 2)));
}

double	get_intersection_v(t_render *rend, double ray)
{
	t_pos	pos;
	t_pos	ply;

	ply = rend->player;
	pos.angle = ray;
	pos.x = floor((ply.x / TAIL)) * TAIL + (cos(ray) < 0) * (-1.0) + (cos(ray) >= 0) * TAIL;
	pos.y = ply.y + (pos.x - ply.x) * tan(ray);
	while (true)
	{
		if (pos.x < 0.0 || pos.y < 0.0 || pos.x > rend->width || pos.y > rend->height)
			return (-1);
		if (check_wall(rend, pos, 0))
			break;
		pos.x += (cos(ray) < 0) * -TAIL + (cos(ray) >= 0) * TAIL;
		pos.y += (pos.x - ply.x) * tan(ray);
	}
	// Point(rend, pos, 0xFF0000FF);
	return (sqrt(pow(pos.x - ply.x, 2) + pow(pos.y - ply.y, 2)));
}

double	get_closest_distance(double distance_h, double distance_v)
{
	if (distance_v == -1)
		return (distance_h);
	if (distance_h == -1)
		return (distance_v);
	return (fmin(distance_h, distance_v));
}

void	draw_wall(t_render *render, double wall_height, int x)
{
	int start_y = ((HEIGHT / 2) - wall_height / 2);
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

void	draw_ray(t_render *rend)
{
	double start_angle = rend->player.angle - (M_PI / 6);
	// double end_angle = rend->player.angle + (M_PI / 3);
	double distance;
	double wall_height;
	
	// get_intersection_v(rend, start_angle);
	int x = 0;
	while (x < WIDTH)
	{
		distance = get_closest_distance(get_intersection_v(rend, start_angle), get_intersection_h(rend, start_angle));
		wall_height = TAIL * DIST_TO_WINDOW / distance;
		draw_wall(rend, ceil(wall_height), x);
		// printf("%f\n", distance);
		x++;
		start_angle += (FOV / WIDTH);
	}
	// int	lenght;
	// double	end_x;
	// double	end_y;

	// lenght = 0;
	// end_x = rend->player.x;
	// end_y = rend->player.y;
	// while (lenght < 10)
	// {
	// 	end_x = end_x + cos(rend->player.angle);
	// 	end_y = end_y + sin(rend->player.angle);
	// 	mlx_put_pixel(rend->image, end_x, end_y, 0xFF0000FF);
	// 	lenght++;
	// }
}
void draw_player(t_render *render)
{
	// Point(render, render->player, 0xFF0000FF);
	draw_ray(render);
}
