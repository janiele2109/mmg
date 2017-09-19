#ifndef MAKERAREAS_H
#define MAKERAREAS_H

#include <cstdint>
#include <memory>

#include <QColor>

#include "comdef.h"


using namespace std;


class HoleMatrix;


class MakerAreas
{
    public:
        MakerAreas(uint8_t num_of_rows                  = comdef::makerarea::kDefNumOfRows,
                   uint8_t num_of_large_holes_per_row   = comdef::makerarea::kDefNumOfLargeHolesPerRow);

        ~MakerAreas();

        vector<QColor> GetEncodedColorList();
        shared_ptr<HoleMatrix> GetEncodedColorHolesMatrix();
        shared_ptr<HoleMatrix> GetSmallHolesMatrix();

        void InitEncodedColorRow();
        void InitSmallHolesMatrix();
        void InitEncodedHolesMatrix();

        void DrawEncodedColorRow();
        void DrawSmallHolesMatrix();

        void SetKeyPeg(uint8_t row_idx, QColor color);

    protected:

    private:
        vector<QColor> encoded_color_list_;
        shared_ptr<HoleMatrix> encoded_color_holes_matrix_;
        shared_ptr<HoleMatrix> small_holes_matrix_;
};

#endif // MAKERAREAS_H
