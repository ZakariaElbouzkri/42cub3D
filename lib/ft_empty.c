/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 03:08:18 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/22 09:37:53 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
