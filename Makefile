# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/21 19:14:26 by kain2250          #+#    #+#              #
#    Updated: 2020/11/26 20:11:37 by bdrinkin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Определение системных команд
NAME = doom-nukem
RES = resource

# Флаги компиляции:
GCC = gcc -O2
CCFLAGS = -Wall -Wextra -Werror
OTHERS_FLAGS = -lm

# Список фреймворков и их пути:
FRAME_SDL2_DIR = Frameworks
FRAME_SDL2 = $(FRAME_SDL2_DIR)/SDL2.framework
FRAME_SDL2_IMAGE = $(FRAME_SDL2_DIR)/SDL2_image.framework
FRAME_SDL2_MIXER = $(FRAME_SDL2_DIR)/SDL2_mixer.framework
FRAME_SDL2_TTF = $(FRAME_SDL2_DIR)/SDL2_ttf.framework
FRAME_SDL2_NET = $(FRAME_SDL2_DIR)/SDL2_net.framework
FRAMEWORKS = -F Frameworks \
	-framework SDL2 \
	-framework SDL2_image \
	-framework SDL2_mixer \
	-framework SDL2_ttf \
	-framework SDL2_net \
	-rpath $(FRAME_SDL2_DIR)

# Список библиотек и их пути:
LIBFT_DIRECTORY = libft

# Флаги для сборки библиотек
LIBRARIES_LIBFT = -L $(LIBFT_DIRECTORY) -lft

# Заголовочные файлы и их пути:
INCLUDES_DIRECTORY = includes/
INCLUDES_DIRECTORY_LIBFT = $(LIBFT_DIRECTORY)/includes
INCLUDES_SDL2 = -F $(FRAME_SDL2_DIR) \
	-I $(FRAME_SDL2)/Headers \
	-I $(FRAME_SDL2_IMAGE)/Headers \
	-I $(FRAME_SDL2_MIXER)/Headers \
	-I $(FRAME_SDL2_TTF)/Headers \
	-I $(FRAME_SDL2_NET)/Headers

INCLUDES = -I$(INCLUDES_DIRECTORY) \
	-I$(INCLUDES_DIRECTORY_LIBFT) \
	$(INCLUDES_SDL2)

HEADERS_LIST = *.h

HEADERS = $(addprefix $(INCLUDES_DIRECTORY), $(HEADERS_LIST))

# Основные файлы программы и их пути:
SRC_DIRECTORY = src/
SRC_LIST = main.c \
	debug_file.c \
	tools_for_editor/*.c \
	load_res/*.c \
	primitives/*.c \
	events/*.c \
	init/*.c \
	tools/*.c \
	wad/wad_loader.c \
	wad/wad_reader.c \
	wad/bytes_shift.c \
	wad/draw_wad.c \
	wad/wad_get.c \
	wad/draw_sprite.c


SRC = $(addprefix $(SRC_DIRECTORY), $(SRC_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# Определение цвета вывода:
GREEN = \033[0;32;1m
RED = \033[0;31;1m
RESET = \033[0m

# Лабуда-бу-даб-даб
.PHONY: all clean fclean re

# Основные правила сборки:
all: $(NAME)

$(NAME): $(LIBFT_DIRECTORY) $(SRC) $(HEADERS) $(RES)
	@echo "wolf3d: $(GREEN)Компиляция исполняемого файла$(RESET)\n"
	@$(GCC) $(CCFLAGS) $(INCLUDES) $(LIBRARIES_LIBFT) $(FRAMEWORKS) $(OTHERS_FLAGS) $(SRC) -o $(NAME)
	@echo "wolf3d: $(GREEN)Компиляция завершена$(RESET)\n"

$(RES):
	@echo "wolf3d: $(GREEN)Подгрузка материалов$(RESET)\n"
	@git clone https://github.com/Kain2250/res_doom.git $(CURDIR)/resource
	@echo "wolf3d: $(GREEN)Подгрузка материалов завершена$(RESET)\n"

$(LIBFT_DIRECTORY):
	@$(MAKE) -C $(LIBFT_DIRECTORY)

debug: $(LIBFT_DIRECTORY) $(SRC) $(HEADERS) $(RES)
	@$(MAKE) -C $(LIBFT_DIRECTORY)
	@echo "wolf3d: $(GREEN)Компиляция исполняемого файла$(RESET)\n"
	@$(GCC) -g $(CCFLAGS) $(INCLUDES) $(LIBRARIES_LIBFT) $(FRAMEWORKS) $(OTHERS_FLAGS) $(SRC) -o $(NAME)
	@echo "wolf3d: $(GREEN)Компиляция завершена$(RESET)\n"

clean:
	@$(MAKE) -C $(LIBFT_DIRECTORY) clean

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)Исполняемый файл $(NAME) удален$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIRECTORY) fclean
	@rm -rf $(CURDIR)/resource
	@echo "$(NAME): $(RED)Ресурсы удалены$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIRECTORY) clean

re:
	@$(MAKE) fclean
	@$(MAKE) all
