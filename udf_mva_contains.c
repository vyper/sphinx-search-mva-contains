//
// $Id$
//

//
// Sphinx MVA Contains
//
// Linux
// gcc -fPIC -shared -o udf_mva_contains.so udf_mva_contains.c
// CREATE FUNCTION mva_contains RETURNS INT SONAME 'udf_mva_contains.so';
//
// Windows
// cl /MTd /LD udf_mva_contains.c
// CREATE FUNCTION mva_contains RETURNS INT SONAME 'udf_mva_contains.dll';
//

#include "sphinxudf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

/// UDF version control
/// gets called once when the library is loaded
DLLEXPORT int udf_mva_contains_ver ()
{
	return SPH_UDF_VERSION;
}

//////////////////////////////////////////////////////////////////////////

DLLEXPORT int mva_contains_init ( SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_message )
{
	if ( args->arg_count!=2 ||
    ( args->arg_types[0]!=SPH_UDF_TYPE_UINT32 ) ||
		( args->arg_types[1]!=SPH_UDF_TYPE_UINT32SET ) )
	{
		snprintf ( error_message, SPH_UDF_ERROR_LEN, "AVGMVA() requires 1 INT and 1 MVA argument" );
		return 1;
	}

	return 0;
}

DLLEXPORT int mva_contains ( SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_flag )
{
  unsigned int * val = (unsigned int *) args->arg_values[0];
	unsigned int * mva = (unsigned int *) args->arg_values[1];
	int i, n;

	if ( !mva )
		return 0;

  n = *mva++;

	for ( i=0; i<n; i++ ) {
    if (*mva++ == *val)
      return 1;
  }

	return 0;
}

//
// $Id$
//
