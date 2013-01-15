/********************************************************************************
*
*  The MIT License
*
* Copyright (c)2010 -  t.hayamizu
*
*以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェ
*アを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/ま
*たは販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
*
*上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
*
*ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目*的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法
*行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請
*求、損害、その他の義務について何らの責任も負わないものとします。 
********************************************************************************/
/* 
A C-program for MT19937, with initialization improved 2002/1/26.
Coded by Takuji Nishimura and Makoto Matsumoto.

Before using, initialize the state by using Init(seed)  
or init_by_array(init_key, key_length).

Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.						  

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. The names of its contributors may not be used to endorse or promote 
products derived from this software without specific prior written 
permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Any feedback is very welcome.
http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include "PCH/PCH.h"
#include "Utility/Random.h"

namespace Nyx
{

	// 文字列を使った初期化
	void Random::Init(tstring s) 
	{
		Init((ulong*)s.c_str(), (s.length()+1)/4);
	}

	/* initializes mt[N] with a seed */
	void Random::Init(ulong s)
	{
		mt[0]= s & 0xffffffffUL;
		for (mti=1; mti<N; mti++) {
			mt[mti] = 
				(1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
			/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
			/* In the previous versions, MSBs of the seed affect   */
			/* only MSBs of the array mt[].						*/
			/* 2002/01/09 modified by Makoto Matsumoto			 */
			mt[mti] &= 0xffffffffUL;
			/* for >32 bit machines */
		}
	}

	/* initialize by an array with array-length */
	/* init_key is the array for initializing keys */
	/* key_length is its length */
	/* slight change for C++, 2004/2/26 */
	void Random::Init(ulong init_key[], int key_length)
	{
		int i, j, k;
		Init(19650218UL);
		i=1; j=0;
		k = (N>key_length ? N : key_length);
		for (; k; k--) {
			mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
				+ init_key[j] + j; /* non linear */
			mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
			i++; j++;
			if (i>=N) { mt[0] = mt[N-1]; i=1; }
			if (j>=key_length) j=0;
		}
		for (k=N-1; k; k--) {
			mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
				- i; /* non linear */
			mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
			i++;
			if (i>=N) { mt[0] = mt[N-1]; i=1; }
		}

		mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
	}

	/* generates a random number on [0,0xffffffff]-interval */
	ulong Random::Int32(void)
	{
		ulong y;
		static ulong mag01[2]={0x0UL, MatrixA};
		/* mag01[x] = x * MatrixA  for x=0,1 */

		if (mti >= N) { /* generate N words at one time */
			int kk;

			if (mti == N+1)   /* if Init() has not been called, */
				Init(5489UL); /* a default initial seed is used */

			for (kk=0;kk<N-M;kk++) {
				y = (mt[kk]&UpperMask)|(mt[kk+1]&LowerMask);
				mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
			}
			for (;kk<N-1;kk++) {
				y = (mt[kk]&UpperMask)|(mt[kk+1]&LowerMask);
				mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
			}
			y = (mt[N-1]&UpperMask)|(mt[0]&LowerMask);
			mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

			mti = 0;
		}

		y = mt[mti++];

		/* Tempering */
		y ^= (y >> 11);
		y ^= (y << 7) & 0x9d2c5680UL;
		y ^= (y << 15) & 0xefc60000UL;
		y ^= (y >> 18);

		return y;
	}

	/* generates a random number on [0,0x7fffffff]-interval */
	long Random::Int31(void)
	{
		return (long)(Int32()>>1);
	}

	/* generates a random number on [0,1]-real-interval */
	double Random::Real1(void)
	{
		return Int32()*(1.0/4294967295.0); 
		/* divided by 2^32-1 */ 
	}

	/* generates a random number on [0,1)-real-interval */
	double Random::Real2(void)
	{
		return Int32()*(1.0/4294967296.0); 
		/* divided by 2^32 */
	}

	/* generates a random number on (0,1)-real-interval */
	double Random::Real3(void)
	{
		return (((double)Int32()) + 0.5)*(1.0/4294967296.0); 
		/* divided by 2^32 */
	}

	/* generates a random number on [0,1) with 53-bit resolution*/
	double Random::Res53(void) 
	{ 
		ulong a=Int32()>>5, b=Int32()>>6; 

		return(a*67108864.0+b)*(1.0/9007199254740992.0); 
	} 
	/* These real versions are due to Isaku Wada, 2002/01/09 added */


}