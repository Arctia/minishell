/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arctia <arctia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 10:32:17 by arctia            #+#    #+#             */
/*   Updated: 2022/10/30 10:46:49 by arctia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(long num)
{
	int	res;
	int	n;

	n = 0;
	while (n < MAXINT || n > num / 2)
	{
		res = ft_pow(n, 2);
		if (res == num)
			return (res);
		else if (res > num)
			return (-1);
		n++;
	}
	return (-1);
}
