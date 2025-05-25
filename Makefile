SRC_DIR = .
BUILD_DIR = build
SRC_DIR_FRONTEND = Frontend/src
SRC_DIR_BACKEND = Backend
INC_DIR = -I. -IBackend/Assembler/include -IBackend/common -IBackend/Stack -IFrontend/include -IBackend/Processor/include

SRC_MAIN = main.cpp
SRC_FRONTEND = $(wildcard $(SRC_DIR_FRONTEND)/*.cpp)
SRC_BACKEND = $(wildcard $(SRC_DIR_BACKEND)/Assembler/src/*.cpp) \
              $(wildcard $(SRC_DIR_BACKEND)/Processor/src/*.cpp) \
              $(wildcard $(SRC_DIR_BACKEND)/Stack/*.cpp)

OBJ_MAIN = $(addprefix $(BUILD_DIR)/,$(SRC_MAIN:.cpp=.o))
OBJ_FRONTEND = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FRONTEND))
OBJ_BACKEND = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_BACKEND))

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra $(INC_DIR)

all: program

program: $(OBJ_MAIN) $(OBJ_FRONTEND) $(OBJ_BACKEND)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $@
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR_FRONTEND)
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR_BACKEND)/Assembler/src
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR_BACKEND)/Processor/src
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR_BACKEND)/Stack

clean:
	rm -rf $(BUILD_DIR) program

.PHONY: all clean run
