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

#ifndef Scandy_MeshType_h
#define Scandy_MeshType_h

#include <string>

namespace scandy { namespace core {

  /**
   * Defines the various mesh types that Scandy Core recognizes as valid
   * @class MeshType
   */
  enum class MeshType
  {
    PLY,
    OBJ,
    STL,
    GLB,
    FBX,
    DRACO,
    SCMF, // Scandy Core Mesh Frame
    AUTO
  };

  /**
   * Provides an upper case string version of the MeshType.
   * NOTE: providing AUTO or junk will result in exception being thrown,
   * so be careful with your logic.
   * @method MeshTypeToString
   * @param  mesh_type        The MeshType to get a string for
   * @return                  string version of the MeshType
   */
  inline std::string MeshTypeToString(MeshType mesh_type) {
    switch(mesh_type){
      case MeshType::PLY:
        return "PLY";
      case MeshType::OBJ:
        return "OBJ";
      case MeshType::STL:
        return "STL";
      case MeshType::GLB:
        return "GLB";
      case MeshType::FBX:
        return "FBX";
      case MeshType::DRACO:
        return "DRACO";
      case MeshType::SCMF:
        return "SCMF";
      default:
        throw std::invalid_argument("invalid MeshType");
    };
  }

  /**
   * Provides a lower case string version of the MeshType.
   * NOTE: providing AUTO or junk will result in "", so be careful with your logic
   * @method MeshTypeToLowerString
   * @param  mesh_type        The MeshType to get a string for
   * @return                  string version of the MeshType
   */
  inline std::string MeshTypeToLowerString(MeshType mesh_type) {
    std::string mesh_type_str = MeshTypeToString(mesh_type);
    std::transform(mesh_type_str.begin(), mesh_type_str.end(), mesh_type_str.begin(), ::tolower);
    return mesh_type_str;
  }


  /**
   * Provides a string of the MeshType with a . before, handy for saving files
   * @method MeshTypeExtensionString
   * @param  mesh_type         The MeshType to get a string for
   * @return                   string version of the MeshType
   */
  inline std::string MeshTypeExtensionString(MeshType mesh_type) {
    std::string mesh_type_str = ".";
    mesh_type_str += MeshTypeToString(mesh_type);
    // extensions SHOULD be lower case, just an opinion
    std::transform(mesh_type_str.begin(), mesh_type_str.end(), mesh_type_str.begin(), ::tolower);
    return mesh_type_str;
  }

}}

#endif // Scandy_MeshType_h
