cmake_minimum_required(VERSION 3.10)

project(kalcus)

aux_source_directory(src SourceFiles)

add_executable(kalcus
    ${SourceFiles}
)

target_link_libraries(kalcus
    m
)

target_include_directories(kalcus PRIVATE include)