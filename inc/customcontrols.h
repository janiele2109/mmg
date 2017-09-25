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

        static unique_ptr<QPushButton> CreatePushButton(const QRect& rect,
                                                        const QColor& color,
                                                        const QString& text,
                                                        void (QAbstractButton::* event)(bool),
                                                        const CustomControls* receiver,
                                                        void (CustomControls::* handler)(),
                                                        bool enable_status);

        static unique_ptr<QComboBox> CreateComboBox(const QRect& rect,
                                                    const map<QString, QColor>& item_list,
                                                    void(QComboBox::*)(int index),
                                                    const CustomControls* receiver,
                                                    void (CustomControls::* handler)(int index));

    public slots:
        void SetQPushButtonColor();

    private:

};

#endif // CUSTOMCONTROLS_H
