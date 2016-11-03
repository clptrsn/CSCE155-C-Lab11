
# make file for unlRSS.c, intended for use on CSE

# compile with gcc
CC = gcc

# XML libraries
XML_INCLUDE = -I/usr/include/libxml2
XML_LIB = -lxml2 -lz -lm

#direct compilation: gcc `xml2-config --cflags` unlRSS.c `xml2-config --libs`

rssMain: rssMain.c rss_utils.o rss.o
	$(CC) $(XML_INCLUDE) -o rssMain rssMain.c rss_utils.o rss.o $(XML_LIB)

rss_utils.o: rss_utils.c rss_utils.h
	$(CC) $(XML_INCLUDE) -c -o rss_utils.o rss_utils.c $(XML_LIB)

rss.o: rss.c rss.h
	$(CC) -c -o rss.o rss.c
