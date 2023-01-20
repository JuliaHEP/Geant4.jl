#include "Geant4Wrapper.h"
#include "G4StateManager.hh"
#include "G4ios.hh"

#include <stdexcept>

// --------------------------------------------------------------------------
G4bool G4JLExceptionHandler::Notify(const char* originOfException,
                                    const char* exceptionCode,
                                    G4ExceptionSeverity severity,
                                    const char* description) {
    std::ostringstream message;
    message << "*** G4Exception : " << exceptionCode << G4endl
            << "      issued by : " << originOfException << G4endl
            << description << G4endl;

    switch(severity) {
    case FatalException:
      throw std::runtime_error( message.str() );
      break;
    case FatalErrorInArgument:
      throw std::invalid_argument( message.str() );
      break;
    case RunMustBeAborted:
      throw std::runtime_error( message.str() );
      break;
    case EventMustBeAborted:
      throw std::runtime_error( message.str() );
      break;
    default:
      throw std::runtime_error( message.str() );
      break;
    }
    return false;
  }
}


void G4JLInit(void) {

  auto sm = G4StateManager::GetStateManager();
  sm-> SetExceptionHandler(new G4JLExceptionHandler());



}
