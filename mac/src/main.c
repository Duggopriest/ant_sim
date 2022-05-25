/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 05:57:49 by jgobbett          #+#    #+#             */
/*   Updated: 2022/05/25 19:50:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

int	keypress(int k, t_render *r)
{
	if (k == 65307 || k == 53)
		exit(1);
	return (0);
}

void	pixel_put(t_render *r, int x, int y, int color)
{
	char	*dst;

	dst = r->addr + (y * r->line_length + x * (r->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	pixel_get(t_render *r, int x, int y)
{
	char	*dst;

	dst = r->addr + (y * r->line_length + x * (r->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	disfuse(t_render *r)
{
	int		i;
	int		j;
	int		*color;
	double	sum;

	color = malloc(sizeof(int) * 5);
	while (1)
	{
		i = 0;
		while (i < r->h - 1)
		{
			j = 0;
			while (j < r->w - 1)
			{
				color[0] = pixel_get(r, j - 1, i);
				color[1] = pixel_get(r, j + 1, i);
				color[2] = pixel_get(r, j, i + 1);
				color[3] = pixel_get(r, j, i - 1);
				color[4] = pixel_get(r, j, i);
				sum = ((color[0] + color[1] + color[2] + color[3] + color[4]) / 5);
				if (sum >= color[4])
					pixel_put(r, j, i, sum);
				j += 1;
			}
			i += 1;
		}
		//usleep(100000);
	}
}

t_ant	*spawn_ant(t_render *r, int num)
{
	int		i;
	int		j;
	t_ant	*ants;

	ants = malloc(sizeof(t_ant) * num);
	i = -1;
	while (++i < num / 2)
	{
		ants[i].x = (rand() % 950) + 10;
		ants[i].y = (rand() % 950) + 10;
		ants[i].dir = rand();
	}
	while (++i < num)
	{
		ants[i].x = 600;//(rand() % 1950) + 10;
		ants[i].y = 600;//(rand() % 1450) + 10;
		ants[i].dir = rand();
	}
	return (ants);
}

void	evap_trail(t_render *r)
{
	int	i;
	int	j;
	int	color;

	while (1)
	{
		i = -1;
		while (++i < r->h)
		{
			j = -1;
			while (++j < r->w)
			{
				color = pixel_get(r, j, i);
				if (color > 0)
					color /= 1.01;
				pixel_put(r, j, i, color);
			}
		}
		usleep(100);
	}
}

void	run_threads(t_thstr *th)
{
	int	i;

	while (th->r->loaded)
		;
	printf("%i synced\n", th->id);
	while (1)
	{
		i = -1;
		while (++i < th->num)
			run_ant(&th->ants[i], th->r);
		usleep(5000);
	}
}

void	init_threads(t_render *r)
{
	int		i;
	int		j;
	int		k;
	t_thstr	*th;

	r->loaded = 1;
	r->thread_id = malloc(sizeof(pthread_t) * r->num_threads + 2);
	i = 0;
	k = -1;
	printf("thread ");
	while (++k < r->num_threads)
	{
		j = -1;
		th = malloc(sizeof(t_thstr));
		th->num = 100;
		th->id = k;
		th->ants = &r->ants[i];
		th->r = r;
		i += th->num;
		pthread_create(&r->thread_id[k], NULL,
			(void *)run_threads, th);
		printf("%d.", k);
	}
	pthread_create(&r->thread_id[++k], NULL, (void *)evap_trail, r);
	pthread_create(&r->thread_id[++k], NULL, (void *)disfuse, r);
	printf("created\n");
	r->loaded = 0;
}

int	render_next_frame(t_render *r)
{
	// r->img = mlx_new_image(r->mlx, r->w, r->h);
	// r->addr = mlx_get_data_addr(r->img, &r->bits_per_pixel, &r->line_length, &r->endian);
	mlx_put_image_to_window(r->mlx, r->mlx_win, r->img, 0, 0);
	return (1);
}

int	main(int argc, const char **argv)
{
	t_render	*r;

	if (argc != 2)
		return (0);
	r = malloc(sizeof(t_render));
	r->num_threads = 10;
	r->ant_num = ft_atoi(argv[1]);
	r->ants = spawn_ant(r, r->ant_num);
	r->w = 1000;
	r->h = 1000;
	r->mlx = mlx_init();
	r->mlx_win = mlx_new_window(r->mlx, r->w, r->h, "ant_sim"); // uses grid to change the resolution and adds padding
	r->img = mlx_new_image(r->mlx, r->w, r->h);
	r->addr = mlx_get_data_addr(r->img, &r->bits_per_pixel, &r->line_length, &r->endian);
	init_threads(r);
	mlx_key_hook(r->mlx_win, keypress, r); // sends the key presses to the "keypress" and gives it the r struct
	mlx_loop_hook(r->mlx, render_next_frame, r); // make the game render new frames
	mlx_loop(r->mlx); // make the window stay up
}
