#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"

# ifdef __APPLE__
# include "../mlx-mac/mlx.h"
# elif defined(__LINUX__)
# include "../mlx-linux/mlx.h"
# endif

# define WIN_WIDTH 1280
# define WIN_HEIGTH 720
# define TILE_SIZE 64

# define ERR_MAP "Error Invalid Map\n"

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[3];
	int		set_floor;
	int		ceiling[3];
	int		set_ceiling;
}	t_textures;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	char	dir;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_textures	textures;
	t_player	player;
	t_map		map;
	char		**lines;
}	t_game;

//utils
void	exit_error(t_game *game, char *msg);
void	free_lines(char **lines);
void	free_element(t_game *game);
//parsing
int		check_extension(const char *filename);
char	**read_all_lines(const char *filename);
void	parse_textures(t_game *game, char *line, char **dest);
void	parse_color(t_game *game, char *line, int *rgb, int *flag);
int		parse_file(t_game *game, const char *filename);
int		parse_map(t_game *game, char **lines);
int		is_map(const char *line);
void	check_all_elements(t_game *game);


#endif
