##
## Makefile for 42sh in /u/all/cuvill_h/cu/dev/42sh
## 
## Made by hugo cuvillier
## Login   <cuvill_h@epitech.net>
## 
## Started on  Wed May 19 16:48:28 2010 hugo cuvillier
##

###############################################################################

## SYSTEM DETECTION
SYSTEM		= $(shell uname -s)
SYSTEM		!= uname -s

## COMPILATION/LINKING OPTIONS

INCLUDES	= -I./includes
COMPIL_CF	= -W -Wall -ansi -pedantic -Wstrict-prototypes
OPTI_CF		= -pipe -funroll-loops -g3
SYS_CF		= -D $(SYSTEM)
CFLAGS		= $(INCLUDES) $(COMPIL_CF) $(OPTI_CF) $(SYS_CF)
LDFLAGS		= -ltermcap
RM		= rm -f

## DIRECTORIES PATHS

SRCS_DIR	= ./srcs/
AUTO_DIR	= autocompletion/
BUILT_DIR	= builtin/
ENV_DIR		= env/
HIST_DIR	= history/
LIB_DIR		= lib/
LEXER_DIR	= lexer/
PARS_DIR	= parseur/
PATH_DIR	= path_management/
TC_DIR		= termcaps/
LIST_DIR	= double_linked_lists/

###############################################################################

NAME		= 42sh

##
##sources
##


SRCS		= $(SRCS_DIR)main.c

##
##autocompletion
##
SRCS		+= $(SRCS_DIR)$(AUTO_DIR)auto.c						\
		   $(SRCS_DIR)$(AUTO_DIR)parse_exec.c					\
		   $(SRCS_DIR)$(AUTO_DIR)parse_path.c					\
		   $(SRCS_DIR)$(AUTO_DIR)sort_list.c					\
		   $(SRCS_DIR)$(AUTO_DIR)aff_tty.c					\
		   $(SRCS_DIR)$(AUTO_DIR)semi_comp.c					\
		   $(SRCS_DIR)$(AUTO_DIR)aff_tty_utils.c

##
##builtins
##
SRCS		+= $(SRCS_DIR)$(BUILT_DIR)cd.c						\
		   $(SRCS_DIR)$(BUILT_DIR)echo.c					\
		   $(SRCS_DIR)$(BUILT_DIR)clear.c					\
		   $(SRCS_DIR)$(BUILT_DIR)help.c					\
		   $(SRCS_DIR)$(BUILT_DIR)alias.c					\
		   $(SRCS_DIR)$(BUILT_DIR)put_alias.c					\
		   $(SRCS_DIR)$(BUILT_DIR)lib_alias.c					\
		   $(SRCS_DIR)$(BUILT_DIR)load_conf.c					\
		   $(SRCS_DIR)$(BUILT_DIR)unalias.c					\
		   $(SRCS_DIR)$(BUILT_DIR)history.c					\
		   $(SRCS_DIR)$(BUILT_DIR)builtin.c

##
##env
##
SRCS		+= $(SRCS_DIR)$(ENV_DIR)putenv.c					\
		   $(SRCS_DIR)$(ENV_DIR)env.c						\
		   $(SRCS_DIR)$(ENV_DIR)unsetenv.c					\
		   $(SRCS_DIR)$(ENV_DIR)setenv.c					\
		   $(SRCS_DIR)$(ENV_DIR)path_to_tab.c
##
##history
##
SRCS		+= $(SRCS_DIR)$(HIST_DIR)set_history.c

##
##lib
##
SRCS		+= $(SRCS_DIR)$(LIB_DIR)xfunc.c						\
		   $(SRCS_DIR)$(LIB_DIR)xfunc2.c					\
		   $(SRCS_DIR)$(LIB_DIR)xunistd.c					\
		   $(SRCS_DIR)$(LIB_DIR)list_to_tab.c					\
		   $(SRCS_DIR)$(LIB_DIR)error.c						\
		   $(SRCS_DIR)$(LIB_DIR)list.c						\
		   $(SRCS_DIR)$(LIB_DIR)tools.c						\
		   $(SRCS_DIR)$(LIB_DIR)str.c						\
		   $(SRCS_DIR)$(LIB_DIR)get_next_line.c					\
		   $(SRCS_DIR)$(LIB_DIR)sig.c						\
		   $(SRCS_DIR)$(LIB_DIR)x_sys.c						\
		   $(SRCS_DIR)$(LIB_DIR)string_mod_functions.c				\
		   $(SRCS_DIR)$(LIB_DIR)string_types_tests.c				\
		   $(SRCS_DIR)$(LIB_DIR)my_abspath.c					\
		   $(SRCS_DIR)$(LIB_DIR)$(LIST_DIR)lists_del.c				\
		   $(SRCS_DIR)$(LIB_DIR)$(LIST_DIR)lists_core.c				\
		   $(SRCS_DIR)$(LIB_DIR)$(LIST_DIR)lists_funcs.c			\
		   $(SRCS_DIR)$(LIB_DIR)$(LIST_DIR)lists_op.c				\
		   $(SRCS_DIR)$(LIB_DIR)$(LIST_DIR)my_str_to_wordlist.c			\

##
##lexer
##
SRCS		+= $(SRCS_DIR)$(LEXER_DIR)lexer.c					\
		   $(SRCS_DIR)$(LEXER_DIR)lexer_funcs.c					\
		   $(SRCS_DIR)$(LEXER_DIR)lexlist_core.c				\
		   $(SRCS_DIR)$(LEXER_DIR)lexlist_funcs.c				\
		   $(SRCS_DIR)$(LEXER_DIR)lex_types.c					\
		   $(SRCS_DIR)$(LEXER_DIR)format_verif.c				\
		   $(SRCS_DIR)$(LEXER_DIR)quote_management.c				\
		   $(SRCS_DIR)$(LEXER_DIR)spacialize.c					\
		   $(SRCS_DIR)$(LEXER_DIR)spaces_management.c				\
		   $(SRCS_DIR)$(LEXER_DIR)spacialized_size.c				\

##
##parseur
##
SRCS		+= $(SRCS_DIR)$(PARS_DIR)parser.c					\
		   $(SRCS_DIR)$(PARS_DIR)dbout.c					\
		   $(SRCS_DIR)$(PARS_DIR)free_fifo.c					\
		   $(SRCS_DIR)$(PARS_DIR)check_alias_lexlist.c				\
		   $(SRCS_DIR)$(PARS_DIR)manage_fifo.c					\
		   $(SRCS_DIR)$(PARS_DIR)set_flags.c					\
		   $(SRCS_DIR)$(PARS_DIR)manage_delim.c					\
		   $(SRCS_DIR)$(PARS_DIR)setvar.c					\
		   $(SRCS_DIR)$(PARS_DIR)set_fifo.c					\
		   $(SRCS_DIR)$(PARS_DIR)set_redirect.c					\
		   $(SRCS_DIR)$(PARS_DIR)verif_list.c					\
		   $(SRCS_DIR)$(PARS_DIR)verif_list_par.c				\
		   $(SRCS_DIR)$(PARS_DIR)manage_execution.c				\
		   $(SRCS_DIR)$(PARS_DIR)execute_command.c				\

##
##path management
##
SRCS		+= $(SRCS_DIR)$(PATH_DIR)get_path.c					\
		   $(SRCS_DIR)$(PATH_DIR)pathdirs_to_list.c

##
##termcaps
##
SRCS            += $(SRCS_DIR)$(TC_DIR)termcaps.c					\
		   $(SRCS_DIR)$(TC_DIR)utils.c						\
		   $(SRCS_DIR)$(TC_DIR)utils2.c						\
		   $(SRCS_DIR)$(TC_DIR)input.c						\
		   $(SRCS_DIR)$(TC_DIR)input2.c						\
		   $(SRCS_DIR)$(TC_DIR)list.c						\
		   $(SRCS_DIR)$(TC_DIR)list2.c						\
		   $(SRCS_DIR)$(TC_DIR)list3.c						\
		   $(SRCS_DIR)$(TC_DIR)ctrl_fct.c					\
		   $(SRCS_DIR)$(TC_DIR)ctrl_fct2.c					\
		   $(SRCS_DIR)$(TC_DIR)return_fct.c

##
## C FILES TO OBJECTS
##

OBJS		= $(SRCS:.c=.o)

##
## SYSTEM ADAPTATIONS
##

CC		= CC_$(SYS)
CC		= clang
CC_FreeBSD	= cc
CC_NetBSD	= /usr/bin/clang
CC_sun4		= /usr/sfw/bin/clang
CC_ia64-linux	= /usr/bin/clang
CC_i486-linux	= clang
CC_intel-mac	= clang

MAKE		= MAKE_$(SYS)
MAKE		= make
MAKE_FreeBSD	= make
MAKE_NetBSD	= /usr/bin/make
MAKE_sun4	= /usr/css/bin/make
MAKE_ia64-linux	= make
MAKE_i486-linux	= make
MAKE_intel-mac	= make

##
## RULES
##

$(NAME)		: $(OBJS)
		  @echo -e "\e[47;45;1m[SYSTEM] $(SYSTEM)\e[0m"
		  @echo -e "\e[49;31;1m[CFLAGS] $(CFLAGS)\e[0m"
		  @echo -e "\e[49;31;1m[LINKING] $(NAME) with $(LDFLAGS)\e[0m"
		  $(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
		  @echo -e "\e[49;32;1m	!! 42sh recompiled and ready to use !!\n\tYou like it hum ?\e[0m"

all		: $(NAME)

clean		:
		  @echo -e "\e[49;31;1m[CLEANING]\e[0m"
		  $(RM) $(OBJS)
		  @echo -e "\e[49;32;1m	-->Directory was cleaned, and objects filed were removed\e[0m"

fclean		: clean
		  @echo -e "\e[49;31;1m[FULL CLEANING]\e[0m"
		  $(RM) $(NAME)
		  @echo -e "\e[49;32;1m	-->exec file was removed\e[0m"

re		: fclean all

.PHONY		: clean fclean all re

.SUFFIXES	: .c .o .h

.c.o		:
		  $(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

