/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arctia <arctia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 09:58:04 by arctia            #+#    #+#             */
/*   Updated: 2022/07/09 10:14:52 by arctia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../libft.h"
#include "./../ft_printf.h"
#include <stdio.h>

void	print_y(t_pflags *tf)
{	
	static int	counter;
	char		*str;

	if (!counter)
		counter = 0;
	str = ft_itoa(counter);
	write(1, str, pf_strlen(str));
	write(1, ".", 1);
	tf->dimension += pf_strlen(str) + 1;
	counter++;
	free(str);
}
