/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtiutiun <rtiutiun@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 19:51:23 by mhouser           #+#    #+#             */
/*   Updated: 2017/12/06 12:53:58 by rtiutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define UP 1
# define DN 2
# define LT 3
# define RT 4

typedef struct		s_mnm
{
	char			xmax;
	char			ymax;
	char			xmin;
	char			ymin;
}					t_mm;

typedef struct		s_tet
{
	struct s_tet	*nxt;
	t_mm			*mnm;
	unsigned char	len;
	unsigned char	wid;
	char			xy[4][2];
	char			val;
}					t_tet;

typedef struct		s_map
{
	unsigned char	size;
	char			**buf;
}					t_map;

void				freebufs(t_map *map);
void				ft_memdel(void **ap);
void				*ft_malloc(size_t size);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar(char *c, unsigned char len);
t_map				*tetsolve(t_tet *tets, unsigned char *ntets);
char				havehash(char tet[4][2], char y, char x, char flag);
char				validate(int fd, t_tet *tets, unsigned char *ntets);

#endif
