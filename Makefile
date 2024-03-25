.PHONY:			all clean fclean re
MACHINE 		:= $(shell uname -m)
NAME			= minishell

CC				= gcc
# CFLAGS			= -g -Wall -Wextra -Werror -MMD
CFLAGS			= -g -MMD
override CFLAGS	+= -I/opt/homebrew/opt/readline/include -DRONIN_CL
override LIBS	+= -L/opt/homebrew/opt/readline/lib -lreadline
RM				= rm -rf

INCLUDES		= ./includes
SRCS_DIR		= ./src
UTILS_DIR		= ./utils
LIBFT_DIR		= ./libs/libft
LIBS_DIR		= ./libs
OBJS_DIR		= ./obj

LIBFT			= $(LIBFT_DIR)/libft-$(MACHINE).a

rwildcard		= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRCS			= $(call rwildcard, $(SRCS_DIR)/, *.c) $(call rwildcard, $(UTILS_DIR)/, *.c)
OBJS 			= $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS 			= $(OBJS:.o=.d)
LIBS			= -L$(LIBFT_DIR) -lreadline

$(NAME): $(OBJS) Makefile
	@echo "Linking..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS) -I$(INCLUDES) $(LIBFT)
	@echo "Build complete."

all: libft $(NAME)
	@echo "Building $(NAME)..."
	
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

-include $(DEPS)

libft:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS_DIR) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)

re: fclean all