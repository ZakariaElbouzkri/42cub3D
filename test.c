/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:32:57 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/07 22:49:14 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	"aaabbbbAAAAdsksdsdAaaaabbb" "ab"
*/

char	*trim(const char *str, const char *set)
{
	int	start;
	int	end;

	if (!str || !set)
		return (NULL);
	start = 0;
	end	  = ft_strlen(str) - 1;
	while (start <= end && ft_strchr(set, str[start]))
		start++;
	while (end && ft_strrchr(set, str[end]))
		end--;
	return (ft_substr(str, start, end - start + 1));
}


int main()
{
	char *str = ft_strtrim("\n", "\n");
	if (!*str)
		return (1);
	printf("%s", str);
	return (0);
}