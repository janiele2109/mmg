#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>

#include "breakerareas.h"
#include "holematrix.h"

BreakerAreas::BreakerAreas(uint8_t num_of_rows,
                           uint8_t num_of_large_holes_per_row):large_holes_matrix_(new HoleMatrix(num_of_rows,
                                                                                                num_of_large_holes_per_row))
{
    InitLargeHolesMatrix();
}

BreakerAreas::~BreakerAreas(){}

shared_ptr<HoleMatrix> BreakerAreas::GetLargeHolesMatrix(){ return large_holes_matrix_; }

void BreakerAreas::InitLargeHolesMatrix()
{
    GetLargeHolesMatrix()->InitHolesMatrix(comdef::decodingboard::pushbutton::kInitLargeRect,
                                           comdef::color::kGrey,
                                           comdef::kEmptyString,
                                           0,
                                           &QPushButton::clicked,
                                           new CustomControls(),
                                           &CustomControls::SetQPushButtonColor);
}

void BreakerAreas::DrawLargeHolesMatrix()
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

    vector<vector<shared_ptr<QPushButton>>> large_holes_matrix = GetLargeHolesMatrix()->GetHoles();

    for(auto row: large_holes_matrix)
    {
        unique_ptr<QHBoxLayout> row_layout(new QHBoxLayout);

        for(shared_ptr<QPushButton> push_button: row)
            row_layout->addWidget(push_button.get());

        outter_layout->addLayout(row_layout.get());
    }
}
