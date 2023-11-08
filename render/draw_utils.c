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
	while (lenght < TAIL*4)
	{
		end_x = end_x + cos(rend->player.angle);
		end_y = end_y + sin(rend->player.angle);
		mlx_put_pixel(rend->image, end_x, end_y, 0xFF0000FF);
		lenght++;
	}
}

int check_ifa_wall(t_render *rend, double rayAngle)
{
	double yIntercept;
	double xIntercept;
	double xStep;
	double yStep;
	int check_point[2];

	//TODO: The length of the ray depands on the destence between player and a wall
	//get first intersection of Horizontal point, add the Xstep and Ystep, then check if it hits a wall
	yIntercept = find_1st_yIntercept(rend);
	xIntercept = find_1st_xIntercept(rend, rayAngle);
	yStep = TAIL;
	xStep = find_xStep(rayAngle);
	check_point[0] = floor((yIntercept + yStep) / TAIL);
	check_point[1] = floor((xIntercept + xStep)) / TAIL;
	if (rend->map[check_point[0]][check_point[1]] == '1')
	{
		// printf("It's a Wall there\n");
		return (1);
	}
	else
		printf("It's NOT a Wall there\n");
	return (0);
}

void	draw_line(t_render *rend, double rayAngle)
{
	int	lenght;
	double	end_x;
	double	end_y;

	lenght = 0;
	end_x = rend->player.x;
	end_y = rend->player.y;
	while (lenght < TAIL*4)
	{
		end_x = end_x + cos(rayAngle);
		end_y = end_y + sin(rayAngle);
		mlx_put_pixel(rend->image, end_x, end_y, 0x00FF0088);
		lenght++;
	}
}

double deg_to_red(double degree)
{
	return (degree * (M_PI/180));
}

void castAllRays(t_render *rend)
{
	int i = 0;
	double rayAngle;
	int Num_rays = rend->width/2;

	rayAngle = rend->player.angle - (deg_to_red(FOV) /2);
	// while (i < Num_rays)
	while (i < 1)
	{
		if (check_ifa_wall(rend, rayAngle) == 0)
			draw_line(rend, rayAngle);
		rayAngle += deg_to_red(FOV)/ Num_rays;
		i++;
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
	castAllRays(render);
	draw_ray(render);
}

double find_1st_yIntercept(t_render *rend)
{
	double pY;
	double yIntercept;

	pY = rend->player.y;
	yIntercept = floor(pY/TAIL) * TAIL;
	return (yIntercept);
}

double find_1st_xIntercept(t_render *rend, double rayAngle)
{
	double pY;
	double pX;
	double xIntercept;

	pY = rend->player.y;
	pX = rend->player.x;
	xIntercept = pX + (pY - find_1st_yIntercept(rend)) / tan(rayAngle);
	return (xIntercept);
}

double find_xStep(double rayAngle)
{
	return (TAIL/tan(rayAngle));
}
