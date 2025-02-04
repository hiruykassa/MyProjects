# Let CMake Know we're in the same project
project(bank_app)

#Create a variable
set(SOURCES
    app/main.cpp
)

#Tell CMake "Look in these directories for more instructions"
add_subdirectory(accounts)
add_subdirectory(utils)

#Create executable using the values stored in SOURCES
add_executable(bank_app ${SOURCES})

#Tell CMake where headers are
target_include_directories(
    bank_app
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/accounts
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/utils
)

#Tell CMake to use these libraries
target_link_libraries(bank_app
    PRIVATE 
    accounts
    utils
)

