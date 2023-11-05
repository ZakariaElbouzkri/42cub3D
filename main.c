/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:26:02 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/04 23:34:05 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

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
			render.colors[idx] = prs->colors[idx];
		render.textures[idx] = prs->textures[idx];
		prs->textures[idx] = NULL;
	}
	render.player = prs->player;
	render.width = prs->width + 2;
	render.height = prs->heigth + 2;
	render_game(&render);
}

void print_map(t_parse parser)
{
	printf("NO : %s\n", parser.textures[NO - 1]);
	printf("SO : %s\n", parser.textures[SO - 1]);
	printf("WE : %s\n", parser.textures[WE - 1]);
	printf("EA : %s\n", parser.textures[EA - 1]);
	printf("Floor : 0x%X\n", parser.colors[0]);
	printf("Ceilling : 0x%X\n", parser.colors[1]);
	for (int i=0; parser.map[i]; i++)
		printf("%s\n", parser.map[i]);
}

int	main(int ac, char **av)
{
	t_parse	parser;

	ft_memset(&parser, 0, sizeof(t_parse));
	parser.colors[0] = -1;
	parser.colors[1] = -1;
	if (ac != 2 || ft_strcmp(".cub", ft_strrchr(av[1], '.')))
	{
		ft_puterror(1, "usage: ./cub3d [path/to/map.cub]");
		return (1);
	}
	if (!parsed(av[1], &parser))
		return (free_t_parse(&parser), 1);

	pass_to_rendering(&parser);
	free_t_parse(&parser);
	return (0);
}
