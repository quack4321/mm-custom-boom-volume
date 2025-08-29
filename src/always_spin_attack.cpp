// math.h must be included before any decomp headers to prevent issues that stem from defining `this`.
#include "math.h"

// Define `this` before including decomp headers to work around it being a keyword in C++.
#define this this_
extern "C" {
#   include "global.h"
}
// Undo the `this` define.
#undef this

#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "string_printf.hpp"

#include <string>
#include <vector>

std::vector<int> myvec;

// Patches a function in the base game that's used to check if the player should quickspin.
RECOMP_PATCH s32 Player_CanSpinAttack(Player* player) {
    recomp_printf("enum_option: %d\n", recomp_get_config_u32("enum_option"));
    recomp_printf("number_option: %d\n", recomp_get_config_double("number_option"));
    char* string_option = recomp_get_config_string("string_option");
    if (string_option != NULL) {
        recomp_printf("string_option: %s\n", string_option);
        recomp_free_config_string(string_option);
    }

    recomp_printf("myvec.size(): %d\n", myvec.size());

    // Always spin attack.
    return true;
}

RECOMP_CALLBACK("*", recomp_on_init) void on_init() {
    std::string mystr = recomputils::string_printf("Test: %d %f\n", 1, 2.0f);
    recomp_printf(mystr.c_str());

    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(3);
}
