all: modules/helloworld.so

modules/helloworld.so: $(wildcard *.c)
	phpize
	./configure --enable-helloworld --with-php-config=/usr/bin/php-config
	$(MAKE) -f Makefile

.PHONY:clean

clean:
	phpize --clean

