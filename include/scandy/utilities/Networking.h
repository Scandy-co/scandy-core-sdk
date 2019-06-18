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

#ifndef Scandy_Networking_h
#define Scandy_Networking_h

#define SCANDY_NETWORK_HEADER "SCNETHEAD"
#define SCANDY_NETWORK_DELIMITER ":=:"
#define SCANDY_NETWORK_DELIMITER_LENGTH 3

#define INITIALIZE_COMMAND "INITIALIZE"
#define PREVIEW_COMMAND "PREVIEW"
#define SCAN_COMMAND "SCAN"
#define STOP_COMMAND "STOP"
#define MESH_COMMAND "MESH"
#define SAVE_COMMAND "SAVE"
#define SET_SIZE_COMMAND "SET_SIZE"
#define SET_NOISE_COMMAND "SET_NOISE"
#define SET_VOXEL_SIZE_COMMAND "SET_VOXEL_SIZE"

// After some testing, @hcwiley found 8000 to be the largest packet that would realibly go through on the socket
#define MAX_SOCKET_FRAME_SIZE (uint)(1024 * 8.5)

#include <string>
#include <vector>

namespace scandy { namespace utilities {

std::string getIPAddress();
std::vector<std::string> getTokensFromPacket(std::string packet);
std::string createPacketFromString(std::string action, std::vector<std::string> commands = {});

}}

#endif
