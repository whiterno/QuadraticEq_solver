#ifndef _CPRINT
#define _CPRINT

//!
//! @brief colorful printf
//!
//! @param [in] const int col   printed color
//! @param [out] const char* fmt    output string
//!
//! @return void
//!
void cprint(const int col, const char* fmt, ...);

//!
//! @brief enables or disables cprint
//!
//! @param [in]const int col    ability flag
//!
//! @return void
//!
void set_color_flag(const int col);

#endif
