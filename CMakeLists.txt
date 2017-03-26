cmake_minimum_required(VERSION 2.8)

project( AnimeAvataar )

include(./dlib/cmake)

#FILE(GLOB source src/*.cpp)
#set (source src/face_landmark_detection_ex.cpp)
set (source  src/mainCaller.cpp src/FacialLandmark.cpp  src/header/FacialLandmark.h)
ADD_EXECUTABLE(exec/Feature_extraction ${source})

TARGET_LINK_LIBRARIES(exec/Feature_extraction dlib)
