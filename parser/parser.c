/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:26:15 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/08 00:20:55 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void	read_map(t_lst **lst, int fd, int *heigth)
{
	const	char *line = get_next_line(fd);
	if (!line)
		return ;
	*lst = ft_calloc(sizeof(t_lst), 1);
	(*heigth)++;
	(*lst)->data = (char*)line;
	read_map(&(*lst)->next, fd, heigth);
}

bool	parsed(char *filename, t_parse *prs)
{
	const int fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_puterror(2, filename, strerror(errno)), false);
	read_map(&prs->lst, fd, &prs->heigth);
	close(fd);
	if (!parser_textures(prs) || !parse_map(prs))
		return (false);
	return (map_is_valid(prs->map, prs));
}

