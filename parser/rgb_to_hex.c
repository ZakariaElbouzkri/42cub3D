/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:52:44 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/04 22:25:26 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


static bool check_color(char **rgb2)
{
	int i;
	int j;

	if (rgb2[3] != NULL)
		return (false);
	i = -1;
	while(rgb2[++i])
	{
		j = -1;
		while(rgb2[i][++j])
		{
			if (!ft_isdigit(rgb2[i][j]))
				return (false);
		}
		if (ft_atoi(rgb2[i]) > 255 || ft_atoi(rgb2[i]) < 0)
			return (false);
	}
	return (true);
}

static bool valid(char *str)
{
	int i = 0;
	int flag = 0;
	
	while(str[i])
	{
		(str[i] == ',' && flag++);
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (false);
		i++;
	}
	return (flag == 2);
}
static int convert_to_hex(int r, int g, int b)
{
	return ((r & 255) << 16) + ((g & 255) << 8) + (b & 255);
}

bool	valid_rgb(char *str, int *color)
{
	char **rgb2;

	if (!str || !*str || !valid(str))
		return (free(str), false);
	rgb2 = ft_split(str, ',');
	free(str);
	if (!check_color(rgb2))
		return (free_map(rgb2), false);	
	*color = convert_to_hex(ft_atoi(rgb2[0]), ft_atoi(rgb2[1]),ft_atoi(rgb2[2]));
	return (free_map(rgb2), true);
}
