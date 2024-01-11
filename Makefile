.PHONY: all clean fclean re
MACHINE			:= $(shell uname -m)

NAME			= minishell

CC				= gcc
CFLAGS			= -g -Wall -Wextra -Werror -MMD
RM				= rm -rf
INCLUDES		= ./includes
LIBFT			= -lft-$(MACHINE)

SRCS_DIR		= ./src
UTILS_DIR		= ./utils
LIBS_DIR		= ./libs
OBJS_DIR		= ./obj

rwildcard		= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRCS			= $(call rwildcard, $(SRCS_DIR)/, *.c) $(call rwildcard, $(UTILS_DIR)/, *.c)
OBJS 			= $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS 			= $(OBJS:.o=.d)
LIBS			= -L$(LIBS_DIR) $(LIBFT) -lreadline

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS) -I$(INCLUDES)

all: $(NAME)
	
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS_DIR) $(DEPS)

fclean: clean
	$(RM) $(NAME) $(ASAN_NAME)

re: fclean all