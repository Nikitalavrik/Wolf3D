/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/09 17:14:23 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

void	rot_by_angl(t_wolf3d *wolf3d, double angl)
{
	double	tmp_dir_x;
	double	tmp_plane_x;

	tmp_dir_x = wolf3d->player->dir_x;
	wolf3d->player->dir_x = wolf3d->player->dir_x * cos(angl) -\
	wolf3d->player->dir_y * sin(angl);
	wolf3d->player->dir_y = tmp_dir_x * sin(angl) +\
	wolf3d->player->dir_y * cos(angl);
	tmp_plane_x = wolf3d->player->plane_x;
	wolf3d->player->plane_x = wolf3d->player->plane_x * cos(angl) -\
	wolf3d->player->plane_y * sin(angl);
	wolf3d->player->plane_y = tmp_plane_x * sin(angl) +\
	wolf3d->player->plane_y * cos(angl);
}

void	mouse_event(t_wolf3d *wolf3d, SDL_Event event)
{
	if ((wolf3d->xrel > 0 && event.motion.xrel > 0) ||\
	(wolf3d->xrel < 0 && event.motion.xrel < 0))
		wolf3d->xrel = 0;
	if (event.motion.xrel < 400 && event.motion.xrel > -400)
		rot_by_angl(wolf3d, -wolf3d->frame * event.motion.xrel / MOUSE_SPEED);
}

int		keyboard_events(t_wolf3d *wolf3d, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
		move_up_down(wolf3d, add_double);
	if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
		move_up_down(wolf3d, sub_double);
	if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
		rot_by_angl(wolf3d, wolf3d->frame * 3);
	if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
		rot_by_angl(wolf3d, -wolf3d->frame * 3);
	if (event.key.keysym.sym == SDLK_h && event.type != SDL_KEYUP)
		wolf3d->txt = wolf3d->txt ? 0 : 1;
	if (event.key.keysym.sym == SDLK_LSHIFT)
		wolf3d->speed = wolf3d->speed == 0.05 ? 0.1 : 0.05;
	return (0);
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
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			if (keyboard_events(wolf3d, event))
				return (1);
		}
	}
	return (0);
}
