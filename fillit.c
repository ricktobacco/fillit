/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtiutiun <rtiutiun@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 19:51:23 by mhouser           #+#    #+#             */
/*   Updated: 2017/12/06 02:48:50 by rtiutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void			put(t_map *map, t_tet *tet, unsigned char rc[2])
{
	unsigned char	y;
	unsigned char	x;
	unsigned char	r;
	unsigned char	c;
	char			ch;

	r = rc[0];
	c = rc[1];
	y = 5;
	while (--y > (4 - tet->len))
	{
		x = 5;
		while (--x > (4 - tet->wid))
		{
			if (havehash(tet->xy, y, x, 0))
			{
				ch = (map->buf[r][c] != '.') ? '.' : tet->val;
				map->buf[r][c] = ch;
			}
			c++;
		}
		c -= tet->wid;
		r++;
	}
}

static char			canput(t_map *map, t_tet *tet, unsigned char rc[2])
{
	unsigned char	y;
	unsigned char	x;
	unsigned char	r;
	unsigned char	c;

	r = rc[0];
	c = rc[1];
	if (tet->len + r > map->size || map->size < c + tet->wid)
		return (0);
	y = 5;
	while (--y > (4 - tet->len))
	{
		x = 5;
		while (--x > (4 - tet->wid))
		{
			if (map->buf[r][c] != '.'
				&& havehash(tet->xy, y, x, 0))
				return (0);
			c++;
		}
		c -= tet->wid;
		r++;
	}
	return (1);
}

static t_map		*fillmap(t_map *map, t_tet *tet)
{
	unsigned char	rc[2];

	if (tet)
	{
		rc[0] = 0;
		while ((1 + map->size - tet->len) > rc[0])
		{
			rc[1] = 0;
			while ((1 + map->size - tet->wid) > rc[1])
			{
				if (canput(map, tet, rc))
				{
					put(map, tet, rc);
					if (fillmap(map, tet->nxt))
						return (map);
					else
						put(map, tet, rc);
				}
				rc[1]++;
			}
			rc[0]++;
		}
		return (NULL);
	}
	return (map);
}

static t_map		*mapmaker(unsigned char s)
{
	t_map			*map;

	if ((map = (t_map *)ft_malloc(sizeof(t_map))))
		if ((map->buf = (char **)ft_malloc(sizeof(char *) * (s + 1))))
		{
			map->size = s;
			while (s--)
			{
				if ((map->buf[s] = (char *)ft_malloc(map->size)))
					ft_memset(map->buf[s], '.', map->size);
				else
				{
					freebufs(map);
					break ;
				}
			}
			return (map);
		}
	ft_memdel((void **)&map);
	return (NULL);
}

t_map				*tetsolve(t_tet *tets, unsigned char *ntets)
{
	unsigned char	size;
	t_map			*map;
	t_tet			*tet;

	size = 2;
	tet = tets;
	while (4 * (*ntets) > size * size)
		size++;
	while (!fillmap(map = mapmaker(size++), tets))
		freebufs(map);
	tets = tet;
	while (tets)
	{
		tet = tets->nxt;
		ft_memdel((void **)&tets->mnm);
		ft_memdel((void **)&tets);
		tets = tet;
	}
	return (map);
}
