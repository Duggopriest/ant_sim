#include "ant_sim.h"

int ft_squr(int x)
{
	int lower = 1;
	int upper = x;
	int root = lower + (upper - lower) / 2;

	if (x < 0)
		return (0);
	if (x == 0 || x == 1)
		return (x);
	while (root > x / root || root + 1 <= x/(root+1))
	{
		if (root > x/root)
			upper = root;
		else
			lower = root;
		root = lower + (upper - lower) / 2;
	}
	return (root);
}

int	dist(int fx, int fy, int sx, int sy)
{
	return (ft_squr((sx - fx) * (sx - fx) + (sy - fy) * (sy - fy)));
}
