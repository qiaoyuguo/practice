/* Copyright (c) 1999, 2000 Carlo Wood.  All rights reserved.
 * Copyright (c) 1994 Joseph Arceneaux.  All rights reserved.
 * Copyright (c) 1992 Free Software Foundation, Inc.  All rights reserved.
 *
 * Copyright (c) 1985 Sun Microsystems, Inc. Copyright (c) 1980 The Regents
 * of the University of California. Copyright (c) 1976 Board of Trustees of
 * the University of Illinois. All rights reserved.
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
 * permission. THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES
 * OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * HISTORY
 * 2002-01-17 D.Ingamells Add a final newline if not present in file.
 */

#include "sys.h"

#include <ctype.h>
#include <stdlib.h>
#if defined (HAVE_UNISTD_H)
#include <unistd.h>
#endif
#include <string.h>

#ifdef VMS
#include <file.h>
#include <types.h>
#include <stat.h>
#else /* not VMS */
#include <sys/types.h>
#include <sys/stat.h>
   /* POSIX says that <fcntl.h> should exist.  Some systems might need to use
    * <sys/fcntl.h> or <sys/file.h> instead.  */
#include <fcntl.h>
#if defined (_WIN32) && !defined (__CYGWIN__)
#include <io.h>
#endif
#endif /* not VMS */

#include "indent.h"
#include "io.h"
#include "globs.h"
#include "output.h"

RCSTAG_CC ("$Id: io.c,v 1.50 2002/08/04 17:08:41 david Exp $");

/* number of levels a label is placed to left of code */
#define LABEL_OFFSET 2

/******************************************************************************/
/* Stuff that needs to be shared with the rest of indent. Documented in
 * indent.h.
 */

char *in_prog_pos = NULL;	/* used in output.c        io.c indent.c */
char *buf_ptr = NULL;		/* used in output.c lexi.c io.c indent.c comments.c */
char *buf_end = NULL;		/* used in output.c lexi.c io.c indent.c comments.c */
BOOLEAN had_eof = false;	/* used in output.c        io.c          comments.c parse.c */
char *cur_line = NULL;		/* used in output.c        io.c */

/******************************************************************************/

char *
skip_horiz_space (const char *p)
{
  while ((*p == ' ') || (*p == TAB))
    {
      p++;
    }

  return (char *) p;
}

/******************************************************************************/

void
skip_buffered_space (void)
{
  while ((*buf_ptr == ' ') || (*buf_ptr == TAB))
    {
      buf_ptr++;

      if (buf_ptr >= buf_end)
	{
	  fill_buffer ();
	}
    }
}

/******************************************************************************/

static BOOLEAN
is_comment_start (const char *p)
{
  BOOLEAN ret;

  if ((*p == '/') && ((*(p + 1) == '*') || (*(p + 1) == '/')))
    {
      ret = true;
    }
  else
    {
      ret = false;
    }

  return ret;
}

/******************************************************************************/

int
count_columns (int column, char *bp, int stop_char)
{
  while (*bp != stop_char && *bp != NULL_CHAR)
    {
      switch (*bp++)
	{
	case EOL:
	case '\f':		/* form feed */
	  column = 1;
	  break;
	case TAB:
	  column += settings.tabsize - (column - 1) % settings.tabsize;
	  break;
	case 010:		/* backspace */
	  --column;
	  break;
#ifdef COLOR_DEBUG
	case '\e':		/* ANSI color */
	  while (*bp++ != 'm')
	    {
	    }

	  break;
#endif
	default:
	  ++column;
	  break;
	}
    }

  return column;
}


#ifdef VMS
/******************************************************************************/
/* Folks say VMS requires its own read routine.  Then again, some folks
 * say it doesn't.  Different folks have also sent me conflicting versions
 * of this function.  Who's right?
 *
 * Anyway, this version was sent by MEHRDAD@glum.dev.cf.ac.uk and modified
 * slightly by me. */

static int
vms_read (int file_desc, char *buffer, int nbytes)
{
  char *bufp;
  int nread;
  int nleft;

  bufp = buffer;
  nread = 0;
  nleft = nbytes;

  nread = read (file_desc, bufp, nleft);

  while (nread > 0)
    {
      bufp += nread;
      nleft -= nread;
      if (nleft < 0)
	{
	  fatal (_("Internal buffering error"), 0);
	}

      nread = read (file_desc, bufp, nleft);
    }

  return nbytes - nleft;
}
#endif /* VMS */

/******************************************************************************/
/* Return the column we are at in the input line. */

int
current_column (void)
{
  char *p;
  int column;

  /* Use save_com.size here instead of save_com.end, because save_com is
   * already emptied at this point. */

  if ((buf_ptr >= save_com.ptr) && (buf_ptr <= save_com.ptr + save_com.len))
    {
      p = save_com.ptr;
      column = save_com.start_column;
    }
  else
    {
      p = cur_line;
      column = 1;
    }

  while (p < buf_ptr)
    {
      switch (*p)
	{
	case EOL:
	case 014:		/* form feed */
	  column = 1;
	  break;

	case TAB:
	  column += settings.tabsize - (column - 1) % settings.tabsize;
	  break;

	case '\b':		/* backspace */
	  column--;
	  break;

	default:
	  column++;
	  break;
	}

      p++;
    }

  return column;
}

/******************************************************************************/
/* Return the column in which we should place the code in s_code. */

int
compute_code_target (int paren_targ)
{
  int target_col;

  if (buf_break_used)
    {
      return prev_target_col_break;
    }

  if (parser_state_tos->procname[0] &&
      (s_code_corresponds_to == parser_state_tos->procname))
    {
      target_col = 1;

      if (!parser_state_tos->paren_level)
	{
	  return target_col;
	}
    }
  else
    {
      target_col = parser_state_tos->ind_level + 1;
    }

  if (!parser_state_tos->paren_level)
    {
      if (parser_state_tos->ind_stmt)
	{
	  target_col += settings.continuation_indent;
	}

      return target_col;
    }

  if (!settings.lineup_to_parens)
    {
      return target_col + settings.continuation_indent +
	(settings.paren_indent * (parser_state_tos->paren_level - 1));
    }

  return paren_targ;
}

/******************************************************************************/
int
compute_label_target (void)
{
  /* maybe there should be some option to tell indent where to put public:,
   * private: etc. ? */

  if (*s_lab == '#')
    {
      return 1;
    }

  if (parser_state_tos->pcase)
    {
      return parser_state_tos->cstk[parser_state_tos->tos] + 1;
    }

  if (settings.c_plus_plus && parser_state_tos->in_decl)
    {
      /* FIXME: does this belong here at all? */
      return 1;
    }
  else
    {
      return parser_state_tos->ind_level - LABEL_OFFSET + 1;
    }
}

/******************************************************************************/
/* VMS defines it's own read routine, `vms_read' */
#ifndef INDENT_SYS_READ
#define INDENT_SYS_READ read
#endif

/* Read file FILENAME into a `fileptr' structure, and return a pointer to
   that structure. */

file_buffer_ty *
read_file (char *filename, struct stat * file_stats)
{
  static file_buffer_ty fileptr;

  /*
   * size is required to be unsigned for MSDOS,
   * in order to read files larger than 32767
   * bytes in a 16-bit world...
   */

  unsigned int size;

  int namelen = strlen (filename);
  int fd = open (filename, O_RDONLY, 0777);

  if (fd < 0)
    {
      fatal (_("Can't open input file %s"), filename);
    }

  if (fstat (fd, file_stats) < 0)
    {
      fatal (_("Can't stat input file %s"), filename);
    }

  if (file_stats->st_size == 0)
    {
      ERROR (_("Warning: Zero-length file %s"), filename, 0);
    }

#if !defined(__DJGPP__)
  if (sizeof (int) == 2)	/* Old MSDOS */
    {
      if ((file_stats->st_size < 0) || (file_stats->st_size > (0xffff - 1)))
	{
	  fatal (_("File %s is too big to read"), filename);
	}
    }
  else
#endif
    {
      if (file_stats->st_size < 0)
	{
	  fatal (_("System problem reading file %s"), filename);
	}
    }

  fileptr.size = file_stats->st_size;

  if (fileptr.data != 0)
    {
      fileptr.data = (char *) xrealloc (fileptr.data, (unsigned) file_stats->st_size + 2);	/* add 1 for '\0' and 1 for
												 * potential final added
												 * newline. */
    }
  else
    {
      fileptr.data = (char *) xmalloc ((unsigned) file_stats->st_size + 2);	/* add 1 for '\0' and 1 for
										 * potential final added
										 * newline. */
    }

  size = INDENT_SYS_READ (fd, fileptr.data, fileptr.size);

  if (size == (unsigned int) -1)
    {
      fatal (_("Error reading input file %s"), filename);
    }

  if (close (fd) < 0)
    {
      fatal (_("Error closeing input file %s"), filename);
    }


  /* Apparently, the DOS stores files using CR-LF for newlines, but
   * then the DOS `read' changes them into '\n'.  Thus, the size of the
   * file on disc is larger than what is read into memory.  Thanks, Bill. */

  if (size < fileptr.size)
    {
      fileptr.size = size;
    }

  if (fileptr.name != NULL)
    {
      fileptr.name = (char *) xrealloc (fileptr.name, (unsigned) namelen + 1);
    }
  else
    {
      fileptr.name = (char *) xmalloc (namelen + 1);
    }

  (void) strncpy (fileptr.name, filename, namelen);
  fileptr.name[namelen] = EOS;

  if (fileptr.data[fileptr.size - 1] != EOL)
    {
      fileptr.data[fileptr.size] = EOL;
      fileptr.size++;
    }

  fileptr.data[fileptr.size] = EOS;

  return &fileptr;
}

/* This should come from stdio.h and be some system-optimal number */
#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

/******************************************************************************/
/* Suck the standard input into a file_buffer structure, and
   return a pointer to that structure. */

file_buffer_ty *
read_stdin (void)
{
  static file_buffer_ty stdinptr;

  unsigned int size = 15 * BUFSIZ;
  int ch;
  char *p = NULL;

  if (stdinptr.data != 0)
    {
      free (stdinptr.data);
    }

  stdinptr.data = (char *) xmalloc (size + 1);
  stdinptr.size = 0;

  p = stdinptr.data;

  do
    {
      while (stdinptr.size < size)
	{
	  ch = getc (stdin);

	  if (ch == EOF)
	    {
	      break;
	    }

	  *p++ = ch;
	  stdinptr.size++;
	}

      if (ch != EOF)
	{
	  size += (2 * BUFSIZ);
	  stdinptr.data = xrealloc (stdinptr.data, (unsigned) size);
	  p = stdinptr.data + stdinptr.size;
	}
    }
  while (ch != EOF);

  stdinptr.name = "Standard Input";

  stdinptr.data[stdinptr.size] = EOS;

  return &stdinptr;
}

/******************************************************************************/
/* Advance `buf_ptr' so that it points to the next line of input.
 *
 * If the next input line contains an indent control comment turning
 * off formatting (a comment, C or C++, beginning with *INDENT-OFF*),
 * disable indenting by calling inhibit_indenting() which will cause
 * `dump_line ()' to simply print out all input lines without formatting
 * until it finds a corresponding comment containing *INDENT-0N* which
 * re-enables formatting.
 *
 * Note that if this is a C comment we do not look for the closing
 * delimiter.  Note also that older version of this program also
 * skipped lines containing *INDENT** which represented errors
 * generated by indent in some previous formatting.  This version does
 * not recognize such lines. */

void
fill_buffer (void)
{
  char *p = NULL;
  BOOLEAN finished_a_line = false;

  /* indent() may be saving the text between "if (...)" and the following
   * statement.  To do so, it uses another buffer (`save_com').  Switch
   * back to the previous buffer here. */

  if (bp_save != 0)
    {
      buf_ptr = bp_save;
      buf_end = be_save;
      bp_save = be_save = 0;

      /* only return if there is really something in this buffer */

      if (buf_ptr < buf_end)
	{
	  return;
	}
    }

  if (*in_prog_pos == EOS)
    {
      cur_line = buf_ptr = in_prog_pos;
      had_eof = true;
      return;
    }

  /* Here if we know there are chars to read.  The file is
   * NULL-terminated, so we can always look one character ahead
   * safely. */

  p = cur_line = in_prog_pos;
  finished_a_line = false;

  do
    {
      p = skip_horiz_space (p);

      /* If we are looking at the beginning of a comment, see
       * if it turns off formatting with off-on directives. */

      if (is_comment_start (p))
	{
	  p += 2;

	  p = skip_horiz_space (p);

	  /* Skip all lines between the indent off and on directives. */

	  if (strncmp (p, "*INDENT-OFF*", 12) == 0)
	    {
	      inhibit_indenting (true);
	    }
	}

      while ((*p != EOS) && *p != EOL)
	{
	  p++;
	}

      /* Here for newline -- finish up unless formatting is off */

      if (*p == EOL)
	{
	  finished_a_line = true;
	  in_prog_pos = p + 1;
	}

      /* Here for embedded NULLs */

      else if ((unsigned int) (p - current_input->data) < current_input->size)
	{
	  WARNING (_("Warning: File %s contains NULL-characters\n"),
		   current_input->name, 0);
	  p++;
	}

      /* Here for EOF with no terminating newline char. */
      else
	{
	  in_prog_pos = p;
	  finished_a_line = true;
	}
    }
  while (!finished_a_line);

  buf_ptr = cur_line;
  buf_end = in_prog_pos;

  if (buf_break
      && ((buf_break->offset >= e_code - s_code) || (buf_break->offset <= 0)))
    {
      clear_buf_break_list ();
    }
}
