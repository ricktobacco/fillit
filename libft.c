/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtiutiun <rtiutiun@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 19:51:23 by mhouser           #+#    #+#             */
/*   Updated: 2017/12/03 13:35:02 by rtiutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void				ft_putchar(char *c, unsigned char len)
{
	write(1, (unsigned char*)c, len);
}

void				ft_memdel(void **ap)
{
	if (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	int				i;

	i = 0;
	p = b;
	while (i < (int)len)
		p[i++] = (unsigned char)c;
	return (b);
}

void				*ft_malloc(size_t size)
{
	void			*alloc;

	if ((int)size < 0 || !size)
		return (0);
	alloc = malloc(size);
	if (alloc)
		ft_memset(alloc, 0, size);
	return (alloc ? alloc : 0);
}
