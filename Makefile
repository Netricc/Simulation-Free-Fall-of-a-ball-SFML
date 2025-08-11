SFML_PATH = /opt/homebrew/Cellar/sfml/3.0.1
FINAL_FILE = main

cppFileNames := $(shell find ./src -type f -name "*.cpp")

all: compile

compile:
	mkdir -p bin
	g++ -std=c++23 $(cppFileNames) -I$(SFML_PATH)/include -o ./bin/$(FINAL_FILE) \
	-L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network 

clean:
	rm -rf $(FINAL_FILE) bin
