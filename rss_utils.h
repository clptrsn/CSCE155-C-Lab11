
/**
 * Types of supported RSS Feeds
 */
typedef enum {
  RSS2,
  ATOM1
} Version;

/**
 * Data associated with an RSS Service
 */
typedef struct {
  char *name;
  char *url;
  Version type;
} RssService;

static const RssService cseBitsAndBytes = {
    "CSE Bits and Bytes", "https://newsroom.unl.edu/announce/cse/?format=rss",
    RSS2};

static const RssService huskerNews = {
    "Husker Sports News",
    "http://www.huskers.com/rss.dbml?db_oem_id=100&media=news", RSS2};

/**
 * An RSS feed of Reddit's front page.  Be aware: reddit
 * forces an SSL connection, so we've been forced to use a
 * non-SSL proxy here.  Depending on the fickleness of your
 * instructor, this may or may not be working.
 */
static const RssService reddit = {
  "Reddit", "https://www.reddit.com/.rss",
    ATOM1};

/**
 * A utility function to parse an XML feed from an RSS feed
 */
void parseRssXml(xmlNode *rootNode);

/**
 * A utility function to parse an XML feed from an Atom feed
 */
void parseAtomXml(xmlNode *rootNode);
