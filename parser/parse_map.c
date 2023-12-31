/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:35:13 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/25 03:09:03 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	serounded(char **map, int x, int y)
{
	int			n;
	const int	dx[4] = {-1, 0, 1, 0};
	const int	dy[4] = {0, 1, 0, -1};

	n = -1;
	while (++n < 4)
	{
		if (map[y + dx[n]][x + dy[n]] == ' ')
			return (false);
	}
	return (true);
}

bool	fill_player_pos(t_parse *prs, int x, int y)
{
	static int	a;

	if (a)
		return (false);
	prs->player.x = (x * TAIL) + (TAIL / 2);
	prs->player.y = (y * TAIL) + (TAIL / 2);
	prs->player.angle = (prs->map[y][x] == 'N') * N + 
		(prs->map[y][x] == 'S') * S
		+ (prs->map[y][x] == 'E') * E + (prs->map[y][x] == 'W') * W;
	return (++a);
}

bool	map_is_valid(char **map, t_parse *prs)
{
	int	x;
	int	y;

	y = 0;
	while (map[++y])
	{
		x = 0;
		while (map[y][++x])
		{
			if (ft_strchr("NESW0", map[y][x]) && !serounded(map, x, y))
				return (ft_puterror(1, "Map Not Closed"), false);
			if (ft_strchr("NSEW", map[y][x]) && !fill_player_pos(prs, x, y))
				return (ft_puterror(1, "Duplicated Player"), false);
		}
	}
	if (fill_player_pos(prs, 0, 0) == true)
		return (ft_puterror(1, "Player Not Found"), false);
	return (true);
}

char	*copy_line(char const *src, int size)
{
	char	*result;
	int		idx;

	if (!*src)
		return (ft_puterror(1, "Empty Line On Map"), NULL);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	ft_memset(result, 32, size);
	idx = 0;
	while (*src)
	{
		if (!ft_strchr("10NSEW\t\v\r\n\f\v ", *src))
			return (free(result),
				ft_puterror(1, "Invalid Item Found In Map"), NULL);
		((!ft_strchr("\t\v\r\n\f\v", *src)) && (result[++idx] = *src));
		src++;
	}
	return (result[size] = 0, result);
}

bool	parse_map(t_parse *prs)
{
	int	idx;

	while (prs->lst && ft_empty(prs->lst->data))
	{
		lst_delone(&prs->lst, prs->lst);
		prs->heigth--;
	}
	if (!prs->lst)
		return (ft_puterror(1, "Icomplete Map"), false);
	prs->map = ft_calloc(sizeof(char *), (prs->heigth + 3));
	if (!prs->map)
		return (ft_puterror(1, strerror(errno)), false);
	idx = -1;
	prs->width = max_width(prs->lst);
	prs->map[++idx] = generate_border(' ', prs->width + 2);
	while (prs->lst)
	{
		prs->map[++idx] = copy_line(prs->lst->data, prs->width + 2);
		if (prs->map[idx] == NULL)
			return (false);
		lst_delone(&prs->lst, prs->lst);
	}
	prs->map[++idx] = generate_border(' ', prs->width + 2);
	return (true);
}
