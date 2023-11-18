#include <cub3d.h>

unsigned int rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static unsigned int	my_pixel_put(mlx_texture_t *texture, int x, int y)
{
	unsigned int color;
	int line_len;

	line_len = texture->width * texture->bytes_per_pixel;
	uint32_t r = texture->pixels[((y * line_len + x * texture->bytes_per_pixel) + 0)];
	uint32_t g = texture->pixels[((y * line_len + x * texture->bytes_per_pixel) + 1)];
	uint32_t b = texture->pixels[((y * line_len + x * texture->bytes_per_pixel) + 2)];
	uint32_t a = texture->pixels[((y * line_len + x * texture->bytes_per_pixel) + 3)];
	color = rgba(r, g, b, a);
	return (color);
}

static unsigned int get_texture_offset(t_render *rend, double wall_height, int start_y, mlx_texture_t *texture)
{
	int texture_y;
	int texture_x = 0;
	unsigned int color;

	texture_y = (HEIGHT / 2) - (wall_height / 2);
	if (!rend->hitv)
		texture_x = fmod(rend->inter_posX * texture->width / (double)TAIL, texture->width);
		// texture_x = ((rend->inter_posX - (int)rend->inter_posX)  / TAIL) * texture->width;
		// texture_x = ((rend->inter_posX - (int)rend->inter_posX)  / (double)TAIL) * texture->width;
	else if (rend->hitv)
	{
		texture_x = fmod(rend->inter_posY * texture->width / (double)TAIL, texture->width);
		// texture_x = fmod(rend->inter_posY, TAIL);
		// texture_x = (texture_x * texture->width) / TAIL;
	}

	texture_y = (start_y - texture_y) * (texture->height / wall_height);
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
