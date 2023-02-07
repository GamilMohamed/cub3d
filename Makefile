NAME			=	cub3d

LIBFT			=	libft.a 

MLX				=	libmlx42.a

DIR_SRCS		=	srcs

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
					game/draw.c \
					game/init.c \
					game/minimap.c \
					game/move.c \
					game/raycasting.c \

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes -Ilibft/includes -I/usr/include -I/MLX42/include/MLX42 -I/opt/X11/include -I/opt/homebrew/include

LIB				=	-Llibft -lft -lm -L/usr/lib -L/opt/X11/lib -L/opt/homebrew/lib -framework Cocoa -framework OpenGL -framework IOKit -lglfw -framework OpenGL

CC				=	cc

CDFLAGS 		= 	-MMD -MP

CFLAGS			=	-g3 # -Wall -Werror -Wextra

MAKEFLAGS		=	--no-print-directory

all:	${NAME}

# @make -C mlx/mlx
# mv mlx/mlx/libmlx.a mlx/mlx/libmlx_Linux.a mlx/
$(NAME): $(DIR_OBJS) $(OBJS) 
	@make -C libft
	$(CC) $(OBJS) $(CFLAGS) $(LIB) $(MLX) -o $(NAME)
	@echo "\033[31;5mcub3d\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(MLX_FLAGS)  $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/parsing
	mkdir -p objs/misc
	mkdir -p objs/game

leaks:	${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3d $(dad)
clean:
	make clean -C libft
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	rm -rf ${LIBFT}
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus