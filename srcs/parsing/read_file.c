/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaroni <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:20:31 by lubaroni          #+#    #+#             */
/*   Updated: 2026/04/13 17:56:01 by lubaroni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	open_file(const char *filename)
{
	return (open(filename, O_RDONLY));
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
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static void	fill_lines(char **lines, int fd)
{
	int	i;

	i = 0;
	lines[i] = get_next_line(fd);
	while (lines[i])
	{
		i++;
		lines[i] = get_next_line(fd);
	}
}

char	**read_all_lines(const char *filename)
{
	char	**lines;
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
	fill_lines(lines, fd);
	close(fd);
	return (lines);
}
