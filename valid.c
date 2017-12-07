/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtiutiun <rtiutiun@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 19:51:23 by mhouser           #+#    #+#             */
/*   Updated: 2017/12/06 12:52:21 by rtiutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char				havehash(char tet[4][2], char y, char x, char flag)
{
	unsigned char	c;

	c = 0;
	if (flag)
	{
		y = (flag == UP) ? y + 1 : y;
		y = (flag == DN) ? y - 1 : y;
		x = (flag == LT) ? x + 1 : x;
		x = (flag == RT) ? x - 1 : x;
	}
	while (c < 4)
	{
		if (y == tet[c][1] && tet[c][0] == x)
			return (1);
		c++;
	}
	return (0);
}

static char			check(char tet[4][2], char y, char x, char *flags)
{
	char			checks;

	checks = 0;
	while (*flags)
		checks += havehash(tet, y, x, *flags++);
	return (checks);
}

static char			isvalid(char tet[4][2])
{
	unsigned char	c;
	unsigned char	cksm;
	char			*flag;
	char			flags[5];

	c = 0;
	cksm = 0;
	while (c < 4)
	{
		ft_memset(flags, 0, 5);
		flag = flags;
		if (tet[c][1] != 4)
			*flag++ = UP;
		if (tet[c][1] != 1)
			*flag++ = DN;
		if (tet[c][0] != 4)
			*flag++ = LT;
		if (tet[c][0] != 1)
			*flag++ = RT;
		cksm += check(tet, tet[c][1], tet[c][0], flags);
		c++;
	}
	return (cksm == 6 || cksm == 8);
}

static void			checkall(t_tet **tets, unsigned char *ntets,
													char *cyx, short *cksm)
{
	if ((*cksm == 742) && ((*tets)->nxt = (t_tet *)ft_malloc(sizeof(t_tet))))
	{
		*cksm = 0;
		*tets = (*tets)->nxt;
	}
	if ((*cksm = (*cksm > 742 || *cksm == 742) ? -1 : *cksm) > -1)
	{
		if (cyx[0] == '#' && (*cksm += '#'))
		{
			(*tets)->xy[*ntets % 4][1] = cyx[1];
			(*tets)->xy[*ntets % 4][0] = cyx[2];
			if (((*tets)->val = !(++*ntets % 4) ? 'A' + (*ntets / 4) - 1 : 0))
				*cksm = (isvalid((*tets)->xy)) ? *cksm : -1;
		}
		else if (cyx[0] == '\n' && (*cksm += '\n'))
		{
			*cksm = (cyx[2] && cyx[1] < 4 && 4 > cyx[2]) ? -1 : *cksm;
			cyx[1] = (!cyx[2]) ? cyx[1] - 1 : cyx[1];
		}
		else
			*cksm = (cyx[0] == '.') ? *cksm + '.' : -1;
		cyx[1] = (cyx[1]) ? cyx[1] : 4;
		cyx[2] = (cyx[0] == '\n') ? 4 : cyx[2] - 1;
	}
}

char				validate(int fd, t_tet *tets, unsigned char *ntets)
{
	t_tet			**tet;
	short			*cksm;
	char			cyx[3];

	*ntets = 0;
	if ((cksm = (short *)ft_malloc(sizeof(short)))
		&& (tet = (t_tet **)ft_malloc(sizeof(t_tet *))))
	{
		cyx[1] = 4;
		cyx[2] = 4;
		*tet = tets;
		while (*cksm > -1 && read(fd, cyx, 1))
			checkall(tet, ntets, cyx, cksm);
		*ntets = (*cksm == (742 - '\n')) ?
		*ntets / 4 : 0;
		ft_memdel((void **)&cksm);
	}
	return (close(fd) != -1 && *ntets && *ntets < 27);
}
