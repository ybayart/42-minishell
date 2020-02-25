#include "libft.h"

char	ft_rep_free(char ***args, char *str, size_t i)
{
	free((*args)[i]);
	(*args)[i] = ft_strdup(str);
	return (1);
}
