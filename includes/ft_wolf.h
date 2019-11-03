/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:24:58 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/03 12:58:03 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WOLF_H
# define FT_WOLF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <pthread.h>
# include "../libft/ft_printf/include/ft_printf.h"
# include <math.h>
# include "SDL.h"
# define WIDTH 1280
# define HEIGHT 720

typedef struct	s_coords
{
	int		x;
	int		y;
	int		z;
	int		texture;
	int		prev_z;
}				t_coords;

typedef	struct	s_wolf3d
{
	SDL_Window *win;
	SDL_Surface*screen_surface;
}				t_wolf3d;

t_coords		**parse_file(t_coords *size, char *filename);
void			free_splited(char **splited, int size);
int				split_len(char **splited);

t_wolf3d		*init_wolf3d(void);

void			print_error(char *message);
void			print_coords(t_coords **coords, int max_y, int max_x);

#endif
