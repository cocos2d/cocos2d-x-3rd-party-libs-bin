set(RECAST_SRC
DebugUtils/DebugDraw.cpp
DebugUtils/DetourDebugDraw.cpp
DebugUtils/RecastDebugDraw.cpp
DebugUtils/RecastDump.cpp
Detour/DetourAlloc.cpp
Detour/DetourCommon.cpp
Detour/DetourNavMesh.cpp
Detour/DetourNavMeshBuilder.cpp
Detour/DetourNavMeshQuery.cpp
Detour/DetourNode.cpp
DetourCrowd/DetourCrowd.cpp
DetourCrowd/DetourLocalBoundary.cpp
DetourCrowd/DetourObstacleAvoidance.cpp
DetourCrowd/DetourPathCorridor.cpp
DetourCrowd/DetourPathQueue.cpp
DetourCrowd/DetourProximityGrid.cpp
DetourTileCache/DetourTileCache.cpp
DetourTileCache/DetourTileCacheBuilder.cpp
Recast/Recast.cpp
Recast/RecastAlloc.cpp
Recast/RecastArea.cpp
Recast/RecastContour.cpp
Recast/RecastFilter.cpp
Recast/RecastLayers.cpp
Recast/RecastMesh.cpp
Recast/RecastMeshDetail.cpp
Recast/RecastRasterization.cpp
Recast/RecastRegion.cpp
)

include_directories(
  ..
)

add_library(recast STATIC
  ${RECAST_SRC}
)

set_target_properties(recast
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
