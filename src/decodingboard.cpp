//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      decodingboard.cpp
/// \brief     Implementation of Decoding board
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
#include <QBoxLayout>
#include <QComboBox>

#include "decodingboard.h"
#include "comdef.h"
#include "breaker.h"
#include "maker.h"
#include "holematrix.h"
#include "customcontrols.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn         DecodingBoard::DecodingBoard
/// \brief      Default constructor
///             - Init data member (allocate memory and set default values)
///
/// \return     none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DecodingBoard::DecodingBoard(): breaker_{new Breaker},
                                maker_{new Maker}
{}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     DecodingBoard::~DecodingBoard
/// \brief  Destructor
///         - Cleanup activities (Do nothing right now, shared_ptr variable will be destroyed automatically)
///
/// \param  none
///
/// \return none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DecodingBoard::~DecodingBoard(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     DecodingBoard::GetBreaker
/// \brief  Get breaker
///
/// \param  none
///
/// \return const shared_ptr<Breaker>&
/// \brief  breaker
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const shared_ptr<Breaker>& DecodingBoard::GetBreaker(){ return breaker_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     DecodingBoard::GetMaker
/// \brief  Get maker
///
/// \param  none
///
/// \return const shared_ptr<Maker>&
/// \brief  maker
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const shared_ptr<Maker>& DecodingBoard::GetMaker() { return maker_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     DecodingBoard::GetColorComboxBox
/// \brief  Get color combobox
///
/// \param  none
///
/// \return const shared_ptr<QComboBox>&
/// \brief  color combobox
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const shared_ptr<QComboBox>& DecodingBoard::GetColorComboxBox() { return color_combobox_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     DecodingBoard::GetDisplayPatternCheckBox
/// \brief  Get display pattern checkbox
///
/// \param  none
///
/// \return const shared_ptr<QCheckBox>&
/// \brief  display pattern checkbox
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const shared_ptr<QCheckBox>& DecodingBoard::GetDisplayPatternCheckBox() { return display_pattern_checkbox_; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     DecodingBoard::Draw
/// \brief  Draw all of areas in the decoding board
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DecodingBoard::Draw()
{
    breaker_->GetHolesMatrix()->DrawHolesMatrix();

    maker_->DrawKeyMatrix();

    maker_->DrawPatternMatrix();

    maker_->HidePatternMatrix();

    DrawColorCombo();

    DrawCheckbox();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     DecodingBoard::DrawColorCombo
/// \brief  Draw combobox
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    color_combobox_ = CustomControls::CreateComboBox(comdef::decodingboard::combobox::kInitRect,
                                               item_list,
                                               nullptr,
                                               nullptr,
                                               nullptr);

    outter_layout->addWidget(color_combobox_.get());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     DecodingBoard::DrawCheckBox
/// \brief  Draw checkbox
///
/// \param  none
///
/// \return void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DecodingBoard::DrawCheckbox()
{
    QApplication*   app             =   dynamic_cast<QApplication*>(QApplication::instance());
    QMainWindow*    main_window     =   nullptr;

    for(QWidget* widget: app->topLevelWidgets())
        if(widget->inherits(comdef::mainwindow::kClassName.c_str()))
            main_window = dynamic_cast<QMainWindow*>(widget);

    unique_ptr<QVBoxLayout> outter_layout{new QVBoxLayout{main_window->centralWidget()}};

    display_pattern_checkbox_ = CustomControls::CreateCheckBox(comdef::decodingboard::checkbox::kInitRect,
                                                               comdef::decodingboard::checkbox::kDisplayColorPattern,
                                                               &QCheckBox::clicked,
                                                               new CustomControls(),
                                                               &CustomControls::DisplayColorPattern);

    outter_layout->addWidget(display_pattern_checkbox_.get());
}
