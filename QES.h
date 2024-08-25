#ifndef _QES
#define _QES

#include "in_out/in_out.h"
#include "QES_funcs/QES_funcs.h"
#include "QES_structs.h"
#include "terminal/terminal.h"
#include "tests/tests.h"
#include "useful/useful.h"
#include "consts.h"
#include "cprint/cprint.h"

//!
//! @brief run function
//!
//! @param [in] int check_res   checks the result of terminal input
//! @param [in] int argc    amount of terminal input
//! @param [in] char** argv     terminal input
//!
//! @return void
//!
void runProgramm(int check_res, int argc, char* argv[]);

#endif
