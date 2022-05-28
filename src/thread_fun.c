#include "ant_sim.h"

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
		usleep(th->r->speed * 1000);
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
		th->num = r->ant_num / r->num_threads;
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