include .env

CFLAGS = -std=c++17 -Iinclude -I. -I$(SFML_PATH)/include
LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system

TARGET = a.out
$(TARGET): *.cpp src/*.cpp
	g++ $(CFLAGS) -o $(TARGET) *.cpp src/*.cpp $(LDFLAGS)

.PHONY: test clean

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
