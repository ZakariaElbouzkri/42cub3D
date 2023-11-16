/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:34:23 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/11 10:07:14 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void	free_t_parse(t_parse *parse)
{
	free(parse->textures[0]);
	free(parse->textures[1]);
	free(parse->textures[2]);
	free(parse->textures[3]);
	lst_clear(&parse->lst);
	free_map(parse->map);
}

void	free_map(char **ptr)
{
	int idx;

	idx = -1;
	while (ptr && ptr[++idx])
		free(ptr[idx]);
	free(ptr);
	ptr = NULL;
}


int	get_max_width(t_lst *lst)
{
	int max;

	max = 0;
	while (lst)
	{
		max = ft_max(max, ft_strlen(lst->data));
		lst = lst->next;
	}
	return (max);
}


bool	ft_empty(const char *str)
{
	while (*str)
	{
		if (!ft_strchr("\v\t\f\r\n ", *str))
			return (false);
		str++;
	}
	return (true);
}

void	lst_delone(t_lst **lst, t_lst *node)
{
	if (!lst || !*lst || !node)
		return ;
	if (*lst == node)
	{
		(*lst) = (*lst)->next;
		if (node->data)
			(free(node->data), node->data = NULL);
		free(node);
		return ;
	}
	lst_delone(&(*lst)->next, node);
}

void	lst_clear(t_lst **lst)
{
	t_lst	*itr;

	while (*lst)
	{
		itr = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = itr;
	}
	*lst = NULL;
}
