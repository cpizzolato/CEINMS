## Authors: Monica Reggiani, Claudio Pizzolato
set(Common_HEADERS  ArrayConverter.h
                    FileUtils.h
                    Parameter.h
                    SimulatedAnnealingParameters.h)

set(Common_SOURCES  Parameter.cpp)
include_directories(${Boost_INCLUDE_DIRS})
source_group("Headers" FILES ${Common_HEADERS})
source_group("Sources" FILES ${Common_SOURCES})
add_library(ceinms_common STATIC ${Common_SOURCES} ${Common_HEADERS})
target_link_libraries(ceinms_common ${Boost_LIBRARIES})
set(ceinms_common_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Include directory for library of common files")
mark_as_advanced(ceinms_common_INCLUDE_DIRS)