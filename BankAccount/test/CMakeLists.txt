find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Define the test executable
add_executable(bank_account_tests
    BankAccountTests.cpp
    CheckingAccountTests.cpp
    SavingsAccountTests.cpp
    AccountManagerTests.cpp
)

# Include directories for the test executable
target_include_directories(bank_account_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/accounts
    ${Boost_INCLUDE_DIRS}
)

# Link the existing libraries
target_link_libraries(bank_account_tests
    PRIVATE
    accounts    # Link against the pre-defined 'accounts' library from src
    utils       # Link against the pre-defined 'utils' library
    ${Boost_LIBRARIES}
)
