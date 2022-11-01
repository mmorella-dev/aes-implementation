set (CMAKE_CXX_STANDARD 20)

add_subdirectory(aes)

add_executable(main "main.cpp")
target_link_libraries(main aes)

# target_include_directories(${LIBRARY_NAME} PUBLIC
#     ${LIBRARY_INCLUDES})