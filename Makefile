CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++20 -Iinclude
TARGET = diy-camera

SRC_DIR := src
OBJ_DIR := obj
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: debug

debug: CXXFLAGS += -g -O0 -DDEBUG
debug: print_debug $(TARGET)
	@echo "~~ compiled debug build ~~"

print_debug:
	@echo "~~ making release build ~~"

release: CXXFLAGS += -O2
release: print_release $(TARGET)
	@echo "~~ compiled release build ~~"

print_release:
	@echo "~~ making release build ~~"

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean debug release
