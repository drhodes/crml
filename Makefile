NACLPORTS_ROOT = /home/derek/dev/naclports/src
NACL_SDK_ROOT = /home/derek/dev/nacl_sdk
CRML_ROOT = /home/derek/dev/crml/src

DEBUGFLAGS = -O2 #-DNDEBUG

BUILDFLAGS = 
LINKFLAGS = -lgoogle_nacl_imc \
			-lgoogle_nacl_npruntime \
            -lgoogle_nacl_pgl \
			-lgoogle_nacl_gpu \
			-lpthread \
			-lsrpc \
			-losg

#-llua \

INCLUDES =	-I$(NACLPORTS_ROOT) \
			-I$(NACL_SDK_ROOT)

export CC     = nacl-gcc
export CPP    = nacl-g++
export CFLAGS =	-Wall -Wno-long-long -pthread -DXP_UNIX -Werror -std=gnu++0x -m32 \
				-enable-static \
				-enable-shared=no \
				$(DEBUGFLAGS) $(BUILDFLAGS)

export CFLAGSEXT  = -I../../../include -I../.. $(DEBUGFLAGS) $(BUILDFLAGS)
export LDFLAGS    = $(LINKFLAGS)
export LIBPATH    = ../../build
export VERSION    = 0.1
export CP         = cp
export LN         = nacl-ld
export LNFLAGS    = -s -f
export AR         = nacl-ar
export ARFLAGS    = rcs
export DESTDIR    = ../../build
export DESTLIBDIR = $(DESTDIR)/lib
export DESTINCDIR = $(DESTDIR)/include

all:	build-headers \
		crml-core \
		crml-win \
		crml-sys \
		crml-evt \
		crml-gfx \

# crml-net crml-aud


-include $(NACLPORTS_ROOT)/common_build_scripts/nacl_build.mk

build-headers:
	@(cd ./src && ./header_gen)

crml-sys:
	@(mkdir -p ./build)
	@(cd ./src/sys && $(MAKE))

crml-core:
	@(mkdir -p ./build)
	@(cd ./src/core && $(MAKE))

crml-win:
	@(mkdir -p ./lib)
	@(cd ./src/win && $(MAKE))

crml-evt:
	@(mkdir -p ./lib)
	@(cd ./src/evt && $(MAKE))

crml-gfx:
	@(mkdir -p ./lib)
	@(cd ./src/gfx && $(MAKE))


# crml-net:
# 	@(mkdir -p ../../lib)
# 	@(cd ./net && $(MAKE))

# crml-aud:
# 	@(mkdir -p ../../lib)
# 	@(cd ./aud && $(MAKE))

.PHONY: clean mrproper

clean:
	@(	cd  ./src/sys && $(MAKE) $@ && \
		cd ../core && $(MAKE) $@ && \
		cd ../win && $(MAKE) $@ && \
		cd ../evt && $(MAKE) $@ && \
		cd ../gfx && $(MAKE) $@ && \
		cd ../../build && rm -f *.a$ ) 
#&& \
#		cd ../win && $(MAKE) $@ && \
		cd ../net && $(MAKE) $@ && \
		cd ../gfx && $(MAKE) $@ && \
		cd ../aud && $(MAKE) $@ )

mrproper: clean
	@(	cd ./src/sys && $(MAKE) $@ && \
		cd ../core && $(MAKE) $@ && \
		cd ../win && $(MAKE) $@ && \
		cd ../net && $(MAKE) $@ && \
		cd ../gfx && $(MAKE) $@ && \
		cd ../aud && $(MAKE) $@ )

#
#install:
#	@(mkdir -p $(DESTLIBDIR))
#	@(mkdir -p $(DESTINCDIR))
#	@(	cd ./src/sys && $(MAKE) $@ && \
#		cd ../win && $(MAKE) $@ && \
#		cd ../net && $(MAKE) $@ && \
#		cd ../gfx && $(MAKE) $@ && \
#		cd ../aud && $(MAKE) $@ &&\
#		$(CP) -r ../../../include/CRML/ $(DESTINCDIR)/ )