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

	ants = malloc(sizeof(t_ant) * num + 1);
	i = -1;
	while (++i < num)
	{
		ants[i].x = (rand() % 900) + 50;
		ants[i].y = (rand() % 900) + 50;
		ants[i].dir = i;
	}
	printf("ants spawned\n");
	return (ants);
}



void	take_input(t_render *r)
{
	float	in;
	while (1)
	{
		system("clear");
		printf("0 | EXIT\n");
		printf("1 | turn speed		=	%f\n", r->turnSpeed);
		printf("2 | angle		=	%f\n", r->angle);
		printf("3 | steps		=	%f\n", r->steps);
		printf("4 | distance		=	%d\n", r->distance);
		printf("5 | slow		=	%d\n", r->speed);
		printf("6 | box config		=	%d\n", r->box_type);
		printf("7 | toggle trail	=	%d\n", r->ant_only);
		printf("8 | evap amount		=	%f\n", r->evap);
		scanf("%f", &in);
		printf("enter new int\n");
		if (in == 0)
		{
			system("clear");
			exit(0);
		}
		else if (in == 1)
		{
			scanf("%f", &in);
			r->turnSpeed = in;
		}
		else if (in == 2)
		{
			scanf("%f", &in);
			r->angle = in;
		}
		else if (in == 3)
		{
			scanf("%f", &in);
			r->steps = in;
		}
		else if (in == 4)
		{
			scanf("%f", &in);
			r->distance = in;
		}
		else if (in == 5)
		{
			scanf("%f", &in);
			r->speed = in;
		}
		else if (in == 6)
		{
			system("clear");
			printf("box config\n");
			printf("1 | open\n");
			printf("2 | box\n");
			printf("3 | circle\n");
			printf("4 | circle Bounce\n");
			scanf("%f", &in);
			r->box_type = in;
		}
		else if (in == 7)
		{
			scanf("%f", &in);
			r->ant_only = in;
		}
		else if (in == 8)
		{
			scanf("%f", &in);
			r->evap = in;
		}
	}
}

int	render_next_frame(t_render *r)
{
	if (r->loaded)
	{
		usleep(100000);
		r->loaded = 0;
	}
	if (r->ant_only == 1)
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

	r->evap = 10;
	r->size = 0;
	r->steps = 1;
	r->angle = 30;
	r->box_type = 2;
	r->ant_only = -1;
	r->distance = 35;
	r->turnSpeed = 1;

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
