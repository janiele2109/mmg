#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>

#include "holematrix.h"

HoleMatrix::HoleMatrix(uint8_t num_of_rows,
                       uint8_t num_of_holes_per_row): num_of_rows_{num_of_rows},
                                                      num_of_holes_per_row_{num_of_holes_per_row},
                                                      last_enabled_row_{comdef::breakerarea::kLastEnableRowIndex}
{}

HoleMatrix::~HoleMatrix(){}

uint8_t HoleMatrix::GetNumOfRows(){ return num_of_rows_; }

uint8_t HoleMatrix::GetNumOfHolesPerRow(){ return num_of_holes_per_row_; }

uint8_t HoleMatrix::GetLastEnabledRow(){ return last_enabled_row_; }

const vector<vector<shared_ptr<QPushButton>>>& HoleMatrix::GetHoles(){ return holes_; }

void HoleMatrix::InitHolesMatrix(QRect            rect,
                                 const QColor&    color,
                                 const QString&   text,
                                 const int        row_break_index,
                                 void (QAbstractButton::* event)(bool),
                                 const CustomControls* receiver,
                                 void (CustomControls::* handler)())
{
    uint16_t org_top_left_x     =   rect.x();
    uint16_t padding            =   comdef::decodingboard::pushbutton::kLargePadding;
    uint16_t row_spacing        =   comdef::decodingboard::pushbutton::kLargeRowSpacing;

    for(uint8_t cur_row = 0; cur_row < num_of_rows_; cur_row++)
    {
        vector<shared_ptr<QPushButton>> row;

        for(uint8_t cur_hole = 0; cur_hole < num_of_holes_per_row_; cur_hole++)
        {
            if(row_break_index == comdef::makerarea::kDefRowBreakIndex &&
               cur_hole % 2 == 0)
            {
                row_spacing = comdef::decodingboard::pushbutton::kSmallRowSpacing;

                padding = comdef::decodingboard::pushbutton::kSmallPadding;

                rect.moveTo(org_top_left_x,
                            rect.y() + rect.height() + padding);
            }

            shared_ptr<QPushButton> btn = CustomControls::CreatePushButton(rect,
                                                                           color,
                                                                           text,
                                                                           event,
                                                                           receiver,
                                                                           handler,
                                                                           false);

            rect.moveTo(rect.x() + rect.width() + padding,
                        rect.y());

            row.push_back(btn);
        }

        rect.moveTo(org_top_left_x,
                    rect.y() + row_spacing);

        holes_.push_back(row);
    }
}

void HoleMatrix::DisableCurrentRow()
{
    for(auto& push_button: holes_[last_enabled_row_])
        push_button->setEnabled(false);
}

void HoleMatrix::EnableNewRow()
{
    for(auto& push_button: holes_[++last_enabled_row_])
    {
        QString style_sheet{comdef::color::kBgColorStyleText.arg(comdef::color::kGrey.name())};

        push_button->setStyleSheet(style_sheet);

        push_button->setEnabled(true);        
    }
}

bool HoleMatrix::IsCurrentRowFilled()
{
    for(auto& push_button: holes_[last_enabled_row_])
        if(push_button->palette().color(QPalette::Background) == comdef::color::kGrey)
            return false;

    return true;
}

void HoleMatrix::DrawHolesMatrix()
{
    QApplication*   app             =   dynamic_cast<QApplication*>(QApplication::instance());
    QMainWindow*    main_window     =   nullptr;

    for(QWidget* widget: app->topLevelWidgets())
        if(widget->inherits(comdef::mainwindow::kClassName.c_str()))
            main_window = dynamic_cast<QMainWindow*>(widget);

    unique_ptr<QVBoxLayout> outter_layout{new QVBoxLayout{main_window->centralWidget()}};

    for(auto& row: holes_)
    {
        unique_ptr<QHBoxLayout> row_layout{new QHBoxLayout};

        for(auto& push_button: row)
            row_layout->addWidget(push_button.get());

        outter_layout->addLayout(row_layout.get());
    }
}
