CC = g++
CFLAGS = -Iinclude -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

TARGET = run
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
DUMP_DIR = dump

SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/vector.cpp $(SRC_DIR)/tokenizer.cpp $(SRC_DIR)/parser.cpp $(SRC_DIR)/tree.cpp $(SRC_DIR)/codeGenerator.cpp
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

$(BIN_DIR)/$(TARGET): $(OBJ) 
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

clean:
	@rm -rf $(BIN_DIR) $(BUILD_DIR) $(DUMP_DIR)

run: $(BIN_DIR)/$(TARGET)
	@mkdir -p $(DUMP_DIR)
	@./$<
