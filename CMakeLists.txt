# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.12.0)

if(CMAKE_BUILD_RPATH)
    message("CMAKE_BUILD_RPATH: ${CMAKE_BUILD_RPATH}")
endif()

project(algorithm)

# 设置编译选项
if (CMAKE_BUILD_RPATH AND (CMAKE_BUILD_TYPE MATCHES DEBUG)) 
    add_definitions(-D_DEBUG_)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g") 
endif()    

if (CMAKE_BUILD_RPATH AND (CMAKE_BUILD_TYPE MATCHES RELEASE))
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()

if (CMAKE_BUILD_RPATH AND (CMAKE_BUILD_TYPE MATCHES GTEST)) 
    add_definitions(-D_GTEST_)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -g -fprofile-arcs -ftest-coverage") 
endif()    

# 目录下的所有源文件
aux_source_directory(algorithm AL_ALGORITHM)
aux_source_directory(chapter-13 AL_CHAPTER_13)
aux_source_directory(chapter-14 AL_CHAPTER_14)
if (CMAKE_BUILD_TYPE MATCHES GTEST)
	aux_source_directory(gtest AL_TEST_FILES)
endif()

# 头文件目录
include_directories(${PROJECT_SOURCE_DIR}/algorithm)
include_directories(${PROJECT_SOURCE_DIR}/chapter-13)
include_directories(${PROJECT_SOURCE_DIR}/chapter-14)

# 库文件目录
include_directories(${CMAKE_BUILD_RPATH}/include)
link_directories(${CMAKE_BUILD_RPATH}/lib)

# 指定生成目标
if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    add_library(algorithm STATIC
        chapter-13/RbTree.cpp
    )
endif()

if (CMAKE_BUILD_TYPE MATCHES RELEASE)
    add_library(algorithm STATIC
                chapter-13/RbTree.cpp
        )
endif()

if (CMAKE_BUILD_TYPE MATCHES GTEST)
    #添加编译选项
    add_executable(algorithm ${AL_TEST_FILES}
                    ${AL_ALGORITHM}
                    ${AL_CHAPTER_13} 
                    ${AL_CHAPTER_14})
    target_link_libraries(algorithm PRIVATE gtest)
    target_link_libraries(algorithm PRIVATE gcov)
    target_link_libraries(algorithm PRIVATE pthread)

    # #执行程序
    add_custom_target(test
    COMMAND ./algorithm
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
    COMMENT "run test suit.")

    add_custom_target(gen_coverage
    COMMAND lcov -d CMakeFiles/algorithm.dir/chapter-13 -t algorithm -o 'chapter-13.cov.info' -b . -c
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
    COMMENT "genarate coverage info")

    add_custom_target(gen_coverage_html
    COMMAND genhtml -o cov_result chapter-13.cov.info
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
    COMMENT "genarate coverage info to ./cov_result")
   
    add_dependencies(gen_coverage test)
    add_dependencies(gen_coverage algorithm)
    add_dependencies(gen_coverage_html gen_coverage)
endif()
