cmake_minimum_required(VERSION 2.8)

project( AnimeAvataar )

include(./dlib/cmake)

FILE(GLOB source src/*.cpp)
ADD_EXECUTABLE(exec/Feature_extraction ${source})

TARGET_LINK_LIBRARIES(exec/Feature_extraction dlib)




