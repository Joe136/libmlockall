prefix = /usr/local

all: libmlockall.so.0.0

libmlockall.so.0.0: Makefile libmlockall.c
	${CC} -fPIC -Os -shared -Wall -Wextra -Wpedantic -Wl,-soname,libmlockall.so.0 -o libmlockall.so.0.0 -lc libmlockall.c  # -Wl,-export-dynamic

clean:
	rm -Rf *.o lib*.so*

# for checkinstall
install:
	install -s --mode=640 --group=mlockall libmlockall.so.0.0 "${prefix}/lib/"
	ln -fs libmlockall.so.0.0 "${prefix}/lib/libmlockall.so"
	ln -fs libmlockall.so.0.0 "${prefix}/lib/libmlockall.so.0"
