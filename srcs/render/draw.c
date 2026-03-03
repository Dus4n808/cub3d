/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:59:44 by dufama            #+#    #+#             */
/*   Updated: 2026/03/03 15:27:55 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*res;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGTH)
		return ;
	res = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)res = color;
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	floor;
	int	ceiling;

	floor = rgb_to_int(game->textures.floor[0], game->textures.floor[1], game->textures.floor[2]);
	ceiling = rgb_to_int(game->textures.ceiling[0], game->textures.ceiling[1], game->textures.ceiling[2]);
	y = 0;
	while (y < WIN_HEIGTH)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGTH / 2)
				put_pixel(&game->img, x, y, ceiling);
			else
				put_pixel(&game->img, x, y, floor);
			x++;
		}
		y++;
	}
}


