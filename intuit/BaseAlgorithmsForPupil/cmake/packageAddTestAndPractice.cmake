# Usage
# include(package_add_test)

# packageAddTestAndPractice(
#        INTUIT::baseAlgorithmsForPupil::lec1_complexity_of_algorithms::lib
#        INTUIT::baseAlgorithmsForPupil::lec1_complexity_of_algorithms::practice
#        lec1_test_bubble_sort
#        test_bubble_sort.cpp
# )
#
# where lib_under_test - lib your test is linked with (all includes and target properties are used from this lib,
# this is possible due to Modern cmake concept where we use PUBLIC/INTERFACE/PRIVATE and idea of targets )


# Refs:
# https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
# https://cmake.org/cmake/help/latest/guide/tutorial/index.html


function(packageAddTestAndPractice lib_under_test lib_for_practice TESTNAME)
    # create an exectuable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN}) # for test
    add_executable(${TESTNAME}_practice ${ARGN}) # for practice

    # link the Google test infrastructure, mocking library, and a default main fuction to
    # the test executable.  Remove g_test_main if writing your own main function.

    set(DEBUG_FLAGS
            -Wconversion -Wsign-conversion -Wall -Wextra -Wpedantic
#            -Werror
            -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fsanitize=bounds
            -g -O0 --coverage)
    set(RELEASE_FLAGS -Wconversion -Wsign-conversion -Wall -Wextra -Wpedantic
#            -Werror
            -O3)

    set(targets ${TESTNAME} ${TESTNAME}_practice)
    foreach(target ${targets})
        target_compile_definitions(${target}
            PRIVATE
                # use generator expressions
                "$<$<CONFIG:DEBUG>:_GLIBCXX_DEBUG>"
                "$<$<CONFIG:DEBUG>:_GLIBCXX_DEBUG_PEDANTIC>"
        )

        target_compile_options(${target}
            PRIVATE
                "$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>"
                "$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>"
        )
        target_link_libraries(${target}
            PRIVATE
                # https://wiki.tizen.org/ASan#Enabling_sanitized_build_for_single_package
                "$<$<CONFIG:DEBUG>:-lasan>" # to be able to use -fsanitize=address
                # (https://stackoverflow.com/questions/31803705/using-gcc-undefined-behavior-sanitizer)
                "$<$<CONFIG:DEBUG>:-lubsan>" # to be able to use -fsanitize=undefined
                "$<$<CONFIG:DEBUG>:-lgcov>"
        )
        target_compile_features(${target} PRIVATE cxx_std_17)
        set_target_properties(${target} PROPERTIES FOLDER tests)
        target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
    endforeach()

    target_link_libraries(${TESTNAME} PRIVATE gtest gmock gtest_main ${lib_under_test})
    target_link_libraries(${TESTNAME}_practice PRIVATE gtest gmock gtest_main ${lib_for_practice})
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    #    gtest_discover_tests(${TESTNAME}
    #            # set a working directory so your project root so that you can find test data via paths relative to the project root
    #            WORKING_DIRECTORY ${PROJECT_DIR}
    #            PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    #            )
endfunction()