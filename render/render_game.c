/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:20:27 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/06 04:48:42 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void draw_square(mlx_image_t	*g_img, int x, int y, int color)
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
	// int newX;
	// int newY;

	// newY = y*TAIL;
	
	// while (newY < TAIL)
	// {
	// 	newX = x*TAIL;
	// 	while(newX < TAIL)
	// 	{
	// 			mlx_put_pixel(g_img, newX, newY, color);
	// 		newX++;
	// 	}
	// 	newY++;
	// }
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
	while (lenght < TAIL)
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

void display_player_info(t_pos *player)
{
	printf("\n----------Player_infos----------\n");
	printf("pX: %d\n", player->x);
	printf("pY: %d\n", player->y);
	printf("turDir: %d\n", player->turnDir);
	printf("walkDir: %d\n", player->walkDir);
	printf("rot_angle: %f\n", player->angle);
}

void update_player(t_render **rend)
{
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_W))
		(*rend)->player.y += sin((*rend)->player.angle) * SPEED;	
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_S))
		(*rend)->player.y -= sin((*rend)->player.angle) * SPEED;	
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_A))
		(*rend)->player.x += cos((*rend)->player.angle) * SPEED;
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_D))
		(*rend)->player.x -= cos((*rend)->player.angle) * SPEED;
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_RIGHT))
		(*rend)->player.angle += 0.05;
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_LEFT))
		(*rend)->player.angle -=  0.05;
	if (mlx_is_key_down((*rend)->mlx, MLX_KEY_ESCAPE))
		exit(1);
}


void keypress(void *ptr)
{
	t_render *rend;

	rend = (t_render *)ptr;
	if (mlx_is_key_down(rend->mlx, MLX_KEY_ESCAPE))
		exit(0);
	const int x = mlx_is_key_down(rend->mlx, MLX_KEY_A) * -SPEED + mlx_is_key_down(rend->mlx, MLX_KEY_D) * SPEED;
	const int y = mlx_is_key_down(rend->mlx, MLX_KEY_W) * -SPEED + mlx_is_key_down(rend->mlx, MLX_KEY_S) * SPEED;
	const double rot = mlx_is_key_down(rend->mlx, MLX_KEY_LEFT) * -0.05 + mlx_is_key_down(rend->mlx, MLX_KEY_RIGHT) * 0.05;
	rend->player.angle += rot;
	if (y != 0)
	{
		// if (rend->map[(rend->player.y + y) / TAIL][(rend->player.x + x) / TAIL] == '1')
		// 	return ;
		printf("X: %d Y: %d\n", x, y);
		if (y < 0)
		{
			rend->player.x += cos(rend->player.angle) * SPEED;
			rend->player.y += sin(rend->player.angle) * SPEED;
		}
		else
		{
			rend->player.x += cos(rend->player.angle) * -SPEED;
			rend->player.y += sin(rend->player.angle) * -SPEED;
		}
	}
	// mlx_delete_image(rend->mlx, rend->image);
	// rend->image = mlx_new_image(rend->mlx, rend->width * TAIL, rend->height * TAIL);
	// mlx_image_to_window(rend->mlx, rend->image, 0, 0);
	// update_player(&rend);
	draw_map(rend);
}

void	render_game(t_render *render)
{
	const int width = (render->width + 2) * TAIL;
	const int height = (render->height + 2) * TAIL;
	render->mlx = mlx_init(width, height, "CUB3D", true);
	if (render->mlx == NULL) 
		return (ft_puterror(1, mlx_strerror(mlx_errno)));
	render->image = mlx_new_image(render->mlx, width, height);
	if (!render->image || (mlx_image_to_window(render->mlx, render->image, 0, 0) < 0))
			ft_puterror(1, mlx_strerror(mlx_errno));
	//----------Drawing function----------
	draw_map(render);

	mlx_loop_hook(render->mlx, &keypress, render);
	display_player_info(&render->player);
	mlx_loop(render->mlx);
	printf("Done\n");
}