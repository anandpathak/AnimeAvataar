cmake_minimum_required(VERSION 2.8)
project( AnimeAvataar )
find_package( OpenCV REQUIRED )
add_executable( AnimeAvataar facedetection2.cpp )
target_link_libraries( AnimeAvataar ${OpenCV_LIBS} )

