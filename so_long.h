#ifndef SO_LONG_H
#define SO_LONG_H

#include <mlx.h>
#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include <stdlib.h>


typedef struct s_var {
	int	i;
	int	j;
	int	size1;
	int	size2;
	int	sizep;
}	t_var;

typedef struct s_map{
    char *map;
    char **tab;
    int w;
    int h;
    int player;
    int exit;
    int colec;
    int i;
    int px;
    int py;
    int pm;
}   t_map;

typedef struct s_mlx{
    int bpp;
	int line;
	int endian;
	char *addr;
	void *mlx;
    void *win;
    void *img;
    void *img2;
	int x;
    int y;
} t_mlx;

typedef struct s_data 
{
   t_mlx *mlxx;
   t_map *mapp;
}t_data;

char	*get_next_line(int fd);
int		the_end(char *str);
char	*get_intel(int fd, int size, char *buffer);
size_t	ft_strlen(const char *s);
char	*get_line(char *buffer);
char	*get_rest(char *buffer);
char	*ft_strjoin(char *s1, char *s2);
void checkend(t_data *data,int x,int y);

char	*ft_strchr(const char *s, int c);
#endif

