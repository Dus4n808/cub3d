/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaroni <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:20:03 by lubaroni          #+#    #+#             */
/*   Updated: 2026/04/13 17:33:43 by lubaroni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** FIX: map path is now read from argv[1] instead of being hardcoded.
**      Also added return value and proper usage error message.
*/
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
