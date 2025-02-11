###########################################################
## ARGUMENTS
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
RMD = rmdir

###########################################################
## SOURCES

SRCS = ft_printf.c \
       print_c.c \
       print_nbr.c \
       print_p.c \
       print_s.c \
       print_xlow.c \
       print_xup.c \
       print_u.c \
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
	   ft_split_quotes.c \
       ft_split.c \
       ft_strncmp.c \
       ft_isalpha.c \
       ft_memcpy.c \
       ft_strchr.c \
	   ft_strcmp.c \
       ft_strnstr.c \
       ft_isascii.c \
       ft_strcmp.c \
       ft_memmove.c \
       ft_strdup.c \
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
       ft_lstclear_bonus.c \
       get_next_line.c \
       get_next_line_utils.c

# Creer un repertoir objs si necessaire
OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

###########################################################
## RULES

# Regle par defaut : creer la bibliotheque
all: $(NAME)

# Creer la bibliotheque a partir des fichiers objets
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Creer le repertoire objs s'il n'existe pas encore
$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers objets
clean:
	$(RM) $(OBJS)

# Nettoyer les fichiers objets et la bibliotheque
fclean: clean
	$(RM) $(NAME)
	$(RMD) $(OBJS_DIR)

# Recompiler la bibliotheque
re: fclean all

.PHONY: all clean fclean re
