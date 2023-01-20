#ifndef G4Wrap_H
#define G4Wrap_H

#include "G4VExceptionHandler.hh"

class G4JLExceptionHandler : public G4VExceptionHandler {
public:
  G4JLExceptionHandler(): G4VExceptionHandler() {}
  ~G4JLExceptionHandler() = default;
  G4bool Notify(const char* originOfException,
                const char* exceptionCode,
                G4ExceptionSeverity severity,
                const char* description);
};

char* G4JL_getenv(const std::string& x) { return std::getenv(x.c_str()); };
char* G4JL_setenv(const std::string& x, const std::string& v) { return setenv(x.c_str(), v.c_str(), 1); }

void G4JL_init(void);

#endif