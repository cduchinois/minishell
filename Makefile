# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 15:50:42 by yuewang           #+#    #+#              #
#    Updated: 2024/01/31 21:25:53 by yuewang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## ARGUMENTS ###########

NAME	  = minishell
CC		  = cc
RLFLAG	  = -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline #compile line for Yue
# RLFLAG	  = -lreadline
CFLAG	  = -Wall -Wextra -Werror -v
INC_LIBFT = -I src/libft/
INC		  = -I inc/
RM		  = rm -f

########## SOURCES ###########

LIBFT_DIR 	= src/libft/
LIBFT		= $(LIBFT_DIR)libft.a

SRC_DIR    = src/
SRC_FILES = $(wildcard $(SRC_DIR)*.c) #wildcard to be changed to sources filenames
OBJ_DIR    = obj/
OBJ 	   = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

########## RULES ###########

all : $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME) $(LIBFT) $(RLFLAG)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAG) $(INC) $(INC_LIBFT) -c $< -o $@

clean :
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)

fclean_libft :
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean : clean fclean_libft
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re fclean_libft