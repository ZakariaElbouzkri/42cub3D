/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:15:00 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/22 09:45:13 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


uint32_t	my_pixel_put(mlx_texture_t *texture, int x, int y)
{
	t_rgba	rgba;
	int		size;
	int		idx;

	size = texture->width * texture->bytes_per_pixel;
	idx = y * size + x * texture->bytes_per_pixel;
	rgba.red = texture->pixels[idx + 0];
	rgba.green = texture->pixels[idx + 1];
	rgba.blue = texture->pixels[idx + 2];
	rgba.alpha = texture->pixels[idx + 3];
	rgba.hex = (rgba.red << 24 | rgba.green << 16 | rgba.blue << 8 | rgba.alpha);
	return (rgba.hex);
}

uint32_t get_texture_offset(t_render *rend, double wall_height, int start_y, mlx_texture_t *texture)
{
	int			texture_y;
	int			texture_x;
	uint32_t	color;

	texture_y = (HEIGHT / 2) - (wall_height / 2);
	texture_x = 0;
	if (!rend->hitv)
		texture_x = fmod(rend->inter.x * texture->width / (double)TAIL, texture->width);
	else if (rend->hitv)
		texture_x = fmod(rend->inter.y * texture->width / (double)TAIL, texture->width);
	texture_y = (start_y - texture_y) * (texture->height / wall_height);
	color = my_pixel_put(texture, texture_x, texture_y);
	return (color);
}

uint32_t	get_texture_color(t_render *rend, double wall_height, int screen_y)
{
	uint32_t	color;

	if (!rend->hitv)
	{
		if (sin(rend->ray_angle) < 0)
			color = get_texture_offset(rend, wall_height, screen_y, rend->tuxtures[NO -1]);
		else
			color = get_texture_offset(rend, wall_height, screen_y, rend->tuxtures[SO -1]);
	}
	else
	{
		if (cos(rend->ray_angle) > 0)
			color = get_texture_offset(rend, wall_height, screen_y, rend->tuxtures[EA -1]);
		else
			color = get_texture_offset(rend, wall_height, screen_y, rend->tuxtures[WE -1]);
	}
	return (color);
}
