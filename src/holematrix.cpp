//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      holematrix.cpp
/// \brief     Implementation of Hole Matrix
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

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>

#include "holematrix.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn         HoleMatrix::HoleMatrix
/// \brief      Constructor (with default values for arguments, played role as default constructor as well as
///             parameterized constructor)
///             - Init data member (allocate memory and set default values for all push controls in Maker area: pattern and key)
///
/// \param      num_of_rows
/// \brief      number of rows in Maker area
/// \default    comdef::makerarea::kDefNumOfRows
///
/// \param      num_of_holes_per_row
/// \brief      number of holes per row in Maker area
/// \default    comdef::makerarea::kDefNumOfHolesPerRow
///
/// \return     none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HoleMatrix::HoleMatrix(uint8_t num_of_rows,
                       uint8_t num_of_holes_per_row): num_of_rows_{num_of_rows},
                                                      num_of_holes_per_row_{num_of_holes_per_row},
                                                      last_enabled_row_{comdef::breakerarea::kLastEnableRowIndex}
{}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     HoleMatrix::~HoleMatrix
/// \brief  Destructor
///         - Cleanup activities (Do nothing right now, shared_ptr variable will be destroyed automatically)
///
/// \param  none
///
/// \return none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HoleMatrix::~HoleMatrix(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     HoleMatrix::GetNumOfRows
/// \brief  Get number of rows in matrix
///
/// \param  none
///
/// \return uint8_t
/// \brief  number of rows
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t HoleMatrix::GetNumOfRows(){ return num_of_rows_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     HoleMatrix::GetNumOfHolesPerRow
/// \brief  Get number of holes per row in matrix
///
/// \param  none
///
/// \return uint8_t
/// \brief  number of holes per row
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t HoleMatrix::GetNumOfHolesPerRow(){ return num_of_holes_per_row_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     HoleMatrix::GetLastEnabledRow
/// \brief  Get index of last enable row in matrix
///
/// \param  none
///
/// \return uint8_t
/// \brief  index of last enabled row
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t HoleMatrix::GetLastEnabledRow(){ return last_enabled_row_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     HoleMatrix::GetHoles
/// \brief  Get hole matrix
///
/// \param  none
///
/// \return const vector<vector<shared_ptr<QPushButton>>>&
/// \brief  holes
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const vector<vector<shared_ptr<QPushButton>>>& HoleMatrix::GetHoles(){ return holes_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn         CustomControls::CreatePushButton
/// \brief      Create QT push button
///
/// \param      rect
/// \brief      default size and location of push button which will be created
/// \default    comdef::decodingboard::pushbutton::kInitLargeRect
///
/// \param      color
/// \brief      default color of disable push button
/// \default    comdef::color::kGrey
///
/// \param      text
/// \brief      default text of push button (label)
/// \default    comdef::kEmptyString
///
/// \param      row_break_index
/// \brief      index of push button which will be broken down to another row (used for key push buttons in Maker area)
/// \default    comdef::decodingboard::kDefRowBreakIndex
///
/// \param      event
/// \brief      triggered event from push button which would be handled
/// \default    nullptr
///
/// \param      receiver
/// \brief      object which would handle triggered event
/// \default    nullptr
///
/// \param      handler
/// \brief      handler function for the triggered event
/// \default    nullptr
///
/// \return     void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     HoleMatrix::DisableCurrentRow
/// \brief  Disable all push buttons in current rows
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HoleMatrix::DisableCurrentRow()
{
    for(auto& push_button: holes_[last_enabled_row_])
        push_button->setEnabled(false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     HoleMatrix::EnableNewRow
/// \brief  Eable all push buttons in next disable rows
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HoleMatrix::EnableNewRow()
{
    for(auto& push_button: holes_[++last_enabled_row_])
    {
        QString style_sheet{comdef::color::kBgColorStyleText.arg(comdef::color::kGrey.name())};

        push_button->setStyleSheet(style_sheet);

        push_button->setEnabled(true);        
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     HoleMatrix::IsCurrentRowFilled
/// \brief  Check for whether all push buttons in current enable row has been chosen with a color by breaker
///
/// \param  none
///
/// \return bool
/// \brief  result of checking
/// \retval true: breaker has finished their turn => execute checking
/// \retval false: breaker has not finished their turn
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool HoleMatrix::IsCurrentRowFilled()
{
    for(auto& push_button: holes_[last_enabled_row_])
        if(push_button->palette().color(QPalette::Background) == comdef::color::kGrey)
            return false;

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     HoleMatrix::DrawHolesMatrix
/// \brief  Draw all push buttons in the decoding area (display all push buttons)
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
