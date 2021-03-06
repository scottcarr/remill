# Copyright (c) 2017 Trail of Bits, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

find_package(gtest REQUIRED)

# google gtest
find_package(gtest REQUIRED)
list(APPEND PROJECT_LIBRARIES ${gtest_LIBRARIES})
list(APPEND PROJECT_INCLUDEDIRECTORIES ${gtest_INCLUDE_DIRS})

enable_testing()
enable_language(BC)
enable_language(ASM)

add_custom_target(build_aarch64_tests)

add_executable(lift-aarch64-tests
    EXCLUDE_FROM_ALL
    Lift.cpp
    Tests.S
)

target_compile_options(lift-aarch64-tests
    PRIVATE ${X86_TEST_FLAGS}
            -DIN_TEST_GENERATOR
)

target_link_libraries(lift-aarch64-tests PUBLIC remill ${PROJECT_LIBRARIES})
target_include_directories(lift-aarch64-tests PUBLIC ${PROJECT_INCLUDEDIRECTORIES})
target_compile_definitions(lift-aarch64-tests PUBLIC ${PROJECT_DEFINITIONS})

add_executable(run-aarch64-tests
    EXCLUDE_FROM_ALL
    Run.cpp
    Tests.S
    tests_aarch64.S
)

add_custom_command(
    OUTPUT tests_aarch64.bc
    COMMAND lift-aarch64-tests
            --arch aarch64
            --bc_out tests_aarch64.bc
    DEPENDS lift-aarch64-tests semantics
)

add_custom_command(
    OUTPUT  tests_aarch64.S
    COMMAND ${CMAKE_BC_COMPILER}
            -Wno-override-module
            -S -O3 -g0
            -c tests_aarch64.bc
            -o tests_aarch64.S
    DEPENDS tests_aarch64.bc
)

target_link_libraries(run-aarch64-tests PUBLIC remill ${PROJECT_LIBRARIES})
target_include_directories(run-aarch64-tests PUBLIC ${PROJECT_INCLUDEDIRECTORIES})
target_compile_definitions(run-aarch64-tests PUBLIC ${PROJECT_DEFINITIONS})

target_compile_options(run-aarch64-tests
    PRIVATE -I${CMAKE_SOURCE_DIR}
            -DADDRESS_SIZE_BITS=64
            -DGTEST_HAS_RTTI=0
            -DGTEST_HAS_TR1_TUPLE=0
)

add_dependencies(build_aarch64_tests
    lift-aarch64-tests
    run-aarch64-tests
)

add_test(aarch64 run-aarch64-tests)
