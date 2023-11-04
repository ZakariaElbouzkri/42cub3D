/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:26:02 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/04 03:06:13 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}


// void	leaks(){
// 	system("leaks cub3d");
// }

int	main(int ac, char **av)
{
	t_parse	parser;

	// atexit(leaks);
	ft_memset(&parser, 0, sizeof(t_parse));
	parser.colors[0] = -1;
	parser.colors[1] = -1;
	if (ac != 2 || ft_strcmp(".cub", ft_strrchr(av[1], '.')))
	{
		ft_puterror(1, "usage: ./cub3d [path/to/map.ber]");
		return (1);
	}
	// if (!parsed(av[1], &parser))
	// 	return (free_t_parse(&parser), 1);
	// printf("\nNO: %s\n", parser.textures[NO - 1]);
	// printf("SO: %s\n", parser.textures[SO - 1]);
	// printf("WE: %s\n", parser.textures[WE - 1]);
	// printf("EA: %s\n", parser.textures[EA - 1]);
	// printf("F color: %X\n", parser.colors[F - 5]);
	// printf("C color: %X\n", parser.colors[C - 5]);
	// printf("====== Map: ======\n");
	// for (int i=0; parser.map[i]; i++){
	// 	printf("%s\n", parser.map[i]);
	// }
	free_t_parse(&parser);
	return (0);
}
