/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:35:06 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/09 17:02:33 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	put_square(t_wolf3d *wolf3d, int x, int y, t_coords size)
{
	int i;
	int	j;
	int	color;

	i = y * size.y;
	color = 0x343434;
	if ((int)(wolf3d->player->x) == x && (int)(wolf3d->player->y) == y)
		color = 0xc70d3a;
	else if (wolf3d->coords[y][x].texture)
		color = 0x8f4426;
	while (i < (y + 1) * size.y)
	{
		j = WIDTH - 200 + x * size.x;
		while (j < WIDTH - 200 + (x + 1) * size.x)
		{
			put_pixel(wolf3d, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_wolf3d *wolf3d)
{
	int			x;
	int			y;
	t_coords	size;

	y = 0;
	size.x = 200 / (wolf3d->width);
	size.y = 200 / (wolf3d->height);
	while (y < wolf3d->height)
	{
		x = 0;
		while (x < wolf3d->width)
		{
			put_square(wolf3d, x, y, size);
			x++;
		}
		y++;
	}
}

void	draw_fps(t_wolf3d *wolf3d)
{
	SDL_Surface	*textsurface;
	SDL_Rect	textlocation;
	char		*fps;

	if (wolf3d->font)
	{
		fps = ft_itoa((int)(1 / wolf3d->frame));
		textsurface = TTF_RenderText_Solid(wolf3d->font, fps, wolf3d->fg);
		textlocation.x = 50;
		textlocation.y = 30;
		SDL_BlitSurface(textsurface, NULL, wolf3d->surf, &textlocation);
		ft_memdel((void **)&fps);
		SDL_FreeSurface(textsurface);
	}
}
