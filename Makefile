all:
	g++ -g *.cc -o game -L/usr/lib -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_dialog
