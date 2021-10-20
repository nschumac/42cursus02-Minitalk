#include "../includes/includes.h"

char	ft_printerror(const char	*error)
{
	write(2, error, ft_strlen(error));
	exit(0);
	return (1);
}

int	ft_pow(int base, int pow)
{
	int	ret;

	ret = 1;
	while (pow--)
		ret *= base;
	return (ret);
}
