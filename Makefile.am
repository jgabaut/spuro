AUTOMAKE_OPTIONS = foreign
CFLAGS = @CFLAGS@
SHELL := /bin/bash
.ONESHELL:
MACHINE := $$(uname -m)
PACK_NAME = $(TARGET)-$(VERSION)-$(OS)-$(MACHINE)
spuro_demo_SOURCES = src/main.c
lib_SOURCES = src/spuro.c
LDADD = $(SPR_LDFLAGS)
AM_LDFLAGS = -O2
AM_CFLAGS = $(SPR_CFLAGS) -O2 -Werror -Wpedantic -Wall
if DEBUG_BUILD
AM_LDFLAGS += -ggdb -O0
AM_CFLAGS += ""
else
AM_LDFLAGS += -s
endif

libspuro.o: $(lib_SOURCES)
	@echo -e "\033[1;35m[Makefile]\e[0m    Building \"$@\":"
	$(CCOMP) -c $(CFLAGS) $(AM_CFLAGS) -fPIC $< -o $@
	@echo -e "\033[1;33mDone.\e[0m"

$(SHARED_LIB): libspuro.o
	@echo -e "\033[1;35m[Makefile]\e[0m    Building \"$@\":"
	@echo -e "    \033[1;35mAM_CFLAGS\e[0m: [ \"\033[1;34m$(AM_CFLAGS)\e[0m\" ]"
	@echo -e "    \033[1;35mCFLAGS\e[0m: [ \"\033[1;34m$(CFLAGS)\e[0m\" ]"
	$(CCOMP) $(CFLAGS) $(AM_CFLAGS) -shared $< -o $@
	@echo -e "\033[1;33mDone.\e[0m"

libspuro.a: libspuro.o
	@echo -e "\033[1;35m[Makefile]\e[0m    Building \"$@\":"
	ar rcs $@ $<
	@echo -e "\033[1;33mDone.\e[0m"

%.o: %.c
	$(CCOMP) -c $(CFLAGS) $(AM_CFLAGS) $< -o $@

$(TARGET): $(spuro_demo_SOURCES:.c=.o)
	@echo -e "    AM_CFLAGS: [ $(AM_CFLAGS) ]"
	@echo -e "    LDADD: [ $(LDADD) ]"
	$(CCOMP) $(CFLAGS) $(AM_CFLAGS) $(spuro_demo_SOURCES:.c=.o) -o $@ $(LDADD) $(AM_LDFLAGS)

clean:
	@echo -en "Cleaning build artifacts:  "
	-rm $(TARGET)
	-rm ./*.o
	-rm ./*.so
	-rm ./*.dll
	-rm ./*.a
	-rm src/*.o
	-rm src/*.so
	-rm static/*.o
	-rm static/*.so
	@echo -e "Done."

cleanob:
	@echo -en "Cleaning object build artifacts:  "
	-rm ./*.o
	-rm ./*.so
	-rm ./*.dll
	-rm ./*.a
	-rm src/*.o
	-rm src/*.so
	-rm static/*.o
	-rm static/*.so
	@echo -e "Done."

all: $(TARGET) $(SHARED_LIB) libspuro.a
rebuild: clean all
.DEFAULT_GOAL := all
