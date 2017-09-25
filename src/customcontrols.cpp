#include <QApplication>

#include "customcontrols.h"
#include "comdef.h"
#include "mainwindow.h"
#include "mastermindgame.h"
#include "decodingboard.h"
#include "breaker.h"
#include "holematrix.h"

CustomControls::CustomControls() {}

CustomControls::~CustomControls() {}

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
