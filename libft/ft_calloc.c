/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:44:59 by vgavioli          #+#    #+#             */
/*   Updated: 2022/01/30 15:45:03 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmem, size_t size)
{
	void	*ptr;

	ptr = malloc(nmem * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, (nmem * size));
	return (ptr);
}
