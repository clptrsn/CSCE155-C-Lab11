#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "rss.h"
#include "rss_utils.h"

void parseRssXml(xmlNode *rootNode) {
  // we limit the number of items to a maximum of 100
  int n = 100;
  int i = 0, numItems = 0;
  Rss items[100];
  xmlNode *cur_node = NULL;
  xmlNode *inner_node = NULL;
  xmlNode *channel = rootNode->children->next;

  for (cur_node = channel->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE &&
        strcmp(cur_node->name, "item") == 0) {
      Rss *anRss = NULL;

      char *title = NULL;
      char *link = NULL;
      char *date = NULL;
      char *description = NULL;

      for (inner_node = cur_node->children; inner_node;
           inner_node = inner_node->next) {
        if (inner_node->type == XML_ELEMENT_NODE) {
          if (strcmp(inner_node->name, "title") == 0) {
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

      if (numItems < n) {
        items[numItems] = *anRss;
        i++;
        numItems++;
      }
    }
  }
  for (i = 0; i < numItems; i++) {
    printRss(&items[i]);
  }
}

void parseAtomXml(xmlNode *rootNode) {
  // we limit the number of items to a maximum of 100
  int n = 100;
  int i = 0, numItems = 0;
  Rss items[100];
  xmlNode *cur_node = NULL;
  xmlNode *inner_node = NULL;

  // there is no <channel> element, so we go directly to the children,
  // matching <entry> tags
  for (cur_node = rootNode->children; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE &&
        strcmp(cur_node->name, "entry") == 0) {
      Rss *anRss = NULL;

      char *title = NULL;
      char *link = NULL;
      char *date = NULL;
      char *description = NULL;

      for (inner_node = cur_node->children; inner_node;
           inner_node = inner_node->next) {
        if (inner_node->type == XML_ELEMENT_NODE) {
          if (strcmp(inner_node->name, "title") == 0) {
            title = xmlNodeGetContent(inner_node);
          } else if (strcmp(inner_node->name, "link") == 0) {
            link = xmlNodeGetContent(inner_node);
          } else if (strcmp(inner_node->name, "content") == 0) {
            description = xmlNodeGetContent(inner_node);
          } else if (strcmp(inner_node->name, "updated") == 0) {
            date = xmlNodeGetContent(inner_node);
          }
        }
      }

      if (numItems < n) {
        items[numItems] = *createRss(title, link, date, description);
        i++;
        numItems++;
      }
    }
  }

  for (i = 0; i < numItems; i++) {
    printRss(&items[i]);
  }
}
