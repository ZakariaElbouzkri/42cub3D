/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:57:59 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/03 22:44:31 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdint.h>
# include <libft.h>
# include <errno.h>
# include <math.h>
# include <MLX42.h>

typedef enum s_token{
	NON, NO, SO, WE, EA, F, C
} t_token;

typedef struct s_lst {
	char    *data;
	struct s_lst    *next;
} t_lst;


typedef struct s_pos {
	int x;
	int y;
	double angle;
}	t_pos;

typedef struct s_parse {
	t_lst    *lst;
	char    **map;
	char    *textures[4];
	int     colors[2];
	int		heigth;
	int		width;
	t_pos	player;
}   t_parse;


// parser functions
bool	parsed(char *filename, t_parse *prs);
void	read_map(t_lst **lst, int fd, int *heigth);

bool	map_is_valid(char **map, t_parse *prs);
char	*generate_border(char c, int width);
char	*copy_line(char const *src, int size);
bool	parse_map(t_parse *prs);

bool	valid_rgb(char *str, int *color);
t_token	get_id(char c1, char c2);
bool	parser_textures(t_parse *prs);


// parser utils
int	ft_max(int a, int b);
void	free_t_parse(t_parse *parse);
void	free_map(char **ptr);
int	get_max_width(t_lst *lst);
bool	ft_empty(char *str);
void	lst_delone(t_lst **lst, t_lst *node);
void	lst_clear(t_lst **lst);



#endif
