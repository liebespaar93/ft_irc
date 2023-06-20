include color.mk

NAME = server


CC = c++
CFLAGS = 
IFLAGS = -I ./src  -I ./src/cmd -I ./src/control
DFLAGS = 
CXXFLAGS = 


ROOTDIR = $(abspath $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))
SRC_DIR = $(ROOTDIR)/src
SRC_CONTROL_DIR = $(ROOTDIR)/src/control

OBJ_DIR = $(ROOTDIR)/obj
INCLUDE_DIR = $(ROOTDIR)/include

SRC_FILE =	main.cpp	\
			Socket.cpp	\
			Server.cpp	\
			User.cpp	\
			Channel.cpp	\
			Utile.cpp	\

SRC_C = $(addprefix $(SRC_DIR)/, $(SRC_FILE))

SRC_CONTROL_FILE =	ChannelControl.cpp \
					UserControl.cpp


SRC_CONTROL_C = $(addprefix $(SRC_CONTROL_DIR)/, $(SRC_CONTROL_FILE))

OBJS =	$(SRC_C:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)	\
		$(SRC_CONTROL_C:$(SRC_CONTROL_DIR)/%.cpp=$(OBJ_DIR)/%.o)

OBJS_CLEAN = $(OBJS)

all: $(NAME)

play : DFLAGS+= -D PLAY
play : CXXFLAGS+= -pedantic -g3 -fsanitize=address -fsanitize=undefined -fsanitize=bounds -fsanitize=null
play : fclean $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(FG_LYELLOW)"
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(FG_LMAGENTA)$(CC) $(FG_BLUE) $(CFLAGS)"
	@(for i in $(IFLAGS); do echo $$i; done)
	@echo "$(LDLIBS) $(FG_LCYAN)"
	@(for i in $(OBJS); do echo $$i; done)
	@echo "$(FG_BLUE)-o $(FG_LYELLOW) $(NAME) $(NO_COLOR)"

$(OBJ_DIR) :
	@echo "$(FG_LGREEN)"
	mkdir $@
	@echo "$(NO_COLOR)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_CONTROL_DIR)/%.cpp
	@$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "$(FG_LRED)"
	rm -f $(OBJS_CLEAN)
	@echo "$(NO_COLOR)"

fclean: OBJS+=$(NAME)
fclean: clean

re: fclean all

.PHONY: all re clean fclean play