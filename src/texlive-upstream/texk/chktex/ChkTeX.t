%%
%%  ChkTeX v1.7.4, LaTeX documentation for ChkTeX program.
%%  Copyright (C) 1995-96 Jens T. Berger Thielemann
%%
%%  This program is free software; you can redistribute it and/or modify
%%  it under the terms of the GNU General Public License as published by
%%  the Free Software Foundation; either version 2 of the License, or
%%  (at your option) any later version.
%%
%%  This program is distributed in the hope that it will be useful,
%%  but WITHOUT ANY WARRANTY; without even the implied warranty of
%%  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%%  GNU General Public License for more details.
%%
%%  You should have received a copy of the GNU General Public License
%%  along with this program; if not, write to the Free Software
%%  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
%%
%%  Contact the author at:
%%              Jens Berger
%%              Spektrumvn. 4
%%              N-0666 Oslo
%%              Norway
%%              E-mail: <jensthi@ifi.uio.no>
%%
%% NOTE: This file is written in LaTeX, and should be compiled
%% before viewing. If you don't know how to do this, consult
%% your local TeX guru. If you don't possess LaTeX, you are
%% assumed to not need this program; so there's no text version
%% of this file...
%%
%% You may still be able to view the DVI or PostScript versions of
%% this file, though, they are included in the archive.
%%



\documentclass[a4paper]{article}
%latex
\usepackage{array, tabularx, verbatim, multicol}
\usepackage[T1]{fontenc}
\nonfrenchspacing
\newcounter{errornum}
\setcounter{errornum}{1}
%endlatex
\newcommand{\jtbt}{Jens~T. Berger~Thielemann}
\newcommand{\Cmd}[1]{``\texttt{#1}''}
\newcommand{\rsrc}{``\texttt{chktexrc}''}
\newcommand{\chktex}{Chk\TeX}

%latex
\newcolumntype{Y}{>{\raggedright\arraybackslash}X}
\newcommand{\fmted}[1]{%
  {\noindent\large%
    \begin{tabularx}{\linewidth}{lY}%
      \bf Warning \theerrornum:  & \texttt{#1}%
    \end{tabularx}}\stepcounter{errornum}\nopagebreak[4]}

\newenvironment{errdesc}[1]{\noindent\fmted{#1}\begin{quote}}{\end{quote}%
\pagebreak[3]}

\newenvironment{html}{\comment}{\endcomment}
\newenvironment{rawhtml}{\comment}{\endcomment}

\makeatletter
\@namedef{errdesc*}#1{\begin{errdesc}{\textit{#1}}}
\@namedef{enderrdesc*}{\end{errdesc}}
\makeatother


\newenvironment{errexam}
{
\vskip 0pt plus 5pt
\begin{center}
}
{\end{center}}
\columnseprule 0.1pt

%!\newcommand{\BS}{\verb@\@}
%!\newcommand{\chktex}{ChkTeX}
%!\newcommand{\slash}{/}
%endlatex


\title{\chktex\ v1.7.4}
\author{Jens~T. Berger~Thielemann}
\date{\today}


\begin{document}
\maketitle

%latex
\newcommand{\BS}{\char`\\}
%endlatex
\section{Introduction}

This program has been written in frustration because some constructs in
\LaTeX\ are sometimes non-intuitive, and easy to forget. It is
\emph{not} a replacement for the built-in checker in \LaTeX\@; however it
catches some typographic errors \LaTeX\ oversees. In other words, it
is Lint for \LaTeX. Filters are also provided for checking the
\LaTeX\ parts of CWEB documents.

It is written in ANSI C and compiles silently under GCC using
\Cmd{-Wall -ansi -pedantic} and almost all warning flags. This means
that you can compile \& use the program on your favorite machine.
Full source included.

The program also supports output formats suitable for further
processing by editors or other programs, making errors easy to cycle through.
For example, recent versions of AUC\TeX\ (the Emacs mode) interface
beautifully with \chktex.

The program itself does not have any machine requirements; However compiling
for other platforms has not been done for a long time now so the code has been
removed. If interest rises it can be resurrected.


\section{Features}
\chktex\ begins to get quite a few bells \& whistles now.  However, you
should be aware of that in most cases, all this is transparent to the user.
As you will see, \chktex\ offers the ability to adapt to many environments
and configurations.

\begin{itemize}
\item Supports over 40 warnings. Warnings include:
%latex
  \begin{multicols}{2}
    \begin{flushleft}
%endlatex
      \begin{itemize}
      \item Commands terminated with space. Ignores \Cmd{\BS{}tt}, etc.
      \item Space in front of references instead of \Cmd{\~{}}.
      \item Forgetting to group parenthesis characters when
        sub-\slash{}super\-scripting.
      \item Italic correction (\Cmd{\BS/}) mistakes (double,
        missing, unnecessary).
      \item Parenthesis and environment matching.
      \item Ellipsis detection; also checks whether to use
        \Cmd{\BS{}dots}, \Cmd{\BS{}cdots} or \Cmd{\BS{}ldots}.
      \item Enforcement of normal space after abbreviation. Detects
        most abbreviations automagically.
      \item Enforcement of end-of-sentence space when the last
        sentence ended with capital letter.
      \item Math-mode on/off detection.
      \item Quote checking, both wrong types (\Cmd{"}) and wrong
        direction.
      \item Recommends splitting three quotes in a row.
      \item Searching for user patterns.
      \item Displays comments.
      \item Space in front of \Cmd{\BS{}label} and similar commands.
      \item Use of \Cmd{x} instead of \Cmd{\$\BS{}times\$} between numbers.
      \item Multiple spaces in input which will be rendered as one
        space (or multiple spaces, where that is undesirable).
      \item Warns about text which may be ignored.
      \item Mathematical operators typeset as variables.
      \item No space in front of/after parenthesis.
      \item Demands a consistent quote style.
      \item Punctuation inside inner math mode/outside display math
        mode.
      \item Use of \TeX\ primitives where \LaTeX\ equivalents are
        available.
      \item Space in front of footnotes.
      \item Bogus characters following commands.
      \item Ability to suppress warnings on a single line.
      \end{itemize}
%latex
    \end{flushleft}
  \end{multicols}
%endlatex
\item Fully customizable. Intelligent resource format makes it
  possible to make \chktex\ respect your \LaTeX\ setup.  Even
  command-line options may be specified globally in the \rsrc\ file.
\item Supports \Cmd{\BS{}input} command; both \TeX\ and \LaTeX\ version.
  Actually includes the files. \Cmd{TEXINPUTS}-equivalent search path.
\item Intelligent warning/error handling. The user may promote/mute
  warnings to suit his preferences. You may also mute warnings in the
  header of a file; thus killing much unwanted garbage.
\item Scripts included for checking CWEB files written in \LaTeX.
  (Requires perl v5).
\item Supports both \LaTeX\ 2.09 and \LaTeXe{}.
\item Flexible output handling. Has some predefined formats and lets
  the user specify his own format.  Uses a \Cmd{printf()} similar
  syntax. \Cmd{lacheck} compatible mode included for interfacing with
  systems which only support lacheck.
\item Written in ANSI C\@. \Cmd{configure} script included for easy
  setup and installation on UNIX systems.
\end{itemize}

Still, it is important to realize that the output from \chktex\ is
only intended as a \emph{guide} to fixing faults. However, it is by
no means always correct. This means that correct \LaTeX\ code may
produce errors in \chktex, and vice versa: Incorrect \LaTeX\ code may pass
silently through.



\section{Legal stuff}

\chktex{}, documentation, installations scripts, CWEB filters and other
materials provided are copyright \copyright\ 1995--96 Jens~T.
Berger~Thielemann, unless explicitly stated otherwise.

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY\@; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE\@.  See the GNU General Public License for
more details.

You  should  have  received  a  copy of the GNU General Public License
along   with  this  program;  if  not,  write  to:
\begin{quote}
    The  Free  Software Foundation, Inc. \\
    51 Franklin Street \\
    Fifth Floor \\
    Boston \\
    MA 02110-1301 \\
    USA
\end{quote}


\section{Availability}

This program is on CTAN\@; thus it can be found at any mirrors of those.
It is also part of TeX Live 2011.

\section{Installation}

A few words on installation on various platforms:

\begin{description}
\item[UNIX:] Type \Cmd{configure}, \Cmd{make} and finally
  \Cmd{make~install}. To make sure everything proceeded correctly,
  type \Cmd{make~check}.  If you don't have superuser privileges and thus
  access to the default system areas, you should type
  \Cmd{configure~-{}-help} to help you set up correct paths.

  If you haven't installed any software like this before, that is
  distributed in source form, here are some guidelines to help you
  install it locally at your account. Please note that a mail to the
  system administrator may be less work for you.

  We assume that you have put the archive (\Cmd{chktex.tar.gz}) in a
  subdir of yours, with path \Cmd{\~{}/tmp}. We further assume that
  your shell is \Cmd{csh} or \Cmd{tcsh}. Do the following:

  \begin{enumerate}
  \item First of all, unpack the archive contents.

\begin{verbatim}
> cd ~/tmp
> gunzip chktex.tar.gz
> tar xf chktex.tar
\end{verbatim}

  \item Now, we can configure the program.  There are some
    configuration options you should know about:
    \begin{description}
    \item[\Cmd{-{}-enable-pcre}:] Allows using PCRE (perl compatible
      regular expressions) for use defined warnings.  The default is
      to use PCRE if it is installed on your system as determined by
      \Cmd{pcre-config}.  You can use \Cmd{-{}-disable-pcre} if you
      plan to distribute this for systems in which you cannot ensure
      PCRE will be installed.

      User defined regular expressions are defined using
      \texttt{UserWarnRegex} in the \rsrc\ file.  See warning~44 for
      more information.

    \item[\Cmd{-{}-enable-lacheck-replace}] This enables a quick
      hack for using \chktex\ instead of lacheck. This is done by
      installing a stub script which ``overrides'' the original
      lacheck executable. In this way, tools which support lacheck
      can be easily made to support chktex instead.

    \item[\Cmd{-{}-enable-debug-info}] \chktex\ has an ability to spit
      out various diagnostic messages using the \Cmd{-d} flag. This
      behaviour is on by default. By adding the flag
      \Cmd{-{}-disable-debug-info} to the commandline, this will not be
      compiled in.

      This may be useful if you're running short of disk space (the
      time savings are neglible).
    \end{description}

    If you are installing the program on your local account, use the
    following command:

\begin{verbatim}
> configure --prefix ~/
\end{verbatim}

    Add eventual extra flags as specified above. This command will
    generate a significant amount of output, this can usually be ignored.

  \item Finally, we can just build the program and install it.

\begin{verbatim}
> make
> make install
\end{verbatim}

  \item Finished! The program is now installed and ready to use. You
    may now tell other people to put your bindir in their path in
    order to benefit from your work. All that remains is to make the
    shell aware of your installation.

\begin{verbatim}
> rehash
\end{verbatim}

    To make the remaining parts of your system aware of this, you'll
    have to log out and re-log in, I'm afraid. However, you should delay this
    until you've completed this installation procedure.

  \item If you wish to make sure that everything is OK (you ought to),
    you may now ask \chktex\ to do a self-test:

\begin{verbatim}
> make check
\end{verbatim}

  \end{enumerate}

\item[Other platforms:] First of all, you have to copy the
  \Cmd{config.h.in} file to a file named \Cmd{config.h}.  Then, edit
  it to reflect your system.  Do the same with \Cmd{OpSys.h} (this
  file has been reduced significantly).  If you wish, you may define
  \Cmd{DATADIR} to the path you want the global resource file to be
  put.

  Now, I would suggest that you take a peak at the \Cmd{OpSys.c}
  file, and edit it appropiately, for more
  comfort.  This should not be necessary, though, at least not the
  first time.

  Finally, you may now compile and link all \verb@.c@ files.  Do not
  forget to define \Cmd{HAVE\_CONFIG\_H} to 1 (on the command-line,
  for instance).  If the \Cmd{config.h} you wish to use has another
  name, define \Cmd{CONFIG\_H\_NAME} to that (in that case, don't
  define \Cmd{HAVE\_CONFIG\_H}).

  Put the directory path of the \rsrc\ file in a environment variable
  named \Cmd{CHKTEXRC}.  The files \Cmd{deweb.in} and \Cmd{chkweb}
  should be moved to a directory in your path.  These files may need
  further setup, as they haven't got the location of perl
  initialized.

  If your compiler/the compiled program complains (or crashes!), you
  may try the hints listed below.  Please note that it only makes
  sense to try these hints if your compiler fails to produce a working
  program.

  \begin{enumerate}
  \item Increase the preprocessor buffers and line buffers. The
    \chktex{} sources define macros sized 3--4k (expanding to about
    the same), and passes arguments sized about 1k.
  \item Use the magic switch which lets us use large
    \Cmd{switch(\dots)\{\dots\}} statements; some of these statements
    have about 120 \Cmd{case} entries.
  \item The sources require that at least the first 12 of each
    identifier is significant.
  \end{enumerate}
\end{description}
\paragraph{Note:} You \emph{must} install the new \rsrc\ file; \chktex\ will
fail to function otherwise!

    After   doing   this,   you   may  enhance  \chktex'  behaviour  by
reading/editing the \rsrc\ file.

%latex
\section{Usage}

\subsection{\chktex}

\subsubsection{Synopsis}

A UNIX-compliant template format follows:

\newcommand{\Group}[1]{\mbox{[#1]}}
\begin{tabularx}{.95\linewidth}{lY}
  \texttt{chktex} & \ttfamily \Group{-hiqrW} \Group{-v[0-\dots]} \Group{-l
    <rcfile>} \Group{-[wemn] <[1-42]|all>} \Group{-d[0-\ldots]} \Group{-p
    <pseudoname>} \Group{-o <outputfile>} \Group{-[btxgI][0|1]}
  file1 file2 \dots
\end{tabularx}


\subsubsection{Options}

These are the options \chktex\ currently accepts.
Please note that single-lettered options requiring a numerical or no
argument may be concatenated. E.g.\ saying \Cmd{-v0qb0w2} is the
same as saying \Cmd{-v0~-q~-b0~-w2}, except for being less to
type.

Enough general talk; here's a rather detailed description of all
options:
\begin{description}
\item[Misc.\ options:] General options which aren't related to some
  specific subpart of \chktex.
  \begin{description}
  \item[\texttt{-h [-{}-help]}] Gives you a command summary.
  \item[\texttt{-i [-{}-license]}] Shows distribution information.
  \item[\texttt{-l [-{}-localrc]}] Reads a resource-file formatted
    as the global resource-file \rsrc, in addition to the global
    resource-file. This option needs the name of the resource-file
    as a parameter. See also \texttt{-g}.
  \item[\texttt{-r [-{}-reset]}] This will reset all settings to their
    defaults. This may be useful if you use the \texttt{CMDLINE}
    directive in your \rsrc\ file, and wish to do something
    unusual.
  \item[\texttt{-d [-{}-debug]}] Needs a numeric argument; a bitmask
    telling what to output.  The values below may be added in order
    to output multiple debugging info.

    \begin{tabularx}\linewidth{cX}
      \bf Value & \bf Dumps\ldots\\
      1 & All warnings available and their current status. \\
      2 & Statistics for all lists in the resource file. \\
      4 & The contents of all lists in the resource file. \\
      8 & Misc.\ other status information. \\
      16 & Run-time info (note that this isn't widely used). \\
    \end{tabularx}
    The info is produced after all switches and resource files have
    been processed.

    It is possible to install versions of \chktex\ that ignore this
    flag; this means that it is not certain that this flag works.
  \item[\texttt{-W [-{}-version]}] Displays version information, and exits.
  \end{description}
\item[Muting warning messages:] Controls whether and in what form
  error messages will appear. Usually they accept a specific warning
  number (e.g.\ \Cmd{-w2}), but you may also say \Cmd{all} (e.g.\
  \Cmd{-wall}) which does the operation on \emph{all} warnings.
  \begin{description}
  \item[\texttt{-w [-{}-warnon]}] Makes the message number passed as
    parameter a warning and turns it on.
  \item[\texttt{-e [-{}-erroron]}] Makes the message number passed as
    parameter an error and turns it on.
  \item[\texttt{-m [-{}-msgon]}] Makes the message number passed as
    parameter a message and turns it on. Messages are not counted.
  \item[\texttt{-n [-{}-nowarn]}] Turns the warning/error number passed
    as a parameter off.
  \item[\texttt{-L [-{}-nolinesupp]}] Turns off suppression of messages
    on a per line basis.  This is meant to be used to ensure that no new
    errors have crept into a document while editing.
  \end{description}
\item[Output control flags:] Determines the appearance and
  destination of the error reports.
  \begin{description}
  \item[\texttt{-q [-{}-quiet]}] Shuts up about copyright information.
  \item[\texttt{-o [-{}-output]}] Normally, all errors are piped to \texttt{stdout}.
    Using this option with a parameter, errors will be sent to the
    named file instead. Only information relative to the \LaTeX\ file
    will be sent to that file. Memory problems and similar will as as
    always be sent to \texttt{stderr}. If a file with the name given
    already exists, it will be renamed to \Cmd{foobar.bak}
    (\Cmd{foobar.\$cl} under MS-DOS), \Cmd{foobar} being the name of
    the file.  See also \Cmd{-b}.

  \item[\texttt{-v [-{}-verbosity]}] Specifies how much and how you
    wish the error reports to be displayed. This is specified in the
    \rsrc\ file; we'll list the default values below. If you wish,
    you may thus edit the \rsrc\ file to add or modify new formats.

    The default is mode 1 (that is, the \emph{second} entry in the
    \rsrc\ file), using \texttt{-v} without any parameter will give you
    mode 2.

    \begin{description}
    \item[0] Will show the information in a way that should be
      suitable for further parsing by \texttt{awk}, \texttt{sed} or
      similar.  The format is as follows:
\begin{verbatim}
File:Line:Column:Warning number:Warning message
\end{verbatim}
      The colons may be replaced with another string; use the
      \verb@-s@ switch for this.

      As the program does not output all errors in quite order, this
      output format is also suitable for piping through \Cmd{sort}.
    \item[1] Shows the information in a way which is more
      comprehensible for humans, but which still doesn't need
      anything but a glass tty.
    \item[2] Shows the information in a fancy way, using escape
      codes and stuff. It is the indeed most readable of all
      modes; however, it needs proper set up of the \Cmd{ChkTeX.h}
      at compilation time. UNIX boxes, however, will find the
      information automatically.
    \item[3] Shows the information suitable for parsing by Emacs;
      this is the same format as \texttt{lacheck} uses. More formally,
      it is the following:
\begin{verbatim}
"File", line Line: Warning message
\end{verbatim}

      To utilize this, type \verb@M-x compile RET@. Delete whatever
      is written in the minibuffer, and type
      \verb@chktex -v3 texfile.tex@, and you should be able to
      browse through the
      error messages.  Use \verb@C-x `@ to parse the messages.
    \item[4] More or less the same as \verb@-v3@, but also includes
      information on where the error actually was found. Takes somewhat
      longer time to parse, but much more informative in use.
    \end{description}

  \item[\texttt{-f [-{}-format]}] Specifies the format of the output.
    This is done using a format similar to \Cmd{printf()}, where we
    support the specifiers listed below.

    \smallskip
    \newcommand{\Pf}[1]{\texttt{\%#1} &}
    \begin{tabularx}{\linewidth}{cX}
      \bf Code & \bf Description \\
      \Pf{b} String to print \textbf{b}etween fields (from \texttt{-s}
      option).\\
      \Pf{c} \textbf{C}olumn position of error. \\
      \Pf{d} Length of error (\textbf{d}igit). \\
      \Pf{f} Current \textbf{f}ilename.\\
      \Pf{i} Turn on \textbf{i}nverse printing mode.\\
      \Pf{I} Turn off \textbf{i}nverse printing mode.\\
      \Pf{k} \textbf{k}ind of error (warning, error, message).\\
      \Pf{l} \textbf{l}ine number of error.\\
      \Pf{m} Warning \textbf{m}essage.\\
      \Pf{n} Warning \textbf{n}umber.\\
      \Pf{u} An \textbf{u}nderlining line (like the one which
      appears when using \Cmd{-v1}).\\
      \Pf{r} Part of line in front of error ($\mbox{`S'} -
      1$).\\
      \Pf{s} Part of line which contains error (\textbf{s}tring).\\
      \Pf{t} Part of line after error ($\mbox{`S'} + 1$).
    \end{tabularx}
    \smallskip

    Other characters will be passed literally; thus you can say
    \Cmd{\%\%} to achieve a single percent sign in the output.
    Please note that we may introduce other specifiers in the future,
    so don't abuse this feature for other characters.

    Also, note that we do \emph{not} support field lengths (yet).
    This may come in the future, if I get the time\dots

    The \texttt{-v} command is implemented by indexing into the \rsrc\
    file; read that for seeing how each format is implemented. If
    you find yourself using a particular format often by using the
    -f switch, consider putting it in the \rsrc\ file instead.
  \item[\texttt{-V [-{}-pipeverb]}] Which entry we'll use in the \rsrc\
    file whenever \texttt{stdout} isn't a terminal.

    The default is to use the same mode as specified with the
    \texttt{-v} switch; using \texttt{-V} without any parameter will give you
    mode 1.

    This switch was implemented because GNU less has problems with
    the escape codes \chktex\ uses for displaying inverse text.
    Under UNIX, there's another way around, though, which is slightly
    more elegant. Add the following line to your \Cmd{.envir} file:
\begin{verbatim}
setenv LESS -r
\end{verbatim}

  \item[\texttt{-p [-{}-pseudoname]}] With this switch, you can provide
    the filename which will be used when we report the errors. This
    may be useful in scripts, especially when doing pipes. It is in
    other words similar to C's \verb@#line@ directive.

    We will only assume this name for the uppermost file; files that
    this one in turn \verb@\@\verb@input@ are presented under their original
    names. This seems most logical to me.

  \item[\texttt{-s [-{}-splitchar]}] String to use instead of the
    colons when doing \texttt{-v0}; e.g.\ this string will be output
    between the fields.

  \end{description}
\item[Boolean switches:] Common for all of these are that they
  take an optional parameter.  If it is \texttt{0}, the feature will
  be disabled, if it is \texttt{1}, it will be enabled. All these
  features are on by default; and are toggled if you don't give
  any parameter.

  \begin{description}
  \item[\texttt{-b [-{}-backup]}] If you use the \texttt{-o} switch, and the
    named outputfile exists, it will be renamed to \texttt{filename.bak}.
  \item[\texttt{-I [-{}-inputfiles]}] Execute \verb@\@\verb@input@
    statements; e.g.\ include the file in the input. Our input parsing
    does of course nest; we use an input-stack to keep track of this.
  \item[\texttt{-H [-{}-headererr]}] Show errors found in front of the
    \verb@\begin{document}@ line. Some people keep \emph{lots} of
    pure \TeX\ code there, which errors can't be detected reliably
    (in other words, we will in most cases just produce a lot of
    garbage).
  \item[\texttt{-g [-{}-globalrc]}] Read in the global resource file.  This
    switch may be useful together with the \texttt{-l} option.
  \item[\texttt{-t [-{}-tictoc]}] Display a twirling baton, to show that
    we're working. \texttt{-v0} does an \texttt{-t0}, too, as it assumes
    that the user then uses the program non-interactively.  This is
    now a no-op.
  \item[\texttt{-x [-{}-wipeverb]}] Ignore the ``\verb@\verb@'' command
    found within the \LaTeX\ file and its argument is completely by
    the checking routines.  This is done by simply overwriting them.
    If you somehow don't like that (for instance, you would like to
    count brackets inside those commands, too), use this switch.
  \end{description}
\end{description}


If you don't specify any input \LaTeX-files on the commandline, we'll
read from \texttt{stdin}.  To abort \texttt{stdin} input, press the
following keycombinations:

\smallskip
\begin{tabular}{ll}
  \bf Machine & \bf Key-combination \\
  UNIX & $\fbox{\texttt{Ctrl}} + \fbox{\texttt{D}}$ \\
  MS-DOS & $\fbox{\texttt{Ctrl}} + \fbox{Z}$, followed by return.
\end{tabular}
\smallskip

By default, we use GNU's \Cmd{getopt()} routine.

\begin{itemize}
\item Options may be given in any order; the names of the \LaTeX-files
  do not have to be the last arguments. This behaviour may be turned
  off by creating an environment variable named \Cmd{POSIXLY\_CORRECT}.
\item The special argument \Cmd{-{}-} forces an end of
  option-scanning.
\item Long-named options begin with \Cmd{-{}-} instead of \Cmd{-}.
  Their names may be abbreviated as long as the abbreviation is unique
  or is an exact match for some defined option. If they have an
  argument, it follows the option name in the argument, separated from
  the option name by a \Cmd{=}, or else the in next argument.
\end{itemize}

\subsubsection{The \rsrc\ file}

You should also take a look at the \rsrc\ file. As it is
self-documenting, you should be able to get the meaning of each
keyword by simply reading the file. In fact, since not all options
are described in this documentation it is necessary that you read
the \rsrc\ file in order to understand them all. The method for
\emph{finding it} has grown rather complex. An outline is given below.

If \chktex\ finds multiple files when searching, each and every one
will be read in the order specified below. The \Cmd{Keyword = \{ item
  item \dots \}} may thus be necessary to reset previously defined
lists.

In this list, \Cmd{\$foo} is assumed to be the environment variable
\Cmd{foo}:

\begin{enumerate}
\item First, we'll take a look at the directory which was specified as
  \Cmd{DATADIR} during compilation. On UNIX boxes, this usually
  evaluates to something similar to
  \Cmd{/usr/local/share/chktexrc}, under MS-DOS it is set
  to \Cmd{\BS{}emtex\BS{}data\BS{}chktexrc}.

\item Look in the following system directories:

  \begin{tabular}{ll}
    \bf Machine & \bf Directory \\
    UNIX        & \Cmd{\$HOME/.chktexrc} or \Cmd{\$LOGDIR/.chktexrc} \\
    MSDOS       & Program installation path
  \end{tabular}

\item Look for it in the directory pointed to by an environment
  variable, as specified in the table below:

  \begin{tabularx}\linewidth{lY}
    \bf Machine & \bf Directory \\
    UNIX & \Cmd{\$CHKTEXRC/.chktexrc} \\
    MSDOS &  \Cmd{\$CHKTEXRC\BS{}chktexrc}, \Cmd{\$CHKTEX\_HOME\BS
      chktexrc} or \Cmd{\$EMTEXDIR\BS{}data\BS{}chktexrc}
  \end{tabularx}

\item Look for it in the current directory. On UNIX boxes,
  we expect the filename to be \Cmd{.chktexrc}; on other machines
  \Cmd{chktexrc}.

\end{enumerate}

If you for some reason wish to undo what the previous files may have
done, you may say \Cmd{CmdLine \{ -g0 -r \}} somewhere in the \rsrc\
file; this will reset all previous settings.

\subsubsection{Per Line and File Suppressions}

There are many cases in which \chktex{} will give a warning about a
construct which, although it usually indicates a mistake, is
intentional.  In these cases it can be extremely annoying to have
this message appear everytime \chktex{} is run.  For this reason you
can use \LaTeX{} comments to suppress a certain message on a single
line.  This can be done by adding a (case-insensitive) comment at the
end of the line of the form
\begin{center}
  \verb+% chktex ##+
\end{center}
where \verb+##+ is the number of the message to be suppressed.
For example the line
\begin{center}
  \verb+$[0,\infty)$+\\*
\end{center}
will produce a warning (number 9) about mismatched \verb+]+ and \verb+)+.
However the lines
\begin{center}
  \verb+$[0,\infty)$ % chktex 9+\\*
  \verb+$[0,\infty)$ % ChkTeX 9+\\*
\end{center}
will not produce such a message.  In this case, message number 17 will
still appear at the end, stating that the numbers of \verb+]+ and
\verb+)+ don't match for the entire file.

To suppress two different errors on the same line you will need two
instances of \verb+chktex+ in the comment.  This format is a little
cumbersome, but it shouldn't be needed often, and hopefully will help
avoid accidental suppressions.
\begin{center}
  \verb+Jordan--H\"older on $[0,\infty)$ % chktex 8 chktex 9+\\*
\end{center}

One problem inherent in line-by-line suppressions is that during editing
another error of the same type may creep into the same line.  Therefore,
I suggest using the \texttt{-L} or \texttt{-{}-nolinesupp} option to
disallow line based suppressions once just before the document is finished.
At that point you should go back over all the warnings and decide if they
should be fixed.

In addition to line-specific suppressions, you can create a suppression which will be in effect for the remainder of the file.
This can be used, for example, to turn off warning 18 (about \verb+"+) in a file which uses a package (like \Cmd{babel}) where \verb+"+ is an active character.
The syntax is nearly the same, namely
\begin{center}
  \verb+% chktex-file ##+
\end{center}

\subsubsection{Hints}
I've tried to collect some advice that may be useful --- if you have a
favourite hint, feel free to send it to me!

\begin{itemize}
\item If you use \Cmd{german.sty} or several of \Cmd{babel} languages
  which use \verb+"+ as an active character; it may be wise to put \Cmd{-n18} in
  the \Cmd{CmdLine} entry in the \rsrc\ file. This will probably reduce
  the amount of false warnings significantly. Alternately, you can put
  \verb+% chktex-file 18+ in your files which use one of these packages so
  that other files will still have these checks performed.
\item Put \Cmd{-v} in the \Cmd{CmdLine} entry of the \rsrc\ file; this
  makes the fancy printing the default.
\item If you're working on a large project, it may pay off to make a
  local resource file which is included in addition to the global
  one. In this one, add the necessary info to reduce the amount of
  false warnings --- these usually don't do anything but hide the
  real warnings.
\item Create a total ignore environment, which \chktex\ will ignore
  completely. In here, you can place all that code which outsmarts
  \chktex\ completely. For instance, add the following lines at the top
  of your \LaTeX\ file:
\begin{verbatim}
% ChkTeX will ignore material within this environment
\newenvironment{ignore}{}{}
\end{verbatim}
  In addition, you should add the item \Cmd{ignore} to the \Cmd{VerbEnvir}
  entry in the \rsrc\ file.
\end{itemize}
\subsubsection{Bugs}

No fatal ones, I think, but the program currently has some problems when a
\LaTeX\ command/parameter stretch over a two lines --- some extra spaces
may be inserted into the input.  I regard the program as fairly well
tested; using the SAS/C \Cmd{cover} utility I was able to make sure that
approximately 95\% of the code has actually been run successfully in the
final version.  This does indeed leave some lines; most of these are
procedure terminating brackets or ``can't happen'' lines, though.

We've got some problems when isolating the arguments of a command.
Although improved, it will certainly fail in certain cases; \chktex\
can for instance not handle arguments stretching over two lines. This
also means that \Cmd{WIPEARG} entries in the \rsrc\ file will only
have the first half of their argument wiped if the argument stretches
over two lines. We will, however, take care not to wipe parenthesis
in such cases, in order to avoid false warnings.

Long lines are broken up into chunks and handled separately.  The exact
length is platform dependent, though is guaranteed to be at least 256 bytes.
The first portions of the line will have line numbers that are 1 less than
they should be.  Some errors can be missed and some can be added erroneously.
A warning will be issued if lines are too long.

Before submitting a bug report, please first see whether the problem can be
solved by editing the \rsrc\ file appropriately.



\subsection{ChkWEB}

This shell script is provided for checking CWEB files.  The template is
as follows:
\begin{verbatim}
chkweb [options] file1 file2 ...
\end{verbatim}
As you may see from the script, it is only a trivial interface towards
\texttt{deweb} and \chktex.  It does not support any individual options
on the command line --- all options found will be passed onto \chktex.
If \Cmd{-{}-} or a filename is found, the remaining parameters will be
ignored.
The  only  real  intelligence  it  features  is  that it will try to append
\verb@.w@ to filenames it can't find.

If no filenames are given, we will read from \texttt{stdin}.

\subsection{DeWEB}

This program strips away C code and CWEB commands from CWEB sources.
It is called with the following synopsis:

\begin{verbatim}
deweb file1 file2 ...
\end{verbatim}

\texttt{deweb} filters away all C \&\ CWEB commands from a CWEB source
code. This leaves only the \LaTeX\ code.  This stripped code, in turn,
may then be passed to a suitable syntax checker for \LaTeX, like
\chktex\ and \texttt{lacheck}, or spell-checkers like \texttt{ispell}.

When \texttt{deweb} strips away the C code from your CWEB source, it tries to
preserve line breaks.  This means that the error reports from {\it your
  favorite tool\/} will be correct regarding to line numbers.  In most
cases, the column position will also be correct.  This significantly
simplifies finding the errors in the \LaTeX\ source (in contrast to the
output from \texttt{cweave}, which output is truly difficult to figure
anything out from).

\texttt{deweb} accepts a list of filenames on the argument line, and will send
its output to \texttt{stdout}.  If no filenames are given, it will read from
stdin, acting as a filter.  No options are currently accepted.

Macho users may try to pipe the output from \texttt{deweb} directly into
\LaTeX, theoretically, this should work.  This would ease the debugging of
the \LaTeX\ code significantly, as when \LaTeX\ complains about wrong
syntax, you'll be able to find the erroneous line much more easily.  Don't
expect that the output looks very much like the final one, though.

\texttt{deweb} should now understand all correct \texttt{CWEB} opcodes.  If it
complains about not understanding a correct opcode, please inform the
author.

\subsubsection{Bugs}

\texttt{deweb} will not even \emph{compile} under Perl versions before perl
v5.  Unfortunately, this means that we can't even tell the user why we
failed; Perl will just complain about not being able to compile the
regexps.

\section{Explanation of error messages}
Below is a description of all error-messages \chktex\ outputs.
Error messages set in {\it italic type\/} are turned off by default.
Where margin paragraphs are listed in the text, they refer to the
keyword in the \rsrc\ file which controls the discussed warning.

\newcommand\Keyword[1]{\marginpar{\texttt{\hfill\\ #1}}}

\smallskip\pagebreak[2]
\Keyword{Silent}
\begin{errdesc}{Command terminated with space.}
  You tried to terminate a command with a blank space.  Usually, this
  is an error as these are ignored by \LaTeX. In most cases, you would
  like to have a real space there.

  You can also specify regular expressions to match commands which can
  safely be terminated with a space.  They are specified in the
  \rsrc\ file in \texttt{[]}, which in some other cases is used to
  indicate case-insensitive matching.  This is used for example to
  support the \verb+\startXXX+ macros of Con\TeX t.

  \begin{errexam}
    \verb@\LaTeX@\underline{\tt\ }\verb@is a typesetter.@ \\*
    \LaTeX is a typesetter. \\*
    \smallskip
    \verb@\LaTeX\ is a typesetter.@ \\*
    \LaTeX\ is a typesetter.  \\*
  \end{errexam}
\end{errdesc}

\Keyword{Linker}
\begin{errdesc}{Non-breaking space (`\~{}') should have been used.}
  When reading a document, it is not very pretty when references are
  split across lines.  If you use the \verb@~@ character, \LaTeX\ will
  assign a very high penalty for splitting a line at that point.
  \chktex\ issues this warning if you have forgot to do this.

  \begin{errexam}
    \verb@Please refer to figure@\underline{\tt\ }\verb@\ref{foo}.@ \\*
    Please refer to figure 11.                \\* % Gotta cheat here! :)
    \smallskip
    \verb@Please refer to figure~\ref{foo}.@ \\*
    Please refer to figure~11.  \\*
  \end{errexam}
\end{errdesc}

\begin{errdesc}{You should enclose the previous  parenthesis with `\{\}'.}

  This is a warning which you may ignore, but for maximum aestethic
  pleasure, you should enclose your bracket characters with `\{\}'s.

  \begin{errexam}
    \verb@$@\underline{\tt\ }\verb@[(ab)^{-1}]@\underline{\tt\ }\verb@\^{-2}$@ \\*
    $[(ab)^{-1}]^{-2}$ \\*
    \smallskip
    \verb@${[{(ab)}^{-1}]}^{-2}$@ \\*
    ${[(ab)^{-1}]}^{-2}$ \\*
  \end{errexam}
\end{errdesc}

\Keyword{Italic\\ItalCmd\\NonItalic}
\begin{errdesc}{Italic correction (`\BS/') found in non-italic
    buffer.}
  If you try to use the \verb@\/@ command when \chktex\ believes that
  the buffer is not outputted as italic, you'll get this warning.

  \begin{errexam}
    \verb@This is an@\underline{\tt\BS/}\verb@ example@ \\*
    This is an\/ example. \\*
    \smallskip
    \verb@This is an example.@ \\*
    This is an example. \\*
  \end{errexam}
\end{errdesc}

\Keyword{Italic\\ItalCmd\\NonItalic}
\begin{errdesc}{Italic correction (`\BS/') found more than once.}
  If the buffer is italic, and you try to use the \verb@\/@ command
  more than once, you'll get this warning.

  \begin{errexam}
    \verb@This {\it example\/@\underline{\tt\BS/}\verb@} is not amusing.@ \\*
    This {\it example\/\/} is not amusing. \\*
    \smallskip
    \verb@This {\it example\/} is not amusing.@  \\*
    This {\it example\/} is not amusing. \\*
  \end{errexam}
\end{errdesc}

\Keyword{Italic\\ItalCmd\\NonItalic}
\begin{errdesc}{No italic correction (`\BS/') found.}
  You get this error if \chktex\ believes that you are switching from
  italic to non-italic, and you've forgot to use the \verb@\/@ command
  to insert that extra little spacing. If you use the \Cmd{em} option,
  you may ignore this warning.

  \begin{errexam}
    \verb@This {\it example@\underline{\tt\ }\verb@} is not amusing, either.@ \\*
    This {\it example} is not amusing, either. \\*
    \smallskip
    \verb@This {\it example\/} is not amusing, either.@ \\*
    This {\it example\/} is not amusing, either. \\*
  \end{errexam}
\end{errdesc}

\Keyword{IJAccent}
\begin{errdesc}{Accent command `command' needs  use of `command'.}
  If you're using accenting commands, `i' and `j' should lose their
  dots before they get accented. This is accomplished by using the
  \verb@\i@, \verb@\j@, \verb@\imath@ and \verb@\jmath@ command.

  \begin{errexam}
    \verb@This is an example of use of accents: \'{@\underline{\tt i}\verb@}.@ \\*
    This is an example of use of accents: \'{i}. \\*
    \smallskip
    \verb@This is an example of use of accents: \'{\i}.@ \\*
    This is an example of use of accents: \'{\i}. \\*
  \end{errexam}
\end{errdesc}

\Keyword{HyphDash\\NumDash\\WordDash\\DashExcpt}
\begin{errdesc}{Wrong length of dash may have been used.}
  This warning suggests that a wrong number of dashes may have been
  used.  It does this by classifying the dash according to the the
  character in front and after the dashes.

  If they are of the same type, \chktex\ will determine which keyword
  to use in the \rsrc\ file. If not, it will shut up and accept that
  it doesn't know.

  \begin{tabular}{ll}
    \bf Character type & \bf Keyword in \rsrc\ file \\*
    Space & \texttt{WordDash} \\*
    Number & \texttt{NumDash} \\*
    Alphabetic character & \texttt{HyphDash} \\*
  \end{tabular}

  This is more or less correct, according to my references.  One
  complication is that most often a hyphen (single dash) is desired
  between letters, but occasionally an n-dash (double dash) is
  required.  This is the case for theorems named after two people
  e.g.\ Jordan--H\"older.  A hyphen would indicate that it was one
  person with a hyphenated name e.g.\ Gregorio Ricci-Curbastro.
  If this is rare enough, it can be dealt with via line based suppressions.
  However, exceptions can also be handled by adding them to the
  \texttt{DashExcpt} list.  The ``words'' in this list are
  considered to be correct regardless of any other settings.
  Adding \verb+Jordan--H\"older+ to this list will cause no warning
  to be issued.  There is still the problem that no warning will be
  raised for Jordan-H\"older (unless added explicitly via regular
  expression), so care must still be taken.

  Some manuals---particularly American manuals---also suggest
  \emph{not} adding space around an m-dash (triple dash).
  Hopefully this check can be improved even more (suggestions?).

  \begin{errexam}
    \verb@It wasn't anything @\underline{\tt-}\verb@ just a 2@\underline
    {\tt-{}-{}-}\verb@3 star@\underline{\tt-{}-}\verb@shots.@ \\*
    It wasn't anything - just a 2---3 star--shots. \\*
    \smallskip
    \verb@It wasn't anything --- just a 2--3 star-shots@ \\*
    It wasn't anything --- just a 2--3 star-shots. \\*
  \end{errexam}
\end{errdesc}


\fmted{`\%s' expected, found  `\%s'.}
\begin{errdesc}{Solo `\%s' found.}
  Either brackets or environments don't match.
  \chktex\ expects to find matching brackets/environments in the
  same order as their opposites were found, and no closing delimiters
  which haven't been preceded by an opening one.

  While bracket matching is not an explicit error, it is usually a
  sign that something is wrong.

\end{errdesc}

\Keyword{CenterDots\\LowDots}
\begin{errdesc}{You should use `\%s' to achieve  an ellipsis.}
  Simply typing three \Cmd{.} in a row will not give a perfect spacing
  between the dots.  The \verb@\ldots@ is much more suitable for this.
  Similar problems are noted for two periods in a row (instead of three)
  since lacheck does.

  In math mode, you should also distinguish between \verb@\cdots@ and
  \verb@\ldots@; take a look at the example below.

  \begin{errexam}
    \newcommand{\td}{\underline{\tt...}}
    \verb@Foo@\td\verb@bar. $1,@\td\verb@,3$. $1+@\td\verb@+3$. $1,@%
    \underline{\tt\BS{}cdots}\verb@,3$.@ \\*
    Foo...bar. $1,...,3$. $1+...+3$. $1,\cdots,3$.  \\*
    \smallskip
    \verb@Foo\dots bar. $1,\ldots,3$. $1+\cdots+3$. $1,\ldots,3$.@ \\*
    Foo\dots bar. $1,\ldots,3$. $1+\cdots+3$. $1,\ldots,3$. \\
  \end{errexam}
\end{errdesc}

\Keyword{Abbrev}
\begin{errdesc}{Interword spacing (`\BS\ ') should perhaps be used.}

  One of the specified abbreviations were found. Unless you have
  previously said \verb@\frenchspacing@, you'll have incorrect
  spacing, which one should avoid if possible.

  You can also specify case-insensitive abbreviations in \texttt{[]}, though
  only the first letter is actually case-insensitive.

  \begin{errexam}
    \verb@This is an example, i.e.@\underline{\tt\ }\verb@an demonstration.@ \\*
    This is an example, i.e. an demonstration.        \\*
    \smallskip
    \verb@This is an example, i.e.\ an demonstration.@   \\*
    This is an example, i.e.\ an demonstration.        \\*
  \end{errexam}
\end{errdesc}

\begin{errdesc}{Intersentence spacing (`\BS{}@') should perhaps be used.}

  \LaTeX' detection of whether a period ends a sentence or not, is
  only based upon the character in front of the period. If it's
  uppercase, it assumes that it does not end a sentence. While this
  may be correct in many cases, it may be incorrect in others.
  \chktex\ thus outputs this warning in every such case.

  \begin{errexam}
    \verb@I've seen an UFO!@\underline{\tt\ }\verb@Right over there!@ \\*
    I've seen an UFO! Right over there!        \\*
    \smallskip
    \verb+I've seen an UFO\@! Right over there!+ \\*
    I've seen an UFO\@! Right over there!        \\*
  \end{errexam}
\end{errdesc}

\begin{errdesc}{Could not find argument for  command.}

  \chktex\ will in some cases need the argument of a function to
  detect an error. As \chktex\ currently processes the \LaTeX\ file on
  a line-by-line basis, it won't find the argument if the command
  which needed it was on the previous line. On the other hand, this
  \emph{may} also be an error; you ought to check it to be safe.

  \begin{errexam}
    \verb@$\hat$@ \\*
    This will give a \LaTeX\ error\dots  \\*
    \smallskip
    \verb@$\hat{a}$@ \\*
    $\hat{a}$        \\*
  \end{errexam}
\end{errdesc}

\begin{errdesc}{No match found for `\%s'.}

  This warning is triggered if we find a single, \emph{opening}
  bracket or environment.  While bracket matching is not an explicit
  error, it is usually a sign that something is wrong.

\end{errdesc}

\Keyword{MathEnvir}
\begin{errdesc}{Mathmode still on at end of LaTeX  file.}
  This error is triggered if you at some point have turned on
  mathmode, and \chktex\ couldn't see that you remembered to turn it
  off.

\end{errdesc}

\begin{errdesc}{Number of `character' doesn't match the number of `character'.}

  Should be self-explanatory. \chktex\ didn't find the same number of
  an opening bracket as it found of a closing bracket.

\end{errdesc}

\begin{errdesc}{You should use either `` or '' as  an alternative to `\,"\,'.}
  Self-explanatory. Look in the example, and you'll understand why.

  \begin{errexam}
    \verb@This is an @\underline{\tt"}\verb@example@\underline{\tt"} \\*
    This is an "example" \\*
    \smallskip
    \verb@This is an ``example''@ \\*
    This is an ``example'' \\*
  \end{errexam}
\end{errdesc}

\begin{errdesc}{You should use "'" (ASCII 39)  instead  of
    "'" (ASCII 180).} On some keyboards you might get the wrong quote.
  This quote looks, IMHO, \emph{ugly} compared to the standard
  quotes, it doesn't even come out as a quote!  Just see in the
  example.


  \begin{errexam}
    \verb@``There@\underline{\tt '}\verb@s quotes and there@\underline{\tt  '}\verb@s quotes@
    \underline{\tt ''} \\* % ''
    ``There�s quotes and there�s quotes�� \\* % ''
    \smallskip
    \verb@``There's quotes and there's quotes''@ \\*
    ``There's quotes and there's quotes'' \\*
  \end{errexam}
\end{errdesc}

\Keyword{UserWarn}
\begin{errdesc}{User-specified pattern found: \%s.}
  A substring you've specified using \texttt{UserWarn} in the \rsrc\ file,
  has been found.  See also warning~44 which allows using regular
  expressions.  You can also specify case-insensitive versions in
  \texttt{[]}.
  % Normally I would use a ref here, but if the numbers change that would be
  % hugely backwards incompatible.  Also it would require adding special label code.
\end{errdesc}

\begin{errdesc*}{This command might not be intended.}
  I implemented this because a friend of mine kept on making these
  mistakes.  Easily done if you haven't gotten quite into the syntax
  of \LaTeX.

  \begin{errexam}
    \verb@\LaTeX\ is an extension of \TeX@\underline{\tt\BS.}\verb@ Right?@ \\*
    \LaTeX\ is an extension of \TeX\. Right? \\*
    \smallskip
    \verb@\LaTeX\ is an extension of \TeX. Right?@ \\*
    \LaTeX\ is an extension of \TeX. Right? \\*
  \end{errexam}
\end{errdesc*}

\begin{errdesc*}{Comment displayed.}
  \chktex\ dumps all comments it finds, which in some cases is useful.
  I usually keep all my notes in the comments, and like to review them
  before I ship the final version. For commenting out parts of the
  document, the \Cmd{comment} environment is better suited. Setting
  this warning allows you to see notes you have left in comments.
\end{errdesc*}


\begin{errdesc}{Either ''\BS,' or '\BS,'' will look  better.}

  This error is generated whenever you try to typeset three quotes in
  a row; this will not look pretty, and one of them should be
  separated from the rest.

  \begin{errexam}
    \underline{\tt```}\verb@Hello', I heard him said'', she remembered.@ \\*
    ```Hello', I heard him said'', she remembered. \\*
    \smallskip
    \verb@``\,`Hello', I heard him said'', she remembered.@ \\*
    ``\,`Hello', I heard him said'', she remembered.
  \end{errexam}
\end{errdesc}

\Keyword{PostLink}
\begin{errdesc}{Delete this space to maintain correct  pagereferences.}
  This message, issued when a space is found in front of a
  \verb@\index@, \verb@\label@ or similar command (can be set in the
  \rsrc\ file).  Sometimes, this space may cause that the word and the
  index happens on separate pages, if a pagebreak happens just there.

  Warning~42 is similar in that it warns about spaces in front of footnotes.
  The difference is that the warning text makes more sense for that case.

  \begin{errexam}
    \verb@Indexing text@\underline{\tt\ }\verb@\index{text} is fun!@ \\*
    \smallskip
    \verb@Indexing text\index{text} is fun!@ \\*
  \end{errexam}
\end{errdesc}

\begin{errdesc}{You might wish to put this between a pair of `\{\}'}

  This warning is given whenever \chktex\ finds a \Cmd{\^{ }}' or a
  \Cmd{\_} followed by either two or more numeric digits or two or
  more alphabetic characters.  In most situations, this means that
  you've forgotten some \{\}'s.

  \begin{errexam}
    \verb@$5\cdot10^@\underline{\tt10}\verb@$@ \\*
    $5\cdot10^10$ \\*
    \smallskip
    \verb@$5\cdot10^{10}$@ \\*
    $5\cdot10^{10}$
  \end{errexam}
\end{errdesc}

\begin{errdesc}{You ought to remove spaces in front of punctuation.}

  This warning is issued if \chktex\ finds space in front of an
  end-of-sentence character.

  \begin{errexam}
    \verb@Do you understand@\underline{\tt\ }\verb@?@ \\*
    Do you understand ? \\*
    \smallskip
    \verb@Do you understand?@ \\*
    Do you understand? \\*
  \end{errexam}
\end{errdesc}

\begin{errdesc}{Could not execute LaTeX command.}

  Some \LaTeX\ commands will be interpreted by \chktex; however, some
  of them are sensible to errors in the \LaTeX\ source. Most notably,
  the \verb@\@\verb@input@ command requires that the input file exist\dots

\end{errdesc}

\Keyword{Italic\\ItalCmd\\NonItalic}
\begin{errdesc}{Don't use \BS/ in front of small punctuation.}
  Italic correction should generally \emph{not} be used in front of
  small punctuation characters like `.' and `,'; as it looks better
  when the preceding italic character leans ``over'' the punctum or
  comma.

  \begin{errexam}
    \verb@It is just a {\it test@\underline{\tt\BS/}\verb@}, don't think anything else.@ \\*
    It is just a {\it test\/}, don't think anything else. \\*
    \smallskip
    \verb@It is just a {\it test}, don't think anything else.@ \\*
    It is just a {\it test}, don't think anything else.
  \end{errexam}
\end{errdesc}

\begin{errdesc}{\$\BS{}times\$ may look prettier here.}
  In ASCII environments, it is usual to use the `x' character as an
  infix operator to denote a dimension. The mathemathical symbol
  $\times$ provided by the \verb@$\times$@ command is better suited for
  this.

  \begin{errexam}
    \verb@The program opens a screen sized 640@\underline{\tt x}\verb@200 pixels.@ \\*
    The program opens a screen sized 640x200 pixels. \\*
    \smallskip
    \verb@The program opens a screen sized $640\times200$ pixels.@ \\*
    The program opens a screen sized $640\times200$ pixels.
  \end{errexam}
\end{errdesc}

\begin{errdesc*}{Multiple spaces detected in output.}

  This warning, intended for the novice, will remind you that even if
  you \emph{type} multiple spaces in your input, only a single space
  will come out. Some ways to come around this is listed below.

  \begin{errexam}
    \verb@White           is a beautiful colour.@ \\*
    White           is a beautiful colour. \\*
    \smallskip
    \verb@White~~~~~{ }{ }{ }\ \ \ is a beautiful colour.@ \\*
    White~~~~~{ }{ }{ }\ \ \ is a beautiful colour. \\
  \end{errexam}
\end{errdesc*}

\Keyword{VerbEnvir}
\begin{errdesc}{This text may be ignored.}
  Certain implementations of the \verb@verbatim@ environment and
  derivations of that, ignore all text on the same line as
  \verb@\end{verbatim}@.  This will warn you about this.


\end{errdesc}

\fmted{Use ` to begin quotation, not '.}\hfill\\
\fmted{Use ' to end quotation, not `.}\hfill\\
\begin{errdesc}{Don't mix quotes.}

  Proper quotations should start with a \verb@`@ and end with a
  \verb@'@; anything else isn't very pretty. Both these warnings are
  relative to this; look in the example below.

  \begin{errexam}
    \verb@There are @\underline{\tt`'}%
    \verb@examples'' and there are ``examples@\underline{\tt``}\verb@.@ \\*
    There are `'examples'' and there are ``examples``. \\*
    \smallskip
    \verb@There are ``examples'' and there are ``examples''.@ \\*
    There are ``examples'' and there are ``examples''.
  \end{errexam}
\end{errdesc}

\Keyword{MathRoman}
\begin{errdesc}{You should perhaps use `cmd' instead.}
  Most mathematical operators should be set as standard roman font,
  instead of the math italic \LaTeX\ uses for variables. For many
  operators, \LaTeX\ provides a pre-defined command which will typeset
  the operator correctly. Look below for an illustration of the point.

  \begin{errexam}
    \verb@$@\underline{\tt sin}\verb@^2 x + @\underline{\tt cos}\verb@^2 x = 1$@ \\*
    $sin^2 x + cos^2 x= 1$ \\*
    \smallskip
    \verb@$\sin^2 x + \cos^2 x = 1$@ \\*
    $\sin^2 x + \cos^2 x = 1$
  \end{errexam}
\end{errdesc}

\fmted{You should put a space in front of/after parenthesis.}\hfill\\
\begin{errdesc}{You should avoid spaces in front of/after parenthesis.}
  Outside math mode, you should put a space in front of any group of
  opening parenthesis, and no spaces after. If you have several after
  each other, you should of course not put a space in between each;
  look in the example below.  Likewise, there should not be spaces in
  front of closing parenthesis, but there should be at least one
  after.



  \begin{errexam}
    \verb@This@\underline{\tt( }\verb@an example@\underline{\tt( }%
    \verb@Nuff said@\underline{\tt\ }\verb@)), illustrates@\underline{\tt( }%
    \verb@``my''@\underline{\tt\ )}\verb@point.@\\
    This( an example( Nuff said )), illustrates( ``my'' )point. \\
    \smallskip
    \verb@This (an example (Nuff said)), illustrates (``my'') point.@\\
    This (an example (Nuff said)), illustrates (``my'') point.\\
  \end{errexam}
\end{errdesc}

\Keyword{QuoteStyle}
\begin{errdesc}{You should not use punctuation in front of/after
    quotes.}
                                %
  For best looking documents, you should decide on how you
  wish to put quotes relative to punctuation. \chktex\ recognizes two
  styles; you may specify which you use in the \rsrc\ file. A
  description on each style follows:
  \begin{description}
  \item[Traditional:] This style is the most visually pleasing. It
    always puts the punctuation \emph{in front of} the quotes, which
    gives a continuous bottom line.

    However, it may in certain cases be ambigious. Consider the
    following example from a fictious \Cmd{vi(1)}
    tutorial (quote taken from the Jargon file):
    \begin{center}
      \verb@Then delete a line from the file by typing ``dd.''@ \\*
      Then delete a line from the file by typing ``dd.''
    \end{center}
    That would be very bad --- because the reader would be prone to
    type the string d-d-dot, and it happens that in \Cmd{vi(1)} dot
    repeats the last command accepted. The net result would be to
    delete \emph{two} lines! This problem is avoided using logical
    style, described below.
    \pagebreak[3]
  \item[Logical:] This style uses quotes as balanced delimiters like
    parentheses. While this is not the most visual pleasing, it is
    can't be misunderstood. The above sentence would then become:
    \nopagebreak
    \begin{center}
      \verb@Then delete a line from the file by typing ``dd''.@ \\*
      Then delete a line from the file by typing ``dd''.
    \end{center}
    \nopagebreak
  \end{description}

\end{errdesc}

\begin{errdesc}{Double space found.}
  This warning is triggered whenever \chktex\ finds a space in front
  of a hard space, or vice versa. This will be rendered as two spaces
  (which you usually don't wish).

  \begin{errexam}
    \verb@For output codes, see table@\underline{\tt\ }%
    \verb@~@\underline{\tt\ }\verb@\ref{foo}.@ \\*
    For output codes, see table ~ 1.1.\\*
    \smallskip
    \verb@For output codes, see table~\ref{foo}.@ \\*
    For output codes, see table~1.1.
  \end{errexam}
\end{errdesc}

\Keyword{MathEnvir}
\begin{errdesc}{You should put punctuation outside inner/inside
    display math mode.}
  As recommended in the \TeX{}book, you should try to put punctuation
  outside inner math mode, as this is gets formatted better.

  Similarily, you should let any final punctuation in display math
  mode end up within it. Look at the following example, which was
  taken from the \TeX{}book:
  \begin{errexam}
    \verb@for $x = a@\underline{\tt,}\verb@b$, or $c$.@\\*
    for $x = a,b$, or $c$. \\*
    \smallskip
    \verb@for $x = a$, $b$, or $c$.@\\*
    for $x = a$, $b$, or $c$.\\*
  \end{errexam}

\end{errdesc}

\Keyword{Primitives}
\begin{errdesc*}{You ought to not use primitive TeX in LaTeX code.}
  This warning is triggered whenever you use a raw \TeX\ command
  which has been replaced by a \LaTeX\ equivalent. If you consider
  yourself a purist (or want to be sure your code works under \LaTeX3),
  you should use the \LaTeX\ equivalent.
\end{errdesc*}

\Keyword{NotPreSpaced}
\begin{errdesc}{You should remove spaces in front of `\%s'}

  Some commands should not be prepended by a space character, for cosmetical
  reasons.  This notes you of this whenever this has happened.

  \begin{errexam}
    \verb@This is a footnote@\underline{\tt\ }\verb@\footnotemark[1] mark.@\\*
    This is a footnote ${}^1$ mark. \\*
    \smallskip
    \verb@This is a footnote\footnotemark[1] mark.@\\*
    This is a footnote${}^1$ mark. \\*
  \end{errexam}
\end{errdesc}

\Keyword{NoCharNext}
\begin{errdesc}{`\%s' is normally not followed by `\%c'.}
  \LaTeX' error message when calling \verb@\left \{@ instead of
  \verb@left \{@ is unfortunately rather poor. This warning detects
  this and similar errors.
\end{errdesc}

\Keyword{UserWarnRegex}
\begin{errdesc}{User Regex:\ \%s.}
  A pattern you've specified using \texttt{UserWarnRegex} in the \rsrc\ file,
  has been found.  See also warning~20 which allows specification of simple
  string matching.

  Depending on how \chktex\ was configured, you can use either PCRE regular
  expressions, POSIX extended regular expressions, or none at all.
  A warning will be issued if \chktex\ was built without regular expression
  support, but you try to use one.

  By default the matching portion of the line is printed to help distinguish
  between user specified regular expressions.  However, if the regular
  expression begins with a PCRE comment (which has a syntax of
  \verb+(?#+~\dots~\verb+)+), then that comment will be printed instead.
  This can be used to remind yourself why you were searching for the problem
  or how to fix it.  This applies even if POSIX regular expressions are used
  since \chktex\ itself parses a single initial PCRE-style comment.

  \emph{Note:} If a regular expression (not a comment) starts with
  \texttt{PCRE:} or \texttt{POSIX:} it will be used only if support for that
  regular expression engine has been compiled in.  It is primarily meant to
  make testing easier but, can be used to allow better regular expressions
  if PCRE is available.  If you want a regular expression that starts with
  \texttt{PCRE:} or \texttt{POSIX:} then you can enclose one of the
  characters in brackets like \texttt{[P]CRE:}.

  An example, included in the \rsrc\ file, is given below.  Remember that you
  have to escape (with~\verb+!+) spaces and \verb+#+ as well as a few other
  characters.  One should always use \verb+\nmid+ instead of \verb+\not\mid+
  because the results are much better.
  \begin{errexam}
    \verb+\\not! *(\||\\mid)+\\*
    \verb+User Regex: \not\mid.+\\*
  \end{errexam}
  or with an initial comment
  \begin{errexam}
    \verb+(?!#Always! use! \nmid)\\not! *(\||\\mid)+\\*
    \verb+User Regex: Always use \nmid.+
  \end{errexam}

  You can use \verb+% chktex 44+ to suppress user regular expression
  warnings on a given line, but this is often undesirable since all such
  warnings are suppressed this way.  For this reason you can ``name'' user
  regular expression warnings with negative numbers.  For example
  \verb+% chktex 4+ will suppress the system warning number 4, but
  \verb+% chktex -4+ will suppress the user regular expression warning
  number 4.  Since one might wish to add, remove, or rearrange user warnings
  in the \rsrc\ file, you must explicitly name particular warnings rather
  than relying on position in that file.

  In order to name one, include an initial PCRE-style comment with the first
  characters being a number (positive or negative---the absolute value will
  be used).  The numbers are limited by the number of bits in a \texttt{long},
  usually giving 1--63 as possible names.  You can give more than one regular
  expression the same name, and suppressing that name will suppress all
  regular expressions with that name.

  Using the example from before, all of the following will be suppressed with
  \verb+% chktex -4+.  Note that the name \emph{will} be printed as written
  so that you know which number to suppress.
  \begin{errexam}
    \verb+(?!#4:Always! use! \nmid)\\not! *(\||\\mid)+\\*
    \verb+(?!#-4Always! use! \nmid)\\not! *(\||\\mid)+\\*
    \verb+(?!#-4! Always! use! \nmid)\\not! *(\||\\mid)+\\*
  \end{errexam}
\end{errdesc}

\section{Future plans}

In a somewhat prioritized sequence, this is what I'd like to put into the
program --- if I have the time.

\begin{itemize}
\item De-linearize the checker. Currently, it works on a line-by-line
  basis, in most respects, at least. I hope to be able to remove this
  barrier; as this will reduce the amount of false warnings
  somewhat.

\item Probably some more warnings/errors; just have to think them out
  first.  Suggestions are appreciated --- I've ``stolen'' most that
  similar programs provides, and am running out of ideas, really.

  It would also be nice to investigate the field of ``globally''
  oriented warnings; i.e.\ warnings regarding the document as a
  whole. Currently, \chktex\ operates mainly on a local/``greedy''
  basis.

  If you have suggestions/ideas on this topic, they're certainly
  welcome, including references to literature.

\item Fix a few more bugs.
\end{itemize}

\section{Notes}

\subsection{Wish to help?}

As most other living creatures, I have only a limited amount of time. If
you like \chktex\ and would like to help improving it, here's a few things
I would like to receive. The following ideas are given:

\begin{itemize}
\item Does anyone have a $\mbox{\LaTeX}\rightarrow \mbox{\texttt{troff}}$
  conversion program? It would be really nice if I could extract the
  relevant sections from this manual, and present them as a man page.
  I will not, however, convert this manual to \TeX{}info in order to
  be able to do this; IMHO \TeX{}info documents have far too limited
  typographic possibilities.

  This doesn't mean that I'm not willing to restructure the document
  at all. This manual already uses some kind of preprocessing in order
  to achieve HTML output via \LaTeX2\texttt{html}, I'm willing to do the
  same in order to produce \texttt{troff} output.

\item Help me port the program! This is a prioritized one. It's no fun
  writing ANSI C when people haven't got a C compiler.

  Of course, I'll provide whatever help necessary to modify the sources
  to fit to the new platform. Take contact if you're interested. I will
  include your compiled binary in the distribution, and give you
  credit where appropiate.

  Just one request: If you have to modify the sources in order to make
  \chktex\ compile \& work on the new platform, \emph{please} enclose your
  changes in something like \Cmd{\#ifdef \_\_PLATFORM\_\_\dots code\dots\#endif}!
  It makes life so much easier later, when we try to merge the two
  source trees.

\item Reports on problems configuring and compiling \chktex\ on supported
  (and unsupported) systems are welcomed.

\item Filters for other file formats. I do believe that there are
  several formats using \LaTeX\ for its formatting purposes, combining
  that with something else. If you can write a program or script which
  filters everything away but the \LaTeX\ code, it will surely be
  appreciated (and included). Look at the \verb@deweb@ script to see
  what I mean.

\item Interfaces for other editors are also welcomed.

\item If you update the \rsrc\ file in anyway that is not strictly
  local, I would appreciate to receive your updated version.

\item Suggestions for new warnings are always welcomed. Both formal
  (i.e.\ regexps or similar) and non-formal (plain English) descriptions
  are welcomed.
\end{itemize}

Of course, people doing any of this will be mentioned in this document, and
thus receive eternal glory and appreciation.

\subsection{Caps and stuff}

Where trademarks have been used, the author is aware of that they
belong to someone, and has tried to stick to the original caps.

\section{About the author}

A quick summary of who I am and what I do:

I'm 21 years old, and live in Oslo, the capital of Norway.  I'm
currently studying maths and computer science at the
University~of~Oslo; planning to get a degree within mathematical
modeling, with a dash of physics and emphazing the computer part of
the study.  More precisely, in autumn'96 my studies consist of
mathematical analysis, statistics \& probability calculations plus
studying the relationship between society and computers.

At home I now possess 4 computers, of which 1 is regular use: A
vanilla Amiga 1200, expanded only by a HD\@.  The others are a
\texttt{80286} PC and an Amiga 500, both semi-out-of-order.  The last
one is a Commodore VIC-20, which for some peculiar reason never seems
to be used. Plans are to get a Linux-capable PC, though.

Most of the time in front of these computers (including SGI Indy's and
SPARC stations at our university) is spent on C and shell programming,
plus some text-processing.

                                % I am also involved in writing the document
                                % for {\sc Isaac} --- Interactive Simulation as an Alternative to
                                % Advanced Calculations.  This is planned to help newcomers to physics,
                                % by providing a computer program which enables one to simulate most
                                % experiments relating to classical mechanics.
                                %

C and shell programming are not my only knowledge areas regarding
computers, however.  I write the following languages more or less:
Perl, Motorola \texttt{68000} assembly code, ARexx, Simula, C++, \LaTeX,
HTML, AmigaGuide, Amos Basic and Installer LISP\@.  Once I also
mastered Commodore Basic V2, the ``language'' included with my VIC-20.

However, I also try to not to end up as a computer nerd.  Thus, in
addition to the compulsory (?) interest for computers, I am a scout.
Still running into the woods, climbing the trees, falling down and
climbing up once more, in other words.  To be more specific, I am a
now a troop leader for `Ulven' scout-group; Norwegian Scouts
Association.  I am also a active rover in `V{\aa}lerenga' scout-group.

Certainly a lot more to tell (I play the piano and like cross-country
skiing, for instance); but I'll stop here before you fall
asleep\dots


\section{Thanks}

The author wishes to thank the following people (in alphabetical order):

\def\Name#1#2{%
\item[]
  \setbox0=\hbox{
    \begin{tabular}{l}
      \textbf{#1} \\
      \texttt{#2} \\
    \end{tabular}
    } \usebox0\\ }

\begin{description}

  \Name{Russ Bubley}{russ@scs.leeds.ac.uk}
  He has been the main external beta-tester for this program, sending
  me loads and loads of understandable and reproducible bug reports.
  If you somehow think that \chktex\ is well-behaved and free from
  bugs, send warm thoughts to Russ. He has also provided ideas for
  enhanced checks and so forth.

  In addition, he sent me a huge list of 238 common English
  abbreviations, for inclusion in the \rsrc\ file! Together with the
  enhanced abbreviation recognizer, I do now believe most
  abbreviations should be caught\dots

  Finally, he has also given me valuable hints for improving the
  program's outputting routine, and given me lots of suggestions for
  filtering unnecessary/false warnings away.

  \Name{Gerd B\"ohm}{Gerd.Boehm@physik.uni-regensburg.de}
  Improved and bug-fixed the MS-DOS port of \chktex\ v1.4, sending me
  ready-to-yank code patches. The original port didn't respect all
  the peculiarities of the MS-DOS file-system, unfortunately.

  \Name{Antonio DiCesare}{dicesare@vodafone.it}
  He provided many feature requests and bug reports for the 1.7.1
  version making it a much better release than it would have otherwise
  been.  He also helped expand several keywords in the \rsrc\ file.

  \Name{Mojca Miklavec}{mojca.miklavec.lists@gmail.com}
  Found and helped debug a problem (fixed in 1.7.2) occurring only on
  some platforms, 32 bit Macs for one.

  \Name{Baruch Even}{chktex@ev-en.org}
  Maintainer of \chktex\ for about a decade.

  \Name{Lars Frellesen}{frelle@math-tech.dk} Sent a few bug reports
  regarding the filtering of messages. He has also helped me to
  expand the \Cmd{SILENT} keyword in the \rsrc\ file.

  \Name{Wolfgang Fritsch}{fritsch@hmi.de}
  Author of the OS/2 port, which he did using the emx compiler.
  Please direct questions regarding strictly to that port to him (I
  would like to receive a carbon copy, though).

  \Name{Stefan  Gerberding}{stefan@inferenzsysteme.informatik.th-darmstadt.de}
  First one to report the Enforcer hit in v1.2 when using \chktex\ as
  a pipe.  Also came with suggestions to make \chktex\ more easily
  compile on early gcc compilers.

  He has also kept on beta-testing later versions of \chktex, giving
  me bug-reports and enhancements requests.

  \Name{Kasper B. Graversen}{kbg2001@internet.dk} Lots of creative
  suggestions and improvements.  Several of the warnings implemented
  were based on his ideas. In addition, he has given advice for
  improving the existing warnings.

  Has also provided some OS-oriented code.

  \Name{Frank Luithle}{f\_luithle@outside.sb.sub.de}
  Wrote a translation for v1.0.  Unfortunately, he remained unreachable
  after that\dots:-/

  \Name{Nat}{nat@nataa.frmug.fr.net}
  Reported the same bug as Gerberding.  In addition, he taught me a
  few tricks regarding the use of gcc + made me understand that the
  ANSI standard isn't unambigious; at least the \verb@getenv()@ call
  seem to be open for interpretations.  Many possible
  incompatibilities have been removed due to these lessons.

  \Name{Michael Sanders}{sanders@umich.edu}
  Has found some of the bugs in this beast; both obscure and
  long-lived. Has also provided motivation to clarify this document.

  \Name{Bj\o rn Ove Thue}{bjort@ifi.uio.no}
  Author of the MSDOS port; please direct questions regarding
  strictly to that port to him (I would like to receive a carbon
  copy, though).

  \Name{Martin Ward}{Martin.Ward@durham.ac.uk}
  Sent a few bug-reports; also gave me information upon where to find
  regexp code. He also provided a Perl script for checking ordinary
  text, which ideas I was able to implement in \chktex. In addition,
  he sent me the source code for \verb@lacheck@; which also inspired some
  of the warnings.
\end{description}

%endlatex
\section{Contacting the author}

If you wish to contact me for any reason or would like to participate in
the development of \chktex, please write to:
%latex
\begin{samepage}
%endlatex
  \begin{quote}
    Jens Berger           \\
    Spektrumvn. 4         \\
    N-0666 Oslo           \\
    Norway                \\
    E-mail: \texttt{<jensthi@ifi.uio.no>}
  \end{quote}
%latex
\end{samepage}
%endlatex
Any signs of intelligent life are welcomed; that should exclude piracy.

Since the original author is unreachable, the maintainer these days is:
%latex
\begin{samepage}
%endlatex
  \begin{quote}
    Ivan Andrus     \\
    E-mail: \texttt{<darthandrus@gmail.com>}
  \end{quote}
%latex
\end{samepage}
%endlatex

\medskip\noindent
Have fun.

\end{document}

% The "Make" target is my own.
% Local Variables:
% TeX-command-default: "Make"
% TeX-master: "ChkTeX.tex"
% End:
