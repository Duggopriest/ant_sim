#include "mlx.h"
#include "ant_sim.h"

int	keypress(int k, t_render *r)
{
	if (k == 65307 || k == 53)
		exit(1);
	return (0);
}

t_ant	*spawn_ant(t_render *r, int num)
{
	int		i;
	int		j;
	t_ant	*ants;

	ants = malloc(sizeof(t_ant) * num);
	i = -1;
	while (++i < num)
	{
		ants[i].x = 500;//(rand() % 900) + 50;
		ants[i].y = 500;//(rand() % 900) + 50;
		ants[i].dir = i;
	}
	return (ants);
}



void	take_input(t_render *r)
{
	int	in;
	while (1)
	{
		printf("0 | EXIT\n",);
		printf("1 | turn speed		=	%d\n", r->turnSpeed);
		printf("2 | angle			=	%d\n", r->angle);
		printf("3 | steps			=	%d\n", r->steps);
		printf("4 | distance		=	%d\n", r->distance);
		printf("5 | speed			=	%d\n", r->speed);
		printf("6 | box config		=	%d\n", r->box_type);
		printf("7 | toggle trail	=	%d\n", r->ant_only);
		scanf("%d", &in);
		printf("enter new int\n");
		if (in == 0)
			exit(0);
		else if (in == 1)
		{
			scanf("%d", &in);
			r->turnSpeed = in;
		}
		if (in == 2)
		{
			scanf("%d", &in);
			r->angle = in;
		}
		if (in == 3)
		{
			scanf("%d", &in);
			r->steps = in;
		}
		if (in == 4)
		{
			scanf("%d", &in);
			r->distance = in;
		}
		if (in == 5)
		{
			scanf("%d", &in);
			r->speed = in;
		}
		if (in == 6)
		{
			system("clear");
			printf("box config\n");
			printf("1 | open\n");
			printf("2 | box\n");
			printf("3 | circle\n");
			scanf("%d", &in);
			r->box_type = in;
		}
		if (in == 7)
			r->ant_num *= -(1);
	}
}

int	render_next_frame(t_render *r)
{
	if (r->ant_only)
	{
		r->img = mlx_new_image(r->mlx, r->w, r->h);
		r->addr = mlx_get_data_addr(r->img, &r->bits_per_pixel, &r->line_length, &r->endian);
	}
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

	r->evap = 5;
	r->size = 1;
	r->steps = 1;
	r->angle = 30;
	r->box_type = 1;
	r->ant_only = -1;
	r->distance = 35;
	r->turnSpeed = 2;

	r->w = 1000;
	r->h = 1000;
	r->mlx = mlx_init();
	r->mlx_win = mlx_new_window(r->mlx, r->w, r->h, "ant_sim");
	r->img = mlx_new_image(r->mlx, r->w, r->h);
	r->addr = mlx_get_data_addr(r->img, &r->bits_per_pixel, &r->line_length, &r->endian);

	init_threads(r);

	mlx_key_hook(r->mlx_win, keypress, r);
	mlx_loop_hook(r->mlx, render_next_frame, r);
	mlx_loop(r->mlx);
}
