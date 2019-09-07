# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 16:40:26 by thzimmer          #+#    #+#              #
#    Updated: 2019/07/23 18:17:44 by thzimmer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, lib, $(NAME), $(NAME2)

# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

SRCS_PATH  = srcs/
OBJS_PATH  = objs/

NAME       = lem-in
SRC_NAME   = lem_in.c memory.c move_ants.c flows_manager.c check_rooms.c \
             check_links.c find_routesets.c sort_routesets.c simple_bfs.c \
             find_augmenting_paths.c utils.c reader.c
OBJ_NAME   = $(SRC_NAME:.c=.o)
SRCS       = $(addprefix $(SRCS_PATH),$(SRC_NAME))
OBJS       = $(addprefix $(OBJS_PATH),$(OBJ_NAME))

NAME2      = viewer
SRC_NAME2  = viewer.c memory.c move_ants.c flows_manager.c check_rooms.c \
             check_links.c find_routesets.c sort_routesets.c simple_bfs.c \
             find_augmenting_paths.c utils.c reader.c viewertools.c
OBJ_NAME2  = $(SRC_NAME2:.c=.o)
SRCS2      = $(addprefix $(SRCS_PATH),$(SRC_NAME2))
OBJS2      = $(addprefix $(OBJS_PATH),$(OBJ_NAME2))

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all           : $(NAME) $(NAME2)

CC            = gcc -O3
CFLAGS        = -Wall -Wextra -Werror
SDLFLAGS      = `sdl2-config --cflags --libs`
LIB_DEP       = $(shell find libft/srcs/*/*.c)

libft/libft.a : $(LIB_DEP) libft/Makefile libft/includes/libft.h
	@make -sC libft

lib           : libft/libft.a

clean         :
	@rm -rf objs
	@make clean -sC libft
	@printf "make: objs cleaned\\n"

fclean        : clean
	@rm -rf $(NAME) $(NAME2)
	@make fclean -sC libft
	@printf "make: programs cleaned\\n"

re            : fclean all

# **************************************************************************** #
#                                COMPILATION                                   #
# **************************************************************************** #

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c Makefile libft/libft.a includes/lem_in.h
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[K"
	@printf "make: compiling $<\\r"

$(NAME)         : $(OBJS)
	@printf "\033[K"
	@$(CC) $(CFLAGS) $^ -o $(NAME) -L libft -lft
	@printf "\033[37;1m-- $(NAME)        [ \033[32;1mOK\033[37;1m ]\033[0m\\n"

$(NAME2)        : $(OBJS2)
	@printf "\033[K"
	@$(CC) $(CFLAGS) $^ -o $(NAME2) $(SDLFLAGS) -L libft -lft
	@printf "\033[37;1m-- $(NAME2)        [ \033[32;1mOK\033[37;1m ]\033[0m\\n"

# ****************************************************** Made by Zim-Zoom  *** #
