//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      mastermindgame.h
/// \brief     All declarations and definition for Master Mind Game
///
/// \author    Janie
/// \version   1.0.0.0
///
/// \note
///
/// Version      When        Who         Remarks
/// ===========================================================================================================================
///
/// 0.0.0.1      14Sep2017   Janie       First creation
/// 1.0.0.0      25Sep2017   Janie       First release
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MASTERMINDGAME_H
#define MASTERMINDGAME_H

#include <memory>

#include <QColor>
#include <QComboBox>

#include "comdef.h"

using namespace std;

class DecodingBoard;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \class      MasterMindGame
/// \brief      Abstract object which is responsible for Master Mind Game
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MasterMindGame
{
    public:
        MasterMindGame();
        ~MasterMindGame();

        const shared_ptr<DecodingBoard>& GetDecodingBoard();

        bool IsExistedInColorPattern(const QColor& color);

        bool IsSamePosInColorPattern(const QColor& color,
                                     uint8_t pos_index);

        unique_ptr<vector<comdef::AnalizedCodeColor>> AnalyzeCodeColor();

        uint8_t CountColor(const vector<comdef::AnalizedCodeColor>& analized_code_color,
                           const QColor& color);

        uint8_t CalculateScores();

        void CheckResult();

    protected:

    private:
        /// handle decoding board
        shared_ptr<DecodingBoard> decoding_board_;
};

#endif // MASTERMINDGAME_H
