# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phtruong <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/29 19:54:02 by phtruong          #+#    #+#              #
#    Updated: 2019/09/04 19:17:34 by phtruong         ###   ########.fr        #
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
NAME := fdf
CFLAGS := -Werror -Wall -Wextra -O3
OPEN_GL := -framework OpenGl -framework Appkit
SRC_DIR := src/
OBJ_DIR := obj/
LIBFT_DIR := libft/
MLX_DIR := minilibx_macos/ 
FT_LS := ft_ls/

INC := -Iincludes

FILES :=	button_mapping_brightness.c \
			button_mapping_depth.c \
			button_mapping_extra.c \
			button_mapping_theme.c \
			button_mapping_view.c \
			button_mapping_zoom.c \
			color_ramp.c \
			color_ramp_util.c\
			draw_help_1.c \
			draw_help_2.c \
			draw_help_driver.c \
			draw_menu_1.c \
			draw_menu_2.c \
			draw_menu_driver.c \
			fdf_parser.c \
			fdf_main.c \
			fdf_minishell.c \
			fdf_theme.c \
			fdf_initializers.c \
			fdf_utility.c \
			keyboard_mapping.c \
			map_fdf.c \
			map_fdf_utility.c \
			mouse_handler.c \
			plot_init.c \
			plot_main.c \
			plot_pixel.c \
			plot_util_calculations.c \
			point_generator.c \
			rotation_magic.c \
			shell_animate_wrapper.c \
			shell_animate_sort.c \
			shell_animate_utility.c \
			shell_change_wrapper.c \
			shell_info_wrapper.c \
			shell_ls_wrapper.c \
			zoom_magic.c \

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
	@make -C $(LIBFT_DIR)
	@make -C $(FT_LS)
	@make -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(INC) -lmlx -lm -lft -L $(LIBFT_DIR) -L $(MLX_DIR) $(OPEN_GL) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@if [ "$(HEADER)" = "NO" ]; then \
		printf "\n🌭🍔🍟🍰♨o(>_<)o♨🥐🍞🧀🥚\n";\
		echo "${CYAN}";\
		echo "      ___        _____          ___   ";\
		echo "     /  /\      /  /::\        /  /\  ";\
		echo "    /  /:/_    /  /:/\:\      /  /:/_ ";\
		echo "   /  /:/ /\  /  /:/  \:\    /  /:/ /\\";\
		echo "  /  /:/ /:/ /__/:/ \__\:|  /  /:/ /:/";\
		echo " /__/:/ /:/  \  \:\ /  /:/ /__/:/ /:/ ";\
		echo " \  \:\/:/    \  \:\  /:/  \  \:\/:/  ";\
		echo "  \  \::/      \  \:\/:/    \  \::/   ";\
		echo "   \  \:\       \  \::/      \  \:\   ";\
		echo "    \  \:\       \__\/        \  \:\  ";\
		echo "     \__\/                     \__\/  ";\
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
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@make -C $(FT_LS) clean
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_LS) fclean
	@/bin/rm -rf $(NAME)

re: fclean all
