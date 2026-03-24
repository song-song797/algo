cmake_minimum_required(VERSION 3.20)
project(CompetitionProblems LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(COMPAT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/.competition-compat")

# 编译选项（区分编译器）
if(MSVC)
    add_compile_options(/W4 /Zi /utf-8)
else()
    add_compile_options(-Wall -Wextra -g -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# 所有可执行文件输出到 build/bin 目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 递归扫描所有 .cpp 文件
file(GLOB_RECURSE ALL_CPP_FILES
    "${CMAKE_SOURCE_DIR}/CCF CSP认证/round*/*.cpp"
    "${CMAKE_SOURCE_DIR}/蓝桥杯省赛B组/*.cpp"
)

# 用递增计数器为每个文件生成唯一的纯 ASCII 目标名
set(TARGET_INDEX 0)
foreach(CPP_FILE ${ALL_CPP_FILES})
    # 获取不带扩展名的文件名作为可执行文件名
    get_filename_component(FILE_NAME_WE "${CPP_FILE}" NAME_WE)
    file(RELATIVE_PATH REL_CPP_PATH "${CMAKE_SOURCE_DIR}" "${CPP_FILE}")
    string(REPLACE "\\" "/" REL_CPP_PATH "${REL_CPP_PATH}")
    set(OUTPUT_FILE_NAME "${FILE_NAME_WE}")

    # CCF 多轮题解使用轮次前缀，避免同名题目产物冲突
    if(REL_CPP_PATH MATCHES "^CCF CSP认证/(round[0-9]+)/")
        set(OUTPUT_FILE_NAME "${CMAKE_MATCH_1}_${FILE_NAME_WE}")
    endif()

    # 使用 target_N 作为 CMake 内部目标名（避免中文问题）
    math(EXPR TARGET_INDEX "${TARGET_INDEX} + 1")
    set(TARGET_NAME "target_${TARGET_INDEX}")

    add_executable("${TARGET_NAME}" "${CPP_FILE}")
    target_include_directories("${TARGET_NAME}" PRIVATE "${COMPAT_INCLUDE_DIR}")

    # 设置输出的可执行文件名，CCF 题目附带轮次前缀
    set_target_properties("${TARGET_NAME}" PROPERTIES
        OUTPUT_NAME "${OUTPUT_FILE_NAME}"
    )
endforeach()

message(STATUS "Configured ${TARGET_INDEX} C++ targets with ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
