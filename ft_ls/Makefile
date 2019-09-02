# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phtruong <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 21:46:13 by phtruong          #+#    #+#              #
#    Updated: 2019/08/30 14:06:29 by phtruong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
DEFAULT:=\033[39m
BLACK:=\033[30m
RED:=\033[31m
GREEN:=\033[32m
YELLOW:=\033[33m
BLUE:=\033[34m
MAGENTA:=\033[35m
CYAN:=\033[36m
LGRAY:=\033[37m
DGRAY:=\033[90m
LRED:=\033[91m
LGREEN:=\033[92m
LYELLOW:=\033[93m
LBLUE:=\033[94m
LMAGENTA:=\033[95m
LCYAN:=\033[96m
WHITE:=\033[97m
NC:=\033[0m

CC := gcc
NAME := ft_ls
CFLAGS := -Werror -Wall -Wextra

SRC_DIR := src/
OBJ_DIR := obj/
LIBFT_DIR := ../libft/

INC := -Iincludes

FILES :=	switch_cases_1.c \
			switch_cases_2.c \
			switch_cases_3.c \
			sort_util.c \
			get_settings.c \
			get_macros.c \
			ls_core_struct.c \
			ls_boolean_check.c\
			ls_index.c \
			ls_dir.c \
			ls_driver.c \
			ls_print_util.c \
			ls_time_util.c \
			ls_col_util.c \
			ft_ls_util.c \
			ft_ls.c

SRC := $(addprefix $(SRC_DIR), $(FILES))
OBJ := $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

no_files := $(words $(SRC))
HEADER := NO
X := 1
Y := 231
DIFF := $(shell echo ${Y} - ${X} + 1| bc)
COLOR_NUM := $(shell echo ${X} + $$RANDOM % ${DIFF} | bc)
COUNT := 1

all:	$(NAME)

$(NAME): $(OBJ)
	@echo "${LCYAN}Compiling:${NC} \033[0K${GREEN}Completed${NC}\r\c"
	@echo
	@echo "Total file compiled: ${no_files}"
	@$(CC) $(CFLAGS) $(OBJ) $(INC) -L $(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@if [ "$(HEADER)" = "NO" ]; then \
		printf "\n🌭🍔🍟🍰♨o(>_<)o♨🥐🍞🧀🥚\n";\
		echo "${RED}";\
		echo ".----------------.  .----------------.  .----------------.  .----------------.  .----------------. ";\
		echo "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |";\
		echo "| |  _________   | || |  _________   | || |              | || |   _____      | || |    _______   | |";\
		echo "| | |_   ___  |  | || | |  _   _  |  | || |              | || |  |_   _|     | || |   /  ___  |  | |";\
		echo "| |   | |_  \_|  | || | |_/ | | \_|  | || |              | || |    | |       | || |  |  (__ \_|  | |";\
		echo "| |   |  _|      | || |     | |      | || |              | || |    | |   _   | || |   '.___-.\   | |";\
		echo "| |  _| |_       | || |    _| |_     | || |              | || |   _| |__/ |  | || |  |-\____) |  | |";\
		echo "| | |_____|      | || |   |_____|    | || |   _______    | || |  |________|  | || |  |_______.'  | |";\
		echo "| |              | || |              | || |  |_______|   | || |              | || |              | |";\
		echo "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |";\
		echo " '----------------'  '----------------'  '----------------'  '----------------'  '----------------' ";\
		echo "${NC}"; \
		$(eval HEADER = YES) \
	fi
	@$(CC) $(CFLAGS) $(INC) -c $< -o  $@
	$(eval COLOR_NUM = $(shell echo ${X} + $$RANDOM % ${DIFF} | bc))
	@echo "${LCYAN}Compiling🥖:${NC}   \033[38;5;${COLOR_NUM}m\033[0K[$<]${NC} \
	Progress: ${COUNT} out of ${no_files}"
	$(eval COUNT = $(shell echo ${COUNT}+1 | bc))

.PHONY: all, clean, fclean, re

clean:
	@make -C $(LIBFT_DIR)/ clean
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR)/ fclean
	@/bin/rm -rf $(NAME)

re: fclean all
