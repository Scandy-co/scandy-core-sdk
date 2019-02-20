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

#ifndef Scandy_MeshExportOptions_h
#define Scandy_MeshExportOptions_h

#include <scandy/core/MeshType.h>
#include <scandy/core/CompressionType.h>

#include <string>

namespace scandy { namespace core {

  /**
   * Defines the options when exporting a mesh
   * @class MeshExportOptions
   */
  typedef struct _MeshExportOptions{

    /**
     * The desired MeshType to export as.
     */
    MeshType m_mesh_type=scandy::core::MeshType::OBJ;

    /**
     * Source directory path for exporting the mesh. Used when exporting many frames.
     */
    std::string m_src_dir_path;

    /**
     * Source file path for exporting the mesh. Used when exporting a single mesh.
     */
    std::string m_src_file_path;

    /**
     * Destintation directory path for exporting the mesh. Used when exporting many frames.
     */
    std::string m_dst_dir_path;

    /**
     * Destintation file path for exporting the mesh. Used when exporting a single mesh.
     */
    std::string m_dst_file_path;

    /**
     * What compression type to use on individual mesh files files
     */
    CompressionType m_compression_type=CompressionType::NONE;

    /**
     * Whether or not the original raw file should be removed.
     */
    bool m_remove_raw_file=true;

    /**
     * The texture quality level for the export. 0.0 is lowest possible quality, 1.0 is highest possible, also the original quality
     */
    float m_texture_quality=1.0f;

    /**
     * Whether or not the original raw file should be removed.
     */
    bool m_texture_as_mp4=false;

    /**
     * How levels of detial to use when applying a poisson filter. 0 means off.
     */
    uint8_t m_poisson_levels=0;

    /**
     * Number of smoothing iterations to apply.
     */
    uint8_t m_smoothing=0;

    /**
     * Percent decimation desired on exported mesh.
     */
    float m_decimate=0.0f;

  } MeshExportOptions;

}}

#endif // Scandy_MeshExportOptions_h
