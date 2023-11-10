/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:32:06 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/10 18:59:18 by zel-bouz         ###   ########.fr       */
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

bool	check_wall(char **map, t_pos ray, int flg)
{
	double prx = (flg == 0 && cos(ray.angle) < 0) * (-1.0);
	double pry = (flg == 1 && sin(ray.angle) < 0) * (-1.0);
	if (map[(int)((ray.y + pry) / TAIL)][(int)((ray.x + prx) / TAIL)] == '1')
		return (true);
	// if (map[(int)((ray.y) / TAIL)][(int)((ray.x) / TAIL)] == '1')
	// 	return (true);
	return (false);
}

double	vertical_intersection(t_render *rend, t_pos *ray)
{
	t_pos	ply;

	ply = rend->player;
	while (true)
	{
		if (ray->x < 0.0 || ray->y < 0.0 || ray->y > rend->height || ray->x > rend->width)
			return (-1);
		if (check_wall(rend->map, *ray, 0))
			break;
		ray->x += (cos(ray->angle) >= 0) * TAIL + (cos(ray->angle) < 0) * -TAIL;
		ray->y += (ray->x - ply.x) * tan(ray->angle);
	}
	return (sqrt(pow(ply.x - ray->x, 2) + pow(ply.y - ray->y, 2)));
}

double	horizontal_intersection(t_render *rend, t_pos *ray)
{
	t_pos	ply;

	ply = rend->player;
	while (true)
	{
		if (ray->x < 0.0 || ray->y < 0.0 || ray->x > rend->width || ray->y > rend->height)
			break;
		if (check_wall(rend->map, *ray, 1))
			break;
		ray->y += (sin(ray->angle) < 0) * -TAIL + (sin(ray->angle) >= 0) * TAIL;
		ray->x += (ray->y - ply.y) / tan(ray->angle);
	}
	return (sqrt(pow(ray->x - ply.x, 2) + pow(ray->y - ply.y, 2)));
}

double	min(double a, double b)
{
	if (a == -1)
		return (b);
	if (b == -1)
		return (a);
	return (fmin(a, b));
}

double	cast_ray(t_render *rend, double ray_angle)
{
	t_pos	v_intsc;
	t_pos	h_intsc;
	double	v_distance = 0;
	double	h_distance = 0;

	v_intsc.angle = ray_angle;
	h_intsc.angle = ray_angle;

	v_intsc.x = floor((rend->player.x / TAIL)) * TAIL + (cos(ray_angle) >= 0) * TAIL;
	v_intsc.y = rend->player.y + (v_intsc.x - rend->player.x) * tan(ray_angle);
	
	h_intsc.y = floor((rend->player.y / TAIL)) * TAIL + (sin(ray_angle) > 0) * TAIL;
	h_intsc.x = rend->player.x + (h_intsc.y - rend->player.y) / tan(ray_angle);

	v_distance = vertical_intersection(rend, &v_intsc);
	h_distance = horizontal_intersection(rend, &h_intsc);
	if (v_distance == -1)
		mlx_put_pixel(rend->image, h_intsc.x, h_intsc.y, 0xFF0000FF);
	else if (h_distance == -1)
		mlx_put_pixel(rend->image, v_intsc.x, v_intsc.y, 0xFF0000FF);
	else if (h_distance < v_distance){
		mlx_put_pixel(rend->image, h_intsc.x, h_intsc.y, 0xFF0000FF);
	} else{
		mlx_put_pixel(rend->image, v_intsc.x, v_intsc.y, 0xFF0000FF);
	}
	return (min(v_distance, h_distance));
}

void	draw_ray(t_render *rend)
{
	double	ray_angle;
	double	wall_height;
	int		x;

	ray_angle = rend->player.angle - HALF_FOV;
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		wall_height = cast_ray(rend, ray_angle);
		ray_angle += RAY_STEP;
	}

	int	lenght;
	double	end_x;
	double	end_y;

	lenght = 0;
	end_x = rend->player.x;
	end_y = rend->player.y;
	while (lenght < 10)
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
