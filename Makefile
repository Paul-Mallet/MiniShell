NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
R_FLAG = -lreadline
SRC_DIR = src/
SRC_BUILTINS = builtins/

OBJ_DIR = obj/

SRCS = $(addprefix $(SRC_DIR), \
	main.c)
SRCS_BUILTINS = $(addprefix $(SRC_DIR)$(SRC_BUILTINS), \
	cd.c \
	echo.c \
	env.c \
	exit.c \
	export.c \
	pwd.c \
	unset.c)

OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
OBJS_BUILTINS = $(SRCS_BUILTINS:%.c=$(OBJ_DIR)%.o)

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(OBJS_BUILTINS)
	$(CC) $(CFLAGS) $(R_FLAG) -o $@ $(OBJS) $(OBJS_BUILTINS) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re