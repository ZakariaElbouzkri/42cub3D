/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:34:23 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/22 04:25:50 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	max_width(t_lst *lst)
{
	int	max_len;

	max_len = 0;
	while (lst)
	{
		max_len = ft_max(max_len, ft_strlen(lst->data));
		lst = lst->next;
	}
	return (max_len);
}

char	*generate_border(char c, int width)
{
	char	*ans;

	ans = malloc(sizeof(char) * (width + 1));
	if (!ans)
		return (false);
	ft_memset(ans, c, width);
	return (ans[width] = 0, ans);
}

t_token	get_id(char c1, char c2, char c3)
{
	int	ans;

	if (!ft_strchr("NSWEFC", c1) || !ft_strchr("OEA\t ", c2))
		return (NON);
	if ((c1 == 'F' || c1 == 'C') && ft_strchr("\r\t\f\v ", c2))
		return ((c1 == 'F') * F + (c1 == 'C') * C);
	ans = ((c1 == 'N') * NO) + ((c1 == 'S') * SO) + 
		((c1 == 'W') * WE) + ((c1 == 'E') * EA);
	ans *= ((c1 == 'N' || c1 == 'S') * (c2 == 'O') + 
			((c1 == 'W') * (c2 == 'E')) + ((c1 == 'E') * (c2 == 'A')));
	return (ans * ft_strchr("\t\v ", c3));
}

bool	valid_rgb(char *str, int n)
{
	int	idx;

	if (!*str)
		return (n == 3);
	if (!ft_isdigit(*str))
		return (false);
	idx = 0;
	while (str[idx] && ft_isdigit(str[idx]))
		idx++;
	(str[idx] == ',' && (n < 2) && idx++);
	return (valid_rgb(&str[idx], n + 1));
}
