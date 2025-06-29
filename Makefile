#Compilador

CXX= g++

#Flags

CXXFLAGS= -Wall -g

#Arquivos fonte

SRCS= main.cpp
HDRS= menus.h local.h veiculo.h pedido.h

#Objetos

OBJS = $(SRCS:.cpp=.o)

#Executável

TARGET= localizepp

# Regra principal

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para limpar arquivos objeto e executável

clean:
	rm -f $(OBJS) $(TARGET)
