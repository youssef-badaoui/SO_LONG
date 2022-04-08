/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:37:46 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/03/29 09:37:50 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check(t_map *map, char *line)
{
	int			i;
	static int	j;

	i = 0;
	while (line[i] != 10 && line[i] != 0)
	{
		if (line[i] == 'C')
			map->colec++;
		else if (line[i] == 'E')
			map->exit++;
		else if (line[i] == 'P')
		{
			map->player++;
			map->px = i;
			map->py = j;
		}
		else if (line[i] != '1' && line[i] != '0')
			map->error = 1;
		map->i++;
		i++;
	}
	j++;
}

void	lenmap(t_map *map_data)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(map_data->map, O_RDWR);
	if (fd < 1)
		return ;
	i = 0;
	while (map_data->map[i])
		i++;
	if (map_data->map[i - 1] != 'r' || map_data->map[i - 2] != 'e'
		|| map_data->map[i - 3] != 'b' || map_data->map[i - 4] != '.')
		map_data->error = 1;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map_data->h++;
		map_data->w = ft_strlen(line);
		check(map_data, line);
		free(line);
	}
	close(fd);
}

void	full_map(t_map *map)
{
	int	fd;
	int	k;

	fd = open(map->map, O_RDWR);
	if (fd < 1)
		return ;
	k = 0;
	while (k < map->h)
	{
		map->tab[k] = get_next_line(fd);
		if (!map->tab[k])
			return ;
		k++;
	}
}

void	printit(int i, int j, t_map *map, t_mlx *mlx)
{
	int	x;
	int	y;

	while (i < map->h)
	{
		if (map->tab[i][j] == '1')
			mlx->img = mlx_xpm_file_to_image(mlx->mlx, "wall.xpm", &x, &y);
		else if (map->tab[i][j] == 'C')
			mlx->img = mlx_xpm_file_to_image(mlx->mlx, "C.xpm", &x, &y);
		else if (map->tab[i][j] == 'E')
			mlx->img = mlx_xpm_file_to_image(mlx->mlx, "E.xpm", &x, &y);
		else if (map->tab[i][j] == 'P')
			mlx->img = mlx_xpm_file_to_image(mlx->mlx, "P.xpm", &x, &y);
		if (map->tab[i][j] != '0')
			mlx_put_image_to_window(mlx->mlx, mlx->win,
				mlx->img, 20 * j, 20 * i);
		j++;
		if (j == map->w)
		{
			j = 0;
			i++;
		}
	}
}

void	replace(t_data *data, int x, int y)
{
	int	a;
	int	b;

	if (data->mapp->tab[data->mapp->py + y][data->mapp->px + x] != '1' &&
		data->mapp->tab[data->mapp->py + y][data->mapp->px + x] != 'E')
	{
		checkend(data, x, y);
		ft_put_move(++data->mapp->pm);
		data->mapp->tab[data->mapp->py][data->mapp->px] = '0';
		data->mapp->tab[data->mapp->py + y][data->mapp->px + x] = 'P';
		data->mlxx->img = mlx_xpm_file_to_image(data->mlxx->mlx,
				"b.xpm", &a, &b);
		mlx_put_image_to_window(data->mlxx->mlx, data->mlxx->win,
			data->mlxx->img, 20 * data->mapp->px, 20 * data->mapp->py);
		data->mapp->px += x;
		data->mapp->py += y;
		mlx_put_image_to_window(data->mlxx->mlx, data->mlxx->win,
			data->mlxx->img, 20 * data->mapp->px, 20 * data->mapp->py);
		data->mlxx->img = mlx_xpm_file_to_image(data->mlxx->mlx,
				"P.xpm", &x, &y);
		mlx_put_image_to_window(data->mlxx->mlx, data->mlxx->win,
			data->mlxx->img, 20 * data->mapp->px, 20 * data->mapp->py);
	}
	else if (data->mapp->tab[data->mapp->py + y][data->mapp->px + x] == 'E')
		checkend(data, x, y);
}
