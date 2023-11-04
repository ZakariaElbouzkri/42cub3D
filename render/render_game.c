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

void	draw_square(t_render, int x, int y)
{
	
}


void	draw_map(t_render *render)
{
	int x;
	int y;

	y = -1;
	while (render->map[++y])
	{
		x = -1;
		while (render->map[++x])
		{
			draw_square(render, x, y);
		}
	}
}

void	clear_t_render(t_render *render)
{
	
}

void	render_game(t_render *render)
{
	render->mlx = mlx_init(render->width * TAIL, render->height * TAIL, "CUB3D", false);
	if (!render)
	draw_map(render);
	mlx_loop(render->mlx);
	printf("Done\n");
}