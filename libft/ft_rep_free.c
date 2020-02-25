#include "libft.h"

char	ft_rep_free(char ***args, char **str, size_t i)
{
	printf("1 - %p |%s|\n", (*args)[i], (*args)[i]);
	free((*args)[i]);
	(*args)[i] = (*str);
	return (1);
}
