##
## EPITECH PROJECT, 2018
## makefile
## File description:
## makefile
##

SERVER		=	server

CLIENT		=	client

CC		=	gcc -g3

RM		=	rm -f

SRCS_SERVER	=	srcs/server/add_remove_chanel.c		\
			srcs/server/add_remove_init_channel.c	\
			srcs/server/add_remove_server.c		\
			srcs/server/add_remove_client.c		\
			srcs/server/add_remove_init_client.c 	\
			srcs/server/add_remove_file.c		\
			srcs/server/names.c			\
			srcs/server/tools.c			\
			srcs/server/user_users.c		\
			srcs/server/msg.c			\
			srcs/server/client.c			\
			srcs/server/join_part.c			\
			srcs/server/ping_pong_quit.c		\
			srcs/server/ping.c			\
			srcs/server/main.c			\
			srcs/server/reader.c			\
			srcs/server/server.c

SRCS_CLIENT	=	srcs/client/main.c

SRCS 		=	srcs/fd.c				\
			srcs/ip.c				\
			srcs/array.c				\
			srcs/free_secur.c			\
			srcs/linkedlist.c			\
			srcs/my_strncmp.c			\
			srcs/getter.c				\
			srcs/deleter.c				\
			srcs/signal.c				\
			srcs/socket.c

OBJS 		=	$(SRCS:.c=.o)

OBJS_SERVER	=	$(SRCS_SERVER:.c=.o)

OBJS_CLIENT	=	$(SRCS_CLIENT:.c=.o)

CFLAGS		=	-I include

CFLAGS		+=	-W -Wall -Wextra

LDFLAGS 	=

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 34s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 36s\n" $< | tr ' ' '.'

all: 		$(SERVER)

$(SERVER):	$(OBJS) $(OBJS_SERVER) $(OBJS_CLIENT)
		@$(CC) $(OBJS) $(OBJS_SERVER) -o $(SERVER) $(LDFLAGS) && \
		(printf "[\033[1;36mbuilt\033[0m] % 37s\n" $(SERVER) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 36s\n" $(SERVER) | tr ' ' '.') && \
		$(CC) $(OBJS) $(OBJS_CLIENT) -o $(CLIENT) $(LDFLAGS) && \
		printf "[\033[1;36mbuilt\033[0m] % 37s\n" $(CLIENT) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 36s\n" $(CLIENT) | tr ' ' '.'


clean:
		@$(RM) $(OBJS_CLIENT) && \
		(printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(OBJS_CLIENT) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(OBJS_CLIENT) | tr ' ' '.') && \
		$(RM) $(OBJS) && \
		(printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(OBJS) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(OBJS) | tr ' ' '.') && \
		$(RM) $(OBJS_SERVER) && \
		(printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(OBJS_SERVER) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(OBJS_SERVER) | tr ' ' '.')

fclean: 	clean
		@$(RM) $(SERVER) && \
		(printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(SERVER) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(SERVER) | tr ' ' '.') && \
		$(RM) $(CLIENT) && \
		(printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(CLIENT) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 35s\n" $(CLIENT) | tr ' ' '.')

re:		fclean all

.PHONY: 	all clean fclean re
