# Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/subneteo

SRCS = main.cpp Subnet.cpp
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

INPUT_DIR = input
DEFAULT_FILE = ejemplo1.txt

# Captura archivo como segundo argumento si se llama con: make run ejemplo2.txt
FILE := $(word 2, $(MAKECMDGOALS))
ifeq ($(FILE),)
  FILE := $(DEFAULT_FILE)
endif

# Regla por defecto
all: $(TARGET)

# Compilar ejecutable
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar .cpp a .o
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar programa con archivo
run: all
	$(TARGET) $(INPUT_DIR)/$(FILE)

# Ejecutar programa con entrada por teclado
manual: all
	$(TARGET)

# Limpiar objetos y binarios
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Evita que Make trate 'ejemploX.txt' como un objetivo real
%:
	@true

.PHONY: all run manual clean
