#include "mastermindgame.h"
#include "decodingboard.h"

MasterMindGame::MasterMindGame(): decoding_board_(new DecodingBoard){}

MasterMindGame::~MasterMindGame(){}

shared_ptr<DecodingBoard> MasterMindGame::GetDecodingBoard(){ return decoding_board_; }
