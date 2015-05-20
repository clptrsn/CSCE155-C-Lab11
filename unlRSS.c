#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <time.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#define HTTP_PORT 80
#define DIRSIZE   100000

typedef struct {
  //TODO: define your structure here
} RSS;

/* Implement these functions */
RSS * createEmptyRSS();
RSS * createRSS(char * title, char * link, char * date, char * description);
void printRSS(RSS * item);

/* these functions are done for you, do not change them */
void parseRSS_XML(xmlNode * root_node);
char * getRSS_XML(const char * hostname, const char * resource);

int main(int argc, char **argv)
{
  //TODO: uncomment the RSS feed that you wish to use

  /*
  //UNL In the News Channel:
  char hostname[] = "ucommxsrv1.unl.edu";
  char resource[] = "/rssfeeds/unlinthenewsrss.xml";
  */

  /*
  //Nebraska Headline News - Husker Sports
  char hostname[] = "www.huskers.com";
  char resource[] = "/rss.dbml?db_oem_id=100&media=news";
  */

  /*
  //The scarlet - The news source for faculty and staff at the University of Nebraska-Lincoln
  char hostname[] = "scarlet.unl.edu";
  char resource[] = "/?feed=rss2";
  */

  char *rawXML = getRSS_XML(hostname, resource);

  xmlDocPtr doc = xmlReadMemory(rawXML, strlen(rawXML), "noname.xml", NULL, 0);
  xmlNode *root_element = xmlDocGetRootElement(doc);

  parseRSS_XML(root_element);

  xmlCleanupParser();
}

RSS * createEmptyRSS() {
  //TODO: implement
}

RSS * createRSS(char * title, char * link, char * date, char * description) {
  //TODO: implement
}

void printRSS(RSS * item) {
  //TODO: implement
}

void parseRSS_XML(xmlNode * root_node)
{
  //we limit the number of items to a maximum of 100
  int n=100;
  int i=0, numItems=0;
  RSS items[100];
  xmlNode *cur_node = NULL;
  xmlNode *inner_node = NULL;
  xmlNode *channel = root_node->children->next;
  
  for(cur_node=channel->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE && strcmp(cur_node->name, "item") == 0) {

      RSS * anRSS = NULL;

      char * title = NULL;
      char * link  = NULL;
      char * date  = NULL;
      char * description = NULL;

      for(inner_node=cur_node->children; inner_node; inner_node = inner_node->next) {
        if(inner_node->type == XML_ELEMENT_NODE) {
	  if(strcmp(inner_node->name, "title") == 0) {
	    title = xmlNodeGetContent(inner_node);
	  } else if (strcmp(inner_node->name, "link") == 0) {
	    link = xmlNodeGetContent(inner_node);
	  } else if (strcmp(inner_node->name, "description") == 0) {
	    description = xmlNodeGetContent(inner_node);
	  } else if (strcmp(inner_node->name, "pubDate") == 0) {
	    date = xmlNodeGetContent(inner_node);
          }
        }
      }
      anRSS = createRSS(title, link, date, description);

      if(numItems < n) {
	items[numItems] = *anRSS;
	i++;
        numItems++;
      }
    }
  }
  for(i=0; i<numItems; i++) {
    printRSS(&items[i]);
  }
}

char * getRSS_XML(const char * hostname, const char * resource)
{
  char *rawXML;
  char dir[DIRSIZE];
  char result[DIRSIZE * 2];
  char * request = (char *) malloc(sizeof(char) * (200 + strlen(hostname) + strlen(resource)));
  sprintf(request, "GET %s HTTP/1.1 \r\nHost: %s\r\n\r\n", resource, hostname);

  int sd;
  struct sockaddr_in sin;
  struct sockaddr_in pin;
  struct hostent *hp;

  /* go find out about the desired host machine */
  if ((hp = gethostbyname(hostname)) == 0) {
    perror("gethostbyname");
    exit(1);
  }
  
  /* fill in the socket structure with host information */
  memset(&pin, 0, sizeof(pin));
  pin.sin_family = AF_INET;
  pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
  pin.sin_port = htons(HTTP_PORT);
  
  /* grab an Internet domain socket */
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }
  
  /* connect to PORT on HOST */
  if (connect(sd,(struct sockaddr *)  &pin, sizeof(pin)) == -1) {
    perror("connect");
    exit(1);
  }
  
  /* send a message to the server PORT on machine HOST */
  if (send(sd, request, strlen(request), 0) == -1) {
    perror("send");
    exit(1);
  }

  int len = 0;
  while(1) {
    len = recv(sd, dir, DIRSIZE, 0);
    strncat(result, dir, len);
    if(len <= 0)
      break;
  }

  rawXML = (char *) malloc(sizeof(char) * (strlen(strchr(result, '<')) + 1));
  strcpy(rawXML, strchr(result, '<'));
  close(sd);
  return rawXML;

}
