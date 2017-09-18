#include <QApplication>

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

    connect(btn.get(), event, receiver, handler);

    return move(btn);

}

unique_ptr<QComboBox> CustomControls::CreateComboBox(QRect rect,
                                                     map<QString, QColor> item_list,
                                                     void(QComboBox::* /* event - unused */)(),
                                                     CustomControls* /* receiver - unused */,
                                                     void (CustomControls::* /* handler - unused */)())

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

    QString style = QString(comdef::color::kBgColorStyleText).arg(combobox->currentText());
    push_button->setStyleSheet(style);
}
