# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 19:32:48 by nomargen          #+#    #+#              #
#    Updated: 2022/10/10 20:46:52 by nomargen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra -O0 -g

SRC_DIR		=	src/

INC_DIR		=	inc/

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

INC			=	$(addprefix $(INC_DIR), $(INC_FILES))

SRC_FILES	=	main.c parser_1.c parser_2.c parser_3.c parser_utils_1.c parser_utils_2.c get_next_line_utils.c get_next_line.c

INC_FILES	=	main.h parser.h get_next_line.h

OBJ			=	$(SRC:.c=.o)

LIBFT_DIR	=	lib/libft

LIBFT		=	$(addsuffix .a, $(LIBFT_DIR))

RM			=	rm -rf

LDLIBS		=	-lft


%.o: %.с  
	$(CC) $(CFLAGS) -c -o $@ $<

all:	$(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -o $(NAME) $(INC) $(OBJ) -Llib $(LDLIBS)

$(LIBFT): $(LIBFT_DIR)/libft.a
	cp $(LIBFT_DIR)/libft.a $(LIBFT)

$(LIBFT_DIR)/libft.a:
	make --directory=$(LIBFT_DIR) bonus

lib_clean:
	make --directory=$(LIBFT_DIR) fclean
	$(RM) lib/libft.a

fclean: clean
	$(RM) $(NAME)

clean: lib_clean
	$(RM) $(OBJ)

re: fclean all

.PHONY: all clean fclean lib_clean re
