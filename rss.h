
typedef struct {
  // TODO: define your structure here
} Rss;

/**
 * A factory function to create an empty RSS feed
 * with "default" values
 */
Rss* createEmptyRss();

/**
 * A factory function to create an Rss structure
 * with the given values
 */
Rss* createRss(const char* title, const char* link, const char* date,
               const char* description);

/**
 * A function that prints the given Rss structure
 * to the standard output.
 */
void printRss(Rss* item);
