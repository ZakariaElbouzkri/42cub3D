/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:31:29 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/25 03:47:27 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <math.h>

# define TAIL 64
# define SPEED 6.0
# define ROT 0.05

# define N -M_PI_2
# define S M_PI_2
# define W M_PI
# define E 0.0

# define FOV M_PI_4

# define WIDTH  1240
# define HEIGHT 1024

# define HALF_WIDTH WIDTH / 2
# define HALF_HEIGHT HEIGHT / 2

# define M_START_X 10
# define M_START_Y 10
# define M_WIDTH 200
# define M_HEIGHT 200
# define M_HALF_W M_WIDTH / 2
# define M_HALF_H M_HEIGHT / 2
# define M_PLAYER_X M_START_X + M_HALF_W
# define M_PLAYER_Y M_START_Y + M_HALF_H

# define FRAME_POSX HALF_WIDTH - 180
# define FRAME_POSY HEIGHT - 180

# define DIST_TO_WINDOW  (HEIGHT / 2) / tan(FOV / 2)

#endif
