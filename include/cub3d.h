/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:57:59 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/25 03:37:16 by zel-bouz         ###   ########.fr       */
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
# include <defines.h>

typedef struct s_minimap
{
	int	start_y;
	int	start_x;
}	t_mmp;

typedef struct s_rgba
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	alpha;
	uint32_t	hex;
	bool		visited;
}	t_rgba;

typedef enum s_token
{
	NON,
	NO,
	SO,
	WE,
	EA,
	F,
	C
}	t_token;

typedef struct s_lst
{
	char			*data;
	struct s_lst	*next;
}	t_lst;

typedef struct s_pos
{
	double	x;
	double	y;
	double	xstep;
	double	ystep;
	double	angle;
}	t_pos;

typedef struct s_parse
{
	t_lst	*lst;
	char	**map;
	char	*textures[4];
	t_rgba	rgba[2];
	int		heigth;
	int		width;
	t_pos	player;
}	t_parse;

typedef struct s_render
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	char			**map;
	char			*paths[4];
	mlx_texture_t	*tuxtures[4];
	t_rgba			rgba[2];
	t_pos			player;
	mlx_image_t		*frames[5];
	t_pos			inter;
	int				width;
	int				height;
	int				hitv;
	double			ray_angle;
	int				state;
}	t_render;

bool		parsed(char *filename, t_parse *prs);
bool		map_is_valid(char **map, t_parse *prs);
char		*generate_border(char c, int width);
char		*copy_line(char const *src, int size);
bool		parse_map(t_parse *prs);
t_token		get_id(char c1, char c2, char c3);
bool		parser_textures(t_parse *prs);
void		render_game(t_render *render);
uint32_t	rgba_to_hex(t_rgba rgba);
void		keypress(void *ptr);
bool		valid_rgb(char *str, int n);
void		free_t_parse(t_parse *parse);
void		free_map(char **ptr);
int			max_width(t_lst *lst);
void		lst_delone(t_lst **lst, t_lst *node);
void		lst_clear(t_lst **lst);
void		clear_t_render(t_render *rend, const char *err);
void		render_frames(t_render *rend, int *state);
void		cast_rays(t_render *rend);
void		draw_minimap(t_render *rend);
bool		check_wall(t_render *rend, t_pos pos);
double		distance_horizontal(t_render *rend, double ray);
double		distance_vertival(t_render *rend, double ray);
void		draw_wall(t_render *render, double wall_height, int x);
double		get_distance(t_render *rend, double ray_angle);
uint32_t	get_texture_color(t_render *rend, double wall_height, int screen_y);

#endif
