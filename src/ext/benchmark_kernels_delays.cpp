/* The MIT License (MIT)
 *
 * Copyright (c) 2014 Microsoft
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file
 * 
 * @brief Implementation file for benchmark kernel functions for doing the actual work we care about. :)
 *
 * Optimization tricks include:
 *   - UNROLL macros to manual loop unrolling. This reduces the relative branch overhead of the loop.
 *     We don't want to benchmark loops, we want to benchmark memory! But unrolling too much can hurt
 *	   code size and instruction locality, potentially decreasing I-cache utilization and causing extra overheads.
 *	   This is why we allow multiple unroll lengths at compile-time.
 *   - volatile keyword to prevent compiler from optimizing the code and removing instructions that we need.
 *     The compiler is too smart for its own good!
 */

//Headers
#include <benchmark_kernels_delays.h>
#include <common.h>

//Libraries
#ifdef _WIN32
#include <intrin.h> //For Intel intrinsics
#endif

#ifdef __gnu_linux__
#include <immintrin.h> //for Intel intrinsics
#endif

using namespace xmem;

/***********************************************************************
 ***********************************************************************
 ******************* THROUGHPUT-RELATED BENCHMARK KERNELS **************
 ***********************************************************************
 ***********************************************************************/

/* -------------------- DUMMY BENCHMARK ROUTINES ------------------------- */

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay0(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(wordptr++;) 
		placeholder = 0;
	}
	return placeholder;
}

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay1(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(my_nop();) 
		placeholder = 0;
	}
	return placeholder;
}

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay2(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(my_nop2();) 
		placeholder = 0;
	}
	return placeholder;
}

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay4(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(my_nop4();) 
		placeholder = 0;
	}
	return placeholder;
}

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay8(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(my_nop8();) 
		placeholder = 0;
	}
	return placeholder;
}

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay16(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(my_nop16();) 
		placeholder = 0;
	}
	return placeholder;
}

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay32(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(my_nop32();) 
		placeholder = 0;
	}
	return placeholder;
}

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay64(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(my_nop64();) 
		placeholder = 0;
	}
	return placeholder;
}

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay128(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(my_nop128();) 
		placeholder = 0;
	}
	return placeholder;
}

int32_t xmem::dummy_forwSequentialLoop_Word64_Delay256(void* start_address, void* end_address) {
	volatile int32_t placeholder = 0; //Try our best to defeat compiler optimizations
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(my_nop256();) 
		placeholder = 0;
	}
	return placeholder;
}

/* -------------------- CORE BENCHMARK ROUTINES -------------------------- */

int32_t xmem::forwSequentialRead_Word64_Delay0(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++;)
	}
	return 0;
}

int32_t xmem::forwSequentialRead_Word64_Delay1(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++; my_nop();)
	}
	return 0;
}

int32_t xmem::forwSequentialRead_Word64_Delay2(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++; my_nop2();)
	}
	return 0;
}

int32_t xmem::forwSequentialRead_Word64_Delay4(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++; my_nop4();)
	}
	return 0;
}

int32_t xmem::forwSequentialRead_Word64_Delay8(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++; my_nop8();)
	}
	return 0;
}

int32_t xmem::forwSequentialRead_Word64_Delay16(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++; my_nop16();)
	}
	return 0;
}

int32_t xmem::forwSequentialRead_Word64_Delay32(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++; my_nop32();)
	}
	return 0;
}

int32_t xmem::forwSequentialRead_Word64_Delay64(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++; my_nop64();)
	}
	return 0;
}

int32_t xmem::forwSequentialRead_Word64_Delay128(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++; my_nop128();)
	}
	return 0;
}

int32_t xmem::forwSequentialRead_Word64_Delay256(void* start_address, void* end_address) {
	register Word64_t val;
	for (volatile Word64_t* wordptr = static_cast<Word64_t*>(start_address), *endptr = static_cast<Word64_t*>(end_address); wordptr < endptr;) {
		UNROLL512(val = *wordptr++; my_nop256();)
	}
	return 0;
}
