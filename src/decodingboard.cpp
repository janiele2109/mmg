#include <QApplication>
#include <QMainWindow>
#include <QBoxLayout>
#include <QComboBox>

#include "decodingboard.h"
#include "comdef.h"
#include "breakerareas.h"
#include "makerareas.h"
#include "customcontrols.h"

DecodingBoard::DecodingBoard(): breaker_areas_(new BreakerAreas),
                                maker_areas_(new MakerAreas)
{}

DecodingBoard::~DecodingBoard(){}

shared_ptr<BreakerAreas> DecodingBoard::GetBreakerAreas(){ return breaker_areas_; }

shared_ptr<MakerAreas> DecodingBoard::GetMakerAreas() { return maker_areas_; }

void DecodingBoard::Draw()
{
    GetBreakerAreas()->DrawLargeHolesMatrix();

    GetMakerAreas()->DrawSmallHolesMatrix();

    DrawColorCombo();
}

void DecodingBoard::DrawColorCombo()
{
    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    QMainWindow* main_window = nullptr;

    foreach(QWidget *widget, app->topLevelWidgets()) {
        if(widget->inherits("QMainWindow"))
        {
            main_window = dynamic_cast<QMainWindow*>(widget);
        }
    }

    unique_ptr<QVBoxLayout> outter_layout(new QVBoxLayout(main_window->centralWidget()));

    map<QString, QColor> item_list{{comdef::color::kRedStr,     comdef::color::kRed},
                                   {comdef::color::kGreenStr,   comdef::color::kGreen},
                                   {comdef::color::kBlueStr,    comdef::color::kBlue},
                                   {comdef::color::kWhiteStr,   comdef::color::kWhite},
                                   {comdef::color::kBlackStr,   comdef::color::kBlack},
                                   {comdef::color::kGreyStr,    comdef::color::kGrey},
                                   {comdef::color::kYellowStr,  comdef::color::kYellow}};

    unique_ptr<QComboBox> combobox = CustomControls::CreateComboBox(comdef::decodingboard::combobox::kInitRect,
                                                                    item_list,
                                                                    nullptr,
                                                                    nullptr,
                                                                    nullptr);

    outter_layout->addWidget(combobox.release());
}
