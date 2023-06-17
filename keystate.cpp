#include "keystate.hpp"

rdm::types::KeyState operator&(rdm::types::KeyState t_ks1, rdm::types::KeyState t_ks2)
{
    return {
        static_cast<rdm::types::KeyState>(
            static_cast<int>(t_ks1) & static_cast<int>(t_ks2)
        )
    };
}

rdm::types::KeyState operator|(rdm::types::KeyState t_ks1, rdm::types::KeyState t_ks2)
{
    return {
        static_cast<rdm::types::KeyState>(
            static_cast<int>(t_ks1) | static_cast<int>(t_ks2)
        )
    };
}