/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:56:09 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/25 03:29:19 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	check_wall(t_render *rend, t_pos pos)
{
	int	x;
	int	y;

	x = (int)(pos.x / (int)TAIL);
	y = (int)(pos.y / (int)TAIL);
	if (rend->map[y][x] == '1')
		return (true);
	return (false);
}

double	get_distance(t_render *rend, double ray_angle)
{
	double	distance_v;
	double	distance_h;

	distance_v = distance_vertival(rend, ray_angle);
	distance_h = distance_horizontal(rend, ray_angle);
	rend->hitv = (distance_v < distance_h);
	return (fmin(distance_h, distance_v));
}

uint32_t	rgba_to_hex(t_rgba rgba)
{
	return (rgba.red << 24 | rgba.green << 16 | rgba.blue << 8 | rgba.alpha);
}
