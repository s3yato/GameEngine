add_executable(Sandbox
    main.cpp
 "Game.cpp")

 target_sources(Sandbox PRIVATE
    Game.cpp
)

target_link_libraries(Sandbox
    PRIVATE
        TinyEngine
)

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Sandbox>/assets"
)