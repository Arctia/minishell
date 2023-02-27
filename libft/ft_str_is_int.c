/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arctia <arctia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 09:56:55 by arctia            #+#    #+#             */
/*   Updated: 2022/10/15 10:01:07 by arctia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is_int(const char *str)
{
	long	num;

	num = ft_atol(str);
	if (num > MAXINT || num < MININT)
		return (0);
	if (ft_issign(str[0]))
		str++;
	while (str++[0])
	{
		if (!ft_isdigit(str[-1]))
			return (0);
	}
	return (1);
}
