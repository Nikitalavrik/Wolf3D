/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:24:58 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/09 17:15:13 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WOLF_H
# define FT_WOLF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <pthread.h>
# include "../libft/ft_printf/include/ft_printf.h"
# include <math.h>
# include <time.h>
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"

# define NUMBER_OF_TEXTURES 9
# define WIDTH 1280
# define HEIGHT 720
# define WALL_HEIGHT HEIGHT
# define WALL_HALF_HEIGHT HEIGHT / 2
# define ROT 0.1
# define MOUSE_SPEED 8

typedef struct	s_dcoords
{
	double		x;
	double		y;
	double		z;
}				t_dcoords;

typedef struct	s_coords
{
	int			x;
	int			y;
	int			z;
	int			texture;
	int			prev_z;
}				t_coords;

typedef struct	s_player
{
	double		x;
	double		y;
	int			step_x;
	int			step_y;
	double		len_ray_x;
	double		len_ray_y;
	double		dir_x;
	double		dir_y;
	double		ray_x;
	double		ray_y;
	double		plane_x;
	double		plane_y;
	double		delta_x;
	double		delta_y;
}				t_player;

typedef	struct	s_wolf3d
{
	TTF_Font	*font;
	SDL_Color	fg;
	SDL_Window	*win;
	SDL_Surface	*surf;
	int			width;
	int			height;
	t_coords	**coords;
	t_player	*player;
	double		frame;
	int			xrel;
	SDL_Surface	*textures[9];
	double		speed;
	int			txt;
	int			x;
}				t_wolf3d;

int				check_file(int fd);
t_coords		**parse_file(t_coords *size, char *filename);
void			free_splited(char **splited, int size);
int				split_len(char **splited);

t_player		*init_player(t_coords **coords, t_coords size);
t_wolf3d		*init_wolf3d(t_coords sizes, t_coords **coords);
int				main_loop(t_wolf3d *wolf3d);

int				detect_event(t_wolf3d *wolf3d);
void			move_up_down(t_wolf3d *wolf3d, double f(double, double));
double			sub_double(double number1, double number2);
double			add_double(double number1, double number2);

void			load_textures(t_wolf3d *wolf3d);

void			put_pixel(t_wolf3d *wolf3d, int x, int y, int color);
void			draw_fps(t_wolf3d *wolf3d);
void			draw_minimap(t_wolf3d *wolf3d);
void			draw_surface(t_wolf3d *wolf3d);
void			draw_line(t_wolf3d *wolf3d, int x, t_coords line, int color);
void			draw_textures(t_wolf3d *wolf3d, t_coords line,
													int lineheight, int side);
void			draw_floor(t_wolf3d *wolf3d, t_dcoords dist,
													t_coords map, int x);

void			print_error(char *manage, char *message);
void			print_coords(t_coords **coords, int max_y, int max_x);

#endif
