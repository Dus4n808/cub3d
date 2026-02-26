/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:55:36 by dufama            #+#    #+#             */
/*   Updated: 2026/02/26 17:20:29 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\r' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_map(const char *line)
{
	int	i;

	i = 0;
	if (empty_line(line))
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}


static int	parse_elements(t_game *game, char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && !is_map(lines[i]))
	{
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
			parse_textures(game, lines[i], &game->textures.north);
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
			parse_textures(game, lines[i], &game->textures.south);
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
			parse_textures(game, lines[i], &game->textures.west);
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
			parse_textures(game, lines[i], &game->textures.east);
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
			parse_color(game, lines[i], game->textures.floor);
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
			parse_color(game, lines[i], game->textures.ceiling);
		else if (empty_line(lines[i]))
			;
		else
			exit_error(game, "Unknown element");
		i++;
	}
	return (0);
}

int	parse_file(t_game *game, const char *filename)
{
	char	**lines;

	if (check_extension(filename))
		exit_error(game, "Wrong Extension");
	lines = read_all_lines(filename);
	if (!lines)
		exit_error(game, "Failed to read file");
	if (parse_elements(game, lines) || parse_map(game, lines))
	{
		free_lines(lines);
		exit_error(game, "Invalid Map file");
	}
	return (0);
}
