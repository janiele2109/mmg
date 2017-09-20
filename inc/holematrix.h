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
        HoleMatrix(uint8_t num_of_rows            = comdef::makerarea::kDefNumOfRows,
                   uint8_t num_of_holes_per_row   = comdef::makerarea::kDefNumOfHolesPerRow);

        ~HoleMatrix();

        uint8_t GetNumOfRows();
        uint8_t GetNumOfHolesPerRow();
        uint8_t GetLastEnabledRow();

        const vector<vector<shared_ptr<QPushButton>>>& GetHoles();

        void InitHolesMatrix(QRect            rect                      = comdef::decodingboard::pushbutton::kInitLargeRect,
                             const QColor&    color                     = comdef::color::kGrey,
                             const QString&   text                      = comdef::kEmptyString,
                             const int        row_break_index           = comdef::decodingboard::kDefRowBreakIndex,
                             void (QAbstractButton::* event)(bool)      = nullptr,
                             const CustomControls* receiver              = nullptr,
                             void (CustomControls::* handler)()         = nullptr);

        void DisableCurrentRow();
        void EnableNewRow();
        bool IsCurrentRowFilled();

        void DrawHolesMatrix();

    protected:

    private:
        uint8_t num_of_rows_;
        uint8_t num_of_holes_per_row_;
        int     last_enabled_row_;

        vector<vector<shared_ptr<QPushButton>>> holes_;
};

#endif // HOLEMATRIX_H
