#include "cub3d.h"

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("Failed open file");
	return (fd);
}

int	check_extension(const char *filename)
{
	char	*dot;

	dot = ft_strchr(filename, '.');
	if (dot && ft_strncmp(dot, ".cub", 4) == 0 && ft_strlen(dot) == 4)
		return (0);
	return (1);
}

int	count_line(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open_file(filename);
	if (fd == -1)
		return (1);
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

int	fill_map(t_game *map, const char *filename)
{
	size_t	i;
	int		fd;
	char	*line;

	if (!map || !filename)
		return (1);
	map->row = count_line(filename);
	map->map = malloc(sizeof(char *) * (map->row + 1));
	if (!map->map)
		return (1);
	i = 0;
	fd = open_file(filename);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		map->map[i] = line;
		i++;
	}
	map->map[i] = NULL;
	close(fd);
	return (0);
}


