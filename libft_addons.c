#include "libft.h"

int	ft_isspace(int c)
{
	if (9 <= c && c <= 13 || c == 32)
		return (1);
	return (0);
}

int	ft_isntspace(int c)
{
	if (9 <= c && c <= 13 || c == 32)
		return (0);
	return (1);
}
