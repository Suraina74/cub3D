NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLX_DIR = ./MLX42
LIBFT_DIR = ./LIBFT

HEADER = -I $(MLX_DIR)/include -I $(LIBFT_DIR)
LIBS = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
CFILES = src/cub3d.c src/validation.c src/utils.c src/parse.c src/fill_map.c src/parse_rgb.c src/flood_fill.c src/cleanup.c src/cleanup_two.c \
src/key_presses.c src/draw_c_f.c src/raycasting.c src/draw_walls.c src/initialization.c src/fill_metadata.c
OFILES = $(CFILES:.c=.o)

all: libmlx libft $(NAME)

libmlx:
	@if [ -f "$(MLX_DIR)" ]; then echo "Submodule already initialized"; else git submodule update --init --recursive $(MLX_DIR); fi
ifndef $(MLX_DIR)/build
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4
endif

libft:
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c cub3d.h
	@$(CC) -c $(CFLAGS) $< -o $@ $(HEADER)

$(NAME): $(OFILES) $(LIBFT_DIR)/libft.a $(MLX_DIR)/build/libmlx42.a
	@$(CC) $(CFLAGS) $(OFILES) $(LIBS) $(LIBFT_DIR)/libft.a -o $(NAME)

clean:
	@rm -f $(OFILES)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)/build
	@rm -f $(LIBFT_DIR)/libft.a

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft