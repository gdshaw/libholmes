# This file is part of libholmes.
# Copyright 2021 Graham Shaw.
# Distribution and modification are permitted within the terms of the
# GNU General Public License (version 3 or any later version).

prefix = /usr/local
exec_prefix = $(prefix)
libdir = $(exec_prefix)/lib

CPPFLAGS = -MD -MP -I.
CXXFLAGS = -fPIC -O2 --std=c++17 -Wall -Wpedantic

HOLMES = $(wildcard holmes/*.cc) $(wildcard holmes/*/*.cc) $(wildcard holmes/*/*/*.cc)

.PHONY: all
all: holmes.so

holmes.so: $(HOLMES:%.cc=%.o)
	gcc -shared -o $@ $^

.PHONY: clean
clean:
	rm -f holmes/*.[do]
	rm -f holmes/*/*.[do]
	rm -f holmes/*/*/*.[do]
	rm -f *.so

.PHONY: install
install: all
	@mkdir -p $(libdir)
	cp holmes.so $(libdir)/

.PHONY: uninstall
uninstall:
	rm -f $(libdir)/holmes.so

-include $(HOLMES:%.cc=%.d)
