# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/10 19:59:22 by cgarrot      #+#   ##    ##    #+#        #
#    Updated: 2019/12/28 10:35:03 by seanseau    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
INC = libft.h

#------------------------------------FILE--------------------------------------#

FILES = ft_atoi\
		ft_bzero\
		ft_isalnum\
		ft_isalpha\
		ft_isascii\
		ft_isdigit\
		ft_isprint\
		ft_itoa\
		ft_memalloc\
		ft_memccpy\
		ft_memchr\
		ft_memcmp\
		ft_memcpy\
		ft_memdel\
		ft_memmove\
		ft_memset\
		ft_putchar\
		ft_putchar_fd\
		ft_putendl\
		ft_putendl_fd\
		ft_putnbr\
		ft_putnbr_fd\
		ft_putstr\
		ft_putstr_fd\
		ft_strcat\
		ft_strchr\
		ft_strclr\
		ft_strcmp\
		ft_strcpy\
		ft_strdel\
		ft_strdup\
		ft_strequ\
		ft_striter\
		ft_striteri\
		ft_strjoin\
		ft_strlcat\
		ft_strlen\
		ft_strmap\
		ft_strmapi\
		ft_strncat\
		ft_strncmp\
		ft_strncpy\
		ft_strnequ\
		ft_strnew\
		ft_strnstr\
		ft_strrchr\
		ft_strsplit\
		ft_strstr\
		ft_strsub\
		ft_strtrim\
		ft_tolower\
		ft_toupper\
		ft_lstnew\
		ft_lstdelone\
		ft_lstdel\
		ft_lstadd\
		ft_lstiter\
		ft_lstmap\
		ft_strndup\
		ft_swap\
		ft_lltoa\
		ft_ulltoa\
		ft_utoa\
		ft_uhhtoa\
		ft_uhtoa\
		ft_htoa\
		ft_hhtoa\
		ft_strjoinfree\
		ft_strsubfree\
		ft_ftoa\
		get_next_line\
		ft_intcpy\

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

%.o: %.c $(INC)
	@$(CC) $(FLAGS) -o $@ -c $< -I $(INC)

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
