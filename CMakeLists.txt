cmake_minimum_required (VERSION 2.8)
project (NR)
set(CMAKE_BUILD_TYPE Debug)
add_executable(nr main.cpp)
target_link_libraries(nr newrelic-collector-client newrelic-common newrelic-transaction)
