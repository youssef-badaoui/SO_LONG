NAME = solong

SRC = so_long.c so_long_utils.c get_next_line.c get_next_line_utils.c ft_strlen.c  so_long_utils_two.c 

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(MLX_FLAGS)  -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all