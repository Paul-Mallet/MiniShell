NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
R_FLAG = -lreadline -lhistory

SRC_DIR = src/
SRC_BUILTINS = builtins/
SRC_ENV = env/
SRC_PARSING = parsing/
SRC_LEXER = parsing/lexer/
SRC_PARSER = parsing/parser/
SRC_EXPANDER = parsing/expander/
SRC_SIGNALS = signals/
SRC_EXECUTING = executing/
SRC_REDIR = executing/redir/
SRC_COMMAND = executing/command/

OBJ_DIR = obj/

SRCS = $(addprefix $(SRC_DIR), \
	main.c \
	init.c \
	error_management.c \
	free_data.c)
SRCS_REDIR = $(addprefix $(SRC_DIR)$(SRC_REDIR), \
	lst_redir.c \
	redir_managing.c \
	redir_checkers.c)
SRCS_COMMAND = $(addprefix $(SRC_DIR)$(SRC_COMMAND), \
	lst_cmd.c \
	init_cmd.c \
	print_cmd.c \
	env_path.c)
SRCS_EXECUTING = $(addprefix $(SRC_DIR)$(SRC_EXECUTING), \
	exec.c \
	exec_utils.c \
	exec_cmd.c \
	exec_cmd_utils.c \
	here_doc.c)
SRCS_BUILTINS = $(addprefix $(SRC_DIR)$(SRC_BUILTINS), \
	builtins.c \
	cd.c \
	echo.c \
	env.c \
	exit.c \
	export.c \
	pwd.c \
	unset.c)
SRCS_LEXER = $(addprefix $(SRC_DIR)$(SRC_LEXER), \
	lexer.c)
SRCS_PARSER = $(addprefix $(SRC_DIR)$(SRC_PARSER), \
	first_tokenizer.c \
	first_tokenizer_utils.c \
	handler_first_tokenizer.c \
	second_tokenizer.c \
	second_tokenizer_utils.c \
	tokenizer_utils.c)
SRCS_EXPANDER = $(addprefix $(SRC_DIR)$(SRC_EXPANDER), \
	expander_len.c \
	expander.c)
SRCS_PARSING = $(addprefix $(SRC_DIR)$(SRC_PARSING), \
	parsing.c \
	quotes_utils.c \
	token_handling.c \
	quotes_handling.c \
	quotes_changing.c)
SRCS_SIGNALS = $(addprefix $(SRC_DIR)$(SRC_SIGNALS), \
	signals.c)
SRCS_ENV = $(addprefix $(SRC_DIR)$(SRC_ENV), \
	get_env.c)

OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
OBJS_EXECUTING = $(SRCS_EXECUTING:%.c=$(OBJ_DIR)%.o)
OBJS_BUILTINS = $(SRCS_BUILTINS:%.c=$(OBJ_DIR)%.o)
OBJS_LEXER = $(SRCS_LEXER:%.c=$(OBJ_DIR)%.o)
OBJS_PARSER = $(SRCS_PARSER:%.c=$(OBJ_DIR)%.o)
OBJS_EXPANDER = $(SRCS_EXPANDER:%.c=$(OBJ_DIR)%.o)
OBJS_PARSING = $(SRCS_PARSING:%.c=$(OBJ_DIR)%.o)
OBJS_SIGNALS = $(SRCS_SIGNALS:%.c=$(OBJ_DIR)%.o)
OBJS_ENV = $(SRCS_ENV:%.c=$(OBJ_DIR)%.o)
OBJS_REDIR = $(SRCS_REDIR:%.c=$(OBJ_DIR)%.o)
OBJS_COMMAND = $(SRCS_COMMAND:%.c=$(OBJ_DIR)%.o)

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

all: $(NAME)
	@echo "minishell compiled"

$(NAME): $(LIBFT) $(OBJS) $(OBJS_EXECUTING) $(OBJS_BUILTINS) $(OBJS_ENV) $(OBJS_PARSING) $(OBJS_PARSER) $(OBJS_LEXER) $(OBJS_EXPANDER) $(OBJS_REDIR) $(OBJS_COMMAND) $(OBJS_SIGNALS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(OBJS_EXECUTING) $(OBJS_BUILTINS) $(OBJS_ENV) $(OBJS_PARSING) $(OBJS_PARSER) $(OBJS_LEXER) $(OBJS_EXPANDER) $(OBJS_REDIR) $(OBJS_COMMAND) $(OBJS_SIGNALS) $(LIBFT) $(R_FLAG)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
