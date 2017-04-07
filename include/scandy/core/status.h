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

#ifndef Scandy_status_h
#define Scandy_status_h

namespace scandy { namespace core {
    enum class Status
    {
        SUCCESS, //!< no errors
        UNKNOWN_LIBRARY_VERSION, //!< unknown library version
        NOT_IMPLEMENTED,

        EXCEPTION_IN_HANDLER,

        REPLACED_EXISTING_ITEM,
        DID_NOT_REPLACE_EXISTING_ITEM,

        NOT_RUNNING,

        NOT_FOUND,

        FILE_NOT_FOUND,

        INVALID_VALUE,
        INVALID_STATE,
        INVALID_LICENSE,

        MUTEX_LOCK_FAILED,
        MUTEX_UNLOCK_FAILED,

        NO_VISUALIZER_FOUND,

        TANGO_INIT_FAILED,

        ROYALE_RUNTIME_ERROR,
        ROYALE_DISCONNECTED,
        ROYALE_INVALID_VALUE,
        ROYALE_TIMEOUT,

        ROYALE_LOGIC_ERROR,
        ROYALE_NOT_IMPLEMENTED,
        ROYALE_OUT_OF_BOUNDS,

        ROYALE_RESOURCE_ERROR,
        ROYALE_FILE_NOT_FOUND,
        ROYALE_COULD_NOT_OPEN,
        ROYALE_DATA_NOT_FOUND,
        ROYALE_DEVICE_IS_BUSY,

        ROYALE_USECASE_NOT_SUPPORTED,
        ROYALE_FRAMERATE_NOT_SUPPORTED,
        ROYALE_EXPOSURE_TIME_NOT_SUPPORTED,
        ROYALE_DEVICE_NOT_INITIALIZED,
        ROYALE_CALIBRATION_DATA_ERROR,
        ROYALE_INSUFFICIENT_PRIVILEGES,
        ROYALE_DEVICE_ALREADY_INITIALIZED,
        ROYALE_EXPOSURE_MODE_INVALID,
        ROYALE_NO_CALIBRATION_DATA,
        ROYALE_INSUFFICIENT_BANDWIDTH,
        ROYALE_DUTYCYCLE_NOT_SUPPORTED,
        ROYALE_SPECTRE_NOT_INITIALIZED,

        ROYALE_FSM_INVALID_TRANSITION,
        ROYALE_UNKNOWN,

        OPENCL_SUCCESS,
        OPENCL_DEVICE_NOT_FOUND,
        OPENCL_DEVICE_NOT_AVAILABLE,
        OPENCL_COMPILER_NOT_AVAILABLE,
        OPENCL_MEM_OBJECT_ALLOCATION_FAILURE,
        OPENCL_OUT_OF_RESOURCES,
        OPENCL_OUT_OF_HOST_MEMORY,
        OPENCL_PROFILING_INFO_NOT_AVAILABLE,
        OPENCL_MEM_COPY_OVERLAP,
        OPENCL_IMAGE_FORMAT_MISMATCH,
        OPENCL_IMAGE_FORMAT_NOT_SUPPORTED,
        OPENCL_BUILD_PROGRAM_FAILURE,
        OPENCL_MAP_FAILURE,
        OPENCL_MISALIGNED_SUB_BUFFER_OFFSET,
        OPENCL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST,
        OPENCL_COMPILE_PROGRAM_FAILURE,
        OPENCL_LINKER_NOT_AVAILABLE,
        OPENCL_LINK_PROGRAM_FAILURE,
        OPENCL_DEVICE_PARTITION_FAILED,
        OPENCL_KERNEL_ARG_INFO_NOT_AVAILABLE,

        OPENCL_INVALID_VALUE,
        OPENCL_INVALID_DEVICE_TYPE,
        OPENCL_INVALID_PLATFORM,
        OPENCL_INVALID_DEVICE,
        OPENCL_INVALID_CONTEXT,
        OPENCL_INVALID_QUEUE_PROPERTIES,
        OPENCL_INVALID_COMMAND_QUEUE,
        OPENCL_INVALID_HOST_PTR,
        OPENCL_INVALID_MEM_OBJECT,
        OPENCL_INVALID_IMAGE_FORMAT_DESCRIPTOR,
        OPENCL_INVALID_IMAGE_SIZE,
        OPENCL_INVALID_SAMPLER,
        OPENCL_INVALID_BINARY,
        OPENCL_INVALID_BUILD_OPTIONS,
        OPENCL_INVALID_PROGRAM,
        OPENCL_INVALID_PROGRAM_EXECUTABLE,
        OPENCL_INVALID_KERNEL_NAME,
        OPENCL_INVALID_KERNEL_DEFINITION,
        OPENCL_INVALID_KERNEL,
        OPENCL_INVALID_ARG_INDEX,
        OPENCL_INVALID_ARG_VALUE,
        OPENCL_INVALID_ARG_SIZE,
        OPENCL_INVALID_KERNEL_ARGS,
        OPENCL_INVALID_WORK_DIMENSION,
        OPENCL_INVALID_WORK_GROUP_SIZE,
        OPENCL_INVALID_WORK_ITEM_SIZE,
        OPENCL_INVALID_GLOBAL_OFFSET,
        OPENCL_INVALID_EVENT_WAIT_LIST,
        OPENCL_INVALID_EVENT,
        OPENCL_INVALID_OPERATION,
        OPENCL_INVALID_GL_OBJECT,
        OPENCL_INVALID_BUFFER_SIZE,
        OPENCL_INVALID_MIP_LEVEL,
        OPENCL_INVALID_GLOBAL_WORK_SIZE,
        OPENCL_INVALID_PROPERTY,
        OPENCL_INVALID_IMAGE_DESCRIPTOR,
        OPENCL_INVALID_COMPILER_OPTIONS,
        OPENCL_INVALID_LINKER_OPTIONS,
        OPENCL_INVALID_DEVICE_PARTITION_COUNT,
        OPENCL_INVALID_PIPE_SIZE,
        OPENCL_INVALID_DEVICE_QUEUE,

        CLIENT_CONNECTED,
        CLIENT_UNINITIALIZED,
        SERVER_UNINITIALIZED,
        NETWORK_DISCONNECTED,
        CONNECTION_ABORTED,
        CONNECTION_REFUSED,
        CONNECTION_RESET,
        CONNECTION_TIMEOUT,
        SERVER_UNREACHABLE,
        NETWORK_ERROR,

        UNKNOWN,
        LAST
    };
}}

#endif // Scandy_status_h
