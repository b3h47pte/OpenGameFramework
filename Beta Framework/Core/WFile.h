#pragma once
#ifndef _WFILE_H
#define _WFILE_H

#include "CommonCore.h"
#include <vector>

class  WFile
{
public:
  WFile(const std::string&);
  virtual ~WFile(void);

  /*
   * Reads a file as binary data and puts a NULL at the end.
   */
  char* ReadAllBinaryDataNull() {
    int i;
    return ReadAllBinaryDataNull(i);  
  } 
  char* ReadAllBinaryDataNull(int&);

  /*
   * Reads a file as pure text data and each line is a string inside the input vector.
   */
  void ReadAllTextData(std::vector<std::string>&);

protected:
  WFile() {}
  std::string mFileName;
};

#endif // _WFILE_H
