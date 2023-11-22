/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:26:15 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/22 03:21:03 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	read_file(t_lst	**lst, int fd, int size)
{
	const char	*line = get_next_line(fd);

	if (!line)
		return (size);
	*lst = ft_calloc(sizeof(t_lst), 1);
	if (!*lst)
		return (-1);
	(*lst)->data = (char *)line;
	return (read_file(&(*lst)->next, fd, size + 1));
}

bool	parsed(char *filename, t_parse *prs)
{
	const int	fd = open(filename, O_RDONLY);

	if (fd == -1)
		return (ft_puterror(2, filename, strerror(errno)), false);
	prs->heigth = read_file(&prs->lst, fd, 0);
	if (prs->heigth == -1)
		return (ft_puterror(1, strerror(errno)), false);
	close(fd);
	if (!prs->lst)
		return (ft_puterror(1, "Empty File"), false);
	if (!parser_textures(prs) || !parse_map(prs))
		return (false);
	return (map_is_valid(prs->map, prs));
}
