#include "AnimManager.h"

namespace anim
{

    namespace Hangman
    {
        struct Data
        {
            int gallow;
            int divider;

        };
        
        void init_data(void* p, int gallow = 8);
        
        void reset(void* p);

        void advance_gallow(void* p);

        void play(void* p);
    }

}