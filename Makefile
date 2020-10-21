# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehell <фпгшддук@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/06 22:26:44 by aguiller          #+#    #+#              #
#    Updated: 2020/10/11 10:23:28 by aguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c parsing.c work_withstruct.c parsing_p2.c func.c validation.c

SRC_DIR = src/

LEM_IN_H =	-I includes/
PRINTF_H =	-I libftprintf/includes
LIB_H =	-I libftprintf/libft/


SRCS=$(addprefix $(SRC_DIR), $(SRC))

NAME = Lem-in

OBJ = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) 
	@cd libftprintf && $(MAKE) all
	@cp libftprintf/libftprintf.a ./
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) libftprintf.a


%.o:%.c
	gcc -Wall -Wextra -ggdb -Werror $(LEM_IN_H) $(PRINTF_H) $(LIB_H) -c $< -o $@

clean:
	@cd libftprintf && $(MAKE) clean	
	@/bin/rm -f $(OBJ)
	@/bin/rm -f libftprintf.a

fclean: clean
	@cd libftprintf && $(MAKE) fclean
	@/bin/rm -f $(NAME)

re: fclean  all 

