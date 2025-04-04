/* 
 * File:   main.h
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */
#include <xc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MAIN_H
#define	MAIN_H


#ifdef	__cplusplus
extern "C" {
#endif

    #define _XTAL_FREQ 20000000
    
    void chenillard(bool right);
    void read_button(bool *up, bool *menu);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

