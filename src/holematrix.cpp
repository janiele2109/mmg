#include "holematrix.h"

HoleMatrix::HoleMatrix(uint8_t num_of_rows,
                       uint8_t num_of_large_holes_per_row): num_of_rows_(num_of_rows),
                                                            holes_per_row_(num_of_large_holes_per_row),
                                                            first_disable_row_(0)
{}

HoleMatrix::~HoleMatrix(){}

uint8_t HoleMatrix::GetNumOfRows(){ return num_of_rows_; }

uint8_t HoleMatrix::GetHolesPerRow(){ return holes_per_row_; }

uint8_t HoleMatrix::GetFirstDisableRow(){ return first_disable_row_; }

vector< vector<shared_ptr<QPushButton>> >& HoleMatrix::GetHoles()
{
    return holes_;
}

void HoleMatrix::InitHolesMatrix(QRect      init_rect,
                                 QColor     color,
                                 QString    title,
                                 uint8_t    breakdow_index,
                                 void (QAbstractButton::*event)(bool),
                                 CustomControls* receiver,
                                 void (CustomControls::*handler)())
{
    uint16_t org_x          = init_rect.x();
    uint16_t padding        = comdef::decodingboard::pushbutton::kLargePadding;
    uint16_t row_spacing    = comdef::decodingboard::pushbutton::kLargeRowSpacing;

    for(int i = 0; i < num_of_rows_; i++)
    {
        vector<shared_ptr<QPushButton>> row;

        for(int j = 0; j < holes_per_row_; j++)
        {
            if (breakdow_index != 0 && j % 2 == 0)
            {
                row_spacing = comdef::decodingboard::pushbutton::kSmallRowSpacing;

                padding = comdef::decodingboard::pushbutton::kSmallPadding;

                init_rect.moveTo(org_x, init_rect.y() + init_rect.height() + padding);
            }

            unique_ptr<QPushButton> btn = CustomControls::CreatePushButton(init_rect,
                                                                           color,
                                                                           title,
                                                                           event,
                                                                           receiver,
                                                                           handler);

            init_rect.moveTo(init_rect.x() + init_rect.width() + padding, init_rect.y());

            row.push_back(move(btn));
        }

        init_rect.moveTo(org_x, init_rect.y() + row_spacing);

        holes_.push_back(row);
    }
}

void HoleMatrix::DisableAllPushButtons()
{
    for(auto row: holes_)
        for(auto push_button: row)
            push_button->setEnabled(false);
}

void HoleMatrix::EnableNewRow()
{
    for(auto push_button: holes_.at(first_disable_row_))
    {
        push_button->setEnabled(true);

        QString style = QString("%1%2").arg(comdef::color::kBgColorStyleText).arg("#").arg(comdef::color::kGrey.rgba(), 8, 16);
        push_button->setStyleSheet(style);
    }

    first_disable_row_++;
}

bool HoleMatrix::IsFulfilledRow()
{
    for(auto push_button: holes_.at(first_disable_row_ - 1))
        if(push_button->palette().color(QPalette::Background).rgb() == comdef::color::kGrey.rgb())
            return false;

    return true;
}
