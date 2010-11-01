NACLPORTS_ROOT = /home/derek/dev/naclports/src
NACL_SDK_ROOT = /home/derek/dev/nacl_sdk

DEBUGFLAGS = -O2 #-DNDEBUG

BUILDFLAGS = 
LINKFLAGS = -lgoogle_nacl_imc \
			-lgoogle_nacl_npruntime \
            -lgoogle_nacl_pgl \
			-lgoogle_nacl_gpu \
			-lpthread \
			-lsrpc \
			-llua \
			-losg

export CC         = nacl-gcc
export CPP        = nacl-g++
export CFLAGS     = -Wall -Wno-long-long -pthread -DXP_UNIX -Werror -std=gnu++0x \
					-I$(NACLPORTS_ROOT) -I$(NACL_SDK_ROOT) $(DEBUGFLAGS) $(BUILDFLAGS)
export CFLAGSEXT  = -I../../../include -I../.. $(DEBUGFLAGS) $(BUILDFLAGS)
export LDFLAGS    = $(LINKFLAGS)
export LIBPATH    = ../build
export VERSION    = 0.1
export CP         = cp
export LN         = nacl-ld
export LNFLAGS    = -s -f
export AR         = nacl-ar
export ARFLAGS    = rcs
export DESTDIR    = build
export DESTLIBDIR = $(DESTDIR)/lib
export DESTINCDIR = $(DESTDIR)/include

all: crml-sys # crml-win crml-net crml-gfx crml-aud

crml-sys:
	@(mkdir -p ./build)
	@(cd ./sys && $(MAKE))

# crml-win:
# 	@(mkdir -p ../../lib)
# 	@(cd ./win && $(MAKE))

# crml-net:
# 	@(mkdir -p ../../lib)
# 	@(cd ./net && $(MAKE))

# crml-gfx:
# 	@(mkdir -p ../../lib)
# 	@(cd ./gfx && $(MAKE))

# crml-aud:
# 	@(mkdir -p ../../lib)
# 	@(cd ./aud && $(MAKE))

.PHONY: clean mrproper

clean:
	@(	cd  ./sys && $(MAKE) $@ && \
		cd ../win && $(MAKE) $@ && \
		cd ../net && $(MAKE) $@ && \
		cd ../gfx && $(MAKE) $@ && \
		cd ../aud && $(MAKE) $@ )

mrproper: clean
	@(cd ./sys && $(MAKE) $@	&& cd ../win && $(MAKE) $@ && cd ../net && $(MAKE) $@ && cd ../gfx && $(MAKE) $@ && cd ../aud && $(MAKE) $@)

install:
	@(mkdir -p $(DESTLIBDIR))
	@(mkdir -p $(DESTINCDIR))
	@(cd ./sys && $(MAKE) $@ && cd ../win && $(MAKE) $@ && cd ../net && $(MAKE) $@ && cd ../gfx && $(MAKE) $@ && cd ../aud && $(MAKE) $@ && $(CP) -r ../../../include/CRML/ $(DESTINCDIR)/)
