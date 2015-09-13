
# raspistill/raspivid/raspiyuv

SET(COMPILE_DEFINITIONS -Werror)

include_directories(${CMAKE_SOURCE_DIR}/host_applications/linux/libs/bcm_host/include)
include_directories(${CMAKE_SOURCE_DIR}/host_applications/linux/apps/raspicam/)
link_directories(/usr/local/lib)

# Your-external "mylib"
#add_library( zmq SHARED IMPORTED )
# You can define two import-locations: one for debug and one for release.
#set_target_properties( zmq PROPERTIES IMPORTED_LOCATION /usr/local/lib/) 
set (GL_SCENE_SOURCES
   gl_scenes/models.c
   gl_scenes/mirror.c
   gl_scenes/yuv.c
   gl_scenes/sobel.c
   gl_scenes/square.c
   gl_scenes/teapot.c)

set (COMMON_SOURCES
   RaspiCamControl.c
   RaspiCLI.c
   RaspiPreview.c)

find_package( OpenCV REQUIRED )
#find_package( Zmq REQUIRED )

add_executable(camcvCircle ${COMMON_SOURCES} camcv_vid_circle.cpp  RaspiTex.c RaspiTexUtil.c tga.c ${GL_SCENE_SOURCES})
add_executable(camcvCircle2 ${COMMON_SOURCES} camcv_vid_circle2.cpp  RaspiTex.c RaspiTexUtil.c tga.c ${GL_SCENE_SOURCES})
add_executable(camcv5 ${COMMON_SOURCES} camcv_vid5.cpp  RaspiTex.c RaspiTexUtil.c tga.c ${GL_SCENE_SOURCES})
add_executable(camcv4 ${COMMON_SOURCES} camcv_vid4.cpp  RaspiTex.c RaspiTexUtil.c tga.c ${GL_SCENE_SOURCES})
add_executable(camcv3 ${COMMON_SOURCES} camcv_vid3.cpp  RaspiTex.c RaspiTexUtil.c tga.c ${GL_SCENE_SOURCES})
add_executable(camcv2 ${COMMON_SOURCES} camcv_vid2.cpp  RaspiTex.c RaspiTexUtil.c tga.c ${GL_SCENE_SOURCES})
add_executable(raspistill ${COMMON_SOURCES} RaspiStill.c  RaspiTex.c RaspiTexUtil.c tga.c ${GL_SCENE_SOURCES})
add_executable(raspiyuv   ${COMMON_SOURCES} RaspiStillYUV.c)
add_executable(raspivid   ${COMMON_SOURCES} RaspiVid.c)

set (MMAL_LIBS mmal_core mmal_util mmal_vc_client)

target_link_libraries(camcvCircle ${MMAL_LIBS} vcos bcm_host GLESv2 EGL m ${OpenCV_LIBS} zmq pthread)
target_link_libraries(camcvCircle2 ${MMAL_LIBS} vcos bcm_host GLESv2 EGL m ${OpenCV_LIBS} zmq pthread)
target_link_libraries(camcv5 ${MMAL_LIBS} vcos bcm_host GLESv2 EGL m ${OpenCV_LIBS} zmq pthread)
target_link_libraries(camcv4 ${MMAL_LIBS} vcos bcm_host GLESv2 EGL m ${OpenCV_LIBS} zmq pthread)
target_link_libraries(camcv3 ${MMAL_LIBS} vcos bcm_host GLESv2 EGL m ${OpenCV_LIBS} zmq pthread)
target_link_libraries(camcv2 ${MMAL_LIBS} vcos bcm_host GLESv2 EGL m ${OpenCV_LIBS} zmq pthread)
target_link_libraries(raspistill ${MMAL_LIBS} vcos bcm_host GLESv2 EGL m)
target_link_libraries(raspiyuv   ${MMAL_LIBS} vcos bcm_host)
target_link_libraries(raspivid   ${MMAL_LIBS} vcos bcm_host)

install(TARGETS raspistill raspiyuv raspivid RUNTIME DESTINATION bin)
