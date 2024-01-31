########## ARGUMENTS ###########

NAME   = libft.a
CC     = cc
CFLAGS = -Wall -Wextra -Werror
INC	   = -I./inc/

########## SOURCES ###########

SRC_DIR	= src/

OBJ_DIR = obj/

SRC     = $(shell ls $(SRC_DIR)ft_is/*.c) \
          $(shell ls $(SRC_DIR)ft_mem/*.c) \
          $(shell ls $(SRC_DIR)ft_put/*.c) \
		  $(shell ls $(SRC_DIR)ft_to/*.c) \
		  $(shell ls $(SRC_DIR)ft_str/*.c) \
		  $(shell ls $(SRC_DIR)ft_lst/*.c) \
		  $(shell ls $(SRC_DIR)ft_printf/*.c) \
		  $(shell ls $(SRC_DIR)get_next_line/*.c) \



OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

########## COMMANDS ###########

AR=ar rcs
RM=rm -f

########## RULES ###########

all : $(NAME)

$(NAME) : $(OBJ) 
	$(AR) $@ $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re