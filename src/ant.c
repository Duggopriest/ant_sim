#include "ant_sim.h"

float	sense(t_render *r, t_ant *ant, float angle, int size, float dist)
{
	float	SAngle 	= ant->dir + angle;
	int		sx 		= ant->x + cos(SAngle * 3.14 / 180) * dist;
	int		sy 		= ant->y + sin(SAngle * 3.14 / 180) * dist;
	float	sum		= 0;
	int		px;
	int		py;

	for (int offsetX = -size; offsetX <= size; offsetX++)
	{
		for (int offsety = -size; offsety <= size; offsety++)
		{
			px = sx + offsetX;
			py = sy + offsety;
			sum += pixel_get(r, px, py);
		}
	}
	return (sum);
}

int randomRange(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void	box(t_ant *ant, t_render *r)
{
	if (ant->x < 10)
		ant->dir = randomRange(-85, 85);
	else if (ant->x > r->w - 10)
		ant->dir = randomRange(-265, 265);
	else if (ant->y < 10)
		ant->dir = randomRange(-5, 175);
	else if (ant->y > r->h - 10)
		ant->dir = randomRange(-185, 5);
}

void	open_box(t_ant *ant, t_render *r)
{
	if (ant->x < 10)
		ant->x = r->w - 15;
	else if (ant->x > r->w - 10)
		ant->x = 15;
	else if (ant->y < 10)
		ant->y = r->h - 15;
	else if (ant->y > r->h - 10)
		ant->y = 15;
}

void	circle(t_ant *ant)
{
	if (dist(ant->x, ant->y, 500, 500) > 500)
	{
		ant->x = 500;
		ant->y = 500;
	}
}

void	draw_square(int	x, int y, int size, t_render *r)
{
	int	i;
	int	j;

	j = y + size + 1;
	while (--j > y)
	{
		i = x + size + 1;
		while (--i > x)
			if (i > x && i < x + size && j > y && j < y + size)
				pixel_put(r, i, j, 0x000000FF);
	}	
}

void	run_ant(t_ant *ant, t_render *r)
{
	float	left;
	float	right;
	float	ford;

	ant->x += steps * cos(ant->dir * 3.14 / 180);
	ant->y += steps * sin(ant->dir * 3.14 / 180);
	if (r->box_type == 1)
		open_box(ant, r);
	else if (r->box_type == 2)
		box(ant, r);
	else if (r->box_type == 3)
		circle(ant);
	ford = sense(r, ant, 0, size, distance);
	left = sense(r, ant, angle, size, distance);
	right = sense(r, ant, -angle, size, distance);
	if (ford > right && ford > left)
		ant->dir += 0;
	else if (right > left)
		ant->dir -= r->turnspeed;
	else if (right < left)
		ant->dir += r->turnspeed;
	pixel_put(r, ant->x, ant->y, 0x000000FF);
}
