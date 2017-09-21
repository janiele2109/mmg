#include <random>

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGridLayout>

#include "comdef.h"
#include "maker.h"
#include "holematrix.h"

MakerAreas::MakerAreas(): pattern_matrix_(new HoleMatrix(comdef::makerarea::kDefNumOfRows,
                                                         comdef::makerarea::kDefNumOfHolesPerRow)),
                          key_matrix_(new HoleMatrix(comdef::breakerarea::kDefNumOfRows,
                                                     comdef::breakerarea::kDefNumOfHolesPerRow))
{
    InitPatternMatrix();

    InitKeyMatrix();
}

MakerAreas::~MakerAreas(){}

shared_ptr<HoleMatrix> MakerAreas::GetPatternMatrix(){ return pattern_matrix_; }

shared_ptr<HoleMatrix> MakerAreas::GetKeyMatrix(){ return key_matrix_; }

void MakerAreas::InitPatternMatrix()
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
                                     &CustomControls::SetQPushButtonColor);

    uint8_t num_of_holes = pattern_matrix_->GetNumOfHolesPerRow();
    uint8_t cur_pattern_row = pattern_matrix_->GetNumOfRows() - 1;

    for(uint8_t cur_hole = 0; cur_hole < num_of_holes; cur_hole++)
    {
        int index_rand_val = uniform_dist(rand_en);

        QString style_sheet{comdef::color::kBgColorStyleText.arg(color[index_rand_val].name())};

        pattern_matrix_->GetHoles()[cur_pattern_row][cur_hole]->setStyleSheet(style_sheet);
    }
}

void MakerAreas::InitKeyMatrix()
{
    QRect rect(comdef::decodingboard::pushbutton::kInitSmallRect);

    uint16_t init_x = comdef::decodingboard::pushbutton::kInitX;
    uint16_t width_rect = comdef::decodingboard::pushbutton::kInitLargeRect.width();
    uint16_t padding = comdef::decodingboard::pushbutton::kLargePadding;
    uint8_t  num_of_code_holes_per_row = pattern_matrix_->GetNumOfHolesPerRow();

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
                                 &CustomControls::SetQPushButtonColor);
}

void MakerAreas::DrawPatternMatrix()
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
}

void MakerAreas::DrawKeyMatrix()
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

void MakerAreas::SetKeyColor(uint8_t row_idx, const QColor& color)
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
