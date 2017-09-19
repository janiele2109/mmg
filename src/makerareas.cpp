#include <random>

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGridLayout>

#include "comdef.h"
#include "makerareas.h"
#include "holematrix.h"

MakerAreas::MakerAreas(uint8_t /* num_of_rows = reserved */,
                       uint8_t /* num_of_large_holes_per_row = reserved */): encoded_color_holes_matrix_(new HoleMatrix(comdef::makerarea::kDefNumOfRows,
                                                                                                                        comdef::makerarea::kDefNumOfLargeHolesPerRow)),
                                                                             small_holes_matrix_(new HoleMatrix(comdef::breakerarea::kDefNumOfRows,
                                                                                                                comdef::breakerarea::kDefNumOfLargeHolesPerRow))
{
    InitSmallHolesMatrix();

    InitEncodedColorRow();

    InitEncodedHolesMatrix();

    small_holes_matrix_->DisableAllPushButtons();

    encoded_color_holes_matrix_->DisableAllPushButtons();
}

MakerAreas::~MakerAreas(){}

vector<QColor> MakerAreas::GetEncodedColorList(){ return encoded_color_list_; }

shared_ptr<HoleMatrix> MakerAreas::GetEncodedColorHolesMatrix(){ return encoded_color_holes_matrix_; }

shared_ptr<HoleMatrix> MakerAreas::GetSmallHolesMatrix(){ return small_holes_matrix_; }

void MakerAreas::InitEncodedColorRow()
{
    random_device rand_dev;

    default_random_engine rand_en(rand_dev());

    uniform_int_distribution<int> uniform_dist(0, 5);

    vector<QColor> color{ comdef::color::kGreen,
                          comdef::color::kBlue,
                          comdef::color::kYellow,
                          comdef::color::kLightGreen,
                          comdef::color::kBrown,
                          comdef::color::kRed
                        };

    uint8_t num_of_holes = small_holes_matrix_->GetHolesPerRow();

    for(uint8_t i = 0; i < num_of_holes; i++)
    {
        int index_rand_val = uniform_dist(rand_en);

        encoded_color_list_.push_back(color.at(index_rand_val));
    }
}

void MakerAreas::InitSmallHolesMatrix()
{
    QRect small_rect(comdef::decodingboard::pushbutton::kInitSmallRect);

    uint16_t init_x = comdef::decodingboard::pushbutton::kInitX;
    uint16_t width_rect = comdef::decodingboard::pushbutton::kInitLargeRect.width();
    uint16_t padding = comdef::decodingboard::pushbutton::kLargePadding;
    uint16_t num_of_large_holes_per_row = GetSmallHolesMatrix()->GetHolesPerRow();

    uint16_t new_x = init_x +
                     num_of_large_holes_per_row * width_rect +
                     (num_of_large_holes_per_row - 1) * padding +
                     padding;

    small_rect.moveTo(new_x, small_rect.y());

    small_holes_matrix_->InitHolesMatrix(small_rect,
                                         comdef::color::kLight,
                                         comdef::kEmptyString,
                                         2,
                                         &QPushButton::clicked,
                                         new CustomControls(),
                                         &CustomControls::SetQPushButtonColor);
}

void MakerAreas::InitEncodedHolesMatrix()
{
    QRect large_rect(comdef::decodingboard::pushbutton::kInitLargeRect);

    uint16_t new_y = comdef::decodingboard::combobox::kInitRect.y() -
                     comdef::decodingboard::pushbutton::kLargeHeight -
                     comdef::decodingboard::pushbutton::kLargePadding -
                     comdef::decodingboard::pushbutton::kSmallPadding;

    large_rect.moveTo(large_rect.x(), new_y);

    encoded_color_holes_matrix_->InitHolesMatrix(large_rect,
                                                 comdef::color::kGreen,
                                                 comdef::kEmptyString,
                                                 0,
                                                 &QPushButton::clicked,
                                                 new CustomControls(),
                                                 &CustomControls::SetQPushButtonColor);
}

void MakerAreas::DrawSmallHolesMatrix()
{
    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    QMainWindow* main_window = nullptr;

    foreach(QWidget *widget, app->topLevelWidgets()) {
        if(widget->inherits("QMainWindow"))
        {
            main_window = static_cast<QMainWindow*>(widget);
        }
    }

    unique_ptr<QVBoxLayout> outter_layout(new QVBoxLayout(main_window->centralWidget()));

    vector<vector<shared_ptr<QPushButton>>> small_holes_matrix = small_holes_matrix_->GetHoles();

    for(auto row: small_holes_matrix)
    {
        unique_ptr<QGridLayout> row_layout(new QGridLayout);

        for(shared_ptr<QPushButton> pushButton: row)
            row_layout->addWidget(pushButton.get());

        outter_layout->addLayout(row_layout.get());
     }
}

void MakerAreas::DrawEncodedColorRow()
{
    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    QMainWindow* main_window = nullptr;

    foreach(QWidget *widget, app->topLevelWidgets()) {
        if(widget->inherits("QMainWindow"))
        {
            main_window = static_cast<QMainWindow*>(widget);
        }
    }

    unique_ptr<QVBoxLayout> outter_layout(new QVBoxLayout(main_window->centralWidget()));

    vector<vector<shared_ptr<QPushButton>>> large_holes_matrix = encoded_color_holes_matrix_->GetHoles();

    uint8_t color_idx = 0;

    for(auto row: large_holes_matrix)
    {
        unique_ptr<QHBoxLayout> row_layout(new QHBoxLayout);

        for(shared_ptr<QPushButton> push_button: row)
        {
            QString style = QString("%1%2").arg(comdef::color::kBgColorStyleText).arg("#").arg(encoded_color_list_.at(color_idx).rgba(), 8, 16);
            push_button->setStyleSheet(style);

            row_layout->addWidget(push_button.get());

            color_idx++;
        }

        outter_layout->addLayout(row_layout.get());
    }
}

void MakerAreas::SetKeyPeg(uint8_t row_idx, QColor color)
{
    QString style = QString("%1%2").arg(comdef::color::kBgColorStyleText).arg("#").arg(color.rgba(), 8, 16);

    for(auto small_button: small_holes_matrix_->GetHoles().at(row_idx))
        if(small_button->palette().color(QPalette::Button) == comdef::color::kLight)
        {
            small_button->setStyleSheet(style);
            return;
        }
}
