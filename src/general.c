#include "general.h"
#include <ctype.h>

bool string_is_empty(const char *s) {
  while (*s != '\0') {
    if (!isspace((unsigned char)*s))
      return false;
    s++;
  }
  return true;
}