export INCLUDE_DIR := 
export SRC_DIR := 
export OBJ_DIR := 
export NDK_ROOT := 
export CC := 
export CXX := 
export LD := 
export SYSROOT := 
export SHELL := 
TMP_OUT_LIBS_DIR := 
OUTPUT_DIR := 
DEPENDENT_LIBS := 
BINARY_NAME := 
TARGET_NAME := 
CF := 
CCF := 
CPPF:= 

SRC := $(CF) $(CCF) $(CPPF)
OBJ := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(patsubst %.cc, %.o, $(SRC)))))
TARGET := $(addprefix $(OUTPUT_DIR)/, $(BINARY_NAME))

all: files $(TARGET)

files:
ifdef CF
	@$(MAKE) -f Makefile.src TARGET="$(TARGET_NAME)" SUFFIX=c COMPILER_C="$(CC)" SRC_FILES="$(CF)"
endif
ifdef CCF
	@$(MAKE) -f Makefile.src TARGET="$(TARGET_NAME)" SUFFIX=cc COMPILER_CXX="$(CXX)" SRC_FILES="$(CCF)"
endif
ifdef CPPF
	@$(MAKE) -f Makefile.src TARGET="$(TARGET_NAME)" SUFFIX=cpp COMPILER_CXX="$(CXX)" SRC_FILES="$(CPPF)"
endif

$(TARGET): $(OBJ) $(DEPENDENT_LIBS)
	@echo '[Build]                  ': $(BINARY_NAME)
	$(LD)

rebuild: all

.PHONY: all rebuild files

