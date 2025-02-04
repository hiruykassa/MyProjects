find_package(Boost)

# Tell CMake you're making a library called accounts
add_library(accounts)

# List CPP files needed by library
target_sources(
    accounts
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/BankAccount.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/SavingsAccount.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/CheckingAccount.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/AccountManager.cpp
)   

# Tell CMake where headers are
target_include_directories(
    accounts
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/accounts
    ${CMAKE_SOURCE_DIR}/include/utils
    ${Boost_INCLUDE_DIRS}
)

