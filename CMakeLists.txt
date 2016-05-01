cmake_minimum_required(VERSION 2.8)
project( AnimeAvataar )

include(./dlib/cmake)

ADD_EXECUTABLE(face_landmark_detection_ex face_landmark_detection_ex.cpp)

TARGET_LINK_LIBRARIES(face_landmark_detection_ex dlib)
MACRO(add_example name)
   ADD_EXECUTABLE(${name} ${name}.cpp)
   TARGET_LINK_LIBRARIES(${name} dlib )
ENDMACRO()
#add_example(face_landmark_detection_ex)

find_package( OpenCV REQUIRED )
#add_executable( AnimeAvataar facedetection2.cpp )
#target_link_libraries( AnimeAvataar ${OpenCV_LIBS} )


