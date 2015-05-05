LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := recast_static

LOCAL_MODULE_FILENAME := librecast

LOCAL_SRC_FILES := \
DebugUtils/DebugDraw.cpp \
DebugUtils/DetourDebugDraw.cpp \
DebugUtils/RecastDebugDraw.cpp \
DebugUtils/RecastDump.cpp \
Detour/DetourAlloc.cpp \
Detour/DetourCommon.cpp \
Detour/DetourNavMesh.cpp \
Detour/DetourNavMeshBuilder.cpp \
Detour/DetourNavMeshQuery.cpp \
Detour/DetourNode.cpp \
DetourCrowd/DetourCrowd.cpp \
DetourCrowd/DetourLocalBoundary.cpp \
DetourCrowd/DetourObstacleAvoidance.cpp \
DetourCrowd/DetourPathCorridor.cpp \
DetourCrowd/DetourPathQueue.cpp \
DetourCrowd/DetourProximityGrid.cpp \
DetourTileCache/DetourTileCache.cpp \
DetourTileCache/DetourTileCacheBuilder.cpp \
Recast/Recast.cpp \
Recast/RecastAlloc.cpp \
Recast/RecastArea.cpp \
Recast/RecastContour.cpp \
Recast/RecastFilter.cpp \
Recast/RecastLayers.cpp \
Recast/RecastMesh.cpp \
Recast/RecastMeshDetail.cpp \
Recast/RecastRasterization.cpp \
Recast/RecastRegion.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..
                                 
include $(BUILD_STATIC_LIBRARY)