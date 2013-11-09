set (SCREEN Screen)
set (SPLASH Splash)
set (CONFIG Config)
set (MAIN Main)
set (END End)

# Build
add_library (${SCREEN} Screen.cpp)
add_library (${SPLASH} Splash.cpp)
add_library (${CONFIG} Config.cpp)
add_library (${MAIN} Main.cpp)
add_library (${END} End.cpp)

add_dependencies (${SPLASH} Screen)
add_dependencies (${CONFIG} Screen)
add_dependencies (${MAIN} Screen)
add_dependencies (${END} Screen)

target_link_libraries (${SPLASH} ${SCREEN})
target_link_libraries (${CONFIG} ${SCREEN})
target_link_libraries (${MAIN} ${SCREEN})
target_link_libraries (${END} ${SCREEN})
