#ifndef MASTERMINDGAME_H
#define MASTERMINDGAME_H

#include <QColor>
#include <memory>

using namespace std;

class DecodingBoard;

struct AnalizedColorPattern
{
    QColor color;
    uint8_t count;
};

struct AnalizedCodeColor
{
    QColor code_color;
    QColor key_color;
};

class MasterMindGame
{
    public:
        MasterMindGame();
        ~MasterMindGame();

        const shared_ptr<DecodingBoard>& GetDecodingBoard();

        bool IsExistedInColorPattern(const QColor& color);
        bool IsSamePosInColorPattern(const QColor& color, uint8_t pos_index);

        unique_ptr<vector<AnalizedColorPattern>> AnalyzeColorPattern();
        unique_ptr<vector<AnalizedCodeColor>> AnalyzeCodeColor();

        uint8_t CountColor(const vector<AnalizedCodeColor>& analized_code_color, const QColor& color);
        uint8_t CalculateScores();

        void CheckResult();

    protected:

    private:
        shared_ptr<DecodingBoard> decoding_board_;
};

#endif // MASTERMINDGAME_H
