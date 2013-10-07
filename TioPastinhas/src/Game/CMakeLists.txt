set (OUTPUT Game)

# Build
add_library (${OUTPUT} Game.cc)
add_dependencies (${OUTPUT} Card)
add_dependencies (${OUTPUT} Player)
add_dependencies (${OUTPUT} Screen)
add_dependencies (${OUTPUT} Question)
target_link_libraries (${OUTPUT} allegro Card Player Screen Question)
