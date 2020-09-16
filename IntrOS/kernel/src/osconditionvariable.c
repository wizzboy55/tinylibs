/******************************************************************************

    @file    IntrOS: osconditionvariable.c
    @author  Rajmund Szymanski
    @date    29.03.2020
    @brief   This file provides set of functions for IntrOS.

 ******************************************************************************

   Copyright (c) 2018-2020 Rajmund Szymanski. All rights reserved.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.

 ******************************************************************************/

#include "inc/osconditionvariable.h"
#include "inc/oscriticalsection.h"

/* -------------------------------------------------------------------------- */
void cnd_init( cnd_t *cnd )
/* -------------------------------------------------------------------------- */
{
	assert(cnd);

	sys_lock();
	{
		memset(cnd, 0, sizeof(cnd_t));
	}
	sys_unlock();
}

/* -------------------------------------------------------------------------- */
void cnd_wait( cnd_t *cnd, mtx_t *mtx )
/* -------------------------------------------------------------------------- */
{
	unsigned signal;

	assert(cnd);
	assert(mtx);

	mtx_give(mtx);

	sys_lock();
	{
		signal = cnd->signal;
	}
	sys_unlock();

	while (cnd->signal == signal) core_ctx_switch();

	mtx_wait(mtx);
}

/* -------------------------------------------------------------------------- */
void cnd_give( cnd_t *cnd )
/* -------------------------------------------------------------------------- */
{
	assert(cnd);

	sys_lock();
	{
		cnd->signal++;
	}
	sys_unlock();
}

/* -------------------------------------------------------------------------- */
