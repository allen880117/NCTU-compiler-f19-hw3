CC      = g++
LEX     = flex
YACC    = bison
CFLAGS  = -Wall -std=c++11
LIBS    = -lfl -ly
INCLUDE = -Iinclude

SCANNER = scanner
PARSER  = parser

ASTDIR = src/AST/
AST := $(shell find $(ASTDIR) -name '*.cpp')

VISITORDIR = src/visitor/
VISITOR := $(shell find $(VISITORDIR) -name '*.cpp')

SRC := $(AST) \
       $(VISITOR)

EXEC = $(PARSER)
OBJS = $(PARSER:=.cpp) \
       $(SCANNER:=.cpp) \
       $(SRC)

# Substitution reference
DEPS := $(OBJS:%.cpp=%.d)
OBJS := $(OBJS:%.cpp=%.o)

all: $(EXEC)

# Static pattern rule
$(SCANNER).cpp: %.cpp: %.l
	$(LEX) -o $@ $<

$(PARSER).cpp: %.cpp: %.y
	$(YACC) -o $@ --defines=parser.h -v $<

%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) $(INCLUDE) -c -MMD $<

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(INCLUDE)

clean:
	$(RM) $(DEPS) $(SCANNER:=.cpp) $(PARSER:=.cpp) $(OBJS) $(EXEC)

-include $(DEPS)
