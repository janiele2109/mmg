//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      customcontrols.h
/// \brief     All declarations and definition for Custom Controls lib
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

#ifndef CUSTOMCONTROLS_H
#define CUSTOMCONTROLS_H

#include <memory>

#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRect>
#include <QColor>
#include <QObject>

#include "comdef.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \class      CustomControls
/// \brief      Abstract object which is responsible for creating custom controls
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CustomControls: public QObject
{
    Q_OBJECT

    public:
        CustomControls();
        ~CustomControls();

        static unique_ptr<QPushButton> CreatePushButton(const QRect& rect,
                                                        const QColor& color = comdef::color::kLight,
                                                        const QString& text = comdef::kEmptyString,
                                                        void (QAbstractButton::* event)(bool) = nullptr,
                                                        const CustomControls* receiver = nullptr,
                                                        void (CustomControls::* handler)() = nullptr,
                                                        bool enable_status = false);

        static unique_ptr<QComboBox> CreateComboBox(const QRect& rect,
                                                    const map<QString, QColor>& item_list,
                                                    void(QComboBox::* event)(int index),
                                                    const CustomControls* receiver,
                                                    void (CustomControls::* handler)(int index));

        static unique_ptr<QCheckBox> CreateCheckBox(const QRect& rect,
                                                    const QString& text = comdef::kEmptyString,
                                                    void (QCheckBox::* event)(bool checked) = nullptr,
                                                    const CustomControls* receiver = nullptr,
                                                    void (CustomControls::* handler)(bool checked) = nullptr);

    public slots:
        void SetQPushButtonColor();
        void DisplayColorPattern(bool checked = true);

    private:

};

#endif // CUSTOMCONTROLS_H
