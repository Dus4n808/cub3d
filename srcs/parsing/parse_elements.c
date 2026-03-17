/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:57:44 by dufama            #+#    #+#             */
/*   Updated: 2026/03/17 12:48:46 by dufama           ###   ########.fr       */
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

static int	is_valid_num(const char *str)
{
	int	i;
	int	digit;

	i = 0;
	digit = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(str[i]))
			return (0);
		digit = 1;
		i++;
	}
	return (digit);
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
		if (sec)
			free_lines(sec);
		exit_error(game, "Invalid RGB format");
	}
	if (!is_valid_num(sec[0]) || !is_valid_num(sec[1]) || !is_valid_num(sec[2]))
	{
		free_lines(sec);
		exit_error(game, "RGB values must be numbers");
	}
	rgb[0] = ft_atoi(sec[0]);
	rgb[1] = ft_atoi(sec[1]);
	rgb[2] = ft_atoi(sec[2]);
	free_lines(sec);
	valid_rgb(game, rgb[0]);
	valid_rgb(game, rgb[1]);
	valid_rgb(game, rgb[2]);
	*flag = 1;
}

