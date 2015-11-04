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
#define DIRSIZE   50000

typedef struct {
  char *name;
  char *host;
  char *resource;
} RssService;

static const RssService unlNews = {
  "UNL News",
  "newsroom.unl.edu",
  "/releases/?format=xml"
};

static const RssService huskerNews = {
  "Husker Sports News",
  "www.huskers.com",
  "/rss.dbml?db_oem_id=100&media=news" 
};

/**
 * An RSS feed of Reddit's front page.  Be aware: reddit 
 * forces an SSL connection, so we've been forced to use a 
 * non-SSL proxy here.  Depending on the fickleness of your
 * instructor, this may or may not be working.
 */
static const RssService reddit = {
  "Reddit (proxy)",
  "cse.unl.edu",
  "/~cbourke/proxies/redditRSS.php"
};

typedef struct {
  //TODO: define your structure here
} Rss;

/* Implement these functions */
Rss * createEmptyRss();
Rss * createRss(const char * title, const char * link, const char * date, const char * description);
void printRss(Rss * item);

/* these functions are done for you, do not change them */
void parseRssXml(xmlNode * rootNode);
char * getRssXml(const char * hostname, const char * resource);

int main(int argc, char **argv)
{
  //default: UNL News
  RssService s = unlNews;

  if(argc > 1) {
    int choice = atoi(argv[1]);
    if(choice == 2) {
      s = huskerNews;
    } else if(choice == 3) {
      s = reddit;
    }
  }

  printf("Using RSS Service: %s (%s%s)\n", s.name, s.host, s.resource);

  char *rawXml = getRssXml(s.host, s.resource);

  xmlDocPtr doc = xmlReadMemory(rawXml, strlen(rawXml), "noname.xml", NULL, 0);
  xmlNode *rootElement = xmlDocGetRootElement(doc);

  parseRssXml(rootElement);

  xmlCleanupParser();
}

Rss * createEmptyRss() {
  //TODO: implement
}

Rss * createRss(const char * title, const char * link, const char * dateStr, const char * description) {
  //TODO: implement
}

void printRss(Rss * item) {
  //TODO: implement
}

void parseRssXml(xmlNode * rootNode)
{
  //we limit the number of items to a maximum of 100
  int n=100;
  int i=0, numItems=0;
  Rss items[100];
  xmlNode *cur_node = NULL;
  xmlNode *inner_node = NULL;
  xmlNode *channel = rootNode->children->next;
  
  for(cur_node=channel->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE && strcmp(cur_node->name, "item") == 0) {

      Rss * anRss = NULL;

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
      anRss = createRss(title, link, date, description);

      if(numItems < n) {
	items[numItems] = *anRss;
	i++;
        numItems++;
      }
    }
  }
  for(i=0; i<numItems; i++) {
    printRss(&items[i]);
  }
}

char * getRssXml(const char * hostname, const char * resource)
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

  //chomp everything after the last >:
  int i=strlen(rawXML)-1;
  while(rawXML[i] != '>') {
    rawXML[i] = '\0';
    i--;
  }

  return rawXML;

}
