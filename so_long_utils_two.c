/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:38:00 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/03/29 09:38:01 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw(t_mlx *mlx, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printit(i, j, map, mlx);
}

int	out(void)
{
	exit(1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_putchar(n + '0');
	}
}

void	ft_put_move(int nb)
{
	ft_putnbr(nb);
	write(1, " move\n", 6);
}
