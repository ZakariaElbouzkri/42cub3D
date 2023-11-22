/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:22:22 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/22 09:39:05 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(const char *str, const char *set)
{
	int	start;
	int	end;

	if (!str || !set)
		return (NULL);
	if (!*str)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(str) - 1;
	while (start <= end && ft_strchr(set, str[start]))
		start++;
	while (end && ft_strrchr(set, str[end]))
		end--;
	return (ft_substr(str, start, end - start + 1));
}
