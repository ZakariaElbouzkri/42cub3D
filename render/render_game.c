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


void draw_full_image(t_render *render)
{
	int y = 0;
	int x;
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
				draw_square(render->image, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}


void draw_player(t_render *render)
{
	draw_square(render->image, render->player.x, render->player.y, 0xFFFF00FF);
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

void draw_mainFunc(t_render *render)
{
	draw_player(render);
}


void update_player(t_render **rend)
{
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_W))
		(*rend)->player.y -= 1;
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_S))
		(*rend)->player.y += 1;
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_A))
		(*rend)->player.x -= 1;
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_D))
		(*rend)->player.x += 1;
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_RIGHT))
		printf("key RIGHT\n");
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_LEFT))
		printf("key LEFT\n");
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_ESCAPE))
		exit(1);
}


void keypress(void *ptr)
{
	t_render *rend;

	rend = (t_render *)ptr;
	mlx_delete_image(rend->mlx, rend->image);
	rend->image = mlx_new_image(rend->mlx, rend->width * TAIL, rend->height * TAIL);
	mlx_image_to_window(rend->mlx, rend->image, 0, 0);
	draw_full_image(rend);
	update_player(&rend);
	draw_player(rend);
}

void	render_game(t_render *render)
{
	printf("Height: %d\n", render->height*TAIL);
	printf("Width: %d\n", render->width*TAIL);

	render->player.speed = 3.0;
	render->player.rot_speed = 3 * (3.141593/180);
	render->mlx = mlx_init(render->width * TAIL, render->height * TAIL, "CUB3D", true);
	render->image = mlx_new_image(render->mlx, render->width * TAIL, render->height * TAIL);
	if (!render->image || (mlx_image_to_window(render->mlx, render->image, 0, 0) < 0))
			ft_puterror(2, "mlx_image_to_window failed");

	//----------Drawing function----------
	draw_full_image(render);
	draw_mainFunc(render);

	mlx_loop_hook(render->mlx, &keypress, render);
	display_player_info(&render->player);
	mlx_loop(render->mlx);
	printf("Done\n");
}