/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaroni <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 09:36:51 by lubaroni          #+#    #+#             */
/*   Updated: 2026/04/14 14:11:00 by lubaroni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_fov_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED)
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ game->player.dir_y * cos(-ROT_SPEED);
	old_fov_x = game->player.fov_x;
	game->player.fov_x = game->player.fov_x * cos(-ROT_SPEED)
		- game->player.fov_y * sin(-ROT_SPEED);
	game->player.fov_y = old_fov_x * sin(-ROT_SPEED)
		+ game->player.fov_y * cos(-ROT_SPEED);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_fov_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED)
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED)
		+ game->player.dir_y * cos(ROT_SPEED);
	old_fov_x = game->player.fov_x;
	game->player.fov_x = game->player.fov_x * cos(ROT_SPEED)
		- game->player.fov_y * sin(ROT_SPEED);
	game->player.fov_y = old_fov_x * sin(ROT_SPEED)
		+ game->player.fov_y * cos(ROT_SPEED);
}
