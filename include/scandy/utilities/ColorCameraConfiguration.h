/****************************************************************************\
 * Copyright (C) 2018 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

#ifndef Scandy_ColorCamera_Configuration_h
#define Scandy_ColorCamera_Configuration_h

namespace scandy { namespace utilities {

class ColorCameraConfiguration {
public:
  bool mUseManualControl = false;

  long mExposureMinimum = (long)( (1/120.0) * 1e9); // nanoseconds
  long mExposureMaximum = (long)( (1/5.0) * 1e9); // nanoseconds
  long mExposureValue =   (long)( (1/30.0) * 1e9); // nanoseconds

  int mISOMinimum = 100;
  int mISOMaximum = 1600;
  int mISOValue = 200;

  float mFocusMinimum;
  float mFocusValue = 1.0f;
};

}  // namespace utilities
}  // namespace scandy

#endif // Scandy_ColorCamera_Configuration_h
