# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 01:58:20 by sabdelra          #+#    #+#              #
#    Updated: 2022/12/09 01:58:20 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Werror -Wextra

SRCS = support.c ft_printf.c bonsu.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

NAME = libftprintf.a

all: $(NAME) # the first and default target to run, can be used to ensure that multiple
#              targets are run before it runss (pre-requisite)

$(NAME): $(OBJS) # $@ is automatic variable (shortcut) contains the target name 'libft.a'
	ar rcs $@ $(OBJS)
# man ar (r-make into single, c-if doesnt exist create)
# ar rcs is the most common when compiling library

# program: $(NAME) main.o
# 	ar rcs $@ $(NAME)

clean: # not default (first) and not a pre-requisite anywhere else
	$(RM) $(OBJS)
# clean won't run unless specifically called
# clean isn't inteded to be a file name -> therefore defined in .PHONY

fclean:	clean # removes
	$(RM) $(NAME)
