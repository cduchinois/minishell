# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 15:50:42 by yuewang           #+#    #+#              #
#    Updated: 2024/04/19 21:12:06 by yuewang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## ARGUMENTS ###########

NAME	  = minishell
CC		  = cc -g #-fsanitize=address
CFLAG	  = -Wall -Wextra -Werror #-v 
LDFLAGS   = -lreadline
CPPFLAGS  = -I inc/ -I src/libft/ -I/usr/include/readline
INC_LIBFT = -I src/libft/
INC		  = -I inc/
RM		  = rm -f

########## SOURCES ###########

LIBFT_DIR 	= src/libft/
LIBFT		= $(LIBFT_DIR)libft.a

SRC_DIR    = src/
SRC_FILES = $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)execute/*.c) $(wildcard $(SRC_DIR)execute/built-in/*.c) $(wildcard $(SRC_DIR)parsing/*.c) $(wildcard $(SRC_DIR)signal/*.c)
 #wildcard to be changed to sources filenames
OBJ_DIR    = obj/
OBJ 	   = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

########## RULES ###########

all : $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) $(LIBFT)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)

fclean_libft :
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean : clean fclean_libft
	$(RM) $(NAME)

re : fclean all

leaks: all
	valgrind -s --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=del.supp  ./minishell

.PHONY : all clean fclean re fclean_libft