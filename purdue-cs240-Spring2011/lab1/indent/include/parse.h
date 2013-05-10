/* Copyright (c) 1999 Carlo Wood.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef INDENT_PARSE_H
#define INDENT_PARSE_H

RCSTAG_H (parse, "$Id: parse.h,v 1.6 2002/02/26 20:38:27 david Exp $");

#include "indent.h"

extern int inc_pstack (void);
extern void parse_lparen_in_decl (void);
extern exit_values_ty parse (codes_ty tk);
extern void init_parser (void);
extern void reset_parser (void);
extern void reduce (void);

#endif /* INDENT_PARSE_H */
