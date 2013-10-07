set (OUTPUT Player)

# Build
add_library (${OUTPUT} Player.cc)
add_dependencies (${OUTPUT} Company)
target_link_libraries (${OUTPUT} Company)
