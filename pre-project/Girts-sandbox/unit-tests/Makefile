# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

# Files
SRC = $(SRC_DIR)/factorial.cpp $(SRC_DIR)/factorial_tests.cpp
OBJS = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
FACTORIAL_TESTS = $(BIN_DIR)/factorial_tests

# Targets
all: $(FACTORIAL_TESTS)

$(FACTORIAL_TESTS): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)