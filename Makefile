# Compilador
CC = g++

# Flags de compilação (Avisos + Incluir a pasta include)
CFLAGS = -Wall -Wextra -O2 -I$(INCDIR)

# Bibliotecas (Devem ser linkadas no FINAL do comando)
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Pastas
SRCDIR = source
OBJDIR = obj
INCDIR = include

# Ficheiros
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
TARGET = physicsEngine

# Regra principal
all: $(TARGET)

# Cria o executável ligando os objetos (Nota o $(LIBS) no fim!)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Compila cada .cpp num .o dentro da pasta obj/
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Correr o jogo
run: all
	./$(TARGET)

.PHONY: all clean run
