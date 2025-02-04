# Tell CMake you're making a library called utils
add_library(utils)

# List CPP files needed by library
target_sources(
    utils
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
)

# Tell CMake where headers are
target_include_directories(
    utils
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/accounts
)

