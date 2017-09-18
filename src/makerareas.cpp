#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGridLayout>

#include "makerareas.h"
#include "holematrix.h"

MakerAreas::MakerAreas(uint8_t num_of_rows,
                       uint8_t num_of_large_holes_per_row): large_holes_row_(new HoleMatrix(num_of_rows,
                                                                                          num_of_large_holes_per_row)),
                                                            small_holes_matrix_(new HoleMatrix(comdef::breakerarea::kDefNumOfRows,
                                                                                             comdef::breakerarea::kDefNumOfLargeHolesPerRow))
{
    InitSmallHolesMatrix();
}

MakerAreas::~MakerAreas(){}

shared_ptr<HoleMatrix> MakerAreas::GetLargeHolesRow(){ return large_holes_row_; }

shared_ptr<HoleMatrix> MakerAreas::GetSmallHolesMatrix(){ return small_holes_matrix_; }

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

    GetSmallHolesMatrix()->InitHolesMatrix(small_rect,
                                           comdef::color::kGrey,
                                           comdef::kEmptyString,
                                           2,
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

    vector<vector<shared_ptr<QPushButton>>> small_holes_matrix = GetSmallHolesMatrix()->GetHoles();

    for(auto row: small_holes_matrix)
    {
        unique_ptr<QGridLayout> row_layout(new QGridLayout);

        for(shared_ptr<QPushButton> pushButton: row)
            row_layout->addWidget(pushButton.get());

        outter_layout->addLayout(row_layout.get());
     }
}
