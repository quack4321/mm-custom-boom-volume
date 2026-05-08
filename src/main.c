#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "audio_api/all.h"
#include "z_daytelop.h"

// --- Missing Declarations ---
// We tell the compiler these exist in the game even if they aren't in our headers
void ShrinkWindow_Destroy(void);
void DayTelop_Main(GameState* thisx);
void DayTelop_Noop(DayTelopState* this);
void DayTelop_LoadGraphics(DayTelopState* this);

// If your headers are missing this constant, we define it here (0x80 is standard for MM)
#ifndef NA_BGM_UNKNOWN
#define NA_BGM_UNKNOWN 0x80
#endif

RECOMP_PATCH void DayTelop_Init(GameState* thisx) {
    DayTelopState* this = (DayTelopState*)thisx;

    GameState_SetFramerateDivisor(&this->state, 1);
    Matrix_Init(&this->state);
    ShrinkWindow_Destroy();
    View_Init(&this->view, this->state.gfxCtx);
    this->state.main = DayTelop_Main;
    this->state.destroy = DayTelop_Destroy;
    this->transitionCountdown = 140;
    this->fadeInState = DAYTELOP_HOURSTEXT_OFF;

    if (gSaveContext.save.day < 9) {
        if (gSaveContext.save.day == 0) {
            Sram_ClearFlagsAtDawnOfTheFirstDay();
        }
        Sram_IncrementDay();
    }

    DayTelop_Noop(this);
    DayTelop_LoadGraphics(this);

    // --- CUSTOM AUDIO INJECTION ---
    
    // 1. Get the volume from your slider (0.0 to 3.0)
    double custom_volume = recomp_get_config_double("jingle_volume");

    // 2. Register the audio file. 
    // The function returns the ID directly as an s32!
    AudioApiFileInfo myBoom = { 0 };
    s32 boomId = AudioApi_CreateStreamedFanfare(&myBoom, "assets", "vanilla_boom.ogg");

    // 3. Play it. 
    // Standard N64 volume is 0-127. We multiply your slider by 64 
    // so that "1.0" on your slider is normal volume, and "2.0" is max.
    u16 vol = (u16)(custom_volume * 64.0);
    if (vol > 127) vol = 127; // Cap it at N64 max

    SEQCMD_EXTENDED_PLAY_SEQUENCE(0, 0, vol, boomId);
}