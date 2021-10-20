#include "../includes/includes.h"

static void	ft_sendstr(pid_t pid, char *str)
{
	int	c[2];

	ft_bzero(c, 2 * sizeof(int));
	while (++c[0])
	{
		c[1] = 0;
		while (++c[1] && c[1] <= 8)
		{
			usleep(80);
			if ((str[c[0] - 1] / ft_pow(2, c[1] - 1)) % 2)
			{
				if (kill(pid, SIGUSR1) == -1
					&& ft_printerror("Error\n[Process doesnt exist]"))
					return ;
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1
					&& ft_printerror("Error\n[Process doesnt exist]"))
					return ;
			}
		}
		if (str[c[0] - 1] == '\0')
			return ;
	}
}

static char	ft_strappend(char **str, unsigned char c)
{
	char				*buf;
	unsigned long		len;

	len = ft_strlen(*str);
	buf = (char *)calloc(len + 2, 1);
	if (!buf)
	{
		free(*str);
		return (0);
	}
	ft_strlcpy(buf, *str, len + 1);
	buf[len] = c;
	free(*str);
	*str = buf;
	return (1);
}

static void	ft_resetlistener(t_listener *listener, char str_only)
{
	if (str_only == 3)
	{
		listener->i_bitcount = 0;
		listener->i_char = 0;
	}
	else
	{
		if (!str_only)
		{
			ft_bzero(listener, sizeof(t_listener));
		}
		if (listener->str)
			free(listener->str);
		listener->str = (char *)calloc(1, 1);
		if (!listener->str)
			ft_printerror("Error\nMalloc Failed\n");
	}
}

void	ft_handler(int	sig)
{
	static t_listener	listener;

	if (!listener.str)
		ft_resetlistener(&listener, 0);
	if (sig == SIGUSR1)
		listener.i_char += ft_pow(2, listener.i_bitcount);
	listener.i_bitcount++;
	if (listener.i_bitcount == 8)
	{
		if (listener.i_char == 0)
		{
			if (!listener.i_pid)
				listener.i_pid = ft_atoi(listener.str);
			else
			{
				ft_putendl_fd(listener.str, 1);
				ft_sendstr(listener.i_pid, "[server] Communication Success!");
				listener.i_pid = 0;
			}
			ft_resetlistener(&listener, 1);
		}
		else
			ft_strappend(&listener.str, listener.i_char);
		ft_resetlistener(&listener, 3);
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("PID: %u\n", pid);
	sa.__sigaction_u.__sa_handler = ft_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (TRUE)
	{
		pause();
	}
}
