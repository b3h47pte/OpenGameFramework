#pragma once
#ifndef _ERRORCATCH_H
#define _ERRORCATCH_H

#include "CommonCore.h"

class ErrorCatch;

/*
 * Allows us to detect whether or not there has been some sort of error that happened via some public functions. 
 */ 
class ErrorCatch
{
public:
  ErrorCatch(void);
  virtual ~ErrorCatch(void);

  bool GetError(int& code) const { code = mErrorCode; return mErrorState; }
  void SetError(int code) { mErrorCode = code; mErrorState = true; }
  void ClearError() { mErrorState = false; }

  // Print out error into CERR
  virtual void DumpError(int) const = 0;

private:
  bool  mErrorState;
  int    mErrorCode;
};

/*
 * Takes in a pointer to a pointer of a class that derives from ErrorCatch and checks its error state. It will perform the delete and set the pointer to NULL if an error state is found.
 */
inline bool ERROR_CHECK_CLEANUP(ErrorCatch* inError) {
  int code;
  if (inError->GetError(code)) {
    inError->DumpError(code);
    delete inError;
    return true;
  }
  return false;
}

/* 
 * Macro: Calls ERROR_CHECK_CLEANUP for us but will also set the pointer to NULL and return the pointer to prevent further indentation levels.
 */
#define WRAP_ERROR_CHECK_CLEANUP_SETNULL_RETURN(a)  \
{                          \
  if (ERROR_CHECK_CLEANUP(a)) {          \
    a = NULL;                  \
    return a;                  \
  }                        \
}

/*
 * Macro: Calls ERROR_CHECK_CLEANUP for us but if there is an error, will set the error status to b.
 */
#define WRAP_ERROR_CHECK_CLEANUP_SETERROR(a, b) \
{                        \
  if (ERROR_CHECK_CLEANUP(a)) {        \
    a->SetError(b);              \
  }                      \
}

/*
 * Print Error into console.
 */
inline void ERROR_PRINT(std::string inMessage) {
  std::cout << "Error: " << inMessage << std::endl;
}

#endif
