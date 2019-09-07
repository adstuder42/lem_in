# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 16:40:26 by thzimmer          #+#    #+#              #
#    Updated: 2019/07/23 15:02:31 by thzimmer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re 

# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

NAME       = libft.a

# ******************************     LIBFT     ******************************* #

SRCS_PATH  = srcs/libft/
OBJS_PATH  = objs/libft/
SRC_NAME   = ft_atoi.c ft_binary.c ft_isdigit.c ft_itoa.c ft_pow.c\
             ft_putchar.c ft_putstr.c ft_strchr.c ft_strdup.c ft_strjoin.c\
             ft_strlen.c ft_strncmp.c ft_strncpy.c ft_dpow.c ft_upow.c\
             ft_iscapital.c ft_itoa_base.c ft_strcmp.c ft_strsub.c ft_strequ.c\
             ft_putstr_fd.c ft_strrev.c ft_intlen.c ft_sortarr.c ft_strsplit.c\
             ft_freetab.c ft_join3.c ft_check_intmax.c get_next_line.c\
             ft_putendl.c ft_putstr_len.c ft_freetab.c ft_strnequ.c \
             ft_strjoinmulti.c
OBJ_NAME   = $(SRC_NAME:.c=.o)
SRCS       = $(addprefix $(SRCS_PATH),$(SRC_NAME))
OBJS       = $(addprefix $(OBJS_PATH),$(OBJ_NAME))

# ******************************   FT_PRINTF   ******************************* #

SRCS2_PATH = srcs/ft_printf/
OBJS2_PATH = objs/ft_printf/
SRC2_NAME  = ft_printf_apply_attributes.c ft_printf_exponent.c\
             ft_printf_float_output.c ft_printf_get_attributes.c\
             ft_printf.c ft_printf_notreadable.c ft_printf_standard_output.c\
             ft_printf_time_and_gconv.c ft_printf_numerical_to_ascii.c
OBJ2_NAME  = $(SRC2_NAME:.c=.o)
SRCS2      = $(addprefix $(SRCS2_PATH),$(SRC2_NAME))
OBJS2      = $(addprefix $(OBJS2_PATH),$(OBJ2_NAME))

# **************************************************************************** #
#                                 COMPILATION                                  #
# **************************************************************************** #

all     : $(NAME)

CC      = gcc -O3
CFLAGS  = -Wall -Wextra -Werror

$(NAME) : $(OBJS) $(OBJS2)
	@printf "\033[K"
	@ar rc $(NAME) $^
	@ranlib $(NAME)
	@printf "\033[37;1m-- $(NAME)       [ \033[32;1mOK\033[37;1m ]\033[0m\\n"

# ******************************     LIBFT     ******************************* #

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c Makefile includes/libft.h
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "\033[K"
	@printf "make: compiling $<\\r"

# ******************************   FT_PRINTF   ******************************* #

$(OBJS2_PATH)%.o : $(SRCS2_PATH)%.c Makefile includes/libft.h
	@mkdir -p $(OBJS2_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "\033[K"
	@printf "make: compiling $<\\r"

# **************************************************************************** #
#                                  COMMANDS                                    #
# **************************************************************************** #

clean  :
	@rm -rf objs

fclean : clean
	@rm -rf $(NAME)

re     : fclean all

# ****************************************************** Made by Zim-Zoom  *** #
