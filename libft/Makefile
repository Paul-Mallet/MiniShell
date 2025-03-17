###########################################################
## ARGUMENTS
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I includes
AR = ar rcs
RM = rm -rf
RMD = rmdir

###########################################################
## DIRECTORIES
SRCS_LIBFT_DIR = libft/
SRCS_FT_PRINTF_DIR = ft_printf/
SRCS_GNL_DIR = get_next_line/
OBJS_DIR = objs/

###########################################################
## SOURCES

SRCS_LIBFT = ft_isspace.c \
             ft_isdigit.c \
             ft_memset.c \
             ft_strjoin.c \
             ft_strtrim.c \
             ft_isprint.c \
             ft_putchar_fd.c \
             ft_strlcat.c \
             ft_substr.c \
             ft_atoi.c \
             ft_itoa.c \
             ft_atol.c \
             ft_putendl_fd.c \
             ft_strlcpy.c \
             ft_tolower.c \
             ft_bzero.c \
             ft_putnbr_fd.c \
             ft_strlen.c \
             ft_toupper.c \
             ft_calloc.c \
             ft_memchr.c \
             ft_putstr_fd.c \
             ft_strmapi.c \
             ft_isalnum.c \
             ft_memcmp.c \
             ft_split.c \
             ft_strncmp.c \
             ft_isalpha.c \
             ft_memcpy.c \
             ft_strchr.c \
             ft_strcmp.c \
             ft_strnstr.c \
             ft_isascii.c \
             ft_memmove.c \
             ft_strdup.c \
             ft_strndup.c \
             ft_strrchr.c \
             ft_striteri.c \
             ft_lstnew_bonus.c \
             ft_lstmap_bonus.c \
             ft_lstadd_front_bonus.c \
             ft_lstlast_bonus.c \
             ft_lstsize_bonus.c \
             ft_lstiter_bonus.c \
             ft_lstadd_back_bonus.c \
             ft_lstdelone_bonus.c \
             ft_lstclear_bonus.c

SRCS_FT_PRINTF = ft_printf.c \
                 print_c.c \
                 print_nbr.c \
                 print_p.c \
                 print_s.c \
                 print_xlow.c \
                 print_xup.c \
                 print_u.c

SRCS_GNL = get_next_line.c \
           get_next_line_utils.c

SRCS = $(addprefix $(SRCS_LIBFT_DIR), $(SRCS_LIBFT)) \
       $(addprefix $(SRCS_FT_PRINTF_DIR), $(SRCS_FT_PRINTF)) \
       $(addprefix $(SRCS_GNL_DIR), $(SRCS_GNL))

OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

###########################################################
## RULES

all: $(NAME)
	@echo "libft compiled"

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

