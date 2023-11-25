/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:33:38 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/25 03:10:27 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	parse_rgb(char *str, t_rgba	*rgba)
{
	char	**colors;

	if (rgba->visited)
		return (free(str), ft_puterror(1, "Duplicated RGB Color"), false);
	if (!str || !*str || !valid_rgb(str, 0))
		return (free(str), ft_puterror(1, "Invalid RGB Color"), false);
	colors = ft_split(str, ',');
	if (colors == NULL)
		return (free(str), false);
	rgba->red = ft_atoi(colors[0]);
	rgba->green = ft_atoi(colors[1]);
	rgba->blue = ft_atoi(colors[2]);
	rgba->alpha = 0xFF;
	free(str);
	free_map(colors);
	if (rgba->red > 255 || rgba->green > 255 || rgba->blue > 255)
		return (ft_puterror(1, "Invalid RGB Color"), false);
	rgba->hex = rgba->red << 24 | rgba->green << 16 | rgba->blue << 8
		| rgba->alpha;
	return ((rgba->visited = true));
}

bool	add_texture(t_parse *prs, char *temp)
{
	t_token	id;

	if (!temp[0] || !temp[1] || !temp[1])
		return (ft_puterror(1, "Invalid Identifier"), false);
	id = get_id(temp[0], temp[1], temp[2]);
	if (!id || (id < 5 && prs->textures[id - 1]))
		return (free(temp), ft_puterror(1, "Invalid Identifier"), false);
	if (id < 5)
	{
		prs->textures[id - 1] = ft_strtrim(&temp[2], "\t\v ");
		if (prs->textures[id - 1] == NULL || prs->textures[id - 1][0] == '\0')
			return (free(temp), ft_puterror(1, "Texture Path Is Empty"), false);
	}
	else if (!parse_rgb(ft_strtrim(&temp[1], "\t\v "), &prs->rgba[id - 5]))
		return (free(temp), false);
	return (true);
}

bool	parser_textures(t_parse *prs)
{
	int		number_of_textures;
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
	if (number_of_textures < 6)
		return (ft_puterror(1, "Incomplete Map File"), false);
	return (true);
}
