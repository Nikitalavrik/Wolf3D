/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:55:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/09 17:29:55 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	put_pixel(t_wolf3d *wolf3d, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		((int *)wolf3d->surf->pixels)[(y * wolf3d->surf->w) + x] = color;
}

void	choose_direction_flr(t_player *player, t_dcoords *flr, t_coords map,
													double dist_without_fixing)
{
	if ((!map.z || map.z == 2) && player->ray_x > 0)
	{
		flr->x = map.x;
		flr->y = map.y + dist_without_fixing;
	}
	else if ((!map.z || map.z == 2) && player->ray_x < 0)
	{
		flr->x = map.x + 1.0;
		flr->y = map.y + dist_without_fixing;
	}
	else if ((map.z == 1 || map.z == 3) && player->ray_y > 0)
	{
		flr->x = map.x + dist_without_fixing;
		flr->y = map.y;
	}
	else if ((map.z == 1 || map.z == 3))
	{
		flr->x = map.x + dist_without_fixing;
		flr->y = map.y + 1.0;
	}
}

void	draw_floor(t_wolf3d *wolf3d, t_dcoords dist, t_coords map, int end)
{
	int			y;
	t_coords	cube;
	t_dcoords	dists;
	t_dcoords	flr;
	t_dcoords	cur;

	choose_direction_flr(wolf3d->player, &flr, map, dist.y);
	dists.x = dist.x;
	dists.y = 0;
	y = end;
	while (y < HEIGHT)
	{
		cur.z = HEIGHT / (2.0 * y - HEIGHT);
		cur.z = (cur.z - dists.y) / (dists.x - dists.y);
		cur.x = cur.z * flr.x + (1.0 - cur.z) * wolf3d->player->x;
		cur.y = cur.z * flr.y + (1.0 - cur.z) * wolf3d->player->y;
		cube.x = (int)(cur.x * 64) % 64;
		cube.y = (int)(cur.y * 64) % 64;
		put_pixel(wolf3d, wolf3d->x, y,
		((int *)wolf3d->textures[1]->pixels)[64 * cube.y + cube.x]);
		put_pixel(wolf3d, wolf3d->x, HEIGHT - y,
		((int *)wolf3d->textures[5]->pixels)[64 * cube.y + cube.x]);
		y++;
	}
}

void	draw_textures(t_wolf3d *wolf3d, t_coords line, int lineheight, int side)
{
	int				y;
	int				calc_dist;
	int				fix_y;
	unsigned int	color;

	y = line.x;
	while (y < line.y)
	{
		calc_dist = (y << 8) - (HEIGHT << 7) + (lineheight << 7);
		fix_y = ((calc_dist << 6) / lineheight) >> 8;
		if (!side)
			color = ((int *)wolf3d->textures[line.texture]->pixels)[\
			(fix_y << 6) + line.z];
		else if (side == 1)
			color = ((int *)wolf3d->textures[2]->pixels)[(fix_y << 6) + line.z];
		else if (side == 2)
			color = ((int *)wolf3d->textures[3]->pixels)[(fix_y << 6) + line.z];
		else if (side == 3)
			color = ((int *)wolf3d->textures[7]->pixels)[(fix_y << 6) + line.z];
		put_pixel(wolf3d, wolf3d->x, y, color);
		y++;
	}
}

void	draw_line(t_wolf3d *wolf3d, int x, t_coords line, int side)
{
	int y;
	int color;

	color = 0x1b2a49;
	if (side == 1)
		color = 0x465881;
	else if (side == 2)
		color = 0x00909e;
	else if (side == 3)
		color = 0xc9d1d3;
	y = line.x;
	while (y < line.y)
	{
		put_pixel(wolf3d, x, y, color);
		y++;
	}
}
