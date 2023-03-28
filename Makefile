# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsantama <fsantama@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 13:37:38 by fsantama          #+#    #+#              #
#    Updated: 2023/03/28 18:58:30 by fsantama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================================================================#
#                        	GENERAL CONFIG & FLAGS                             #
# =============================================================================#

# PROGRAM FOR COMPILING C PROGRAMS

CC = gcc

CFLAGS = -Werror -Wall -Wextra

NAME_SERVER = server
SERVER_SRCS = server.c

NAME_CLIENT = client
CLIENT_SRCS = client.c

NAME_SERVER_BONUS = server_bonus
SERVER_SRCS_BONUS = server_bonus.c

NAME_CLIENT_BONUS = client_bonus
CLIENT_SRCS_BONUS = client_bonus.c

all : $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_CLIENT) : $(CLIENT_SRCS)
	@$(CC) $(CLIENT_SRCS) -o $(NAME_CLIENT)
	@printf "\e[32m$@ built🗣\e[0m\n"

$(NAME_SERVER) : $(SERVER_SRCS)
	@$(CC) $(SERVER_SRCS) -o $(NAME_SERVER)
	@printf "\e[32m$@ built✔\e[0m\n"

%.o : %.c
	@$(CC) $(CFLAGS) $< -c

clean :
	@rm -f client.o server.o client_bonus.o server_bonus.o
	@printf "\e[31mclean done\e[0m\n"

fclean : clean
	@rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	@printf "\e[31mfclean done\e[0m\n"

re : fclean all

bonus : $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_CLIENT_BONUS) : $(CLIENT_SRCS_BONUS)
	@$(CC) $(CLIENT_SRCS_BONUS) -o $(NAME_CLIENT_BONUS)
	@printf "\e[32m$@ built🗣 \e[0m\n"

$(NAME_SERVER_BONUS) : $(SERVER_SRCS_BONUS)
	@$(CC) $(SERVER_SRCS_BONUS) -o $(NAME_SERVER_BONUS)
	@printf "\e[32m$@ built✔\e[0m\n"

.PHONY: all clean fclean re bonus
