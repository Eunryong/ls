# Compiler
CC := cc

# Compiler flags
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -I

# Directories
SRCDIR := src/ft_ls
LIBFTDIR := src/libft
LIBFT := src/libft/libft.a
INCDIR := includes
BUILDDIR := build
PWD := $(shell pwd)
# Targets
TARGET := ft_ls
SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.d)

# Includes
INC := -I./$(INCDIR)

# Default target
all: $(TARGET)

$(TARGET): $(LIBFT) $(OBJECTS)
	@echo " Linking..."
	$(CC) $(OBJECTS) $(LIBFT) $(INC) -o $(TARGET) $(FLAGS)
	@echo " Finished linking."

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " Compiling $<..."
	$(CC) $(CFLAGS) $(INC) -MMD -c -o $@ $< $(FLAGS)

$(LIBFT) :
	make -C $(LIBFTDIR) INCLUDE=$(PWD)/$(INCDIR) FLAGS=$(FLAGS)

clean:
	@echo " Cleaning..."
	make -C $(LIBFTDIR) fclean
	$(RM) -r $(BUILDDIR)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

# Dependency files
-include $(DEPS)

.PHONY: clean
