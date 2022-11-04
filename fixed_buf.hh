#ifndef fixedbuf_hh
#define fixedbuf_hh fixedbuf_hh

#include <stdio.h>

template<size_t _size>
struct fixed_buf {
  char buf[_size];
  char *beg() { return buf; }
  char *end() { return buf+_size; }
  const char *beg() const { return buf; }
  const char *end() const { return buf+_size; }
  size_t size() { return _size; }
};
void format_now(fixed_buf<20> &buf);
#endif
