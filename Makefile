NAME = particleSystem

OS := $(shell uname)
OPTIONS:= 
ifeq ($(OS),Darwin)
	OPTIONS += -framework OpenCL
else
	OPTIONS += -l OpenCL
endif

SRC = main.cpp GPU.cpp Graphics.cpp Input.cpp

FRAMEWORKS = -framework OpenGl

BREW_INC = -I ~/.brew/include

GLFW_LINK = -L ~/.brew/lib -lglfw

all : $(NAME)

$(NAME) : $(SRC)
	clang++ -w $(SRC) -o $(NAME) $(FRAMEWORKS) $(BREW_INC) $(GLFW_LINK) $(OPTIONS)

fclean:
	rm -f $(NAME)

re: fclean all