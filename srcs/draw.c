/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:55:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/03 16:32:13 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	put_pixel(t_wolf3d *wolf3d, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		((int *)wolf3d->surf->pixels)[(y * wolf3d->surf->w) + x] = color;

}

void	draw_line(t_wolf3d *wolf3d, int x, t_coords line, int color)
{
	int y;

	y = line.x;
	while (y < line.y)
	{
		put_pixel(wolf3d, x, y, color);
		y++;
	}
}

void	draw_surf(t_wolf3d *wolf3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < wolf3d->height + 200)
	{
		x = 0;
		while (x < wolf3d->width + 200)
		{
			put_pixel(wolf3d, x, y, 0x087f23);
			x++;
		}
		y++;
	}
}
