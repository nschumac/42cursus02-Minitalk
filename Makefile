NAME1 = server

NAME2 = client

CC = gcc
CFLAGS = -Wall -Werror -Wextra

FTPRINTF = ./42cursus01-Ft_printf

SERVERSOURCES =	sources/error.c				\
				sources/main_server.c		\

CLIENTSOURCES = sources/error.c				\
				sources/main_client.c		\

SERVEROBJECTS = $(SERVERSOURCES:.c=.o)

CLIENTOBJECTS = $(CLIENTSOURCES:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ -c $<

all: $(NAME1) $(NAME2)

$(NAME1): $(SERVEROBJECTS)
	@Make -s --directory=$(FTPRINTF)
	@$(CC) $(CFLAGS) $(SERVEROBJECTS) $(FTPRINTF)/libftprintf.a -o $(NAME1)
	@echo $(NAME1) Compiled!

$(NAME2): $(CLIENTOBJECTS)
	@Make -s --directory=$(FTPRINTF)
	@$(CC) $(CFLAGS) $(CLIENTOBJECTS) $(FTPRINTF)/libftprintf.a -o $(NAME2)
	@echo $(NAME2) Compiled!

clean:
	@make clean --directory=$(FTPRINTF)
	@rm -rf $(SERVEROBJECTS) $(CLIENTOBJECTS)

fclean: clean
	@make fclean --directory=$(FTPRINTF)
	@rm -rf $(NAME1) $(NAME2)

re: fclean all

