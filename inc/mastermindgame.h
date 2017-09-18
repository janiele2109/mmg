#ifndef MASTERMINDGAME_H
#define MASTERMINDGAME_H

#include <memory>

using namespace std;

class DecodingBoard;

class MasterMindGame
{
    public:
        MasterMindGame();
        ~MasterMindGame();

        shared_ptr<DecodingBoard> GetDecodingBoard();

    protected:

    private:
        shared_ptr<DecodingBoard> decoding_board_;
};

#endif // MASTERMINDGAME_H
