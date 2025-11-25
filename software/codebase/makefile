CPP = g++
FLAGS = -Wall -Iinclude -g -pthread
PIFLAG = -lpigpio -lrt

BIN_DIR = bin

# Diretórios e arquivos da biblioteca motor
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRC))
LIB = $(BIN_DIR)/libmotor.a

# Diretórios e arquivos da biblioteca camera
CAM_DIR = camera
CAM_SRC = $(wildcard $(CAM_DIR)/*.cpp)
CAM_OBJ = $(patsubst $(CAM_DIR)/%.cpp, $(BIN_DIR)/%.o, $(CAM_SRC))
CAM_LIB = $(BIN_DIR)/libcamera.a

# Execução final
EXEC = final
MAIN = main.cpp

# Flags das libs
LIBFLAG = -Lbin -lmotor -lcamera

all : $(EXEC)

# Compilação final
$(EXEC): $(LIB) $(CAM_LIB) $(OBJ) $(CAM_OBJ) | $(BIN_DIR)
	$(CPP) $(FLAGS) $(MAIN) -o $(EXEC) $(LIBFLAG) $(PIFLAG)

# Gera libmotor.a
$(LIB): $(OBJ) | $(BIN_DIR)
	ar rcs $(LIB) $^

# Gera libcamera.a
$(CAM_LIB): $(CAM_OBJ) | $(BIN_DIR)
	ar rcs $(CAM_LIB) $^

# Compila objetos da pasta src/
$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CPP) $(FLAGS) -c $< -o $@ $(PIFLAG)

# Compila objetos da pasta camera/
$(BIN_DIR)/%.o : $(CAM_DIR)/%.cpp | $(BIN_DIR)
	$(CPP) $(FLAGS) -c $< -o $@ $(PIFLAG)

# Cria pasta bin/
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpar projeto
clean:
	rm -rf $(BIN_DIR) $(EXEC)

.PHONY: clean
