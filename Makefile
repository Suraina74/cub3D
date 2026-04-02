NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = ./MLX42
LIBFT_DIR = ./LIBFT

HEADER = -I $(MLX_DIR)/include -I $(LIBFT_DIR)
LIBS = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
CFILES = cub3d.c validation.c utils.c parse.c parse_rgb.c flood_fill.c initialization.c raycasting.c draw_walls.c key_presses.c draw_c_f.c
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