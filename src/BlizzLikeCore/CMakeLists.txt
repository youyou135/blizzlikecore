# Copyright (C) 2011-2013 BlizzLikeCore <http://blizzlike.servegame.com/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

file(GLOB sources_localdir *.cpp *.h)

set(WORLDSERVER_SRCS
  ${WORLDSERVER_SRCS}
  ${sources_localdir}
)

if( WIN32 )
  set(WORLDSERVER_SRCS
    ${WORLDSERVER_SRCS}
    ${sources_Debugging}
    worldserver.rc
  )
endif()

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/dep/gsoap
  ${CMAKE_SOURCE_DIR}/dep/sockets/include
  ${CMAKE_SOURCE_DIR}/dep/SFMT
  ${CMAKE_SOURCE_DIR}/dep/mersennetwister
  ${CMAKE_SOURCE_DIR}/src/collision
  ${CMAKE_SOURCE_DIR}/src/shared
  ${CMAKE_SOURCE_DIR}/src/shared/Database
  ${CMAKE_SOURCE_DIR}/src/framework
  ${CMAKE_SOURCE_DIR}/src/game
  ${ACE_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
  ${OPENSSL_INCLUDE_DIR}
)

set(WORLDSERVER_LINK_FLAGS "")

add_executable(worldserver ${WORLDSERVER_SRCS})

if( NOT WIN32 )
  add_definitions(-D_BLIZZLIKE_WORLD_CONFIG="${CONF_DIR}/worldserver.conf")
endif()

add_dependencies(worldserver revision.h)

if( UNIX )
  set(WORLDSERVER_LINK_FLAGS "-pthread ${WORLDSERVER_LINK_FLAGS}")
endif()

set_target_properties(worldserver PROPERTIES LINK_FLAGS "${WORLDSERVER_LINK_FLAGS}")

target_link_libraries(worldserver
  game
  shared
  scripts
  blizzlikeframework
  collision
  g3dlib
  gsoap
  ${JEMALLOC_LIBRARY}
  ${READLINE_LIBRARY}
  ${TERMCAP_LIBRARY}
  ${ACE_LIBRARY}
  ${MYSQL_LIBRARY}
  ${OPENSSL_LIBRARIES}
  ${OPENSSL_EXTRA_LIBRARIES}
  ${ZLIB_LIBRARIES}
  ${OSX_LIBS}
)

if( WIN32 )
  add_custom_command(TARGET worldserver
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/worldserver.conf.dist ${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/
  )
endif()

if( UNIX )
  install(TARGETS worldserver DESTINATION bin)
  install(FILES worldserver.conf.dist DESTINATION etc)
elseif( WIN32 )
  install(TARGETS worldserver DESTINATION "${CMAKE_INSTALL_PREFIX}")
  install(FILES worldserver.conf.dist DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
