/*

    Copyright (C) 2014, The University of Texas at Austin

    This file is part of libflame and is available under the 3-Clause
    BSD license, which can be found in the LICENSE file at the top-level
    directory, or at http://opensource.org/licenses/BSD-3-Clause

*/

#include "FLAME.h"

#ifdef FLA_ENABLE_NON_CRITICAL_CODE

FLA_Error FLA_Syrk_ut_unb_var5( FLA_Obj alpha, FLA_Obj A, FLA_Obj beta, FLA_Obj C )
{
  FLA_Obj AT,              A0,
          AB,              a1t,
                           A2;

  FLA_Scalr_external( FLA_UPPER_TRIANGULAR, beta, C );

  FLA_Part_2x1( A,    &AT, 
                      &AB,            0, FLA_TOP );

  while ( FLA_Obj_length( AT ) < FLA_Obj_length( A ) ){

    FLA_Repart_2x1_to_3x1( AT,                &A0, 
                        /* ** */            /* *** */
                                              &a1t, 
                           AB,                &A2,        1, FLA_BOTTOM );

    /*------------------------------------------------------------*/

    /* C := C + a1t' * a1t */ 
    FLA_Syr_external( FLA_UPPER_TRIANGULAR, alpha, a1t, C );

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x1_to_2x1( &AT,                A0, 
                                                  a1t, 
                            /* ** */           /* *** */
                              &AB,                A2,     FLA_TOP );

  }

  return FLA_SUCCESS;
}

#endif
