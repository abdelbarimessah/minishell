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
		builtins/ft_cd.c		 		\
		builtins/ft_sig.c		 		\
		builtins/ft_unset.c		 		\
		builtins/ft_ctrl_d.c		 	\


OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = "-L/goinfre/amessah/.brew/opt/readline/lib"

CPPFLAGS = "-I/goinfre/amessah/.brew/opt/readline/include"

CC = cc

all : $(NAME)
	@echo "\n███████████████████████ minishell ███████████████████████\n"

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -lreadline -lncurses $(OBJ) -o $(NAME) $(LDFLAGS) $(CPPFLAGS)

clean : 
	@rm -f $(OBJ)

fclean : clean 
	@rm -rf $(NAME)

re : fclean all