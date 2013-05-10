/* Copyright (c) 1999, 2000 Carlo Wood.  All rights reserved.
 * Copyright (c) 1994, 1996, 1997 Joseph Arceneaux.  All rights reserved.
 * Copyright (c) 1992, Free Software Foundation, Inc.  All rights reserved.
 *
 * Copyright (c) 1985 Sun Microsystems, Inc. 
 * Copyright (c) 1980 The Regents of the University of California.
 * Copyright (c) 1976 Board of Trustees of the University of Illinois. All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that
 * the above copyright notice and this paragraph are duplicated in all such
 * forms and that any documentation, advertising materials, and other
 * materials related to such distribution and use acknowledge that the
 * software was developed by the University of California, Berkeley, the
 * University of Illinois, Urbana, and Sun Microsystems, Inc.  The name of
 * either University or Sun Microsystems may not be used to endorse or
 * promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES
 * OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Updates;
 * 2002-08-05: Matthias <moh@itec.uni-klu.ac.at> and Eric Lloyd <ewlloyd@neta.com>
 *             Added support for -brf to place function opening brace after function
 *             declaration.
 */

#include "sys.h"

#if defined (HAVE_UNISTD_H)
#include <unistd.h>
#endif
#ifdef PRESERVE_MTIME
#include <time.h>
#ifdef HAVE_UTIME_H
#include <utime.h>
#elif defined(HAVE_SYS_UTIME_H)
#include <sys/utime.h>
#endif
#endif
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif
#include "indent.h"
#include "backup.h"
#include "io.h"
#include "globs.h"
#include "parse.h"
#include "comments.h"
#include "args.h"
#include "output.h"

RCSTAG_CC ("$Id: indent.c,v 1.77 2002/10/28 20:00:56 david Exp $");

/* Round up P to be a multiple of SIZE. */

#ifndef ROUND_UP
#define ROUND_UP(p, size) (((unsigned long) (p) + (size) - 1) & ~((size) - 1))
#endif

/* Stuff that needs to be shared with the rest of indent.
 * Documented in indent.h.
 */

char           * labbuf                      = NULL;
char           * s_lab                       = NULL;
char           * e_lab                       = NULL;
char           * l_lab                       = NULL;
char           * codebuf                     = NULL;
char           * s_code                      = NULL;
char           * e_code                      = NULL;
char           * l_code                      = NULL;
char           * combuf                      = NULL;
char           * s_com                       = NULL;
char           * e_com                       = NULL;
char           * l_com                       = NULL;
char           * s_code_corresponds_to       = NULL;
buf_ty           save_com;
char           * bp_save                     = NULL;
char           * be_save                     = NULL;
int              code_lines                  = 0;
int              line_no                     = 0;
int              break_comma                 = 0;
int              n_real_blanklines           = 0;
int              prefix_blankline_requested  = 0;
codes_ty         prefix_blankline_requested_code;
int              postfix_blankline_requested  = 0;
codes_ty         postfix_blankline_requested_code;
char           * in_name                     = 0; /* Points to current input file name */
file_buffer_ty * current_input               = 0; /* Points to the current input buffer */
int              embedded_comment_on_line    = 0; /* True if there is an embedded comment on this code line */
int              else_or_endif               = 0;
int            * di_stack                    = NULL; /* structure indentation levels */
int              di_stack_alloc              = 0; /* Currently allocated size of di_stack.  */
int              squest                      = 0; /* when this is positive, we have seen a ? without
                                                * the matching : in a <c>?<s>:<s> construct */
unsigned long    in_prog_size   = 0U;
char           * in_prog        = NULL;
int              break_line     = 0;

/* The position that we will line the current line up with when it comes time
 * to print it (if we are lining up to parentheses).  */

static int       paren_target   = 0;

#ifdef DEBUG
int            debug = 1;
#endif

/******************************************************************************/
static void check_code_size(void)
{
    if (e_code >= l_code)                               
    {                                                   
        int nsize = l_code - s_code + 400;               
        codebuf   = (char *) xrealloc (codebuf, nsize);  
        e_code    = codebuf + (e_code - s_code) + 1; 
        l_code    = codebuf + nsize - 5; 
        s_code    = codebuf + 1; 
    }
}

/******************************************************************************/
static void check_lab_size(void)
{
    if (e_lab >= l_lab)
    {
        int nsize  = l_lab - s_lab + 400;               
        labbuf = (char *) xrealloc (labbuf, nsize); 
        e_lab  = labbuf + (e_lab - s_lab) + 1;        
        l_lab  = labbuf + nsize - 5;                
        s_lab  = labbuf + 1;                        
    }
}


/******************************************************************************/
static INLINE void need_chars (
    buf_ty * bp,
    int      needed)
{
    int current_size = (bp->end - bp->ptr);

    if ((current_size + needed) >= bp->size)
    {
        bp->size = ROUND_UP (current_size + needed, 1024);
        bp->ptr = xrealloc (bp->ptr, bp->size);
        if (bp->ptr == NULL)
        {
            fatal (_("Ran out of memory"), 0);
        }

        bp->end = bp->ptr + current_size;
    }
}

/******************************************************************************/
/* Compute the length of the line we will be outputting. */

int output_line_length (void)
{
    int code_length = 0;
    int com_length = 0;
    int length;

    if (s_lab == e_lab)
    {
        length = 0;
    }
    else
    {
        length = count_columns (compute_label_target (), s_lab, EOL) - 1;
    }

    if (s_code != e_code)
    {
        int code_col = compute_code_target (paren_target);

        code_length = count_columns (code_col, s_code, EOL) - code_col;
    }

    if (s_com != e_com)
    {
        int com_col = parser_state_tos->com_col;

        com_length = count_columns (com_col, s_com, EOL) - com_col;
    }

    if (code_length != 0)
    {
        length += compute_code_target(paren_target) - 1 + code_length;

        if (embedded_comment_on_line)
        {
            length += com_length;
        }
    }

    return length;
}

/******************************************************************************/
static void copy_id(
    const codes_ty   type_code,
    BOOLEAN        * force_nl,
    exit_values_ty * file_exit_value,
    const bb_code_ty can_break)
{
    char           * t_ptr;
    
    if (parser_state_tos->want_blank)
    {
        set_buf_break (bb_ident, paren_target);
        *e_code++ = ' ';
    }
    else if (can_break)
    {
        set_buf_break (can_break, paren_target);
    }

    if (s_code == e_code)
    {
        s_code_corresponds_to = token;
    }

    for (t_ptr = token; t_ptr < token_end; ++t_ptr)
    {
        check_code_size();
        *e_code++ = *t_ptr;
    }

    *e_code = '\0'; /* null terminate code sect */

    parser_state_tos->want_blank = true;

    /* Handle the options -nsaf, -nsai and -nsaw */

    if ((type_code == sp_paren) &&
        ((!settings.space_after_if && (*token == 'i')) ||
         (!settings.space_after_for && (*token == 'f')) ||
         (!settings.space_after_while && (*token == 'w'))))
    {
        parser_state_tos->want_blank = false;
    }

    /* If the token is one of the GNU gettext macro's '_' or 'N_'
     * then we don't want a blank */

    if ((((token_end - token) == 1) && (*token == '_')) ||
        (((token_end - token) == 2) && (*token == 'N') &&
         (token[1] == '_')))
    {
        parser_state_tos->want_blank = false;
    }

    /* If the token is va_dcl, it appears without a semicolon, so we
     * need to pretend that one was there.  */

    if (((token_end - token) == 6) && (strncmp (token, "va_dcl", 6) == 0))
    {
        parser_state_tos->in_or_st = 0;
        parser_state_tos->just_saw_decl--;
        parser_state_tos->in_decl = false;

        do
        {
            if (parse (semicolon) != total_success) 
            {
                *file_exit_value = indent_error;
            }
        } while(0);
                
        *force_nl = true;
    }
}

/******************************************************************************/
static void handle_token_form_feed(void)
{
    parser_state_tos->use_ff = true;        /* a form feed is treated
                                             * much like a newline */
    dump_line (true, &paren_target);
    parser_state_tos->want_blank = false;
}

/******************************************************************************
 * 2002-06-13 D.Ingamells Reset force_nl if the line is dumped.
 */
static void handle_token_newline(
    BOOLEAN * force_nl)
{
            
    if (s_lab != e_lab && *s_lab == '#')
    {
        dump_line (true, &paren_target);

        if (s_code == e_code)
        {
            parser_state_tos->want_blank = false;
        }

        *force_nl = false;
    }
    else
    {
        if ( ( (parser_state_tos->last_token != comma) || 
               !settings.leave_comma ||
               !break_comma || 
               (parser_state_tos->p_l_follow > 0) ||
               parser_state_tos->block_init || 
               (s_com != e_com)) &&
             ( ( (parser_state_tos->last_token != rbrace) ||
                 !(settings.braces_on_struct_decl_line && 
                   parser_state_tos->in_decl))))
        {
            /* Attempt to detect the newline before a procedure name,
             * and if e.g., K&R style, leave the procedure on the
             * same line as the type. */

            if (!settings.procnames_start_line && 
                (s_lab == e_lab) &&
                (parser_state_tos->last_token != lparen) &&
                (parser_state_tos->last_token != semicolon) &&
                (parser_state_tos->last_token != comma) &&
                (parser_state_tos->last_rw == rw_decl) &&
                (parser_state_tos->last_rw_depth == 0) &&
                (!parser_state_tos->block_init) &&
                (parser_state_tos->in_decl))
            {
                /* Put a space between the type and the procedure name,
                 * unless it was a pointer type and the user doesn't
                 * want such spaces after '*'. */

                if (!((e_code > s_code) &&
                      (e_code[-1] == '*')))
                {
                    parser_state_tos->want_blank = true;
                }
            }

            if (!parser_state_tos->in_stmt ||
                (s_com != e_com) || 
                embedded_comment_on_line)
            {
                dump_line (true, &paren_target);

                if (s_code == e_code)
                {
                    parser_state_tos->want_blank = false;
                }

                *force_nl = false;
            }
        }
    }

    /* If we were on the line with a #else or a #endif, we aren't
     * anymore.  */

    else_or_endif = false;
    ++line_no;              /* keep track of input line number */
}

/******************************************************************************/
static void handle_token_lparen(
    BOOLEAN        * force_nl,
   BOOLEAN        * sp_sw,
   int            * dec_ind)
{
    char lparen = *token;
    
    /* Braces in initializer lists should be put on new lines. This is
     * necessary so that -gnu does not cause things like char
     * *this_is_a_string_array[] = { "foo", "this_string_does_not_fit",
     * "nor_does_this_rather_long_string" } which is what happens
     * because we are trying to line the strings up with the
     * parentheses, and those that are too long are moved to the right
     * an ugly amount.
     *
     * However, if the current line is empty, the left brace is
     * already on a new line, so don't molest it.
     */

    if ((*token == '{') && ((s_code != e_code) ||
                              (s_com  != e_com)  ||
                              (s_lab  != e_lab)))
    {
        dump_line (true, &paren_target);

        /* Do not put a space before the '{'.  */

        parser_state_tos->want_blank = false;
    }

    /* Count parens so we know how deep we are.  */
    
    ++parser_state_tos->p_l_follow;
    
    if (parser_state_tos->p_l_follow >= parser_state_tos->paren_indents_size)
    {
        parser_state_tos->paren_indents_size *= 2;
        parser_state_tos->paren_indents =
                (short *) xrealloc ((char *) parser_state_tos->paren_indents,
                                    parser_state_tos->paren_indents_size *
                                    sizeof (short));
    }

    parser_state_tos->paren_depth++;

    if (parser_state_tos->want_blank &&
        (*token != '[') &&
        ( (parser_state_tos->last_token != ident) ||
          settings.proc_calls_space ||
          (parser_state_tos->its_a_keyword &&
           (!parser_state_tos->sizeof_keyword || settings.blank_after_sizeof))))
    {
        set_buf_break (bb_proc_call, paren_target);
        *e_code++ = ' ';
        *e_code = '\0';     /* null terminate code sect */
    }
    else
    {
        set_buf_break (bb_proc_call, paren_target);
    }

    if (parser_state_tos->in_decl && !parser_state_tos->block_init)
    {
        if ((*token != '[') && !buf_break_used)
        {
            while ((e_code - s_code) < *dec_ind)
            {
                check_code_size();
                set_buf_break (bb_dec_ind, paren_target);
                *e_code++ = ' ';
            }

            *e_code++ = token[0];
            parser_state_tos->ind_stmt = false;
        }
        else
        {
            *e_code++ = token[0];
        }
    }
    else
    {
        *e_code++ = token[0];
    }

    if (settings.parentheses_space && *token != '[')
    {
        *e_code++ = ' ';
    }

    parser_state_tos->paren_indents[parser_state_tos->p_l_follow - 1] =
            e_code - s_code;

    if (*sp_sw && (parser_state_tos->p_l_follow == 1) &&
        settings.extra_expression_indent &&
        (parser_state_tos->paren_indents[0] < 2 * settings.ind_size))
    {
        parser_state_tos->paren_indents[0] = 2 * settings.ind_size;
    }

    parser_state_tos->want_blank = false;

    if ((parser_state_tos->in_or_st == 1) && *token == '(')
    {
        /* this is a kludge to make sure that declarations will be
         * correctly aligned if proc decl has an explicit type on it, i.e.
         * "int a(x) {..." */

        parse_lparen_in_decl ();

        /* Turn off flag for structure decl or initialization.  */
        
        parser_state_tos->in_or_st = 0;
    }

    /* For declarations, if user wants all fn decls broken, force that
     * now. 
     */
    
    if ((*token == '(')                   && 
        settings.break_function_decl_args &&
        parser_state_tos->in_stmt         && 
        parser_state_tos->in_decl         &&
        (parser_state_tos->paren_depth == 1))
    {
        dump_line(true, &paren_target);
        *force_nl = false;
        
        paren_target = parser_state_tos->paren_depth * settings.ind_size + 1;
        parser_state_tos->paren_indents[parser_state_tos->p_l_follow - 1] = -paren_target;
    }

    if (parser_state_tos->sizeof_keyword)
    {
        parser_state_tos->sizeof_mask |= 1 << parser_state_tos->p_l_follow;
    }

    /* The '(' that starts a cast can never be preceded by an
     * indentifier or decl.  */

    if ((parser_state_tos->last_token == decl) ||
        ((parser_state_tos->last_token == ident) &&
         (parser_state_tos->last_rw != rw_return)))
    {
        parser_state_tos->noncast_mask |=
                1 << parser_state_tos->p_l_follow;
    }
    else
    {
        parser_state_tos->noncast_mask &=
                ~(1 << parser_state_tos->p_l_follow);
    }
}

/******************************************************************************/
static void handle_token_rparen(
   BOOLEAN        * force_nl,
   BOOLEAN        * sp_sw,
   codes_ty       * hd_type,
   BOOLEAN        * last_token_ends_sp,
   exit_values_ty * file_exit_value)
{
            
    parser_state_tos->paren_depth--;
    
#if 1
    /* For declarations, if user wants close of fn decls broken, force that
     * now. 
     */
    if ((*token == ')')                   &&
        settings.break_function_decl_args_end &&
        !parser_state_tos->in_or_st       &&
         parser_state_tos->in_stmt        && 
        parser_state_tos->in_decl         &&
        (parser_state_tos->paren_depth == 0))
    {
        if ((s_code != e_code) || (s_lab != e_lab) || (s_com != e_com))
        {
            dump_line(true, &paren_target);
        }
        
        paren_target = parser_state_tos->paren_depth * settings.ind_size;
        parser_state_tos->paren_indents[parser_state_tos->p_l_follow - 1] = paren_target;
        parser_state_tos->ind_stmt = 0;
    }
#endif

    if (parser_state_tos->
        cast_mask & (1 << parser_state_tos->
                     p_l_follow) & ~parser_state_tos->sizeof_mask)
    {
        parser_state_tos->last_u_d = true;
        parser_state_tos->cast_mask &=
                (1 << parser_state_tos->p_l_follow) - 1;
        if (!parser_state_tos->cast_mask && settings.cast_space)
        {
            parser_state_tos->want_blank = true;
        }
        else
        {
            parser_state_tos->want_blank = false;
            parser_state_tos->can_break = bb_cast;
        }
    }
    else if (parser_state_tos->in_decl &&
             !parser_state_tos->block_init &&
             (parser_state_tos->paren_depth == 0))
    {
        parser_state_tos->want_blank = true;
    }

    parser_state_tos->sizeof_mask &=
            (1 << parser_state_tos->p_l_follow) - 1;

    if (--parser_state_tos->p_l_follow < 0)
    {
        parser_state_tos->p_l_follow = 0;
        WARNING (_("Extra %c"),
                 (unsigned long) *((unsigned char *) token), 0);
    }

    /* if the paren starts the line, then indent it */

    if (e_code == s_code)
    {
        int level = parser_state_tos->p_l_follow;

        parser_state_tos->paren_level = level;
        if (level > 0)
        {
            paren_target = -parser_state_tos->paren_indents[level - 1];
        }
        else
        {
            paren_target = 0;
        }
    }

    if (settings.parentheses_space && *token != ']')
    {
        *e_code++ = ' ';
    }

    *e_code++ = token[0];

    /* check for end of if (...), or some such */

    if (*sp_sw && (parser_state_tos->p_l_follow == 0))
    {
        /* Indicate that we have just left the parenthesized expression
         * of a while, if, or for, unless we are getting out of the
         * parenthesized expression of the while of a do-while loop.
         * (do-while is different because a semicolon immediately
         * following this will not indicate a null loop body).  */

        if (parser_state_tos->p_stack[parser_state_tos->tos] != dohead)
        {
            *last_token_ends_sp = 2;
        }

        *sp_sw = false;
        *force_nl = true;    /* must force newline after if */
        parser_state_tos->last_u_d = true;  /* inform lexi that a
                                             * following operator is
                                             * unary */
        parser_state_tos->in_stmt = false;  /* dont use stmt
                                             * continuation
                                             * indentation */

        if (parse (*hd_type) != total_success)
        {
            *file_exit_value = indent_error;
        }
    }

    /* this should ensure that constructs such as main(){...} and
     * int[]{...} have their braces put in the right place
     */
    
    parser_state_tos->search_brace = settings.btype_2;
}

/******************************************************************************/
static void handle_token_unary_op(
   int            * dec_ind,
   const bb_code_ty can_break)
{
    char           * t_ptr;
    
    if (parser_state_tos->want_blank)
    {
        set_buf_break (bb_unary_op, paren_target);
        *e_code++ = ' ';
        *e_code = '\0';     /* null terminate code sect */
    }
    else if (can_break)
    {
        set_buf_break (can_break, paren_target);
    }

    {
        char *res = token;
        char *res_end = token_end;

        /* if this is a unary op in a declaration, we should
         * indent this token */

        if ((parser_state_tos->paren_depth == 0) &&
            parser_state_tos->in_decl && !buf_break_used &&
            !parser_state_tos->block_init)
        {
            while ((e_code - s_code) < (*dec_ind - (token_end - token)))
            {
                check_code_size();
                set_buf_break (bb_dec_ind, paren_target);
                *e_code++ = ' ';
            }

            parser_state_tos->ind_stmt = false;
        }

        for (t_ptr = res; t_ptr < res_end; ++t_ptr)
        {
            check_code_size();
            *e_code++ = *t_ptr;
        }

        *e_code = '\0';     /* null terminate code sect */
    }

    parser_state_tos->want_blank = false;
}
/******************************************************************************/
static void handle_token_binary_op(
   const bb_code_ty can_break)
{
    char           * t_ptr;
            
    if (parser_state_tos->want_blank
        || (e_code > s_code && *e_code != ' '))
    {
        set_buf_break (bb_binary_op, paren_target);
        *e_code++ = ' ';
        *e_code = '\0';     /* null terminate code sect */
    }
    else if (can_break)
    {
        set_buf_break (can_break, paren_target);
    }

    {
        char *res = token;
        char *res_end = token_end;

        for (t_ptr = res; t_ptr < res_end; ++t_ptr)
        {
            check_code_size();
            *e_code++ = *t_ptr;     /* move the operator */
        }
    }

#if 1
    if (*token == '=')
    {
        parser_state_tos->in_decl = false;
        
    }
#endif
    
    parser_state_tos->want_blank = true;
}
/******************************************************************************/
static void handle_token_postop(void)
{
    *e_code++ = token[0];
    *e_code++ = token[1];
    parser_state_tos->want_blank = true;
}

/******************************************************************************/
static void handle_token_question(
   const bb_code_ty can_break)
{
    squest++;               /* this will be used when a later colon
                             * appears so we can distinguish the
                             * <c>?<n>:<n> construct */

    if (parser_state_tos->want_blank)
    {
        set_buf_break (bb_question, paren_target);
        *e_code++ = ' ';
    }
    else if (can_break)
    {
        set_buf_break (can_break, paren_target);
    }

    *e_code++ = '?';
    parser_state_tos->want_blank = true;
    *e_code = '\0'; /* null terminate code sect */
}

/******************************************************************************/
static void handle_token_casestmt(
   BOOLEAN        * scase,
   exit_values_ty * file_exit_value)
{
    *scase = true;           /* so we can process the later colon
                              * properly */
    do
    {
        if (parse (casestmt) != total_success)
        {
            *file_exit_value = indent_error;
        }
    } while(0);       /* Let parser know about it */
            
}

/******************************************************************************/
static void handle_token_colon(
   BOOLEAN        * scase,
   BOOLEAN        * force_nl,
   int            * dec_ind,
   const bb_code_ty can_break)
{
    char           * t_ptr;

    if (squest > 0)
    {
        /* it is part of the <c> ? <n> : <n> construct */

        --squest;
        if (parser_state_tos->want_blank)
        {
            set_buf_break (bb_colon, paren_target);
            *e_code++ = ' ';
        }
        else if (can_break)
        {
            set_buf_break (can_break, paren_target);
        }

        *e_code++ = ':';
        *e_code = '\0';     /* null terminate code sect */
        parser_state_tos->want_blank = true;
    }
    else
    {
        /*            __ e_code
         *           |
         * "  private:\n"                     C++, treat as label.
         *  ^^^        ^
         *  |          |
         *  |          `- buf_ptr (in different buffer though!)
         *  `- s_code
         *
         * or
         *
         * "  unsigned int private:4\n"       C/C++, treat as bits.
         */
                
        if (parser_state_tos->in_decl)
        {
            if (!(((e_code - s_code > 6) &&
                   !strncmp (&buf_ptr[-8], "private:", 8)) &&
                  !isdigit (*buf_ptr)) &&
                !(((e_code - s_code > 8) &&
                   !strncmp (&buf_ptr[-10], "protected:", 10)) &&
                  !isdigit (*buf_ptr)) &&
                !(((e_code - s_code > 5) &&
                   !strncmp (&buf_ptr[-7], "public:", 7)) &&
                  !isdigit (*buf_ptr)))
            {
                *e_code++ = ':';
                parser_state_tos->want_blank = false;
                return;
            }
            else if (*s_code == ' ')
            {
                /*
                 * It is possible that dec_ind spaces have been inserted before
                 * the `public:' etc. label because indent thinks it's of the
                 * type:
                 */
                /*
                 * Only now we see the '4' isn't there.
                 * Remove those spaces:
                 */
                        
                char *p1 = s_code;
                char *p2 = s_code + *dec_ind;
                        
                while (p2 < e_code)
                {
                    *p1++ = *p2++;
                }
                        
                e_code -= *dec_ind;
                *e_code = '\0';
            }
        }
                
        parser_state_tos->in_stmt = false;      /* seeing a label does not
                                                 * imply we are in a stmt */
        for (t_ptr = s_code; *t_ptr; ++t_ptr)
        {
            *e_lab++ = *t_ptr;  /* turn everything so far into a label */
        }
                
        e_code = s_code;
        clear_buf_break_list ();        /* This is bullshit for C code, because
                                         * normally a label doesn't have breakpoints
                                         * at all of course.  But in the case of
                                         * wrong code, not clearing the list can make
                                         * indent core dump. */
        *e_lab++ = ':';
        set_buf_break (bb_label, paren_target);
        *e_lab++ = ' ';
        *e_lab = '\0';
                
        /* parser_state_tos->pcas e will be used by dump_line to decide
         * how to indent the label. force_nl will force a case n: to be
         * on a line by itself */
                
        *force_nl = parser_state_tos->pcase = *scase;
        *scase = false;
        parser_state_tos->want_blank = false;
    }
}

/******************************************************************************/
static void handle_token_doublecolon(void)
{
    *e_code++ = ':';
    *e_code++ = ':';
    parser_state_tos->want_blank = false;
    parser_state_tos->can_break = bb_doublecolon;
    parser_state_tos->last_u_d = true;
    parser_state_tos->saw_double_colon = true;
}

/******************************************************************************/
static void handle_token_semicolon(
   BOOLEAN        * scase,
   BOOLEAN        * force_nl,
   BOOLEAN        * sp_sw,
   int            * dec_ind,
   BOOLEAN        * last_token_ends_sp,
   exit_values_ty * file_exit_value)
{
    parser_state_tos->in_or_st = 0;
    parser_state_tos->saw_double_colon = false;
    *scase = false;
    squest = 0;

    /* The following code doesn't seem to do much good. Just because
     * we've found something like extern int foo();    or int (*foo)();
     * doesn't mean we are out of a declaration.  Now if it was serving
     * some purpose we'll have to address that.... if
     * (parser_state_tos->last_token == rparen)
     * parser_state_tos->in_parameter_declaration = 0; */

    parser_state_tos->cast_mask = 0;
    parser_state_tos->sizeof_mask = 0;
    parser_state_tos->block_init = 0;
    parser_state_tos->block_init_level = 0;
    parser_state_tos->just_saw_decl--;

    if (parser_state_tos->in_decl &&
        (s_code == e_code) && !buf_break_used &&
        !parser_state_tos->block_init)
    {
        while ((e_code - s_code) < (*dec_ind - 1))
        {
            check_code_size();
            set_buf_break (bb_dec_ind, paren_target);
            *e_code++ = ' ';
        }

        parser_state_tos->ind_stmt = false;
    }

    *e_code = '\0'; /* null terminate code sect */

    /* if we were in a first level structure declaration,
     * we aren't any more */

    parser_state_tos->in_decl = (parser_state_tos->dec_nest > 0) ? true : false;

    /* If we have a semicolon following an if, while, or for, and the
     * user wants us to, we should insert a space (to show that there
     * is a null statement there).  */

    if (*last_token_ends_sp && settings.space_sp_semicolon)
    {
        *e_code++ = ' ';
    }

    *e_code++ = ';';
    *e_code = '\0'; /* null terminate code sect */
    parser_state_tos->want_blank = true;

    /* we are no longer in the middle of a stmt */

    parser_state_tos->in_stmt = (parser_state_tos->p_l_follow > 0);

    if (!*sp_sw)
    {                       /* if not if for (;;) */
        do
        {
            if (parse (semicolon) != total_success)
            {
                *file_exit_value = indent_error;
            }
        } while(0);
                
        *force_nl = true;    /* force newline after a end of stmt */
    }
}

/******************************************************************************/
static void handle_token_lbrace(
   BOOLEAN        * force_nl,
   int            * dec_ind,
   exit_values_ty * file_exit_value)
{
    parser_state_tos->saw_double_colon = false;

    if (!parser_state_tos->block_init)
    {
        *force_nl = true;    /* force other stuff on same line as '{' onto
                              * new line */
        parser_state_tos->in_stmt = false;  /* dont indent the '{' */
    }
    else
    {
        /* dont indent the '{' unless it is followed by more code. */

        char *p = buf_ptr;

        for (;;)
        {
            p = skip_horiz_space(p);

            if (*p == EOL || (*p == '/' && p[1] == '/'))
            {
                parser_state_tos->in_stmt = false;
                break;
            }
            else if (*p == '/' && p[1] == '*')
            {
                p += 2;
                /* skip over comment */

                while (*p && *p != EOL && (*p != '*' || p[1] != '/'))
                {
                    ++p;
                }

                if (!*p || *p == EOL)
                {
                    parser_state_tos->in_stmt = false;
                    break;
                }
                p += 2;

                if (!*p)
                {
                    break;
                }
            }
            else
            {
                break;
            }

        }

        if (parser_state_tos->block_init_level <= 0)
        {
            parser_state_tos->block_init_level = 1;
        }
        else
        {
            parser_state_tos->block_init_level++;
        }
    }

    if (s_code != e_code && parser_state_tos->block_init != 1)
    {
        if ((!parser_state_tos->in_decl && !settings.btype_2) ||
            (parser_state_tos->in_decl &&
             !settings.braces_on_struct_decl_line &&
             !settings.braces_on_func_def_line))
        {
            dump_line (true, &paren_target);
            parser_state_tos->want_blank = false;
        }
        else
        {
            if (parser_state_tos->in_parameter_declaration &&
                !parser_state_tos->in_or_st)
            {
                parser_state_tos->i_l_follow = 0;
                
                if (!settings.braces_on_func_def_line)
                {
                    dump_line (true, &paren_target);
                }
                else
                {
                    *e_code++ = ' ';
                }
                
                parser_state_tos->want_blank = false;
            }
            else
            {
                parser_state_tos->want_blank = true;
            }
        }
    }

    if (parser_state_tos->in_parameter_declaration)
    {
        prefix_blankline_requested = 0;
    }

    if (s_code == e_code)
    {
        parser_state_tos->ind_stmt = false; /* dont put extra indentation
                                               on line with '{' */
    }

    if (parser_state_tos->in_decl && parser_state_tos->in_or_st)
    {
        /* This is a structure declaration.  */

        if (parser_state_tos->dec_nest >= di_stack_alloc)
        {
            di_stack_alloc *= 2;
            di_stack =
                    (int *) xrealloc ((char *) di_stack,
                                      di_stack_alloc * sizeof (*di_stack));
        }

        di_stack[parser_state_tos->dec_nest++] = *dec_ind;
    }
    else
    {
        parser_state_tos->in_decl = false;
        parser_state_tos->decl_on_line = false;     /* we cant be in the
                                                     * middle of a
                                                     * declaration, so dont
                                                     * do special
                                                     * indentation of
                                                     * comments */

        parser_state_tos->in_parameter_declaration = 0;
    }

    *dec_ind = 0;

    /* We are no longer looking for an initializer or structure. Needed
     * so that the '=' in "enum bar {a = 1" does not get interpreted as
     * the start of an initializer.  */

    parser_state_tos->in_or_st = 0;

    do
    {
        if (parse (lbrace) != total_success)
        {
            *file_exit_value = indent_error;
        }
    } while(0);
            
    set_buf_break (bb_lbrace, paren_target);
    if (parser_state_tos->want_blank && s_code != e_code)
    {
        /* put a blank before '{' if '{' is not at start of line */

        *e_code++ = ' ';
    }

    parser_state_tos->want_blank = false;
    *e_code++ = '{';
    *e_code = '\0'; /* null terminate code sect */

    parser_state_tos->just_saw_decl = 0;

    if (parser_state_tos->block_init &&
        (parser_state_tos->block_init_level >= 2))
    {
        /* Treat the indentation of the second '{' as a '('
         * in * struct foo { { bar }, ... } */

        if (++parser_state_tos->p_l_follow >=
            parser_state_tos->paren_indents_size)
        {
            parser_state_tos->paren_indents_size *= 2;
            parser_state_tos->paren_indents =
                    (short *) xrealloc ((char *) parser_state_tos->
                                        paren_indents,
                                        parser_state_tos->paren_indents_size *
                                        sizeof (short));
        }

        ++parser_state_tos->paren_depth;
        parser_state_tos->paren_indents[parser_state_tos->p_l_follow -
                                        1] = e_code - s_code;
    }
    else if (parser_state_tos->block_init &&
             (parser_state_tos->block_init_level == 1))
    {
        /* Put a blank after the first '{' */

        parser_state_tos->want_blank = true;
    }
}
/******************************************************************************/
static void handle_token_rbrace(
    BOOLEAN        * force_nl,
    int            * dec_ind,
    exit_values_ty * file_exit_value)
{
    /* semicolons can be omitted in declarations */
    if (((parser_state_tos->p_stack[parser_state_tos->tos] == decl) &&
         !parser_state_tos->block_init) ||
        /* ANSI C forbids label at end of compound statement, but we don't I guess :/ */
        (parser_state_tos->p_stack[parser_state_tos->tos] == casestmt))
    {
        if (parse (semicolon) != total_success)
        {
            *file_exit_value = indent_error;
        }
    }

    parser_state_tos->just_saw_decl = 0;
    parser_state_tos->ind_stmt = false;
    parser_state_tos->in_stmt  = false;

    if ((parser_state_tos->block_init_level-- == 1)
        && (s_code != e_code))
    {
        /* Found closing brace of declaration initialisation, with
         * code on the same line before the brace */

        if (parser_state_tos->matching_brace_on_same_line < 0)
        {
            /* The matching '{' is not on the same line:
             * put the '}' on its own line. */

            dump_line (true, &paren_target);
        }
        else
        {
            /* Put a space before the '}' */
            set_buf_break (bb_rbrace, paren_target);
            *e_code++ = ' ';
        }
    }

    *e_code++ = '}';
    parser_state_tos->want_blank = true;

    if (parser_state_tos->block_init &&
        (parser_state_tos->block_init_level > 0))
    {
        /* We were treating this { } as normal ( ) */

        --parser_state_tos->paren_depth;

        if (--parser_state_tos->p_l_follow < 0)
        {
            parser_state_tos->p_l_follow = 0;
            WARNING (_("Extra %c"),
                     (unsigned long) *((unsigned char *) token), 0);
        }
    }
    else if (parser_state_tos->dec_nest > 0)
    {
        /* we are in multi-level structure
         * declaration */

        *dec_ind = di_stack[--parser_state_tos->dec_nest];

        if ((parser_state_tos->dec_nest == 0) &&
            !parser_state_tos->in_parameter_declaration)
        {
            parser_state_tos->just_saw_decl = 2;
        }

        parser_state_tos->in_decl = true;
    }

    prefix_blankline_requested = 0;
            
    if (parse (rbrace) != total_success) 
    {
        *file_exit_value = indent_error;
    }
            
    parser_state_tos->search_brace =
            (settings.cuddle_else &&
             (parser_state_tos->p_stack[parser_state_tos->tos] == ifhead)) ||
            (settings.cuddle_do_while &&
             (parser_state_tos->p_stack[parser_state_tos->tos] == dohead));

    if (parser_state_tos->p_stack[parser_state_tos->tos] == stmtl)
    {
        if ( (parser_state_tos->last_rw != rw_struct_like) &&
             (parser_state_tos->last_rw != rw_enum) &&
             (parser_state_tos->last_rw != rw_decl) )
        {
            *force_nl = true;
        }
#if 0
        else if (!settings.braces_on_struct_decl_line &&
                 (parser_state_tos->block_init != 1))
        {
            *force_nl = true;
        }
#endif
    }

    if ( (parser_state_tos->p_stack[parser_state_tos->tos] == ifhead) ||
         ( (parser_state_tos->p_stack[parser_state_tos->tos] == dohead) &&
           !settings.cuddle_do_while && !settings.btype_2))
    {
        *force_nl = true;
    }

    if (!parser_state_tos->in_decl && (parser_state_tos->tos <= 0) &&
        settings.blanklines_after_procs && (parser_state_tos->dec_nest <= 0))
    {
        postfix_blankline_requested = 1;
        postfix_blankline_requested_code =
                parser_state_tos->in_decl ? decl : rbrace;
    }
}

/******************************************************************************/
static void handle_token_swstmt(
    BOOLEAN        * sp_sw,
    codes_ty       * hd_type)
{
            
    *sp_sw = true;
    *hd_type = swstmt;       /* keep this for when we have seen the
                              * expression */
    parser_state_tos->in_decl = false;
}

/******************************************************************************/
static void handle_token_sp_paren(
    BOOLEAN        * sp_sw,
    codes_ty       * hd_type)
{
    /* the interesting stuff is done after the expression is scanned */
    *sp_sw = true;

    /* remember the type of header for later use by parser */
    *hd_type =
            (*token == 'i' ? ifstmt : (*token == 'w' ? whilestmt : forstmt));
}

/******************************************************************************/
static void handle_token_nparen(
    BOOLEAN        * force_nl,
    exit_values_ty * file_exit_value,
    BOOLEAN        * last_else)
{
    parser_state_tos->in_stmt = false;
    if (*token == 'e')
    {
        if (e_code != s_code && (!settings.cuddle_else || e_code[-1] != '}'))
        {
            if (settings.verbose)
            {
                WARNING (_("Line broken"), 0, 0);
            }
            
            dump_line (true, &paren_target);       /* make sure this starts a line */
            parser_state_tos->want_blank = false;
        }
        
        /* This will be over ridden when next we read an `if' */
        
        *force_nl = true;    /* also, following stuff must go onto new
                              * line */
        *last_else = 1;

        if (parse (elselit) != total_success) 
        {
            *file_exit_value = indent_error;
        }
    }
    else
    {
        if (e_code != s_code)
        {
            /* make sure this starts a line */
            
            if (settings.verbose)
            {
                WARNING (_("Line broken"), 0, 0);
            }
            
            dump_line (true, &paren_target);
            parser_state_tos->want_blank = false;
        }
        
        *force_nl = true;    /* also, following stuff must go onto new
                              * line */
        *last_else = 0;

        if (parse (dolit) != total_success) 
        {
            *file_exit_value = indent_error;
        }
    }
}

/******************************************************************************/
static void handle_token_overloaded(
    const bb_code_ty can_break)
{
    char           * t_ptr;

    if (parser_state_tos->want_blank)
    {
        set_buf_break (bb_overloaded, paren_target);
        *e_code++ = ' ';
    }
    else if (can_break)
    {
        set_buf_break (can_break, paren_target);
    }

    parser_state_tos->want_blank = true;

    for (t_ptr = token; t_ptr < token_end; ++t_ptr)
    {
        check_code_size();
        *e_code++ = *t_ptr;
    }

    *e_code = '\0'; /* null terminate code sect */
}

/******************************************************************************/
static void handle_token_decl(
    int            * dec_ind,
    exit_values_ty * file_exit_value)
{
    /* handle C++ const function declarations like
     * const MediaDomainList PVR::get_itsMediaDomainList() const
     * {
     * return itsMediaDomainList;
     * }
     * by ignoring "const" just after a parameter list */

    if ((parser_state_tos->last_token == rparen) &&
        parser_state_tos->in_parameter_declaration &&
        parser_state_tos->saw_double_colon &&
        !strncmp (token, "const", 5))
    {
        char           * t_ptr;
        set_buf_break (bb_const_qualifier, paren_target);
        *e_code++ = ' ';

        for (t_ptr = token; t_ptr < token_end; ++t_ptr)
        {
            check_code_size();
            *e_code++ = *t_ptr;
        }

        *e_code = '\0';     /* null terminate code sect */
    }
    else
    {
        
        if (!parser_state_tos->sizeof_mask)
        {
            if (parse (decl) != total_success)
            {
                *file_exit_value = indent_error;
            }
        }
        
        if ((parser_state_tos->last_token == rparen) &&
            (parser_state_tos->tos <= 1))
        {
            parser_state_tos->in_parameter_declaration = 1;
            
            if (s_code != e_code)
            {
                dump_line (true, &paren_target);
                parser_state_tos->want_blank = false;
            }
        }

        if (parser_state_tos->in_parameter_declaration &&
            (parser_state_tos->dec_nest == 0) &&
            (parser_state_tos->p_l_follow == 0))
        {
            parser_state_tos->ind_level = parser_state_tos->i_l_follow =
                    settings.indent_parameters;

            parser_state_tos->ind_stmt = false;
        }
        
        /* in_or_st set for struct or initialization decl. Don't set it if
         * we're in ansi prototype */
        
        if (!parser_state_tos->paren_depth)
        {
            parser_state_tos->in_or_st = 1;
        }
        
        if (!parser_state_tos->sizeof_mask)
        {
            parser_state_tos->in_decl      = true;
            parser_state_tos->decl_on_line = true;
            
            if (parser_state_tos->dec_nest <= 0)
            {
                parser_state_tos->just_saw_decl = 2;
            }
        }
        
        if (prefix_blankline_requested &&
            ((parser_state_tos->block_init != 0) ||
             (parser_state_tos->block_init_level != -1) ||
             (parser_state_tos->last_token != rbrace) ||
             (e_code != s_code) || 
             (e_lab  != s_lab)  || 
             (e_com  != s_com)))
        {
            prefix_blankline_requested = 0;
        }
        
        *dec_ind = settings.decl_indent > 0 ? settings.decl_indent :
                                              token_end - token + 1; /* get length of token plus 1 */
    }
}

/******************************************************************************/
static void handle_token_ident(
    BOOLEAN        * force_nl,
    BOOLEAN        * sp_sw,
    codes_ty       * hd_type,
    int            * dec_ind,
    exit_values_ty * file_exit_value,
    const bb_code_ty can_break,
    BOOLEAN          is_procname_definition)
{
    /* If we are in a declaration, we must indent identifier. But not
     * inside the parentheses of an ANSI function declaration.  */

    if (parser_state_tos->in_decl &&
        (parser_state_tos->p_l_follow == 0) &&
        (parser_state_tos->last_token != rbrace))
    {
        if (parser_state_tos->want_blank)
        {
            set_buf_break (bb_ident, paren_target);
            *e_code++ = ' ';
            *e_code = '\0'; /* null terminate code sect */
        }
        else if (can_break)
        {
            set_buf_break (can_break, paren_target);
        }

        parser_state_tos->want_blank = false;

        if ((is_procname_definition == false) ||
            (!settings.procnames_start_line && (s_code != e_code)))
        {
            if (!parser_state_tos->block_init && !buf_break_used)
            {
                if (is_procname_definition)
                {
                    *dec_ind = 0;
                }

                while ((e_code - s_code) < *dec_ind)
                {
                    check_code_size();
                    set_buf_break (bb_dec_ind, paren_target);
                    *e_code++ = ' ';
                }

                *e_code = '\0';     /* null terminate code sect */
                parser_state_tos->ind_stmt = false;
            }
        }
        else
        {
            if ((s_code != e_code) &&
                (parser_state_tos->last_token != doublecolon))
            {
                dump_line(true, &paren_target);
            }

            *dec_ind = 0;
            parser_state_tos->want_blank = false;
        }
    }
    else if (*sp_sw && parser_state_tos->p_l_follow == 0)
    {
        *sp_sw = false;
        *force_nl = true;
        parser_state_tos->last_u_d = true;
        parser_state_tos->in_stmt = false;
                
        if (parse (*hd_type) != total_success) 
        {
            *file_exit_value = indent_error;
        }
    }
}

/******************************************************************************/

static void handle_token_struct_delim(void)
{
    char           * t_ptr;
    for (t_ptr = token; t_ptr < token_end; ++t_ptr)
    {
        check_code_size();
        *e_code++ = *t_ptr;
    }

    parser_state_tos->want_blank = false;   /* dont put a blank after a
                                             * period */
    parser_state_tos->can_break = bb_struct_delim;
}

/******************************************************************************/
static void handle_token_comma(
    BOOLEAN        * force_nl,
    int            * dec_ind,
    BOOLEAN          is_procname_definition)
{
    parser_state_tos->want_blank = true;

    if ((parser_state_tos->paren_depth == 0) &&
        parser_state_tos->in_decl &&
        !buf_break_used && (is_procname_definition == false) &&
        !parser_state_tos->block_init)
    {
        while ((e_code - s_code) < (*dec_ind - 1))
        {
            check_code_size();
            set_buf_break (bb_dec_ind, paren_target);
            *e_code++ = ' ';
        }

        parser_state_tos->ind_stmt = false;
    }

    *e_code++ = ',';

    if (parser_state_tos->p_l_follow == 0)
    {
        if (parser_state_tos->block_init_level <= 0)
        {
            parser_state_tos->block_init = 0;
        }

        /* If we are in a declaration, and either the user wants all
         * comma'd declarations broken, or the line is getting too
         * long, break the line.  */

        if (break_comma && !settings.leave_comma)
        {
            *force_nl = true;
        }
    }

    if (parser_state_tos->block_init)
    {
        parser_state_tos->in_stmt = false;  /* Don't indent after comma */
    }

    /* For declarations, if user wants all fn decls broken, force that
     * now. */

    if (settings.break_function_decl_args &&
        (!parser_state_tos->in_or_st &&
         parser_state_tos->in_stmt && parser_state_tos->in_decl))
    {
        *force_nl = true;
    }

}

/******************************************************************************/
static void handle_token_preesc(
    exit_values_ty * file_exit_value)
{
    char * t_ptr;
    char * p;

    if ((s_com != e_com) || (s_lab != e_lab) || (s_code != e_code))
    {
        dump_line(true, &paren_target);
    }

    {
        int in_comment = 0;
        int in_cplus_comment = 0;
        int com_start = 0;
        char quote = 0;
        int com_end = 0;

        /* ANSI allows spaces between '#' and preprocessor directives.
         * If the user specified "-lps" and there are such spaces,
         * they will be part of `token', otherwise `token' is just
         * '#'. */

        for (t_ptr = token; t_ptr < token_end; ++t_ptr)
        {
            check_lab_size();
            *e_lab++ = *t_ptr;
        }

        while (!had_eof && (*buf_ptr != EOL || in_comment))
        {
            check_lab_size();
            *e_lab = *buf_ptr++;

            if (buf_ptr >= buf_end)
            {
                fill_buffer ();
            }

            switch (*e_lab++)
            {
            case BACKSLASH:
                if (!in_comment && !in_cplus_comment)
                {
                    *e_lab++ = *buf_ptr++;
                    if (buf_ptr >= buf_end)
                    {
                        fill_buffer ();
                    }
                }
                break;

            case '/':
                if (((*buf_ptr == '*') ||
                     (*buf_ptr == '/')) &&
                    !in_comment && !in_cplus_comment && !quote)
                {
                    save_com.column = current_column () - 1;

                    if (*buf_ptr == '/')
                    {
                        in_cplus_comment = 1;
                    }
                    else
                    {
                        in_comment = 1;
                    }

                    *e_lab++ = *buf_ptr++;
                    com_start = e_lab - s_lab - 2;

                    /* Store the column that corresponds with the start
                     * of the buffer */

                    if (save_com.ptr == save_com.end)
                    {
                        save_com.start_column = current_column () - 2;
                    }
                }
                break;

            case '"':
            case '\'':
                if (!quote)
                {
                    quote = e_lab[-1];
                }
                else if (e_lab[-1] == quote)
                {
                    quote = 0;
                }

                break;

            case '*':
                if (*buf_ptr == '/' && in_comment)
                {
                    in_comment = 0;
                    *e_lab++ = *buf_ptr++;
                    com_end = e_lab - s_lab;
                }
                break;
            }
        }

        while (e_lab > s_lab && (e_lab[-1] == ' ' || e_lab[-1] == TAB))
        {
            e_lab--;
        }


        if (in_cplus_comment)   /* Should we also check in_comment? -jla */
        {
            in_cplus_comment = 0;
            *e_lab++ = *buf_ptr++;
            com_end = e_lab - s_lab;
        }

        if (e_lab - s_lab == com_end && bp_save == 0)
        {
            /* comment on preprocessor line */

            if (save_com.end != save_com.ptr)
            {
                need_chars (&save_com, 2);
                *save_com.end++ = EOL;  /* add newline between
                                         * comments */
                *save_com.end++ = ' ';
                save_com.len += 2;
                --line_no;
            }

            need_chars (&save_com, com_end - com_start + 1);
            strncpy (save_com.end, s_lab + com_start,
                     com_end - com_start);
            save_com.end[com_end - com_start] = '\0';
            save_com.end += com_end - com_start;
            save_com.len += com_end - com_start;

            e_lab = s_lab + com_start;

            while ((e_lab > s_lab) &&
                   ((e_lab[-1] == ' ') || (e_lab[-1] == TAB)))
            {
                e_lab--;
            }


            /* Switch input buffers so that calls to lexi() will
             * read from our save buffer. */

            bp_save = buf_ptr;
            be_save = buf_end;
            buf_ptr = save_com.ptr;
            need_chars (&save_com, 1);
            buf_end = save_com.end;
            save_com.end = save_com.ptr;        /* make save_com empty */
        }

        *e_lab = '\0';  /* null terminate line */
        parser_state_tos->pcase = false;
    }

    p = s_lab + 1;

    p = skip_horiz_space(p);

    if (strncmp (p, "if", 2) == 0)
    {
        if (settings.blanklines_around_conditional_compilation)
        {
            prefix_blankline_requested++;
            prefix_blankline_requested_code = preesc;

            while (*in_prog_pos++ == EOL)
            {
            }

            in_prog_pos--;
        }

        {
            /* Push a copy of the parser_state onto the stack. All
             * manipulations will use the copy at the top of stack, and
             * then we can return to the previous state by popping the
             * stack.  */

            parser_state_ty *new;

            new = (parser_state_ty *)
                    xmalloc (sizeof (parser_state_ty));
            (void) memcpy (new, parser_state_tos,
                           sizeof (parser_state_ty));

            /* We need to copy the dynamically allocated arrays in the
             * struct parser_state too.  */

            new->p_stack =
                    (codes_ty *) xmalloc (parser_state_tos->p_stack_size *
                                          sizeof (codes_ty));

            (void) memcpy (new->p_stack, parser_state_tos->p_stack,
                           (parser_state_tos->p_stack_size *
                            sizeof (codes_ty)));

            new->il =
                    (int *) xmalloc (parser_state_tos->p_stack_size *
                                     sizeof (int));

            (void) memcpy (new->il, parser_state_tos->il,
                           parser_state_tos->p_stack_size *
                           sizeof (int));

            new->cstk =
                    (int *) xmalloc (parser_state_tos->p_stack_size *
                                     sizeof (int));

            (void) memcpy (new->cstk, parser_state_tos->cstk,
                           parser_state_tos->p_stack_size *
                           sizeof (int));

            new->paren_indents =
                    (short *) xmalloc (parser_state_tos->paren_indents_size *
                                       sizeof (short));
            (void) memcpy (new->paren_indents,
                           parser_state_tos->paren_indents,
                           (parser_state_tos->paren_indents_size *
                            sizeof (short)));

            new->next = parser_state_tos;
            parser_state_tos = new;
            /* GDB_HOOK_parser_state_tos */
        }
    }
    else if ((strncmp (p, "else", 4) == 0) ||
             (strncmp (p, "elif", 4) == 0))
    {
        /* When we get #else, we want to restore the parser state to
         * what it was before the matching #if, so that things get
         * lined up with the code before the #if.  However, we do not
         * want to pop the stack; we just want to copy the second to
         * top elt of the stack because when we encounter the #endif,
         * it will pop the stack.  */

        else_or_endif = (strncmp (p, "else", 4) == 0);
        prefix_blankline_requested = 0;

        if (parser_state_tos->next)
        {
            /* First save the addresses of the arrays for the top of
             * stack.  */

            codes_ty * tos_p_stack       = parser_state_tos->p_stack;
            int      * tos_il            = parser_state_tos->il;
            int      * tos_cstk          = parser_state_tos->cstk;
            short    * tos_paren_indents =
                    parser_state_tos->paren_indents;
            parser_state_ty * second = parser_state_tos->next;

            (void) memcpy (parser_state_tos, second,
                           sizeof (parser_state_ty));
            parser_state_tos->next = second;

            /* Now copy the arrays from the second to top of stack to
             * the top of stack.  */

            /* Since the p_stack, etc. arrays only grow, never shrink,
             * we know that they will be big enough to fit the array
             * from the second to top of stack.  */

            parser_state_tos->p_stack = tos_p_stack;
            (void) memcpy (parser_state_tos->p_stack,
                           parser_state_tos->next->p_stack,
                           parser_state_tos->p_stack_size *
                           sizeof (codes_ty));

            parser_state_tos->il = tos_il;
            (void) memcpy (parser_state_tos->il,
                           parser_state_tos->next->il,
                           (parser_state_tos->p_stack_size *
                            sizeof (int)));

            parser_state_tos->cstk = tos_cstk;
            (void) memcpy (parser_state_tos->cstk,
                           parser_state_tos->next->cstk,
                           (parser_state_tos->p_stack_size *
                            sizeof (int)));

            parser_state_tos->paren_indents = tos_paren_indents;
            (void) memcpy (parser_state_tos->paren_indents,
                           parser_state_tos->next->paren_indents,
                           (parser_state_tos->paren_indents_size *
                            sizeof (short)));
        }
        else
        {
            ERROR (else_or_endif ? _("Unmatched #else") :
                   _("Unmatched #elif"), 0, 0);
            *file_exit_value = indent_error;
        }
    }
    else if (strncmp (p, "endif", 5) == 0)
    {
        else_or_endif = true;
        prefix_blankline_requested = 0;
        /* We want to remove the second to top elt on the stack, which
         * was put there by #if and was used to restore the stack at
         * the #else (if there was one). We want to leave the top of
         * stack unmolested so that the state which we have been using
         * is unchanged.  */

        if (parser_state_tos->next)
        {
            parser_state_ty *second = parser_state_tos->next;

            parser_state_tos->next = second->next;
            free (second->p_stack);
            free (second->il);
            free (second->cstk);
            free (second->paren_indents);
            free (second);
        }
        else
        {
            ERROR (_("Unmatched #endif"), 0, 0);
            *file_exit_value = indent_error;
        }

        if (settings.blanklines_around_conditional_compilation)
        {
            postfix_blankline_requested++;
            postfix_blankline_requested_code = preesc;
            n_real_blanklines = 0;
        }
    }

    /* Don't put a blank line after declarations if they are directly
     * followed by an #else or #endif -Run */

    if (else_or_endif && prefix_blankline_requested_code == decl)
    {
        prefix_blankline_requested = 0;
    }

    /* Normally, subsequent processing of the newline character
     * causes the line to be printed.  The following clause handles
     * a special case (comma-separated declarations separated
     * by the preprocessor lines) where this doesn't happen. */

    if ((parser_state_tos->last_token == comma) &&
        (parser_state_tos->p_l_follow <= 0) &&
        settings.leave_comma &&
        !parser_state_tos->block_init &&
        break_comma && (s_com == e_com))
    {
        dump_line(true, &paren_target);
        parser_state_tos->want_blank = false;
    }

}

/******************************************************************************/
static void handle_token_comment(
    BOOLEAN        * force_nl,
    BOOLEAN        * flushed_nl)
{
            if (parser_state_tos->last_saw_nl && (s_code != e_code))
            {
                *flushed_nl = false;
                dump_line(true, &paren_target);
                parser_state_tos->want_blank = false;
                *force_nl = false;
            }
            print_comment (&paren_target);
}

/******************************************************************************/
static void handle_token_attribute(
    )
{
    char           * t_ptr;
    
    if (s_code != e_code)
    {
        set_buf_break (bb_attribute, paren_target);
        *e_code++ = ' ';
    }

    for (t_ptr = token; t_ptr < token_end; ++t_ptr)
    {
        check_code_size();
        *e_code++ = *t_ptr;
    }

    parser_state_tos->in_decl = false;
    parser_state_tos->want_blank = true;
}

/******************************************************************************/
static void handle_the_token(
    const codes_ty   type_code,
    BOOLEAN        * scase,
    BOOLEAN        * force_nl,
    BOOLEAN        * sp_sw,
    BOOLEAN        * flushed_nl,
    codes_ty       * hd_type,
    int            * dec_ind,
    BOOLEAN        * last_token_ends_sp,
    exit_values_ty * file_exit_value,
    const bb_code_ty can_break,
    BOOLEAN        * last_else,
    BOOLEAN          is_procname_definition)
{
    switch (type_code)
    {
        case form_feed:     /* found a form feed in line */
            handle_token_form_feed();
            break;

        case newline:
            handle_token_newline(force_nl);
            break;

        case lparen:
            handle_token_lparen(force_nl, sp_sw, dec_ind);
            break;

        case rparen:
            handle_token_rparen(force_nl, sp_sw, hd_type, last_token_ends_sp,
                                file_exit_value);
            break;

        case unary_op:
            /* this could be any unary operation */
            handle_token_unary_op( dec_ind, can_break);
            break;

        case binary_op:
            /* any binary operation */
            handle_token_binary_op(can_break);
            break;

        case postop:
            /* got a trailing ++ or -- */
            handle_token_postop();
            break;

        case question:
            /* got a ? */
            handle_token_question(can_break);
            break;

        case casestmt:
            /* got word 'case' or 'default' */
            handle_token_casestmt(scase, file_exit_value);
            copy_id(type_code, force_nl, file_exit_value,can_break);
            break;
            
        case colon:
            /* got a ':' */
            handle_token_colon(scase, force_nl, dec_ind, can_break);
            break;

        case doublecolon:
            /* Deal with C++ Class::Method */
            handle_token_doublecolon();
            break;

        case semicolon:
            /* we are not in an initialization or structure declaration */
            handle_token_semicolon(scase, force_nl, sp_sw, dec_ind,
                                   last_token_ends_sp, file_exit_value);
            break;

        case lbrace:
            /* got a '{' */
            handle_token_lbrace(force_nl, dec_ind, file_exit_value);
            break;

        case rbrace:
            /* got a '}' */
            handle_token_rbrace(force_nl, dec_ind, file_exit_value);
            
            break;

        case swstmt:
            /* got keyword "switch" */
            handle_token_swstmt(sp_sw, hd_type);
            copy_id(type_code, force_nl, file_exit_value, can_break);
            break;
            
        case sp_paren:
            /* token is if, while, for */
            handle_token_sp_paren(sp_sw,  hd_type);
            copy_id(type_code, force_nl, file_exit_value, can_break);
            break;
            
        case sp_else:
            /* got else */
        case sp_nparen:
            /* got do */
            handle_token_nparen(force_nl, file_exit_value, last_else);
            copy_id(type_code, force_nl, file_exit_value,can_break);
            break;
            
        case overloaded:
            /* Handle C++ operator overloading like:
             *
             * Class foo::operator = ()"
             *
             * This is just like a decl, but we need to remember this
             * token type. */
            
            handle_token_overloaded(can_break);
            break;

        case decl:
            /* we have a declaration type (int, register, etc.) */

            handle_token_decl(dec_ind, file_exit_value);
            
            copy_id(type_code, force_nl, file_exit_value, can_break);
            break;
            
        case cpp_operator:
            /* Handle C++ operator overloading.  See case overloaded above. */
        case ident:
            /* got an identifier or constant */
            handle_token_ident(force_nl,  sp_sw, hd_type,
                               dec_ind, file_exit_value,
                               can_break, is_procname_definition);
            
            copy_id(type_code, force_nl, file_exit_value, can_break);
            
            break;

        case struct_delim:
            handle_token_struct_delim();
            break;

        case comma:
            handle_token_comma(force_nl, dec_ind, is_procname_definition);
            break;

        case preesc:
            /* got the character '#' */
            handle_token_preesc(file_exit_value);
            break;

        case comment:
        case cplus_comment:
            /* A C or C++ comment. */
            handle_token_comment(force_nl, flushed_nl);
            break;

            /* An __attribute__ qualifier */
        case attribute:
            handle_token_attribute();
            break;

        default:
            abort ();
    }                       /* end of big switch stmt */
}

/******************************************************************************/
static void sw_buffer(void)
{
    parser_state_tos->search_brace = false;
    bp_save = buf_ptr;
    be_save = buf_end;
    buf_ptr = save_com.ptr;
    need_chars (&save_com, 1);
    buf_end = save_com.end;
    save_com.end = save_com.ptr;        /* make save_com empty */
}

/******************************************************************************/
static BOOLEAN search_brace(
    codes_ty       * type_code,
    BOOLEAN        * force_nl,
    BOOLEAN        * flushed_nl,
    BOOLEAN        * last_else,
    BOOLEAN        * is_procname_definition)
{
    while (parser_state_tos->search_brace)
    {
        /* After scanning an if(), while (), etc., it might be necessary to
         * keep track of the text between the if() and the start of the
         * statement which follows.  Use save_com to do so.
         */

        switch (*type_code)
        {
        case newline:
            ++line_no;
            *flushed_nl = true;
            break;
        case form_feed:
            break;              /* form feeds and newlines found here will be
                                 * ignored */
        case lbrace:
            /* Ignore buffering if no comment stored. */

            if (save_com.end == save_com.ptr)
            {
                parser_state_tos->search_brace = false;
                return true;                                                            /* RETURN */
            }

            /* We need to put the '{' back into save_com somewhere.  */

            if (settings.btype_2 && (parser_state_tos->last_token != rbrace))
            {
                /* Kludge to get my newline back */
                if ((parser_state_tos->last_token == sp_else) &&
                    (save_com.end > &save_com.ptr[4]) &&
                    (save_com.end[-2] == '*') &&
                    (save_com.end[-1] == '/') &&
                    (save_com.ptr[2] == '/') &&
                    (save_com.ptr[3] == '*'))
                {
                    char *p;

                    for (p = &save_com.ptr[4];
                         *p != '\n' && p < &save_com.end[-2]; ++p)
                    {
                    }

                    if (*p != '\n')
                    {
                        *save_com.end++ = EOL;
                    }
                }

                /* Put the brace at the beginning of the saved buffer */

                save_com.ptr[0] = '{';
                save_com.len = 1;
                save_com.column = current_column ();
            }
            else
            {
                /* Put the brace at the end of the saved buffer, after
                 * a newline character.  The newline char will cause
                 * a `dump_line' call, thus ensuring that the brace
                 * will go into the right column. */

                *save_com.end++ = EOL;
                *save_com.end++ = '{';
                save_com.len += 2;
            }

            /* Go to common code to get out of this loop.  */

            sw_buffer();
            break;
                    
        case comment:
            /* Save this comment in the `save_com' buffer, for
             * possible re-insertion in the output stream later. */

            if (!*flushed_nl || (save_com.end != save_com.ptr))
            {
                need_chars (&save_com, 10);

                if (save_com.end == save_com.ptr)
                {
                    /* if this is the first comment, we must set
                     * up the buffer */

                    save_com.start_column = current_column ();
                    save_com.ptr[0] = save_com.ptr[1] = ' ';
                    save_com.end = save_com.ptr + 2;
                    save_com.len = 2;
                    save_com.column = current_column ();
                }
                else
                {
                    *save_com.end++ = EOL;      /* add newline between
                                                 * comments */
                    *save_com.end++ = ' ';
                    save_com.len += 2;
                    --line_no;
                }

                *save_com.end++ = '/';  /* copy in start of comment */
                *save_com.end++ = '*';

                for (;;)
                {
                    /* loop until we get to the end of the
                     * comment */

                    /* make sure there is room for this character and
                     * (while we're at it) the '/' we might add at the end
                     * of the loop. */
                        
                    need_chars (&save_com, 2);
                    *save_com.end = *buf_ptr++;
                    save_com.len++;

                    if (buf_ptr >= buf_end)
                    {
                        fill_buffer ();

                        if (had_eof)
                        {
                            ERROR (_("EOF encountered in comment"), 0, 0);
                            return indent_punt;                               /* RETURN */
                        }
                    }

                    if (*save_com.end++ == '*' && *buf_ptr == '/')
                    {
                        break;  /* we are at end of comment */
                    }
                }

                *save_com.end++ = '/';  /* add ending slash */
                save_com.len++;

                if (++buf_ptr >= buf_end)       /* get past / in buffer */
                {
                    fill_buffer ();
                }

                break;
            }

            /* Just some statement. */

        default:
            /* Some statement.  Unless it's special, arrange
             * to break the line. */

            if (((*type_code == sp_paren) && (*token == 'i') &&    /* "if" statement */
                 *last_else) ||
                ((*type_code == sp_else)  &&     /* "else" statement */
                 (e_code != s_code) && (e_code[-1] == '}')))       /* The "else" follows '}' */
            {
                *force_nl = false;
            }
            else if (*flushed_nl)
            {
                *force_nl = true;
            }

            if (save_com.end == save_com.ptr)
            {
                /* ignore buffering if comment wasnt saved up */

                parser_state_tos->search_brace = false;
                return true;                                      /* RETURN */
            }

            if (*force_nl)
            {
                *force_nl = false;
                --line_no;      /* this will be re-increased when the nl is read from the buffer */
                need_chars (&save_com, 2);
                *save_com.end++ = EOL;
                save_com.len++;
                if (settings.verbose && !*flushed_nl)
                {
                    WARNING (_("Line broken"), 0, 0);
                }

                *flushed_nl = false;
            }

            /* Now copy this token we just found into the saved buffer. */

            *save_com.end++ = ' ';
            save_com.len++;
            buf_ptr = token;

            /* A total nightmare is created by trying to get the
             * next token into this save buffer.  Rather than that,
             * I've just backed up the buffer pointer to point
             * at `token'. --jla 9/95 */

            parser_state_tos->procname      = "\0";
            parser_state_tos->procname_end  = "\0";
            parser_state_tos->classname     = "\0";
            parser_state_tos->classname_end = "\0";

            /* Switch input buffers so that calls to lexi() will
             * read from our save buffer. */

            sw_buffer();
            break;
        }                   /* end of switch */

        if (*type_code != code_eof)
        {
            int just_saw_nl = false;

            if (*type_code == newline)
            {
                just_saw_nl = true;
            }

            *type_code = lexi ();

            if ( ( (*type_code == newline) && (just_saw_nl == true)) ||
                 ( (*type_code == comment) && parser_state_tos->last_saw_nl &&
                   (parser_state_tos->last_token != sp_else)))
            {
                dump_line(true, &paren_target);
                *flushed_nl = true;
            }

            *is_procname_definition = ((parser_state_tos->procname[0] != '\0') &&
                                       parser_state_tos->in_parameter_declaration);
        }

        if ((*type_code == ident) && *flushed_nl &&
            !settings.procnames_start_line &&
            parser_state_tos->in_decl &&
            (parser_state_tos->procname[0] != '\0'))
        {
            *flushed_nl = 0;
        }
    }                       /* end of while (search_brace) */

    *last_else = 0;

    return true;
}

/******************************************************************************/
static exit_values_ty indent_main_loop(void)
{
    codes_ty         hd_type         = code_eof;
    char           * t_ptr           = NULL;
    codes_ty         type_code       = start_token;
    exit_values_ty   file_exit_value = total_success;
    int              dec_ind         = 0; /* current indentation for declarations */

    BOOLEAN          scase           = false; /* true when we've just see a "case";
                                               * determines what to do with the
                                               * following colon */
    BOOLEAN          flushed_nl;              /* Used when buffering up comments to remember that
                                               * a newline was passed over */
    BOOLEAN          sp_sw           = false; /* true when in the expression part of if(...),
                                               * while(...), etc. */
    BOOLEAN          force_nl        = false;

    /* last_token_ends_sp: True if we have just encountered the end of an if (...),
     * etc. (i.e. the ')' of the if (...) was the last token).  The variable is
     * set to 2 in the middle of the main token reading loop and is decremented
     * at the beginning of the loop, so it will reach zero when the second token
     * after the ')' is read.
     */

    BOOLEAN          last_token_ends_sp = false;

    BOOLEAN          last_else = false; /* true if last keyword was an else */

    for (;;)
    {
        /* this is the main loop.  it will go until
         * we reach eof */

        BOOLEAN is_procname_definition;
        bb_code_ty can_break;

        if (type_code != newline)
        {
            can_break = parser_state_tos->can_break;
        }

        parser_state_tos->last_saw_nl = false;
        parser_state_tos->can_break = bb_none;

        type_code = lexi ();    /* lexi reads one token.  "token" points to
                                 * the actual characters. lexi returns a code
                                 * indicating the type of token */

        /* If the last time around we output an identifier or
         * a paren, then consider breaking the line here if it's
         * too long.
         *
         * A similar check is performed at the end of the loop, after
         * we've put the token on the line. */

        if ((settings.max_col > 0) &&
            (buf_break != NULL) &&
            ( ( (parser_state_tos->last_token == ident) &&
                (type_code != comma) &&
                (type_code != semicolon) &&
                (type_code != newline) &&
                (type_code != form_feed) &&
                (type_code != rparen) &&
                (type_code != struct_delim)) ||
              ( (parser_state_tos->last_token == rparen) &&
                (type_code != comma) &&
                (type_code != rparen) ) ) &&
            (output_line_length () > settings.max_col))
        {
            break_line = 1;
        }

        if (last_token_ends_sp > 0)
        {
            last_token_ends_sp--;
        }

        is_procname_definition =
                (((parser_state_tos->procname[0] != '\0') &&
                  parser_state_tos->in_parameter_declaration) ||
                 (parser_state_tos->classname[0] != '\0'));

        /* The following code moves everything following an if (), while (),
         * else, etc. up to the start of the following stmt to a buffer. This
         * allows proper handling of both kinds of brace placement.
         */

        flushed_nl = false;

        if (!search_brace(&type_code, &force_nl, &flushed_nl, &last_else, &is_procname_definition))
        {
            /* Hit EOF unexpectedly in comment. */
            return indent_punt;
        }
        
        if (type_code == code_eof)
        {
            /* we got eof */
            if (s_lab != e_lab || s_code != e_code || s_com != e_com)   /* must dump end of line */
            {
                dump_line(true, &paren_target);
            }

            if (parser_state_tos->tos > 1)      /* check for balanced braces */
            {
                ERROR (_("Unexpected end of file"), 0, 0);
                file_exit_value = indent_error;
            }

            if (settings.verbose)
            {
                printf (_("There were %d non-blank output lines and %d comments\n"),
                        (int) out_lines, (int) com_lines);
                if (com_lines > 0 && code_lines > 0)
                {
                    printf (_("(Lines with comments)/(Lines with code): %6.3f\n"),
                            (1.0 * com_lines) / code_lines);
                }
            }
            flush_output ();

            return file_exit_value;                                              /* RETURN */
        }

        if ((type_code != comment) &&
            (type_code != cplus_comment) &&
            (type_code != newline) &&
            (type_code != preesc) &&
            (type_code != form_feed))
        {
            if (force_nl &&
                (type_code != semicolon) &&
                ( (type_code != lbrace) ||
                  (!parser_state_tos->in_decl && !settings.btype_2) ||
                  (parser_state_tos->in_decl && !settings.braces_on_struct_decl_line) ||
                  (parser_state_tos->last_token == rbrace)))
            {
                if (settings.verbose && !flushed_nl)
                {
                    WARNING (_("Line broken 2"), 0, 0);
                }

                flushed_nl = false;
                dump_line(true, &paren_target);
                parser_state_tos->want_blank = false;
                force_nl = false;
            }

            parser_state_tos->in_stmt = true;   /* turn on flag which causes
                                                 * an extra level of
                                                 * indentation. this is
                                                 * turned off by a ; or } */
            if (s_com != e_com)
            {
                /* the code has an embedded comment in the
                 * line. Move it from the com buffer to the
                 * code buffer.
                 *
                 * Do not add a space before the comment if it is the first
                 * thing on the line.
                 */

                if (e_code != s_code)
                {
                    set_buf_break (bb_embedded_comment_start, paren_target);
                    *e_code++ = ' ';
                    embedded_comment_on_line = 2;
                }
                else
                {
                    embedded_comment_on_line = 1;
                }

                for (t_ptr = s_com; *t_ptr; ++t_ptr)
                {
                    check_code_size();
                    *e_code++ = *t_ptr;
                }

                set_buf_break (bb_embedded_comment_end, paren_target);
                *e_code++ = ' ';
                *e_code = '\0'; /* null terminate code sect */
                parser_state_tos->want_blank = false;
                e_com = s_com;
            }
        }
        else if ((type_code != comment) &&
                 (type_code != cplus_comment) &&
                 !(settings.break_function_decl_args &&
                   (parser_state_tos->last_token == comma)) &&
                 !( (parser_state_tos->last_token == comma) &&
                    !settings.leave_comma))
        {
            /* preserve force_nl thru a comment but
             * cancel forced newline after newline, form feed, etc.
             * however, don't cancel if last thing seen was comma-newline
             * and -bc flag is on. */

            force_nl = false;
        }

        /* Main switch on type of token scanned */

        check_code_size();
        
        /* now, decide what to do with the token */

        handle_the_token(type_code, &scase, &force_nl, &sp_sw, &flushed_nl,
                         &hd_type, &dec_ind, &last_token_ends_sp, &file_exit_value,
                         can_break, &last_else, is_procname_definition);
        
        *e_code = '\0';         /* make sure code section is null terminated */

        if ((type_code != comment) &&
            (type_code != cplus_comment) &&
            (type_code != newline) &&
            (type_code != preesc) &&
            (type_code != form_feed))
        {
            parser_state_tos->last_token = type_code;
        }

        /* Now that we've put the token on the line (in most cases),
         * consider breaking the line because it's too long.
         *
         * Don't consider the cases of `unary_op', newlines,
         * declaration types (int, etc.), if, while, for,
         * identifiers (handled at the beginning of the loop),
         * periods, or preprocessor commands. */

        if ((settings.max_col > 0) && (buf_break != NULL))
        {
            if ( ( (type_code == binary_op) ||
                   (type_code == postop) ||
                   (type_code == question) ||
                   ((type_code == colon) && (scase || (squest <= 0))) ||
                   (type_code == semicolon) ||
                   (type_code == sp_nparen) ||
                   (type_code == sp_else) ||
                   ((type_code == ident) && (*token == '\"')) ||
                   (type_code == struct_delim) ||
                   (type_code == comma)) &&
                 (output_line_length () > settings.max_col))
            {
                break_line = 1;
            }
        }
    }                           /* end of main infinite loop */
}

/******************************************************************************/
static exit_values_ty indent (
    file_buffer_ty * this_file)
{
    in_prog                     = this_file->data;
    in_prog_pos                 = this_file->data;
    in_prog_size                = this_file->size;
    squest                      = false;
    n_real_blanklines           = 0;
    postfix_blankline_requested = 0;

    clear_buf_break_list ();
    
    break_line = 0;

    if (settings.decl_com_ind <= 0)      /* if not specified by user, set this */
    {
        settings.decl_com_ind = settings.ljust_decl ? (settings.com_ind <= 10 ? 2 :
                                                       settings.com_ind - 8) :
                                                       settings.com_ind;
    }

    if (settings.continuation_indent == 0)
    {
        settings.continuation_indent = settings.ind_size;
    }

    if (settings.paren_indent == -1)
    {
        settings.paren_indent = settings.continuation_indent;
    }

    if (settings.case_brace_indent == -1)
    {
        settings.case_brace_indent = settings.ind_size;   /* This was the previous default */
    }

    fill_buffer ();             /* Fill the input buffer */

    return indent_main_loop();         /* do the work. */
}

/******************************************************************************/
static char * handle_profile (int argc, char *argv[])
{
    int i;
    char *profile_pathname = NULL;

    for (i = 1; i < argc; ++i)
    {
        if ((strcmp (argv[i], "-npro") == 0) ||
            (strcmp (argv[i], "--ignore-profile") == 0) ||
            (strcmp (argv[i], "+ignore-profile") == 0))
        {
            break;
        }
    }

    if (i >= argc)
    {
        profile_pathname = set_profile ();
    }

    return profile_pathname;
}

/******************************************************************************/
static char    * out_name        = 0; /* Points to the name of the output file */
static int       input_files     = 0; /* How many input files were specified */
static char **   in_file_names   = NULL; /* Names of all input files */
static int       max_input_files = 128; /* Initial number of input filenames to allocate. */


/******************************************************************************/
static exit_values_ty process_args (
    int       argc,
    char    * argv[],
    BOOLEAN * using_stdin)
{
    int i;
    exit_values_ty exit_status = total_success;

    for (i = 1; i < argc; ++i)
    {
        if ((*argv[i] != '-') && (*argv[i] != '+'))       /* Filename */
        {
            if (settings.expect_output_file == true)       /* Last arg was "-o" */
            {
                if (out_name != 0)
                {
                    fprintf (stderr,
                             _("indent: only one output file (2nd was %s)\n"),
                             argv[i]);
                    exit_status = invocation_error;
                    break;
                }

                if (input_files > 1)
                {
                    fprintf (stderr,
                             _("indent: only one input file when output file is specified\n"));
                    exit_status = invocation_error;
                    break;
                }

                out_name = argv[i];
                settings.expect_output_file = false;
                continue;
            }
            else
            {
                if (*using_stdin)
                {
                    fprintf (stderr,
                             _("indent: can't have filenames when specifying standard input\n"));
                    exit_status = invocation_error;
                    break;
                }

                input_files++;

                if (input_files > 1)
                {
                    if (out_name != 0)
                    {
                        fprintf (stderr,
                                 _("indent: only one input file when output file is specified\n"));
                        exit_status = invocation_error;
                        break;
                    }

                    if (settings.use_stdout != 0)
                    {
                        fprintf (stderr,
                                 _("indent: only one input file when stdout is used\n"));
                        exit_status = invocation_error;
                        break;
                    }

                    if (input_files > max_input_files)
                    {
                        max_input_files = 2 * max_input_files;
                        in_file_names =
                                (char **) xrealloc ((char *) in_file_names,
                                                    (max_input_files *
                                                     sizeof (char *)));
                    }
                }

                in_file_names[input_files - 1] = argv[i];
            }
        }
        else
        {
            /* '-' as filename means stdin. */
            
            if (strcmp (argv[i], "-") == 0)
            {
                if (input_files > 0)
                {
                    fprintf (stderr,
                             _("indent: can't have filenames when specifying standard input\n"));
                    exit_status = invocation_error;
                    break;
                }

                *using_stdin = true;
            }
            else
            {
                i += set_option (argv[i], (i < argc ? argv[i + 1] : 0), 1);
            }
        }
    }

    return exit_status;
}

/******************************************************************************/
static exit_values_ty indent_multiple_files(void)
{
    exit_values_ty exit_status = total_success;
    
    int i;
    /* When multiple input files are specified, make a backup copy
     * and then output the indented code into the same filename. */

    for (i = 0; input_files; i++, input_files--)
    {
        exit_values_ty status;
        struct stat file_stats;

        in_name = in_file_names[i];
        out_name = in_file_names[i];
        current_input = read_file(in_file_names[i], &file_stats);

        open_output(out_name, "r+");

        make_backup(current_input, &file_stats); /* Aborts on failure. */

        /* We have safely made a backup so the open file can be truncated. */
          
        reopen_output_trunc(out_name);
          
        reset_parser();
        status = indent (current_input);

        if (status > exit_status)
        {
            exit_status = status;
        }

        if (settings.preserve_mtime)
        {
            close_output(&file_stats, out_name);
        }
        else
        {
            close_output(NULL, out_name);
        }
    }
    
    return exit_status;
}

/******************************************************************************/
static exit_values_ty indent_single_file(BOOLEAN using_stdin)
{
    exit_values_ty exit_status = total_success;
    struct stat    file_stats;

    if (input_files == 0 || using_stdin)
    {
        input_files = 1;
        in_file_names[0] = "Standard input";
        in_name = in_file_names[0];
        current_input = read_stdin ();
    }
    else
    {
        /* 1 input file */

        in_name = in_file_names[0];
        current_input = read_file (in_file_names[0], &file_stats);

        if (!out_name && !settings.use_stdout)
        {
            out_name = in_file_names[0];
            make_backup (current_input, &file_stats);
        }
    }

    /* Use stdout if it was specified ("-st"), or neither input
     * nor output file was specified. */

    if (settings.use_stdout || !out_name)
    {
        open_output(NULL, NULL);
    }
    else
    {
        open_output(out_name, "w");
    }

    reset_parser ();

    exit_status = indent (current_input);

    if (input_files > 0 && !using_stdin && settings.preserve_mtime)
    {
        close_output(&file_stats, out_name);
    }
    else
    {
        close_output(NULL, out_name);
    }
    
    return exit_status;
}

/******************************************************************************/
static exit_values_ty indent_all (BOOLEAN using_stdin)
{
    exit_values_ty exit_status = total_success;

    if (input_files > 1)
    {
        exit_status = indent_multiple_files();
        
    }
    else
    {
        /* One input stream -- specified file, or stdin */
        exit_status = indent_single_file(using_stdin);
        
    }

    return exit_status;
}

/******************************************************************************/
int main (
    int     argc,
    char ** argv)
{
    int i;
    char *profile_pathname = 0;
    BOOLEAN using_stdin = false;
    exit_values_ty exit_status;

#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
    setlocale (LC_MESSAGES, "");
#endif
    bindtextdomain (PACKAGE, ".");
    textdomain (PACKAGE);

#if defined (_WIN32) && !defined (__CYGWIN__)
    /* wildcard expansion of commandline arguments, see wildexp.c */

    extern void wildexp (int *argc, char ***argv);

    wildexp (&argc, &argv);
#endif /* defined (_WIN32) && !defined (__CYGWIN__) */

#ifdef DEBUG
    if (debug)
    {
        debug_init ();
    }
#endif

    init_parser ();
    initialize_backups ();
    exit_status = total_success;

    input_files = 0;
    in_file_names = (char **) xmalloc (max_input_files * sizeof (char *));

    set_defaults ();

    profile_pathname = handle_profile (argc, argv);

    exit_status = process_args (argc, argv, &using_stdin);

    if (exit_status == total_success)
    {
        if (settings.verbose && profile_pathname)
        {
            fprintf (stderr, _("Read profile %s\n"), profile_pathname);
        }

        set_defaults_after ();

        exit_status = indent_all (using_stdin);
    }
    
    return (exit_status);
}
