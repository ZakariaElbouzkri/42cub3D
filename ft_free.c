/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 03:15:45 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/25 03:12:08 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_map(char **ptr)
{
	int	idx;

	idx = -1;
	while (ptr && ptr[++idx])
	{
		free(ptr[idx]);
		ptr[idx] = NULL;
	}
	free(ptr);
	ptr = NULL;
}

void	free_t_parse(t_parse *parse)
{
	free(parse->textures[0]);
	free(parse->textures[1]);
	free(parse->textures[2]);
	free(parse->textures[3]);
	lst_clear(&parse->lst);
	free_map(parse->map);
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

void	clear_t_render(t_render *rend, const char *err)
{
	int	idx;

	idx = -1;
	while (++idx < 5)
	{
		if (rend->tuxtures[idx] && idx < 4)
			mlx_delete_texture(rend->tuxtures[idx]);
		if (rend->frames[idx] != NULL)
			mlx_delete_image(rend->mlx, rend->frames[idx]);
	}
	free_map(rend->map);
	mlx_delete_image(rend->mlx, rend->image);
	mlx_terminate(rend->mlx);
	if (err)
		ft_puterror(1, err);
	exit(err != NULL);
}
