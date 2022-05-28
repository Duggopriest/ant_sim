#include "ant_sim.h"

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
	}
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
					color /= (0.01 * r->evap);
				pixel_put(r, j, i, color);
			}
		}
		usleep(1000);
	}
}
