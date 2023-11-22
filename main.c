/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:26:02 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/22 04:17:17 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	pass_to_rendering(t_parse *prs)
{
	t_render	render;
	int			idx;

	ft_memset(&render, 0, sizeof(t_render));
	render.map = prs->map;
	prs->map = NULL;
	idx = -1;
	while (++idx < 4)
	{
		if (idx < 2)
			render.rgba[idx] = prs->rgba[idx];
		render.paths[idx] = prs->textures[idx];
		prs->textures[idx] = NULL;
	}
	render.player = prs->player;
	render.width = ((prs->width + 2) * TAIL);
	render.height = ((prs->heigth + 2) * TAIL);
	render_game(&render);
}

void leaks() {
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_parse	parser;

	// atexit(leaks);
	ft_memset(&parser, 0, sizeof(t_parse));
	if (ac != 2 || ft_strcmp(".cub", ft_strrchr(av[1], '.')))
		return (ft_puterror(1, "usage: ./cub3d [path/to/map.cub]"), 1);
	if (!parsed(av[1], &parser))
		return (free_t_parse(&parser), 1);
	pass_to_rendering(&parser);
	free_t_parse(&parser);
	return (0);
}
