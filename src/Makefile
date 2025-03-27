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

# Regra principal: compila todos os .o num único executável "main" e apaga os .o no fim
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)
	rm -f $(OBJS)  # Apaga os ficheiros .o depois da compilação

# Regra para compilar cada ficheiro .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar tudo (executável e .o)
clean:
	rm -f $(OBJS) $(TARGET)
