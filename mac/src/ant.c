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

float	sense(t_render *r, t_ant *ant, int x, int y, int size)
{
	float	sum = 0;
	int		px;
	int		py;

	for (int offsetX = -size; offsetX <= size; offsetX++)
	{
		for (int offsety = -size; offsety <= size; offsety++)
		{
			px = x + offsetX;
			py = y + offsety;
			sum += pixel_get(r, px, py);
		}
	}
	return (sum);
}

void	box(t_ant *ant, t_render *r)
{
	if (ant->x < 10 || ant->x > r->w - 10)
	{
		ant->dir = 180 - ant->dir;
		ant->x += cos(ant->dir * 3.14 / 180);
		ant->y += sin(ant->dir * 3.14 / 180);
	}
	else if (ant->y < 10 || ant->y > r->h - 10)
	{
		ant->dir = 360 - ant->dir;
		ant->x += cos(ant->dir * 3.14 / 180);
		ant->y += sin(ant->dir * 3.14 / 180);
	}
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
		ant->dir += 180;//(rand() % 50);
}

//pixel_put(r, ant->x + steps * cos(ant->dir * 3.14 / 180) + 2, ant->y + steps * sin(ant->dir * 3.14 / 180) + 2, 0x00FF0000);
//pixel_put(r, ant->x + steps * cos(ant->dir * 3.14 / 180) - 2, ant->y + steps * sin(ant->dir * 3.14 / 180) + 2, 0x0000FF00);

void	run_ant(t_ant *ant, t_render *r)
{
	float	left;
	float	right;
	float	ford;
	float	turnSpeed = 9000;
	double	steps = .5;
	int		spacing = 5;
	int		distance = 5;
	int		size = 5;

	ant->x += steps * cos(ant->dir * 3.14 / 180);
	ant->y += steps * sin(ant->dir * 3.14 / 180);
	open_box(ant, r);
	ford = sense(r, ant, ant->x + steps * cos(ant->dir * 3.14 / 180), ant->y + steps * sin(ant->dir * 3.14 / 180) + distance, size);
	left = sense(r, ant, ant->x + steps * cos(ant->dir * 3.14 / 180) - spacing, ant->y + steps * sin(ant->dir * 3.14 / 180) + distance, size);
	right = sense(r, ant, ant->x + steps * cos(ant->dir * 3.14 / 180) + spacing, ant->y + steps * sin(ant->dir * 3.14 / 180) + distance, size);
	if (ford > right && ford > left)
		ant->dir += 0;
	else if (right > left)
		ant->dir -=  right / turnSpeed;
	else if (right < left)
		ant->dir += left / turnSpeed;
	//ant->dir += (left - right) / 10;
	pixel_put(r, ant->x, ant->y, 0x000000FF);
}
