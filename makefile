
# make file for unlRSS.c, intended for use on CSE

# compile with gcc
CC = gcc 

# XML libraries
XML_INCLUDE = -I/usr/include/libxml2
XML_LIB = -lxml2 -lz -lm

#direct compilation: gcc `xml2-config --cflags` unlRSS.c `xml2-config --libs`

unlRSS: unlRSS.c
	$(CC) $(XML_INCLUDE) -o unlRSS unlRSS.c $(XML_LIB)

