#include <cub3d.h>

// void is_hith_or_hitv(t_render *rend,  double h_dist, double v_dist)
// {
// 	if (h_dist < v_dist)
// 		rend->hitv = 0;
// 	else
// 		rend->hitv = 1;
// }

static unsigned int	my_pixel_put(mlx_texture_t *texture, int x, int y)
{
	unsigned char	*buf;
	unsigned int color;
	int line_len;

	// if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	// 	return (0);
	line_len = texture->width * texture->bytes_per_pixel;
	buf = texture->pixels + (y * line_len + x * texture->bytes_per_pixel);
	color = *(unsigned int *)buf;
	return (color);
}

static unsigned int get_texture_offset(t_render *rend, double wall_height, int screen_y, mlx_texture_t *texture)
{
	int texture_y;
	int texture_x;
	unsigned int color;

	texture_y = (HEIGHT / 2) - (wall_height /2);
	if (!rend->hitv)
		texture_x = fmod(rend->inter_posX * texture->width/ TAIL, texture->width);
		// texture_x = ((rend->inter_posX - (int)rend->inter_posX)  / TAIL) * texture->width;
		// texture_x = fmod(rend->inter_posX, texture->width) * texture->width /TAIL;
		// texture_x = ((rend->inter_posX - (int)rend->inter_posX)  / (double)TAIL) * texture->width;
	else
		texture_x = fmod(rend->inter_posY * texture->width / TAIL, texture->width);
	texture_y = (screen_y - texture_y) * (texture->height / wall_height);
	color = my_pixel_put(texture, texture_x, texture_y);
	return (color);
}

unsigned int get_texture_color(t_render *rend, double wall_height, int screen_y)
{
	unsigned int color;


	color = 0xFFFF00FF;
	if (!rend->hitv)
	{
		if (sin(rend->ray_angle) < 0)
		{
			// printf("NO_RAY_ANGLE: %f\n", rend->ray_angle);
			color = get_texture_offset(rend, wall_height, screen_y, rend->tuxtures[NO -1]);
		}
		else
		{
			// printf("SO_RAY_ANGLE: %f\n", rend->ray_angle);
			color = get_texture_offset(rend, wall_height, screen_y, rend->tuxtures[SO -1]);
		}
	}
	else
	{
		if (cos(rend->ray_angle) > 0)
		{
			// printf("EA_RAY_ANGLE: %f\n", rend->ray_angle);
			color = get_texture_offset(rend, wall_height, screen_y, rend->tuxtures[EA -1]);
		}
		else
		{
			// printf("WE_RAY_ANGLE: %f\n", rend->ray_angle);
			color = get_texture_offset(rend, wall_height, screen_y, rend->tuxtures[WE -1]);
		}
	}
	return (color);
}
