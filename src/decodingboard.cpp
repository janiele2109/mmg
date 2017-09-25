#include <QApplication>
#include <QMainWindow>
#include <QBoxLayout>
#include <QComboBox>

#include "decodingboard.h"
#include "comdef.h"
#include "breaker.h"
#include "maker.h"
#include "holematrix.h"
#include "customcontrols.h"

DecodingBoard::DecodingBoard(): breaker_areas_{new Breaker},
                                maker_areas_{new MakerAreas}
{}

DecodingBoard::~DecodingBoard(){}

const shared_ptr<Breaker>& DecodingBoard::GetBreaker(){ return breaker_areas_; }

const shared_ptr<MakerAreas>& DecodingBoard::GetMaker() { return maker_areas_; }

void DecodingBoard::Draw()
{
    breaker_areas_->GetHolesMatrix()->DrawHolesMatrix();

    maker_areas_->DrawKeyMatrix();

    maker_areas_->DrawPatternMatrix();

    DrawColorCombo();
}

void DecodingBoard::DrawColorCombo()
{
    QApplication*   app             =   dynamic_cast<QApplication*>(QApplication::instance());
    QMainWindow*    main_window     =   nullptr;

    for(QWidget* widget: app->topLevelWidgets())
        if(widget->inherits(comdef::mainwindow::kClassName.c_str()))
            main_window = dynamic_cast<QMainWindow*>(widget);

    unique_ptr<QVBoxLayout> outter_layout{new QVBoxLayout{main_window->centralWidget()}};

    map<QString, QColor> item_list{{comdef::color::kRedStr,         comdef::color::kRed},
                                   {comdef::color::kGreenStr,       comdef::color::kGreen},
                                   {comdef::color::kBlueStr,        comdef::color::kBlue},
                                   {comdef::color::kYellowStr,      comdef::color::kYellow},
                                   {comdef::color::kLightStr,       comdef::color::kLight},
                                   {comdef::color::kLightGreenStr,  comdef::color::kLightGreen},
                                   {comdef::color::kBrownStr,       comdef::color::kBrown}};

    combobox_ = CustomControls::CreateComboBox(comdef::decodingboard::combobox::kInitRect,
                                               item_list,
                                               nullptr,
                                               nullptr,
                                               nullptr);

    outter_layout->addWidget(combobox_.get());
}
