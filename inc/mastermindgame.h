#ifndef MASTERMINDGAME_H
#define MASTERMINDGAME_H

#include <QColor>
#include <memory>

using namespace std;

class DecodingBoard;

struct encodedColorAnalized{
    encodedColorAnalized(QColor color, uint8_t dup_no)
    {
        dup_color = color;
        no_of_present = dup_no;
    }

    QColor dup_color;
    uint8_t no_of_present;
};

struct pickedColorAnalized{
    pickedColorAnalized(QColor picked, QColor key)
    {
        picked_color = picked;
        key_peg_color = key;
    }

    QColor picked_color;
    QColor key_peg_color;
};

class MasterMindGame
{
    public:
        MasterMindGame();
        ~MasterMindGame();

        shared_ptr<DecodingBoard> GetDecodingBoard();

        bool CheckColorExistence(QColor color);
        bool SameColorPos(QColor color, uint8_t pos_index);
        uint8_t CalculatePoint();
        void CheckResult();
        vector<encodedColorAnalized> analyzeEncodedCodeList();
        vector<pickedColorAnalized> analyzePickedCodeList();
        uint8_t CountColor(vector<pickedColorAnalized> search_vec, QColor color);

    protected:

    private:
        shared_ptr<DecodingBoard> decoding_board_;
};

#endif // MASTERMINDGAME_H
