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

#ifndef Scandy_CompressionType_h
#define Scandy_CompressionType_h

#include <string>

namespace scandy { namespace core {

  /**
   * Defines the various compression types that Scandy Core recognizes as valid
   * @class CompressionType
   */
  enum class CompressionType
  {
    NONE,
    LZ4RAW,
    ZIP,
    LZMA
  };

  /**
   * Provides an upper case string version of the CompressionType.
   * NOTE: providing AUTO or junk will result in exception being thrown,
   * so be careful with your logic.
   * @method CompressionTypeToString
   * @param  compression_type   The CompressionType to get a string for
   * @return                    string version of the CompressionType
   */
  inline std::string CompressionTypeToString(CompressionType compression_type) {
    switch(compression_type){
      case CompressionType::NONE:
        return "None";
      case CompressionType::LZ4RAW:
        return "LZ4Raw";
      case CompressionType::ZIP:
        return "Zip";
      case CompressionType::LZMA:
        return "LZMA";
      default:
        throw std::invalid_argument("invalid CompressionType");
    };
  }

  /**
   * Provides a lower case string version of the CompressionType.
   * NOTE: providing AUTO or junk will result in "", so be careful with your logic
   * @method CompressionTypeToLowerString
   * @param  compression_type   The CompressionType to get a string for
   * @return                    string version of the CompressionType
   */
  inline std::string CompressionTypeToLowerString(CompressionType compression_type) {
    std::string compression_type_str = CompressionTypeToString(compression_type);
    std::transform(compression_type_str.begin(), compression_type_str.end(), compression_type_str.begin(), ::tolower);
    return compression_type_str;
  }


  /**
   * Provides a string of the CompressionType with a . before, handy for saving files
   * @method CompressionTypeExtensionString
   * @param  compression_type         The CompressionType to get a string for
   * @return                   string version of the CompressionType
   */
  inline std::string CompressionTypeExtensionString(CompressionType compression_type) {
    std::string compression_type_str = ".";
    compression_type_str += CompressionTypeToString(compression_type);
    // extensions SHOULD be lower case, just an opinion
    std::transform(compression_type_str.begin(), compression_type_str.end(), compression_type_str.begin(), ::tolower);
    return compression_type_str;
  }

}}

#endif // Scandy_CompressionType_h
