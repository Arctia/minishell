/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arctia <arctia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 10:28:10 by arctia            #+#    #+#             */
/*   Updated: 2022/10/30 10:41:33 by arctia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_pow(int num, int n)
{
	long	res;

	if (num == 0)
		return (0);
	if (n == 0)
		return (1);
	res = num;
	n--;
	while (n-- > 0)
		res = res * num;
	return (res);
}
