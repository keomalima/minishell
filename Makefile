NAME = minishell

LIBFTDIR := libft
LIBSRCS := $(LIBFTDIR)/src

CC := cc
CFLAGS := -Wall -Wextra -Werror -Iincludes -I$(LIBFTDIR)/includes -MMD -MP -g3
LDFLAGS := -lreadline
RM := rm -f

SRCSDIR := srcs
OBJDIR := objects

OBJ_SUBDIR = \
	$(OBJDIR) \
	$(OBJDIR)/tester \
	$(OBJDIR)/token \
	$(OBJDIR)/lexical \
	$(OBJDIR)/parsing \
	$(OBJDIR)/translator \
	$(OBJDIR)/expanser \
	$(OBJDIR)/exec \
	$(OBJDIR)/builtins

MAIN = main ms_utils ms_utils2 ms_clean
TESTER = print_test
TOKENISER = token_creator list_handler token_utils
LEXICAL = lex_analysis lex_heredoc
PARSER = parsing parsing_utils ft_list_cmd
TRANSLATOR = translator joined_list final_joined_list
EXPANSER = expanser expanser_utils split_expand remplace_expand remplace_expand_utils clear_multi_space
EXECUTOR = exec_cmd exec_utils exec_parse exec_heredoc exec_file_handler exec_file_handler_solo
BUILTINS = exec_builtin builtins_clean env_management\
			cd_command cd_update_pwd cd_check_valid\
			pwd_command\
			env_command\
			echo_command\
			export_command export_utils export_get_variable export_modify_env\
			exit_command\
			unset_command

SRCS = $(addsuffix .c, $(addprefix $(SRCSDIR)/, $(MAIN))) \
			$(addsuffix .c, $(addprefix $(SRCSDIR)/tester/, $(TESTER))) \
			$(addsuffix .c, $(addprefix $(SRCSDIR)/token/, $(TOKENISER))) \
			$(addsuffix .c, $(addprefix $(SRCSDIR)/lexical/, $(LEXICAL))) \
			$(addsuffix .c, $(addprefix $(SRCSDIR)/parsing/, $(PARSER))) \
			$(addsuffix .c, $(addprefix $(SRCSDIR)/translator/, $(TRANSLATOR))) \
			$(addsuffix .c, $(addprefix $(SRCSDIR)/expanser/, $(EXPANSER))) \
			$(addsuffix .c, $(addprefix $(SRCSDIR)/exec/, $(EXECUTOR))) \
			$(addsuffix .c, $(addprefix $(SRCSDIR)/builtins/, $(BUILTINS)))

OBJS := $(SRCS:$(SRCSDIR)/%.c=$(OBJDIR)/%.o)

DEPS = $($(OBJDIR)/%.o=.d)

LIBFT_SRCS := $(LIBSRCS)/ft_atoi.c $(LIBSRCS)/ft_bzero.c $(LIBSRCS)/ft_calloc.c \
			$(LIBSRCS)/ft_isalnum.c $(LIBSRCS)/ft_isalpha.c $(LIBSRCS)/ft_isascii.c \
			$(LIBSRCS)/ft_isdigit.c $(LIBSRCS)/ft_isprint.c $(LIBSRCS)/ft_memchr.c \
			$(LIBSRCS)/ft_memcmp.c $(LIBSRCS)/ft_memcpy.c $(LIBSRCS)/ft_memmove.c \
			$(LIBSRCS)/ft_memset.c $(LIBSRCS)/ft_strchr.c $(LIBSRCS)/ft_strdup.c \
			$(LIBSRCS)/ft_strlcat.c $(LIBSRCS)/ft_strlcpy.c $(LIBSRCS)/ft_strlen.c \
			$(LIBSRCS)/ft_strncmp.c $(LIBSRCS)/ft_strnstr.c $(LIBSRCS)/ft_strrchr.c \
			$(LIBSRCS)/ft_tolower.c $(LIBSRCS)/ft_toupper.c $(LIBSRCS)/ft_itoa.c \
			$(LIBSRCS)/ft_putchar_fd.c $(LIBSRCS)/ft_putendl_fd.c \
			$(LIBSRCS)/ft_putnbr_fd.c $(LIBSRCS)/ft_putstr_fd.c \
			$(LIBSRCS)/ft_split.c $(LIBSRCS)/ft_striteri.c \
			$(LIBSRCS)/ft_strjoin.c $(LIBSRCS)/ft_strmapi.c \
			$(LIBSRCS)/ft_strtrim.c $(LIBSRCS)/ft_substr.c \
			$(LIBSRCS)/get_next_line.c $(LIBSRCS)/get_next_line_utils.c \
			$(LIBSRCS)/ft_printf.c $(LIBSRCS)/ft_print_char.c \
			$(LIBSRCS)/ft_print_hex.c $(LIBSRCS)/ft_print_int.c \
			$(LIBSRCS)/ft_print_ptr.c $(LIBSRCS)/ft_lstmap.c \
			$(LIBSRCS)/ft_lstadd_back.c $(LIBSRCS)/ft_lstadd_front.c \
			$(LIBSRCS)/ft_lstclear.c $(LIBSRCS)/ft_lstdelone.c \
			$(LIBSRCS)/ft_lstiter.c $(LIBSRCS)/ft_lstlast.c \
			$(LIBSRCS)/ft_lstnew.c $(LIBSRCS)/ft_lstsize.c

LIBFT_HEADERS := $(LIBFTDIR)/includes/libft.h
LIBFT := $(LIBFTDIR)/libft.a

HEADERS := includes/minishell.h  $(LIBFT_HEADERS)



all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c $(HEADERS) $(LIBFT_SRCS) Makefile | $(OBJDIR)/token $(OBJDIR)/parsing $(OBJDIR)/translator $(OBJDIR)/expanser $(OBJDIR)/exec $(OBJDIR)/tester $(OBJDIR)/builtins $(OBJDIR)/lexical
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_SUBDIR):
	mkdir -p $@

$(LIBFT): $(LIBFT_SRCS) $(LIBFT_HEADERS)
	$(MAKE) -C $(LIBFTDIR)

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=ignore_readline.supp --track-origins=yes --show-mismatched-frees=yes ./$(NAME)

valmax:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=ignore_readline.supp --track-origins=yes --show-mismatched-frees=yes ./$(NAME)

clean:
	$(RM) -rf $(OBJDIR) $(SRCSDIR)/*.d $(SRCSDIR)/*.o
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)