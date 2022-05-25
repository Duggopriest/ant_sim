/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:02 by marvin            #+#    #+#             */
/*   Updated: 2022/05/15 18:45:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static int	ft_long_border(const char c, int mult, long nb)
{
	long	border;

	border = 922337203685477580;
	if ((nb > border || (nb == border && (c - '0') > 7)) && mult == 1)
		return (-1);
	else if ((nb > border || (nb == border && (c - '0') > 8)) && mult == -1)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;
	int		brd;

	num = 0;
	sign = 1;
	brd = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		brd = ft_long_border(*str, sign, num);
		if (brd < 1)
			return (brd);
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}
