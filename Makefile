NAME = minishell

LIBFTDIR = libft
LIBSRCS = $(LIBFTDIR)/src

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFTDIR)/includes -MMD -MP -g3
LDFLAGS = -lreadline
RM := rm -f

##======================    MINISHELL SOURCES    ======================##
SRCSDIR = srcs

MAIN = main ms_utils ms_utils2 ms_clean
TESTER = print_test
TOKENISER = token_creator list_handler token_utils
LEXICAL = lex_analysis lex_heredoc lex_utils
PARSER = parsing parsing_utils ft_list_cmd
TRANSLATOR = translator joined_list final_joined_list
EXPANSER = expanser expanser_utils split_expand remplace_expand remplace_expand_utils clear_multi_space
EXECUTOR = exec_cmd exec_utils exec_parse exec_heredoc exec_file_handler exec_file_handler_solo exec_heredoc_utils exec_cmd_utils
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


##==================    OBJECTS & DEPENDENCIES    ===================##
OBJDIR = objects
OBJS = $(SRCS:$(SRCSDIR)/%.c=$(OBJDIR)/%.o)
OBJ_SUBDIRS = \
	$(OBJDIR) \
	$(OBJDIR)/tester \
	$(OBJDIR)/token \
	$(OBJDIR)/lexical \
	$(OBJDIR)/parsing \
	$(OBJDIR)/translator \
	$(OBJDIR)/expanser \
	$(OBJDIR)/exec \
	$(OBJDIR)/builtins

DEPS = $($(OBJDIR)/%.o=.d)
-include $(DEPS)


##========================    LIBFT LIBRARY    =======================##
LIBFT = $(LIBFTDIR)/libft.a



##=========================    MAIN RULES    =========================##



all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "🔥\\e[1;33mMinishell compiled\\e[0m🔥"

$(OBJDIR)/%.o: $(SRCSDIR)/%.c $(HEADERS)  Makefile | $(OBJ_SUBDIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_SUBDIRS):
	mkdir -p $@

$(LIBFT): FORCE
	@$(MAKE) -C $(LIBFTDIR) --no-print-directory


##============================	VALGRIND RULES	============================##
val:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=ignore_readline.supp --track-origins=yes --show-mismatched-frees=yes ./$(NAME)

valmax:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=ignore_readline.supp --track-origins=yes --show-mismatched-frees=yes ./$(NAME)

clean:
	$(RM) -rf $(OBJDIR) $(SRCSDIR)/*.d $(SRCSDIR)/*.o
	$(MAKE) -C $(LIBFTDIR) clean

valmax:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=ignore_readline.supp --track-origins=yes --show-mismatched-frees=yes ./$(NAME)


##============================	CLEANING RULES	============================##
clean:
	@$(RM) -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean --no-print-directory
	@echo "\033[92mClean minishell\033[0m"

fclean:
	@$(RM) -rf $(OBJDIR)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean --no-print-directory
	@echo "\033[92mClean minishell\033[0m"

re: fclean all

.PHONY: all clean fclean re

.PHONY: FORCE
FORCE:
