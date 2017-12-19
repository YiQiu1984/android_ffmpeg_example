# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 查找所有源码 并拼接到路径列表
aux_source_directory(${CMAKE_HOME_DIRECTORY}/src/main/cpp SRC_LIST)
#aux_source_directory(${CMAKE_HOME_DIRECTORY}/src/main/cpp CORE_SRC_LIST)
#把CORE_SRC_LIST 加到SRC_LIST
#list(APPEND SRC_LIST ${CORE_SRC_LIST})
add_library(native-lib SHARED ${SRC_LIST})


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# 指定 include 头文件所在路径
include_directories(${CMAKE_HOME_DIRECTORY}/src/main/cpp/include)
include_directories(${CMAKE_HOME_DIRECTORY}/src/main/cpp)
#include_directories(/Users/qiuyi/code/ffmpeg)

# 设置根目录变量 DIR
set(DIR ../../../../libs)

# 这一句和 下面的 set_target_properties 这一句表示，
# 将 armeabi 目录下的 libavcodec-56.so 导入为 avcodec-56 库，并且在项目中引用
# 下面的七组功能类似。 注意：add_library 中的 avcodec-56 命名 需要与 .so 库的命名一致
# 去掉前缀 lib 和后缀 .so
# TODO ${CMAKE_SOURCE_DIR}：表示 CMakeLists.txt的当前文件夹路径
# TODO ${ANDROID_ABI}：编译时会自动根据 CPU架构去选择相应的库
add_library( avcodec-57
             SHARED
             IMPORTED )

set_target_properties( avcodec-57
                       PROPERTIES IMPORTED_LOCATION
                       ${DIR}/${ANDROID_ABI}/libavcodec-57.so
                     )

#
add_library( avdevice-57
             SHARED
             IMPORTED )

set_target_properties( avdevice-57
                       PROPERTIES IMPORTED_LOCATION
                       ${DIR}/${ANDROID_ABI}/libavdevice-57.so
                     )

#
add_library( avfilter-6
             SHARED
             IMPORTED )

set_target_properties( avfilter-6
                       PROPERTIES IMPORTED_LOCATION
                       ${DIR}/${ANDROID_ABI}/libavfilter-6.so
                     )

#
add_library( avformat-57
             SHARED
             IMPORTED )

set_target_properties( avformat-57
                       PROPERTIES IMPORTED_LOCATION
                       ${DIR}/${ANDROID_ABI}/libavformat-57.so
                     )

#
add_library( avresample-3
             SHARED
             IMPORTED )

set_target_properties( avresample-3
                       PROPERTIES IMPORTED_LOCATION
                       ${DIR}/${ANDROID_ABI}/libavresample-3.so
                     )

#
add_library( avutil-55
             SHARED
             IMPORTED )

set_target_properties( avutil-55
                       PROPERTIES IMPORTED_LOCATION
                       ${DIR}/${ANDROID_ABI}/libavutil-55.so
                     )

#
add_library( postproc-54
             SHARED
             IMPORTED )

set_target_properties( postproc-54
                       PROPERTIES IMPORTED_LOCATION
                       ${DIR}/${ANDROID_ABI}/libpostproc-54.so
                     )

#
add_library( swresample-2
             SHARED
             IMPORTED )

set_target_properties( swresample-2
                       PROPERTIES IMPORTED_LOCATION
                       ${DIR}/${ANDROID_ABI}/libswresample-2.so
                     )

#
add_library( swscale-4
             SHARED
             IMPORTED )

set_target_properties( swscale-4
                       PROPERTIES IMPORTED_LOCATION
                       ${DIR}/${ANDROID_ABI}/libswscale-4.so
                     )


# 最终生成 native-lib 库，以及生成所依赖的其他的库
target_link_libraries( native-lib
                       avcodec-57
                       avdevice-57
                       avfilter-6
                       avformat-57
                       avresample-3
                       avutil-55
                       postproc-54
                       swresample-2
                       swscale-4
                       ${log-lib}
                        )