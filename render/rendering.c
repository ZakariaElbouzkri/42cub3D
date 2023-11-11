/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:20:27 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/11 10:53:39 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_player(t_render *rend)
{
	t_pos	player;
	double		x;
	double		y;

	player = rend->player;
	if (rend->player.xstep != 0
		&& rend->map[(int)(player.y / TAIL)][(int)((player.x + player.xstep) / TAIL)] != '1')
		player.x += player.xstep;
	else if (rend->player.ystep != 0)
	{
		x = player.x + (cos(player.angle) * player.ystep);
		y = player.y + (sin(player.angle) * player.ystep);
		if (rend->map[(int)(y / TAIL)][(int)(x / TAIL)] != '1'
			&& rend->map[(int)((y + 5.0)/ TAIL)][(int)(x / TAIL)] != '1'
			&& rend->map[(int)((y - 5.0)/ TAIL)][(int)(x / TAIL)] != '1'
			&& rend->map[(int)(y/ TAIL)][(int)((x + 5.0) / TAIL)] != '1'
			&& rend->map[(int)(y/ TAIL)][(int)((x - 5.0) / TAIL)] != '1')
		{
			player.x = x;
			player.y = y;
		}
	}
	rend->player = player;
}


void keypress(void *ptr)
{
	t_render	*rend;

	rend = (t_render *)ptr;
	if (mlx_is_key_down(rend->mlx, MLX_KEY_ESCAPE))
		clear_t_render(rend, NULL);
	rend->player.xstep = mlx_is_key_down(rend->mlx, MLX_KEY_A) * -SPEED
		+ mlx_is_key_down(rend->mlx, MLX_KEY_D) * SPEED;
	rend->player.ystep = mlx_is_key_down(rend->mlx, MLX_KEY_S) * -SPEED
		+ mlx_is_key_down(rend->mlx, MLX_KEY_W) * SPEED;
	rend->player.angle += mlx_is_key_down(rend->mlx, MLX_KEY_LEFT) * -ROT
		+ mlx_is_key_down(rend->mlx, MLX_KEY_RIGHT) * ROT;
	move_player(rend);
	cast_rays(rend);
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
	rend->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!rend->mlx)
		clear_t_render(rend, mlx_strerror(mlx_errno));
	rend->image = mlx_new_image(rend->mlx, WIDTH, HEIGHT);
	if (!rend->image || mlx_image_to_window(rend->mlx, rend->image, 0, 0) < 0)
		clear_t_render(rend, mlx_strerror(mlx_errno));
	if (!load_textures(rend))
		clear_t_render(rend, mlx_strerror(mlx_errno));
}

void	render_game(t_render *render)
{
	init_mlx_vars(render);
	cast_rays(render);
	mlx_loop_hook(render->mlx, &keypress, render);
	mlx_loop(render->mlx);
	clear_t_render(render, NULL);
}