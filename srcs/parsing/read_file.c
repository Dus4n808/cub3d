#include "cub3d.h"

static int	open_file(const char *filename)
{
	return(open(filename, O_RDONLY));
}

int	check_extension(const char *filename)
{
	char	*dot;
	char	*slash;
	char	*check;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (1);
	if (ft_strncmp(dot, ".cub", 4) != 0 || ft_strlen(dot) != 4)
		return (1);
	slash = ft_strrchr(filename, '/');
	if (slash)
		check = slash + 1;
	else
		check = (char *)filename;
	while (check < dot)
	{
		if (*check == '.')
			return (1);
		check++;
	}
	return (0);
}

static int	count_line(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open_file(filename);
	if (fd == -1)
		return (-1);
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

char	**read_all_lines(const char *filename)
{
	char	**lines;
	int		i;
	int		nb_line;
	int		fd;

	fd = open_file(filename);
	if (fd == -1)
		return (NULL);
	nb_line = count_line(filename);
	if (nb_line == -1)
		return (NULL);
	lines = malloc(sizeof(char *) * (nb_line + 1));
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	i = 0;
	while ((lines[i] = get_next_line(fd)) != NULL)
		i++;
	lines[i] = NULL;
	close(fd);
	return (lines);
}


