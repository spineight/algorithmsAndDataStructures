# Usage
# include(package_add_test)
# package_add_test(lib_under_test test_name sources headers )
# example: package_add_test(Stankevich::lec1 test_bubble_sort test_bubble_sort.cpp )
#
# where lib_under_test - lib your test is linked with (all includes and target properties are used from this lib,
# this is possible due to Modern cmake concept where we use PUBLIC/INTERFACE/PRIVATE and idea of targets )


# Taken from here: https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
# Then, to add a test, I'd recommend the following macro:
function(package_add_test lib_under_test TESTNAME)
    # create an exectuable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN})
    # link the Google test infrastructure, mocking library, and a default main fuction to
    # the test executable.  Remove g_test_main if writing your own main function.

    target_compile_definitions(${TESTNAME}
            PRIVATE
            "$<$<CONFIG:DEBUG>:_GLIBCXX_DEBUG>"
            "$<$<CONFIG:DEBUG>:_GLIBCXX_DEBUG_PEDANTIC>"
    )
    set(DEBUG_FLAGS
            -Wall -Wextra -Wpedantic -Werror
            -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
            -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fsanitize=bounds
            -g -O0 --coverage)
    set(RELEASE_FLAGS -Wall -Wextra -Wpedantic -Werror -O3)
    target_compile_options(${TESTNAME}
            PRIVATE
            "$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>"
            "$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>"
    )
    target_link_libraries(${TESTNAME}
            PRIVATE
            # https://wiki.tizen.org/ASan#Enabling_sanitized_build_for_single_package
            "$<$<CONFIG:DEBUG>:-lasan>" # to be able to use -fsanitize=address
            # (https://stackoverflow.com/questions/31803705/using-gcc-undefined-behavior-sanitizer)
            "$<$<CONFIG:DEBUG>:-lubsan>" # to be able to use -fsanitize=undefined
            "$<$<CONFIG:DEBUG>:-lgcov>"
    )
    # ASan runtime does not come first in initial library list; you should either link runtime to your application or manually preload it with LD_PRELOAD
    # https://wiki.tizen.org/ASan
    ## Before that: sudo yum install libasan

    target_link_libraries(${TESTNAME} PRIVATE gtest gmock gtest_main ${lib_under_test})
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    #    gtest_discover_tests(${TESTNAME}
    #            # set a working directory so your project root so that you can find test data via paths relative to the project root
    #            WORKING_DIRECTORY ${PROJECT_DIR}
    #            PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    #            )
    target_compile_features(${TESTNAME} PRIVATE cxx_std_17)
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endfunction()