# Директории
SRC_DIR = .
BUILD_DIR = build
SRC_DIR_FRONTEND = Frontend/src
SRC_DIR_BACKEND = Backend
INC_DIR = -I. -IBackend/Assembler/include -IBackend/common -IBackend/Stack -IFrontend/include -IBackend/Processor/include

# Исходные файлы
SRC_MAIN = main.cpp
SRC_FRONTEND = $(wildcard $(SRC_DIR_FRONTEND)/*.cpp)
SRC_BACKEND = $(wildcard $(SRC_DIR_BACKEND)/Assembler/src/*.cpp) \
              $(wildcard $(SRC_DIR_BACKEND)/Processor/src/*.cpp) \
              $(wildcard $(SRC_DIR_BACKEND)/Stack/*.cpp)

# Объектные файлы
OBJ_MAIN = $(addprefix $(BUILD_DIR)/,$(SRC_MAIN:.cpp=.o))
OBJ_FRONTEND = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FRONTEND))
OBJ_BACKEND = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_BACKEND))

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra $(INC_DIR)

# Цель по умолчанию
all: program

# Сборка программы
program: $(OBJ_MAIN) $(OBJ_FRONTEND) $(OBJ_BACKEND)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Правила для объектных файлов
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создание директории сборки
$(BUILD_DIR):
	@mkdir -p $@
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR_FRONTEND)
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR_BACKEND)/Assembler/src
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR_BACKEND)/Processor/src
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR_BACKEND)/Stack

# Очистка
clean:
	rm -rf $(BUILD_DIR) program

.PHONY: all clean run
