NAME = minishell

HEADER = includes/minishell.h

SRC = 	minishell.c                   	\
		utils/functions/functions1.c  	\
		utils/functions/functions2.c  	\
		utils/functions/split.c       	\
		utils/functions/get_env_info.c  \
		utils/functions/split_two.c 	\
		utils/linked_list/ft_lists1.c 	\
		utils/linked_list/ft_lists2.c	\
		syntax/check_syntax.c			\
		parsing/token.c 			  	\
		pip/ft_utils.c				    \
		pip/ft_utils2.c 				\
		pip/gnl.c 						\
		pip/main_bonus.c 				\
		builtins/test_builtins.c 		\
		builtins/builtins_utils.c 		\
		builtins/ft_echo.c		 		\
		builtins/ft_pwd.c		 		\
		builtins/ft_env.c		 		\
		builtins/ft_exit.c		 		\
		builtins/ft_export.c		 	\


OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME)

clean : 
	@rm -f $(OBJ)

fclean : clean 
	@rm -rf $(NAME)

re : fclean all