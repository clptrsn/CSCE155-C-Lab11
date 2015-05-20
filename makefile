
#Example makefile

#define a variable called CC
CC = gcc 
XML_INCLUDE = -I/usr/include/libxml2
XML_LIB = -lxml2 -lz -lm

#gcc `xml2-config --cflags` unlRSS.c `xml2-config --libs`

unlRSS: unlRSS.c
	$(CC) $(XML_INCLUDE) -o unlRSS unlRSS.c $(XML_LIB)

#gcd.o: gcd.h gcd.c
#	$(CC) -c -o gcd.o gcd.c

clean:
	rm -f *.o *~ gcdProg
