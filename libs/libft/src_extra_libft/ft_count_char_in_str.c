#include "libft.h"

int	ft_count_char_in_str(char *str, char c)
{
	int	count;

	count = 0;
	if (!str)
		return (count);
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
