#pragma once

namespace tens {

using IndexType = __int64;

enum TENSRO_BINARY_CALC {
	BINARY_BASE = -1,			// Save lhs, rhs data
	BINARY_CUSTOM = 0,			// CUSTOM function
	EWISE_ADD = 1,				// A + B
	EWISE_SUBTRACT = 2,			// A - B
	EWISE_MULTIPLICATE = 3,		// EMul(A,B)
	EWISE_DEVIDE = 4,			// EDiv(A,B)
	EWISE_GREATER = 5,			// A > B
	EWISE_GREATEREQUAL = 6,		// A >= B
	EWISE_EQUAL = 7,			// A == B
	EWISE_NEQ = 8,				// A != B
	EWISE_LESS = 9,				// A < B
	EWISE_LESSEQUAL = 10,		// A <= B
	EWISE_AND = 11,				// A && B
	EWISE_OR = 12,				// A || B
	EWISE_XOR = 13,				// A ^ B
	EWISE_POW = 14				// EPow(A,B)
};

 
 enum TENSOR_UNARY_CALC {
 	UNARY_BASE = -1,			// Save lhs, rhs data
 	UNARY_CUSTOM = 0,			//  
 	EWISE_NEGATIVE = 1,			// -A
 	EWISE_NOT = 2,				// !A	// not implemented
	EWISE_SQRT = 3,				// A.ESqrt()
	EWISE_SQUARE = 4,			// A.Square()
	EWISE_EXP = 5,				// A.Exp()
	EWISE_LOG = 6,				// A.Log()
	EWISE_CEIL = 7,				// A.CEIL()
	EWISE_FLOOR  = 8,			// A.FLOOR()
	EWISE_ROUND = 9,				// A.ROUND()
	EWISE_CLIP = 10
};


 enum TENSOR_REDUCTION_CALC {
	 REDUCE_BASE = -1,			
	 REDUCE_CUSTOM = 0,
	 REDUCE_MAXIMUM = 1,
	 REDUCE_MINIMUM = 2,
	 REDUCE_SUM = 3,
	 REDUCE_MEAN = 4,
	 REDUCE_RMSE = 5,
 };

enum MATRIX_TYPE
{
	MATRIX = 0,
	ROWVECTOR = 1,
	COLUMNVECTOR = 2
};




}