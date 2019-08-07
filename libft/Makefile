# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phtruong <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 21:46:13 by phtruong          #+#    #+#              #
#    Updated: 2019/06/19 14:46:09 by phtruong         ###   ########.fr        #
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
NAME := libft.a
CFLAGS := -Werror -Wall -Wextra

src := $(wildcard *.c)
pfsrc := $(wildcard ./printf/*.c)
no_files := $(words $(src), $(pfsrc))
obj := $(src:.c=.o) $(pfsrc:.c=.o)
HEADER := NO
X := 1
Y := 231
DIFF := $(shell echo ${Y} - ${X} + 1| bc)
COLOR_NUM := $(shell echo ${X} + $$RANDOM % ${DIFF} | bc)
COUNT := 1

all:	$(NAME)

$(NAME): $(obj)
	@echo "${LCYAN}Compiling:${NC} \033[0K${GREEN}Completed${NC}\r\c"
	@echo
	@echo "Total file compiled: ${no_files}"
	@ar rc $(NAME) $(obj)

$(PRINTF_D)%.o:$(PRINTF_D)%.c
	@$(CC) $(CFLAGS) -I$(LIBFT_INC) -I$(PRINTF_INC) -c $< -o $@

%.o: %.c
	@if [ "$(HEADER)" = "NO" ]; then \
		printf "\n🍩🍩🍩🍩♨o(>_<)o♨🍩🍩🍩🍩\n";\
		echo "${GREEN}";\
		echo "██╗     ██╗██████╗ ███████╗████████╗";\
		echo "██║     ██║██╔══██╗██╔════╝╚══██╔══╝";\
		echo "██║     ██║██████╔╝█████╗     ██║   ";\
		echo "██║     ██║██╔══██╗██╔══╝     ██║   ";\
		echo "███████╗██║██████╔╝██║        ██║   ";\
		echo "╚══════╝╚═╝╚═════╝ ╚═╝        ╚═╝   ";\
		echo "${NC}"; \
		$(eval HEADER = YES) \
	fi
	@$(CC) $(CFLAGS) -I. -c $< -o  $@
	$(eval COLOR_NUM = $(shell echo ${X} + $$RANDOM % ${DIFF} | bc))
	@echo "${LCYAN}Compiling🍩:${NC}   \033[38;5;${COLOR_NUM}m\033[0K[$<]${NC} \
	Progress: ${COUNT} out of ${no_files}"
	$(eval COUNT = $(shell echo ${COUNT}+1 | bc))

.PHONY: all, clean, fclean, re

clean:
	@rm -rf $(obj)

.PHONY: fclean
fclean: clean
	@rm -rf $(NAME)

re: fclean all
