/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:36:34 by dufama            #+#    #+#             */
/*   Updated: 2026/03/03 15:55:10 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_e_w(t_player *player)
{
	if (player->dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->fov_x = 0;
		player->fov_y = 0.66;
	}
	else if (player->dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->fov_x = 0;
		player->fov_y = -0.66;
	}
}

void	init_player_pos(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->fov_x = 0.66;
		player->fov_y = 0;
	}
	else if (player->dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->fov_x = -0.66;
		player->fov_y = 0;
	}
	init_player_e_w(player);
}
