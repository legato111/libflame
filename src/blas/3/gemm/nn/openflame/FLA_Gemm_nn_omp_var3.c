
#include "FLAME.h"

FLA_Error FLA_Gemm_nn_omp_var3( FLA_Obj alpha, FLA_Obj A, FLA_Obj B, FLA_Obj C, fla_gemm_t* cntl )
{
  FLA_Obj BL,    BR,       B0,  B1,  B2;

  FLA_Obj CL,    CR,       C0,  C1,  C2;

  int b;

  FLA_Part_1x2( B,    &BL,  &BR,      0, FLA_LEFT );

  FLA_Part_1x2( C,    &CL,  &CR,      0, FLA_LEFT );

  #pragma intel omp parallel taskq
  {
  while ( FLA_Obj_width( BL ) < FLA_Obj_width( B ) ){

    b = FLA_Determine_blocksize( B, BL, FLA_LEFT, FLA_Cntl_blocksize( cntl ) );

    FLA_Repart_1x2_to_1x3( BL,  /**/ BR,        &B0, /**/ &B1, &B2,
                           b, FLA_RIGHT );

    FLA_Repart_1x2_to_1x3( CL,  /**/ CR,        &C0, /**/ &C1, &C2,
                           b, FLA_RIGHT );

    /*------------------------------------------------------------*/

    #pragma intel omp task captureprivate( B1, C1 )
    {
    /* C1 = alpha * A * B1 + C1; */
    FLA_Gemm_external( FLA_NO_TRANSPOSE, FLA_NO_TRANSPOSE,
                       alpha, A, B1, FLA_ONE, C1 );
    }

    /*------------------------------------------------------------*/

    FLA_Cont_with_1x3_to_1x2( &BL,  /**/ &BR,        B0, B1, /**/ B2,
                              FLA_LEFT );

    FLA_Cont_with_1x3_to_1x2( &CL,  /**/ &CR,        C0, C1, /**/ C2,
                              FLA_LEFT );

  }
  }

  return FLA_SUCCESS;
}

