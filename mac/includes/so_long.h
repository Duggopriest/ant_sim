/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:29:19 by jgobbett          #+#    #+#             */
/*   Updated: 2022/05/26 12:21:14 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>

typedef struct s_render	t_render;

typedef struct s_ant
{
	double	x;
	double	y;
	double	dir;
}	t_ant;

typedef struct s_thstr
{
	t_render	*r;
	t_ant		*ants;
	int			num;
	int			id;
}	t_thstr;

// holds the everything so I can pass this as a semi global var
typedef struct s_render {
	int			sync;
	int			loaded;
	int			num_threads;
	pthread_t	*thread_id;
	void		*mlx;
	void		*mlx_win;
	int			h;
	int			w;
	t_ant		*ants;
	int			ant_num;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_render;

int			keypress(int keycode, t_render *r); // uses the key presses
int			render_next_frame(t_render *render); // this makes the window draw new frames you give it
void		render_new_frame(t_render *r); // this is what draws the next frame
void		run_ant(t_ant *ant, t_render *r);
int			ft_atoi(const char *str);
int			dist(int fx, int fy, int sx, int sy);
void		pixel_put(t_render *r, int x, int y, int color);
int			pixel_get(t_render *r, int x, int y);
void	run_ant(t_ant *ant, t_render *r);

#endif
