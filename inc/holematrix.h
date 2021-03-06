//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      holematrix.h
/// \brief     All declarations and definition for Hole Matrix
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

#ifndef HOLEMATRIX_H
#define HOLEMATRIX_H

#include <cstdint>
#include <vector>
#include <memory>

#include <QPushButton>

#include "comdef.h"
#include "customcontrols.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \class      HoleMatrix
/// \brief      Abstract object which is responsible for holes used in decoding board
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                             const CustomControls* receiver             = nullptr,
                             void (CustomControls::* handler)()         = nullptr,
                             bool enable_status                         = false);

        void DisableCurrentRow();
        void EnableNewRow();
        bool IsCurrentRowFilled();

        void DrawHolesMatrix();

    protected:

    private:
        /// number of rows in the matrix
        uint8_t num_of_rows_;

        /// number of holes per row in the matrix
        uint8_t num_of_holes_per_row_;

        /// index of last enabled row in the breaker area
        int     last_enabled_row_;

        /// holes matrix
        vector<vector<shared_ptr<QPushButton>>> holes_;
};

#endif // HOLEMATRIX_H
