/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtiutiun <rtiutiun@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 19:51:23 by mhouser           #+#    #+#             */
/*   Updated: 2017/12/06 12:58:47 by rtiutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void				freebufs(t_map *map)
{
	unsigned char	c;

	c = 0;
	while (map->buf[c])
		ft_memdel((void **)&map->buf[c++]);
	ft_memdel((void **)&map->buf);
	ft_memdel((void **)&map);
}

static void			printmap(t_map *map)
{
	unsigned char	r;

	r = 0;
	while (map && r < map->size)
	{
		ft_putchar(map->buf[r++], map->size);
		ft_putchar("\n", 1);
	}
	freebufs(map);
}

static void			findmnms(t_tet *tets)
{
	unsigned char	c;
	char			x;
	char			y;

	while (tets)
	{
		tets->mnm = (t_mm *)ft_malloc(sizeof(t_mm));
		tets->mnm->xmin = tets->xy[3][0];
		tets->mnm->ymin = tets->xy[3][1];
		tets->mnm->xmax = tets->mnm->xmin;
		tets->mnm->ymax = tets->mnm->ymin;
		c = 3;
		while (c--)
		{
			x = tets->xy[c][0];
			y = tets->xy[c][1];
			tets->mnm->xmax = (x > tets->mnm->xmax) ? x : tets->mnm->xmax;
			tets->mnm->xmin = (x < tets->mnm->xmin) ? x : tets->mnm->xmin;
			tets->mnm->ymax = (y > tets->mnm->ymax) ? y : tets->mnm->ymax;
			tets->mnm->ymin = (y < tets->mnm->ymin) ? y : tets->mnm->ymin;
		}
		tets->len = 1 + tets->mnm->ymax - tets->mnm->ymin;
		tets->wid = 1 + tets->mnm->xmax - tets->mnm->xmin;
		tets = tets->nxt;
	}
}

static void			trimtets(t_tet *tets)
{
	unsigned char	c;

	while (tets)
	{
		c = 4;
		while (c--)
		{
			tets->xy[c][0] += 4 - tets->mnm->xmax;
			tets->xy[c][1] += 4 - tets->mnm->ymax;
		}
		tets = tets->nxt;
	}
}

int					main(int argc, char **argv)
{
	int				fd;
	t_map			*map;
	t_tet			*tets;
	unsigned char	ntets[1];

	if (argc != 2)
		ft_putchar("usage: ./fillit target_file", 27);
	else if ((fd = open(argv[1], O_RDONLY)) != -1
			&& (tets = (t_tet *)ft_malloc(sizeof(t_tet)))
			&& validate(fd, tets, ntets))
	{
		findmnms(tets);
		trimtets(tets);
		map = tetsolve(tets, ntets);
		printmap(map);
		return (0);
	}
	else
		ft_putchar("error\n", 6);
	return (1);
}
