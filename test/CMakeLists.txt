include(FetchContent)

FetchContent_Declare(
                googletest
                URL https://github.com/google/googletest/archive/e47544ad31cb3ceecd04cc13e8fe556f8df9fe0b.zip)
            
FetchContent_MakeAvailable(googletest)
            
enable_testing()

add_executable(
                TCPServer_test
                main.cpp)
            
target_link_libraries(
                TCPServer_test
                TCPServer_lib
                GTest::gtest_main
                GTest::gmock_main)
            
include(GoogleTest)
            
gtest_discover_tests(TCPServer_test)