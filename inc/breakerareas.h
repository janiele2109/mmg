#ifndef BREAKERAREAS_H
#define BREAKERAREAS_H

#include <cstdint>
#include <memory>

#include "comdef.h"


using namespace std;


class HoleMatrix;


class BreakerAreas
{
    public:
        BreakerAreas(uint8_t num_of_rows                  = comdef::breakerarea::kDefNumOfRows,
                     uint8_t num_of_large_holes_per_row   = comdef::breakerarea::kDefNumOfLargeHolesPerRow);

        ~BreakerAreas();

        shared_ptr<HoleMatrix> GetLargeHolesMatrix();

        void InitLargeHolesMatrix();
        void DrawLargeHolesMatrix();


    protected:
    private:
        shared_ptr<HoleMatrix> large_holes_matrix_;
};

#endif // BREAKERAREAS_H
