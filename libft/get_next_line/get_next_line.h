/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:05:14 by vgavioli          #+#    #+#             */
/*   Updated: 2022/06/20 15:05:56 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		line_len_n(char *str);
size_t	gnl_strlen(char *str);
char	*free_buffer(char *buffer);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strchr(char *s, int c);

#endif