OBJ_DIR=obj
TARGET_DIR=bin
TARGET=$(TARGET_DIR)/Client

SRC_DIR=src
SRC_CURLPP_DIR=curlpp/src

SRC_CPP_FILES=./$(SRC_DIR)/main.cpp
SRC_CPP_FILES+=./$(SRC_DIR)/Client.cpp

SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/cURLpp.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/Easy.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/Exception.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/Form.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/Info.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/Multi.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/OptionBase.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/Options.cpp

SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/internal/CurlHandle.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/internal/OptionList.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/internal/OptionSetter.cpp
SRC_CPP_FILES+=./$(SRC_CURLPP_DIR)/curlpp/internal/SList.cpp

SRC_HPP_FILES+=./$(SRC_DIR)/json.hpp

INCL_PATHS=./$(SRC_DIR)
INCL_PATHS+=./curlpp/include/curlpp

LIB=curl
LIB+=ssl
LIB+=stdc++

OBJ_CPP_FILES=$(patsubst ./%.cpp,$(OBJ_DIR)/%.o,$(SRC_CPP_FILES))
DEPS=$(OBJ_CPP_FILES:.o=.d)
INCL_ARGS=$(patsubst ./%,-I./%,$(INCL_PATHS))
LIB_ARGS=$(patsubst %,-l%,$(LIB))

OPTIM=-Os

CC = gcc
CXXFLAGS = -std=c++0x $(INCL_ARGS)
CFLAGS = -Wall -Werror $(OPTIM)
LFLAGS = -L


all: $(TARGET)

-include $(DEPS)

$(TARGET): $(TARGET_DIR) $(OBJ_DIR) $(OBJ_CPP_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_CPP_FILES) $(LIB_ARGS)
	
$(OBJ_CPP_FILES):
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $(patsubst obj/%.o,%.cpp,$@)

$(TARGET_DIR):
	mkdir $(TARGET_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	

# cleanup
clean:
	rm -rf *.o $(TARGET_DIR) $(OBJ_DIR)
	
	