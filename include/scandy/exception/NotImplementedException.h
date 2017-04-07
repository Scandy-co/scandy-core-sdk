/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

#ifndef Scandy_NotImplemented_h
#define Scandy_NotImplemented_h

#include <exception>

namespace scandy { namespace exception {
  class NotImplementedException : public std::exception {
    virtual const char* what() const throw();
  };
}}

#endif // Scandy_NotImplemented_h
