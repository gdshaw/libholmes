# This file is part of libholmes.
# Copyright 2021 Graham Shaw.
# Distribution and modification are permitted within the terms of the
# GNU General Public License (version 3 or any later version).

prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
libdir = $(exec_prefix)/lib
libexecdir = $(libdir)

pkgname = holmes

CPPFLAGS = -MD -MP -I. '-DLIBEXECDIR="$(libexecdir)"' '-DPKGNAME="$(pkgname)"'
CXXFLAGS = -fPIC -O2 --std=c++17 -Wall -Wpedantic
LDLIBS = -ldl

SRC = $(wildcard src/*.cc)
BIN = $(SRC:src/%.cc=bin/%)
MAINBIN = bin/$(pkgname)
AUXBIN = $(filter-out $(MAINBIN),$(BIN))

HOLMES = $(wildcard holmes/*.cc) $(wildcard holmes/*/*.cc) $(wildcard holmes/*/*/*.cc)

.PHONY: all
all: $(BIN)

$(BIN): bin/%: src/%.o holmes.so
	@mkdir -p bin
	g++ -rdynamic -Wl,-rpath $(libdir) -o $@ $^ $(LDLIBS)

holmes.so: $(HOLMES:%.cc=%.o)
	gcc -shared -o $@ $^

.PHONY: clean
clean:
	rm -f holmes/*.[do]
	rm -f holmes/*/*.[do]
	rm -f holmes/*/*/*.[do]
	rm -f src/*.[do]
	rm -f *.so
	rm -rf bin

.PHONY: install
install: all
	@mkdir -p $(bindir)
	@mkdir -p $(libdir)
	@mkdir -p $(libexecdir)/$(pkgname)/bin
	cp $(MAINBIN) $(bindir)/
	cp holmes.so $(libdir)/
	cp $(AUXBIN) $(libexecdir)/$(pkgname)/bin/

.PHONY: uninstall
uninstall:
	rm -f $(bindir)/$(notdir $(MAINBIN))
	rm -rf $(libexecdir)/$(pkgname)

-include $(HOLMES:%.cc=%.d)
-include $(SRC:%.cc=%.d)
