TARGET := main

CC := g++
CXXFLAGS := -g -Wall

LINKER := g++ -o

SRCDIR := src
OBJDIR := obj

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS)
	@echo "Linking Complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	rm -rf obj;
	mkdir obj;
	rm main;
