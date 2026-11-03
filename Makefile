# Compilador e opções
CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -g -Iinclude

# Pastas
SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
TARGET  := $(BIN_DIR)/cinema

# Lista de arquivos, montada automaticamente
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Alvo padrão: rodar só "make" executa este
all: $(TARGET)

# Link: junta todos os .o no executável
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilação: cada .cpp vira um .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Recompila quem inclui um .h que mudou
-include $(OBJS:.o=.d)

# Cria as pastas se não existirem
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(BIN_DIR)

.PHONY: all run clean