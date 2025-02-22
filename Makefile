# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 16:06:54 by apercebo          #+#    #+#              #
#    Updated: 2022/07/01 11:16:08 by apercebo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### LISTES ####

SOURCES = main.c \
		  parsing.c \
		  parsing2.c \
		  parsing_redir.c \
		  env_replace_list.c \
		  env_replace_str.c \
		  env_in_list.c \
		  error.c \
		  cmd_lst_utils1.c \
		  cmd_lst_utils2.c \
		  env_lst_utils1.c \
		  env_lst_utils2.c \
		  ft_utils.c \
		  ft_utils2.c \
		  ft_utils3.c \
		  ft_utils4.c \
		  execution_one.c \
		  execution_two.c \
		  exec_path_fct.c \
		  exec_one_cmd.c \
		  rm_quote.c \
		  bin_eepc.c \
		  bin_cd.c \
		  bin_exit.c \
		  bin_export.c \
		  bin_unset1.c \
		  bin_unset2.c \
		  signals.c

OBJETS = $(SOURCES:.c=.o)
INCLUDES = minishell.h


#### DIRECTORY ####

DIR_SRC = sources
DIR_OBJ = .object
DIR_INC = include


#### COMPLETE_PATH ####

SRC := $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJ := $(addprefix $(DIR_OBJ)/,$(OBJETS))
INC := $(addprefix $(DIR_INC)/,$(INCLUDES))


#### OTHER ####

CC := gcc
CFLAGS := -Wall -Werror -Wextra
LDFLAGS := -L /usr/include -lreadline -L $(shell brew --prefix readline)/lib
CPPFLAGS := -I $(shell brew --prefix readline)/include
NAME := minishell


#### STANDARD_RULE ####

all : $(NAME)
re : fclean all
clean :
	rm -rf $(DIR_OBJ)
fclean : clean
	rm -rf minishell


### CUSTOM_RULE ####

$(NAME) : $(OBJ) | $(DIR_BIN)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $(NAME) -lreadline
$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c $(INC) Makefile | $(DIR_OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -I $(DIR_INC)
$(DIR_OBJ) :
	mkdir -p $(DIR_OBJ)


#### UTILS #####

.PHONY : all bonus re clean fclean
