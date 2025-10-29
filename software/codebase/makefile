CPP = g++
FLAGS = -Wall -Iinclude -g -pthread
PIFLAG = -lpigpio -lrt
LIBFLAG = -Lbin -lmotor

BIN_DIR = bin
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRC))
LIB = $(BIN_DIR)/libmotor.a
EXEC = final
MAIN = main.cpp

all : $(EXEC);

$(EXEC): $(LIB) $(OBJ) | $(BIN_DIR)
	$(CPP) $(FLAGS) $(MAIN) -o $(EXEC) $(LIBFLAG) $(PIFLAG)

$(LIB) : $(OBJ) | $(BIN_DIR) 
	ar rcs $(LIB) $^

$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CPP) $(FLAGS) -c $< -o $@ $(PIFLAG)

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

clean : 
	rm -rf $(BIN_DIR) $(EXEC)


.PHONY : clean
