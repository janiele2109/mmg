#include <QPalette>
#include <QMessageBox>

#include "mastermindgame.h"
#include "decodingboard.h"
#include "breakerareas.h"
#include "makerareas.h"
#include "holematrix.h"

MasterMindGame::MasterMindGame(): decoding_board_{new DecodingBoard}{}

MasterMindGame::~MasterMindGame(){}

shared_ptr<DecodingBoard> MasterMindGame::GetDecodingBoard(){ return decoding_board_; }

vector<encodedColorAnalized> MasterMindGame::analyzeEncodedCodeList()
{
    vector<encodedColorAnalized> encoded_color_analyzed;

    uint8_t num_of_holes_per_row = decoding_board_->GetMakerAreas()->GetEncodedColorList().size();

    for(uint8_t idx = 0; idx < num_of_holes_per_row; idx++)
    {
        QColor cur_color = decoding_board_->GetMakerAreas()->GetEncodedColorList().at(idx);

        uint8_t i = 0;
        bool flag = true;

        for(; i < encoded_color_analyzed.size(); i++)
            if(encoded_color_analyzed[i].dup_color == cur_color)
            {
                encoded_color_analyzed[i].no_of_present++;
                flag = false;
            }

        if(flag &&
           (encoded_color_analyzed.size() == 0 ||
           encoded_color_analyzed.size() == i))
        {
            encodedColorAnalized item(cur_color, 1);
            encoded_color_analyzed.push_back(item);
        }
    }

    return encoded_color_analyzed;
}

vector<pickedColorAnalized> MasterMindGame::analyzePickedCodeList()
{
    vector<pickedColorAnalized> picked_color_analyzed;

    uint8_t num_of_holes_per_row = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetHolesPerRow();

    for(uint8_t idx = 0; idx < num_of_holes_per_row; idx++)
    {
        uint8_t first_disable_row = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetFirstDisableRow();
        shared_ptr<QPushButton> push_button = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetHoles().at(first_disable_row - 1).at(idx);

        QColor cur_color = push_button->palette().color(QPalette::Button);

        bool color_exists = CheckColorExistence(cur_color);
        bool flag = true;

        QColor key_peg = comdef::color::kLight;

        if(color_exists)
            if(SameColorPos(cur_color, idx))
                key_peg = comdef::color::kBlack;
            else
                key_peg = comdef::color::kWhite;

        uint8_t i = 0;

        for(; i < picked_color_analyzed.size(); i++)
            if(picked_color_analyzed[i].picked_color == cur_color &&
               picked_color_analyzed[i].key_peg_color == key_peg &&
               key_peg == comdef::color::kWhite)
            {
                flag = false;
                break;
            }

        if(flag &&
           (key_peg == comdef::color::kWhite || key_peg == comdef::color::kBlack) &&
           (picked_color_analyzed.size() == 0 || picked_color_analyzed.size() == i))
        {
            pickedColorAnalized item(cur_color, key_peg);
            picked_color_analyzed.push_back(item);
        }
    }

    return picked_color_analyzed;
}

bool MasterMindGame::CheckColorExistence(QColor color)
{
    uint8_t num_of_holes_per_row = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetHolesPerRow();

    for(uint8_t idx = 0; idx < num_of_holes_per_row; idx++)
        if(color.rgb() == decoding_board_->GetMakerAreas()->GetEncodedColorList().at(idx).rgb())
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

uint8_t MasterMindGame::CountColor(vector<pickedColorAnalized> search_vec, QColor color)
{
    uint8_t cnt = 0;

    for(auto item: search_vec)
        if(item.picked_color == color)
            cnt++;

    return cnt;
}
#include <QMessageBox>
uint8_t MasterMindGame::CalculatePoint()
{
    uint8_t final_point = 0;
    uint8_t cur_row_idx = decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetFirstDisableRow() - 1;

    vector<encodedColorAnalized> encoded_color_analized = analyzeEncodedCodeList();

    vector<pickedColorAnalized> picked_color_analized = analyzePickedCodeList();

    for(encodedColorAnalized item: encoded_color_analized)
    {
        int cnt = CountColor(picked_color_analized, item.dup_color);

        while(cnt > item.no_of_present)
        {
            for(vector<pickedColorAnalized>::iterator it = picked_color_analized.begin(); it != picked_color_analized.end(); it++)
                if(it->picked_color == item.dup_color &&
                   it->key_peg_color == comdef::color::kWhite)
                {
                    picked_color_analized.erase(it);
                    cnt--;
                    break;
                }
        }
    }

    for(pickedColorAnalized item: picked_color_analized)
    {
        final_point++;
        decoding_board_->GetMakerAreas()->SetKeyPeg(cur_row_idx, item.key_peg_color);
    }

    return final_point;
}

void MasterMindGame::CheckResult()
{
    if(CalculatePoint() == comdef::makerarea::kDefNumOfLargeHolesPerRow)
    {
        //decoding_board_->GetMakerAreas()->DrawEncodedColorRow();
        QMessageBox::information(nullptr, comdef::info::kAppName, "Hurray! You win!");
    }
    else if(decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->GetFirstDisableRow() < comdef::breakerarea::kDefNumOfRows)
    {
        decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->DisableAllPushButtons();
        decoding_board_->GetBreakerAreas()->GetLargeHolesMatrix()->EnableNewRow();
    }
    else
    {
        //decoding_board_->GetMakerAreas()->DrawEncodedColorRow();
        QMessageBox::information(nullptr, comdef::info::kAppName, "You lose!");
    }
}
