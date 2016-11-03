
#define HTTP_PORT 80
#define BUFFER_SIZE 50000

typedef enum {
  RSS2,
  ATOM1
} Version;

typedef struct {
  char *name;
  char *host;
  char *resource;
  int type;
} RssService;

static const RssService unlNews = {
  "UNL News",
  "newsroom.unl.edu",
  "/releases/?format=xml",
  RSS2
};

static const RssService huskerNews = {
  "Husker Sports News",
  "www.huskers.com",
  "/rss.dbml?db_oem_id=100&media=news",
  RSS2
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
  "/~cbourke/proxies/redditRSS.php",
  ATOM1
};

/**
 * A utility function to parse an XML feed from an RSS feed
 */
void parseRssXml(xmlNode * rootNode);

/**
 * A utility function to retrieve RSS or ATOM feed
 */
char * getRssXml(const char * hostname, const char * resource);
