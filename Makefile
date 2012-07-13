CFLAGS = -I. -I/usr/local/include -O3 -g
LIBS = -L. -L/usr/local/lib -lgeoip

.PHONY : test

all: geoip

geoip: geoip.c 
	$(CC) $(CFLAGS) -o geoip geoip.c $(LIBS)

install:
	/usr/bin/install geoip /usr/local/bin/

test: geoip
	./test/test.sh

clean:
	rm -f geoip
