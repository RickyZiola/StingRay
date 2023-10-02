CC=g++
MAIN=main.cpp

LIBS=$(shell find -name "*.cpp" ! -name $(MAIN))

# TODO: release build process

default: lines dbg

lines:
	@echo "Current line count: $(shell find ./ -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec cat {} \; | wc -l)"

dbg-dirs:
	@rm -rf -r lib/dbg
	@rm -rf -r bin/dbg

	@mkdir -p lib
	@cd lib && mkdir -p dbg

	@mkdir -p bin
	@cd bin && mkdir -p dbg

dbg-libs:
ifneq ($(LIBS),)
	@cd lib/dbg && $(CC) -c $(foreach lib,$(LIBS), ../../$(lib)) -g -O0
endif

dbg-main:
	@cd bin/dbg && $(CC) -L../../lib/dbg $(foreach lib,$(LIBS),'-l:$(notdir $(basename $(lib))).o' ) ../../$(MAIN) -o main

dbg-run:
	@bin/dbg/main

dbg: dbg-dirs dbg-libs dbg-main dbg-run