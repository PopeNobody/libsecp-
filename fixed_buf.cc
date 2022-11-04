#include "fixed_buf.hh"
#include <time.h>


void format_now(fixed_buf<20> &res)
{
  tm gm;
  time_t now;
  time(&now);
  gmtime_r(&now,&gm);
  snprintf(res.buf,res.size(),"%04d-%02d-%02d-%02d%02d%02dz",
      gm.tm_year+1900,gm.tm_mon+1,gm.tm_mday,
      gm.tm_hour,gm.tm_min,gm.tm_sec);
};
