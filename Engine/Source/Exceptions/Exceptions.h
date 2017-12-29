#pragma once

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <stdexcept>

#define EXCEPTION_STRINGIFY(X) #X
#define EXCEPTION_STRING(X) EXCEPTION_STRINGIFY(X)
#define EXCEPTION_FUNC std::string(__func__) + " File: " EXCEPTION_STRING(__FILE__) EXCEPTION_STRING(:) EXCEPTION_STRING(__LINE__) EXCEPTION_STRING(:)
#define EXCEPTION_MESSAGE(STRING) EXCEPTION_FUNC + std::string(STRING) + std::string("\n")

#define FUNC_PREF(STRING) \
STRING##__func__



#define UNWIND_EXCEPTION_STACK_TRACE(STRING_TARGET,VECTOR_MESSAGES,VECTOR_CAUSES)\
for(auto & message : VECTOR_MESSAGES){\
  STRING_TARGET += message;\
  STRING_TARGET.append('\n');\
}

enum class ExceptionCause : std::uint32_t
{
  //Was not able to init properly
  InitializationError, 

  //Tried to use an invalid object
  InvalidObjectUsed, 

  //Dereferenced a nullptr - if this is caused by something that could constantly fire this exception, it should be shut down
  //Either the engine totally shut down if needed, or just the offending system shut down and restarted
  NullPointer, 

  //An object was invalidated and this SELF-RAISED this excpetion
  ObjectWasInvalidated, 

  //Were not able to generate an ID for this, something has clogged the ID set
  IDGenerationError, 

  //Something blew up while trying to construct this
  ConstructionError, 

  //Failed to copy something
  CopyError, 

  //An error occurred while spawning
  SpawnError, 

  //An object completely failed to spawn
  SpawnFailure, 

  //The container was unable to hold an item that needed it
  InvalidContainer, 

  //Passed an invalid parameter and could not recover
  InvalidParameter,

  //Vague - an error occurred that is going to bring us down
  Catastrophic,

  //Could not initialize physics because of bad data
  PhysicsInitInvalidData,

  //An error occurred while initializing physics
  PhysicsInitError,

  //An unknown error occurred with the physics
  PhysicsUnknown,

  //An error occurred because of a formatting error
  DataFormatError,

  //An error occurred while parsing
  DataParseError,

  //An error occurred when trying to use a stream
  StreamError,

  //A stream has failed - likely due to failing to obtain a valid destination
  StreamFailure,

  //An invalid value - it could not be recovered from
  InvalidValue,

  //The messager is invalid
  MessagerInvalid,

  //Value is too large
  ValueTooLarge,

  //Value is too small
  ValueTooSmall,

  //Value is NaN (likely due to division by zero)
  ValueNaN,

  //Exception occcurred from the standard library
  StdException, 

  //Undocumented reason, but something threw an exception and didn't provide a known documented cause
  Unknown, 
};



class EngineRuntimeError : public std::runtime_error
{
public:
  explicit EngineRuntimeError(const std::vector<ExceptionCause> &causes, const char *message)
    : msg_(message), Causes(causes), std::runtime_error(message) {}
  explicit EngineRuntimeError(const std::vector<ExceptionCause> &causes, const std::string &string)
    : msg_(string), Causes(causes), std::runtime_error(string) {}
  virtual ~EngineRuntimeError() throw () override = default;

  virtual const char* what() {
    std::string exception_trace;
    for (auto & msg : Messages) {
      exception_trace += msg;
      exception_trace.append("\n");
    }
      
    return exception_trace.c_str();
  }

  virtual void AddCause(const ExceptionCause &cause) {
    Causes.push_back(cause);
  }
  virtual void AddMessage(const std::string &string) {
    Messages.push_back(string);
  }

  std::string UnwindTrace() {
    std::string message = "";
    for (auto & str : Messages) {
      message += str + "\n";
    }

    return message;
  }

  std::string msg_;
  std::vector<ExceptionCause> Causes = { ExceptionCause::Unknown };
  std::vector<std::string> Messages = {};
};

class MessageException : public EngineRuntimeError {
public:
  explicit MessageException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit MessageException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}
  virtual ~MessageException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }
};

class StdException : public EngineRuntimeError {
public:
  explicit StdException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit StdException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}
  virtual ~StdException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }
};

class FormattingError : public EngineRuntimeError
{
public:
  explicit FormattingError(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit FormattingError(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}
  virtual ~FormattingError() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }
};

class StreamException : public EngineRuntimeError
{
public:
  explicit StreamException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit StreamException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}
  virtual ~StreamException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }
};

class PhysicsInterfaceException : public EngineRuntimeError
{
public:
  explicit PhysicsInterfaceException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit PhysicsInterfaceException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}
  virtual ~PhysicsInterfaceException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }
};


class Exception : public std::exception
{
public:
  explicit Exception(const char *message)
    : msg_(message) {}
  explicit Exception(const std::string &string)
    : msg_(string.c_str()) {}

  virtual ~Exception() throw () override = default;

  virtual const char* what()
  {
    return msg_.c_str();
  }

protected:

  std::string msg_;
    
};

class ValueException : public EngineRuntimeError
{
public:
  explicit ValueException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit ValueException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}
  virtual ~ValueException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }

};

//Throw this exception if a nullptr is given as a parameter and it is a function that should NEVER be given a nullptr
class NullPointerException : public EngineRuntimeError
{
public:
  explicit NullPointerException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit NullPointerException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}
  virtual ~NullPointerException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }

};


//Throw this exception if, during runtime initialization checks, an object was not set up properly
//  If a class expects a method to be called prior to use, and that was not called, throw this exception
//Can also throw this exception if an object was already initialized, but something tried to init it again
class InitializationException : public EngineRuntimeError
{
public:
  explicit InitializationException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit InitializationException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}

  virtual ~InitializationException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }


};

//Throw this exception whenever an invalid object tries to be used
//  This shouldn't happen, as containers should be able to intercept the action
//  but if a non-container holds a reference (like a shared_ptr) to an object that has been invalidated
//  this exception could be thrown if they do not check before using it
//     To avoid this, revalidate the object or replace it with a new one
class InvalidObjectException : public EngineRuntimeError
{
public:
  explicit InvalidObjectException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message)
  {}
  explicit InvalidObjectException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string)
  {}

  virtual ~InvalidObjectException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }
};

//Throw this exception whenever an invalid parameter is passed and you cannot recover from it
class InvalidParameter : public EngineRuntimeError
{
public:
  explicit InvalidParameter(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit InvalidParameter(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}

  virtual ~InvalidParameter() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }
};

//Throw this exception if an ID fails to be generated
class IDException : public EngineRuntimeError
{
public:
  explicit IDException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
    explicit IDException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}

  virtual ~IDException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }
};

class ConstructionException : public EngineRuntimeError
{
public:
  explicit ConstructionException(const std::vector<ExceptionCause> &causes, const char *message)
    : EngineRuntimeError(causes, message) {}
  explicit ConstructionException(const std::vector<ExceptionCause> &causes, const std::string &string)
    : EngineRuntimeError(causes, string) {}

  virtual ~ConstructionException() throw () override = default;

  virtual const char* what() override {
    return msg_.c_str();
  }
};
