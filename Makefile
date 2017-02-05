SYS = $(shell gcc -dumpmachine)
ifneq (,$(findstring mingw,$(SYS)))
OS=windows
else
OS=unix
endif

ifeq ($(OS),windows)
	MKDIRP=mkdir
	SLASH=\\
	EXE_EXTENSION=.exe
	DLL_PREFIX=
	DLL_EXTENSION=.dll
	LIBGL=opengl32
	CLEANCMD = IF exist obj ( rmdir /Q /S obj lib )
else
	MKDIRP=mkdir -p
	SLASH=/
	EXE_EXTENSION=
	DLL_PREFIX=lib
	DLL_EXTENSION=.so
	LIBGL=GL
	CLEANCMD = rm -rf obj lib
endif

.PHONY: all clean mrproper re dirs

CC = gcc
CFLAGS = -g -Wall -Isrc
LDLIBS = -Llib -Wl,-rpath,lib -Wl,-rpath,../lib -lglimagimp -lm
EXE = bin/imagimp$(EXE_EXTENSION)
LIBGLIMAGIMP = lib/$(DLL_PREFIX)glimagimp$(DLL_EXTENSION)


all: $(LIBGLIMAGIMP) $(EXE)


dirs: bin lib obj/glimagimp obj/imagimp
obj:
	$(MKDIRP) $@
obj$(SLASH)glimagimp: | obj
	$(MKDIRP) $@
obj$(SLASH)imagimp: | obj
	$(MKDIRP) $@
lib:
	$(MKDIRP) $@
bin:
	$(MKDIRP) $@


obj/imagimp/%.o : src/imagimp/%.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE): $(addsuffix .o, \
			$(addprefix obj/imagimp/, \
				$(notdir \
					$(basename \
						$(wildcard src/imagimp/*.c)))))
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

obj/glimagimp/%.o: src/glimagimp/%.c | dirs
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(LIBGLIMAGIMP): obj/glimagimp/interface.o \
			     obj/glimagimp/outils.o
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@ -l$(LIBGL) -lGLU -lglut -lm

clean:
	$(CLEANCMD)
mrproper: clean all
re: mrproper
