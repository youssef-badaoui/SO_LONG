/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:37:33 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/03/29 09:37:39 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	hun(int keycode, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (keycode == 2)
		x = 1;
	else if (keycode == 0)
		x = -1;
	else if (keycode == 1)
		y = 1;
	else if (keycode == 13)
		y = -1;
	else if (keycode == 53 || keycode == 17)
		exit(0);
	else
		return (0);
	replace(data, x, y);
	return (0);
}

void	checkend(t_data *data, int x, int y)
{
	if (data->mapp->tab[data->mapp->py + y][data->mapp->px + x] == 'C')
		data->mapp->colec--;
	else if (data->mapp->tab[data->mapp->py + y][data->mapp->px + x] == 'E')
	{
		if (data->mapp->colec <= 0)
			exit(0);
	}
}

int	check_bord(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->h)
	{
		if (map->tab[i][0] != '1' || map->tab[i][map->w - 1] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->w)
	{
		if (map->tab[0][i] != '1' || map->tab[map->h - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	full_stct(t_map *map, char *va)
{
	map->w = 0;
	map->h = 0;
	map->player = 0;
	map->exit = 0;
	map->colec = 0;
	map->i = 0;
	map->px = 0;
	map->py = 0;
	map->pm = 0;
	map->error = 0;
	map->map = va;
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_map	map;
	t_data	data;

	full_stct(&map, av[1]);
	if (ac != 2)
		return (0);
	lenmap(&map);
	full_map(&map);
	if (map.h == map.w || map.player != 1 || map.colec < 1 || map.exit < 1
		||map.h * map.w != map.i || !check_bord(&map) || map.error)
	{
		write (2, "error\nmap error!", 16);
		exit(1);
	}
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 20 * map.w, 20 * map.h, "so_long");
	data.mapp = &map;
	data.mlxx = &mlx;
	draw(&mlx, &map);
	mlx_hook(mlx.win, 02, 00, hun, &data);
	mlx_hook(mlx.win, 17, 00, out, &data);
	mlx_loop(mlx.mlx);
	return (0);
}
