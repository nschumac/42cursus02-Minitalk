#ifndef INCLUDES_H
# define INCLUDES_H

# include <signal.h>
# include "../42cursus01-Ft_printf/ft_printf.h"

char	ft_printerror(const char	*error);
int		ft_pow(int base, int pow);

typedef struct s_listener
{
	int		i_char;
	int		i_bitcount;
	char	*str;
	pid_t	i_pid;
}				t_listener;

#endif