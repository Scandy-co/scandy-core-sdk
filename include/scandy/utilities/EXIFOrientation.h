/****************************************************************************\
 * Copyright (C) 2017 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

#ifndef Scandy_EXIFOrientation_h
#define Scandy_EXIFOrientation_h

namespace scandy { namespace utilities {
    // See http://www.daveperrett.com/articles/2012/07/28/exif-orientation-handling-is-a-ghetto/
    // for helpful explanation and experimentation with EXIF orientation
    enum class EXIFOrientation
    {
      ONE,
      TWO,
      THREE,
      FOUR,
      FIVE,
      SIX,
      SEVEN,
      EIGHT
    };
}}

#endif // Scandy_EXIFOrientation_h
