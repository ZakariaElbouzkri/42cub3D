/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:52:07 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/25 03:19:26 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	check_collisions(char **map, double x, double y)
{
	if (map[(int)(y / TAIL)][(int)(x / TAIL)] != '1'
		&& map[(int)((y + 3.0) / TAIL)][(int)(x / TAIL)] != '1'
		&& map[(int)((y - 3.0) / TAIL)][(int)(x / TAIL)] != '1'
		&& map[(int)(y / TAIL)][(int)((x + 3.0) / TAIL)] != '1'
		&& map[(int)(y / TAIL)][(int)((x - 3.0) / TAIL)] != '1')
		return (true);
	return (false);
}

int	move_player(t_render *rend)
{
	t_pos		player;
	double		x;
	double		y;

	player = rend->player;
	if (player.xstep != 0)
	{
		x = player.x - (player.xstep * sin(player.angle));
		y = player.y + (player.xstep * cos(player.angle));
	}
	else
	{
		x = player.x + (cos(player.angle) * player.ystep);
		y = player.y + (sin(player.angle) * player.ystep);
	}
	if (check_collisions(rend->map, x, y))
	{
		player.x = x;
		player.y = y;
	}
	rend->player = player;
	return (0);
}

void	mouse_hook(t_render *rend)
{
	int	x;
	int	y;
	int	n;

	mlx_get_mouse_pos(rend->mlx, &x, &y);
	n = HALF_WIDTH - x;
	n = (n < 0) + (n > 0) * (-1);
	rend->player.angle += (((x >= HALF_WIDTH) * ROT 
				+ (x < HALF_WIDTH) * ROT)) * n;
}

void	keypress(void *ptr)
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
	((rend->player.xstep != 0 || rend->player.ystep != 0) && move_player(rend));
	if (mlx_is_mouse_down(rend->mlx, MLX_MOUSE_BUTTON_LEFT)
		|| mlx_is_key_down(rend->mlx, MLX_KEY_SPACE) || rend->state == true)
		render_frames(rend, &rend->state);
	mouse_hook(rend);
	mlx_set_mouse_pos(rend->mlx, HALF_WIDTH, HALF_HEIGHT);
	cast_rays(rend);
	draw_minimap(rend);
}
