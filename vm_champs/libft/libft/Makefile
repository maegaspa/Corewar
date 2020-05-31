#**************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/10 19:59:22 by cgarrot      #+#   ##    ##    #+#        #
#    Updated: 2020/04/03 19:01:26 by maegaspa         ###   ########lyon.fr    #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
INC = inc/libft.h
HEADER = include

#------------------------------------FILE--------------------------------------#

FILES = lib/ft_atoi\
		lib/ft_bzero\
		lib/ft_isalnum\
		lib/ft_isalpha\
		lib/ft_isascii\
		lib/ft_isdigit\
		lib/ft_isprint\
		lib/ft_itoa\
		lib/ft_memalloc\
		lib/ft_memccpy\
		lib/ft_memchr\
		lib/ft_memcmp\
		lib/ft_memcpy\
		lib/ft_memdel\
		lib/ft_memmove\
		lib/ft_memset\
		lib/ft_putchar\
		lib/ft_putchar_fd\
		lib/ft_putendl\
		lib/ft_putendl_fd\
		lib/ft_putnbr\
		lib/ft_putnbr_fd\
		lib/ft_putstr\
		lib/ft_putstr_fd\
		lib/ft_strcat\
		lib/ft_strchr\
		lib/ft_strclr\
		lib/ft_strcmp\
		lib/ft_strcpy\
		lib/ft_strdel\
		lib/ft_strdup\
		lib/ft_strequ\
		lib/ft_striter\
		lib/ft_striteri\
		lib/ft_strjoin\
		lib/ft_strlcat\
		lib/ft_strlen\
		lib/ft_strmap\
		lib/ft_strmapi\
		lib/ft_strncat\
		lib/ft_strncmp\
		lib/ft_strncpy\
		lib/ft_strnequ\
		lib/ft_strnew\
		lib/ft_strnstr\
		lib/ft_strrchr\
		lib/ft_strsplit\
		lib/ft_strstr\
		lib/ft_strsub\
		lib/ft_strtrim\
		lib/ft_tolower\
		lib/ft_toupper\
		lib/ft_lstnew\
		lib/ft_lstdelone\
		lib/ft_lstdel\
		lib/ft_lstadd\
		lib/ft_lstiter\
		lib/ft_lstmap\
		lib/ft_strndup\
		lib/ft_swap\
		lib/ft_lltoa\
		lib/ft_ulltoa\
		lib/ft_utoa\
		lib/ft_uhhtoa\
		lib/ft_uhtoa\
		lib/ft_htoa\
		lib/ft_hhtoa\
		lib/ft_strjoinfree\
		lib/ft_strsubfree\
		lib/get_next_line\
		lib/ft_intcpy\

#----------------------------------COLOR---------------------------------------#

GREY='\x1b[30m'
RED='\x1b[31m'
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
	@printf $(RED)"                                                                      ___ \n"
	@printf "                                _____________________________________ //  \n"
	@printf "                              / /-----------|  |----------| |--------- \ \n"
	@printf "                            / /             |  |          | |           \ \n"
	@printf "                          / /               |  |          | |           | \n"
	@printf "               _________/ /                 |  |          | |           | \n"
	@printf "      _______"
	@printf $(YELLOW)"("
	@printf $(RED)"|___________\_________________|  |----------===============\          "
	@printf $(W)"(@)\n"
	@printf $(RED)"    /                  |                 (=) |           (=)|            "
	@printf $(YELLOW)"/\ "
	@printf $(RED)"       "
	@printf $(W)"(@) (@)\n"
	@printf $(RED)"  /                   |      "
	@printf $(PURPLE)"cgarrot"
	@printf $(RED)"        |                |           "
	@printf $(YELLOW)"\/"
	@printf $(RED)"\     "
	@printf $(W)"(@) (@)\n"
	@printf $(RED)" /"
	@printf $(YELLOW)"<>"
	@printf $(RED)"      ________    |           "
	@printf $(PURPLE)"Libft"
	@printf $(RED)"     |                |________      \     "
	@printf $(W)"(@)\n"
	@printf $(RED)" |      /  "
	@printf $(W)"______"
	@printf $(RED)"  \   |  <==================|===========>  /  "
	@printf $(W)"______"
	@printf $(RED)"  \   -/   "
	@printf $(W)"(@)\n"
	@printf $(RED)" |)    |  "
	@printf $(W)"/ \  / \ "
	@printf $(RED)" |__|_____________________|_____________|  "
	@printf $(W)"/ \  / \ "
	@printf $(RED)" | [ "
	@printf $(W)"(@)\n"
	@printf $(RED)" \____ | "
	@printf $(W)"|   ()   | "
	@printf $(RED)"|______________________________________| "
	@printf $(W)"|   ()   | "
	@printf $(RED)"|_/ \n"
	@printf $(W)"          \_/__\_/                                            \_/__\_/ \n"
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

object/%.o: src/%.c $(HEADER)
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer les OBJECT------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@rm -f $(OBJ)

fclean: clean
	@echo "\n"
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer la libft.a------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@rm -f $(NAME) 

re: fclean all
