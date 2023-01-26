# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 01:58:20 by sabdelra          #+#    #+#              #
#    Updated: 2023/01/27 03:32:38 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Werror -Wextra -g

SRCS = put.c utils.c ft_printf.c bonsu.c bonus_utils.c error.c

BSRCS = put.c utils.c ft_printf.c bonsu.c bonus_utils.c error.c

OBJS = $(SRCS:.c=.o)

BOBJS = $(BSRCS:.c=.o)

RM = rm -f

NAME = libftprintf.a

all: $(NAME) # the first and default target to run, can be used to ensure that multiple
#              targets are run before it runs (pre-requisite)

$(NAME): $(OBJS) # $@ is automatic variable (shortcut) contains the target name 'libft.a'
	ar rcs $@ $(OBJS)

bonus: $(BOBJS) # make a better bonus rule plx
	ar rcs $(NAME) $(BOBJS)
# man ar (r-make into single, c-if doesnt exist create)
# ar rcs is the most common when compiling library

# program: $(NAME) main.o
# 	ar rcs $@ $(NAME)

clean: # not default (first) and not a pre-requisite anywhere else
	$(RM) $(OBJS) $(BOBJS)
# clean won't run unless specifically called
# clean isn't inteded to be a file name -> therefore defined in .PHONY

fclean:	clean # removes
	$(RM) $(NAME)

re: fclean all
