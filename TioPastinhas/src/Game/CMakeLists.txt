set (OUTPUT Game)

# Build
add_library (${OUTPUT} Game.cpp)
add_dependencies (${OUTPUT} Splash)
add_dependencies (${OUTPUT} Config)
add_dependencies (${OUTPUT} Main)
add_dependencies (${OUTPUT} End)

target_link_libraries (${OUTPUT}
	allegro
	allegro_ttf
	allegro_font
	allegro_image
	allegro_audio
	allegro_acodec
	allegro_dialog
	allegro_primitives
	Splash
	Config
	Main
	End
)
