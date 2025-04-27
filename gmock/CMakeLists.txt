
cmake_minimum_required( VERSION 3.4 )

list( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules )
include( TeraInit )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

TeraVersion( versionfile version-info.in FORCE_TEAMCITY_BUILD_NUMBER_VAR VERSION_HUMAN_READABLE DESCRIBE )
add_custom_target( calcversion ALL )
add_dependencies( calcversion versionfile )

add_subdirectory( audio )
add_subdirectory( authenticator )
add_subdirectory( blobparser )
add_subdirectory( container )
add_subdirectory( logger )
if( UNIX AND NOT APPLE )
    add_subdirectory( mailbox )
endif()
add_subdirectory( pixelstuff )
add_subdirectory( pixelworker )
add_subdirectory( reaper )
add_subdirectory( session )
add_subdirectory( statemachine )
add_subdirectory( stringutils )
add_subdirectory( topology )
add_subdirectory( video )
