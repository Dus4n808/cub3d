#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct	s_game
{
	char **map;
	int	row;
} t_game;

//parsing
int	open_file(const char *filename);
int	check_extension(const char *filename);
int	count_line(const char *filename);
int	fill_map(t_game *map, const char *filename);

#endif
