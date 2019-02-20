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

#ifndef Scandy_Compression_h
#define Scandy_Compression_h

#include <scandy/core/CompressionType.h>

#include <string>
#include <vector>

namespace scandy { namespace utilities {

/**
 * Compresses the provided data using the LZ4 raw compressor
 * @method compressMemoryLZ4Raw
 * @param  in_data              A pointer to the memory to compress
 * @param  in_data_size         Size in bytes of the memory to compress
 * @param  out_data             A vector to store the compressed data to.
 * @param  resize               Option to resize the out_data after compression to the compressed size
 * @return                      The number of bytes in the compressed data
 */
size_t compressMemoryLZ4Raw(void *in_data, size_t in_data_size, std::vector<uint8_t> &out_data, bool resize=false);


/**
 * Decompresses the provided data using the LZ4 raw decompressor
 * @method uncompressMemoryLZ4Raw
 * @param  in_data                A pointer to the memory to decompress
 * @param  in_data_size           Size in bytes of the memory to decompress
 * @param  out_data               A vector to store the decompressed data to.
 * @param  resize                 Option to resize the out_data after compression to the compressed size
 * @return                        The number of bytes in the decompressed data
 */
size_t decompressMemoryLZ4Raw(void *in_data, size_t in_data_size, std::vector<uint8_t> &out_data, bool resize=false);

/**
 * Compress the input_file using the specified compression_type to the output_file.
 * @param  input_file       The absolute path to the file to compress
 * @param  compression_type The compression to be used. Currently only LZ4RAW is supported
 * @param  output_file      The absolute path for where to save the compressed file
 * @return                  The number of bytes in the decompressed data
 */
size_t compressFile(std::string input_file, scandy::core::CompressionType compression_type, std::string output_file);

/**
 * Decompress the input_file using the specified compression_type to the output_file.
 * @param  input_file       The absolute path to the file to decompress
 * @param  compression_type The compression to be used. Currently only LZ4RAW is supported
 * @param  output_file      The absolute path for where to save the decompressed file
 * @return                  The number of bytes in the decompressed data
 */
size_t decompressFile(std::string input_file, scandy::core::CompressionType compression_type, std::string output_file);

/**
 * Decompress the input_file using the specified compression_type to the out_data.
 * @param  input_file       The absolute path to the file to decompress
 * @param  compression_type The compression to be used. Currently only LZ4RAW is supported
 * @param  out_data         A vector to store the decompressed data to.
 * @param  resize           Option to resize the out_data after compression to the compressed size
 * @return                  The number of bytes in the decompressed data
 */
size_t decompressFileToMemory(std::string input_file, scandy::core::CompressionType compression_type, std::vector<uint8_t> &out_data, bool resize=false);

}}

#endif  // #ifndef Scandy_Compression_h
