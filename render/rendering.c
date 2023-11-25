/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:20:27 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/25 03:22:31 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

bool	load_frames(t_render *rend)
{
	int				itr;
	mlx_texture_t	*texture;
	const char		*paths[] = {
		"./textures/frames/frame0.png",
		"./textures/frames/frame1.png",
		"./textures/frames/frame2.png",
		"./textures/frames/frame3.png",
		"./textures/frames/frame4.png"
	};

	itr = -1;
	while (++itr < 5)
	{
		texture = mlx_load_png(paths[itr]);
		if (!texture)
			return (false);
		rend->frames[itr] = mlx_texture_to_image(rend->mlx, texture);
		mlx_image_to_window(rend->mlx, rend->frames[itr], 
			FRAME_POSX, FRAME_POSY);
		rend->frames[itr]->enabled = (itr == 0);
		mlx_delete_texture(texture);
	}
	return (true);
}

void	init_mlx_vars(t_render *rend)
{
	rend->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!rend->mlx)
		clear_t_render(rend, mlx_strerror(mlx_errno));
	rend->image = mlx_new_image(rend->mlx, WIDTH, HEIGHT);
	if (!rend->image || mlx_image_to_window(rend->mlx, rend->image, 0, 0) < 0)
		clear_t_render(rend, mlx_strerror(mlx_errno));
	if (!load_textures(rend) || !load_frames(rend))
		clear_t_render(rend, mlx_strerror(mlx_errno));
}

void	render_game(t_render *render)
{
	init_mlx_vars(render);
	cast_rays(render);
	mlx_loop_hook(render->mlx, &keypress, render);
	mlx_set_cursor_mode(render->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop(render->mlx);
	clear_t_render(render, NULL);
}
