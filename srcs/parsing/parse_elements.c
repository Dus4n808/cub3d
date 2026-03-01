/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:57:44 by dufama            #+#    #+#             */
/*   Updated: 2026/03/01 16:14:47 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_textures(t_game *game, char *line, char **dest)
{
	char	*path;

	if (*dest)
		exit_error(game, "Duplicate texture identifier");
	path = line + 3;
	while (*path == ' ')
		path++;
	if (*path == '\n')
		exit_error(game, "Missing texture path");
	*dest = ft_strdup(path);
	if (!*dest)
		exit_error(game, "Memory allocation failed");
}

static void	valid_rgb(t_game *game, int value)
{
	if (value < 0 || value > 255)
		exit_error(game, "RGB invalid");
}

void	parse_color(t_game *game, char *line, int *rgb, int *flag)
{
	char	**sec;

	if (*flag)
		exit_error(game, "Duplicate color");
	line += 2;
	while (*line == ' ')
		line++;
	sec = ft_split(line, ',');
	if (!sec || !sec[0] || !sec[1] || !sec[2] || sec[3])
	{
		free_lines(sec);
		exit_error(game, "Invalid RGB format");
	}
	rgb[0] = ft_atoi(sec[0]);
	rgb[1] = ft_atoi(sec[1]);
	rgb[2] = ft_atoi(sec[2]);
	valid_rgb(game, rgb[0]);
	valid_rgb(game, rgb[1]);
	valid_rgb(game, rgb[2]);
	free_lines(sec);
	*flag = 1;
}

