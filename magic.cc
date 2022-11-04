#include <magic.h>
#define __GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "unixpp.hh"
#include "checkret.hh"
#include <string>
using std::string;
using namespace checkret;
using unixpp::range_t;

std::string unixpp::magic_mime(const range_t &range) {
  int argc=10;
  static magic_t cookie=0;
  if(!cookie) {
    cookie=magic_open(MAGIC_ERROR|MAGIC_MIME);
    magic_load(cookie,0);
    if(magic_errno(cookie)){
      dprintf(2,"%d: %s\n",magic_errno(cookie),magic_error(cookie));
      exit(1);
    };
  };
  
  string res; 
  res=magic_buffer(cookie,range.beg(),range.size());
  res=res.substr(0,res.find(';'));
  return res;
};
std::string unixpp::magic_ext(const range_t &range) {
  int argc=10;
  static magic_t cookie=0;
  if(!cookie) {
    cookie=magic_open(MAGIC_ERROR|MAGIC_EXTENSION);
    magic_load(cookie,0);
    if(magic_errno(cookie)){
      dprintf(2,"%d: %s\n",magic_errno(cookie),magic_error(cookie));
      exit(1);
    };
  };
  
  string res; 
  res=magic_buffer(cookie,range.beg(),range.size());
  res=res.substr(0,res.find(';'));
  return res;
};
  //  magic_t cookie=magic_open(MAGIC_ERROR);
   // magic_list(cookie,"/usr/lib/file/magic.mgc");
//       magic_t mime=magic_open(MAGIC_ERROR|MAGIC_MIME);
//       magic_load(mime,0);

//       dprintf(1,"file: %s\n", fn_buf.buf);
//       char *text;
//       text=strdup(magic_file(mime,fn_buf.buf));
//       char *pos=text;
//       while(1) {
//         if(*pos==';')
//           *pos=0;
//         if(!*pos)
//           break;
//         ++pos;
//       };
//         
//       dprintf(1,"mime: %s\n", text);
