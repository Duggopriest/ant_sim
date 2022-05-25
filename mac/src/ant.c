/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:50:55 by marvin            #+#    #+#             */
/*   Updated: 2022/05/25 19:50:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

float	sense(r_render *r, t_ant *ant, int x, int y)
{
	float	sum = 0;
	float	size = 1;
	int		x;
	int		y;

	for (int offsetX = -size; offsetX <= size; offsetX++)
	{
		for (int offsety = -size; offsety <= size; offsety++)
		{
			x = x + offsetX;
			y = y + offsety;
			sum += pixel_get(r, x, y);
		}
	}
	return (sum);
}

void	box(t_ant *ant)
{
	if (ant->x < 10 || ant->x > r->w - 10)
	{
		ant->dir = 180 - ant->dir;
		ant->x += steps * cos(ant->dir * 3.14 / 180);
		ant->y += steps * sin(ant->dir * 3.14 / 180);
	}
	else if (ant->y < 10 || ant->y > r->h - 10)
	{
		ant->dir = 360 - ant->dir;
		ant->x += steps * cos(ant->dir * 3.14 / 180);
		ant->y += steps * sin(ant->dir * 3.14 / 180);
	}
}

void	open_box(t_ant *ant)
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
		ant->dir += 180;//(rand() % 50);
}

//pixel_put(r, ant->x + steps * cos(ant->dir * 3.14 / 180) + 2, ant->y + steps * sin(ant->dir * 3.14 / 180) + 2, 0x00FF0000);
//pixel_put(r, ant->x + steps * cos(ant->dir * 3.14 / 180) - 2, ant->y + steps * sin(ant->dir * 3.14 / 180) + 2, 0x0000FF00);

void	run_ant(t_ant *ant, t_render *r)
{
	double	steps = 1;
	int	left;
	int	right;
	int	ford;
	int	turnSpeed = 1;

	ant->x += steps * cos(ant->dir * 3.14 / 180);
	ant->y += steps * sin(ant->dir * 3.14 / 180);
	open_box(ant);
	ford = sense(r, ant, ant->x + steps * cos(ant->dir * 3.14 / 180), ant->y + steps * sin(ant->dir * 3.14 / 180) + 3);
	left = sense(r, ant, ant->x + steps * cos(ant->dir * 3.14 / 180) - 3, ant->y + steps * sin(ant->dir * 3.14 / 180) + 3);
	right = sense(r, ant, ant->x + steps * cos(ant->dir * 3.14 / 180) + 3, ant->y + steps * sin(ant->dir * 3.14 / 180) + 3);
	if (right > left)
		ant->dir -= turnSpeed;
	else if (right < left)
		ant->dir += turnSpeed;
	//ant->dir += (left - right) / 10;
	pixel_put(r, ant->x, ant->y, 0x000000FF);
}
