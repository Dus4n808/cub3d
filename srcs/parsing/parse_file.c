/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaroni <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:55:36 by dufama            #+#    #+#             */
/*   Updated: 2026/04/13 17:54:52 by lubaroni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n'
			&& line[i] != '\r' && line[i] != '\t')
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

static void	parse_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_textures(game, line, &game->textures.north);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_textures(game, line, &game->textures.south);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_textures(game, line, &game->textures.west);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_textures(game, line, &game->textures.east);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(game, line, game->textures.floor,
			&game->textures.set_floor);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(game, line, game->textures.ceiling,
			&game->textures.set_ceiling);
	else if (!empty_line(line))
		exit_error(game, "Unknown element");
}

static int	parse_elements(t_game *game, char **lines)
{
	int	i;

	i = 0;
	while (lines[i] && !is_map(lines[i]))
	{
		parse_line(game, lines[i]);
		i++;
	}
	return (0);
}

int	parse_file(t_game *game, const char *filename)
{
	if (check_extension(filename))
		exit_error(game, "Wrong Extension");
	game->lines = read_all_lines(filename);
	if (!game->lines)
		exit_error(game, "Failed to read file");
	if (parse_elements(game, game->lines) || parse_map(game, game->lines))
		exit_error(game, "Invalid Map file");
	check_all_elements(game);
	free_lines(game->lines);
	game->lines = NULL;
	return (0);
}
