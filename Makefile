NAME			=	cub3D

LIBFT			=	libft.a 

MLX				=	libmlx_Linux.a libmlx.a

DIR_SRCS		=	srcs

DIR_BONUS		=	bonus

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c \
					parsing/parsing.c \
					parsing/args.c \
					parsing/split.c \
					parsing/map.c \
					parsing/read.c \
					parsing/fill.c \
					misc/error.c \
					misc/free.c \
					misc/print.c \
					game/game.c \
					game/calc.c \
					game/color.c \
					game/init.c \
					game/move.c \
					game/raycasting.c \
					game/textures.c \
					game/key.c \
					game/utils.c \

BONUS			=	main_bonus.c \
					parsing/parsing_bonus.c \
					parsing/args_bonus.c \
					parsing/split_bonus.c \
					parsing/map_bonus.c \
					parsing/read_bonus.c \
					parsing/fill_bonus.c \
					misc/error_bonus.c \
					misc/free_bonus.c \
					misc/print_bonus.c \
					game/game_bonus.c \
					game/calc_bonus.c \
					game/color_bonus.c \
					game/init_bonus.c \
					game/move_bonus.c \
					game/raycasting_bonus.c \
					game/textures_bonus.c \
					game/key_bonus.c \
					game/utils_bonus.c \
					help/help_bonus.c \
					game/minimap_bonus.c \
					game/sprite_bonus.c \


OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

OBJS_NAMES_B	=	${BONUS:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

DEPS_B			=	${BONUS:.c=.d}

SRCS_B			=	$(addprefix $(DIR_BONUS)/,$(BONUS))

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

OBJS_B			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES_B))

INC				=	-Iincludes -Ilibft/includes -I/usr/include -I/mlx/include/mlx.h 

LIB				=	-Llibft -lft -lm -lXext -lX11 -L/usr/lib -Lmlx -lmlx -L/usr/lib -Imlx

#LIB				=	-Llibft -lft -lm -L/usr/lib -L/opt/X11/lib -L/opt/homebrew/lib -framework Cocoa -framework OpenGL -framework IOKit -lglfw -framework OpenGL

CC				=	cc

CDFLAGS 		= 	-MMD -MP

CFLAGS			=	-g3 # -Wall -Werror -Wextra

MAKEFLAGS		=	--no-print-directory

all:	${NAME}

# @make -C mlx/mlx
# mv mlx/mlx/libmlx.a mlx/mlx/libmlx_Linux.a mlx/
$(NAME): $(DIR_OBJS) $(OBJS) 
	@make -C libft
	@make -C mlx/mlx
	@cp mlx/mlx/libmlx.a mlx/mlx/libmlx_Linux.a .
	$(CC) $(OBJS) $(CFLAGS) $(LIB) $(MLX) -o $(NAME)
	@echo "\033[32;5mcub3d\033[0m"

bonus: $(DIR_OBJS) $(OBJS_B) 
	@make -C libft
	@make -C mlx/mlx
	@cp mlx/mlx/libmlx.a mlx/mlx/libmlx_Linux.a .
	$(CC) $(OBJS_B) $(CFLAGS) $(LIB) $(MLX) -o $(NAME)
	@echo "\033[31;5mcub3d bonus\033[0m"

$(OBJS_B) : $(DIR_OBJS)/%.o : $(DIR_BONUS)/%.c
	$(CC) $(CFLAGS) $(MLX_FLAGS)  $(CDFLAGS) $(INC) -c $< -o $@ 

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(MLX_FLAGS)  $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/parsing
	mkdir -p objs/misc
	mkdir -p objs/help
	mkdir -p objs/game

leaks:	${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3d $(dad)
clean:
	make clean -C libft
	make clean -C mlx/mlx
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	rm -rf ${LIBFT}
	rm -rf ${MLX}
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus