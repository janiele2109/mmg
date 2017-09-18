#ifndef MAKERAREAS_H
#define MAKERAREAS_H

#include <cstdint>
#include <memory>

#include "comdef.h"


using namespace std;


class HoleMatrix;


class MakerAreas
{
    public:
        MakerAreas(uint8_t num_of_rows                  = comdef::makerarea::kDefNumOfRows,
                   uint8_t num_of_large_holes_per_row   = comdef::makerarea::kDefNumOfLargeHolesPerRow);

        ~MakerAreas();

        shared_ptr<HoleMatrix> GetLargeHolesRow();
        shared_ptr<HoleMatrix> GetSmallHolesMatrix();

        void InitSmallHolesMatrix();
        void DrawSmallHolesMatrix();

    protected:

    private:
        shared_ptr<HoleMatrix> large_holes_row_;
        shared_ptr<HoleMatrix> small_holes_matrix_;
};

#endif // MAKERAREAS_H
