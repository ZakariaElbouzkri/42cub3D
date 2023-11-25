/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:18:02 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/25 03:19:51 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_nex_frame(int *state)
{
	static int	a;
	static int	idx;

	if (idx == 4)
		*state = false;
	if (a < 3)
		return (++a, idx);
	idx = ((idx + 1) % 5);
	*state = true;
	return (a = 0, idx);
}

void	render_frames(t_render *rend, int *state)
{
	int	itr;

	itr = -1;
	while (++itr < 5)
		rend->frames[itr]->enabled = false;
	itr = get_nex_frame(state);
	rend->frames[itr]->enabled = true;
}
