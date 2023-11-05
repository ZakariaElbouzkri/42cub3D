/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:20:27 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/04 03:38:33 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void draw_square(mlx_image_t	*g_img, int x, int y, int color)
{
	int xEnd = (x+1) *TAIL;
	int yEnd = (y+1) *TAIL;
	int newX;
	int newY;

	newY = y*TAIL;
	
	while (newY < yEnd)
	{
		newX = x*TAIL;
		while(newX < xEnd)
		{
				mlx_put_pixel(g_img, newX, newY, color);
			newX++;
		}
		newY++;
	}
}

// void update_func(t_render *render)
// {

// }

void draw_full_image(t_render *render)
{
	int y = 0;
	int x;
	// update_func(render);
	while (render->map[y])
	{
		x = 0;
		while(render->map[y][x])
		{
			if (render->map[y][x] == '1')
				draw_square(render->image, x , y, 0xE5FFCC);
			else if (render->map[y][x] == '0')
				draw_square(render->image, x , y, 0x000000FF);
			else if (render->map[y][x] == 'N')
				draw_square(render->image, x, y, 0xb52e31FF);
			x++;
		}
		y++;
	}
}

void display_player_info(t_pos *player)
{
	printf("\n----------Player_infos----------\n");
	printf("pX: %d\n", player->x);
	printf("pY: %d\n", player->y);
	printf("turDir: %d\n", player->turnDir);
	printf("walkDir: %d\n", player->walkDir);
	printf("rot_angle: %f\n", player->angle);
	printf("speed: %f\n", player->speed);
	printf("rot_speed: %f\n", player->rot_speed);
}

void	render_game(t_render *render)
{
	printf("Height: %d\n", render->height);
	printf("Width: %d\n", render->width);

	render->player.speed = 3.0;
	render->player.rot_speed = 3 * (3.141593/180);
	render->mlx = mlx_init(render->width * TAIL, render->height * TAIL, "CUB3D", true);
	render->image = mlx_new_image(render->mlx, render->width * TAIL, render->height * TAIL);
	if (!render->image || (mlx_image_to_window(render->mlx, render->image, 0, 0) < 0))
			ft_puterror(2, "mlx_image_to_window failed");
	draw_full_image(render);

	
	display_player_info(&render->player);
	mlx_loop(render->mlx);
	printf("Done\n");
}