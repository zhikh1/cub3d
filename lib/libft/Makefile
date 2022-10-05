# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 21:02:37 by nomargen          #+#    #+#              #
#    Updated: 2022/06/24 02:07:29 by cjanetta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

SRC		=	ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
			ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c
OBJ		=	$(SRC:.c=.o)
BONUS_S	=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
BONUS_O	=	$(BONUS_S:.c=.o)
HEAD	=	libft.h

RM		=	rm -rf

.PHONY:	all bonus clean fclean re

all : $(NAME)

bonus : $(NAME)
	
$(NAME): $(OBJ) $(if $(findstring bonus, $(MAKECMDGOALS)), $(BONUS_O))
	ar rcs $(NAME) $(OBJ) $(if $(findstring bonus, $(MAKECMDGOALS)), $(BONUS_O))

%.o : %.c $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $(addsuffix .o, $(basename $<))

clean:
	$(RM) $(OBJ) $(BONUS_O)

fclean: clean
	$(RM) $(NAME)

re: fclean all
