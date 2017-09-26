//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      mastermindgame.cpp
/// \brief     Implementation of Master Mind Game
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

#include <QPalette>
#include <QMessageBox>

#include "mastermindgame.h"
#include "decodingboard.h"
#include "breaker.h"
#include "maker.h"
#include "holematrix.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn         MasterMindGame::MasterMindGame
/// \brief      Default constructor
///             - Init data member (allocate memory and set default values)
///
/// \param      none
///
/// \return     none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MasterMindGame::MasterMindGame(): decoding_board_{new DecodingBoard}{}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     MasterMindGame::~MasterMindGame
/// \brief  Destructor
///         - Cleanup activities (Do nothing right now, shared_ptr variable will be destroyed automatically)
///
/// \param  none
///
/// \return none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MasterMindGame::~MasterMindGame(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     MasterMindGame::GetDecodingBoard
/// \brief  Get decording board
///
/// \param  none
///
/// \return const shared_ptr<DecodingBoard>&
/// \brief  decoding board
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const shared_ptr<DecodingBoard>& MasterMindGame::GetDecodingBoard(){ return decoding_board_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     MasterMindGame::IsExistedInColorPattern
/// \brief  Check for whether specific color exists in color pattern
///
/// \param      color
/// \brief      specific color for checking
///
/// \return bool
/// \brief  result of checking
/// \retval true: color exists
/// \retval false: color does not exist
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MasterMindGame::IsExistedInColorPattern(const QColor& color)
{
    uint8_t num_of_holes_per_row = decoding_board_->GetMaker()->GetPatternMatrix()->GetNumOfHolesPerRow();

    vector<shared_ptr<QPushButton>> color_pattern{decoding_board_->GetMaker()->GetPatternMatrix()->GetHoles()[0]};

    for(uint8_t cur_hole_index = 0; cur_hole_index < num_of_holes_per_row; cur_hole_index++)
        if(color == color_pattern[cur_hole_index]->palette().color(QPalette::Button))
            return true;

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     MasterMindGame::IsSamePosInColorPattern
/// \brief  Check for whether specific color exists in color pattern at specified position
///
/// \param      color
/// \brief      specific color for checking
///
/// \param      pos_index
/// \brief      specific position for checking
///
/// \return bool
/// \brief  result of checking
/// \retval true: color exists at the same position
/// \retval false: color does not exist at the same position
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MasterMindGame::IsSamePosInColorPattern(const QColor& color, uint8_t pos_index)
{
    uint8_t num_of_holes_per_row = decoding_board_->GetMaker()->GetPatternMatrix()->GetNumOfHolesPerRow();

    vector<shared_ptr<QPushButton>> color_pattern{decoding_board_->GetMaker()->GetPatternMatrix()->GetHoles()[0]};

    for(uint8_t cur_hole_index = 0; cur_hole_index < num_of_holes_per_row; cur_hole_index++)
        if(color == color_pattern[cur_hole_index]->palette().color(QPalette::Button) &&
           cur_hole_index == pos_index)
            return true;

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     MasterMindGame::AnalyzeCodeColor
/// \brief  Analyze color chosen by breaker in Breaker area
///
/// \param  none
///
/// \return unique_ptr<vector<comdef::AnalizedCodeColor>>
/// \brief  analized code colors
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unique_ptr<vector<comdef::AnalizedCodeColor>> MasterMindGame::AnalyzeCodeColor()
{
    unique_ptr<vector<comdef::AnalizedCodeColor>> analized_code_color{new vector<comdef::AnalizedCodeColor>};

    uint8_t num_of_holes_per_row = decoding_board_->GetBreaker()->GetHolesMatrix()->GetNumOfHolesPerRow();

    uint8_t last_enable_row_index = decoding_board_->GetBreaker()->GetHolesMatrix()->GetLastEnabledRow();

    vector<shared_ptr<QPushButton>> code_color_row{decoding_board_->GetBreaker()->GetHolesMatrix()->GetHoles()[last_enable_row_index]};

    for(uint8_t cur_hole_index = 0; cur_hole_index < num_of_holes_per_row; cur_hole_index++)
    {
        shared_ptr<QPushButton> code_color_btn = code_color_row.at(cur_hole_index);

        QColor cur_color = code_color_btn->palette().color(QPalette::Button);

        QColor key_color = comdef::color::kLight;

        if(IsExistedInColorPattern(cur_color))
        {
            if(IsSamePosInColorPattern(cur_color, cur_hole_index))
                key_color = comdef::color::kBlack;
            else
                key_color = comdef::color::kWhite;
        }

        bool skip = false;

        for(uint8_t color_index = 0; color_index < analized_code_color.get()->size(); color_index++)
            if(analized_code_color.get()->at(color_index).code_color == cur_color &&
               analized_code_color.get()->at(color_index).key_color == key_color &&
               key_color == comdef::color::kWhite)

                skip = true;

        if(!skip && key_color != comdef::color::kLight)
            analized_code_color.get()->push_back(comdef::AnalizedCodeColor{cur_color, key_color});
    }

    return analized_code_color;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     MasterMindGame::CountColor
/// \brief  Count for specific color in analyzed code color (for checking duplicate cases)
///
/// \param  analized_code_color
/// \brief  analyzed code color for looping
///
/// \param  color
/// \brief  color used for checking
///
/// \return uint8_t
/// \brief  number of occurence of specific color in analyzed code color
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t MasterMindGame::CountColor(const vector<comdef::AnalizedCodeColor>& analized_code_color, const QColor& color)
{
    uint8_t cnt = 0;

    for(auto& item: analized_code_color)
        if(item.code_color.rgb() == color.rgb())
            cnt++;

    return cnt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     MasterMindGame::CalculateScores
/// \brief  Calculate final score
///
/// \param  none
///
/// \return uint8_t
/// \brief  final score
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t MasterMindGame::CalculateScores()
{
    uint8_t final_point = 0;

    uint8_t cur_row_idx = decoding_board_->GetBreaker()->GetHolesMatrix()->GetLastEnabledRow();

    shared_ptr<vector<comdef::AnalizedColorPattern>> analized_color_pattern = decoding_board_->GetMaker()->GetAnalizedColorPattern();

    unique_ptr<vector<comdef::AnalizedCodeColor>> analized_code_color = AnalyzeCodeColor();

    for(comdef::AnalizedColorPattern& item: *(analized_color_pattern.get()))
    {
        // count specific color from color pattern generated by maker in code color array chosen by breaker
        int cnt = CountColor(*(analized_code_color.get()), item.color);

        // if there are more item with specific color than in the color pattern, remove redundant items in code color array
        while(cnt > item.count)
        {
            for(vector<comdef::AnalizedCodeColor>::iterator it = analized_code_color.get()->begin(); it != analized_code_color.get()->end(); it++)
                if(it->code_color == item.color &&
                   it->key_color == comdef::color::kWhite)
                {
                    analized_code_color.get()->erase(it);
                    cnt--;
                    break;
                }
        }
    }

    for(comdef::AnalizedCodeColor& item: *(analized_code_color.get()))
    {
        if(item.key_color == comdef::color::kBlack)
            final_point++;

        decoding_board_->GetMaker()->SetKeyColor(cur_row_idx, item.key_color);
    }

    return final_point;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     MasterMindGame::CheckResult
/// \brief  Check the result of game (win or lose) and display appropriate messages
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MasterMindGame::CheckResult()
{
    uint8_t score                   = CalculateScores();
    uint8_t num_of_holes_per_row    = decoding_board_->GetBreaker()->GetHolesMatrix()->GetNumOfHolesPerRow();
    uint8_t last_enabled_row        = decoding_board_->GetBreaker()->GetHolesMatrix()->GetLastEnabledRow();

    if(score == num_of_holes_per_row)
    {
        decoding_board_->GetMaker()->DisplayPatternMatrix();
        QMessageBox::information(nullptr, comdef::info::kAppName, "Hurray! You win!");
    }
    else if(score < num_of_holes_per_row &&
            last_enabled_row == comdef::breakerarea::kDefNumOfRows - 1)
    {
        QMessageBox::information(nullptr, comdef::info::kAppName, "You lose!");
        decoding_board_->GetMaker()->DisplayPatternMatrix();
    }
    else
    {
        decoding_board_->GetBreaker()->GetHolesMatrix()->DisableCurrentRow();
        decoding_board_->GetBreaker()->GetHolesMatrix()->EnableNewRow();
    }
}
