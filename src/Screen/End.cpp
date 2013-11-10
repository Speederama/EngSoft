# include "End.hpp"

// Constructor
End::End(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data) {

	// Fonts
	_load_font("main", config::misc::font::dejavu, 15);
	_load_font("title", config::misc::font::dejavu, 45);

        _load_image("back", config::misc::image::main);

        _create_image("cover", 1 * _width, 1 * _height);
        _image["cover"]->set_color(_palette, "black", 220);

        _create_image("VLine",.001* _width, 1 * _height);
        _image["VLine"]->set_color(_palette, "royalblue", 255);
        
        _create_image("HLine",1* _width, .001 * _width);
        _image["HLine"]->set_color(_palette, "royalblue", 255);
        
        _create_image("HLine2",1* _width, .004 * _width);
        _image["HLine2"]->set_color(_palette, "royalblue", 255);

        _create_image("box", 0.30 * _width, 0.412 * _height);
          _image["box"]->set_color(_palette, "grey", 0);


}

// Destructor
End::~End(void) {
}

// Processes new events
const bool End::process(void) {

	if (_key.is_released(ALLEGRO_KEY_ESCAPE)) return true;
	return false;

}


void End::drawPlayerStatus(Player* player,double startX, double startY){
  char name[100], process[100], numbOfComp[100], meanLevel[100];

  const std::vector<Company*>& companies (player-> _get_companies());
  int numberOfCompanies = companies.size();
  
  double meanCMMILevel = 0.0;
  for(int i=0; i<numberOfCompanies; i++)
    meanCMMILevel += companies[i]->_level();

  if(meanCMMILevel != 0)
    meanCMMILevel /= (double)numberOfCompanies;
  
  sprintf(name,"Player Name: %s", player->_name.data());
  sprintf(process,"Process: %s",player->_process.data());
  sprintf(numbOfComp,"Number of Companies: %ld", companies.size());
  sprintf(meanLevel,"Mean level of CMMI: %.1lf", meanCMMILevel);


  player->_avatar->draw<Image::SCALED>(startX + .025,
      startY + .07, .15 * _width, .3 * _height);

  _image["box"]->draw<Image::NORMAL>(startX + .198, startY + 0.01);

  _font["main"]->draw(_palette, "black", startX + 0.2, startY+0.02, name);
  _font["main"]->draw(_palette, "black", startX + 0.2, startY+0.06, process);
  _font["main"]->draw(_palette, "black", startX + 0.2, startY+0.1, numbOfComp);
  _font["main"]->draw(_palette, "black", startX + 0.2, startY+0.14, meanLevel);
  
}


// Draws contents to display
void End::draw(void) {

        Image::set_target(_display);
        // Drawing background
        _image["back"]->draw<Image::SCALED>(0, 0, _width, _height);
        _image["cover"]->draw<Image::NORMAL>(.0, .0);
        _image["VLine"]->draw<Image::NORMAL>(.5,.15);
        
        _image["HLine2"]->draw<Image::NORMAL>(.0,.15);
        _image["HLine"]->draw<Image::NORMAL>(.0,.575);


        _font["title"]->draw<Font::CENTER>(_palette, "white", .5, .025,
                    "GAME OVER - STATUS");

          

        ++_counter;

        double winnerPoints=-1;
        int winnerId=-1;
        for(unsigned i=0; i< _data.player.size(); i++){
          double points = _data.player[i]->_get_points();

          this->drawPlayerStatus(_data.player[i], (i%2)*.5,((i>>1)%2)*0.425+.15);
          
          if(points > winnerPoints){
            winnerPoints = points;
            winnerId = i;
          }
        }


        char finalMessage[500];


        sprintf(finalMessage, "The player %s has Won with %.0lf points", 
            _data.player[winnerId]->_name.data(), winnerPoints);

//	_font["main"]->draw<Font::CENTER>(_palette, 
//            ((_counter%30) > 15 ? "royalblue" : "green"),
//			.5, .85,
			//"THE END!!!\nTHE GROUP...\nWanna quit? press <ESC>");
//			finalMessage);

}
