#ifndef HOLEMATRIX_H
#define HOLEMATRIX_H

#include <cstdint>
#include <vector>
#include <memory>

#include <QPushButton>

#include "comdef.h"
#include "customcontrols.h"

using namespace std;

class HoleMatrix: public CustomControls
{
    public:
        HoleMatrix(uint8_t num_of_rows                  = comdef::makerarea::kDefNumOfRows,
                   uint8_t num_of_large_holes_per_row   = comdef::makerarea::kDefNumOfLargeHolesPerRow);

        ~HoleMatrix();

        uint8_t getNumOfRows();
        uint8_t GetHolesPerRow();

        vector< vector<shared_ptr<QPushButton>> >& GetHoles();

        void InitHolesMatrix(QRect      init_rect                   = comdef::decodingboard::pushbutton::kInitLargeRect,
                             QColor     color                       = comdef::color::kGrey,
                             QString    title                       = comdef::kEmptyString,
                             uint8_t    breakdow_index              = 0,
                             void (QAbstractButton::*event)(bool)   = nullptr,
                             CustomControls* receiver               = nullptr,
                             void (CustomControls::*handler)()      = nullptr);
    protected:

    private:
        uint8_t num_of_rows_;
        uint8_t holes_per_row_;

        vector< vector<shared_ptr<QPushButton>> > holes_;
};

#endif // HOLEMATRIX_H
