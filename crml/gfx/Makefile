SRC       = $(wildcard *.cpp)
OBJ       = $(SRC:.cpp=.o)

LIB     = crml-aud.a
LIBNAME = $(LIBPATH)/$(LIB)
INSTALL = 

all: $(LIB)

libcrml-aud.a: $(OBJ) $(OBJVORBIS)
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
