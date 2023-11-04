/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:33:38 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/04 23:35:06 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_token	get_id(char c1, char c2)
{
	int ans;

	if (!ft_strchr("NSWEFC", c1) || !ft_strchr("OEA\t ", c2))
		return NON;
	if ((c1 == 'F' || c1 == 'C') && ft_strchr("\r\t\f\v ", c2))
		return ((c1 == 'F') * F + (c1 == 'C') * C);
	ans = ((c1 == 'N') * NO) + ((c1 == 'S') * SO) + 
		((c1 == 'W') * WE) + ((c1 == 'E') * EA);
	ans *= ((c1 == 'N' || c1 == 'S') * (c2 == 'O') + 
		((c1 == 'W') * ( c2 == 'E')) + ((c1 == 'E') * (c2 == 'A')));
	return (ans);
}

bool	add_texture(t_parse *prs, char *temp)
{
	t_token	id;

	id = get_id(temp[0], temp[1]);
	if (!id || (id < 5 && prs->textures[id - 1] != NULL)
		|| (id > 4 && prs->colors[id - 5] != -1))
		return (free(temp), ft_puterror(1, "Invalid identifier"), false);
	if (id < 5){
		prs->textures[id - 1] = ft_strtrim(&temp[2], "\t\v ");
		if (prs->textures[id - 1] == NULL || prs->textures[id - 1][0] == '\0')
			return (free(temp), ft_puterror(1, "Emty texture path"), false);
	}
	else if (!valid_rgb(ft_strtrim(&temp[1], "\t\v "), &prs->colors[id - 5]))
		return (free(temp), ft_puterror(1, "Invalid RGB color"), false);
	return (true);
}

bool	parser_textures(t_parse *prs)
{
	int		number_of_textures;
	// t_token	id;
	char	*temp;

	number_of_textures = 0;
	while (prs->lst && number_of_textures < 6)
	{
		temp = ft_strtrim(prs->lst->data, "\n\t ");
		lst_delone(&prs->lst, prs->lst);
		prs->heigth--;
		if ((temp && *temp) && !add_texture(prs, temp))
			return (false);
		number_of_textures += (temp && *temp);
		free(temp);
	}
	return (number_of_textures == 6);
}
