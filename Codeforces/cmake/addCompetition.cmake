function(addCompetitionTarget targetName)
    set(SOURCES
            src/main.cpp
            )


    add_executable(${targetName} ${SOURCES})
    target_compile_features(${targetName} PRIVATE cxx_std_17)


    IF (USE_THREAD_SANITIZER)
        target_compile_options(${targetName} PRIVATE "$<$<CONFIG:DEBUG>:-fsanitize=thread>")
        target_link_libraries(${targetName} PRIVATE "$<$<CONFIG:DEBUG>:-fsanitize=thread>")
    ENDIF ()
    IF (USE_ASAN_UBSAN)
        target_compile_options(${targetName} PRIVATE "$<$<CONFIG:DEBUG>:-fsanitize=address>")
        target_link_libraries(${targetName} PRIVATE "$<$<CONFIG:DEBUG>:-lasan>")

        target_compile_options(${targetName} PRIVATE "$<$<CONFIG:DEBUG>:-fsanitize=undefined>")
        target_link_libraries(${targetName} PRIVATE "$<$<CONFIG:DEBUG>:-lubsan>")
    ENDIF ()

    target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${targetName} PRIVATE pthread)

    set(RELEASE_FLAGS
            -O3
            )

    set(DEBUG_FLAGS
            -O0
            )

    target_compile_options(${targetName}
            PRIVATE
            -Wconversion -Wsign-conversion -Wall -Wextra -pedantic -mclflushopt "$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>" "$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>"
            )

    target_compile_definitions(${targetName} PRIVATE "$<$<CONFIG:DEBUG>:_GLIBCXX_DEBUG>")
    target_compile_definitions(${targetName} PRIVATE "$<$<CONFIG:RELEASE>:RELEASE_BUILD=1>")
endfunction()

## to run on my machine:
##  $sudo make install
##  goldrush
#install(TARGETS ${targetName}
#        RUNTIME DESTINATION bin
#)


