//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      maker.cpp
/// \brief     Implementation of Maker area in Decoding board
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

#include <random>

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGridLayout>

#include "maker.h"
#include "comdef.h"
#include "holematrix.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn         Maker::Maker
/// \brief      Default constructor
///             - Init data member (allocate memory and set default values for all push controls in Breaker area)
///             - Initialize color pattern (assumed created by maker)
///             - Analyze the color pattern in order to compare with pattern from breaker
///             - Initialize key matrix (holes) in maker area
///
/// \param      none
///
/// \return     none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Maker::Maker(): pattern_matrix_{new HoleMatrix{comdef::makerarea::kDefNumOfRows,
                                               comdef::makerarea::kDefNumOfHolesPerRow}},
                analized_color_pattern_{new vector<comdef::AnalizedColorPattern>},
                key_matrix_{new HoleMatrix{comdef::breakerarea::kDefNumOfRows,
                                           comdef::breakerarea::kDefNumOfHolesPerRow}}
{
    InitPatternMatrix();

    InitKeyMatrix();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::~Maker
/// \brief  Destructor
///         - Cleanup activities (Do nothing right now, shared_ptr variable will be destroyed automatically)
///
/// \param  none
///
/// \return none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Maker::~Maker(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::GetPatternMatrix
/// \brief  Get pattern matrix (all of push buttons in Maker area)
///
/// \param  none
///
/// \return shared_ptr<HoleMatrix>
/// \brief  color pattern matrix in Maker area
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

shared_ptr<HoleMatrix> Maker::GetPatternMatrix(){ return pattern_matrix_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::GetAnalizedColorPattern
/// \brief  Get analized color pattern from color pattern in Maker area
///
/// \param  none
///
/// \return shared_ptr<vector<comdef::AnalizedColorPattern>>
/// \brief  analized color pattern
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

shared_ptr<vector<comdef::AnalizedColorPattern>> Maker::GetAnalizedColorPattern(){ return analized_color_pattern_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::GetKeyMatrix
/// \brief  Get key matrix (holes) in Maker area
///
/// \param  none
///
/// \return shared_ptr<HoleMatrix>
/// \brief  key matrix in Maker area
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

shared_ptr<HoleMatrix> Maker::GetKeyMatrix(){ return key_matrix_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::InitPatternMatrix
/// \brief  Initialize color pattern (assumed created by maker)
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Maker::InitPatternMatrix()
{
    QRect rect{comdef::decodingboard::pushbutton::kInitLargeRect};

    uint16_t new_y = comdef::decodingboard::combobox::kInitRect.y() -
                     comdef::decodingboard::pushbutton::kLargeHeight -
                     comdef::decodingboard::pushbutton::kLargePadding -
                     comdef::decodingboard::pushbutton::kSmallPadding;

    vector<QColor> color{comdef::color::kGreen,
                         comdef::color::kBlue,
                         comdef::color::kYellow,
                         comdef::color::kLightGreen,
                         comdef::color::kBrown,
                         comdef::color::kRed,
                         comdef::color::kLight};

    random_device rand_dev;

    default_random_engine rand_en{rand_dev()};

    uniform_int_distribution<int> uniform_dist(0, color.size() - 1);

    rect.moveTo(rect.x(), new_y);

    pattern_matrix_->InitHolesMatrix(rect,
                                     comdef::color::kLight,
                                     comdef::kEmptyString,
                                     comdef::decodingboard::kDefRowBreakIndex,
                                     &QPushButton::clicked,
                                     new CustomControls(),
                                     &CustomControls::SetQPushButtonColor,
                                     false);

    uint8_t num_of_holes = pattern_matrix_->GetNumOfHolesPerRow();
    uint8_t cur_pattern_row = pattern_matrix_->GetNumOfRows() - 1;

    for(uint8_t cur_hole = 0; cur_hole < num_of_holes; cur_hole++)
    {
        int index_rand_val = uniform_dist(rand_en);

        QString style_sheet{comdef::color::kBgColorStyleText.arg(color[index_rand_val].name())};

        pattern_matrix_->GetHoles()[cur_pattern_row][cur_hole]->setStyleSheet(style_sheet);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::InitKeyMatrix
/// \brief  Initialize key matrix (holes) in maker area
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Maker::InitKeyMatrix()
{
    QRect rect(comdef::decodingboard::pushbutton::kInitSmallRect);

    uint16_t init_x = comdef::decodingboard::pushbutton::kInitX;
    uint16_t width_rect = comdef::decodingboard::pushbutton::kInitLargeRect.width();
    uint8_t  num_of_code_holes_per_row = pattern_matrix_->GetNumOfHolesPerRow();
    uint16_t padding = comdef::decodingboard::pushbutton::kLargePadding;

    uint16_t new_x = init_x +
                     num_of_code_holes_per_row * width_rect +
                     (num_of_code_holes_per_row - 1) * padding +
                     padding;

    rect.moveTo(new_x, rect.y());

    key_matrix_->InitHolesMatrix(rect,
                                 comdef::color::kLight,
                                 comdef::kEmptyString,
                                 comdef::makerarea::kDefRowBreakIndex,
                                 &QPushButton::clicked,
                                 new CustomControls(),
                                 &CustomControls::SetQPushButtonColor,
                                 false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::AnalyzeColorPattern
/// \brief  Analyze the color pattern in order to compare with pattern from breaker
///
/// \param  none
///
/// \return const shared_ptr<vector<comdef::AnalizedColorPattern>>&
/// \brief  analized color pattern
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const shared_ptr<vector<comdef::AnalizedColorPattern>>& Maker::AnalyzeColorPattern()
{
    uint8_t num_of_holes_per_row = GetPatternMatrix()->GetNumOfHolesPerRow();

    vector<shared_ptr<QPushButton>> color_pattern{GetPatternMatrix()->GetHoles()[0]};

    for(uint8_t cur_hole_index = 0; cur_hole_index < num_of_holes_per_row; cur_hole_index++)
    {
        bool existed = false;

        QColor cur_color = color_pattern[cur_hole_index]->palette().color(QPalette::Button);

        for(uint8_t color_index = 0; color_index < analized_color_pattern_.get()->size(); color_index++)
            if(analized_color_pattern_.get()->at(color_index).color == cur_color)
            {
                analized_color_pattern_.get()->at(color_index).count++;
                existed = true;
            }

        if(!existed)
            analized_color_pattern_.get()->push_back(comdef::AnalizedColorPattern{cur_color, 1});
    }

    return analized_color_pattern_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::DrawPatternMatrix
/// \brief  Display color pattern matrix
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Maker::DrawPatternMatrix()
{
    QApplication*   app             =   dynamic_cast<QApplication*>(QApplication::instance());
    QMainWindow*    main_window     =   nullptr;

    for(QWidget* widget: app->topLevelWidgets())
        if(widget->inherits(comdef::mainwindow::kClassName.c_str()))
            main_window = dynamic_cast<QMainWindow*>(widget);

    unique_ptr<QVBoxLayout> outter_layout{new QVBoxLayout{main_window->centralWidget()}};

    vector<vector<shared_ptr<QPushButton>>> pattern_hole_matrix = pattern_matrix_->GetHoles();

    for(auto& row: pattern_hole_matrix)
    {
        unique_ptr<QHBoxLayout> row_layout{new QHBoxLayout};

        for(auto& color_btn: row)
            row_layout->addWidget(color_btn.get());

        outter_layout->addLayout(row_layout.get());
    }

    AnalyzeColorPattern();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::DisplayPatternMatrix
/// \brief  Display color pattern matrix
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Maker::DisplayPatternMatrix()
{
    vector<vector<shared_ptr<QPushButton>>> pattern_hole_matrix = pattern_matrix_->GetHoles();

    for(vector<shared_ptr<QPushButton>>& row: pattern_hole_matrix)
        for(shared_ptr<QPushButton>& hole: row)
            hole->setVisible(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::HidePatternMatrix
/// \brief  Hide color pattern matrix
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Maker::HidePatternMatrix()
{
    vector<vector<shared_ptr<QPushButton>>> pattern_hole_matrix = pattern_matrix_->GetHoles();

    for(vector<shared_ptr<QPushButton>>& row: pattern_hole_matrix)
        for(shared_ptr<QPushButton>& hole: row)
            hole->setVisible(false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::DrawKeyMatrix
/// \brief  Display key matrix in Maker area
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Maker::DrawKeyMatrix()
{
    QApplication*   app             =   dynamic_cast<QApplication*>(QApplication::instance());
    QMainWindow*    main_window     =   nullptr;

    for(QWidget* widget: app->topLevelWidgets())
        if(widget->inherits(comdef::mainwindow::kClassName.c_str()))
            main_window = dynamic_cast<QMainWindow*>(widget);

    unique_ptr<QVBoxLayout> outter_layout{new QVBoxLayout{main_window->centralWidget()}};

    vector<vector<shared_ptr<QPushButton>>> key_hole_matrix = key_matrix_->GetHoles();

    for(auto& row: key_hole_matrix)
    {
        unique_ptr<QHBoxLayout> row_layout{new QHBoxLayout};

        for(auto& key_btn: row)
            row_layout->addWidget(key_btn.get());

        outter_layout->addLayout(row_layout.get());
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Maker::SetKeyColor
/// \brief  Set color for push button in key matrix
///
/// \param      row_idx
/// \brief      index of row (corresponding with rows in Breaker area)
///
/// \param      color
/// \brief      color to be set
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Maker::SetKeyColor(uint8_t row_idx, const QColor& color)
{
    QString style_sheet{comdef::color::kBgColorStyleText.arg(color.name())};

    vector<vector<shared_ptr<QPushButton>>> key_hole_matrix = key_matrix_->GetHoles();

    for(auto& key_button: key_hole_matrix[row_idx])
        if(key_button->palette().color(QPalette::Button) == comdef::color::kLight)
        {
            key_button->setStyleSheet(style_sheet);
            break;
        }
}
