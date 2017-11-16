
# compile with gcc
CC = gcc

# XML libraries
XML_INCLUDE = -I/usr/include/libxml2
XML_LIB = -lxml2 -lz -lm
CURL_LIB = -lcurl

#direct compilation: gcc `xml2-config --cflags` unlRSS.c `xml2-config --libs`

runRss: runRss.c rss_utils.o rss.o curl_utils.o
	$(CC) $(XML_INCLUDE) -o runRss runRss.c curl_utils.o rss_utils.o rss.o $(XML_LIB) $(CURL_LIB)

rss_utils.o: rss_utils.c rss_utils.h
	$(CC) $(XML_INCLUDE) -c -o rss_utils.o rss_utils.c $(XML_LIB)

rss.o: rss.c rss.h
	$(CC) -c -o rss.o rss.c

curl_utils.o: curl_utils.c curl_utils.h
	$(CC) -c -o curl_utils.o curl_utils.c

curlTest: curl_utils.o
	$(CC) -o curlTest curl_utils.o curlTest.c $(CURL_LIB)

clean: 
	rm -f *.o *~
