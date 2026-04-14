/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:20:03 by lubaroni          #+#    #+#             */
/*   Updated: 2026/04/14 16:39:33 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	parse_file(&game, argv[1]);
	map_is_playable(&game);
	init_player_pos(&game.player);
	init_game(&game);
	render(&game);
	mlx_loop(game.mlx);
	free_element(&game);
	return (0);
}
