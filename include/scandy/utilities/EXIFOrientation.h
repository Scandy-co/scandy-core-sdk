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

/**
 * \file EXIFOrientation.h
 * \brief Furnishes class for `EXIFOrientation`.
 */

#ifndef Scandy_EXIFOrientation_h
#define Scandy_EXIFOrientation_h

namespace scandy { namespace utilities {
    /**
     * \class EXIFOrientation
     * \breif Specifies orientation of a photo pursuant to EXIF (exchangeable
     * image file format); has 8 possible values, spanning every possible
     * combination of rotation and mirroring of an image.
     *
     * For a helpful explanation of and experimentation with EXIF orientation, see:
     * http://www.daveperrett.com/articles/2012/07/28/exif-orientation-handling-is-a-ghetto/
     */
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
