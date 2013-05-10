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

#ifndef INDENT_ARGS_H
#define INDENT_ARGS_H

RCSTAG_H (args, "$Id: args.h,v 1.7 2002/03/15 07:48:45 david Exp $");

extern void set_defaults (void);
extern void set_defaults_after (void);
extern int set_option (const char *option, const char *param, int explicit);
extern char *set_profile (void);

#endif /* INDENT_ARGS_H */
