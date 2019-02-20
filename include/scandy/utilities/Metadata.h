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

#ifndef Scandy_Metadata_h
#define Scandy_Metadata_h

#include <scandy/utilities/ID_types.h>

#if ENABLE_HIBERLITE
#include <hiberlite.h>
#endif

namespace scandy { namespace utilities {

/**
 * \brief Metadata is the base to all metadata types
 */
class Metadata {
public:
  // The version for a frame. this is helpful in case frames change and are
  // not backwards compatible.
  int version=0;
  // The relative frame_id for the stream
  uint64_t frame_id=0;
  // The timestamp for a frame
  uint64_t timestamp=0;

  // unique id for the metadata
  MetadataUID uid = 0;

public:
  Metadata(){
    version = 0;
    frame_id = 0;
    timestamp = 0;
  }

  Metadata(const Metadata&) = default;
  Metadata(Metadata&&) = default;
  Metadata& operator=(const Metadata&) = default;
  Metadata& operator=(Metadata&) = default;
  Metadata& operator=(Metadata&&) = default;


  template <class Archive>
  void serialize(Archive& archive){
    archive(
      version,
      frame_id,
      timestamp,
      uid
    );
  }

#if ENABLE_HIBERLITE
  friend class hiberlite::access;
  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(frame_id);
    ar & HIBERLITE_NVP(timestamp);
    ar & HIBERLITE_NVP(uid);
  }
#endif
};

}}

#endif // Scandy_Metadata_h
