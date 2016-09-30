# Nice name for the IDEs
project(openddl)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")  # -Weverything equivalent to g++ -pedantic, -Werror and -Wall
else()
  set(CMAKE_CXX_FLAGS "-pedantic -Wall")
endif()


set( HDRS
  oddlarray.h
  oddlmap.h
  oddlstring.h
  oddltree.h
  oddltypes.h
  openddl.h
  )

set( SRCS
  oddlmap.cpp
  oddlstring.cpp
  oddltree.cpp
  openddl.cpp
  )


#########
# Compile
add_library( ${PROJECT_NAME} ${HDRS} ${SRCS} )

#add_executable( Test1 ${HDRS} test1.cpp )
#target_link_libraries( Test1 ${PROJECT_NAME} )

