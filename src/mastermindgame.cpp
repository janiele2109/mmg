#include "mastermindgame.h"
#include "decodingboard.h"
#include "breakerareas.h"
#include "makerareas.h"
#include "holematrix.h"
#include <QPalette>

#include <QMessageBox>

MasterMindGame::MasterMindGame(): decoding_board_(new DecodingBoard){}

MasterMindGame::~MasterMindGame(){}

shared_ptr<DecodingBoard> MasterMindGame::GetDecodingBoard(){ return decoding_board_; }

bool MasterMindGame::CheckColorExistence(QColor color)
{
    uint8_t num_of_holes_per_row = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetHolesPerRow();

    for(uint8_t i = 0; i < num_of_holes_per_row; i++)
        if(color.rgb() == decoding_board_->GetMakerAreas()->GetEncodedColorList().at(i).rgb())
            return true;

    return false;
}

bool MasterMindGame::SameColorPos(QColor color, uint8_t index)
{
    uint8_t num_of_holes_per_row = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetHolesPerRow();

    for(uint8_t i = 0; i < num_of_holes_per_row; i++)
        if(color.rgb() == decoding_board_->GetMakerAreas()->GetEncodedColorList().at(i).rgb() &&
           i == index)
            return true;

    return false;
}

uint8_t MasterMindGame::CalculatePoint()
{
    uint8_t final_point = 0;
    uint8_t cur_row_idx = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetFirstDisableRow() - 1;
    uint8_t num_of_holes_per_row = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetHolesPerRow();

    for(uint8_t i = 0; i < num_of_holes_per_row; i++)
    {
        QColor key_peg = comdef::color::kLight;

        shared_ptr<QPushButton> push_button = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetHoles().at(cur_row_idx).at(i);

        QColor cur_color = push_button->palette().color(QPalette::Button);

        bool color_exists = CheckColorExistence(cur_color);

        if(color_exists)
        {
            if(SameColorPos(cur_color, i))
            {
                final_point++;
                key_peg = comdef::color::kBlack;
            }
            else
                key_peg = comdef::color::kWhite;
        }

        if(key_peg == comdef::color::kBlack ||
           (key_peg == comdef::color::kWhite))
            decoding_board_->GetMakerAreas()->SetKeyPeg(cur_row_idx, key_peg);
    }

    return final_point;
}

void MasterMindGame::CheckResult()
{
    if(CalculatePoint() == comdef::makerarea::kDefNumOfLargeHolesPerRow)
        QMessageBox::information(nullptr, "MasterMind", "Hurray! You win!");
    else if(decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetFirstDisableRow() < comdef::breakerarea::kDefNumOfRows)
    {
        decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->DisableAllPushButtons();
        decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->EnableNewRow();
    }
    else
        QMessageBox::information(nullptr, "MasterMind", "You lose!");
}
