/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:57:59 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/10 16:36:20 by zel-bouz         ###   ########.fr       */
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

#define TAIL 64.0
#define SPEED 4.0
#define ROT 0.02

#define N (3*M_PI_2)
#define S M_PI_2
#define W M_PI
#define E 0

#define FOV M_PI / 3

#define WIDTH  1024
#define HEIGHT 620

#define DIST_TO_WINDOW  (HEIGHT / 2) / tan(FOV/2)


typedef enum s_token{
	NON, NO, SO, WE, EA, F, C
} t_token;

typedef struct s_lst {
	char    *data;
	struct s_lst    *next;
} t_lst;

typedef struct s_pos {
	double x;
	double y;
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

typedef struct s_render {
	mlx_t		*mlx;
	mlx_image_t	*image;
	char		**map;
	char		*paths[4];
	mlx_texture_t	*tuxtures[4];
	int			colors[2];
	t_pos		player;
	int			width;
	int			height;
} t_render;

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


// rendering
void	render_game(t_render *render);



// parser utils
int	ft_max(int a, int b);
void	free_t_parse(t_parse *parse);
void	free_map(char **ptr);
int		get_max_width(t_lst *lst);
bool	ft_empty(const char *str);
void	lst_delone(t_lst **lst, t_lst *node);
void	lst_clear(t_lst **lst);
void	clear_t_render(t_render *rend, const char *err);

// rendering

void	cast_rays(t_render *rend);
bool	check_wall(t_render *rend, t_pos pos, int h);
double	get_intersection_h(t_render *rend, double ray);
double	get_intersection_v(t_render *rend, double ray);
double	get_closest_distance(double distance_h, double distance_v);
void	draw_wall(t_render *render, double wall_height, int x);


#endif
