set (OUTPUT Screen)

# Build
add_library (${OUTPUT} MainScreen.cc)
target_link_libraries (${OUTPUT} allegro allegro_image
	allegro_primitives allegro_font
	allegro_ttf allegro_dialog)
