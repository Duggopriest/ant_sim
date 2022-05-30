/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_sim.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:29:19 by jgobbett          #+#    #+#             */
/*   Updated: 2022/05/30 12:18:05 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANT_SIM_H
# define ANT_SIM_H

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
	int			ant_num;
	int			num_threads;
	pthread_t	*thread_id;

	int			h;
	int			w;
	void		*mlx;
	void		*mlx_win;

	void		*img;
	char		*addr;
	int			endian;
	int			line_length;
	int			bits_per_pixel;

	t_ant		*ants;
	int			size;
	float		evap;
	double		angle;
	int			speed;
	double		steps;
	int			distance;
	int			ant_only;
	int			box_type;
	float		turnSpeed;

}	t_render;

int			ft_atoi(const char *str);
int			keypress(int keycode, t_render *r);
int			render_next_frame(t_render *render);
void		render_new_frame(t_render *r);
void		take_input(t_render *r);

void		disfuse(t_render *r);
void		evap_trail(t_render *r);
int			pixel_get(t_render *r, int x, int y);
void		pixel_put(t_render *r, int x, int y, int color);

void		run_threads(t_thstr *th);
void		init_threads(t_render *r);
void		run_ant(t_ant *ant, t_render *r);
int			dist(int fx, int fy, int sx, int sy);

#endif
