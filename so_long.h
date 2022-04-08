/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:06:03 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/03/29 11:06:06 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_map{
	int		w;
	int		h;
	int		player;
	int		exit;
	int		colec;
	int		i;
	int		px;
	int		py;
	int		pm;
	int		error;
	char	*map;
	char	*tab[1000];
}	t_map;

typedef struct s_mlx{
	void	*mlx;
	int		bpp;
	int		line;
	int		endian;
	char	*addr;
	void	*win;
	void	*img;
	void	*img2;
	int		x;
	int		y;
}	t_mlx;

typedef struct s_var {
	int	i;
	int	j;
	int	size1;
	int	size2;
	int	sizep;
}	t_var;

typedef struct s_data
{
	t_mlx	*mlxx;
	t_map	*mapp;
}	t_data;

char	*get_next_line(int fd);
void	full_stct(t_map *map, char *va);
int		the_end(char *str);
char	*get_intel(int fd, int size, char *buffer);
size_t	ft_strlen(const char *s);
char	*get_line(char *buffer);
char	*get_rest(char *buffer);
char	*ft_strjoin(char *s1, char *s2);
void	checkend(t_data *data, int x, int y);
void	check(t_map *map, char *line);
void	lenmap(t_map *map_data);
void	full_map(t_map *map);
void	draw(t_mlx *mlx, t_map *map);
void	replace(t_data *data, int x, int y);
char	*ft_strchr(const char *s, int c);
int		out(void);
void	draw(t_mlx *mlx, t_map *map);
void	printit(int i, int j, t_map *map, t_mlx *mlx);
void	ft_putnbr(int nb);
void	ft_put_move(int nb);
void	ft_putchar(char c);
#endif
