.PHONY: all clean fclean re

NAME = corewar
CC = gcc
DEBUG = -g -fsanitize=address
FLAGS = -Wall -Wextra -g
INC = include/corewar.h
HEADER = include

#------------------------------------FILE--------------------------------------#

FILES = src/main\
		src/read_champs\
		src/utils\
		src/utils2\
		src/play_game\
		src/operande\
		src/operande_2\
		src/parse_usage\
		src/ft_process\
		src/error\
		src/jump\
		src/verif_endgame\
		src/check_cycle\
		src/op\
		src/verbose\
		src/parse_flag\
		src/init\
		src/utils_flag\
		src/operations/live_fct\
		src/operations/ld_fct\
		src/operations/st_fct\
		src/operations/add_fct\
		src/operations/sub_fct\
		src/operations/and_fct\
		src/operations/or_fct\
		src/operations/xor_fct\
		src/operations/zjmp_fct\
		src/operations/ldi_fct\
		src/operations/sti_fct\
		src/operations/fork_fct\
		src/operations/lld_fct\
		src/operations/lldi_fct\
		src/operations/lfork_fct\
		src/operations/aff_fct\
		src/operations/binary_op_carry\
		src/visual/visual_body\
		src/visual/visual_keys\
		src/visual/visual_update\
		src/visual/visual_utils\

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
	@$(CC) $(FLAGS) $(SRC) -L. ../libft/libftprintf.a -lncurses -o $(NAME)
	@chmod 111 $(NAME)

object/%.o: src/%.c $(HEADER)
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@make clean -C ../libft/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ../libft/

re: fclean all
