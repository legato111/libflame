/*

    Copyright (C) 2014, The University of Texas at Austin

    This file is part of libflame and is available under the 3-Clause
    BSD license, which can be found in the LICENSE file at the top-level
    directory, or at http://opensource.org/licenses/BSD-3-Clause

*/

#include "FLAME.h"

FLA_Error FLA_Asum_check( FLA_Obj x, FLA_Obj asum_x )
{
  FLA_Error e_val;

  e_val = FLA_Check_floating_object( x );
  FLA_Check_error_code( e_val );

  e_val = FLA_Check_nonconstant_object( x );
  FLA_Check_error_code( e_val );

//  e_val = FLA_Check_real_object( asum_x );
//  FLA_Check_error_code( e_val );

  e_val = FLA_Check_identical_object_precision( x, asum_x );
  FLA_Check_error_code( e_val );

  e_val = FLA_Check_if_scalar( asum_x );
  FLA_Check_error_code( e_val );

  e_val = FLA_Check_if_vector( x );
  FLA_Check_error_code( e_val );

  return FLA_SUCCESS;
}

