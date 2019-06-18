/****************************************************************************\
 * Copyright (C) 2019 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Do distribute this file.
\****************************************************************************/

#ifndef Scandy_IPipeline_h
#define Scandy_IPipeline_h

#include <scandy/core/Status.h>

namespace scandy { namespace core {

/**
 * \brief IPipeline is a connection of ChannelPartition and AlgorithmPartition for processing
 * data in a scalable threadsafe way.
 */
class IPipeline {
public:

  IPipeline() {};

  virtual bool isRunning() { return false; }

  /** Open all channels. */
  virtual scandy::core::Status open() { return Status::NOT_IMPLEMENTED; }

  /** Open all channels and start all algorithms. */
  virtual scandy::core::Status start() { return Status::NOT_IMPLEMENTED; }

  /** Close all channels. */
  virtual scandy::core::Status close() { return Status::NOT_IMPLEMENTED; }

  /** Close all channels and stop all algorithms. */
  virtual scandy::core::Status stop() { return Status::NOT_IMPLEMENTED; }

  /** Join all algorithms. */
  virtual scandy::core::Status join() { return Status::NOT_IMPLEMENTED; }
};

}}

#endif // Scandy_IPipeline_h
