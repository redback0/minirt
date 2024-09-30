CC := cc
CFLAGS := -Wall -Wextra -Werror
DEBUG_FLAGS := -g -DDEBUG=1

NAME := miniRT

# list all files without file extension
FILES := main \

SRC_DIR := src/
OBJ_DIR := obj/
DEBUG_DIR := debug_obj/

SRC := $(addsuffix .c, $(addprefix $(SRC_DIR), $(FILES)))
OBJ := $(addsuffix .o, $(addprefix $(OBJ_DIR), $(FILES)))
DEP := $(OBJ:.o=.d)
DEBUG_OBJ := $(patsubst $(OBJ_DIR)%, $(DEBUG_DIR)%, $(OBJ))
DEBUG_DEP := $(DEBUG_OBJ:.o=.d)

# OS SPECIFICS
UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CFLAGS += -DMAC_OS
	MLX = minilibx_macos
	LFLAGS := -framework OpenGL -framework AppKit
endif
ifeq ($(UNAME),Linux)
	CFLAGS += -DLINUX
	MLX = minilibx-linux
	LFLAGS := -lXext -lX11 -lm
endif

DLIBS := libft $(MLX)
LIBS := ft mlx
FLIBS := $(join $(addsuffix /lib, $(DLIBS)), $(addsuffix .a, $(LIBS)))

LFLAGS += $(addprefix -L, $(DLIBS)) $(addprefix -l, $(LIBS))

IFLAGS := $(addprefix -I, $(DLIBS))

ifdef MAKE_TERMOUT
#PREFIX/COLOUR VARIABLES
C_GRAY := \033[1;30m
C_ORANGE := \033[0;33m
C_RED := \033[0;31m
C_CYAN := \033[0;36m
NC := \033[0m
endif

PREFIX := $(C_ORANGE)<$(NAME)>$(NC)

all: $(NAME)

print:
	@echo $(NAME)
	@echo $(CC)
	@echo $(CFLAGS)
	@echo $(LFLAGS)
	@echo $(IFLAGS)
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(DLIBS)
	@echo $(LIBS)
	@echo $(FLIBS)

$(NAME): $(OBJ) $(FLIBS)
	@printf "$(PREFIX) CREATING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(NAME)_debug: $(DEBUG_OBJ) $(FLIBS)
	@printf "$(PREFIX) CREATING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $(DEBUG_OBJ) $(LFLAGS)

$(FLIBS):
	@printf "$(PREFIX) MAKING $(C_CYAN)$@$(NC) ARCHIVE\n"
	@$(MAKE) -C $(dir $@) --no-print-directory -s

-include $(DEP)
-include $(DEBUG_DEP)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR:/=)
	@printf "$(PREFIX) $(C_GRAY)COMPILING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) $(IFLAGS) -MMD -c $< -o $@

$(OBJ_DIR:/=):
	@mkdir $(OBJ_DIR)

$(DEBUG_DIR)%.o: $(SRC_DIR)%.c | $(DEBUG_DIR:/=)
	@printf "$(PREFIX) $(C_GRAY)COMPILING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(IFLAGS) -MMD -c $< -o $@

$(DEBUG_DIR:/=):
	@mkdir $(DEBUG_DIR)

leaks: debug
	@printf "$(PREFIX) $(C_RED)NOT IMPLEMENTED $(NC)\n"

debug: _debug $(NAME)_debug

_debug:
	@printf "$(PREFIX) $(RED)***DEBUG MODE***$(NC)\n"

clean:
	@printf "$(PREFIX) $(C_RED)REMOVING OBJECT FILES$(NC)\n"
	@rm -rf $(OBJ_DIR) $(DEBUG_DIR)
	@printf "$(PREFIX) $(C_RED)REMOVING LIBRARIES$(NC)\n"
	@- $(foreach D, $(DLIBS), \
		2>/dev/null $(MAKE) clean fclean -C $D \
		--no-print-directory -s || true ;)

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME) $(NAME)_debug

re: fclean all

.PHONY: all clean fclean re debug debug_cflags print
