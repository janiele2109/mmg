#include <QPalette>
#include <QMessageBox>

#include "mastermindgame.h"
#include "decodingboard.h"
#include "breaker.h"
#include "maker.h"
#include "holematrix.h"

MasterMindGame::MasterMindGame(): decoding_board_{new DecodingBoard}{}

MasterMindGame::~MasterMindGame(){}

const shared_ptr<DecodingBoard>& MasterMindGame::GetDecodingBoard(){ return decoding_board_; }

bool MasterMindGame::IsExistedInColorPattern(const QColor& color)
{
    uint8_t num_of_holes_per_row = decoding_board_->GetMaker()->GetPatternMatrix()->GetNumOfHolesPerRow();

    vector<shared_ptr<QPushButton>> color_pattern{decoding_board_->GetMaker()->GetPatternMatrix()->GetHoles()[0]};

    for(uint8_t cur_hole_index = 0; cur_hole_index < num_of_holes_per_row; cur_hole_index++)
        if(color == color_pattern[cur_hole_index]->palette().color(QPalette::Button))
            return true;

    return false;
}

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

unique_ptr<vector<AnalizedColorPattern>> MasterMindGame::AnalyzeColorPattern()
{
    unique_ptr<vector<AnalizedColorPattern>> analized_color_pattern{new vector<AnalizedColorPattern>};

    uint8_t num_of_holes_per_row = decoding_board_->GetMaker()->GetPatternMatrix()->GetNumOfHolesPerRow();

    vector<shared_ptr<QPushButton>> color_pattern{decoding_board_->GetMaker()->GetPatternMatrix()->GetHoles()[0]};

    for(uint8_t cur_hole_index = 0; cur_hole_index < num_of_holes_per_row; cur_hole_index++)
    {
        bool existed = false;

        QColor cur_color = color_pattern[cur_hole_index]->palette().color(QPalette::Button);

        for(uint8_t color_index = 0; color_index < analized_color_pattern.get()->size(); color_index++)
            if(analized_color_pattern.get()->at(color_index).color == cur_color)
            {
                analized_color_pattern.get()->at(color_index).count++;
                existed = true;
            }

        if(!existed)
            analized_color_pattern.get()->push_back(AnalizedColorPattern{cur_color, 1});
    }

    return analized_color_pattern;
}

unique_ptr<vector<AnalizedCodeColor>> MasterMindGame::AnalyzeCodeColor()
{
    unique_ptr<vector<AnalizedCodeColor>> analized_code_color{new vector<AnalizedCodeColor>};

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
            analized_code_color.get()->push_back(AnalizedCodeColor{cur_color, key_color});
    }

    return analized_code_color;
}

uint8_t MasterMindGame::CountColor(const vector<AnalizedCodeColor>& analized_code_color, const QColor& color)
{
    uint8_t cnt = 0;

    for(auto& item: analized_code_color)
        if(item.code_color == color)
            cnt++;

    return cnt;
}

uint8_t MasterMindGame::CalculateScores()
{
    uint8_t final_point = 0;

    uint8_t cur_row_idx = decoding_board_->GetBreaker()->GetHolesMatrix()->GetLastEnabledRow();

    unique_ptr<vector<AnalizedColorPattern>> analized_color_pattern = AnalyzeColorPattern();

    unique_ptr<vector<AnalizedCodeColor>> analized_code_color = AnalyzeCodeColor();

    for(AnalizedColorPattern& item: *(analized_color_pattern.get()))
    {
        int cnt = CountColor(*(analized_code_color.get()), item.color);

        while(cnt > item.count)
        {
            for(vector<AnalizedCodeColor>::iterator it = analized_code_color.get()->begin(); it != analized_code_color.get()->end(); it++)
                if(it->code_color == item.color &&
                   it->key_color == comdef::color::kWhite)
                {
                    analized_code_color.get()->erase(it);
                    cnt--;
                    break;
                }
        }
    }

    for(AnalizedCodeColor& item: *(analized_code_color.get()))
    {
        final_point++;
        decoding_board_->GetMaker()->SetKeyColor(cur_row_idx, item.key_color);
    }

    return final_point;
}

void MasterMindGame::CheckResult()
{
    if(CalculateScores() == comdef::makerarea::kDefNumOfHolesPerRow)
    {
        //decoding_board_->GetMaker()->DrawPatternMatrix();
        QMessageBox::information(nullptr, comdef::info::kAppName, "Hurray! You win!");
    }
    else if(decoding_board_->GetBreaker()->GetHolesMatrix()->GetLastEnabledRow() < comdef::breakerarea::kDefNumOfRows - 1)
    {
        decoding_board_->GetBreaker()->GetHolesMatrix()->DisableCurrentRow();
        decoding_board_->GetBreaker()->GetHolesMatrix()->EnableNewRow();
    }
    else
    {
        //decoding_board_->GetMaker()->DrawPatternMatrix();
        QMessageBox::information(nullptr, comdef::info::kAppName, "You lose!");
    }
}
