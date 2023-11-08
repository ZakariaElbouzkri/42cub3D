/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:20:27 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/08 00:37:44 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>



void keypress(void *ptr)
{
	t_render *rend;

	rend = (t_render *)ptr;
	if (mlx_is_key_down(rend->mlx, MLX_KEY_ESCAPE))
		clear_t_render(rend, NULL);
	const int x = mlx_is_key_down(rend->mlx, MLX_KEY_A) * -SPEED + mlx_is_key_down(rend->mlx, MLX_KEY_D) * SPEED;
	const int y = mlx_is_key_down(rend->mlx, MLX_KEY_W) * -SPEED + mlx_is_key_down(rend->mlx, MLX_KEY_S) * SPEED;
	const double rot = mlx_is_key_down(rend->mlx, MLX_KEY_LEFT) * -0.05 + mlx_is_key_down(rend->mlx, MLX_KEY_RIGHT) * 0.05;
	rend->player.angle += rot;
	if (x != 0)
		rend->player.x += x;
	else if (y != 0)
	{
		rend->player.x += cos(rend->player.angle) * ((y < 0) * SPEED + (y > 0) * -SPEED);
		rend->player.y += sin(rend->player.angle) * ((y < 0) * SPEED + (y > 0) * -SPEED);
	}
	mlx_delete_image(rend->mlx, rend->image);
	rend->image = mlx_new_image(rend->mlx, rend->width, rend->height);
	mlx_image_to_window(rend->mlx, rend->image, 0, 0);
	draw_map(rend);
	// castAllRays(rend);
}

bool	load_textures(t_render *rend)
{
	int		idx;
	int		flg;


	rend->tuxtures[NO - 1] = mlx_load_png(rend->paths[NO - 1]);
	rend->tuxtures[SO - 1] = mlx_load_png(rend->paths[SO - 1]);
	rend->tuxtures[WE - 1] = mlx_load_png(rend->paths[WE - 1]);
	rend->tuxtures[EA - 1] = mlx_load_png(rend->paths[EA - 1]);
	flg = 1;
	idx = -1;
	while (++idx < 4)
	{
		free(rend->paths[idx]);
		rend->paths[idx] = NULL;
		flg *= (rend->tuxtures[idx] != NULL);
	}
	return (flg);
}

void	clear_t_render(t_render *rend, const char *err)
{
	int idx;

	idx = -1;
	while (++idx < 4)
	{
		if (rend->tuxtures[idx])
			mlx_delete_texture(rend->tuxtures[idx]);
		free(rend->paths[idx]);
	}
	free_map(rend->map);
	mlx_delete_image(rend->mlx, rend->image);
	mlx_terminate(rend->mlx);
	if (err)
		ft_puterror(1, err);
	exit(err != NULL);
}

void	init_mlx_vars(t_render *rend)
{
	rend->mlx = mlx_init(rend->width, rend->height, "CUB3D", true);
	if (!rend->mlx)
		clear_t_render(rend, mlx_strerror(mlx_errno));
	rend->image = mlx_new_image(rend->mlx, rend->width, rend->height);
	if (!rend->image || mlx_image_to_window(rend->mlx, rend->image, 0, 0) < 0)
		clear_t_render(rend, mlx_strerror(mlx_errno));
	if (!load_textures(rend))
		clear_t_render(rend, mlx_strerror(mlx_errno));
}

// ###########################################


void	render_game(t_render *render)
{
	init_mlx_vars(render);
	// //----------Drawing function----------
	draw_map(render);
	mlx_loop_hook(render->mlx, &keypress, render);
	mlx_loop(render->mlx);
	printf("Done\n");
}