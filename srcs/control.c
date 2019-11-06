/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/06 19:29:47 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void      rot_by_angl(t_wolf3d *wolf3d, double angl)
{
    double tmp_dir_x;
	double tmp_plane_x;

    tmp_dir_x = wolf3d->player->dir_x;
    wolf3d->player->dir_x = wolf3d->player->dir_x * cos(angl) - wolf3d->player->dir_y * sin(angl);
    wolf3d->player->dir_y = tmp_dir_x * sin(angl) + wolf3d->player->dir_y * cos(angl);
    tmp_plane_x = wolf3d->player->plane_x;
    wolf3d->player->plane_x = wolf3d->player->plane_x * cos(angl) - wolf3d->player->plane_y * sin(angl);
    wolf3d->player->plane_y  = tmp_plane_x * sin(angl) + wolf3d->player->plane_y * cos(angl);
}

void        move_up_down(t_wolf3d *wolf3d, int direction)
{
	t_coords	map;
	t_coords	dir;
	t_dcoords	tmp;

	map.x = floor(wolf3d->player->x);
	map.y = floor(wolf3d->player->y);
    dir.x = floor(wolf3d->player->dir_x);
	dir.y = floor(wolf3d->player->dir_y);
	if (direction)
	{
		tmp.x = wolf3d->player->x + wolf3d->player->dir_x * wolf3d->frame * 5 + 0.5;
		if (!wolf3d->coords[map.y][(int)floor(tmp.x)].texture)
			wolf3d->player->x = tmp.x;
		tmp.y = wolf3d->player->y + wolf3d->player->dir_y * wolf3d->frame * 5 + 0.5;
		if (!wolf3d->coords[(int)floor(tmp.y)][map.x].texture)
			wolf3d->player->y = tmp.y;
		// ft_printf("x = %f\n", wolf3d->player->x);
        // if (wolf3d->coords[map.y][map.x].texture == 0)
        //     if (wolf3d->player->x + (wolf3d->player->dir_x * wolf3d->frame * 5) > 1.1 &&\
		// 	   wolf3d->player->x + (wolf3d->player->dir_x * wolf3d->frame * 5) < wolf3d->width - 1.1)
		// 		wolf3d->player->x += (wolf3d->player->dir_x * wolf3d->frame * 5);
        // if (wolf3d->coords[map.y][map.x].texture == 0)
		// 	if (wolf3d->player->y + wolf3d->player->dir_y * wolf3d->frame * 5 > 1.1 &&\
		// 		wolf3d->player->y + wolf3d->player->dir_y * wolf3d->frame * 5 < wolf3d->height - 1.1)
        //     	wolf3d->player->y += wolf3d->player->dir_y * wolf3d->frame * 5;
		// ft_printf("after x = %f y = %f map x = %i y = %i\n",  wolf3d->player->x, wolf3d->player->y,
		// 													map.x, map.y);
	}
    else
	{
        if (map.x && wolf3d->coords[map.y][map.x - 1].texture == 0)
			if (wolf3d->player->x - (wolf3d->player->dir_x * wolf3d->frame * 5) > 1.1)
            	wolf3d->player->x -= wolf3d->player->dir_x * wolf3d->frame * 5;
        if (map.y && wolf3d->coords[map.y - 1][map.x].texture == 0)
			if (wolf3d->player->y - wolf3d->player->dir_y * wolf3d->frame * 5 > 1.1)
          		wolf3d->player->y -= wolf3d->player->dir_y * wolf3d->frame * 5;
	}
}

void		mouse_event(t_wolf3d *wolf3d, SDL_Event event)
{
	// ft_printf("wol %i xrel %i\n", wolf3d->xrel, event.motion.xrel);
	if ((wolf3d->xrel > 0 && event.motion.xrel > 0) || (wolf3d->xrel < 0 && event.motion.xrel < 0))
		wolf3d->xrel = 0;
	if (event.motion.xrel < 400 && event.motion.xrel > -400)
	{
		rot_by_angl(wolf3d, -wolf3d->frame * (event.motion.xrel + wolf3d->xrel) / (MOUSE_SPEED + wolf3d->xrel));
		if (event.motion.x > WIDTH - 3 || event.motion.x < 3)
		{
			SDL_WarpMouseInWindow(wolf3d->win, WIDTH / 2, HEIGHT / 2);
			wolf3d->xrel = event.motion.xrel;
		}
	}

}

int		detect_event(t_wolf3d *wolf3d)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (event.type == SDL_MOUSEMOTION)
			mouse_event(wolf3d, event);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return (1);
			if (event.key.keysym.sym == SDLK_UP)
				move_up_down(wolf3d, 1);
			if (event.key.keysym.sym == SDLK_DOWN)
				move_up_down(wolf3d, 0);
			if (event.key.keysym.sym == SDLK_LEFT)
				rot_by_angl(wolf3d, wolf3d->frame * 3);
			if (event.key.keysym.sym == SDLK_RIGHT)
				rot_by_angl(wolf3d, -wolf3d->frame * 3);
		}
	}
	return (0);
}
