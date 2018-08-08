NAME = libfts.a
CC = gcc
CC_ASM = nasm

LIBDIR	= ./
SRCDIR	= srcs
INCDIR	= ./includes/
OBJDIR	= objs
HEADER	= libft.h btree.h

ifeq ($(DEBUG),yes)
	CFLAGS = -std=c99 -fPIC -Wextra -Wall -Werror -g -O0 -fsanitize=address -I./$(INCDIR)
	ASMFLAGS = -f macho64 -i $(INCDIR) -libc
else
	CFLAGS = -Ofast -std=c99 -fPIC -Wextra -Wall -Werror -I./$(INCDIR)
	ASMFLAGS = -f macho64 -i $(INCDIR)
endif

SRC_ASM = ft_isalpha ft_id ft_isdigit ft_isalnum ft_isascii ft_isprint ft_toupper ft_tolower ft_puts ft_bzero ft_memset ft_strcat ft_memcpy ft_strlen ft_strdup ft_cat ft_strcpy ft_memchr ft_memcmp ft_strcmp ft_strchr

ASM_DIR		= asm

SRC = 	$(addprefix $(ASM_DIR)/, $(addsuffix .c, $(SRC_ASM))) \

TMP = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(TMP)))

.PHONY: all re clean fclean help

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/$(ASM_DIR)/%.s
	$(CC_ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -vf $(OBJ)

fclean: clean
	rm -vf $(NAME)

re: fclean all

test: $(NAME) main.c $(OBJ)
	$(CC) $(CFLAGS)  main.c libfts.a && ./a.out

test_cat: $(NAME) cat.c $(OBJ)
	$(CC) $(CFLAGS) cat.c libfts.a -o cat
#ld hello_world.o -macosx_version_min 10.8 -lSystem && ./a.out
help:
	@echo
	@echo "Librairy $(NAME)"
	@echo
	@echo "--------------------------------------------------------------------------"
	@echo " Disp rules."
	@echo
	@echo " all     : Compile the librairy if a file has changed, stored in $(LIBDIR)."
	@echo " re      : Recompile all objets of the librairy."
	@echo " clean   : Remove objects."
	@echo " fclean  : Remove objects and executable."
	@echo " help    : Display this."
	@echo "--------------------------------------------------------------------------"
	@echo
