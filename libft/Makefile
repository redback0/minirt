CC = cc

CFLAGS = -Wall -Wextra -Werror -I.

ifeq ($(DEBUG), 1)
	CFLAGS += -g -DDEBUG=1
	export DEBUG
else
	CFLAGS += -DDEBUG=0
endif

NAME = libft.a

FILES := ft_atoi		ft_bzero		ft_calloc \
		 ft_isalnum		ft_isalpha		ft_isascii \
		 ft_isdigit		ft_isprint		ft_isspace \
		 ft_itoa		ft_memchr		ft_memcmp \
		 ft_memcpy		ft_memmove		ft_memset \
		 ft_putchar_fd	ft_putendl_fd	ft_putnbr_base_fd \
		 ft_putunbr_base_fd				ft_putnbr_fd \
		 ft_putstr_fd	ft_putptr_fd	ft_split \
		 ft_strchr		ft_strdup		ft_striteri \
		 ft_strjoin		ft_strlcat		ft_strlcpy \
		 ft_strlen		ft_strmapi		ft_strncmp \
		 ft_strnstr		ft_strrchr		ft_strtrim \
		 ft_substr		ft_tolower		ft_toupper \
		 ft_lstadd_back	ft_lstadd_front	ft_lstclear \
		 ft_lstdelone	ft_lstiter		ft_lstlast \
		 ft_lstmap		ft_lstnew		ft_lstsize \
		 get_next_line	ft_printf		ft_abs \
		 ft_arrmax		ft_arrmin		ft_atoi_strict \
		 ft_log_base_n	ft_memswap		ft_log \
		 ft_split_free	ft_min			ft_max \
		 ft_atoi_base	ft_atou_base	ft_atod \
		 ft_atod_strict

SRC_DIR := src/
OBJ_DIR := obj/

SRC := $(addsuffix .c, $(addprefix $(SRC_DIR), $(FILES)))
OBJ := $(addsuffix .o, $(addprefix $(OBJ_DIR), $(FILES)))
DEP := $(OBJ:.o=.d)

C_GRAY = \033[1;30m
C_ORANGE = \033[0;33m
C_RED = \033[0;31m
NC = \033[0m
PREFIX = $(C_ORANGE)<$(NAME)>

all: $(NAME)

bonus: $(NAME)

list:
	@echo $(NUM_FD)

$(NAME): $(OBJ)
	@printf "$(PREFIX) $(NC)CREATING $(NAME)\n"
	@ar rcs $(NAME) $(OBJ)

-include $(DEP)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR:/=)
	@printf "$(PREFIX) $(C_GRAY)COMPILING $@$(NC)\n"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

# doesn't work on macs for no apparent reason
#$(OBJ_DIR):
#	@mkdir $(OBJ_DIR)

$(OBJ_DIR:/=):
	@mkdir $(OBJ_DIR)

clean:
	@printf "$(PREFIX) $(C_RED)REMOVING OBJECT FILES$(NC)\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
