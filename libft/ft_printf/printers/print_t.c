/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arctia <arctia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:41:12 by arctia            #+#    #+#             */
/*   Updated: 2022/07/10 12:27:42 by arctia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

void	print_t(t_pflags *tf)
{	
	char	*code;

	code = INF;
	if (tf->length != 0)
		tf->dimension--;
	if (tf->length == 1)
		code = ERR;
	else if (tf->length == 2)
		code = SIG;
	else if (tf->length == 3)
		code = WAR;
	write(1, code, pf_strlen(code));
	tf->dimension += pf_strlen(code);
}
