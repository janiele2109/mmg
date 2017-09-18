#ifndef CUSTOMCONTROLS_H
#define CUSTOMCONTROLS_H

#include <memory>

#include <QPushButton>
#include <QComboBox>
#include <QRect>
#include <QColor>
#include <QObject>

using namespace std;

class CustomControls: public QObject
{
    Q_OBJECT

    public:
        CustomControls();
        ~CustomControls();

        static unique_ptr<QPushButton> CreatePushButton(QRect rect,
                                                        QColor color,
                                                        QString text,
                                                        void (QAbstractButton::*event)(bool),
                                                        CustomControls* receiver,
                                                        void (CustomControls::*handler)());

        static unique_ptr<QComboBox> CreateComboBox(QRect rect,
                                                    map<QString, QColor> item_list,
                                                    void(QComboBox::*event)(),
                                                    CustomControls* receiver,
                                                    void (CustomControls::*handler)());

    public slots:
        void SetQPushButtonColor();

    private:

};

#endif // CUSTOMCONTROLS_H
