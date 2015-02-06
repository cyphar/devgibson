/* devgibson: hackers in 'yo kernel!
 * Copyright (C) 2015 @cyphar <cyphar@cyphar.com>
 * Copyright (C) 2015 @sysr-q <chris@gibsonsec.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../plague.h"

struct script_t hackers = {
	/* metadata */
	.title = "Hackers (1995)",
	.director = "Iain Softley",
	.presenter = "Tux",

	/* use casting magic to allow sizeof it do its magic */
	/* your syntax highlighter might start bleeding from its parsers, but that's just part of the hacking process */
	.len = sizeof((struct line_t[]){
#include "hackers.h"
	}) / sizeof(struct line_t),

	/* include the data */
	.lines = {
#include "hackers.h"
	},
};
