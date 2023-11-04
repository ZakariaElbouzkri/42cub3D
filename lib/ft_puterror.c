/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 04:51:57 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/10/16 19:37:12 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_puterror(int n, ...)
{
	va_list	args;

	va_start(args, n);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("cub3D", 2);
	while (n--)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(va_arg(args, char *), 2);
	}
	ft_putstr_fd("\n", 2);
}
