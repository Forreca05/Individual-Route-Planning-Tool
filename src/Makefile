# Nome do executável
TARGET = main

# Lista de ficheiros-fonte
SRCS = main.cpp algorithms.cpp environmentally.cpp independent.cpp restricted.cpp utils.cpp

# Lista de ficheiros-objeto (transforma os .cpp em .o)
OBJS = $(SRCS:.cpp=.o)

# Compilador
CXX = g++

# Flags de compilação (opcional)
CXXFLAGS = -Wall -Wextra -std=c++11

# Regra principal: compila todos os .o num único executável "main"
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

# Regra para compilar cada ficheiro .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar ficheiros compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Limpar apenas os .o
clean_o:
	rm -f $(OBJS)
