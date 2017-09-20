#ifndef MAKER_H
#define MAKER_H

#include <cstdint>
#include <memory>

#include <QColor>

#include "comdef.h"

using namespace std;

class HoleMatrix;

class MakerAreas
{
    public:
        MakerAreas();

        ~MakerAreas();

        shared_ptr<HoleMatrix>  GetPatternMatrix();
        shared_ptr<HoleMatrix>  GetKeyMatrix();

        void InitPatternMatrix();
        void InitKeyMatrix();

        void DrawPatternMatrix();
        void DrawKeyMatrix();

        void SetKeyColor(uint8_t row_idx, const QColor& color);

    protected:

    private:
        shared_ptr<HoleMatrix>  pattern_matrix_;
        shared_ptr<HoleMatrix>  key_matrix_;
};

#endif // MAKER_H
