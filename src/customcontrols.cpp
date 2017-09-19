#include <QApplication>
#include <mainwindow.h>
#include <QMessageBox>

#include "mastermindgame.h"
#include "decodingboard.h"
#include "breakerareas.h"
#include "holematrix.h"
#include "customcontrols.h"
#include "comdef.h"

CustomControls::CustomControls() {}

CustomControls::~CustomControls() {}

unique_ptr<QPushButton> CustomControls::CreatePushButton(QRect rect,
                                                         QColor color,
                                                         QString text,
                                                         void (QAbstractButton::*event)(bool),
                                                         CustomControls* receiver,
                                                         void (CustomControls::*handler)())
{
    unique_ptr<QPushButton> btn(new QPushButton(text));

    QString style_sheet = QString(comdef::color::kBgColorStyleRgb).arg(color.red())
                                                                  .arg(color.green())
                                                                  .arg(color.blue());

    btn->setStyleSheet(style_sheet);

    btn->resize(rect.width(), rect.height());
    btn->move(rect.x(), rect.y());

    if(event != nullptr)
        connect(btn.get(), event, receiver, handler);

    return move(btn);

}

unique_ptr<QComboBox> CustomControls::CreateComboBox(QRect rect,
                                                     map<QString, QColor> item_list,
                                                     void(QComboBox::* /* event - reserved */)(),
                                                     CustomControls* /* receiver - reserved */,
                                                     void (CustomControls::* /* handler - reserved */)())

{
    unique_ptr<QComboBox> comboBox(new QComboBox);

    comboBox->move(rect.x(), rect.y());
    comboBox->resize(rect.width(), rect.height());

    for(auto& item: item_list)
        comboBox->addItem(item.first, item.second);

    comboBox->setCurrentIndex(0);

    return move(comboBox);

}

void CustomControls::SetQPushButtonColor()
{
    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    QComboBox* combobox = nullptr;
    QPushButton* push_button = static_cast<QPushButton*>(QObject::sender());

    foreach(QWidget *widget, app->allWidgets()) {
        if(widget->inherits("QComboBox"))
        {
            combobox = static_cast<QComboBox*>(widget);
        }
    }

    if(push_button->width() == comdef::decodingboard::pushbutton::kLargeWidth &&
       combobox->currentText().indexOf(comdef::color::kBlackStr.split('-')[1]) == -1 &&
       combobox->currentText().indexOf(comdef::color::kWhiteStr.split('-')[1]) == -1)
    {
        QString style = QString(comdef::color::kBgColorStyleText).arg(combobox->currentData().toString());
        push_button->setStyleSheet(style);
    }

    MainWindow* main_window = nullptr;

    foreach(QWidget *widget, app->topLevelWidgets()) {
        if(widget->inherits("QMainWindow"))
        {
            main_window = static_cast<MainWindow*>(widget);
        }
    }

    shared_ptr<MasterMindGame> master_mind_game = main_window->GetMasterMindGame();

    shared_ptr<HoleMatrix> breaker_large_holes_matrix = master_mind_game->GetDecodingBoard()->GetBreakerAreas()->GetLargeHolesMatrix();

    if(breaker_large_holes_matrix->IsFulfilledRow() == true)
        master_mind_game->CheckResult();
}
