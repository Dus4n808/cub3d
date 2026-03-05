#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"

# ifdef __APPLE__
#  include "../mlx-mac/mlx.h"
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  include "../mlx-linux/mlx.h"
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif


# define WIN_WIDTH 1280
# define WIN_HEIGTH 720
# define TILE_SIZE 64
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.03
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3


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
	double	fov_x;
	double	fov_y;
	char	dir;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

typedef struct s_tex_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
} t_tex_img;

typedef struct s_draw_tex
{
	t_tex_img	*tex;
	double		wall_x;
	double		wall_y;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			colors;

} t_draw_tex;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	perp;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
} t_ray;


typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_textures	textures;
	t_tex_img	tex[4];
	t_player	player;
	t_map		map;
	t_img		img;
	char		**lines;
}	t_game;

//utils
void	exit_error(t_game *game, char *msg);
void	free_lines(char **lines);
void	free_element(t_game *game);
void	free_game(t_game *game);
//parsing
int		check_extension(const char *filename);
char	**read_all_lines(const char *filename);
void	parse_textures(t_game *game, char *line, char **dest);
void	parse_color(t_game *game, char *line, int *rgb, int *flag);
int		parse_file(t_game *game, const char *filename);
int		parse_map(t_game *game, char **lines);
int		is_map(const char *line);
void	check_all_elements(t_game *game);
void	map_is_playable(t_game *game);
//render
void	render(t_game *game);
//game
int	init_game(t_game *game);
//draw
void	put_pixel(t_img *img, int x, int y, int color);
int		rgb_to_int(int r, int g, int b);
void	floor_and_ceiling(t_game *game);
//textures
void	load_tex(t_game *game);
void	init_text(t_game *game, t_ray *ray, t_draw_tex *draw);
//raycasting
void	raycasting(t_game *game);
//player
void	init_player_pos(t_player *player);
//move
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

#endif
