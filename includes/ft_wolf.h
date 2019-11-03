/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:24:58 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/03 18:23:59 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WOLF_H
# define FT_WOLF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <pthread.h>
# include "../libft/ft_printf/include/ft_printf.h"
# include <math.h>
# include <SDL2/SDL.h>
# define WIDTH 1280
# define HEIGHT 720
# define WALL_HEIGHT HEIGHT / 2
# define ROT 0.1

typedef struct	s_coords
{
	int		x;
	int		y;
	int		z;
	int		texture;
	int		prev_z;
}				t_coords;

typedef struct	s_player
{
	double		x;
	double		y;
	int			step_x;
	int			step_y;
	int			len_ray_x;
	int			len_ray_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		delta_x;
	double		delta_y;
}				t_player;

typedef	struct	s_wolf3d
{
	SDL_Window 	*win;
	SDL_Surface	*surf;
	int			width;
	int			height;
	t_coords	**coords;
	t_player	*player;
}				t_wolf3d;

t_coords		**parse_file(t_coords *size, char *filename);
void			free_splited(char **splited, int size);
int				split_len(char **splited);

t_player		*init_player(void);
t_wolf3d		*init_wolf3d(t_coords sizes, t_coords **coords);
int				main_loop(t_wolf3d *wolf3d);

void			draw_surf(t_wolf3d *wolf3d);
void			draw_surface(t_wolf3d *wolf3d);
void			draw_line(t_wolf3d *wolf3d, int x, t_coords line, int color);

void			print_error(char *message);
void			print_coords(t_coords **coords, int max_y, int max_x);

#endif
