/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:55:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/06 17:37:50 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	put_pixel(t_wolf3d *wolf3d, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		((int *)wolf3d->surf->pixels)[(y * wolf3d->surf->w) + x] = color;

}

void	choose_direction_flr(t_dcoords *flr, double ray_x, double ray_y, t_coords map, double dist_without_fixing)
{
	if (!map.z && ray_x > 0)
	{
		flr->x = map.x;
		flr->y = map.y + dist_without_fixing;
	}
	else if (!map.z && ray_x < 0)
	{
		flr->x = map.x + 1.0;
		flr->y = map.y + dist_without_fixing;
	}
	else if (map.z && ray_y > 0)
	{
		flr->x = map.x + dist_without_fixing;
		flr->y = map.y;
	}
	else
	{
		flr->x = map.x + dist_without_fixing;
		flr->y = map.y + 1.0;
	}
}

void	draw_floor(t_wolf3d *wolf3d, double ray_x, double ray_y, double dist, int y_end, t_coords map, double dist_without_fixing, int x)
{
	int			y;
	t_coords	cube;
	t_dcoords	dists;
	t_dcoords	flr;
	t_dcoords	cur;

	choose_direction_flr(&flr, ray_x, ray_y, map, dist_without_fixing);
	dists.x = dist;
	dists.y = 0;
	y = y_end;
	while (y < HEIGHT)
	{
		cur.z = HEIGHT / (2.0 * y - HEIGHT);
		cur.z = (cur.z - dists.y) / (dists.x - dists.y);
		cur.x =  cur.z * flr.x + (1.0 - cur.z) * wolf3d->player->x;
		cur.y =  cur.z * flr.y + (1.0 - cur.z) * wolf3d->player->y;
		cube.x = (int)(cur.x * 64) % 64;
		cube.y = (int)(cur.y * 64) % 64;
		// ft_printf("cube x = %i y = %i\n", cube.x, cube.y);
		put_pixel(wolf3d, x, y, ((int *)wolf3d->textures[4]->pixels)[64 * cube.y + cube.x]);
		put_pixel(wolf3d, x, HEIGHT - y, ((int *)wolf3d->textures[2]->pixels)[64 * cube.y + cube.x]);
		y++;
	}
	// exit(0);
}

void	draw_textures(t_wolf3d *wolf3d, int x, t_coords line, int lineheight)
{
	int 			y;
	int				calc_dist;
	int				fixed_y;
	unsigned int	color;

	y = line.x;
	while (y < line.y)
	{
		calc_dist = (y << 8) - (HEIGHT << 7) + (lineheight << 7);
		fixed_y = ((calc_dist << 6) / lineheight) >> 8;
		color = ((int *)wolf3d->textures[line.texture]->pixels)[(fixed_y << 6) + line.z];
		put_pixel(wolf3d, x, y, color);
		y++;
	}
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
