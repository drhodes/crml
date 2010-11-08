SRC       = $(wildcard *.cpp)
OBJ       = $(SRC:.cpp=.o)

LIB     = libcrml_gfx.a
LIBNAME = $(LIBPATH)/$(LIB)
INSTALL = 

all: $(LIB)

libcrml_gfx.a: $(OBJ) $(OBJVORBIS)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJ) $(OBJVORBIS)

$(OBJ): %.o: %.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ) $(OBJVORBIS)

mrproper: clean
	@rm -rf $(LIBNAME)

install:
	@($(CP) $(LIBNAME) $(DESTLIBDIR) $(INSTALL))
