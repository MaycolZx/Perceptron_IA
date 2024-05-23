# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -L${PWD}/lib/ -lglfw3 -lglut -lGL -lGLU -lX11 -lpthread -lXrandr -lXi -ldl
SRCDIR = src
INCDIR = include
BINDIR = bin
TARGET = mi_programa
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

# Regla principal
$(BINDIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $^ -o $@ $(LDFLAGS)

# Regla para compilar objetos
$(BINDIR)/%.o: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Crear directorio binario si no existe
$(BINDIR):
	mkdir -p $(BINDIR)

# Limpiar archivos generados
clean:
	rm -rf $(BINDIR)

# Evitar conflictos con archivos llamados "clean"
.PHONY: clean

