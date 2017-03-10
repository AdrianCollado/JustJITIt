#=============================================================================#
#                                 Just JIT It                                 #
#                 Implementing your own simple JIT compiler.                  #
#-----------------------------------------------------------------------------#
# This file is the build system for *nix systems (assuming GNU tools).        #
#-----------------------------------------------------------------------------#
# Copyright (C) 2017 - Adrian J. Collado                                      #
# All Rights Reserved                                                         #
#-----------------------------------------------------------------------------#
# Permission is hereby granted, free of charge, to any person obtaining a     #
# copy of this software and associated documentation files (the “Software”),  #
# to deal in the Software without restriction, including without limitation   #
# the rights to use, copy, modify, merge, publish, distribute, sublicense,    #
# and/or sell copies of the Software, and to permit persons to whom the       #
# Software is furnished to do so, subject to the following conditions:        #
#                                                                             #
# The above copyright notice and this permission notice shall be included in  #
# all copies or substantial portions of the Software.                         #
#                                                                             #
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  #
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    #
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE #
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      #
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     #
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         #
# DEALINGS IN THE SOFTWARE.                                                   #
#=============================================================================#
.PHONY: all
all: build

.PHONY: clean
clean:
	@$(call EXECUTE,Cleaning Directory,rm -r Build/)
	@$(call EXECUTE,Cleaning Executable,rm jj)

.PHONY: build
build: Makefile jj

.PHONY: rebuild
rebuild: clean build

COM_COLOR   = \033[1;34m
OBJ_COLOR   = \033[1;36m
OK_COLOR    = \033[1;32m
ERROR_COLOR = \033[1;31m
WARN_COLOR  = \033[1;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"
DEL_STRING   = "Cleaning Directory"

define EXECUTE
printf "%b" "$(COM_COLOR)$(1) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(2) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(1)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(1)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(1)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

SRC := $(shell find Source -name '*.cpp')
OBJ := $(patsubst Source/%.cpp,Build/%.o,$(SRC))

CPPFLAGS += -IInclude -g

Build/%.o: Source/%.cpp Makefile
	@mkdir -p $(@D)
	@$(call EXECUTE,Compiling,$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -MF Build/$*.d -c -o $@ $<)

jj: $(OBJ)
	@mkdir -p $(@D)
	@$(call EXECUTE,Linking,$(CXX) -o $@ $^ $(LDFLAGS))