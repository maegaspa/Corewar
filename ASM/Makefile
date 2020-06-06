.PHONY: all clean fclean re

NAME = asm
CC = gcc
DEBUG = -fsanitize=address
FLAGS = -Wall -Wextra -g
INC = include/asm.h
HEADER = include

#------------------------------------FILE--------------------------------------#

FILES = src/error\
		src/free_error\
		src/free_error2\
		src/file_check\
		src/ft_strsplitwhitspace\
		src/init\
		src/lexer\
		src/syntaxe\
		src/main\
		src/main_fnct\
		src/op\
		src/utils\
		src/utils2\
		src/utils3\
		src/utils4\
		src/utils_bytes\
		src/param\
		src/convert_desc\
		src/create_cor\
		src/get_bytes\
		src/write_utils\

#----------------------------------COLOR---------------------------------------#

GREY='\x1b[30m'
RED='\x1b[34m'
GREEN='\x1b[32m'
YELLOW='\x1b[33m'
BLUE='\x1b[34m'
PURPLE='\x1b[35m'
CYAN='\x1b[36m'
W='\x1b[37m'

#----------------------------------SOURCE--------------------------------------#

SRC = $(addsuffix .c , $(FILES))

#----------------------------------OBJECT--------------------------------------#

OBJ = $(addsuffix .o , $(FILES))

#-----------------------------------RULE---------------------------------------#

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ../libft/
	@$(CC) $(FLAGS) $(SRC) -L. ../libft/libftprintf.a -o $(NAME)


object/%.o: src/%.c $(HEADER)
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@make clean -C ../libft/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ../libft/

re: fclean all
