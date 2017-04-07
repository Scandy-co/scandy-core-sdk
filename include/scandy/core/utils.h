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

#ifndef Scandy_utils_h
#define Scandy_utils_h

#include <scandy/core/status.h>
#include <string>
#include <vector>


namespace scandy { namespace core {
    /*! Get human-readable description for status. */
    std::string getStatusString (const scandy::core::Status& status);

    size_t align(size_t byte_count, size_t block_size);
    std::string join(const std::vector<std::string>& srcs, const char* const delim = "\n");
}}

#endif // Scandy_utils_h
