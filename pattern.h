#if !defined(PATTERN_H)
#define PATTERN_H

#include <regex.h>
int RET;
regex_t REGEX;
/* regex pattern */
#define PATTERN "([0-9]+)[[:space:]]+\"([^\"]+)\"[[:space:]]+([0-9]+)"


#endif // PATTERN_H