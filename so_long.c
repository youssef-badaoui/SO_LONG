 #include "so_long.h"

void    check(t_map *map, char *line)
{
	int	i;
	static int	j;

	i = 0;
	while(line[i] != 10 && line[i] != 0)
	{
		if(line[i] == 'C')
			map->colec++;
		else if(line[i] == 'E')
			map->exit++;
		else if(line[i] == 'P')
		{
			map->player++;
			map->px = i;
			map->py = j;
		}
		else if(line[i] != '1' && line[i] != '0')
			map->error = 1;
		map->i++;
		i++;
	}
	j++;
}

void lenmap (t_map *map_data)
{
	int fd;
	char *line;
	int i;

	fd = open(map_data->map, O_RDWR);
	if(fd < 1)
		return;
	i = 0;
	while(map_data->map[i])
		i++;
	if(map_data->map[i-1] != 'r' ||map_data->map[i-2] != 'e' ||map_data->map[i-3] != 'b' ||map_data->map[i-4] != '.')
		map_data->error = 1;
	line = NULL;
	while(1)
	{
		line = get_next_line(fd);
		if(!line)
			break;
		map_data->h++;
		map_data->w = ft_strlen(line);
		check(map_data, line);
		free(line);
	}
	close(fd);
}

void full_map(t_map *map)
{
	int fd;
	int k;
	fd = open(map->map, O_RDWR);
	if(fd < 1)
		return;
	k = 0;
	while(k < map->h)
	{
		map->tab[k] = get_next_line(fd);
			if(!map->tab[k])
				return;
		k++;
	 }
}

void draw(t_mlx *mlx, t_map *map)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	j = 0;
	while(i < map->h)
	{
		if(map->tab[i][j] == '1')
			mlx->img = mlx_xpm_file_to_image(mlx->mlx, "wall.xpm", &x, &y);
		else if(map->tab[i][j] == 'C')
			mlx->img = mlx_xpm_file_to_image(mlx->mlx, "C.xpm", &x, &y);
		else if(map->tab[i][j] == 'E')
			mlx->img = mlx_xpm_file_to_image(mlx->mlx, "E.xpm", &x, &y);
		else if(map->tab[i][j] == 'P')
			mlx->img = mlx_xpm_file_to_image(mlx->mlx, "P.xpm", &x, &y);
		if(map->tab[i][j] != '0')
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 20*j, 20*i);
		j++;
		if(j == map->w)
		{
			j = 0;
			i++;
		}
	}
}

void replace(t_data *data,int x, int y)
{
	int a;
	int b;
	if(data->mapp->tab[data->mapp->py + y][data->mapp->px + x] != '1' && data->mapp->tab[data->mapp->py + y][data->mapp->px + x] != 'E')
	{
		checkend(data, x, y);
		data->mapp->pm++;
		printf("%d move.\n", data->mapp->pm);
		data->mapp->tab[data->mapp->py][data->mapp->px] = '0';
		data-> mapp->tab[data->mapp->py + y][data->mapp->px + x] = 'P';

		data->mlxx->img = mlx_xpm_file_to_image(data->mlxx->mlx, "black.xpm", &a, &b);
		mlx_put_image_to_window(data->mlxx->mlx, data->mlxx->win, data->mlxx->img, 20*data->mapp->px  ,20*data->mapp->py);
		data->mapp->px += x;
		data->mapp->py += y;
		mlx_put_image_to_window(data->mlxx->mlx, data->mlxx->win, data->mlxx->img, 20*data->mapp->px  ,20*data->mapp->py);
		data->mlxx->img = mlx_xpm_file_to_image(data->mlxx->mlx, "P.xpm", &x, &y);
		mlx_put_image_to_window(data->mlxx->mlx, data->mlxx->win, data->mlxx->img, 20*data->mapp->px , 20*data->mapp->py);
	}
	else if(data->mapp->tab[data->mapp->py + y][data->mapp->px + x] == 'E')
		checkend(data, x, y);
}
int out(void)
{
	exit(1);
}
int hun(int keycode, t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if(keycode == 124)
		x = 1;
	else if(keycode == 123)
		x = -1;
	else if(keycode == 125)
		y = 1;
	else if(keycode == 126)
		y = -1;
	else if(keycode == 53 || keycode == 17)
		exit(0);
	else
		return 0;
	replace(data, x, y);
	return (0);
}

void checkend(t_data *data,int x,int y)
{
	int a;
	int b;
	if(data->mapp->tab[data->mapp->py + y][data->mapp->px + x] == 'C')
		data->mapp->colec--;
	else if(data->mapp->tab[data->mapp->py + y][data->mapp->px+ x] == 'E')
	{
		if(data->mapp->colec <= 0)
			exit(0);
	}
}

int check_bord(t_map *map)
{
	int i;

	i = 0;
	while(i < map->h)
	{
		if(map->tab[i][0] != '1' || map->tab[i][map->w - 1] != '1')
		{
			// printf(" i = %d",i);
			// printf("%d %d",map->tab[i][0] ,map->tab[i][map->w - 1]);
			return (0);
		}
		i++;
	}
	i = 0;
	while(i < map->w)
	{
		if(map->tab[0][i] != '1' || map->tab[map->h - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int main(int ac,char **av)
{
	int i;
	int j;
	t_mlx mlx;
	t_map map = {av[1], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	t_data data;
	
	i = 0;
	j = 0;
	lenmap(&map);
	full_map(&map);
	printf("%d\n", map.h);
	printf("%d\n", map.w);
	if( map.h == map.w || map.player != 1 || map.colec < 1 || map.exit < 1 || map.h * map.w != map.i || !check_bord(&map) || map.error)
	{
	    write(2, "error\nmap error!", 16);
	    return 0;
	}
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 20*map.w, 20*map.h, "so_long");
	data.mapp = &map;
	data.mlxx = &mlx;
	draw(&mlx, &map);
	mlx_hook(mlx.win, 02, 00, hun, &data);
	mlx_hook(mlx.win, 17, 00, out, &data);
	mlx_loop(mlx.mlx);
	return (0);
}