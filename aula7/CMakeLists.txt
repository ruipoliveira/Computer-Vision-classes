CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( view )
FIND_PACKAGE( OpenCV REQUIRED )
FIND_PACKAGE( PCL 1.2 REQUIRED )

ADD_EXECUTABLE( reconstruct reconstruct.cpp )
ADD_EXECUTABLE( viewCloud3 viewcloud_ex3.cpp )
ADD_EXECUTABLE( viewCloud4 viewcloud_ex4.cpp )
ADD_EXECUTABLE( viewOpenni pcl_io.cpp )
ADD_EXECUTABLE( ICPalignment viewFreenect.cpp )


include_directories( ${PCL_INCLUDE_DIRS} )
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

TARGET_LINK_LIBRARIES( reconstruct ${OpenCV_LIBS} )
TARGET_LINK_LIBRARIES( viewCloud3 ${OpenCV_LIBS} )
TARGET_LINK_LIBRARIES( viewCloud3 ${PCL_LIBRARIES} )
TARGET_LINK_LIBRARIES( viewCloud4 ${OpenCV_LIBS} )
TARGET_LINK_LIBRARIES( viewCloud4 ${PCL_LIBRARIES} )
TARGET_LINK_LIBRARIES( ICPalignment ${OpenCV_LIBS} )
TARGET_LINK_LIBRARIES( ICPalignment ${PCL_LIBRARIES} )
TARGET_LINK_LIBRARIES( viewOpenni ${OpenCV_LIBS} ${PCL_LIBRARIES} )

