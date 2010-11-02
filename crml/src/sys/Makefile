SRC       = $(wildcard *.cc)
OBJ       = $(SRC:.cc=.o)

LIB     = libcrml_sys.a
LIBNAME = $(LIBPATH)/$(LIB)
INSTALL = 

all: $(LIB)

libcrml_sys.a: $(OBJ)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJ)

$(OBJ): %.o: %.cc
	$(CPP) -fPIC -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(LIBNAME)

install:
	@($(CP) $(LIBNAME) $(DESTLIBDIR) $(INSTALL))
