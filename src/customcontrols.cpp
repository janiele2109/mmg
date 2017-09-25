//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      customcontrols.cpp
/// \brief     Implementation of Custom Controls lib
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

#include "customcontrols.h"
#include "comdef.h"
#include "mainwindow.h"
#include "mastermindgame.h"
#include "decodingboard.h"
#include "breaker.h"
#include "holematrix.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     CustomControls::CustomControls
/// \brief  Default constructor
///
/// \param  none
///
/// \return none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CustomControls::CustomControls() {}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     CustomControls::~CustomControls
/// \brief  Destructor
///         - Cleanup activities (Do nothing right now)
///
/// \param  none
///
/// \return none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CustomControls::~CustomControls() {}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn         CustomControls::CreatePushButton
/// \brief      Create QT push button
///
/// \param      rect
/// \brief      default size and location of push button which will be created
///
/// \param      color
/// \brief      default color of disable push button
/// \default    comdef::color::kLight
///
/// \param      text
/// \brief      default text of push button (label)
/// \default    comdef::kEmptyString
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
/// \param      enable_status
/// \brief      enable status of push button
/// \default    nullptr
///
/// \return     unique_ptr<QPushButton>
/// \brief      newly created push button
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unique_ptr<QPushButton> CustomControls::CreatePushButton(const QRect& rect,
                                                         const QColor& color,
                                                         const QString& text,
                                                         void (QAbstractButton::* event)(bool),
                                                         const CustomControls* receiver,
                                                         void (CustomControls::* handler)(),
                                                         bool enable_status)

{
    unique_ptr<QPushButton> btn{new QPushButton{text}};

    QString style_sheet{comdef::color::kBgColorStyleText.arg(color.name())};

    btn->setStyleSheet(style_sheet);

    btn->resize(rect.width(), rect.height());

    btn->move(rect.x(), rect.y());

    if(event != nullptr)
        connect(btn.get(), event, receiver, handler);

    if(!enable_status)
        btn->setEnabled(false);

    return btn;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn         CustomControls::CreateComboBox
/// \brief      Create QT combobox
///
/// \param      rect
/// \brief      default size and location of combobox which will be created
///
/// \param      item_list
/// \brief      default items in the combobox with corresponding data
///
/// \param      event
/// \brief      triggered event from push button which would be handled - reserved
/// \default    nullptr
///
/// \param      receiver
/// \brief      object which would handle triggered event - reserved
/// \default    nullptr
///
/// \param      handler
/// \brief      handler function for the triggered event - reserved
/// \default    nullptr
///
/// \return     unique_ptr<QComboBox>
/// \brief      newly created combobox
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unique_ptr<QComboBox> CustomControls::CreateComboBox(const QRect& rect,
                                                     const map<QString, QColor>& item_list,
                                                     void(QComboBox::* /* event - reserved */)(int index),
                                                     const CustomControls* /* receiver - reserved */,
                                                     void (CustomControls::* /* handler - reserved */)(int index))

{
    unique_ptr<QComboBox> comboBox{new QComboBox};

    comboBox->resize(rect.width(), rect.height());

    comboBox->move(rect.x(), rect.y());

    for(auto& item: item_list)
        comboBox->addItem(item.first, item.second);

    comboBox->setCurrentIndex(comdef::decodingboard::combobox::kInitCurrentIndex);

    return comboBox;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn         CustomControls::SetQPushButtonColor
/// \brief      Handler function for triggered event (clicked), used to set color for push button
///
/// \param      none
///
/// \return     void
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CustomControls::SetQPushButtonColor()
{    
    QApplication*   app             =   dynamic_cast<QApplication*>(QApplication::instance());
    QPushButton*    push_button     =   dynamic_cast<QPushButton*>(QObject::sender());
    MainWindow*     main_window     =   nullptr;
    QComboBox*      combobox        =   nullptr;
    HoleMatrix*     holes_matrix    =   nullptr;

    MasterMindGame* master_mind_game = nullptr;

    QString         style_sheet;

    for(QWidget* widget: app->allWidgets())
        if(widget->inherits(comdef::decodingboard::combobox::kClassName.c_str()))
            combobox = dynamic_cast<QComboBox*>(widget);

    style_sheet = comdef::color::kBgColorStyleText.arg(combobox->itemData(combobox->currentIndex()).toString());

    push_button->setStyleSheet(style_sheet);

    for(QWidget* widget: app->topLevelWidgets())
        if(widget->inherits(comdef::mainwindow::kClassName.c_str()))
            main_window = dynamic_cast<MainWindow*>(widget);

    master_mind_game = main_window->GetMasterMindGame().get();

    holes_matrix = master_mind_game->GetDecodingBoard()
                                   ->GetBreaker()
                                   ->GetHolesMatrix().get();

    if(holes_matrix->IsCurrentRowFilled())
        master_mind_game->CheckResult();
}
