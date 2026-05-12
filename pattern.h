#if !defined(PATTERN_H)
#define PATTERN_H

#include <regex.h>
int RET;
regex_t REGEX;
/* regex pattern */
#define UINT8_T__PATTERN "(25[0-5]|2[0-4][0-4]|[0-1]?[0-9]?[0-9])"
#define PATTERN "^"UINT8_T__PATTERN"[[:space:]]+(\"([^\"]+)\")[[:space:]]+"UINT8_T__PATTERN"$"


#endif // PATTERN_H