cmake_minimum_required(VERSION 3.12)

# 本工程的名字
project(OpenGLTEST1)

# 本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置统一的运行时库
if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# 定义库文件所在的根目录
set(LIB_DIR ${CMAKE_SOURCE_DIR}/libs)

# 搜索src目录下所有cpp文件
file(GLOB_RECURSE SRCS "src/*.cpp")
message(STATUS "Source files: ${SRCS}")

# 生成可执行文件
add_executable(main ${SRCS})

# 使用现代 CMake 方式添加包含目录
target_include_directories(main PRIVATE
    src
    ${LIB_DIR}/glfw-3.4.bin.WIN64/include
    ${LIB_DIR}/glew-2.2.0/include
    ${LIB_DIR}/glad/include
    ${LIB_DIR}/glm
    ${LIB_DIR}/assimp/include
    ${LIB_DIR}/freetype/include
    ${LIB_DIR}/irrKlang-64bit-1.6.0/include
)

# 将 glad 的源文件添加到编译
target_sources(main PRIVATE ${LIB_DIR}/glad/src/glad.c)

# 链接库文件
target_link_libraries(main PRIVATE
    ${LIB_DIR}/glfw-3.4.bin.WIN64/lib-vc2022/glfw3.lib
    ${LIB_DIR}/glew-2.2.0/lib/Release/x64/glew32s.lib
    ${LIB_DIR}/assimp/lib/assimp-vc143-mtd.lib
    ${LIB_DIR}/freetype/bin/freetype.lib
    ${LIB_DIR}/irrKlang-64bit-1.6.0/lib/Winx64-visualStudio/irrKlang.lib
    opengl32.lib
)

# 拷贝资源文件到运行目录
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources
    COMMENT "Copying resources to build directory"
)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/shaders
    COMMENT "Copying shaders to build directory"
)