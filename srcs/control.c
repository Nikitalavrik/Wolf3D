
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
    if (direction)
	{
        if (wolf3d->coords[(int)wolf3d->player->y][(int)wolf3d->player->x + 1].texture == 0)
            wolf3d->player->x += wolf3d->player->dir_x;
        if (wolf3d->coords[(int)wolf3d->player->y + 1][(int)wolf3d->player->x].texture == 0)
            wolf3d->player->y += wolf3d->player->dir_y;
	}
    else
	{
        if (wolf3d->coords[(int)wolf3d->player->y][(int)wolf3d->player->x - 1].texture == 0)
            wolf3d->player->x -= wolf3d->player->dir_x;
        if (wolf3d->coords[(int)wolf3d->player->y - 1][(int)wolf3d->player->x].texture == 0)
            wolf3d->player->y -= wolf3d->player->dir_y;
	}
}

int		detect_event(t_wolf3d *wolf3d)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return (0);
			if (event.key.keysym.sym == SDLK_UP)
				move_up_down(wolf3d, 1);
			if (event.key.keysym.sym == SDLK_DOWN)
				move_up_down(wolf3d, 0);
			if (event.key.keysym.sym == SDLK_LEFT)
				rot_by_angl(wolf3d, ROT);
			if (event.key.keysym.sym == SDLK_RIGHT)
				rot_by_angl(wolf3d, -ROT);
		}
	}
	return (0);
}
