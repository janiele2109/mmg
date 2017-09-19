#ifndef MASTERMINDGAME_H
#define MASTERMINDGAME_H

#include <QColor>
#include <memory>

using namespace std;

class DecodingBoard;

class MasterMindGame
{
    public:
        MasterMindGame();
        ~MasterMindGame();

        shared_ptr<DecodingBoard> GetDecodingBoard();

        bool CheckColorExistence(QColor color);
        bool SameColorPos(QColor color, uint8_t index);
        uint8_t CalculatePoint();
        void CheckResult();

    protected:

    private:
        shared_ptr<DecodingBoard> decoding_board_;
};

#endif // MASTERMINDGAME_H
