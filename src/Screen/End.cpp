# include "End.hpp"

// Constructor
End::End(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data) {

	// Fonts
	_load_font("main", config::misc::font::dejavu, 15);
	_load_font("results", config::misc::font::dejavu, 20);
	_load_font("title", config::misc::font::dejavu, 45);
	_load_font("14", config::misc::font::dejavu, 14);

        _load_image("back", config::misc::image::main);
        _load_image("podium", config::misc::image::podium);
        _load_image("avatar_bg", config::misc::avatar::bg);

        _create_image("cover", .45 * _width, .8 * _height);
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
  char name[100], process[100], numbOfComp[100], meanLevel[100], points[100];

  const std::vector<Company*>& companies (player-> _get_companies());
  int numberOfCompanies = companies.size();
  
  double meanCMMILevel = 0.0;
  for(int i=0; i<numberOfCompanies; i++)
    meanCMMILevel += companies[i]->_level();

  if(meanCMMILevel != 0)
    meanCMMILevel /= (double)numberOfCompanies;
  
  sprintf(name,"Nome: %s", player->_name.data());
  sprintf(process,"Processo: %s",player->_process.data());
  sprintf(numbOfComp,"Número de empresas: %ld", companies.size());
  sprintf(meanLevel,"Nível CMMI médio: %.1lf", meanCMMILevel);
  sprintf(points, "Pontuação: %d", player->_get_points());


  player->_avatar->draw<Image::SCALED>(startX + .025,
      startY + .07, .15 * _width, .3 * _height);

  _image["box"]->draw<Image::NORMAL>(startX + .198, startY + 0.01);

  _font["main"]->draw(_palette, "black", startX + 0.2, startY+0.02, name);
  _font["main"]->draw(_palette, "black", startX + 0.2, startY+0.06, process);
  _font["main"]->draw(_palette, "black", startX + 0.2, startY+0.1, numbOfComp);
  _font["main"]->draw(_palette, "black", startX + 0.2, startY+0.14, meanLevel);
  _font["main"]->draw(_palette, "black", startX + 0.2, startY+0.18, points);
  
}

void End::drawPodium(const std::vector<std::pair<double,int>>& playerPoints ){

  std::stringstream ss;
  for(unsigned i=0; i<playerPoints.size(); i++){

    //Draw Podium
    double nPoints = playerPoints[i].first;
    int pId = playerPoints[i].second;

    double pHeight = (nPoints + 0.2 + (0*0.25)) * 0.5 * _height;
    double pX = (i*0.12)+ .51, pY = .9 - (pHeight/_height);

    _image["podium"]->draw<Image::SCALED>(pX, pY, 
        0.12 * _width, pHeight ); 
    _data.player[i]->_avatar->draw<Image::SCALED>(pX + .025,
      pY - (.15*_height/_height), .07 * _width, .15 * _height);
    
    //Draw Status
    Player * player = _data.player[i];

    _image["avatar_bg"]->draw<Image::SCALED>(.1,
      .245 + i * .18);

    // Player avatar
    player->_avatar->draw<Image::SCALED>(.113,
                        .266 + i * .18, 79, 70);

    // Player name
    _font["14"]->draw<Font::LEFT>(_palette, "black",
                        .235, .267 + i * .18, player->_name);

    // Player process
    _font["14"]->draw<Font::LEFT>(_palette, "black",
                        .235, .302 + i * .18, player->_process);

    // Player companies
    ss.str(""), ss << player->_num_companies();
    _font["14"]->draw<Font::LEFT>(_palette, "black",
                        .402, .302 + i * .18, ss.str());

    // Player resources
    ss.str(""), ss << player->_get_resources();
    _font["14"]->draw<Font::LEFT>(_palette, "black",
                        .235, .337 + i * .18, ss.str());

    // Player points
    ss.str(""), ss << player->_get_points();
    _font["14"]->draw<Font::LEFT>(_palette, "black",
                        .402, .337 + i * .18, ss.str());

    
//    const std::vector<Company*>& comps = player-> _get_companies();
//    int numComp = (int) comps.size();



    //for(int j=0; j<numComp; j++){
    //  int level = comps[j]->_level();
    //}

  }
}

// Draws contents to display
void End::draw(void) {

        Image::set_target(_display);
        // Drawing background
        _image["back"]->draw<Image::SCALED>(0, 0, _width, _height);
        _image["cover"]->draw<Image::NORMAL>(.05, .15);

//        _image["VLine"]->draw<Image::NORMAL>(.5,.15;
//        _image["HLine2"]->draw<Image::NORMAL>(.0,.15);
//        _image["HLine"]->draw<Image::NORMAL>(.0,.575);


        _font["title"]->draw<Font::CENTER>(_palette, "white", .5, .025,
                    "GAME OVER - STATUS");

        ++_counter;

        double winnerPoints=-1;
        int winnerId=-1;
	bool tie = true;

        std::vector<std::pair<double,int>> playerPoints;
        for(unsigned i=0; i< _data.player.size(); i++){
          double points = _data.player[i]->_get_points();
          
          playerPoints.push_back( std::make_pair(points,i) );

 //         this->drawPlayerStatus(_data.player[i], (i%2)*.5,((i>>1)%2)*0.425+.15);
          
          if(points > winnerPoints){
            winnerPoints = points;
            winnerId = i;
	    tie = false;
          }
	  else if (points == winnerPoints) tie = true;
        }

        if( winnerPoints > 0 )
          for(unsigned i=0; i< _data.player.size(); i++){
            if( playerPoints[i].first > 0 )
              playerPoints[i].first /= winnerPoints;
          }

        this->drawPodium(playerPoints);


        char finalMessage[500];
	if (tie)
		sprintf(finalMessage, "Houve um empate!");
	else
        	sprintf(finalMessage, "%s ganhou o jogo com %.0lf pontos.", 
            		_data.player[winnerId]->_name.data(), winnerPoints);

	_font["results"]->draw<Font::CENTER>(_palette, 
            ((_counter%30) > 15 ? "royalblue" : "green"),
            ( (.45*_width/_width) - .05 ) /2. + .08,
            .15, finalMessage);

}
