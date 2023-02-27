/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:05:53 by vgavioli          #+#    #+#             */
/*   Updated: 2022/02/04 13:51:02 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	h;

	c = 0;
	h = 0;
	while (src[h])
		h++;
	while (c < (dstsize - 1) && src[c] && dstsize != 0)
	{
		dst[c] = src[c];
		c++;
	}
	if (dstsize != 0)
		dst[c] = 0;
	return (h);
}
