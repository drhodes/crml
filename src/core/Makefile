SRC       = $(wildcard *.cc)
OBJ       = $(SRC:.cc=.o)

LIB     = libcrml-core.a
LIBNAME = $(LIBPATH)/$(LIB)
INSTALL = 

all: $(LIB)

libcrml-core.a: $(OBJ)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJ)

$(OBJ): %.o: %.cc
	$(CPP) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(LIBNAME)

install:
	@($(CP) $(LIBNAME) $(DESTLIBDIR) $(INSTALL))
