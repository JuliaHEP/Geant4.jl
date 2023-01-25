#ifndef G4Wrap_H
#define G4Wrap_H

#include "G4VExceptionHandler.hh"
#include <string>

#ifndef VECCORE_ENABLE_VC
  #define VECCORE_ENABLE_VC
#endif

class G4JLExceptionHandler : public G4VExceptionHandler {
public:
  G4JLExceptionHandler(): G4VExceptionHandler() {}
  ~G4JLExceptionHandler() = default;
  G4bool Notify(const char* originOfException,
                const char* exceptionCode,
                G4ExceptionSeverity severity,
                const char* description);
};

char* G4JL_getenv(const std::string& x);
int   G4JL_setenv(const std::string& x, const std::string& v);
void  G4JL_init(void);

#endif