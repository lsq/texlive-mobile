#define EXTERN extern
#include "uptexd.h"

void 
println ( void ) 
{
  println_regmem 
  integer ii  ;
  switch ( selector ) 
  {case 19 : 
    {
      if ( nrestmultichr ( kcodepos ) > 0 ) 
      {register integer for_end; ii = 0 ;for_end = nrestmultichr ( kcodepos 
      ) - 1 ; if ( ii <= for_end) do 
	{
	  putc ( ' ' ,  stdout );
	  putc ( ' ' ,  logfile );
	} 
      while ( ii++ < for_end ) ;} 
      putc ('\n',  stdout );
      putc ('\n',  logfile );
      termoffset = 0 ;
      fileoffset = 0 ;
    } 
    break ;
  case 18 : 
    {
      if ( nrestmultichr ( kcodepos ) > 0 ) 
      {register integer for_end; ii = 0 ;for_end = nrestmultichr ( kcodepos 
      ) - 1 ; if ( ii <= for_end) do 
	putc ( ' ' ,  logfile );
      while ( ii++ < for_end ) ;} 
      putc ('\n',  logfile );
      fileoffset = 0 ;
    } 
    break ;
  case 17 : 
    {
      if ( nrestmultichr ( kcodepos ) > 0 ) 
      {register integer for_end; ii = 0 ;for_end = nrestmultichr ( kcodepos 
      ) - 1 ; if ( ii <= for_end) do 
	putc ( ' ' ,  stdout );
      while ( ii++ < for_end ) ;} 
      putc ('\n',  stdout );
      termoffset = 0 ;
    } 
    break ;
  case 16 : 
  case 20 : 
  case 21 : 
    ;
    break ;
    default: 
    putc ('\n',  writefile [selector ]);
    break ;
  } 
  kcodepos = 0 ;
} 
void 
zprintchar ( ASCIIcode s ) 
{
  /* 10 */ printchar_regmem 
  if ( s == eqtb [28512 ].cint ) {
      
    if ( selector < 20 ) 
    {
      println () ;
      return ;
    } 
  } 
  if ( ( kcodepos == 1 ) || ( ( kcodepos >= 9 ) && ( kcodepos <= 10 ) ) || ( ( 
  kcodepos >= 17 ) && ( kcodepos <= 19 ) ) ) 
  incr ( kcodepos ) ;
  else if ( iskanji1 ( xchr [s ]) ) 
  {
    if ( ( ismultichr ( 4 , 1 , xchr [s ]) ) ) 
    kcodepos = 17 ;
    else if ( ( ismultichr ( 3 , 1 , xchr [s ]) ) ) 
    kcodepos = 9 ;
    else kcodepos = 1 ;
    if ( ( selector == 19 ) || ( selector == 18 ) ) {
	
      if ( fileoffset >= maxprintline - nrestmultichr ( kcodepos ) ) 
      {
	putc ('\n',  logfile );
	fileoffset = 0 ;
      } 
    } 
    if ( ( selector == 19 ) || ( selector == 17 ) ) {
	
      if ( termoffset >= maxprintline - nrestmultichr ( kcodepos ) ) 
      {
	putc ('\n',  stdout );
	termoffset = 0 ;
      } 
    } 
  } 
  else kcodepos = 0 ;
  switch ( selector ) 
  {case 19 : 
    {
      putc ( Xchr (s ),  stdout );
      incr ( termoffset ) ;
      if ( termoffset == maxprintline ) 
      {
	putc ('\n',  stdout );
	termoffset = 0 ;
      } 
      putc ( Xchr (s ),  logfile );
      incr ( fileoffset ) ;
      if ( fileoffset == maxprintline ) 
      {
	putc ('\n',  logfile );
	fileoffset = 0 ;
      } 
    } 
    break ;
  case 18 : 
    {
      putc ( Xchr (s ),  logfile );
      incr ( fileoffset ) ;
      if ( fileoffset == maxprintline ) 
      println () ;
    } 
    break ;
  case 17 : 
    {
      putc ( Xchr (s ),  stdout );
      incr ( termoffset ) ;
      if ( termoffset == maxprintline ) 
      println () ;
    } 
    break ;
  case 16 : 
    ;
    break ;
  case 20 : 
    if ( tally < trickcount ) 
    {
      trickbuf [tally % errorline ]= s ;
      trickbuf2 [tally % errorline ]= kcodepos ;
    } 
    break ;
  case 21 : 
    {
      if ( poolptr < poolsize ) 
      {
	strpool [poolptr ]= s ;
	incr ( poolptr ) ;
      } 
    } 
    break ;
    default: 
    putc ( Xchr (s ),  writefile [selector ]);
    break ;
  } 
  incr ( tally ) ;
} 
void 
zprint ( integer s ) 
{
  /* 10 */ print_regmem 
  poolpointer j  ;
  integer nl  ;
  if ( s >= strptr ) 
  s = 260 ;
  else if ( s < 256 ) {
      
    if ( s < 0 ) 
    s = 260 ;
    else {
	
      if ( selector > 20 ) 
      {
	printchar ( s ) ;
	return ;
      } 
      if ( ( s == eqtb [28512 ].cint ) ) {
	  
	if ( selector < 20 ) 
	{
	  println () ;
	  return ;
	} 
      } 
      nl = eqtb [28512 ].cint ;
      eqtb [28512 ].cint = -1 ;
      j = strstart [s ];
      while ( j < strstart [s + 1 ]) {
	  
	printchar ( strpool [j ]) ;
	incr ( j ) ;
      } 
      eqtb [28512 ].cint = nl ;
      return ;
    } 
  } 
  j = strstart [s ];
  while ( j < strstart [s + 1 ]) {
      
    printchar ( strpool [j ]) ;
    incr ( j ) ;
  } 
} 
void 
zslowprint ( integer s ) 
{
  slowprint_regmem 
  poolpointer j  ;
  if ( ( s >= strptr ) || ( s < 256 ) ) 
  print ( s ) ;
  else {
      
    j = strstart [s ];
    while ( j < strstart [s + 1 ]) {
	
      print ( strpool [j ]) ;
      incr ( j ) ;
    } 
  } 
} 
void 
zprintnl ( strnumber s ) 
{
  printnl_regmem 
  if ( ( ( termoffset > 0 ) && ( odd ( selector ) ) ) || ( ( fileoffset > 0 ) 
  && ( selector >= 18 ) ) ) 
  println () ;
  print ( s ) ;
} 
void 
zprintesc ( strnumber s ) 
{
  printesc_regmem 
  integer c  ;
  c = eqtb [28508 ].cint ;
  if ( c >= 0 ) {
      
    if ( c < 256 ) 
    print ( c ) ;
  } 
  slowprint ( s ) ;
} 
void 
zprintthedigs ( eightbits k ) 
{
  printthedigs_regmem 
  while ( k > 0 ) {
      
    decr ( k ) ;
    if ( dig [k ]< 10 ) 
    printchar ( 48 + dig [k ]) ;
    else printchar ( 55 + dig [k ]) ;
  } 
} 
void 
zprintint ( integer n ) 
{
  printint_regmem 
  unsigned char k  ;
  integer m  ;
  k = 0 ;
  if ( n < 0 ) 
  {
    printchar ( 45 ) ;
    if ( n > -100000000L ) 
    n = - (integer) n ;
    else {
	
      m = -1 - n ;
      n = m / 10 ;
      m = ( m % 10 ) + 1 ;
      k = 1 ;
      if ( m < 10 ) 
      dig [0 ]= m ;
      else {
	  
	dig [0 ]= 0 ;
	incr ( n ) ;
      } 
    } 
  } 
  do {
      dig [k ]= n % 10 ;
    n = n / 10 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  printthedigs ( k ) ;
} 
void 
zprintcs ( integer p ) 
{
  printcs_regmem 
  if ( p < 514 ) {
      
    if ( p >= 257 ) {
	
      if ( p == 513 ) 
      {
	printesc ( 539 ) ;
	printesc ( 540 ) ;
	printchar ( 32 ) ;
      } 
      else {
	  
	printesc ( p - 257 ) ;
	if ( eqtb [25636 + p - 257 ].hh .v.RH == 11 ) 
	printchar ( 32 ) ;
      } 
    } 
    else if ( p < 1 ) 
    printesc ( 541 ) ;
    else print ( p - 1 ) ;
  } 
  else if ( ( ( p >= 24526 ) && ( p <= 29572 ) ) || ( p > eqtbtop ) ) 
  printesc ( 541 ) ;
  else if ( ( hash [p ].v.RH >= strptr ) ) 
  printesc ( 542 ) ;
  else {
      
    printesc ( hash [p ].v.RH ) ;
    printchar ( 32 ) ;
  } 
} 
void 
zsprintcs ( halfword p ) 
{
  sprintcs_regmem 
  if ( p < 514 ) {
      
    if ( p < 257 ) 
    print ( p - 1 ) ;
    else if ( p < 513 ) 
    printesc ( p - 257 ) ;
    else {
	
      printesc ( 539 ) ;
      printesc ( 540 ) ;
    } 
  } 
  else printesc ( hash [p ].v.RH ) ;
} 
void 
zprintfilename ( integer n , integer a , integer e ) 
{
  printfilename_regmem 
  boolean mustquote  ;
  poolpointer j  ;
  mustquote = false ;
  if ( a != 0 ) 
  {
    j = strstart [a ];
    while ( ( ! mustquote ) && ( j < strstart [a + 1 ]) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
  } 
  if ( n != 0 ) 
  {
    j = strstart [n ];
    while ( ( ! mustquote ) && ( j < strstart [n + 1 ]) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
  } 
  if ( e != 0 ) 
  {
    j = strstart [e ];
    while ( ( ! mustquote ) && ( j < strstart [e + 1 ]) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
  } 
  if ( mustquote ) 
  printchar ( 34 ) ;
  if ( a != 0 ) 
  {register integer for_end; j = strstart [a ];for_end = strstart [a + 1 
  ]- 1 ; if ( j <= for_end) do 
    if ( strpool [j ]!= 34 ) 
    print ( strpool [j ]) ;
  while ( j++ < for_end ) ;} 
  if ( n != 0 ) 
  {register integer for_end; j = strstart [n ];for_end = strstart [n + 1 
  ]- 1 ; if ( j <= for_end) do 
    if ( strpool [j ]!= 34 ) 
    print ( strpool [j ]) ;
  while ( j++ < for_end ) ;} 
  if ( e != 0 ) 
  {register integer for_end; j = strstart [e ];for_end = strstart [e + 1 
  ]- 1 ; if ( j <= for_end) do 
    if ( strpool [j ]!= 34 ) 
    print ( strpool [j ]) ;
  while ( j++ < for_end ) ;} 
  if ( mustquote ) 
  printchar ( 34 ) ;
} 
void 
zprintsize ( integer s ) 
{
  printsize_regmem 
  if ( s == 0 ) 
  printesc ( 431 ) ;
  else if ( s == 16 ) 
  printesc ( 432 ) ;
  else printesc ( 433 ) ;
} 
void 
zprintwritewhatsit ( strnumber s , halfword p ) 
{
  printwritewhatsit_regmem 
  printesc ( s ) ;
  if ( mem [p + 1 ].hh .v.LH < 16 ) 
  printint ( mem [p + 1 ].hh .v.LH ) ;
  else if ( mem [p + 1 ].hh .v.LH == 16 ) 
  printchar ( 42 ) ;
  else printchar ( 45 ) ;
} 
void 
zprintcsnames ( integer hstart , integer hfinish ) 
{
  printcsnames_regmem 
  integer c, h  ;
  fprintf ( stderr , "%s%ld%s%ld%c\n",  "fmtdebug:csnames from " , (long)hstart , " to " , (long)hfinish ,   ':' ) ;
  {register integer for_end; h = hstart ;for_end = hfinish ; if ( h <= 
  for_end) do 
    {
      if ( hash [h ].v.RH > 0 ) 
      {
	{register integer for_end; c = strstart [hash [h ].v.RH ];
	for_end = strstart [hash [h ].v.RH + 1 ]- 1 ; if ( c <= for_end) 
	do 
	  {
	    putbyte ( strpool [c ], stderr ) ;
	  } 
	while ( c++ < for_end ) ;} 
	{ putc ( '|' ,  stderr );  putc ( '\n',  stderr ); }
      } 
    } 
  while ( h++ < for_end ) ;} 
} 
void 
printfileline ( void ) 
{
  printfileline_regmem 
  integer level  ;
  level = inopen ;
  while ( ( level > 0 ) && ( fullsourcefilenamestack [level ]== 0 ) ) decr ( 
  level ) ;
  if ( level == 0 ) 
  printnl ( 263 ) ;
  else {
      
    printnl ( 344 ) ;
    print ( fullsourcefilenamestack [level ]) ;
    print ( 58 ) ;
    if ( level == inopen ) 
    printint ( line ) ;
    else printint ( linestack [level + 1 ]) ;
    print ( 607 ) ;
  } 
} 
void 
zprintdir ( eightbits dir ) 
{
  printdir_regmem 
  if ( dir == 4 ) 
  printchar ( 89 ) ;
  else if ( dir == 3 ) 
  printchar ( 84 ) ;
  else if ( dir == 1 ) 
  printchar ( 68 ) ;
} 
void 
zprintdirection ( integer d ) 
{
  printdirection_regmem 
  switch ( abs ( d ) ) 
  {case 4 : 
    print ( 1121 ) ;
    break ;
  case 3 : 
    print ( 1120 ) ;
    break ;
  case 1 : 
    print ( 1122 ) ;
    break ;
  } 
  if ( d < 0 ) 
  print ( 1438 ) ;
  print ( 1439 ) ;
} 
void 
zprintkanji ( KANJIcode s ) 
{
  printkanji_regmem 
  s = toBUFF ( s % 16777216L ) ;
  if ( BYTE1 ( s ) != 0 ) 
  printchar ( BYTE1 ( s ) ) ;
  if ( BYTE2 ( s ) != 0 ) 
  printchar ( BYTE2 ( s ) ) ;
  if ( BYTE3 ( s ) != 0 ) 
  printchar ( BYTE3 ( s ) ) ;
  printchar ( BYTE4 ( s ) ) ;
} 
integer 
zcheckkcatcode ( integer ct ) 
{
  register integer Result; checkkcatcode_regmem 
  if ( ( ( ct >= 16 ) && ( eqtb [25635 ].hh .v.RH == 0 ) ) || ( eqtb [25635 
  ].hh .v.RH == 2 ) ) 
  Result = 1 ;
  else Result = 0 ;
  return Result ;
} 
integer 
zcheckecharrange ( integer c ) 
{
  register integer Result; checkecharrange_regmem 
  if ( ( c >= 0 ) && ( c < 256 ) ) 
  Result = 1 ;
  else Result = 0 ;
  return Result ;
} 
#ifdef TEXMF_DEBUG
#endif /* TEXMF_DEBUG */
void 
jumpout ( void ) 
{
  jumpout_regmem 
  closefilesandterminate () ;
  {
    fflush ( stdout ) ;
    readyalready = 0 ;
    if ( ( history != 0 ) && ( history != 1 ) ) 
    uexit ( 1 ) ;
    else uexit ( 0 ) ;
  } 
} 
void 
error ( void ) 
{
  /* 22 10 */ error_regmem 
  ASCIIcode c  ;
  integer s1, s2, s3, s4  ;
  if ( history < 2 ) 
  history = 2 ;
  printchar ( 46 ) ;
  showcontext () ;
  if ( ( haltonerrorp ) ) 
  {
    history = 3 ;
    jumpout () ;
  } 
  if ( interaction == 3 ) 
  while ( true ) {
      
    lab22: clearforerrorprompt () ;
    {
      ;
      print ( 265 ) ;
      terminput () ;
    } 
    if ( last == first ) 
    return ;
    c = buffer [first ];
    if ( c >= 97 ) 
    c = c - 32 ;
    switch ( c ) 
    {case 48 : 
    case 49 : 
    case 50 : 
    case 51 : 
    case 52 : 
    case 53 : 
    case 54 : 
    case 55 : 
    case 56 : 
    case 57 : 
      if ( deletionsallowed ) 
      {
	s1 = curtok ;
	s2 = curcmd ;
	s3 = curchr ;
	s4 = alignstate ;
	alignstate = 1000000L ;
	OKtointerrupt = false ;
	if ( ( last > first + 1 ) && ( buffer [first + 1 ]>= 48 ) && ( 
	buffer [first + 1 ]<= 57 ) ) 
	c = c * 10 + buffer [first + 1 ]- 48 * 11 ;
	else c = c - 48 ;
	while ( c > 0 ) {
	    
	  gettoken () ;
	  decr ( c ) ;
	} 
	curtok = s1 ;
	curcmd = s2 ;
	curchr = s3 ;
	alignstate = s4 ;
	OKtointerrupt = true ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 278 ;
	  helpline [0 ]= 279 ;
	} 
	showcontext () ;
	goto lab22 ;
      } 
      break ;
	;
#ifdef TEXMF_DEBUG
    case 68 : 
      {
	debughelp () ;
	goto lab22 ;
      } 
      break ;
#endif /* TEXMF_DEBUG */
    case 69 : 
      if ( baseptr > 0 ) 
      {
	editnamestart = strstart [inputstack [baseptr ].namefield ];
	editnamelength = strstart [inputstack [baseptr ].namefield + 1 ]- 
	strstart [inputstack [baseptr ].namefield ];
	editline = line ;
	jumpout () ;
      } 
      break ;
    case 72 : 
      {
	if ( useerrhelp ) 
	{
	  giveerrhelp () ;
	  useerrhelp = false ;
	} 
	else {
	    
	  if ( helpptr == 0 ) 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 280 ;
	    helpline [0 ]= 281 ;
	  } 
	  do {
	      decr ( helpptr ) ;
	    print ( helpline [helpptr ]) ;
	    println () ;
	  } while ( ! ( helpptr == 0 ) ) ;
	} 
	{
	  helpptr = 4 ;
	  helpline [3 ]= 282 ;
	  helpline [2 ]= 281 ;
	  helpline [1 ]= 283 ;
	  helpline [0 ]= 284 ;
	} 
	goto lab22 ;
      } 
      break ;
    case 73 : 
      {
	beginfilereading () ;
	if ( last > first + 1 ) 
	{
	  curinput .locfield = first + 1 ;
	  buffer [first ]= 32 ;
	} 
	else {
	    
	  {
	    ;
	    print ( 277 ) ;
	    terminput () ;
	  } 
	  curinput .locfield = first ;
	} 
	first = last ;
	curinput .limitfield = last - 1 ;
	return ;
      } 
      break ;
    case 81 : 
    case 82 : 
    case 83 : 
      {
	errorcount = 0 ;
	interaction = 0 + c - 81 ;
	print ( 272 ) ;
	switch ( c ) 
	{case 81 : 
	  {
	    printesc ( 273 ) ;
	    decr ( selector ) ;
	  } 
	  break ;
	case 82 : 
	  printesc ( 274 ) ;
	  break ;
	case 83 : 
	  printesc ( 275 ) ;
	  break ;
	} 
	print ( 276 ) ;
	println () ;
	fflush ( stdout ) ;
	return ;
      } 
      break ;
    case 88 : 
      {
	interaction = 2 ;
	jumpout () ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    {
      print ( 266 ) ;
      printnl ( 267 ) ;
      printnl ( 268 ) ;
      if ( baseptr > 0 ) 
      print ( 269 ) ;
      if ( deletionsallowed ) 
      printnl ( 270 ) ;
      printnl ( 271 ) ;
    } 
  } 
  incr ( errorcount ) ;
  if ( errorcount == 100 ) 
  {
    printnl ( 264 ) ;
    history = 3 ;
    jumpout () ;
  } 
  if ( interaction > 0 ) 
  decr ( selector ) ;
  if ( useerrhelp ) 
  {
    println () ;
    giveerrhelp () ;
  } 
  else while ( helpptr > 0 ) {
      
    decr ( helpptr ) ;
    printnl ( helpline [helpptr ]) ;
  } 
  println () ;
  if ( interaction > 0 ) 
  incr ( selector ) ;
  println () ;
} 
void 
zfatalerror ( strnumber s ) 
{
  fatalerror_regmem 
  normalizeselector () ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 286 ) ;
  } 
  {
    helpptr = 1 ;
    helpline [0 ]= s ;
  } 
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
void 
zoverflow ( strnumber s , integer n ) 
{
  overflow_regmem 
  normalizeselector () ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 287 ) ;
  } 
  print ( s ) ;
  printchar ( 61 ) ;
  printint ( n ) ;
  printchar ( 93 ) ;
  {
    helpptr = 2 ;
    helpline [1 ]= 288 ;
    helpline [0 ]= 289 ;
  } 
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
void 
zconfusion ( strnumber s ) 
{
  confusion_regmem 
  normalizeselector () ;
  if ( history < 2 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 290 ) ;
    } 
    print ( s ) ;
    printchar ( 41 ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 291 ;
    } 
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 292 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 293 ;
      helpline [0 ]= 294 ;
    } 
  } 
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
boolean 
initterminal ( void ) 
{
  /* 10 */ register boolean Result; initterminal_regmem 
  topenin () ;
  if ( last > first ) 
  {
    curinput .locfield = first ;
    while ( ( curinput .locfield < last ) && ( buffer [curinput .locfield ]
    == ' ' ) ) incr ( curinput .locfield ) ;
    if ( curinput .locfield < last ) 
    {
      Result = true ;
      return Result ;
    } 
  } 
  while ( true ) {
      
    ;
    Fputs ( stdout ,  "**" ) ;
    fflush ( stdout ) ;
    if ( ! inputln ( stdin , true ) ) 
    {
      putc ('\n',  stdout );
      fprintf ( stdout , "%s\n",  "! End of file on the terminal... why?" ) ;
      Result = false ;
      return Result ;
    } 
    curinput .locfield = first ;
    while ( ( curinput .locfield < last ) && ( buffer [curinput .locfield ]
    == 32 ) ) incr ( curinput .locfield ) ;
    if ( curinput .locfield < last ) 
    {
      Result = true ;
      return Result ;
    } 
    fprintf ( stdout , "%s\n",  "Please type the name of your input file." ) ;
  } 
  return Result ;
} 
strnumber 
makestring ( void ) 
{
  register strnumber Result; makestring_regmem 
  if ( strptr == maxstrings ) 
  overflow ( 259 , maxstrings - initstrptr ) ;
  incr ( strptr ) ;
  strstart [strptr ]= poolptr ;
  Result = strptr - 1 ;
  return Result ;
} 
boolean 
zstreqbuf ( strnumber s , integer k ) 
{
  /* 45 */ register boolean Result; streqbuf_regmem 
  poolpointer j  ;
  boolean result  ;
  j = strstart [s ];
  while ( j < strstart [s + 1 ]) {
      
    if ( strpool [j ]!= buffer [k ]) 
    {
      result = false ;
      goto lab45 ;
    } 
    incr ( j ) ;
    incr ( k ) ;
  } 
  result = true ;
  lab45: Result = result ;
  return Result ;
} 
boolean 
zstreqstr ( strnumber s , strnumber t ) 
{
  /* 45 */ register boolean Result; streqstr_regmem 
  poolpointer j, k  ;
  boolean result  ;
  result = false ;
  if ( ( strstart [s + 1 ]- strstart [s ]) != ( strstart [t + 1 ]- 
  strstart [t ]) ) 
  goto lab45 ;
  j = strstart [s ];
  k = strstart [t ];
  while ( j < strstart [s + 1 ]) {
      
    if ( strpool [j ]!= strpool [k ]) 
    goto lab45 ;
    incr ( j ) ;
    incr ( k ) ;
  } 
  result = true ;
  lab45: Result = result ;
  return Result ;
} 
strnumber 
zsearchstring ( strnumber search ) 
{
  /* 40 */ register strnumber Result; searchstring_regmem 
  strnumber result  ;
  strnumber s  ;
  integer len  ;
  result = 0 ;
  len = ( strstart [search + 1 ]- strstart [search ]) ;
  if ( len == 0 ) 
  {
    result = 344 ;
    goto lab40 ;
  } 
  else {
      
    s = search - 1 ;
    while ( s > 255 ) {
	
      if ( ( strstart [s + 1 ]- strstart [s ]) == len ) {
	  
	if ( streqstr ( s , search ) ) 
	{
	  result = s ;
	  goto lab40 ;
	} 
      } 
      decr ( s ) ;
    } 
  } 
  lab40: Result = result ;
  return Result ;
} 
strnumber 
slowmakestring ( void ) 
{
  /* 10 */ register strnumber Result; slowmakestring_regmem 
  strnumber s  ;
  strnumber t  ;
  t = makestring () ;
  s = searchstring ( t ) ;
  if ( s > 0 ) 
  {
    {
      decr ( strptr ) ;
      poolptr = strstart [strptr ];
    } 
    Result = s ;
    return Result ;
  } 
  Result = t ;
  return Result ;
} 
void 
zprinttwo ( integer n ) 
{
  printtwo_regmem 
  n = abs ( n ) % 100 ;
  printchar ( 48 + ( n / 10 ) ) ;
  printchar ( 48 + ( n % 10 ) ) ;
} 
void 
zprinthex ( integer n ) 
{
  printhex_regmem 
  unsigned char k  ;
  k = 0 ;
  printchar ( 34 ) ;
  do {
      dig [k ]= n % 16 ;
    n = n / 16 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  printthedigs ( k ) ;
} 
void 
zprintromanint ( integer n ) 
{
  /* 10 */ printromanint_regmem 
  poolpointer j, k  ;
  nonnegativeinteger u, v  ;
  j = strstart [261 ];
  v = 1000 ;
  while ( true ) {
      
    while ( n >= v ) {
	
      printchar ( strpool [j ]) ;
      n = n - v ;
    } 
    if ( n <= 0 ) 
    return ;
    k = j + 2 ;
    u = v / ( strpool [k - 1 ]- 48 ) ;
    if ( strpool [k - 1 ]== 50 ) 
    {
      k = k + 2 ;
      u = u / ( strpool [k - 1 ]- 48 ) ;
    } 
    if ( n + u >= v ) 
    {
      printchar ( strpool [k ]) ;
      n = n + u ;
    } 
    else {
	
      j = j + 2 ;
      v = v / ( strpool [j - 1 ]- 48 ) ;
    } 
  } 
} 
void 
printcurrentstring ( void ) 
{
  printcurrentstring_regmem 
  poolpointer j  ;
  j = strstart [strptr ];
  while ( j < poolptr ) {
      
    printchar ( strpool [j ]) ;
    incr ( j ) ;
  } 
} 
void 
terminput ( void ) 
{
  terminput_regmem 
  integer k  ;
  fflush ( stdout ) ;
  if ( ! inputln ( stdin , true ) ) 
  fatalerror ( 262 ) ;
  termoffset = 0 ;
  decr ( selector ) ;
  if ( last != first ) 
  {register integer for_end; k = first ;for_end = last - 1 ; if ( k <= 
  for_end) do 
    print ( buffer [k ]) ;
  while ( k++ < for_end ) ;} 
  println () ;
  incr ( selector ) ;
} 
void 
zinterror ( integer n ) 
{
  interror_regmem 
  print ( 285 ) ;
  printint ( n ) ;
  printchar ( 41 ) ;
  error () ;
} 
void 
normalizeselector ( void ) 
{
  normalizeselector_regmem 
  if ( logopened ) 
  selector = 19 ;
  else selector = 17 ;
  if ( jobname == 0 ) 
  openlogfile () ;
  if ( interaction == 0 ) 
  decr ( selector ) ;
} 
void 
pauseforinstructions ( void ) 
{
  pauseforinstructions_regmem 
  if ( OKtointerrupt ) 
  {
    interaction = 3 ;
    if ( ( selector == 18 ) || ( selector == 16 ) ) 
    incr ( selector ) ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 295 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 296 ;
      helpline [1 ]= 297 ;
      helpline [0 ]= 298 ;
    } 
    deletionsallowed = false ;
    error () ;
    deletionsallowed = true ;
    interrupt = 0 ;
  } 
} 
integer 
zhalf ( integer x ) 
{
  register integer Result; half_regmem 
  if ( odd ( x ) ) 
  Result = ( x + 1 ) / 2 ;
  else Result = x / 2 ;
  return Result ;
} 
scaled 
zrounddecimals ( smallnumber k ) 
{
  register scaled Result; rounddecimals_regmem 
  integer a  ;
  a = 0 ;
  while ( k > 0 ) {
      
    decr ( k ) ;
    a = ( a + dig [k ]* 131072L ) / 10 ;
  } 
  Result = ( a + 1 ) / 2 ;
  return Result ;
} 
void 
zprintscaled ( scaled s ) 
{
  printscaled_regmem 
  scaled delta  ;
  if ( s < 0 ) 
  {
    printchar ( 45 ) ;
    s = - (integer) s ;
  } 
  printint ( s / 65536L ) ;
  printchar ( 46 ) ;
  s = 10 * ( s % 65536L ) + 5 ;
  delta = 10 ;
  do {
      if ( delta > 65536L ) 
    s = s - 17232 ;
    printchar ( 48 + ( s / 65536L ) ) ;
    s = 10 * ( s % 65536L ) ;
    delta = delta * 10 ;
  } while ( ! ( s <= delta ) ) ;
} 
scaled 
zmultandadd ( integer n , scaled x , scaled y , scaled maxanswer ) 
{
  register scaled Result; multandadd_regmem 
  if ( n < 0 ) 
  {
    x = - (integer) x ;
    n = - (integer) n ;
  } 
  if ( n == 0 ) 
  Result = y ;
  else if ( ( ( x <= ( maxanswer - y ) / n ) && ( - (integer) x <= ( maxanswer 
  + y ) / n ) ) ) 
  Result = n * x + y ;
  else {
      
    aritherror = true ;
    Result = 0 ;
  } 
  return Result ;
} 
scaled 
zxovern ( scaled x , integer n ) 
{
  register scaled Result; xovern_regmem 
  boolean negative  ;
  negative = false ;
  if ( n == 0 ) 
  {
    aritherror = true ;
    Result = 0 ;
    texremainder = x ;
  } 
  else {
      
    if ( n < 0 ) 
    {
      x = - (integer) x ;
      n = - (integer) n ;
      negative = true ;
    } 
    if ( x >= 0 ) 
    {
      Result = x / n ;
      texremainder = x % n ;
    } 
    else {
	
      Result = - (integer) ( ( - (integer) x ) / n ) ;
      texremainder = - (integer) ( ( - (integer) x ) % n ) ;
    } 
  } 
  if ( negative ) 
  texremainder = - (integer) texremainder ;
  return Result ;
} 
scaled 
zxnoverd ( scaled x , integer n , integer d ) 
{
  register scaled Result; xnoverd_regmem 
  boolean positive  ;
  nonnegativeinteger t, u, v  ;
  if ( x >= 0 ) 
  positive = true ;
  else {
      
    x = - (integer) x ;
    positive = false ;
  } 
  t = ( x % 32768L ) * n ;
  u = ( x / 32768L ) * n + ( t / 32768L ) ;
  v = ( u % d ) * 32768L + ( t % 32768L ) ;
  if ( u / d >= 32768L ) 
  aritherror = true ;
  else u = 32768L * ( u / d ) + ( v / d ) ;
  if ( positive ) 
  {
    Result = u ;
    texremainder = v % d ;
  } 
  else {
      
    Result = - (integer) u ;
    texremainder = - (integer) ( v % d ) ;
  } 
  return Result ;
} 
halfword 
zbadness ( scaled t , scaled s ) 
{
  register halfword Result; badness_regmem 
  integer r  ;
  if ( t == 0 ) 
  Result = 0 ;
  else if ( s <= 0 ) 
  Result = 10000 ;
  else {
      
    if ( t <= 7230584L ) 
    r = ( t * 297 ) / s ;
    else if ( s >= 1663497L ) 
    r = t / ( s / 297 ) ;
    else r = t ;
    if ( r > 1290 ) 
    Result = 10000 ;
    else Result = ( r * r * r + 131072L ) / 262144L ;
  } 
  return Result ;
} 
#ifdef TEXMF_DEBUG
void 
zprintword ( memoryword w ) 
{
  printword_regmem 
  printint ( w .cint ) ;
  printchar ( 32 ) ;
  printscaled ( w .cint ) ;
  printchar ( 32 ) ;
  printscaled ( round ( 65536L * w .gr ) ) ;
  println () ;
  printint ( w .hh .v.LH ) ;
  printchar ( 61 ) ;
  printint ( w .hh.b0 ) ;
  printchar ( 58 ) ;
  printint ( w .hh.b1 ) ;
  printchar ( 59 ) ;
  printint ( w .hh .v.RH ) ;
  printchar ( 32 ) ;
  printint ( w .qqqq .b0 ) ;
  printchar ( 58 ) ;
  printint ( w .qqqq .b1 ) ;
  printchar ( 58 ) ;
  printint ( w .qqqq .b2 ) ;
  printchar ( 58 ) ;
  printint ( w .qqqq .b3 ) ;
} 
#endif /* TEXMF_DEBUG */
void 
zshowtokenlist ( integer p , integer q , integer l ) 
{
  /* 10 */ showtokenlist_regmem 
  integer m, c  ;
  ASCIIcode matchchr  ;
  ASCIIcode n  ;
  matchchr = 35 ;
  n = 48 ;
  tally = 0 ;
  while ( ( p != -1073741823L ) && ( tally < l ) ) {
      
    if ( p == q ) 
    {
      firstcount = tally ;
      kcp = trickbuf2 [( firstcount - 1 ) % errorline ];
      if ( ( firstcount > 0 ) && ( kcp > 0 ) ) 
      firstcount = firstcount + nrestmultichr ( kcp ) ;
      trickcount = firstcount + 1 + errorline - halferrorline ;
      if ( trickcount < errorline ) 
      trickcount = errorline ;
    } 
    if ( ( p < himemmin ) || ( p > memend ) ) 
    {
      printesc ( 313 ) ;
      return ;
    } 
    if ( mem [p ].hh .v.LH >= 536870911L ) 
    printcs ( mem [p ].hh .v.LH - 536870911L ) ;
    else {
	
      if ( checkkanji ( mem [p ].hh .v.LH ) ) 
      {
	m = mem [p ].hh .v.LH / 16777216L ;
	c = mem [p ].hh .v.LH % 16777216L ;
      } 
      else {
	  
	m = mem [p ].hh .v.LH / 256 ;
	c = mem [p ].hh .v.LH % 256 ;
      } 
      if ( ( m < 16 ) && ( c > 256 ) ) 
      printesc ( 593 ) ;
      else switch ( m ) 
      {case 16 : 
      case 17 : 
      case 18 : 
      case 19 : 
	printkanji ( c ) ;
	break ;
      case 1 : 
      case 2 : 
      case 3 : 
      case 4 : 
      case 7 : 
      case 8 : 
      case 10 : 
      case 11 : 
      case 12 : 
	print ( c ) ;
	break ;
      case 6 : 
	{
	  print ( c ) ;
	  print ( c ) ;
	} 
	break ;
      case 5 : 
	{
	  print ( matchchr ) ;
	  if ( c <= 9 ) 
	  printchar ( c + 48 ) ;
	  else {
	      
	    printchar ( 33 ) ;
	    return ;
	  } 
	} 
	break ;
      case 13 : 
	{
	  matchchr = c ;
	  print ( c ) ;
	  incr ( n ) ;
	  printchar ( n ) ;
	  if ( n > 57 ) 
	  return ;
	} 
	break ;
      case 14 : 
	print ( 594 ) ;
	break ;
	default: 
	printesc ( 593 ) ;
	break ;
      } 
    } 
    p = mem [p ].hh .v.RH ;
  } 
  if ( p != -1073741823L ) 
  printesc ( 592 ) ;
} 
void 
runaway ( void ) 
{
  runaway_regmem 
  halfword p  ;
  if ( scannerstatus > 1 ) 
  {
    switch ( scannerstatus ) 
    {case 2 : 
      {
	printnl ( 608 ) ;
	p = defref ;
      } 
      break ;
    case 3 : 
      {
	printnl ( 609 ) ;
	p = memtop - 3 ;
      } 
      break ;
    case 4 : 
      {
	printnl ( 610 ) ;
	p = memtop - 4 ;
      } 
      break ;
    case 5 : 
      {
	printnl ( 611 ) ;
	p = defref ;
      } 
      break ;
    } 
    printchar ( 63 ) ;
    println () ;
    showtokenlist ( mem [p ].hh .v.RH , -1073741823L , errorline - 10 ) ;
  } 
} 
halfword 
getavail ( void ) 
{
  register halfword Result; getavail_regmem 
  halfword p  ;
  p = avail ;
  if ( p != -1073741823L ) 
  avail = mem [avail ].hh .v.RH ;
  else if ( memend < memmax ) 
  {
    incr ( memend ) ;
    p = memend ;
  } 
  else {
      
    decr ( himemmin ) ;
    p = himemmin ;
    if ( himemmin <= lomemmax ) 
    {
      runaway () ;
      overflow ( 299 , memmax + 1 - memmin ) ;
    } 
  } 
  mem [p ].hh .v.RH = -1073741823L ;
	;
#ifdef STAT
  incr ( dynused ) ;
#endif /* STAT */
  Result = p ;
  return Result ;
} 
void 
zflushlist ( halfword p ) 
{
  flushlist_regmem 
  halfword q, r  ;
  if ( p != -1073741823L ) 
  {
    r = p ;
    do {
	q = r ;
      r = mem [r ].hh .v.RH ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } while ( ! ( r == -1073741823L ) ) ;
    mem [q ].hh .v.RH = avail ;
    avail = p ;
  } 
} 
halfword 
zgetnode ( integer s ) 
{
  /* 40 10 20 */ register halfword Result; getnode_regmem 
  halfword p  ;
  halfword q  ;
  integer r  ;
  integer t  ;
  lab20: p = rover ;
  do {
      q = p + mem [p ].hh .v.LH ;
    while ( ( mem [q ].hh .v.RH == 1073741823L ) ) {
	
      t = mem [q + 1 ].hh .v.RH ;
      if ( q == rover ) 
      rover = t ;
      mem [t + 1 ].hh .v.LH = mem [q + 1 ].hh .v.LH ;
      mem [mem [q + 1 ].hh .v.LH + 1 ].hh .v.RH = t ;
      q = q + mem [q ].hh .v.LH ;
    } 
    r = q - s ;
    if ( r > p + 1 ) 
    {
      mem [p ].hh .v.LH = r - p ;
      rover = p ;
      goto lab40 ;
    } 
    if ( r == p ) {
	
      if ( mem [p + 1 ].hh .v.RH != p ) 
      {
	rover = mem [p + 1 ].hh .v.RH ;
	t = mem [p + 1 ].hh .v.LH ;
	mem [rover + 1 ].hh .v.LH = t ;
	mem [t + 1 ].hh .v.RH = rover ;
	goto lab40 ;
      } 
    } 
    mem [p ].hh .v.LH = q - p ;
    p = mem [p + 1 ].hh .v.RH ;
  } while ( ! ( p == rover ) ) ;
  if ( s == 1073741824L ) 
  {
    Result = 1073741823L ;
    return Result ;
  } 
  if ( lomemmax + 2 < himemmin ) {
      
    if ( lomemmax + 2 <= membot + 1073741823L ) 
    {
      if ( himemmin - lomemmax >= 1998 ) 
      t = lomemmax + 1000 ;
      else t = lomemmax + 1 + ( himemmin - lomemmax ) / 2 ;
      p = mem [rover + 1 ].hh .v.LH ;
      q = lomemmax ;
      mem [p + 1 ].hh .v.RH = q ;
      mem [rover + 1 ].hh .v.LH = q ;
      if ( t > membot + 1073741823L ) 
      t = membot + 1073741823L ;
      mem [q + 1 ].hh .v.RH = rover ;
      mem [q + 1 ].hh .v.LH = p ;
      mem [q ].hh .v.RH = 1073741823L ;
      mem [q ].hh .v.LH = t - lomemmax ;
      lomemmax = t ;
      mem [lomemmax ].hh .v.RH = -1073741823L ;
      mem [lomemmax ].hh .v.LH = -1073741823L ;
      rover = q ;
      goto lab20 ;
    } 
  } 
  overflow ( 299 , memmax + 1 - memmin ) ;
  lab40: mem [r ].hh .v.RH = -1073741823L ;
	;
#ifdef STAT
  varused = varused + s ;
#endif /* STAT */
  if ( s >= 4 ) 
  {
    mem [r + s - 2 ].cint = curinput .synctextagfield ;
    mem [r + s - 1 ].cint = line ;
  } 
  Result = r ;
  return Result ;
} 
void 
zfreenode ( halfword p , halfword s ) 
{
  freenode_regmem 
  halfword q  ;
  mem [p ].hh .v.LH = s ;
  mem [p ].hh .v.RH = 1073741823L ;
  q = mem [rover + 1 ].hh .v.LH ;
  mem [p + 1 ].hh .v.LH = q ;
  mem [p + 1 ].hh .v.RH = rover ;
  mem [rover + 1 ].hh .v.LH = p ;
  mem [q + 1 ].hh .v.RH = p ;
	;
#ifdef STAT
  varused = varused - s ;
#endif /* STAT */
} 
halfword 
newnullbox ( void ) 
{
  register halfword Result; newnullbox_regmem 
  halfword p  ;
  p = getnode ( 10 ) ;
  mem [p ].hh.b0 = 0 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = 0 ;
  mem [p + 2 ].cint = 0 ;
  mem [p + 3 ].cint = 0 ;
  mem [p + 4 ].cint = 0 ;
  mem [p + 5 ].hh .v.RH = -1073741823L ;
  mem [p + 5 ].hh.b0 = 0 ;
  mem [p + 5 ].hh.b1 = 0 ;
  mem [p + 6 ].gr = 0.0 ;
  mem [p + 7 ].hh .v.RH = membot ;
  mem [p + 7 ].hh .v.LH = membot ;
  incr ( mem [membot ].hh .v.RH ) ;
  incr ( mem [membot ].hh .v.RH ) ;
  Result = p ;
  return Result ;
} 
halfword 
znewdirnode ( halfword b , eightbits dir ) 
{
  register halfword Result; newdirnode_regmem 
  halfword p  ;
  if ( mem [b ].hh.b0 > 1 ) 
  confusion ( 300 ) ;
  p = newnullbox () ;
  mem [p ].hh.b0 = 2 ;
  mem [p ].hh.b1 = dir ;
  switch ( ( mem [b ].hh.b1 ) ) 
  {case 4 : 
    switch ( dir ) 
    {case 3 : 
      {
	mem [p + 1 ].cint = mem [b + 3 ].cint + mem [b + 2 ].cint ;
	mem [p + 2 ].cint = mem [b + 1 ].cint / ((double) 2 ) ;
	mem [p + 3 ].cint = mem [b + 1 ].cint - mem [p + 2 ].cint ;
      } 
      break ;
    case 1 : 
      {
	mem [p + 1 ].cint = mem [b + 3 ].cint + mem [b + 2 ].cint ;
	mem [p + 2 ].cint = 0 ;
	mem [p + 3 ].cint = mem [b + 1 ].cint ;
      } 
      break ;
      default: 
      confusion ( 302 ) ;
      break ;
    } 
    break ;
  case 3 : 
    switch ( dir ) 
    {case 4 : 
      {
	mem [p + 1 ].cint = mem [b + 3 ].cint + mem [b + 2 ].cint ;
	mem [p + 2 ].cint = 0 ;
	mem [p + 3 ].cint = mem [b + 1 ].cint ;
      } 
      break ;
    case 1 : 
      {
	mem [p + 1 ].cint = mem [b + 1 ].cint ;
	mem [p + 2 ].cint = mem [b + 3 ].cint ;
	mem [p + 3 ].cint = mem [b + 2 ].cint ;
      } 
      break ;
      default: 
      confusion ( 303 ) ;
      break ;
    } 
    break ;
  case 1 : 
    switch ( dir ) 
    {case 4 : 
      {
	mem [p + 1 ].cint = mem [b + 3 ].cint + mem [b + 2 ].cint ;
	mem [p + 2 ].cint = 0 ;
	mem [p + 3 ].cint = mem [b + 1 ].cint ;
      } 
      break ;
    case 3 : 
      {
	mem [p + 1 ].cint = mem [b + 1 ].cint ;
	mem [p + 2 ].cint = mem [b + 3 ].cint ;
	mem [p + 3 ].cint = mem [b + 2 ].cint ;
      } 
      break ;
      default: 
      confusion ( 304 ) ;
      break ;
    } 
    break ;
    default: 
    confusion ( 301 ) ;
    break ;
  } 
  mem [b ].hh .v.RH = -1073741823L ;
  mem [p + 5 ].hh .v.RH = b ;
  Result = p ;
  return Result ;
} 
halfword 
newrule ( void ) 
{
  register halfword Result; newrule_regmem 
  halfword p  ;
  p = getnode ( 6 ) ;
  mem [p ].hh.b0 = 3 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = -1073741824L ;
  mem [p + 2 ].cint = -1073741824L ;
  mem [p + 3 ].cint = -1073741824L ;
  Result = p ;
  return Result ;
} 
halfword 
znewligature ( internalfontnumber f , quarterword c , halfword q ) 
{
  register halfword Result; newligature_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 8 ;
  mem [p + 1 ].hh.b0 = f ;
  mem [p + 1 ].hh.b1 = c ;
  mem [p + 1 ].hh .v.RH = q ;
  mem [p ].hh.b1 = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
znewligitem ( quarterword c ) 
{
  register halfword Result; newligitem_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b1 = c ;
  mem [p + 1 ].hh .v.RH = -1073741823L ;
  Result = p ;
  return Result ;
} 
halfword 
newdisc ( void ) 
{
  register halfword Result; newdisc_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 9 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.LH = -1073741823L ;
  mem [p + 1 ].hh .v.RH = -1073741823L ;
  Result = p ;
  return Result ;
} 
halfword 
znewmath ( scaled w , smallnumber s ) 
{
  register halfword Result; newmath_regmem 
  halfword p  ;
  p = getnode ( 4 ) ;
  mem [p ].hh.b0 = 11 ;
  mem [p ].hh.b1 = s ;
  mem [p + 1 ].cint = w ;
  Result = p ;
  return Result ;
} 
halfword 
znewspec ( halfword p ) 
{
  register halfword Result; newspec_regmem 
  halfword q  ;
  q = getnode ( 4 ) ;
  mem [q ]= mem [p ];
  mem [q ].hh .v.RH = -1073741823L ;
  mem [q + 1 ].cint = mem [p + 1 ].cint ;
  mem [q + 2 ].cint = mem [p + 2 ].cint ;
  mem [q + 3 ].cint = mem [p + 3 ].cint ;
  Result = q ;
  return Result ;
} 
halfword 
znewparamglue ( smallnumber n ) 
{
  register halfword Result; newparamglue_regmem 
  halfword p  ;
  halfword q  ;
  p = getnode ( 4 ) ;
  mem [p ].hh.b0 = 12 ;
  mem [p ].hh.b1 = n + 1 ;
  mem [p + 1 ].hh .v.RH = -1073741823L ;
  q = eqtb [24527 + n ].hh .v.RH ;
  mem [p + 1 ].hh .v.LH = q ;
  incr ( mem [q ].hh .v.RH ) ;
  Result = p ;
  return Result ;
} 
halfword 
znewglue ( halfword q ) 
{
  register halfword Result; newglue_regmem 
  halfword p  ;
  p = getnode ( 4 ) ;
  mem [p ].hh.b0 = 12 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.RH = -1073741823L ;
  mem [p + 1 ].hh .v.LH = q ;
  incr ( mem [q ].hh .v.RH ) ;
  Result = p ;
  return Result ;
} 
halfword 
znewskipparam ( smallnumber n ) 
{
  register halfword Result; newskipparam_regmem 
  halfword p  ;
  tempptr = newspec ( eqtb [24527 + n ].hh .v.RH ) ;
  p = newglue ( tempptr ) ;
  mem [tempptr ].hh .v.RH = -1073741823L ;
  mem [p ].hh.b1 = n + 1 ;
  Result = p ;
  return Result ;
} 
halfword 
znewkern ( scaled w ) 
{
  register halfword Result; newkern_regmem 
  halfword p  ;
  p = getnode ( 4 ) ;
  mem [p ].hh.b0 = 13 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = w ;
  Result = p ;
  return Result ;
} 
halfword 
znewpenalty ( integer m ) 
{
  register halfword Result; newpenalty_regmem 
  halfword p  ;
  p = getnode ( 4 ) ;
  mem [p ].hh.b0 = 14 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = m ;
  Result = p ;
  return Result ;
} 
#ifdef TEXMF_DEBUG
void 
zcheckmem ( boolean printlocs ) 
{
  /* 31 32 */ checkmem_regmem 
  halfword p, q  ;
  boolean clobbered  ;
  {register integer for_end; p = memmin ;for_end = lomemmax ; if ( p <= 
  for_end) do 
    freearr [p ]= false ;
  while ( p++ < for_end ) ;} 
  {register integer for_end; p = himemmin ;for_end = memend ; if ( p <= 
  for_end) do 
    freearr [p ]= false ;
  while ( p++ < for_end ) ;} 
  p = avail ;
  q = -1073741823L ;
  clobbered = false ;
  while ( p != -1073741823L ) {
      
    if ( ( p > memend ) || ( p < himemmin ) ) 
    clobbered = true ;
    else if ( freearr [p ]) 
    clobbered = true ;
    if ( clobbered ) 
    {
      printnl ( 305 ) ;
      printint ( q ) ;
      goto lab31 ;
    } 
    freearr [p ]= true ;
    q = p ;
    p = mem [q ].hh .v.RH ;
  } 
  lab31: ;
  p = rover ;
  q = -1073741823L ;
  clobbered = false ;
  do {
      if ( ( p >= lomemmax ) || ( p < memmin ) ) 
    clobbered = true ;
    else if ( ( mem [p + 1 ].hh .v.RH >= lomemmax ) || ( mem [p + 1 ].hh 
    .v.RH < memmin ) ) 
    clobbered = true ;
    else if ( ! ( ( mem [p ].hh .v.RH == 1073741823L ) ) || ( mem [p ].hh 
    .v.LH < 2 ) || ( p + mem [p ].hh .v.LH > lomemmax ) || ( mem [mem [p + 
    1 ].hh .v.RH + 1 ].hh .v.LH != p ) ) 
    clobbered = true ;
    if ( clobbered ) 
    {
      printnl ( 306 ) ;
      printint ( q ) ;
      goto lab32 ;
    } 
    {register integer for_end; q = p ;for_end = p + mem [p ].hh .v.LH - 1 
    ; if ( q <= for_end) do 
      {
	if ( freearr [q ]) 
	{
	  printnl ( 307 ) ;
	  printint ( q ) ;
	  goto lab32 ;
	} 
	freearr [q ]= true ;
      } 
    while ( q++ < for_end ) ;} 
    q = p ;
    p = mem [p + 1 ].hh .v.RH ;
  } while ( ! ( p == rover ) ) ;
  lab32: ;
  p = memmin ;
  while ( p <= lomemmax ) {
      
    if ( ( mem [p ].hh .v.RH == 1073741823L ) ) 
    {
      printnl ( 308 ) ;
      printint ( p ) ;
    } 
    while ( ( p <= lomemmax ) && ! freearr [p ]) incr ( p ) ;
    while ( ( p <= lomemmax ) && freearr [p ]) incr ( p ) ;
  } 
  if ( printlocs ) 
  {
    printnl ( 309 ) ;
    {register integer for_end; p = memmin ;for_end = lomemmax ; if ( p <= 
    for_end) do 
      if ( ! freearr [p ]&& ( ( p > waslomax ) || wasfree [p ]) ) 
      {
	printchar ( 32 ) ;
	printint ( p ) ;
      } 
    while ( p++ < for_end ) ;} 
    {register integer for_end; p = himemmin ;for_end = memend ; if ( p <= 
    for_end) do 
      if ( ! freearr [p ]&& ( ( p < washimin ) || ( p > wasmemend ) || 
      wasfree [p ]) ) 
      {
	printchar ( 32 ) ;
	printint ( p ) ;
      } 
    while ( p++ < for_end ) ;} 
  } 
  {register integer for_end; p = memmin ;for_end = lomemmax ; if ( p <= 
  for_end) do 
    wasfree [p ]= freearr [p ];
  while ( p++ < for_end ) ;} 
  {register integer for_end; p = himemmin ;for_end = memend ; if ( p <= 
  for_end) do 
    wasfree [p ]= freearr [p ];
  while ( p++ < for_end ) ;} 
  wasmemend = memend ;
  waslomax = lomemmax ;
  washimin = himemmin ;
} 
#endif /* TEXMF_DEBUG */
#ifdef TEXMF_DEBUG
void 
zsearchmem ( halfword p ) 
{
  searchmem_regmem 
  integer q  ;
  {register integer for_end; q = memmin ;for_end = lomemmax ; if ( q <= 
  for_end) do 
    {
      if ( mem [q ].hh .v.RH == p ) 
      {
	printnl ( 310 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
      if ( mem [q ].hh .v.LH == p ) 
      {
	printnl ( 311 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  {register integer for_end; q = himemmin ;for_end = memend ; if ( q <= 
  for_end) do 
    {
      if ( mem [q ].hh .v.RH == p ) 
      {
	printnl ( 310 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
      if ( mem [q ].hh .v.LH == p ) 
      {
	printnl ( 311 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  {register integer for_end; q = 1 ;for_end = 25581 ; if ( q <= for_end) do 
    {
      if ( eqtb [q ].hh .v.RH == p ) 
      {
	printnl ( 536 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  if ( saveptr > 0 ) 
  {register integer for_end; q = 0 ;for_end = saveptr - 1 ; if ( q <= 
  for_end) do 
    {
      if ( savestack [q ].hh .v.RH == p ) 
      {
	printnl ( 584 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  {register integer for_end; q = 0 ;for_end = hyphsize ; if ( q <= for_end) 
  do 
    {
      if ( hyphlist [q ]== p ) 
      {
	printnl ( 997 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
} 
#endif /* TEXMF_DEBUG */
void 
zshortdisplay ( integer p ) 
{
  shortdisplay_regmem 
  integer n  ;
  while ( p > memmin ) {
      
    if ( ( p >= himemmin ) ) 
    {
      if ( p <= memend ) 
      {
	if ( mem [p ].hh.b0 != fontinshortdisplay ) 
	{
	  if ( ( mem [p ].hh.b0 > fontmax ) ) 
	  printchar ( 42 ) ;
	  else printesc ( hash [15525 + mem [p ].hh.b0 ].v.RH ) ;
	  printchar ( 32 ) ;
	  fontinshortdisplay = mem [p ].hh.b0 ;
	} 
	if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
	{
	  p = mem [p ].hh .v.RH ;
	  printkanji ( mem [p ].hh .v.LH ) ;
	} 
	else print ( mem [p ].hh.b1 ) ;
      } 
    } 
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
    case 4 : 
    case 10 : 
    case 6 : 
    case 7 : 
    case 15 : 
      print ( 312 ) ;
      break ;
    case 3 : 
      printchar ( 124 ) ;
      break ;
    case 12 : 
      if ( mem [p + 1 ].hh .v.LH != membot ) 
      printchar ( 32 ) ;
      break ;
    case 11 : 
      printchar ( 36 ) ;
      break ;
    case 8 : 
      shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
      break ;
    case 9 : 
      {
	shortdisplay ( mem [p + 1 ].hh .v.LH ) ;
	shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
	n = mem [p ].hh.b1 ;
	while ( n > 0 ) {
	    
	  if ( mem [p ].hh .v.RH != -1073741823L ) 
	  p = mem [p ].hh .v.RH ;
	  decr ( n ) ;
	} 
      } 
      break ;
      default: 
      ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
} 
void 
zprintfontandchar ( integer p ) 
{
  printfontandchar_regmem 
  if ( p > memend ) 
  printesc ( 313 ) ;
  else {
      
    if ( ( mem [p ].hh.b0 > fontmax ) ) 
    printchar ( 42 ) ;
    else printesc ( hash [15525 + mem [p ].hh.b0 ].v.RH ) ;
    printchar ( 32 ) ;
    if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
    {
      p = mem [p ].hh .v.RH ;
      printkanji ( mem [p ].hh .v.LH ) ;
    } 
    else print ( mem [p ].hh.b1 ) ;
  } 
} 
void 
zprintmark ( integer p ) 
{
  printmark_regmem 
  printchar ( 123 ) ;
  if ( ( p < himemmin ) || ( p > memend ) ) 
  printesc ( 313 ) ;
  else showtokenlist ( mem [p ].hh .v.RH , -1073741823L , maxprintline - 10 
  ) ;
  printchar ( 125 ) ;
} 
void 
zprintruledimen ( scaled d ) 
{
  printruledimen_regmem 
  if ( ( d == -1073741824L ) ) 
  printchar ( 42 ) ;
  else printscaled ( d ) ;
} 
void 
zprintglue ( scaled d , integer order , strnumber s ) 
{
  printglue_regmem 
  printscaled ( d ) ;
  if ( ( order < 0 ) || ( order > 3 ) ) 
  print ( 314 ) ;
  else if ( order > 0 ) 
  {
    print ( 315 ) ;
    while ( order > 1 ) {
	
      printchar ( 108 ) ;
      decr ( order ) ;
    } 
  } 
  else if ( s != 0 ) 
  print ( s ) ;
} 
void 
zprintspec ( integer p , strnumber s ) 
{
  printspec_regmem 
  if ( ( p < memmin ) || ( p >= lomemmax ) ) 
  printchar ( 42 ) ;
  else {
      
    printscaled ( mem [p + 1 ].cint ) ;
    if ( s != 0 ) 
    print ( s ) ;
    if ( mem [p + 2 ].cint != 0 ) 
    {
      print ( 316 ) ;
      printglue ( mem [p + 2 ].cint , mem [p ].hh.b0 , s ) ;
    } 
    if ( mem [p + 3 ].cint != 0 ) 
    {
      print ( 317 ) ;
      printglue ( mem [p + 3 ].cint , mem [p ].hh.b1 , s ) ;
    } 
  } 
} 
void 
zprintfamandchar ( halfword p , smallnumber t ) 
{
  printfamandchar_regmem 
  KANJIcode cx  ;
  printesc ( 488 ) ;
  printint ( mem [p ].hh.b0 ) ;
  printchar ( 32 ) ;
  if ( t == 1 ) 
  print ( mem [p ].hh.b1 ) ;
  else {
      
    cx = mem [p + 3 ].hh .v.LH ;
    printkanji ( cx ) ;
  } 
} 
void 
zprintdelimiter ( halfword p ) 
{
  printdelimiter_regmem 
  integer a  ;
  a = mem [p ].qqqq .b0 * 256 + mem [p ].qqqq .b1 ;
  a = a * 4096 + mem [p ].qqqq .b2 * 256 + mem [p ].qqqq .b3 ;
  if ( a < 0 ) 
  printint ( a ) ;
  else printhex ( a ) ;
} 
void 
zprintsubsidiarydata ( halfword p , ASCIIcode c ) 
{
  printsubsidiarydata_regmem 
  if ( ( poolptr - strstart [strptr ]) >= depththreshold ) 
  {
    if ( mem [p ].hh .v.RH != 0 ) 
    print ( 318 ) ;
  } 
  else {
      
    {
      strpool [poolptr ]= c ;
      incr ( poolptr ) ;
    } 
    tempptr = p ;
    switch ( mem [p ].hh .v.RH ) 
    {case 1 : 
    case 6 : 
      {
	println () ;
	printcurrentstring () ;
	printfamandchar ( p , mem [p ].hh .v.RH ) ;
      } 
      break ;
    case 2 : 
    case 3 : 
      showinfo () ;
      break ;
    case 4 : 
      if ( mem [p ].hh .v.LH == -1073741823L ) 
      {
	println () ;
	printcurrentstring () ;
	print ( 916 ) ;
      } 
      else showinfo () ;
      break ;
      default: 
      ;
      break ;
    } 
    decr ( poolptr ) ;
  } 
} 
void 
zprintstyle ( integer c ) 
{
  printstyle_regmem 
  switch ( c / 2 ) 
  {case 0 : 
    printesc ( 917 ) ;
    break ;
  case 1 : 
    printesc ( 918 ) ;
    break ;
  case 2 : 
    printesc ( 919 ) ;
    break ;
  case 3 : 
    printesc ( 920 ) ;
    break ;
    default: 
    print ( 921 ) ;
    break ;
  } 
} 
void 
zprintskipparam ( integer n ) 
{
  printskipparam_regmem 
  switch ( n ) 
  {case 0 : 
    printesc ( 392 ) ;
    break ;
  case 1 : 
    printesc ( 393 ) ;
    break ;
  case 2 : 
    printesc ( 394 ) ;
    break ;
  case 3 : 
    printesc ( 395 ) ;
    break ;
  case 4 : 
    printesc ( 396 ) ;
    break ;
  case 5 : 
    printesc ( 397 ) ;
    break ;
  case 6 : 
    printesc ( 398 ) ;
    break ;
  case 7 : 
    printesc ( 399 ) ;
    break ;
  case 8 : 
    printesc ( 400 ) ;
    break ;
  case 9 : 
    printesc ( 401 ) ;
    break ;
  case 10 : 
    printesc ( 402 ) ;
    break ;
  case 11 : 
    printesc ( 403 ) ;
    break ;
  case 12 : 
    printesc ( 404 ) ;
    break ;
  case 13 : 
    printesc ( 405 ) ;
    break ;
  case 14 : 
    printesc ( 406 ) ;
    break ;
  case 17 : 
    printesc ( 407 ) ;
    break ;
  case 18 : 
    printesc ( 408 ) ;
    break ;
  case 19 : 
    printesc ( 409 ) ;
    break ;
  case 15 : 
    printesc ( 410 ) ;
    break ;
  case 16 : 
    printesc ( 411 ) ;
    break ;
  case 20 : 
    print ( 412 ) ;
    break ;
    default: 
    print ( 413 ) ;
    break ;
  } 
} 
void 
zshownodelist ( integer p ) 
{
  /* 10 */ shownodelist_regmem 
  integer n  ;
  real g  ;
  if ( ( poolptr - strstart [strptr ]) > depththreshold ) 
  {
    if ( p > -1073741823L ) 
    print ( 318 ) ;
    return ;
  } 
  n = 0 ;
  while ( p > memmin ) {
      
    println () ;
    printcurrentstring () ;
    if ( p > memend ) 
    {
      print ( 319 ) ;
      return ;
    } 
    incr ( n ) ;
    if ( n > breadthmax ) 
    {
      print ( 320 ) ;
      return ;
    } 
    if ( ( p >= himemmin ) ) 
    {
      printfontandchar ( p ) ;
      if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
      p = mem [p ].hh .v.RH ;
    } 
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
    case 15 : 
      {
	switch ( mem [p ].hh.b0 ) 
	{case 0 : 
	  printesc ( 104 ) ;
	  break ;
	case 1 : 
	  printesc ( 118 ) ;
	  break ;
	case 2 : 
	  printesc ( 323 ) ;
	  break ;
	  default: 
	  printesc ( 324 ) ;
	  break ;
	} 
	print ( 325 ) ;
	printscaled ( mem [p + 3 ].cint ) ;
	printchar ( 43 ) ;
	printscaled ( mem [p + 2 ].cint ) ;
	print ( 326 ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	if ( mem [p ].hh.b0 == 15 ) 
	{
	  if ( mem [p ].hh.b1 != 0 ) 
	  {
	    print ( 285 ) ;
	    printint ( mem [p ].hh.b1 + 1 ) ;
	    print ( 329 ) ;
	  } 
	  if ( mem [p + 6 ].cint != 0 ) 
	  {
	    print ( 330 ) ;
	    printglue ( mem [p + 6 ].cint , mem [p + 5 ].hh.b1 , 0 ) ;
	  } 
	  if ( mem [p + 4 ].cint != 0 ) 
	  {
	    print ( 331 ) ;
	    printglue ( mem [p + 4 ].cint , mem [p + 5 ].hh.b0 , 0 ) ;
	  } 
	} 
	else {
	    
	  g = mem [p + 6 ].gr ;
	  if ( ( g != 0.0 ) && ( mem [p + 5 ].hh.b0 != 0 ) ) 
	  {
	    print ( 332 ) ;
	    if ( mem [p + 5 ].hh.b0 == 2 ) 
	    print ( 333 ) ;
	    if ( fabs ( g ) > 20000.0 ) 
	    {
	      if ( g > 0.0 ) 
	      printchar ( 62 ) ;
	      else print ( 334 ) ;
	      printglue ( 20000 * 65536L , mem [p + 5 ].hh.b1 , 0 ) ;
	    } 
	    else printglue ( round ( 65536L * g ) , mem [p + 5 ].hh.b1 , 0 ) 
	    ;
	  } 
	  if ( mem [p + 4 ].cint != 0 ) 
	  {
	    print ( 327 ) ;
	    printscaled ( mem [p + 4 ].cint ) ;
	  } 
	  if ( ( mem [p ].hh.b1 ) != 0 ) 
	  {
	    print ( 328 ) ;
	    printdirection ( ( mem [p ].hh.b1 ) ) ;
	  } 
	} 
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 5 ].hh .v.RH ) ;
	  decr ( poolptr ) ;
	} 
      } 
      break ;
    case 3 : 
      {
	printesc ( 335 ) ;
	printruledimen ( mem [p + 3 ].cint ) ;
	printchar ( 43 ) ;
	printruledimen ( mem [p + 2 ].cint ) ;
	print ( 326 ) ;
	printruledimen ( mem [p + 1 ].cint ) ;
      } 
      break ;
    case 4 : 
      {
	printesc ( 336 ) ;
	printint ( mem [p ].hh.b1 ) ;
	printdir ( mem [p + 5 ].hh.b1 ) ;
	print ( 337 ) ;
	printscaled ( mem [p + 3 ].cint ) ;
	print ( 338 ) ;
	printspec ( mem [p + 4 ].hh .v.RH , 0 ) ;
	printchar ( 44 ) ;
	printscaled ( mem [p + 2 ].cint ) ;
	print ( 339 ) ;
	printint ( mem [p + 1 ].cint ) ;
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 4 ].hh .v.LH ) ;
	  decr ( poolptr ) ;
	} 
      } 
      break ;
    case 10 : 
      switch ( mem [p ].hh.b1 ) 
      {case 0 : 
	{
	  printwritewhatsit ( 1370 , p ) ;
	  printchar ( 61 ) ;
	  printfilename ( mem [p + 1 ].hh .v.RH , mem [p + 2 ].hh .v.LH , 
	  mem [p + 2 ].hh .v.RH ) ;
	} 
	break ;
      case 1 : 
	{
	  printwritewhatsit ( 632 , p ) ;
	  printmark ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 2 : 
	printwritewhatsit ( 1371 , p ) ;
	break ;
      case 3 : 
	{
	  printesc ( 1372 ) ;
	  printmark ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 4 : 
	{
	  printesc ( 1374 ) ;
	  printint ( mem [p + 1 ].hh .v.RH ) ;
	  print ( 1377 ) ;
	  printint ( mem [p + 1 ].hh.b0 ) ;
	  printchar ( 44 ) ;
	  printint ( mem [p + 1 ].hh.b1 ) ;
	  printchar ( 41 ) ;
	} 
	break ;
	default: 
	print ( 1378 ) ;
	break ;
      } 
      break ;
    case 5 : 
      {
	printesc ( 321 ) ;
	printscaled ( mem [p + 1 ].cint ) ;
      } 
      break ;
    case 12 : 
      if ( mem [p ].hh.b1 >= 100 ) 
      {
	printesc ( 344 ) ;
	if ( mem [p ].hh.b1 == 101 ) 
	printchar ( 99 ) ;
	else if ( mem [p ].hh.b1 == 102 ) 
	printchar ( 120 ) ;
	print ( 345 ) ;
	printspec ( mem [p + 1 ].hh .v.LH , 0 ) ;
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 1 ].hh .v.RH ) ;
	  decr ( poolptr ) ;
	} 
      } 
      else {
	  
	printesc ( 340 ) ;
	if ( mem [p ].hh.b1 != 0 ) 
	{
	  printchar ( 40 ) ;
	  if ( mem [p ].hh.b1 < 98 ) 
	  printskipparam ( mem [p ].hh.b1 - 1 ) ;
	  else if ( mem [p ].hh.b1 == 98 ) 
	  printesc ( 341 ) ;
	  else printesc ( 342 ) ;
	  printchar ( 41 ) ;
	} 
	if ( mem [p ].hh.b1 != 98 ) 
	{
	  printchar ( 32 ) ;
	  if ( mem [p ].hh.b1 < 98 ) 
	  printspec ( mem [p + 1 ].hh .v.LH , 0 ) ;
	  else printspec ( mem [p + 1 ].hh .v.LH , 343 ) ;
	} 
      } 
      break ;
    case 13 : 
      if ( mem [p ].hh.b1 != 99 ) 
      {
	printesc ( 346 ) ;
	if ( mem [p ].hh.b1 != 0 ) 
	printchar ( 32 ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	if ( mem [p ].hh.b1 == 2 ) 
	print ( 347 ) ;
      } 
      else {
	  
	printesc ( 348 ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	print ( 343 ) ;
      } 
      break ;
    case 11 : 
      {
	printesc ( 349 ) ;
	if ( mem [p ].hh.b1 == 0 ) 
	print ( 350 ) ;
	else print ( 351 ) ;
	if ( mem [p + 1 ].cint != 0 ) 
	{
	  print ( 352 ) ;
	  printscaled ( mem [p + 1 ].cint ) ;
	} 
      } 
      break ;
    case 8 : 
      {
	printfontandchar ( p + 1 ) ;
	print ( 353 ) ;
	if ( mem [p ].hh.b1 > 1 ) 
	printchar ( 124 ) ;
	fontinshortdisplay = mem [p + 1 ].hh.b0 ;
	shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
	if ( odd ( mem [p ].hh.b1 ) ) 
	printchar ( 124 ) ;
	printchar ( 41 ) ;
      } 
      break ;
    case 14 : 
      {
	printesc ( 354 ) ;
	printint ( mem [p + 1 ].cint ) ;
	if ( mem [p ].hh.b1 == 1 ) 
	print ( 355 ) ;
	else if ( mem [p ].hh.b1 == 2 ) 
	print ( 356 ) ;
      } 
      break ;
    case 9 : 
      {
	printesc ( 357 ) ;
	if ( mem [p ].hh.b1 > 0 ) 
	{
	  print ( 358 ) ;
	  printint ( mem [p ].hh.b1 ) ;
	} 
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 1 ].hh .v.LH ) ;
	  decr ( poolptr ) ;
	} 
	{
	  strpool [poolptr ]= 124 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 1 ].hh .v.RH ) ;
	decr ( poolptr ) ;
      } 
      break ;
    case 6 : 
      {
	printesc ( 359 ) ;
	printmark ( mem [p + 1 ].cint ) ;
      } 
      break ;
    case 7 : 
      {
	printesc ( 360 ) ;
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 1 ].cint ) ;
	  decr ( poolptr ) ;
	} 
      } 
      break ;
    case 16 : 
      printstyle ( mem [p ].hh.b1 ) ;
      break ;
    case 17 : 
      {
	printesc ( 563 ) ;
	{
	  strpool [poolptr ]= 68 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 1 ].hh .v.LH ) ;
	decr ( poolptr ) ;
	{
	  strpool [poolptr ]= 84 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 1 ].hh .v.RH ) ;
	decr ( poolptr ) ;
	{
	  strpool [poolptr ]= 83 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 2 ].hh .v.LH ) ;
	decr ( poolptr ) ;
	{
	  strpool [poolptr ]= 115 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 2 ].hh .v.RH ) ;
	decr ( poolptr ) ;
      } 
      break ;
    case 18 : 
    case 19 : 
    case 20 : 
    case 21 : 
    case 22 : 
    case 23 : 
    case 24 : 
    case 25 : 
    case 26 : 
    case 29 : 
    case 28 : 
    case 31 : 
    case 30 : 
    case 32 : 
    case 33 : 
      {
	switch ( mem [p ].hh.b0 ) 
	{case 18 : 
	  printesc ( 922 ) ;
	  break ;
	case 19 : 
	  printesc ( 923 ) ;
	  break ;
	case 20 : 
	  printesc ( 924 ) ;
	  break ;
	case 21 : 
	  printesc ( 925 ) ;
	  break ;
	case 22 : 
	  printesc ( 926 ) ;
	  break ;
	case 23 : 
	  printesc ( 927 ) ;
	  break ;
	case 24 : 
	  printesc ( 928 ) ;
	  break ;
	case 25 : 
	  printesc ( 929 ) ;
	  break ;
	case 29 : 
	  printesc ( 930 ) ;
	  break ;
	case 28 : 
	  printesc ( 931 ) ;
	  break ;
	case 31 : 
	  printesc ( 577 ) ;
	  break ;
	case 26 : 
	  {
	    printesc ( 571 ) ;
	    printdelimiter ( p + 5 ) ;
	  } 
	  break ;
	case 30 : 
	  {
	    printesc ( 543 ) ;
	    printfamandchar ( p + 5 , 1 ) ;
	  } 
	  break ;
	case 32 : 
	  {
	    printesc ( 932 ) ;
	    printdelimiter ( p + 1 ) ;
	  } 
	  break ;
	case 33 : 
	  {
	    printesc ( 933 ) ;
	    printdelimiter ( p + 1 ) ;
	  } 
	  break ;
	} 
	if ( mem [p ].hh.b1 != 0 ) {
	    
	  if ( mem [p ].hh.b1 == 1 ) 
	  printesc ( 934 ) ;
	  else printesc ( 935 ) ;
	} 
	if ( mem [p ].hh.b0 < 32 ) 
	printsubsidiarydata ( p + 1 , 46 ) ;
	printsubsidiarydata ( p + 2 , 94 ) ;
	printsubsidiarydata ( p + 3 , 95 ) ;
      } 
      break ;
    case 27 : 
      {
	printesc ( 936 ) ;
	if ( mem [p + 1 ].cint == 1073741824L ) 
	print ( 937 ) ;
	else printscaled ( mem [p + 1 ].cint ) ;
	if ( ( mem [p + 5 ].qqqq .b0 != 0 ) || ( mem [p + 5 ].qqqq .b1 != 
	0 ) || ( mem [p + 5 ].qqqq .b2 != 0 ) || ( mem [p + 5 ].qqqq .b3 
	!= 0 ) ) 
	{
	  print ( 938 ) ;
	  printdelimiter ( p + 5 ) ;
	} 
	if ( ( mem [p + 4 ].qqqq .b0 != 0 ) || ( mem [p + 4 ].qqqq .b1 != 
	0 ) || ( mem [p + 4 ].qqqq .b2 != 0 ) || ( mem [p + 4 ].qqqq .b3 
	!= 0 ) ) 
	{
	  print ( 939 ) ;
	  printdelimiter ( p + 4 ) ;
	} 
	printsubsidiarydata ( p + 2 , 92 ) ;
	printsubsidiarydata ( p + 3 , 47 ) ;
      } 
      break ;
      default: 
      print ( 322 ) ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
} 
void 
zshowbox ( halfword p ) 
{
  showbox_regmem 
  depththreshold = eqtb [28487 ].cint ;
  breadthmax = eqtb [28486 ].cint ;
  if ( breadthmax <= 0 ) 
  breadthmax = 5 ;
  if ( poolptr + depththreshold >= poolsize ) 
  depththreshold = poolsize - poolptr - 1 ;
  shownodelist ( p ) ;
  println () ;
} 
void 
zdeletetokenref ( halfword p ) 
{
  deletetokenref_regmem 
  if ( mem [p ].hh .v.LH == -1073741823L ) 
  flushlist ( p ) ;
  else decr ( mem [p ].hh .v.LH ) ;
} 
void 
zdeleteglueref ( halfword p ) 
{
  deleteglueref_regmem 
  if ( mem [p ].hh .v.RH == -1073741823L ) 
  freenode ( p , 4 ) ;
  else decr ( mem [p ].hh .v.RH ) ;
} 
void 
zflushnodelist ( halfword p ) 
{
  /* 30 */ flushnodelist_regmem 
  halfword q  ;
  while ( p != -1073741823L ) {
      
    q = mem [p ].hh .v.RH ;
    if ( ( p >= himemmin ) ) 
    {
      mem [p ].hh .v.RH = avail ;
      avail = p ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } 
    else {
	
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 2 : 
      case 15 : 
	{
	  flushnodelist ( mem [p + 5 ].hh .v.RH ) ;
	  {
	    if ( mem [mem [p + 7 ].hh .v.RH ].hh .v.RH == -1073741823L ) 
	    freenode ( mem [p + 7 ].hh .v.RH , 4 ) ;
	    else decr ( mem [mem [p + 7 ].hh .v.RH ].hh .v.RH ) ;
	  } 
	  {
	    if ( mem [mem [p + 7 ].hh .v.LH ].hh .v.RH == -1073741823L ) 
	    freenode ( mem [p + 7 ].hh .v.LH , 4 ) ;
	    else decr ( mem [mem [p + 7 ].hh .v.LH ].hh .v.RH ) ;
	  } 
	  freenode ( p , 10 ) ;
	  goto lab30 ;
	} 
	break ;
      case 3 : 
	{
	  freenode ( p , 6 ) ;
	  goto lab30 ;
	} 
	break ;
      case 4 : 
	{
	  flushnodelist ( mem [p + 4 ].hh .v.LH ) ;
	  deleteglueref ( mem [p + 4 ].hh .v.RH ) ;
	  freenode ( p , 6 ) ;
	  goto lab30 ;
	} 
	break ;
      case 10 : 
	{
	  switch ( mem [p ].hh.b1 ) 
	  {case 0 : 
	    freenode ( p , 3 ) ;
	    break ;
	  case 1 : 
	  case 3 : 
	    {
	      deletetokenref ( mem [p + 1 ].hh .v.RH ) ;
	      freenode ( p , 2 ) ;
	      goto lab30 ;
	    } 
	    break ;
	  case 2 : 
	  case 4 : 
	    freenode ( p , 2 ) ;
	    break ;
	    default: 
	    confusion ( 1380 ) ;
	    break ;
	  } 
	  goto lab30 ;
	} 
	break ;
      case 12 : 
	{
	  {
	    if ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH == -1073741823L ) 
	    freenode ( mem [p + 1 ].hh .v.LH , 4 ) ;
	    else decr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	  } 
	  if ( mem [p + 1 ].hh .v.RH != -1073741823L ) 
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	  freenode ( p , 4 ) ;
	  goto lab30 ;
	} 
	break ;
      case 5 : 
	;
	break ;
      case 13 : 
      case 11 : 
      case 14 : 
	{
	  freenode ( p , 4 ) ;
	  goto lab30 ;
	} 
	break ;
      case 8 : 
	flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	break ;
      case 6 : 
	deletetokenref ( mem [p + 1 ].cint ) ;
	break ;
      case 9 : 
	{
	  flushnodelist ( mem [p + 1 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 7 : 
	flushnodelist ( mem [p + 1 ].cint ) ;
	break ;
      case 16 : 
	{
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 17 : 
	{
	  flushnodelist ( mem [p + 1 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	  flushnodelist ( mem [p + 2 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 2 ].hh .v.RH ) ;
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 18 : 
      case 19 : 
      case 20 : 
      case 21 : 
      case 22 : 
      case 23 : 
      case 24 : 
      case 25 : 
      case 26 : 
      case 29 : 
      case 28 : 
      case 31 : 
      case 30 : 
	{
	  if ( ( mem [p + 1 ].hh .v.RH >= 2 ) && ( mem [p + 1 ].hh .v.RH 
	  != 6 ) && ( mem [p + 1 ].hh .v.RH != 7 ) ) 
	  flushnodelist ( mem [p + 1 ].hh .v.LH ) ;
	  if ( mem [p + 2 ].hh .v.RH >= 2 && ( mem [p + 2 ].hh .v.RH != 6 
	  ) && ( mem [p + 2 ].hh .v.RH != 7 ) ) 
	  flushnodelist ( mem [p + 2 ].hh .v.LH ) ;
	  if ( mem [p + 3 ].hh .v.RH >= 2 && ( mem [p + 3 ].hh .v.RH != 6 
	  ) && ( mem [p + 3 ].hh .v.RH != 7 ) ) 
	  flushnodelist ( mem [p + 3 ].hh .v.LH ) ;
	  if ( mem [p ].hh.b0 == 26 ) 
	  freenode ( p , 6 ) ;
	  else if ( mem [p ].hh.b0 == 30 ) 
	  freenode ( p , 6 ) ;
	  else freenode ( p , 5 ) ;
	  goto lab30 ;
	} 
	break ;
      case 32 : 
      case 33 : 
	{
	  freenode ( p , 5 ) ;
	  goto lab30 ;
	} 
	break ;
      case 27 : 
	{
	  flushnodelist ( mem [p + 2 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 3 ].hh .v.LH ) ;
	  freenode ( p , 6 ) ;
	  goto lab30 ;
	} 
	break ;
	default: 
	confusion ( 361 ) ;
	break ;
      } 
      freenode ( p , 2 ) ;
      lab30: ;
    } 
    p = q ;
  } 
} 
halfword 
zcopynodelist ( halfword p ) 
{
  register halfword Result; copynodelist_regmem 
  halfword h  ;
  halfword q  ;
  halfword r  ;
  unsigned char words  ;
  h = getavail () ;
  q = h ;
  while ( p != -1073741823L ) {
      
    words = 1 ;
    if ( ( p >= himemmin ) ) 
    r = getavail () ;
    else switch ( mem [p ].hh.b0 ) 
    {case 2 : 
    case 0 : 
    case 1 : 
    case 15 : 
      {
	r = getnode ( 10 ) ;
	mem [r + 8 ].cint = mem [p + 8 ].cint ;
	mem [r + 9 ].cint = mem [p + 9 ].cint ;
	mem [r + 7 ]= mem [p + 7 ];
	mem [r + 6 ]= mem [p + 6 ];
	mem [r + 5 ]= mem [p + 5 ];
	incr ( mem [mem [r + 7 ].hh .v.RH ].hh .v.RH ) ;
	incr ( mem [mem [r + 7 ].hh .v.LH ].hh .v.RH ) ;
	mem [r + 5 ].hh .v.RH = copynodelist ( mem [p + 5 ].hh .v.RH ) ;
	words = 5 ;
      } 
      break ;
    case 3 : 
      {
	r = getnode ( 6 ) ;
	words = 4 ;
      } 
      break ;
    case 4 : 
      {
	r = getnode ( 6 ) ;
	mem [r + 5 ]= mem [p + 5 ];
	mem [r + 4 ]= mem [p + 4 ];
	incr ( mem [mem [p + 4 ].hh .v.RH ].hh .v.RH ) ;
	mem [r + 4 ].hh .v.LH = copynodelist ( mem [p + 4 ].hh .v.LH ) ;
	words = 4 ;
      } 
      break ;
    case 10 : 
      switch ( mem [p ].hh.b1 ) 
      {case 0 : 
	{
	  r = getnode ( 3 ) ;
	  words = 3 ;
	} 
	break ;
      case 1 : 
      case 3 : 
	{
	  r = getnode ( 2 ) ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	  words = 2 ;
	} 
	break ;
      case 2 : 
      case 4 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
	default: 
	confusion ( 1379 ) ;
	break ;
      } 
      break ;
    case 12 : 
      {
	r = getnode ( 4 ) ;
	incr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	mem [r + 2 ].cint = mem [p + 2 ].cint ;
	mem [r + 3 ].cint = mem [p + 3 ].cint ;
	mem [r + 1 ].hh .v.LH = mem [p + 1 ].hh .v.LH ;
	mem [r + 1 ].hh .v.RH = copynodelist ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 5 : 
      {
	r = getnode ( 2 ) ;
	words = 2 ;
      } 
      break ;
    case 13 : 
    case 11 : 
    case 14 : 
      {
	r = getnode ( 4 ) ;
	words = 4 ;
      } 
      break ;
    case 8 : 
      {
	r = getnode ( 2 ) ;
	mem [r + 1 ]= mem [p + 1 ];
	mem [r + 1 ].hh .v.RH = copynodelist ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 9 : 
      {
	r = getnode ( 2 ) ;
	mem [r + 1 ].hh .v.LH = copynodelist ( mem [p + 1 ].hh .v.LH ) ;
	mem [r + 1 ].hh .v.RH = copynodelist ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 6 : 
      {
	r = getnode ( 2 ) ;
	incr ( mem [mem [p + 1 ].cint ].hh .v.LH ) ;
	words = 2 ;
      } 
      break ;
    case 7 : 
      {
	r = getnode ( 2 ) ;
	mem [r + 1 ].cint = copynodelist ( mem [p + 1 ].cint ) ;
      } 
      break ;
      default: 
      confusion ( 362 ) ;
      break ;
    } 
    while ( words > 0 ) {
	
      decr ( words ) ;
      mem [r + words ]= mem [p + words ];
    } 
    mem [q ].hh .v.RH = r ;
    q = r ;
    p = mem [p ].hh .v.RH ;
  } 
  mem [q ].hh .v.RH = -1073741823L ;
  q = mem [h ].hh .v.RH ;
  {
    mem [h ].hh .v.RH = avail ;
    avail = h ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  Result = q ;
  return Result ;
} 
void 
zprintmode ( integer m ) 
{
  printmode_regmem 
  if ( m > 0 ) 
  switch ( m / ( 116 ) ) 
  {case 0 : 
    print ( 363 ) ;
    break ;
  case 1 : 
    print ( 364 ) ;
    break ;
  case 2 : 
    print ( 365 ) ;
    break ;
  } 
  else if ( m == 0 ) 
  print ( 366 ) ;
  else switch ( ( - (integer) m ) / ( 116 ) ) 
  {case 0 : 
    print ( 367 ) ;
    break ;
  case 1 : 
    print ( 368 ) ;
    break ;
  case 2 : 
    print ( 369 ) ;
    break ;
  } 
} 
void 
zprintinmode ( integer m ) 
{
  printinmode_regmem 
  if ( m > 0 ) 
  switch ( m / ( 116 ) ) 
  {case 0 : 
    print ( 370 ) ;
    break ;
  case 1 : 
    print ( 371 ) ;
    break ;
  case 2 : 
    print ( 372 ) ;
    break ;
  } 
  else if ( m == 0 ) 
  print ( 373 ) ;
  else switch ( ( - (integer) m ) / ( 116 ) ) 
  {case 0 : 
    print ( 374 ) ;
    break ;
  case 1 : 
    print ( 375 ) ;
    break ;
  case 2 : 
    print ( 376 ) ;
    break ;
  } 
} 
void 
pushnest ( void ) 
{
  pushnest_regmem 
  if ( nestptr > maxneststack ) 
  {
    maxneststack = nestptr ;
    if ( nestptr == nestsize ) 
    overflow ( 377 , nestsize ) ;
  } 
  nest [nestptr ]= curlist ;
  incr ( nestptr ) ;
  curlist .headfield = newnullbox () ;
  curlist .tailfield = curlist .headfield ;
  curlist .pnodefield = curlist .tailfield ;
  curlist .pgfield = 0 ;
  curlist .pdispfield = 0 ;
  curlist .lastjchrfield = -1073741823L ;
  curlist .mlfield = line ;
} 
void 
popnest ( void ) 
{
  popnest_regmem 
  {
    if ( mem [mem [curlist .headfield + 7 ].hh .v.RH ].hh .v.RH == 
    -1073741823L ) 
    freenode ( mem [curlist .headfield + 7 ].hh .v.RH , 4 ) ;
    else decr ( mem [mem [curlist .headfield + 7 ].hh .v.RH ].hh .v.RH ) ;
  } 
  {
    if ( mem [mem [curlist .headfield + 7 ].hh .v.LH ].hh .v.RH == 
    -1073741823L ) 
    freenode ( mem [curlist .headfield + 7 ].hh .v.LH , 4 ) ;
    else decr ( mem [mem [curlist .headfield + 7 ].hh .v.LH ].hh .v.RH ) ;
  } 
  freenode ( curlist .headfield , 10 ) ;
  decr ( nestptr ) ;
  curlist = nest [nestptr ];
} 
void 
showactivities ( void ) 
{
  showactivities_regmem 
  integer p  ;
  short m  ;
  memoryword a  ;
  halfword q, r  ;
  integer t  ;
  nest [nestptr ]= curlist ;
  printnl ( 344 ) ;
  println () ;
  {register integer for_end; p = nestptr ;for_end = 0 ; if ( p >= for_end) 
  do 
    {
      m = nest [p ].modefield ;
      a = nest [p ].auxfield ;
      printnl ( 378 ) ;
      printdirection ( nest [p ].dirfield ) ;
      print ( 328 ) ;
      printmode ( m ) ;
      print ( 379 ) ;
      printint ( abs ( nest [p ].mlfield ) ) ;
      if ( m == 117 ) {
	  
	if ( nest [p ].pgfield != 8585216L ) 
	{
	  print ( 380 ) ;
	  printint ( nest [p ].pgfield % 65536L ) ;
	  print ( 381 ) ;
	  printint ( nest [p ].pgfield / 4194304L ) ;
	  printchar ( 44 ) ;
	  printint ( ( nest [p ].pgfield / 65536L ) % 64 ) ;
	  printchar ( 41 ) ;
	} 
      } 
      if ( nest [p ].mlfield < 0 ) 
      print ( 382 ) ;
      if ( p == 0 ) 
      {
	if ( memtop - 2 != pagetail ) 
	{
	  printnl ( 1037 ) ;
	  if ( outputactive ) 
	  print ( 1038 ) ;
	  showbox ( mem [memtop - 2 ].hh .v.RH ) ;
	  if ( pagecontents > 0 ) 
	  {
	    printnl ( 1039 ) ;
	    printtotals () ;
	    printnl ( 1040 ) ;
	    printscaled ( pagesofar [0 ]) ;
	    r = mem [memtop ].hh .v.RH ;
	    while ( r != memtop ) {
		
	      println () ;
	      printesc ( 336 ) ;
	      t = mem [r ].hh.b1 ;
	      printint ( t ) ;
	      print ( 1041 ) ;
	      if ( eqtb [28526 + t ].cint == 1000 ) 
	      t = mem [r + 3 ].cint ;
	      else t = xovern ( mem [r + 3 ].cint , 1000 ) * eqtb [28526 + 
	      t ].cint ;
	      printscaled ( t ) ;
	      if ( mem [r ].hh.b0 == 1 ) 
	      {
		q = memtop - 2 ;
		t = 0 ;
		do {
		    q = mem [q ].hh .v.RH ;
		  if ( ( mem [q ].hh.b0 == 4 ) && ( mem [q ].hh.b1 == mem 
		  [r ].hh.b1 ) ) 
		  incr ( t ) ;
		} while ( ! ( q == mem [r + 1 ].hh .v.LH ) ) ;
		print ( 1042 ) ;
		printint ( t ) ;
		print ( 1043 ) ;
	      } 
	      r = mem [r ].hh .v.RH ;
	    } 
	  } 
	} 
	if ( mem [memtop - 1 ].hh .v.RH != -1073741823L ) 
	printnl ( 383 ) ;
      } 
      showbox ( mem [nest [p ].headfield ].hh .v.RH ) ;
      switch ( abs ( m ) / ( 116 ) ) 
      {case 0 : 
	{
	  printnl ( 384 ) ;
	  if ( a .cint <= -65536000L ) 
	  print ( 385 ) ;
	  else printscaled ( a .cint ) ;
	  if ( nest [p ].pgfield != 0 ) 
	  {
	    print ( 386 ) ;
	    printint ( nest [p ].pgfield ) ;
	    if ( nest [p ].pgfield != 1 ) 
	    print ( 387 ) ;
	    else print ( 388 ) ;
	  } 
	} 
	break ;
      case 1 : 
	{
	  printnl ( 389 ) ;
	  printint ( a .hh .v.LH ) ;
	  if ( m > 0 ) {
	      
	    if ( a .hh .v.RH > 0 ) 
	    {
	      print ( 390 ) ;
	      printint ( a .hh .v.RH ) ;
	    } 
	  } 
	} 
	break ;
      case 2 : 
	if ( a .cint != -1073741823L ) 
	{
	  print ( 391 ) ;
	  showbox ( a .cint ) ;
	} 
	break ;
      } 
    } 
  while ( p-- > for_end ) ;} 
} 
void 
zprintparam ( integer n ) 
{
  printparam_regmem 
  switch ( n ) 
  {case 0 : 
    printesc ( 444 ) ;
    break ;
  case 1 : 
    printesc ( 445 ) ;
    break ;
  case 2 : 
    printesc ( 446 ) ;
    break ;
  case 3 : 
    printesc ( 447 ) ;
    break ;
  case 4 : 
    printesc ( 448 ) ;
    break ;
  case 5 : 
    printesc ( 449 ) ;
    break ;
  case 6 : 
    printesc ( 450 ) ;
    break ;
  case 7 : 
    printesc ( 451 ) ;
    break ;
  case 8 : 
    printesc ( 452 ) ;
    break ;
  case 9 : 
    printesc ( 453 ) ;
    break ;
  case 10 : 
    printesc ( 454 ) ;
    break ;
  case 11 : 
    printesc ( 455 ) ;
    break ;
  case 12 : 
    printesc ( 456 ) ;
    break ;
  case 13 : 
    printesc ( 457 ) ;
    break ;
  case 14 : 
    printesc ( 458 ) ;
    break ;
  case 15 : 
    printesc ( 459 ) ;
    break ;
  case 16 : 
    printesc ( 460 ) ;
    break ;
  case 17 : 
    printesc ( 461 ) ;
    break ;
  case 18 : 
    printesc ( 462 ) ;
    break ;
  case 19 : 
    printesc ( 463 ) ;
    break ;
  case 20 : 
    printesc ( 464 ) ;
    break ;
  case 21 : 
    printesc ( 465 ) ;
    break ;
  case 22 : 
    printesc ( 466 ) ;
    break ;
  case 23 : 
    printesc ( 467 ) ;
    break ;
  case 24 : 
    printesc ( 468 ) ;
    break ;
  case 25 : 
    printesc ( 469 ) ;
    break ;
  case 26 : 
    printesc ( 470 ) ;
    break ;
  case 27 : 
    printesc ( 471 ) ;
    break ;
  case 28 : 
    printesc ( 472 ) ;
    break ;
  case 29 : 
    printesc ( 473 ) ;
    break ;
  case 30 : 
    printesc ( 474 ) ;
    break ;
  case 31 : 
    printesc ( 475 ) ;
    break ;
  case 32 : 
    printesc ( 476 ) ;
    break ;
  case 33 : 
    printesc ( 477 ) ;
    break ;
  case 34 : 
    printesc ( 478 ) ;
    break ;
  case 35 : 
    printesc ( 479 ) ;
    break ;
  case 36 : 
    printesc ( 480 ) ;
    break ;
  case 37 : 
    printesc ( 481 ) ;
    break ;
  case 38 : 
    printesc ( 482 ) ;
    break ;
  case 39 : 
    printesc ( 483 ) ;
    break ;
  case 40 : 
    printesc ( 484 ) ;
    break ;
  case 41 : 
    printesc ( 485 ) ;
    break ;
  case 42 : 
    printesc ( 486 ) ;
    break ;
  case 43 : 
    printesc ( 487 ) ;
    break ;
  case 44 : 
    printesc ( 488 ) ;
    break ;
  case 46 : 
    printesc ( 489 ) ;
    break ;
  case 47 : 
    printesc ( 490 ) ;
    break ;
  case 48 : 
    printesc ( 491 ) ;
    break ;
  case 49 : 
    printesc ( 492 ) ;
    break ;
  case 50 : 
    printesc ( 493 ) ;
    break ;
  case 45 : 
    printesc ( 494 ) ;
    break ;
  case 56 : 
    printesc ( 495 ) ;
    break ;
  case 57 : 
    printesc ( 496 ) ;
    break ;
  case 58 : 
    printesc ( 497 ) ;
    break ;
  case 59 : 
    printesc ( 498 ) ;
    break ;
  case 51 : 
    printesc ( 499 ) ;
    break ;
  case 52 : 
    printesc ( 500 ) ;
    break ;
  case 53 : 
    printesc ( 501 ) ;
    break ;
  case 54 : 
    printesc ( 502 ) ;
    break ;
  case 55 : 
    printesc ( 503 ) ;
    break ;
  case 60 : 
    printesc ( 504 ) ;
    break ;
  case 61 : 
    printesc ( 505 ) ;
    break ;
  case 62 : 
    printesc ( 506 ) ;
    break ;
    default: 
    print ( 507 ) ;
    break ;
  } 
} 
void 
begindiagnostic ( void ) 
{
  begindiagnostic_regmem 
  oldsetting = selector ;
  if ( ( eqtb [28491 ].cint <= 0 ) && ( selector == 19 ) ) 
  {
    decr ( selector ) ;
    if ( history == 0 ) 
    history = 1 ;
  } 
} 
void 
zenddiagnostic ( boolean blankline ) 
{
  enddiagnostic_regmem 
  printnl ( 344 ) ;
  if ( blankline ) 
  println () ;
  selector = oldsetting ;
} 
void 
zprintlengthparam ( integer n ) 
{
  printlengthparam_regmem 
  switch ( n ) 
  {case 0 : 
    printesc ( 510 ) ;
    break ;
  case 1 : 
    printesc ( 511 ) ;
    break ;
  case 2 : 
    printesc ( 512 ) ;
    break ;
  case 3 : 
    printesc ( 513 ) ;
    break ;
  case 4 : 
    printesc ( 514 ) ;
    break ;
  case 5 : 
    printesc ( 515 ) ;
    break ;
  case 6 : 
    printesc ( 516 ) ;
    break ;
  case 7 : 
    printesc ( 517 ) ;
    break ;
  case 8 : 
    printesc ( 518 ) ;
    break ;
  case 9 : 
    printesc ( 519 ) ;
    break ;
  case 10 : 
    printesc ( 520 ) ;
    break ;
  case 11 : 
    printesc ( 521 ) ;
    break ;
  case 12 : 
    printesc ( 522 ) ;
    break ;
  case 13 : 
    printesc ( 523 ) ;
    break ;
  case 14 : 
    printesc ( 524 ) ;
    break ;
  case 15 : 
    printesc ( 525 ) ;
    break ;
  case 16 : 
    printesc ( 526 ) ;
    break ;
  case 17 : 
    printesc ( 527 ) ;
    break ;
  case 18 : 
    printesc ( 528 ) ;
    break ;
  case 19 : 
    printesc ( 529 ) ;
    break ;
  case 21 : 
    printesc ( 530 ) ;
    break ;
  case 22 : 
    printesc ( 531 ) ;
    break ;
  case 20 : 
    printesc ( 532 ) ;
    break ;
    default: 
    print ( 533 ) ;
    break ;
  } 
} 
void 
zprintcmdchr ( quarterword cmd , halfword chrcode ) 
{
  printcmdchr_regmem 
  switch ( cmd ) 
  {case 1 : 
    {
      print ( 595 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 2 : 
    {
      print ( 596 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 3 : 
    {
      print ( 597 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 6 : 
    {
      print ( 598 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 7 : 
    {
      print ( 599 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 8 : 
    {
      print ( 600 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 9 : 
    print ( 601 ) ;
    break ;
  case 10 : 
    {
      print ( 602 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 11 : 
    {
      print ( 603 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 12 : 
    {
      print ( 604 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 16 : 
  case 17 : 
  case 18 : 
  case 19 : 
    {
      print ( 605 ) ;
      printkanji ( chrcode ) ;
    } 
    break ;
  case 83 : 
  case 84 : 
    if ( chrcode < 24548 ) 
    printskipparam ( chrcode - 24527 ) ;
    else if ( chrcode < 24804 ) 
    {
      printesc ( 414 ) ;
      printint ( chrcode - 24548 ) ;
    } 
    else {
	
      printesc ( 415 ) ;
      printint ( chrcode - 24804 ) ;
    } 
    break ;
  case 80 : 
    if ( chrcode >= 25070 ) 
    {
      printesc ( 426 ) ;
      printint ( chrcode - 25070 ) ;
    } 
    else switch ( chrcode ) 
    {case 25061 : 
      printesc ( 417 ) ;
      break ;
    case 25062 : 
      printesc ( 418 ) ;
      break ;
    case 25063 : 
      printesc ( 419 ) ;
      break ;
    case 25064 : 
      printesc ( 420 ) ;
      break ;
    case 25065 : 
      printesc ( 421 ) ;
      break ;
    case 25066 : 
      printesc ( 422 ) ;
      break ;
    case 25067 : 
      printesc ( 423 ) ;
      break ;
    case 25068 : 
      printesc ( 424 ) ;
      break ;
      default: 
      printesc ( 425 ) ;
      break ;
    } 
    break ;
  case 81 : 
    if ( chrcode < 28526 ) 
    printparam ( chrcode - 28462 ) ;
    else {
	
      printesc ( 508 ) ;
      printint ( chrcode - 28526 ) ;
    } 
    break ;
  case 82 : 
    if ( chrcode < 29061 ) 
    printlengthparam ( chrcode - 29038 ) ;
    else {
	
      printesc ( 534 ) ;
      printint ( chrcode - 29061 ) ;
    } 
    break ;
  case 49 : 
    printesc ( 543 ) ;
    break ;
  case 103 : 
    printesc ( 544 ) ;
    break ;
  case 44 : 
    printesc ( 545 ) ;
    break ;
  case 45 : 
    printesc ( 546 ) ;
    break ;
  case 85 : 
    printesc ( 557 ) ;
    break ;
  case 66 : 
    printesc ( 547 ) ;
    break ;
  case 46 : 
    printesc ( 569 ) ;
    break ;
  case 20 : 
    printesc ( 548 ) ;
    break ;
  case 122 : 
    printesc ( 539 ) ;
    break ;
  case 99 : 
    printesc ( 554 ) ;
    break ;
  case 100 : 
    printesc ( 555 ) ;
    break ;
  case 101 : 
    printesc ( 556 ) ;
    break ;
  case 15 : 
    printesc ( 550 ) ;
    break ;
  case 105 : 
    printesc ( 551 ) ;
    break ;
  case 72 : 
    printesc ( 540 ) ;
    break ;
  case 67 : 
    printesc ( 552 ) ;
    break ;
  case 69 : 
    printesc ( 32 ) ;
    break ;
  case 117 : 
    printesc ( 553 ) ;
    break ;
  case 36 : 
    printesc ( 558 ) ;
    break ;
  case 40 : 
    printesc ( 559 ) ;
    break ;
  case 43 : 
    printesc ( 560 ) ;
    break ;
  case 41 : 
    printesc ( 336 ) ;
    break ;
  case 48 : 
    printesc ( 47 ) ;
    break ;
  case 54 : 
    printesc ( 549 ) ;
    break ;
  case 22 : 
    printesc ( 359 ) ;
    break ;
  case 50 : 
    printesc ( 561 ) ;
    break ;
  case 21 : 
    printesc ( 562 ) ;
    break ;
  case 59 : 
    printesc ( 563 ) ;
    break ;
  case 104 : 
    printesc ( 564 ) ;
    break ;
  case 38 : 
    printesc ( 565 ) ;
    break ;
  case 70 : 
    printesc ( 566 ) ;
    break ;
  case 118 : 
    printesc ( 567 ) ;
    break ;
  case 60 : 
    printesc ( 341 ) ;
    break ;
  case 68 : 
    printesc ( 568 ) ;
    break ;
  case 71 : 
    printesc ( 571 ) ;
    break ;
  case 109 : 
    printesc ( 572 ) ;
    break ;
  case 0 : 
    printesc ( 573 ) ;
    break ;
  case 111 : 
    printesc ( 574 ) ;
    break ;
  case 91 : 
    printesc ( 570 ) ;
    break ;
  case 95 : 
    printesc ( 427 ) ;
    break ;
  case 124 : 
    printesc ( 575 ) ;
    break ;
  case 79 : 
    printesc ( 426 ) ;
    break ;
  case 42 : 
    printesc ( 360 ) ;
    break ;
  case 37 : 
    printesc ( 576 ) ;
    break ;
  case 61 : 
    printesc ( 577 ) ;
    break ;
  case 39 : 
    printesc ( 578 ) ;
    break ;
  case 13 : 
    printesc ( 635 ) ;
    break ;
  case 119 : 
    if ( chrcode == 0 ) 
    printesc ( 670 ) ;
    else printesc ( 671 ) ;
    break ;
  case 125 : 
    switch ( chrcode ) 
    {case 1 : 
      printesc ( 673 ) ;
      break ;
    case 2 : 
      printesc ( 674 ) ;
      break ;
    case 3 : 
      printesc ( 675 ) ;
      break ;
    case 4 : 
      printesc ( 676 ) ;
      break ;
      default: 
      printesc ( 672 ) ;
      break ;
    } 
    break ;
  case 102 : 
    if ( chrcode == 0 ) 
    printesc ( 508 ) ;
    else if ( chrcode == 1 ) 
    printesc ( 534 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 414 ) ;
    else printesc ( 415 ) ;
    break ;
  case 90 : 
    if ( chrcode == 1 ) 
    printesc ( 710 ) ;
    else printesc ( 709 ) ;
    break ;
  case 93 : 
    if ( chrcode == 0 ) 
    printesc ( 711 ) ;
    else printesc ( 712 ) ;
    break ;
  case 94 : 
    if ( chrcode == 1 ) 
    printesc ( 713 ) ;
    else if ( chrcode == 3 ) 
    printesc ( 714 ) ;
    else printesc ( 715 ) ;
    break ;
  case 76 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 716 ) ;
      break ;
    case 1 : 
      printesc ( 717 ) ;
      break ;
    case 2 : 
      printesc ( 718 ) ;
      break ;
    case 3 : 
      printesc ( 719 ) ;
      break ;
      default: 
      printesc ( 720 ) ;
      break ;
    } 
    break ;
  case 123 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 778 ) ;
      break ;
    case 1 : 
      printesc ( 779 ) ;
      break ;
    case 3 : 
      printesc ( 780 ) ;
      break ;
    case 4 : 
      printesc ( 781 ) ;
      break ;
    case 5 : 
      printesc ( 782 ) ;
      break ;
    case 2 : 
      printesc ( 783 ) ;
      break ;
    case 6 : 
      printesc ( 784 ) ;
      break ;
    case 7 : 
      printesc ( 785 ) ;
      break ;
    case 8 : 
      printesc ( 786 ) ;
      break ;
    case 9 : 
      printesc ( 787 ) ;
      break ;
    case 10 : 
      printesc ( 788 ) ;
      break ;
      default: 
      printesc ( 789 ) ;
      break ;
    } 
    break ;
  case 120 : 
    switch ( chrcode ) 
    {case 1 : 
      printesc ( 806 ) ;
      break ;
    case 2 : 
      printesc ( 807 ) ;
      break ;
    case 3 : 
      printesc ( 808 ) ;
      break ;
    case 4 : 
      printesc ( 809 ) ;
      break ;
    case 5 : 
      printesc ( 810 ) ;
      break ;
    case 6 : 
      printesc ( 811 ) ;
      break ;
    case 7 : 
      printesc ( 812 ) ;
      break ;
    case 8 : 
      printesc ( 813 ) ;
      break ;
    case 9 : 
      printesc ( 814 ) ;
      break ;
    case 10 : 
      printesc ( 815 ) ;
      break ;
    case 11 : 
      printesc ( 816 ) ;
      break ;
    case 12 : 
      printesc ( 817 ) ;
      break ;
    case 13 : 
      printesc ( 818 ) ;
      break ;
    case 14 : 
      printesc ( 819 ) ;
      break ;
    case 15 : 
      printesc ( 820 ) ;
      break ;
    case 16 : 
      printesc ( 821 ) ;
      break ;
    case 17 : 
      printesc ( 822 ) ;
      break ;
    case 18 : 
      printesc ( 823 ) ;
      break ;
    case 19 : 
      printesc ( 824 ) ;
      break ;
    case 20 : 
      printesc ( 825 ) ;
      break ;
    case 21 : 
      printesc ( 826 ) ;
      break ;
    case 22 : 
      printesc ( 827 ) ;
      break ;
    case 23 : 
      printesc ( 828 ) ;
      break ;
      default: 
      printesc ( 805 ) ;
      break ;
    } 
    break ;
  case 121 : 
    if ( chrcode == 2 ) 
    printesc ( 829 ) ;
    else if ( chrcode == 4 ) 
    printesc ( 830 ) ;
    else printesc ( 831 ) ;
    break ;
  case 4 : 
    if ( chrcode == 256 ) 
    printesc ( 955 ) ;
    else {
	
      print ( 959 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 5 : 
    if ( chrcode == 257 ) 
    printesc ( 956 ) ;
    else printesc ( 957 ) ;
    break ;
  case 92 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 1027 ) ;
      break ;
    case 1 : 
      printesc ( 1028 ) ;
      break ;
    case 2 : 
      printesc ( 1029 ) ;
      break ;
    case 3 : 
      printesc ( 1030 ) ;
      break ;
    case 4 : 
      printesc ( 1031 ) ;
      break ;
    case 5 : 
      printesc ( 1032 ) ;
      break ;
    case 6 : 
      printesc ( 1033 ) ;
      break ;
      default: 
      printesc ( 1034 ) ;
      break ;
    } 
    break ;
  case 14 : 
    if ( chrcode == 1 ) 
    printesc ( 1084 ) ;
    else printesc ( 1083 ) ;
    break ;
  case 30 : 
    switch ( chrcode ) 
    {case 4 : 
      printesc ( 1085 ) ;
      break ;
    case 0 : 
      printesc ( 1086 ) ;
      break ;
    case 1 : 
      printesc ( 1087 ) ;
      break ;
    case 2 : 
      printesc ( 1088 ) ;
      break ;
      default: 
      printesc ( 1089 ) ;
      break ;
    } 
    break ;
  case 31 : 
    switch ( chrcode ) 
    {case 4 : 
      printesc ( 1090 ) ;
      break ;
    case 0 : 
      printesc ( 1091 ) ;
      break ;
    case 1 : 
      printesc ( 1092 ) ;
      break ;
    case 2 : 
      printesc ( 1093 ) ;
      break ;
      default: 
      printesc ( 1094 ) ;
      break ;
    } 
    break ;
  case 32 : 
    printesc ( 342 ) ;
    break ;
  case 33 : 
    printesc ( 346 ) ;
    break ;
  case 34 : 
    printesc ( 348 ) ;
    break ;
  case 25 : 
    if ( chrcode == 1 ) 
    printesc ( 1112 ) ;
    else printesc ( 1113 ) ;
    break ;
  case 26 : 
    if ( chrcode == 1 ) 
    printesc ( 1114 ) ;
    else printesc ( 1115 ) ;
    break ;
  case 24 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 428 ) ;
      break ;
    case 1 : 
      printesc ( 1116 ) ;
      break ;
    case 2 : 
      printesc ( 1117 ) ;
      break ;
    case 3 : 
      printesc ( 1022 ) ;
      break ;
    case 4 : 
      printesc ( 1118 ) ;
      break ;
    case 5 : 
      printesc ( 1024 ) ;
      break ;
      default: 
      printesc ( 1119 ) ;
      break ;
    } 
    break ;
  case 78 : 
    switch ( chrcode ) 
    {case 4 : 
      printesc ( 1121 ) ;
      break ;
    case 3 : 
      printesc ( 1120 ) ;
      break ;
    case 1 : 
      printesc ( 1122 ) ;
      break ;
    } 
    break ;
  case 35 : 
    if ( chrcode == 100 ) 
    printesc ( 1124 ) ;
    else if ( chrcode == 101 ) 
    printesc ( 1125 ) ;
    else if ( chrcode == 102 ) 
    printesc ( 1126 ) ;
    else printesc ( 1123 ) ;
    break ;
  case 47 : 
    if ( chrcode == 0 ) 
    printesc ( 1149 ) ;
    else printesc ( 1148 ) ;
    break ;
  case 29 : 
    if ( chrcode == 12 ) 
    printesc ( 1162 ) ;
    else if ( chrcode == 13 ) 
    printesc ( 1161 ) ;
    else printesc ( 1160 ) ;
    break ;
  case 27 : 
    if ( chrcode == 1 ) 
    printesc ( 1164 ) ;
    else printesc ( 1163 ) ;
    break ;
  case 28 : 
    if ( chrcode == 1 ) 
    printesc ( 1166 ) ;
    else printesc ( 1165 ) ;
    break ;
  case 51 : 
    if ( chrcode == 1 ) 
    printesc ( 45 ) ;
    else printesc ( 357 ) ;
    break ;
  case 52 : 
    if ( chrcode == 1 ) 
    printesc ( 1200 ) ;
    else printesc ( 1199 ) ;
    break ;
  case 55 : 
    switch ( chrcode ) 
    {case 18 : 
      printesc ( 922 ) ;
      break ;
    case 19 : 
      printesc ( 923 ) ;
      break ;
    case 20 : 
      printesc ( 924 ) ;
      break ;
    case 21 : 
      printesc ( 925 ) ;
      break ;
    case 22 : 
      printesc ( 926 ) ;
      break ;
    case 23 : 
      printesc ( 927 ) ;
      break ;
    case 24 : 
      printesc ( 928 ) ;
      break ;
    case 25 : 
      printesc ( 929 ) ;
      break ;
    case 28 : 
      printesc ( 931 ) ;
      break ;
      default: 
      printesc ( 930 ) ;
      break ;
    } 
    break ;
  case 56 : 
    if ( chrcode == 1 ) 
    printesc ( 934 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 935 ) ;
    else printesc ( 1204 ) ;
    break ;
  case 58 : 
    printstyle ( chrcode ) ;
    break ;
  case 57 : 
    switch ( chrcode ) 
    {case 1 : 
      printesc ( 1223 ) ;
      break ;
    case 2 : 
      printesc ( 1224 ) ;
      break ;
    case 3 : 
      printesc ( 1225 ) ;
      break ;
    case 4 : 
      printesc ( 1226 ) ;
      break ;
    case 5 : 
      printesc ( 1227 ) ;
      break ;
      default: 
      printesc ( 1222 ) ;
      break ;
    } 
    break ;
  case 53 : 
    if ( chrcode == 32 ) 
    printesc ( 932 ) ;
    else printesc ( 933 ) ;
    break ;
  case 106 : 
    if ( chrcode == 1 ) 
    printesc ( 1246 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 1247 ) ;
    else printesc ( 1248 ) ;
    break ;
  case 110 : 
    if ( chrcode == 0 ) 
    printesc ( 1249 ) ;
    else if ( chrcode == 1 ) 
    printesc ( 1250 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 1251 ) ;
    else printesc ( 1252 ) ;
    break ;
  case 107 : 
    if ( chrcode != 0 ) 
    printesc ( 1267 ) ;
    else printesc ( 1266 ) ;
    break ;
  case 108 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 1268 ) ;
      break ;
    case 8 : 
      printesc ( 1269 ) ;
      break ;
    case 1 : 
      printesc ( 1270 ) ;
      break ;
    case 2 : 
      printesc ( 1271 ) ;
      break ;
    case 3 : 
      printesc ( 1272 ) ;
      break ;
    case 4 : 
      printesc ( 1273 ) ;
      break ;
    case 5 : 
      printesc ( 1274 ) ;
      break ;
    case 7 : 
      printesc ( 1276 ) ;
      break ;
      default: 
      printesc ( 1275 ) ;
      break ;
    } 
    break ;
  case 73 : 
    {
      printesc ( 548 ) ;
      printhex ( chrcode ) ;
    } 
    break ;
  case 74 : 
    {
      printesc ( 549 ) ;
      printhex ( chrcode ) ;
    } 
    break ;
  case 75 : 
    {
      printesc ( 562 ) ;
      printhex ( chrcode ) ;
    } 
    break ;
  case 96 : 
    if ( chrcode == 25636 ) 
    printesc ( 434 ) ;
    else if ( chrcode == 25892 ) 
    printesc ( 435 ) ;
    else if ( chrcode == 26404 ) 
    printesc ( 436 ) ;
    else if ( chrcode == 27950 ) 
    printesc ( 443 ) ;
    else if ( chrcode == 27182 ) 
    printesc ( 440 ) ;
    else if ( chrcode == 27438 ) 
    printesc ( 441 ) ;
    else if ( chrcode == 27694 ) 
    printesc ( 442 ) ;
    else printesc ( 509 ) ;
    break ;
  case 97 : 
    printsize ( chrcode - 25583 ) ;
    break ;
  case 112 : 
    if ( chrcode == 1 ) 
    printesc ( 1010 ) ;
    else printesc ( 998 ) ;
    break ;
  case 86 : 
    if ( chrcode == 0 ) 
    printesc ( 1298 ) ;
    else printesc ( 1299 ) ;
    break ;
  case 98 : 
    {
      print ( 1307 ) ;
      slowprint ( fontname [chrcode ]) ;
      if ( fontsize [chrcode ]!= fontdsize [chrcode ]) 
      {
	print ( 790 ) ;
	printscaled ( fontsize [chrcode ]) ;
	print ( 416 ) ;
      } 
    } 
    break ;
  case 113 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 273 ) ;
      break ;
    case 1 : 
      printesc ( 274 ) ;
      break ;
    case 2 : 
      printesc ( 275 ) ;
      break ;
      default: 
      printesc ( 1308 ) ;
      break ;
    } 
    break ;
  case 65 : 
    if ( chrcode == 0 ) 
    printesc ( 1310 ) ;
    else printesc ( 1309 ) ;
    break ;
  case 63 : 
    if ( chrcode == 0 ) 
    printesc ( 1311 ) ;
    else printesc ( 1312 ) ;
    break ;
  case 62 : 
    if ( chrcode == 27182 ) 
    printesc ( 1318 ) ;
    else printesc ( 1319 ) ;
    break ;
  case 23 : 
    switch ( chrcode ) 
    {case 1 : 
      printesc ( 1321 ) ;
      break ;
    case 2 : 
      printesc ( 1322 ) ;
      break ;
    case 3 : 
      printesc ( 1323 ) ;
      break ;
    case 4 : 
      printesc ( 1324 ) ;
      break ;
      default: 
      printesc ( 1320 ) ;
      break ;
    } 
    break ;
  case 116 : 
    print ( 1331 ) ;
    break ;
  case 126 : 
    print ( 1332 ) ;
    break ;
  case 127 : 
    printesc ( 1333 ) ;
    break ;
  case 128 : 
    printesc ( 1334 ) ;
    break ;
  case 129 : 
    {
      printesc ( 1246 ) ;
      printesc ( 1334 ) ;
    } 
    break ;
  case 130 : 
    printesc ( 1335 ) ;
    break ;
  case 64 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 1370 ) ;
      break ;
    case 1 : 
      printesc ( 632 ) ;
      break ;
    case 2 : 
      printesc ( 1371 ) ;
      break ;
    case 3 : 
      printesc ( 1372 ) ;
      break ;
    case 4 : 
      printesc ( 1373 ) ;
      break ;
    case 5 : 
      printesc ( 1374 ) ;
      break ;
      default: 
      print ( 1375 ) ;
      break ;
    } 
    break ;
  case 89 : 
    printesc ( 439 ) ;
    break ;
  case 114 : 
    {
      if ( ( chrcode % 2 ) == 0 ) 
      printesc ( 1410 ) ;
      else printesc ( 1411 ) ;
      if ( chrcode < 2 ) 
      print ( 1412 ) ;
      else print ( 1413 ) ;
    } 
    break ;
  case 115 : 
    {
      if ( chrcode == 0 ) 
      printesc ( 1414 ) ;
      else if ( chrcode == 1 ) 
      printesc ( 1415 ) ;
      else printesc ( 1416 ) ;
      print ( 1417 ) ;
    } 
    break ;
  case 77 : 
    printesc ( 1422 ) ;
    break ;
  case 88 : 
    printesc ( 1423 ) ;
    break ;
  case 87 : 
    switch ( chrcode ) 
    {case 1 : 
      printesc ( 1426 ) ;
      break ;
    case 2 : 
      printesc ( 1427 ) ;
      break ;
    } 
    break ;
    default: 
    print ( 606 ) ;
    break ;
  } 
} 
#ifdef STAT
void 
zshoweqtb ( halfword n ) 
{
  showeqtb_regmem 
  if ( n < 1 ) 
  printchar ( 63 ) ;
  else if ( ( n < 24527 ) || ( ( n > 29572 ) && ( n <= eqtbtop ) ) ) 
  {
    sprintcs ( n ) ;
    printchar ( 61 ) ;
    printcmdchr ( eqtb [n ].hh.b0 , eqtb [n ].hh .v.RH ) ;
    if ( eqtb [n ].hh.b0 >= 126 ) 
    {
      printchar ( 58 ) ;
      showtokenlist ( mem [eqtb [n ].hh .v.RH ].hh .v.RH , -1073741823L , 
      32 ) ;
    } 
  } 
  else if ( n < 25060 ) {
      
    if ( n < 24548 ) 
    {
      printskipparam ( n - 24527 ) ;
      printchar ( 61 ) ;
      if ( n < 24544 ) 
      printspec ( eqtb [n ].hh .v.RH , 416 ) ;
      else printspec ( eqtb [n ].hh .v.RH , 343 ) ;
    } 
    else if ( n < 24804 ) 
    {
      printesc ( 414 ) ;
      printint ( n - 24548 ) ;
      printchar ( 61 ) ;
      printspec ( eqtb [n ].hh .v.RH , 416 ) ;
    } 
    else {
	
      printesc ( 415 ) ;
      printint ( n - 24804 ) ;
      printchar ( 61 ) ;
      printspec ( eqtb [n ].hh .v.RH , 343 ) ;
    } 
  } 
  else if ( n < 28462 ) {
      
    if ( n == 25060 ) 
    {
      printesc ( 427 ) ;
      printchar ( 61 ) ;
      if ( eqtb [25060 ].hh .v.RH == -1073741823L ) 
      printchar ( 48 ) ;
      else printint ( mem [eqtb [25060 ].hh .v.RH ].hh .v.LH ) ;
    } 
    else if ( n < 25070 ) 
    {
      printcmdchr ( 80 , n ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH != -1073741823L ) 
      showtokenlist ( mem [eqtb [n ].hh .v.RH ].hh .v.RH , -1073741823L , 
      32 ) ;
    } 
    else if ( n < 25326 ) 
    {
      printesc ( 426 ) ;
      printint ( n - 25070 ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH != -1073741823L ) 
      showtokenlist ( mem [eqtb [n ].hh .v.RH ].hh .v.RH , -1073741823L , 
      32 ) ;
    } 
    else if ( n < 25582 ) 
    {
      printesc ( 428 ) ;
      printint ( n - 25326 ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH == -1073741823L ) 
      print ( 429 ) ;
      else {
	  
	depththreshold = 0 ;
	breadthmax = 1 ;
	shownodelist ( eqtb [n ].hh .v.RH ) ;
      } 
    } 
    else if ( n < 25636 ) 
    {
      if ( n == 25582 ) 
      print ( 430 ) ;
      else if ( n < 25599 ) 
      {
	printesc ( 431 ) ;
	printint ( n - 25583 ) ;
      } 
      else if ( n < 25615 ) 
      {
	printesc ( 432 ) ;
	printint ( n - 25599 ) ;
      } 
      else {
	  
	printesc ( 433 ) ;
	printint ( n - 25615 ) ;
      } 
      printchar ( 61 ) ;
      printesc ( hash [15525 + eqtb [n ].hh .v.RH ].v.RH ) ;
    } 
    else if ( n < 27950 ) 
    {
      if ( n < 25892 ) 
      {
	printesc ( 434 ) ;
	printint ( n - 25636 ) ;
      } 
      else if ( n < 26404 ) 
      {
	printesc ( 435 ) ;
	printint ( n - 25892 ) ;
      } 
      else if ( n < 26660 ) 
      {
	printesc ( 436 ) ;
	printint ( n - 26404 ) ;
      } 
      else if ( n < 26916 ) 
      {
	print ( 437 ) ;
	printint ( n - 26660 ) ;
      } 
      else if ( n < 27172 ) 
      {
	print ( 438 ) ;
	printint ( n - 26916 ) ;
      } 
      else if ( n < 27182 ) 
      {
	printesc ( 439 ) ;
	printint ( n - 27172 ) ;
      } 
      else if ( n < 27438 ) 
      {
	printesc ( 440 ) ;
	printint ( n - 27182 ) ;
      } 
      else if ( n < 27694 ) 
      {
	printesc ( 441 ) ;
	printint ( n - 27438 ) ;
      } 
      else {
	  
	printesc ( 442 ) ;
	printint ( n - 27694 ) ;
      } 
      printchar ( 61 ) ;
      printint ( eqtb [n ].hh .v.RH ) ;
    } 
    else {
	
      printesc ( 443 ) ;
      printint ( n - 27950 ) ;
      printchar ( 61 ) ;
      printint ( eqtb [n ].hh .v.RH ) ;
    } 
  } 
  else if ( n < 29038 ) 
  {
    if ( n < 28526 ) 
    printparam ( n - 28462 ) ;
    else if ( n < 28782 ) 
    {
      printesc ( 508 ) ;
      printint ( n - 28526 ) ;
    } 
    else {
	
      printesc ( 509 ) ;
      printint ( n - 28782 ) ;
    } 
    printchar ( 61 ) ;
    printint ( eqtb [n ].cint ) ;
  } 
  else if ( n < 29317 ) 
  {
    if ( n < 29061 ) 
    printlengthparam ( n - 29038 ) ;
    else {
	
      printesc ( 534 ) ;
      printint ( n - 29061 ) ;
    } 
    printchar ( 61 ) ;
    printscaled ( eqtb [n ].cint ) ;
    print ( 416 ) ;
  } 
  else if ( n <= 29572 ) 
  print ( 535 ) ;
  else printchar ( 63 ) ;
} 
#endif /* STAT */
halfword 
zidlookup ( integer j , integer l ) 
{
  /* 40 */ register halfword Result; idlookup_regmem 
  integer h  ;
  integer d  ;
  halfword p  ;
  halfword k  ;
  h = buffer [j ];
  {register integer for_end; k = j + 1 ;for_end = j + l - 1 ; if ( k <= 
  for_end) do 
    {
      h = h + h + buffer [k ];
      while ( h >= 8501 ) h = h - 8501 ;
    } 
  while ( k++ < for_end ) ;} 
  p = h + 514 ;
  while ( true ) {
      
    if ( hash [p ].v.RH > 0 ) {
	
      if ( ( strstart [hash [p ].v.RH + 1 ]- strstart [hash [p ].v.RH ]
      ) == l ) {
	  
	if ( streqbuf ( hash [p ].v.RH , j ) ) 
	goto lab40 ;
      } 
    } 
    if ( hash [p ].v.LH == 0 ) 
    {
      if ( nonewcontrolsequence ) 
      p = 24526 ;
      else {
	  
	if ( hash [p ].v.RH > 0 ) 
	{
	  if ( hashhigh < hashextra ) 
	  {
	    incr ( hashhigh ) ;
	    hash [p ].v.LH = hashhigh + 29572 ;
	    p = hashhigh + 29572 ;
	  } 
	  else {
	      
	    do {
		if ( ( hashused == 514 ) ) 
	      overflow ( 538 , 15000 + hashextra ) ;
	      decr ( hashused ) ;
	    } while ( ! ( hash [hashused ].v.RH == 0 ) ) ;
	    hash [p ].v.LH = hashused ;
	    p = hashused ;
	  } 
	} 
	{
	  if ( poolptr + l > poolsize ) 
	  overflow ( 258 , poolsize - initpoolptr ) ;
	} 
	d = ( poolptr - strstart [strptr ]) ;
	while ( poolptr > strstart [strptr ]) {
	    
	  decr ( poolptr ) ;
	  strpool [poolptr + l ]= strpool [poolptr ];
	} 
	{register integer for_end; k = j ;for_end = j + l - 1 ; if ( k <= 
	for_end) do 
	  {
	    strpool [poolptr ]= buffer [k ];
	    incr ( poolptr ) ;
	  } 
	while ( k++ < for_end ) ;} 
	hash [p ].v.RH = makestring () ;
	poolptr = poolptr + d ;
	;
#ifdef STAT
	incr ( cscount ) ;
#endif /* STAT */
      } 
      goto lab40 ;
    } 
    p = hash [p ].v.LH ;
  } 
  lab40: Result = p ;
  return Result ;
} 
void 
znewsavelevel ( groupcode c ) 
{
  newsavelevel_regmem 
  if ( saveptr > maxsavestack ) 
  {
    maxsavestack = saveptr ;
    if ( maxsavestack > savesize - 6 ) 
    overflow ( 579 , savesize ) ;
  } 
  savestack [saveptr ].hh.b0 = 3 ;
  savestack [saveptr ].hh.b1 = curgroup ;
  savestack [saveptr ].hh .v.RH = curboundary ;
  if ( curlevel == 65535L ) 
  overflow ( 580 , 65535L ) ;
  curboundary = saveptr ;
  incr ( curlevel ) ;
  incr ( saveptr ) ;
  curgroup = c ;
} 
void 
zeqdestroy ( memoryword w ) 
{
  eqdestroy_regmem 
  halfword q  ;
  switch ( w .hh.b0 ) 
  {case 126 : 
  case 127 : 
  case 128 : 
  case 129 : 
    deletetokenref ( w .hh .v.RH ) ;
    break ;
  case 132 : 
    deleteglueref ( w .hh .v.RH ) ;
    break ;
  case 133 : 
    {
      q = w .hh .v.RH ;
      if ( q != -1073741823L ) 
      freenode ( q , mem [q ].hh .v.LH + mem [q ].hh .v.LH + 1 ) ;
    } 
    break ;
  case 134 : 
    flushnodelist ( w .hh .v.RH ) ;
    break ;
    default: 
    ;
    break ;
  } 
} 
void 
zeqsave ( halfword p , quarterword l ) 
{
  eqsave_regmem 
  if ( saveptr > maxsavestack ) 
  {
    maxsavestack = saveptr ;
    if ( maxsavestack > savesize - 6 ) 
    overflow ( 579 , savesize ) ;
  } 
  if ( l == 0 ) 
  savestack [saveptr ].hh.b0 = 1 ;
  else {
      
    savestack [saveptr ]= eqtb [p ];
    incr ( saveptr ) ;
    savestack [saveptr ].hh.b0 = 0 ;
  } 
  savestack [saveptr ].hh.b1 = l ;
  savestack [saveptr ].hh .v.RH = p ;
  incr ( saveptr ) ;
} 
void 
zeqdefine ( halfword p , quarterword t , halfword e ) 
{
  eqdefine_regmem 
  if ( eqtb [p ].hh.b1 == curlevel ) 
  eqdestroy ( eqtb [p ]) ;
  else if ( curlevel > 1 ) 
  eqsave ( p , eqtb [p ].hh.b1 ) ;
  eqtb [p ].hh.b1 = curlevel ;
  eqtb [p ].hh.b0 = t ;
  eqtb [p ].hh .v.RH = e ;
} 
void 
zeqworddefine ( halfword p , integer w ) 
{
  eqworddefine_regmem 
  if ( xeqlevel [p ]!= curlevel ) 
  {
    eqsave ( p , xeqlevel [p ]) ;
    xeqlevel [p ]= curlevel ;
  } 
  eqtb [p ].cint = w ;
} 
void 
zgeqdefine ( halfword p , quarterword t , halfword e ) 
{
  geqdefine_regmem 
  eqdestroy ( eqtb [p ]) ;
  eqtb [p ].hh.b1 = 1 ;
  eqtb [p ].hh.b0 = t ;
  eqtb [p ].hh .v.RH = e ;
} 
void 
zgeqworddefine ( halfword p , integer w ) 
{
  geqworddefine_regmem 
  eqtb [p ].cint = w ;
  xeqlevel [p ]= 1 ;
} 
void 
zsaveforafter ( halfword t ) 
{
  saveforafter_regmem 
  if ( curlevel > 1 ) 
  {
    if ( saveptr > maxsavestack ) 
    {
      maxsavestack = saveptr ;
      if ( maxsavestack > savesize - 6 ) 
      overflow ( 579 , savesize ) ;
    } 
    savestack [saveptr ].hh.b0 = 2 ;
    savestack [saveptr ].hh.b1 = 0 ;
    savestack [saveptr ].hh .v.RH = t ;
    incr ( saveptr ) ;
  } 
} 
#ifdef STAT
void 
zrestoretrace ( halfword p , strnumber s ) 
{
  restoretrace_regmem 
  begindiagnostic () ;
  printchar ( 123 ) ;
  print ( s ) ;
  printchar ( 32 ) ;
  showeqtb ( p ) ;
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
#endif /* STAT */
void 
unsave ( void ) 
{
  /* 30 */ unsave_regmem 
  halfword p  ;
  quarterword l  ;
  halfword t  ;
  if ( curlevel > 1 ) 
  {
    decr ( curlevel ) ;
    while ( true ) {
	
      decr ( saveptr ) ;
      if ( savestack [saveptr ].hh.b0 == 3 ) 
      goto lab30 ;
      p = savestack [saveptr ].hh .v.RH ;
      if ( savestack [saveptr ].hh.b0 == 2 ) 
      {
	t = curtok ;
	curtok = p ;
	backinput () ;
	curtok = t ;
      } 
      else {
	  
	if ( savestack [saveptr ].hh.b0 == 0 ) 
	{
	  l = savestack [saveptr ].hh.b1 ;
	  decr ( saveptr ) ;
	} 
	else savestack [saveptr ]= eqtb [24526 ];
	if ( ( p < 28462 ) || ( p > 29572 ) ) {
	    
	  if ( eqtb [p ].hh.b1 == 1 ) 
	  {
	    eqdestroy ( savestack [saveptr ]) ;
	;
#ifdef STAT
	    if ( eqtb [28499 ].cint > 0 ) 
	    restoretrace ( p , 582 ) ;
#endif /* STAT */
	  } 
	  else {
	      
	    eqdestroy ( eqtb [p ]) ;
	    eqtb [p ]= savestack [saveptr ];
	;
#ifdef STAT
	    if ( eqtb [28499 ].cint > 0 ) 
	    restoretrace ( p , 583 ) ;
#endif /* STAT */
	  } 
	} 
	else if ( xeqlevel [p ]!= 1 ) 
	{
	  eqtb [p ]= savestack [saveptr ];
	  xeqlevel [p ]= l ;
	;
#ifdef STAT
	  if ( eqtb [28499 ].cint > 0 ) 
	  restoretrace ( p , 583 ) ;
#endif /* STAT */
	} 
	else {
	    
	;
#ifdef STAT
	  if ( eqtb [28499 ].cint > 0 ) 
	  restoretrace ( p , 582 ) ;
#endif /* STAT */
	} 
      } 
    } 
    lab30: curgroup = savestack [saveptr ].hh.b1 ;
    curboundary = savestack [saveptr ].hh .v.RH ;
  } 
  else confusion ( 581 ) ;
} 
void 
preparemag ( void ) 
{
  preparemag_regmem 
  if ( ( magset > 0 ) && ( eqtb [28479 ].cint != magset ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 585 ) ;
    } 
    printint ( eqtb [28479 ].cint ) ;
    print ( 586 ) ;
    printnl ( 587 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 588 ;
      helpline [0 ]= 589 ;
    } 
    interror ( magset ) ;
    geqworddefine ( 28479 , magset ) ;
  } 
  if ( ( eqtb [28479 ].cint <= 0 ) || ( eqtb [28479 ].cint > 32768L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 590 ) ;
    } 
    {
      helpptr = 1 ;
      helpline [0 ]= 591 ;
    } 
    interror ( eqtb [28479 ].cint ) ;
    geqworddefine ( 28479 , 1000 ) ;
  } 
  magset = eqtb [28479 ].cint ;
} 
void 
ztokenshow ( halfword p ) 
{
  tokenshow_regmem 
  if ( p != -1073741823L ) 
  showtokenlist ( mem [p ].hh .v.RH , -1073741823L , 10000000L ) ;
} 
void 
printmeaning ( void ) 
{
  printmeaning_regmem 
  printcmdchr ( curcmd , curchr ) ;
  if ( curcmd >= 126 ) 
  {
    printchar ( 58 ) ;
    println () ;
    tokenshow ( curchr ) ;
  } 
  else if ( curcmd == 125 ) 
  {
    printchar ( 58 ) ;
    println () ;
    tokenshow ( curmark [curchr ]) ;
  } 
} 
void 
showcurcmdchr ( void ) 
{
  showcurcmdchr_regmem 
  begindiagnostic () ;
  printnl ( 123 ) ;
  if ( curlist .modefield != shownmode ) 
  {
    printmode ( curlist .modefield ) ;
    print ( 607 ) ;
    shownmode = curlist .modefield ;
  } 
  printcmdchr ( curcmd , curchr ) ;
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
void 
showcontext ( void ) 
{
  /* 30 31 */ showcontext_regmem 
  unsigned char oldsetting  ;
  halfword s  ;
  integer nn  ;
  boolean bottomline  ;
  integer i  ;
  integer j  ;
  integer l  ;
  integer m  ;
  integer n  ;
  integer p  ;
  integer q  ;
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  nn = -1 ;
  bottomline = false ;
  while ( true ) {
      
    curinput = inputstack [baseptr ];
    if ( ( curinput .statefield != 0 ) ) {
	
      if ( ( curinput .namefield > 17 ) || ( baseptr == 0 ) ) 
      bottomline = true ;
    } 
    if ( ( baseptr == inputptr ) || bottomline || ( nn < eqtb [28517 ].cint 
    ) ) 
    {
      if ( ( baseptr == inputptr ) || ( curinput .statefield != 0 ) || ( 
      curinput .indexfield != 3 ) || ( curinput .locfield != -1073741823L ) ) 
      {
	tally = 0 ;
	oldsetting = selector ;
	if ( curinput .statefield != 0 ) 
	{
	  if ( curinput .namefield <= 17 ) {
	      
	    if ( ( curinput .namefield == 0 ) ) {
		
	      if ( baseptr == 0 ) 
	      printnl ( 612 ) ;
	      else printnl ( 613 ) ;
	    } 
	    else {
		
	      printnl ( 614 ) ;
	      if ( curinput .namefield == 17 ) 
	      printchar ( 42 ) ;
	      else printint ( curinput .namefield - 1 ) ;
	      printchar ( 62 ) ;
	    } 
	  } 
	  else {
	      
	    printnl ( 615 ) ;
	    printint ( line ) ;
	  } 
	  printchar ( 32 ) ;
	  {
	    l = tally ;
	    tally = 0 ;
	    selector = 20 ;
	    kcodepos = 0 ;
	    trickcount = 1000000L ;
	  } 
	  if ( buffer [curinput .limitfield ]== eqtb [28511 ].cint ) 
	  j = curinput .limitfield ;
	  else j = curinput .limitfield + 1 ;
	  if ( j > 0 ) 
	  {register integer for_end; i = curinput .startfield ;for_end = j - 
	  1 ; if ( i <= for_end) do 
	    {
	      if ( i == curinput .locfield ) 
	      {
		firstcount = tally ;
		kcp = trickbuf2 [( firstcount - 1 ) % errorline ];
		if ( ( firstcount > 0 ) && ( kcp > 0 ) ) 
		firstcount = firstcount + nrestmultichr ( kcp ) ;
		trickcount = firstcount + 1 + errorline - halferrorline ;
		if ( trickcount < errorline ) 
		trickcount = errorline ;
	      } 
	      print ( buffer [i ]) ;
	    } 
	  while ( i++ < for_end ) ;} 
	} 
	else {
	    
	  switch ( curinput .indexfield ) 
	  {case 0 : 
	    printnl ( 616 ) ;
	    break ;
	  case 1 : 
	  case 2 : 
	    printnl ( 617 ) ;
	    break ;
	  case 3 : 
	    if ( curinput .locfield == -1073741823L ) 
	    printnl ( 618 ) ;
	    else printnl ( 619 ) ;
	    break ;
	  case 4 : 
	    printnl ( 620 ) ;
	    break ;
	  case 5 : 
	    {
	      println () ;
	      printcs ( curinput .namefield ) ;
	    } 
	    break ;
	  case 6 : 
	    printnl ( 621 ) ;
	    break ;
	  case 7 : 
	    printnl ( 622 ) ;
	    break ;
	  case 8 : 
	    printnl ( 623 ) ;
	    break ;
	  case 9 : 
	    printnl ( 624 ) ;
	    break ;
	  case 10 : 
	    printnl ( 625 ) ;
	    break ;
	  case 11 : 
	    printnl ( 626 ) ;
	    break ;
	  case 12 : 
	    printnl ( 627 ) ;
	    break ;
	  case 13 : 
	    printnl ( 628 ) ;
	    break ;
	  case 14 : 
	    printnl ( 629 ) ;
	    break ;
	  case 15 : 
	    printnl ( 630 ) ;
	    break ;
	    default: 
	    printnl ( 63 ) ;
	    break ;
	  } 
	  {
	    l = tally ;
	    tally = 0 ;
	    selector = 20 ;
	    kcodepos = 0 ;
	    trickcount = 1000000L ;
	  } 
	  if ( curinput .indexfield < 5 ) 
	  {
	    if ( ( curinput .indexfield == 3 ) && ( curinput .locfield != 
	    -1073741823L ) ) 
	    {
	      if ( ( mem [curinput .startfield ].hh .v.RH == -1073741823L ) 
	      && ( checkkanji ( mem [curinput .startfield ].hh .v.LH ) ) ) 
	      {
		curinput = inputstack [baseptr - 1 ];
		s = getavail () ;
		mem [s ].hh .v.LH = ( mem [curinput .locfield ].hh .v.LH % 
		256 ) ;
		curinput = inputstack [baseptr ];
		mem [curinput .startfield ].hh .v.RH = s ;
		showtokenlist ( curinput .startfield , curinput .locfield , 
		100000L ) ;
		{
		  mem [s ].hh .v.RH = avail ;
		  avail = s ;
	;
#ifdef STAT
		  decr ( dynused ) ;
#endif /* STAT */
		} 
		mem [curinput .startfield ].hh .v.RH = -1073741823L ;
		goto lab31 ;
	      } 
	    } 
	    showtokenlist ( curinput .startfield , curinput .locfield , 
	    100000L ) ;
	  } 
	  else showtokenlist ( mem [curinput .startfield ].hh .v.RH , 
	  curinput .locfield , 100000L ) ;
	  lab31: ;
	} 
	selector = oldsetting ;
	if ( trickcount == 1000000L ) 
	{
	  firstcount = tally ;
	  kcp = trickbuf2 [( firstcount - 1 ) % errorline ];
	  if ( ( firstcount > 0 ) && ( kcp > 0 ) ) 
	  firstcount = firstcount + nrestmultichr ( kcp ) ;
	  trickcount = firstcount + 1 + errorline - halferrorline ;
	  if ( trickcount < errorline ) 
	  trickcount = errorline ;
	} 
	if ( tally < trickcount ) 
	m = tally - firstcount ;
	else m = trickcount - firstcount ;
	if ( l + firstcount <= halferrorline ) 
	{
	  p = 0 ;
	  n = l + firstcount ;
	} 
	else {
	    
	  print ( 276 ) ;
	  p = l + firstcount - halferrorline + 3 ;
	  n = halferrorline ;
	} 
	kcp = trickbuf2 [p % errorline ];
	if ( ( kcp % 8 ) > 1 ) 
	{
	  p = p + nrestmultichr ( kcp ) + 1 ;
	  n = n - nrestmultichr ( kcp ) - 1 ;
	} 
	{register integer for_end; q = p ;for_end = firstcount - 1 ; if ( q 
	<= for_end) do 
	  printchar ( trickbuf [q % errorline ]) ;
	while ( q++ < for_end ) ;} 
	println () ;
	{register integer for_end; q = 1 ;for_end = n ; if ( q <= for_end) 
	do 
	  printchar ( 32 ) ;
	while ( q++ < for_end ) ;} 
	if ( m + n <= errorline ) 
	p = firstcount + m ;
	else p = firstcount + ( errorline - n - 3 ) ;
	kcp = trickbuf2 [( p - 1 ) % errorline ];
	if ( ( ( kcp % 8 ) > 0 ) && ( nrestmultichr ( kcp ) > 0 ) ) 
	p = p - ( kcp % 8 ) ;
	{register integer for_end; q = firstcount ;for_end = p - 1 ; if ( q 
	<= for_end) do 
	  printchar ( trickbuf [q % errorline ]) ;
	while ( q++ < for_end ) ;} 
	if ( m + n > errorline ) 
	print ( 276 ) ;
	incr ( nn ) ;
      } 
    } 
    else if ( nn == eqtb [28517 ].cint ) 
    {
      printnl ( 276 ) ;
      incr ( nn ) ;
    } 
    if ( bottomline ) 
    goto lab30 ;
    decr ( baseptr ) ;
  } 
  lab30: curinput = inputstack [inputptr ];
} 
void 
zbegintokenlist ( halfword p , quarterword t ) 
{
  begintokenlist_regmem 
  {
    if ( inputptr > maxinstack ) 
    {
      maxinstack = inputptr ;
      if ( inputptr == stacksize ) 
      overflow ( 631 , stacksize ) ;
    } 
    inputstack [inputptr ]= curinput ;
    incr ( inputptr ) ;
  } 
  curinput .statefield = 0 ;
  curinput .startfield = p ;
  curinput .indexfield = t ;
  if ( t >= 5 ) 
  {
    incr ( mem [p ].hh .v.LH ) ;
    if ( t == 5 ) 
    curinput .limitfield = paramptr ;
    else {
	
      curinput .locfield = mem [p ].hh .v.RH ;
      if ( eqtb [28492 ].cint > 1 ) 
      {
	begindiagnostic () ;
	printnl ( 344 ) ;
	switch ( t ) 
	{case 14 : 
	  printesc ( 359 ) ;
	  break ;
	case 15 : 
	  printesc ( 632 ) ;
	  break ;
	  default: 
	  printcmdchr ( 80 , t + 25055 ) ;
	  break ;
	} 
	print ( 594 ) ;
	tokenshow ( p ) ;
	enddiagnostic ( false ) ;
      } 
    } 
  } 
  else curinput .locfield = p ;
} 
void 
endtokenlist ( void ) 
{
  endtokenlist_regmem 
  if ( curinput .indexfield >= 3 ) 
  {
    if ( curinput .indexfield <= 4 ) 
    flushlist ( curinput .startfield ) ;
    else {
	
      deletetokenref ( curinput .startfield ) ;
      if ( curinput .indexfield == 5 ) 
      while ( paramptr > curinput .limitfield ) {
	  
	decr ( paramptr ) ;
	flushlist ( paramstack [paramptr ]) ;
      } 
    } 
  } 
  else if ( curinput .indexfield == 1 ) {
      
    if ( alignstate > 500000L ) 
    alignstate = 0 ;
    else fatalerror ( 633 ) ;
  } 
  {
    decr ( inputptr ) ;
    curinput = inputstack [inputptr ];
  } 
  {
    if ( interrupt != 0 ) 
    pauseforinstructions () ;
  } 
} 
void 
backinput ( void ) 
{
  backinput_regmem 
  halfword p  ;
  while ( ( curinput .statefield == 0 ) && ( curinput .locfield == 
  -1073741823L ) && ( curinput .indexfield != 2 ) ) endtokenlist () ;
  p = getavail () ;
  mem [p ].hh .v.LH = curtok ;
  if ( curtok < 768 ) {
      
    if ( curtok < 512 ) 
    decr ( alignstate ) ;
    else incr ( alignstate ) ;
  } 
  {
    if ( inputptr > maxinstack ) 
    {
      maxinstack = inputptr ;
      if ( inputptr == stacksize ) 
      overflow ( 631 , stacksize ) ;
    } 
    inputstack [inputptr ]= curinput ;
    incr ( inputptr ) ;
  } 
  curinput .statefield = 0 ;
  curinput .startfield = p ;
  curinput .indexfield = 3 ;
  curinput .locfield = p ;
} 
void 
backerror ( void ) 
{
  backerror_regmem 
  OKtointerrupt = false ;
  backinput () ;
  OKtointerrupt = true ;
  error () ;
} 
void 
inserror ( void ) 
{
  inserror_regmem 
  OKtointerrupt = false ;
  backinput () ;
  curinput .indexfield = 4 ;
  OKtointerrupt = true ;
  error () ;
} 
void 
beginfilereading ( void ) 
{
  beginfilereading_regmem 
  if ( inopen == maxinopen ) 
  overflow ( 634 , maxinopen ) ;
  if ( first == bufsize ) 
  overflow ( 257 , bufsize ) ;
  incr ( inopen ) ;
  {
    if ( inputptr > maxinstack ) 
    {
      maxinstack = inputptr ;
      if ( inputptr == stacksize ) 
      overflow ( 631 , stacksize ) ;
    } 
    inputstack [inputptr ]= curinput ;
    incr ( inputptr ) ;
  } 
  curinput .indexfield = inopen ;
  sourcefilenamestack [curinput .indexfield ]= 0 ;
  fullsourcefilenamestack [curinput .indexfield ]= 0 ;
  linestack [curinput .indexfield ]= line ;
  curinput .startfield = first ;
  curinput .statefield = 1 ;
  curinput .namefield = 0 ;
  curinput .synctextagfield = 0 ;
} 
void 
endfilereading ( void ) 
{
  endfilereading_regmem 
  first = curinput .startfield ;
  line = linestack [curinput .indexfield ];
  if ( curinput .namefield > 17 ) 
  aclose ( inputfile [curinput .indexfield ]) ;
  {
    decr ( inputptr ) ;
    curinput = inputstack [inputptr ];
  } 
  decr ( inopen ) ;
} 
void 
clearforerrorprompt ( void ) 
{
  clearforerrorprompt_regmem 
  while ( ( curinput .statefield != 0 ) && ( curinput .namefield == 0 ) && ( 
  inputptr > 0 ) && ( curinput .locfield > curinput .limitfield ) ) 
  endfilereading () ;
  println () ;
} 
void 
checkoutervalidity ( void ) 
{
  checkoutervalidity_regmem 
  halfword p  ;
  halfword q  ;
  if ( scannerstatus != 0 ) 
  {
    deletionsallowed = false ;
    if ( curcs != 0 ) 
    {
      if ( ( curinput .statefield == 0 ) || ( curinput .namefield < 1 ) || ( 
      curinput .namefield > 17 ) ) 
      {
	p = getavail () ;
	mem [p ].hh .v.LH = 536870911L + curcs ;
	begintokenlist ( p , 3 ) ;
      } 
      curcmd = 10 ;
      curchr = 32 ;
    } 
    if ( scannerstatus > 1 ) 
    {
      runaway () ;
      if ( curcs == 0 ) 
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 642 ) ;
      } 
      else {
	  
	curcs = 0 ;
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 643 ) ;
	} 
      } 
      p = getavail () ;
      switch ( scannerstatus ) 
      {case 2 : 
	{
	  print ( 649 ) ;
	  mem [p ].hh .v.LH = 637 ;
	} 
	break ;
      case 3 : 
	{
	  print ( 650 ) ;
	  mem [p ].hh .v.LH = partoken ;
	  longstate = 128 ;
	} 
	break ;
      case 4 : 
	{
	  print ( 651 ) ;
	  mem [p ].hh .v.LH = 637 ;
	  q = p ;
	  p = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [p ].hh .v.LH = 536886426L ;
	  alignstate = -1000000L ;
	} 
	break ;
      case 5 : 
	{
	  print ( 652 ) ;
	  mem [p ].hh .v.LH = 637 ;
	} 
	break ;
      } 
      begintokenlist ( p , 4 ) ;
      print ( 644 ) ;
      sprintcs ( warningindex ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 645 ;
	helpline [2 ]= 646 ;
	helpline [1 ]= 647 ;
	helpline [0 ]= 648 ;
      } 
      error () ;
    } 
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 636 ) ;
      } 
      printcmdchr ( 120 , curif ) ;
      print ( 637 ) ;
      printint ( skipline ) ;
      {
	helpptr = 3 ;
	helpline [2 ]= 638 ;
	helpline [1 ]= 639 ;
	helpline [0 ]= 640 ;
      } 
      if ( curcs != 0 ) 
      curcs = 0 ;
      else helpline [2 ]= 641 ;
      curtok = 536886429L ;
      inserror () ;
    } 
    deletionsallowed = true ;
  } 
} 
void 
getnext ( void ) 
{
  /* 20 25 21 26 40 10 */ getnext_regmem 
  integer k  ;
  halfword t  ;
  unsigned char cat  ;
  integer l  ;
  ASCIIcode c, cc  ;
  unsigned char d  ;
  lab20: curcs = 0 ;
  if ( curinput .statefield != 0 ) 
  {
    lab25: if ( curinput .locfield <= curinput .limitfield ) 
    {
      curchr = fromBUFF ( ustringcast ( buffer ) , curinput .limitfield , 
      curinput .locfield ) ;
      curcmd = eqtb [25892 + kcatcodekey ( curchr ) ].hh .v.RH ;
      if ( ( multistrlen ( ustringcast ( buffer ) , curinput .limitfield , 
      curinput .locfield ) > 1 ) && checkkcatcode ( curcmd ) ) 
      {
	if ( ( curcmd == 15 ) ) 
	curcmd = 18 ;
	curinput .locfield = curinput .locfield + multistrlen ( ustringcast ( 
	buffer ) , curinput .limitfield , curinput .locfield ) ;
      } 
      else {
	  
	curchr = buffer [curinput .locfield ];
	incr ( curinput .locfield ) ;
	lab21: curcmd = eqtb [25636 + curchr ].hh .v.RH ;
      } 
      switch ( curinput .statefield + curcmd ) 
      {case 10 : 
      case 30 : 
      case 50 : 
      case 70 : 
      case 51 : 
      case 71 : 
	goto lab25 ;
	break ;
      case 1 : 
      case 21 : 
      case 41 : 
      case 61 : 
	{
	  if ( curinput .locfield > curinput .limitfield ) 
	  curcs = 513 ;
	  else {
	      
	    k = curinput .locfield ;
	    curchr = fromBUFF ( ustringcast ( buffer ) , curinput .limitfield 
	    , k ) ;
	    cat = eqtb [25892 + kcatcodekey ( curchr ) ].hh .v.RH ;
	    if ( ( multistrlen ( ustringcast ( buffer ) , curinput .limitfield 
	    , k ) > 1 ) && checkkcatcode ( cat ) ) 
	    {
	      if ( ( cat == 15 ) ) 
	      cat = 18 ;
	      k = k + multistrlen ( ustringcast ( buffer ) , curinput 
	      .limitfield , k ) ;
	    } 
	    else {
		
	      curchr = buffer [k ];
	      cat = eqtb [25636 + curchr ].hh .v.RH ;
	      incr ( k ) ;
	    } 
	    lab26: if ( ( cat == 11 ) || ( cat == 16 ) || ( cat == 17 ) || ( 
	    cat == 19 ) ) 
	    curinput .statefield = 41 ;
	    else if ( cat == 10 ) 
	    curinput .statefield = 41 ;
	    else curinput .statefield = 1 ;
	    if ( cat == 18 ) 
	    {
	      curcs = idlookup ( curinput .locfield , k - curinput .locfield ) 
	      ;
	      curinput .locfield = k ;
	      goto lab40 ;
	    } 
	    else if ( ( ( cat == 11 ) || ( cat == 16 ) || ( cat == 17 ) || ( 
	    cat == 19 ) ) && ( k <= curinput .limitfield ) ) 
	    {
	      do {
		  curchr = fromBUFF ( ustringcast ( buffer ) , curinput 
		.limitfield , k ) ;
		cat = eqtb [25892 + kcatcodekey ( curchr ) ].hh .v.RH ;
		if ( ( multistrlen ( ustringcast ( buffer ) , curinput 
		.limitfield , k ) > 1 ) && checkkcatcode ( cat ) ) 
		{
		  if ( ( cat == 15 ) ) 
		  cat = 18 ;
		  k = k + multistrlen ( ustringcast ( buffer ) , curinput 
		  .limitfield , k ) ;
		} 
		else {
		    
		  curchr = buffer [k ];
		  cat = eqtb [25636 + curchr ].hh .v.RH ;
		  incr ( k ) ;
		} 
		while ( ( buffer [k ]== curchr ) && ( cat == 7 ) && ( k < 
		curinput .limitfield ) ) {
		    
		  c = buffer [k + 1 ];
		  if ( c < 128 ) 
		  {
		    d = 2 ;
		    if ( ( ( ( c >= 48 ) && ( c <= 57 ) ) || ( ( c >= 97 ) && 
		    ( c <= 102 ) ) ) ) {
			
		      if ( k + 2 <= curinput .limitfield ) 
		      {
			cc = buffer [k + 2 ];
			if ( ( ( ( cc >= 48 ) && ( cc <= 57 ) ) || ( ( cc >= 
			97 ) && ( cc <= 102 ) ) ) ) 
			incr ( d ) ;
		      } 
		    } 
		    if ( d > 2 ) 
		    {
		      if ( c <= 57 ) 
		      curchr = c - 48 ;
		      else curchr = c - 87 ;
		      if ( cc <= 57 ) 
		      curchr = 16 * curchr + cc - 48 ;
		      else curchr = 16 * curchr + cc - 87 ;
		    } 
		    else if ( c < 64 ) 
		    curchr = c + 64 ;
		    else curchr = c - 64 ;
		    cat = eqtb [25636 + curchr ].hh .v.RH ;
		    if ( ( cat == 11 ) || ( cat == 7 ) ) 
		    {
		      buffer [k - 1 ]= curchr ;
		      curinput .limitfield = curinput .limitfield - d ;
		      first = first - d ;
		      l = k ;
		      while ( l <= curinput .limitfield ) {
			  
			buffer [l ]= buffer [l + d ];
			incr ( l ) ;
		      } 
		    } 
		  } 
		} 
	      } while ( ! ( ! ( ( cat == 11 ) || ( cat == 16 ) || ( cat == 17 
	      ) || ( cat == 19 ) ) || ( k > curinput .limitfield ) ) ) ;
	      if ( ! ( ( cat == 11 ) || ( cat == 16 ) || ( cat == 17 ) || ( 
	      cat == 19 ) ) ) 
	      decr ( k ) ;
	      if ( cat == 18 ) 
	      k = k - multilenbuffchar ( curchr ) + 1 ;
	      if ( k > curinput .locfield + 1 ) 
	      {
		curcs = idlookup ( curinput .locfield , k - curinput .locfield 
		) ;
		curinput .locfield = k ;
		goto lab40 ;
	      } 
	    } 
	    else {
		
	      if ( buffer [k ]== curchr ) {
		  
		if ( cat == 7 ) {
		    
		  if ( k < curinput .limitfield ) 
		  {
		    c = buffer [k + 1 ];
		    if ( c < 128 ) 
		    {
		      d = 2 ;
		      if ( ( ( ( c >= 48 ) && ( c <= 57 ) ) || ( ( c >= 97 ) 
		      && ( c <= 102 ) ) ) ) {
			  
			if ( k + 2 <= curinput .limitfield ) 
			{
			  cc = buffer [k + 2 ];
			  if ( ( ( ( cc >= 48 ) && ( cc <= 57 ) ) || ( ( cc >= 
			  97 ) && ( cc <= 102 ) ) ) ) 
			  incr ( d ) ;
			} 
		      } 
		      if ( d > 2 ) 
		      {
			if ( c <= 57 ) 
			curchr = c - 48 ;
			else curchr = c - 87 ;
			if ( cc <= 57 ) 
			curchr = 16 * curchr + cc - 48 ;
			else curchr = 16 * curchr + cc - 87 ;
			buffer [k - 1 ]= curchr ;
		      } 
		      else if ( c < 64 ) 
		      buffer [k - 1 ]= c + 64 ;
		      else buffer [k - 1 ]= c - 64 ;
		      curinput .limitfield = curinput .limitfield - d ;
		      first = first - d ;
		      l = k ;
		      curchr = buffer [k - 1 ];
		      cat = eqtb [25636 + curchr ].hh .v.RH ;
		      while ( l <= curinput .limitfield ) {
			  
			buffer [l ]= buffer [l + d ];
			incr ( l ) ;
		      } 
		      goto lab26 ;
		    } 
		  } 
		} 
	      } 
	    } 
	    curcs = 257 + buffer [curinput .locfield ];
	    incr ( curinput .locfield ) ;
	  } 
	  lab40: curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  if ( curcmd >= 128 ) 
	  checkoutervalidity () ;
	} 
	break ;
      case 14 : 
      case 34 : 
      case 54 : 
      case 74 : 
	{
	  curcs = curchr + 1 ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  curinput .statefield = 1 ;
	  if ( curcmd >= 128 ) 
	  checkoutervalidity () ;
	} 
	break ;
      case 8 : 
      case 28 : 
      case 48 : 
      case 68 : 
	{
	  if ( curchr == buffer [curinput .locfield ]) {
	      
	    if ( curinput .locfield < curinput .limitfield ) 
	    {
	      c = buffer [curinput .locfield + 1 ];
	      if ( c < 128 ) 
	      {
		curinput .locfield = curinput .locfield + 2 ;
		if ( ( ( ( c >= 48 ) && ( c <= 57 ) ) || ( ( c >= 97 ) && ( c 
		<= 102 ) ) ) ) {
		    
		  if ( curinput .locfield <= curinput .limitfield ) 
		  {
		    cc = buffer [curinput .locfield ];
		    if ( ( ( ( cc >= 48 ) && ( cc <= 57 ) ) || ( ( cc >= 97 ) 
		    && ( cc <= 102 ) ) ) ) 
		    {
		      incr ( curinput .locfield ) ;
		      if ( c <= 57 ) 
		      curchr = c - 48 ;
		      else curchr = c - 87 ;
		      if ( cc <= 57 ) 
		      curchr = 16 * curchr + cc - 48 ;
		      else curchr = 16 * curchr + cc - 87 ;
		      goto lab21 ;
		    } 
		  } 
		} 
		if ( c < 64 ) 
		curchr = c + 64 ;
		else curchr = c - 64 ;
		goto lab21 ;
	      } 
	    } 
	  } 
	  curinput .statefield = 1 ;
	} 
	break ;
      case 16 : 
      case 36 : 
      case 56 : 
      case 76 : 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 653 ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 654 ;
	    helpline [0 ]= 655 ;
	  } 
	  deletionsallowed = false ;
	  error () ;
	  deletionsallowed = true ;
	  goto lab20 ;
	} 
	break ;
      case 31 : 
      case 11 : 
	{
	  curinput .statefield = 41 ;
	  curchr = 32 ;
	} 
	break ;
      case 6 : 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  curcmd = 10 ;
	  curchr = 32 ;
	} 
	break ;
      case 26 : 
	if ( skipmode ) 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  goto lab25 ;
	} 
	else {
	    
	  curinput .locfield = curinput .limitfield + 1 ;
	  curcmd = 10 ;
	  curchr = 32 ;
	} 
	break ;
      case 46 : 
      case 15 : 
      case 35 : 
      case 55 : 
      case 75 : 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  goto lab25 ;
	} 
	break ;
      case 66 : 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  curcs = parloc ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  if ( curcmd >= 128 ) 
	  checkoutervalidity () ;
	} 
	break ;
      case 2 : 
      case 22 : 
	incr ( alignstate ) ;
	break ;
      case 42 : 
      case 62 : 
	{
	  curinput .statefield = 1 ;
	  incr ( alignstate ) ;
	} 
	break ;
      case 3 : 
      case 23 : 
	decr ( alignstate ) ;
	break ;
      case 43 : 
      case 63 : 
	{
	  curinput .statefield = 1 ;
	  decr ( alignstate ) ;
	} 
	break ;
      case 44 : 
      case 45 : 
      case 47 : 
      case 49 : 
      case 52 : 
      case 53 : 
      case 64 : 
      case 65 : 
      case 67 : 
      case 69 : 
      case 72 : 
      case 73 : 
      case 24 : 
      case 25 : 
      case 27 : 
      case 29 : 
      case 32 : 
      case 33 : 
	curinput .statefield = 1 ;
	break ;
      case 57 : 
      case 58 : 
      case 59 : 
      case 77 : 
      case 78 : 
      case 79 : 
      case 17 : 
      case 18 : 
      case 19 : 
	curinput .statefield = 21 ;
	break ;
      case 60 : 
      case 80 : 
      case 40 : 
	curinput .statefield = 1 ;
	break ;
	default: 
	;
	break ;
      } 
    } 
    else {
	
      curinput .statefield = 61 ;
      if ( curinput .namefield > 17 ) 
      {
	incr ( line ) ;
	first = curinput .startfield ;
	if ( ! forceeof ) 
	{
	  if ( inputln ( inputfile [curinput .indexfield ], true ) ) 
	  firmuptheline () ;
	  else forceeof = true ;
	} 
	if ( forceeof ) 
	{
	  printchar ( 41 ) ;
	  decr ( openparens ) ;
	  fflush ( stdout ) ;
	  forceeof = false ;
	  endfilereading () ;
	  checkoutervalidity () ;
	  goto lab20 ;
	} 
	if ( ( eqtb [28511 ].cint < 0 ) || ( eqtb [28511 ].cint > 255 ) ) 
	decr ( curinput .limitfield ) ;
	else buffer [curinput .limitfield ]= eqtb [28511 ].cint ;
	first = curinput .limitfield + 1 ;
	curinput .locfield = curinput .startfield ;
      } 
      else {
	  
	if ( ! ( curinput .namefield == 0 ) ) 
	{
	  curcmd = 0 ;
	  curchr = 0 ;
	  return ;
	} 
	if ( inputptr > 0 ) 
	{
	  endfilereading () ;
	  goto lab20 ;
	} 
	if ( selector < 18 ) 
	openlogfile () ;
	if ( interaction > 1 ) 
	{
	  if ( ( eqtb [28511 ].cint < 0 ) || ( eqtb [28511 ].cint > 255 ) 
	  ) 
	  incr ( curinput .limitfield ) ;
	  if ( curinput .limitfield == curinput .startfield ) 
	  printnl ( 656 ) ;
	  println () ;
	  first = curinput .startfield ;
	  {
	    ;
	    print ( 42 ) ;
	    terminput () ;
	  } 
	  curinput .limitfield = last ;
	  if ( ( eqtb [28511 ].cint < 0 ) || ( eqtb [28511 ].cint > 255 ) 
	  ) 
	  decr ( curinput .limitfield ) ;
	  else buffer [curinput .limitfield ]= eqtb [28511 ].cint ;
	  first = curinput .limitfield + 1 ;
	  curinput .locfield = curinput .startfield ;
	} 
	else fatalerror ( 657 ) ;
      } 
      {
	if ( interrupt != 0 ) 
	pauseforinstructions () ;
      } 
      goto lab25 ;
    } 
  } 
  else if ( curinput .locfield != -1073741823L ) 
  {
    t = mem [curinput .locfield ].hh .v.LH ;
    curinput .locfield = mem [curinput .locfield ].hh .v.RH ;
    if ( t >= 536870911L ) 
    {
      curcs = t - 536870911L ;
      curcmd = eqtb [curcs ].hh.b0 ;
      curchr = eqtb [curcs ].hh .v.RH ;
      if ( curcmd >= 128 ) {
	  
	if ( curcmd == 131 ) 
	{
	  curcs = mem [curinput .locfield ].hh .v.LH - 536870911L ;
	  curinput .locfield = -1073741823L ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  if ( curcmd > 115 ) 
	  {
	    curcmd = 0 ;
	    curchr = 257 ;
	  } 
	} 
	else checkoutervalidity () ;
      } 
    } 
    else if ( checkkanji ( t ) ) 
    {
      curcmd = t / 16777216L ;
      curchr = t % 16777216L ;
    } 
    else {
	
      curcmd = t / 256 ;
      curchr = t % 256 ;
      switch ( curcmd ) 
      {case 1 : 
	incr ( alignstate ) ;
	break ;
      case 2 : 
	decr ( alignstate ) ;
	break ;
      case 5 : 
	{
	  begintokenlist ( paramstack [curinput .limitfield + curchr - 1 ], 
	  0 ) ;
	  goto lab20 ;
	} 
	break ;
	default: 
	;
	break ;
      } 
    } 
  } 
  else {
      
    endtokenlist () ;
    goto lab20 ;
  } 
  if ( curcmd <= 5 ) {
      
    if ( curcmd >= 4 ) {
	
      if ( alignstate == 0 ) 
      {
	if ( ( scannerstatus == 4 ) || ( curalign == -1073741823L ) ) 
	fatalerror ( 633 ) ;
	curcmd = mem [curalign + 5 ].hh .v.LH ;
	mem [curalign + 5 ].hh .v.LH = curchr ;
	if ( curcmd == 68 ) 
	begintokenlist ( memtop - 10 , 2 ) ;
	else begintokenlist ( mem [curalign + 2 ].cint , 2 ) ;
	alignstate = 1000000L ;
	goto lab20 ;
      } 
    } 
  } 
} 
void 
firmuptheline ( void ) 
{
  firmuptheline_regmem 
  integer k  ;
  curinput .limitfield = last ;
  if ( eqtb [28490 ].cint > 0 ) {
      
    if ( interaction > 1 ) 
    {
      ;
      println () ;
      if ( curinput .startfield < curinput .limitfield ) 
      {register integer for_end; k = curinput .startfield ;for_end = 
      curinput .limitfield - 1 ; if ( k <= for_end) do 
	print ( buffer [k ]) ;
      while ( k++ < for_end ) ;} 
      first = curinput .limitfield ;
      {
	;
	print ( 658 ) ;
	terminput () ;
      } 
      if ( last > first ) 
      {
	{register integer for_end; k = first ;for_end = last - 1 ; if ( k <= 
	for_end) do 
	  buffer [k + curinput .startfield - first ]= buffer [k ];
	while ( k++ < for_end ) ;} 
	curinput .limitfield = curinput .startfield + last - first ;
      } 
    } 
  } 
} 
void 
gettoken ( void ) 
{
  gettoken_regmem 
  nonewcontrolsequence = false ;
  getnext () ;
  nonewcontrolsequence = true ;
  if ( curcs == 0 ) {
      
    if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
    curtok = ( curcmd * 16777216L ) + curchr ;
    else curtok = ( curcmd * 256 ) + curchr ;
  } 
  else curtok = 536870911L + curcs ;
} 
void 
macrocall ( void ) 
{
  /* 10 22 30 31 40 */ macrocall_regmem 
  halfword r  ;
  halfword p  ;
  halfword q  ;
  halfword s  ;
  halfword t  ;
  halfword u, v  ;
  halfword rbraceptr  ;
  smallnumber n  ;
  halfword unbalance  ;
  halfword m  ;
  halfword refcount  ;
  smallnumber savescannerstatus  ;
  halfword savewarningindex  ;
  ASCIIcode matchchr  ;
  savescannerstatus = scannerstatus ;
  savewarningindex = warningindex ;
  warningindex = curcs ;
  refcount = curchr ;
  r = mem [refcount ].hh .v.RH ;
  n = 0 ;
  if ( eqtb [28492 ].cint > 0 ) 
  {
    begindiagnostic () ;
    println () ;
    printcs ( warningindex ) ;
    tokenshow ( refcount ) ;
    enddiagnostic ( false ) ;
  } 
  if ( mem [r ].hh .v.LH != 3584 ) 
  {
    scannerstatus = 3 ;
    unbalance = 0 ;
    longstate = eqtb [curcs ].hh.b0 ;
    if ( longstate >= 128 ) 
    longstate = longstate - 2 ;
    do {
	mem [memtop - 3 ].hh .v.RH = -1073741823L ;
      if ( ( mem [r ].hh .v.LH > 3583 ) || ( mem [r ].hh .v.LH < 3328 ) ) 
      s = -1073741823L ;
      else {
	  
	matchchr = mem [r ].hh .v.LH - 3328 ;
	s = mem [r ].hh .v.RH ;
	r = s ;
	p = memtop - 3 ;
	m = 0 ;
      } 
      lab22: gettoken () ;
      if ( curtok == mem [r ].hh .v.LH ) 
      {
	r = mem [r ].hh .v.RH ;
	if ( ( mem [r ].hh .v.LH >= 3328 ) && ( mem [r ].hh .v.LH <= 3584 
	) ) 
	{
	  if ( curtok < 512 ) 
	  decr ( alignstate ) ;
	  goto lab40 ;
	} 
	else goto lab22 ;
      } 
      if ( s != r ) {
	  
	if ( s == -1073741823L ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 691 ) ;
	  } 
	  sprintcs ( warningindex ) ;
	  print ( 692 ) ;
	  {
	    helpptr = 4 ;
	    helpline [3 ]= 693 ;
	    helpline [2 ]= 694 ;
	    helpline [1 ]= 695 ;
	    helpline [0 ]= 696 ;
	  } 
	  error () ;
	  goto lab10 ;
	} 
	else {
	    
	  t = s ;
	  do {
	      { 
	      q = getavail () ;
	      mem [p ].hh .v.RH = q ;
	      mem [q ].hh .v.LH = mem [t ].hh .v.LH ;
	      p = q ;
	    } 
	    incr ( m ) ;
	    u = mem [t ].hh .v.RH ;
	    v = s ;
	    while ( true ) {
		
	      if ( u == r ) {
		  
		if ( curtok != mem [v ].hh .v.LH ) 
		goto lab30 ;
		else {
		    
		  r = mem [v ].hh .v.RH ;
		  goto lab22 ;
		} 
	      } 
	      if ( mem [u ].hh .v.LH != mem [v ].hh .v.LH ) 
	      goto lab30 ;
	      u = mem [u ].hh .v.RH ;
	      v = mem [v ].hh .v.RH ;
	    } 
	    lab30: t = mem [t ].hh .v.RH ;
	  } while ( ! ( t == r ) ) ;
	  r = s ;
	} 
      } 
      if ( curtok == partoken ) {
	  
	if ( longstate != 127 ) 
	{
	  if ( longstate == 126 ) 
	  {
	    runaway () ;
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 263 ) ;
	      print ( 686 ) ;
	    } 
	    sprintcs ( warningindex ) ;
	    print ( 687 ) ;
	    {
	      helpptr = 3 ;
	      helpline [2 ]= 688 ;
	      helpline [1 ]= 689 ;
	      helpline [0 ]= 690 ;
	    } 
	    backerror () ;
	  } 
	  pstack [n ]= mem [memtop - 3 ].hh .v.RH ;
	  alignstate = alignstate - unbalance ;
	  {register integer for_end; m = 0 ;for_end = n ; if ( m <= for_end) 
	  do 
	    flushlist ( pstack [m ]) ;
	  while ( m++ < for_end ) ;} 
	  goto lab10 ;
	} 
      } 
      if ( curtok < 768 ) {
	  
	if ( curtok < 512 ) 
	{
	  unbalance = 1 ;
	  while ( true ) {
	      
	    {
	      {
		q = avail ;
		if ( q == -1073741823L ) 
		q = getavail () ;
		else {
		    
		  avail = mem [q ].hh .v.RH ;
		  mem [q ].hh .v.RH = -1073741823L ;
	;
#ifdef STAT
		  incr ( dynused ) ;
#endif /* STAT */
		} 
	      } 
	      mem [p ].hh .v.RH = q ;
	      mem [q ].hh .v.LH = curtok ;
	      p = q ;
	    } 
	    gettoken () ;
	    if ( curtok == partoken ) {
		
	      if ( longstate != 127 ) 
	      {
		if ( longstate == 126 ) 
		{
		  runaway () ;
		  {
		    if ( interaction == 3 ) 
		    ;
		    if ( filelineerrorstylep ) 
		    printfileline () ;
		    else printnl ( 263 ) ;
		    print ( 686 ) ;
		  } 
		  sprintcs ( warningindex ) ;
		  print ( 687 ) ;
		  {
		    helpptr = 3 ;
		    helpline [2 ]= 688 ;
		    helpline [1 ]= 689 ;
		    helpline [0 ]= 690 ;
		  } 
		  backerror () ;
		} 
		pstack [n ]= mem [memtop - 3 ].hh .v.RH ;
		alignstate = alignstate - unbalance ;
		{register integer for_end; m = 0 ;for_end = n ; if ( m <= 
		for_end) do 
		  flushlist ( pstack [m ]) ;
		while ( m++ < for_end ) ;} 
		goto lab10 ;
	      } 
	    } 
	    if ( curtok < 768 ) {
		
	      if ( curtok < 512 ) 
	      incr ( unbalance ) ;
	      else {
		  
		decr ( unbalance ) ;
		if ( unbalance == 0 ) 
		goto lab31 ;
	      } 
	    } 
	  } 
	  lab31: rbraceptr = p ;
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = curtok ;
	    p = q ;
	  } 
	} 
	else {
	    
	  backinput () ;
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 678 ) ;
	  } 
	  sprintcs ( warningindex ) ;
	  print ( 679 ) ;
	  {
	    helpptr = 6 ;
	    helpline [5 ]= 680 ;
	    helpline [4 ]= 681 ;
	    helpline [3 ]= 682 ;
	    helpline [2 ]= 683 ;
	    helpline [1 ]= 684 ;
	    helpline [0 ]= 685 ;
	  } 
	  incr ( alignstate ) ;
	  longstate = 126 ;
	  curtok = partoken ;
	  inserror () ;
	  goto lab22 ;
	} 
      } 
      else {
	  
	if ( curtok == 2592 ) {
	    
	  if ( mem [r ].hh .v.LH <= 3584 ) {
	      
	    if ( mem [r ].hh .v.LH >= 3328 ) 
	    goto lab22 ;
	  } 
	} 
	{
	  q = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = curtok ;
	  p = q ;
	} 
      } 
      incr ( m ) ;
      if ( mem [r ].hh .v.LH > 3584 ) 
      goto lab22 ;
      if ( mem [r ].hh .v.LH < 3328 ) 
      goto lab22 ;
      lab40: if ( s != -1073741823L ) 
      {
	if ( ( m == 1 ) && ( mem [p ].hh .v.LH < 768 ) && ( p != memtop - 3 
	) ) 
	{
	  mem [rbraceptr ].hh .v.RH = -1073741823L ;
	  {
	    mem [p ].hh .v.RH = avail ;
	    avail = p ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	  p = mem [memtop - 3 ].hh .v.RH ;
	  pstack [n ]= mem [p ].hh .v.RH ;
	  {
	    mem [p ].hh .v.RH = avail ;
	    avail = p ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
	else pstack [n ]= mem [memtop - 3 ].hh .v.RH ;
	incr ( n ) ;
	if ( eqtb [28492 ].cint > 0 ) 
	{
	  begindiagnostic () ;
	  printnl ( matchchr ) ;
	  printint ( n ) ;
	  print ( 697 ) ;
	  showtokenlist ( pstack [n - 1 ], -1073741823L , 1000 ) ;
	  enddiagnostic ( false ) ;
	} 
      } 
    } while ( ! ( mem [r ].hh .v.LH == 3584 ) ) ;
  } 
  while ( ( curinput .statefield == 0 ) && ( curinput .locfield == 
  -1073741823L ) && ( curinput .indexfield != 2 ) ) endtokenlist () ;
  begintokenlist ( refcount , 5 ) ;
  curinput .namefield = warningindex ;
  curinput .locfield = mem [r ].hh .v.RH ;
  if ( n > 0 ) 
  {
    if ( paramptr + n > maxparamstack ) 
    {
      maxparamstack = paramptr + n ;
      if ( maxparamstack > paramsize ) 
      overflow ( 677 , paramsize ) ;
    } 
    {register integer for_end; m = 0 ;for_end = n - 1 ; if ( m <= for_end) 
    do 
      paramstack [paramptr + m ]= pstack [m ];
    while ( m++ < for_end ) ;} 
    paramptr = paramptr + n ;
  } 
  lab10: scannerstatus = savescannerstatus ;
  warningindex = savewarningindex ;
} 
void 
insertrelax ( void ) 
{
  insertrelax_regmem 
  curtok = 536870911L + curcs ;
  backinput () ;
  curtok = 536886432L ;
  backinput () ;
  curinput .indexfield = 4 ;
} 
void 
expand ( void ) 
{
  expand_regmem 
  halfword t  ;
  halfword p, q, r  ;
  integer j  ;
  integer cvbackup  ;
  smallnumber cvlbackup, radixbackup, cobackup  ;
  halfword backupbackup  ;
  smallnumber savescannerstatus  ;
  incr ( expanddepthcount ) ;
  if ( expanddepthcount >= expanddepth ) 
  overflow ( 659 , expanddepth ) ;
  cvbackup = curval ;
  cvlbackup = curvallevel ;
  radixbackup = radix ;
  cobackup = curorder ;
  backupbackup = mem [memtop - 13 ].hh .v.RH ;
  if ( curcmd < 126 ) 
  {
    if ( eqtb [28498 ].cint > 1 ) 
    showcurcmdchr () ;
    switch ( curcmd ) 
    {case 125 : 
      {
	if ( curmark [curchr ]!= -1073741823L ) 
	begintokenlist ( curmark [curchr ], 14 ) ;
      } 
      break ;
    case 117 : 
      {
	gettoken () ;
	t = curtok ;
	gettoken () ;
	if ( curcmd > 115 ) 
	expand () ;
	else backinput () ;
	curtok = t ;
	backinput () ;
      } 
      break ;
    case 118 : 
      {
	savescannerstatus = scannerstatus ;
	scannerstatus = 0 ;
	gettoken () ;
	scannerstatus = savescannerstatus ;
	t = curtok ;
	backinput () ;
	if ( t >= 536870911L ) 
	{
	  p = getavail () ;
	  mem [p ].hh .v.LH = 536886434L ;
	  mem [p ].hh .v.RH = curinput .locfield ;
	  curinput .startfield = p ;
	  curinput .locfield = p ;
	} 
      } 
      break ;
    case 122 : 
      {
	r = getavail () ;
	p = r ;
	do {
	    getxtoken () ;
	  if ( curcs == 0 ) 
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = curtok ;
	    p = q ;
	  } 
	} while ( ! ( curcs != 0 ) ) ;
	if ( curcmd != 72 ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 666 ) ;
	  } 
	  printesc ( 540 ) ;
	  print ( 667 ) ;
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 668 ;
	    helpline [0 ]= 669 ;
	  } 
	  backerror () ;
	} 
	j = first ;
	p = mem [r ].hh .v.RH ;
	while ( p != -1073741823L ) {
	    
	  if ( j >= maxbufstack ) 
	  {
	    maxbufstack = j + 1 ;
	    if ( maxbufstack == bufsize ) 
	    overflow ( 257 , bufsize ) ;
	  } 
	  if ( checkkanji ( mem [p ].hh .v.LH ) ) 
	  {
	    t = toBUFF ( mem [p ].hh .v.LH % 16777216L ) ;
	    if ( BYTE1 ( t ) != 0 ) 
	    {
	      buffer [j ]= BYTE1 ( t ) ;
	      incr ( j ) ;
	    } 
	    if ( BYTE2 ( t ) != 0 ) 
	    {
	      buffer [j ]= BYTE2 ( t ) ;
	      incr ( j ) ;
	    } 
	    if ( BYTE3 ( t ) != 0 ) 
	    {
	      buffer [j ]= BYTE3 ( t ) ;
	      incr ( j ) ;
	    } 
	    buffer [j ]= BYTE4 ( t ) ;
	    incr ( j ) ;
	    p = mem [p ].hh .v.RH ;
	  } 
	  else {
	      
	    buffer [j ]= mem [p ].hh .v.LH % 256 ;
	    incr ( j ) ;
	    p = mem [p ].hh .v.RH ;
	  } 
	} 
	if ( j > first + 1 ) 
	{
	  nonewcontrolsequence = false ;
	  curcs = idlookup ( first , j - first ) ;
	  nonewcontrolsequence = true ;
	} 
	else if ( j == first ) 
	curcs = 513 ;
	else curcs = 257 + buffer [first ];
	flushlist ( r ) ;
	if ( eqtb [curcs ].hh.b0 == 116 ) 
	{
	  eqdefine ( curcs , 0 , 256 ) ;
	} 
	curtok = curcs + 536870911L ;
	backinput () ;
      } 
      break ;
    case 123 : 
      convtoks () ;
      break ;
    case 124 : 
      insthetoks () ;
      break ;
    case 120 : 
      conditional () ;
      break ;
    case 121 : 
      if ( curchr > iflimit ) {
	  
	if ( iflimit == 1 ) 
	insertrelax () ;
	else {
	    
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 832 ) ;
	  } 
	  printcmdchr ( 121 , curchr ) ;
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 833 ;
	  } 
	  error () ;
	} 
      } 
      else {
	  
	while ( curchr != 2 ) passtext () ;
	{
	  p = condptr ;
	  ifline = mem [p + 1 ].cint ;
	  curif = mem [p ].hh.b1 ;
	  iflimit = mem [p ].hh.b0 ;
	  condptr = mem [p ].hh .v.RH ;
	  freenode ( p , 2 ) ;
	} 
      } 
      break ;
    case 119 : 
      if ( curchr > 0 ) 
      forceeof = true ;
      else if ( nameinprogress ) 
      insertrelax () ;
      else startinput () ;
      break ;
      default: 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 660 ) ;
	} 
	{
	  helpptr = 5 ;
	  helpline [4 ]= 661 ;
	  helpline [3 ]= 662 ;
	  helpline [2 ]= 663 ;
	  helpline [1 ]= 664 ;
	  helpline [0 ]= 665 ;
	} 
	error () ;
      } 
      break ;
    } 
  } 
  else if ( curcmd < 130 ) 
  macrocall () ;
  else {
      
    curtok = 536886431L ;
    backinput () ;
  } 
  curval = cvbackup ;
  curvallevel = cvlbackup ;
  radix = radixbackup ;
  curorder = cobackup ;
  mem [memtop - 13 ].hh .v.RH = backupbackup ;
  decr ( expanddepthcount ) ;
} 
void 
getxtoken ( void ) 
{
  /* 20 30 */ getxtoken_regmem 
  lab20: getnext () ;
  if ( curcmd <= 115 ) 
  goto lab30 ;
  if ( curcmd >= 126 ) {
      
    if ( curcmd < 130 ) 
    macrocall () ;
    else {
	
      curcs = 15520 ;
      curcmd = 9 ;
      goto lab30 ;
    } 
  } 
  else expand () ;
  goto lab20 ;
  lab30: if ( curcs == 0 ) {
      
    if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
    curtok = ( curcmd * 16777216L ) + curchr ;
    else curtok = ( curcmd * 256 ) + curchr ;
  } 
  else curtok = 536870911L + curcs ;
} 
void 
xtoken ( void ) 
{
  xtoken_regmem 
  while ( curcmd > 115 ) {
      
    expand () ;
    getnext () ;
  } 
  if ( curcs == 0 ) {
      
    if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
    curtok = ( curcmd * 16777216L ) + curchr ;
    else curtok = ( curcmd * 256 ) + curchr ;
  } 
  else curtok = 536870911L + curcs ;
} 
void 
scanleftbrace ( void ) 
{
  scanleftbrace_regmem 
  do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  if ( curcmd != 1 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 698 ) ;
    } 
    {
      helpptr = 4 ;
      helpline [3 ]= 699 ;
      helpline [2 ]= 700 ;
      helpline [1 ]= 701 ;
      helpline [0 ]= 702 ;
    } 
    backerror () ;
    curtok = 379 ;
    curcmd = 1 ;
    curchr = 123 ;
    incr ( alignstate ) ;
  } 
} 
void 
scanoptionalequals ( void ) 
{
  scanoptionalequals_regmem 
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curtok != 3133 ) 
  backinput () ;
} 
boolean 
zscankeyword ( strnumber s ) 
{
  /* 10 */ register boolean Result; scankeyword_regmem 
  halfword p  ;
  halfword q  ;
  poolpointer k  ;
  p = memtop - 13 ;
  mem [p ].hh .v.RH = -1073741823L ;
  k = strstart [s ];
  while ( k < strstart [s + 1 ]) {
      
    getxtoken () ;
    if ( ( curcs == 0 ) && ( ( curchr == strpool [k ]) || ( curchr == 
    strpool [k ]- 32 ) ) ) 
    {
      {
	q = getavail () ;
	mem [p ].hh .v.RH = q ;
	mem [q ].hh .v.LH = curtok ;
	p = q ;
      } 
      incr ( k ) ;
    } 
    else if ( ( curcmd != 10 ) || ( p != memtop - 13 ) ) 
    {
      backinput () ;
      if ( p != memtop - 13 ) 
      begintokenlist ( mem [memtop - 13 ].hh .v.RH , 3 ) ;
      Result = false ;
      return Result ;
    } 
  } 
  flushlist ( mem [memtop - 13 ].hh .v.RH ) ;
  Result = true ;
  return Result ;
} 
void 
muerror ( void ) 
{
  muerror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 703 ) ;
  } 
  {
    helpptr = 1 ;
    helpline [0 ]= 704 ;
  } 
  error () ;
} 
void 
scaneightbitint ( void ) 
{
  scaneightbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 255 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 728 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 729 ;
      helpline [0 ]= 730 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scancharnum ( void ) 
{
  scancharnum_regmem 
  scanint () ;
  if ( ! ischarascii ( curval ) && ! ischarkanji ( curval ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 731 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 732 ;
      helpline [0 ]= 730 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfourbitint ( void ) 
{
  scanfourbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 15 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 733 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 734 ;
      helpline [0 ]= 730 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfifteenbitint ( void ) 
{
  scanfifteenbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 32767 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 735 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 736 ;
      helpline [0 ]= 730 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scantwentysevenbitint ( void ) 
{
  scantwentysevenbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 134217727L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 737 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 738 ;
      helpline [0 ]= 730 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfourbitintor18 ( void ) 
{
  scanfourbitintor18_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( ( curval > 15 ) && ( curval != 18 ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 733 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 734 ;
      helpline [0 ]= 730 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfontident ( void ) 
{
  scanfontident_regmem 
  internalfontnumber f  ;
  halfword m  ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curcmd == 100 ) 
  f = eqtb [25631 ].hh .v.RH ;
  else if ( curcmd == 101 ) 
  f = eqtb [25632 ].hh .v.RH ;
  else if ( curcmd == 99 ) 
  f = eqtb [25582 ].hh .v.RH ;
  else if ( curcmd == 98 ) 
  f = curchr ;
  else if ( curcmd == 97 ) 
  {
    m = curchr ;
    scanfourbitint () ;
    f = eqtb [m + curval ].hh .v.RH ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 872 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 873 ;
      helpline [0 ]= 874 ;
    } 
    backerror () ;
    f = 0 ;
  } 
  curval = f ;
} 
void 
zfindfontdimen ( boolean writing ) 
{
  findfontdimen_regmem 
  internalfontnumber f  ;
  integer n  ;
  scanint () ;
  n = curval ;
  scanfontident () ;
  f = curval ;
  if ( n <= 0 ) 
  curval = fmemptr ;
  else {
      
    if ( writing && ( n <= 4 ) && ( n >= 2 ) && ( fontglue [f ]!= 
    -1073741823L ) ) 
    {
      deleteglueref ( fontglue [f ]) ;
      fontglue [f ]= -1073741823L ;
    } 
    if ( n > fontparams [f ]) {
	
      if ( f < fontptr ) 
      curval = fmemptr ;
      else {
	  
	do {
	    if ( fmemptr == fontmemsize ) 
	  overflow ( 879 , fontmemsize ) ;
	  fontinfo [fmemptr ].cint = 0 ;
	  incr ( fmemptr ) ;
	  incr ( fontparams [f ]) ;
	} while ( ! ( n == fontparams [f ]) ) ;
	curval = fmemptr - 1 ;
      } 
    } 
    else curval = n + parambase [f ];
  } 
  if ( curval == fmemptr ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 857 ) ;
    } 
    printesc ( hash [15525 + f ].v.RH ) ;
    print ( 875 ) ;
    printint ( fontparams [f ]) ;
    print ( 876 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 877 ;
      helpline [0 ]= 878 ;
    } 
    error () ;
  } 
} 
eightbits 
zgetjfmpos ( KANJIcode kcode , internalfontnumber f ) 
{
  register eightbits Result; getjfmpos_regmem 
  KANJIcode jc  ;
  halfword sp, mp, ep  ;
  if ( f == 0 ) 
  {
    Result = fontinfo [ctypebase [0 ]+ 0 ].hh .lhfield ;
    return Result ;
  } 
  jc = toDVI ( kcode ) ;
  sp = 1 ;
  ep = fontnumext [f ]- 1 ;
  if ( ( ep >= 1 ) && ( fontinfo [ctypebase [f ]+ sp ].hh .v.RH <= jc ) && 
  ( jc <= fontinfo [ctypebase [f ]+ ep ].hh .v.RH ) ) 
  {
    while ( ( sp <= ep ) ) {
	
      mp = sp + ( ( ep - sp ) / 2 ) ;
      if ( jc < fontinfo [ctypebase [f ]+ mp ].hh .v.RH ) 
      ep = mp - 1 ;
      else if ( jc > fontinfo [ctypebase [f ]+ mp ].hh .v.RH ) 
      sp = mp + 1 ;
      else {
	  
	Result = fontinfo [ctypebase [f ]+ mp ].hh .lhfield ;
	return Result ;
      } 
    } 
  } 
  Result = fontinfo [ctypebase [f ]+ 0 ].hh .lhfield ;
  return Result ;
} 
void 
zprintkansuji ( integer n ) 
{
  printkansuji_regmem 
  unsigned char k  ;
  KANJIcode cx  ;
  k = 0 ;
  if ( n < 0 ) 
  return ;
  do {
      dig [k ]= n % 10 ;
    n = n / 10 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  {
    while ( k > 0 ) {
	
      decr ( k ) ;
      cx = eqtb [27172 + dig [k ]].hh .v.RH ;
      printkanji ( fromDVI ( cx ) ) ;
    } 
  } 
} 
halfword 
zgetinhibitpos ( KANJIcode c , smallnumber n ) 
{
  /* 30 31 */ register halfword Result; getinhibitpos_regmem 
  halfword p, s  ;
  s = calcpos ( c ) ;
  p = s ;
  if ( n == 0 ) 
  {
    do {
	if ( ( eqtb [26660 + p ].hh .v.RH == 0 ) || ( eqtb [26660 + p ]
      .hh .v.RH == c ) ) 
      goto lab30 ;
      incr ( p ) ;
      if ( p > 255 ) 
      p = 0 ;
    } while ( ! ( s == p ) ) ;
    p = 1000 ;
  } 
  else {
      
    do {
	if ( eqtb [26660 + p ].hh .v.RH == 0 ) 
      goto lab31 ;
      if ( eqtb [26660 + p ].hh .v.RH == c ) 
      goto lab30 ;
      incr ( p ) ;
      if ( p > 255 ) 
      p = 0 ;
    } while ( ! ( s == p ) ) ;
    lab31: p = 1000 ;
  } 
  lab30: Result = p ;
  return Result ;
} 
halfword 
zgetkinsokupos ( KANJIcode c , smallnumber n ) 
{
  /* 30 31 */ register halfword Result; getkinsokupos_regmem 
  halfword p, s  ;
  s = calcpos ( c ) ;
  p = s ;
	;
#ifdef TEXMF_DEBUG
  println () ;
  print ( 1428 ) ;
  printint ( c ) ;
  print ( 1429 ) ;
  printint ( s ) ;
  if ( p + 26916 < 0 ) 
  {
    print ( 1430 ) ;
    println () ;
  } 
#endif /* TEXMF_DEBUG */
  if ( n == 0 ) 
  {
    do {
	if ( ( eqtb [26916 + p ].hh.b0 == 0 ) || ( eqtb [26916 + p ].hh 
      .v.RH == c ) ) 
      goto lab30 ;
      incr ( p ) ;
      if ( p > 255 ) 
      p = 0 ;
    } while ( ! ( s == p ) ) ;
    p = 1000 ;
  } 
  else {
      
    do {
	if ( eqtb [26916 + p ].hh.b0 == 0 ) 
      goto lab31 ;
      if ( eqtb [26916 + p ].hh .v.RH == c ) 
      goto lab30 ;
      incr ( p ) ;
      if ( p > 255 ) 
      p = 0 ;
    } while ( ! ( s == p ) ) ;
    lab31: p = 1000 ;
  } 
  lab30: Result = p ;
  return Result ;
} 
void 
zscansomethinginternal ( smallnumber level , boolean negative ) 
{
  scansomethinginternal_regmem 
  halfword m  ;
  halfword tx  ;
  halfword qx  ;
  integer p  ;
  halfword q, r  ;
  m = curchr ;
  switch ( curcmd ) 
  {case 87 : 
    {
      scanint () ;
      q = getkinsokupos ( curval , 1 ) ;
      curvallevel = 0 ;
      curval = 0 ;
      if ( ( q != 1000 ) && ( m == eqtb [26916 + q ].hh.b0 ) ) 
      {
	curval = eqtb [29317 + q ].cint ;
	curvallevel = 0 ;
      } 
    } 
    break ;
  case 88 : 
    {
      scanint () ;
      q = getinhibitpos ( curval , 1 ) ;
      curvallevel = 0 ;
      curval = 3 ;
      if ( q != 1000 ) 
      curval = eqtb [26660 + q ].hh.b0 ;
    } 
    break ;
  case 96 : 
    {
      scancharnum () ;
      if ( m == 27950 ) 
      {
	curval = eqtb [27950 + curval ].hh .v.RH ;
	curvallevel = 0 ;
      } 
      else if ( m == 25892 ) 
      {
	curval = eqtb [m + kcatcodekey ( curval ) ].hh .v.RH ;
	curvallevel = 0 ;
      } 
      else if ( m < 27950 ) 
      {
	if ( ! ischarascii ( curval ) ) 
	{
	  curval = eqtb [m + Hi ( curval ) ].hh .v.RH ;
	  curvallevel = 0 ;
	} 
	else {
	    
	  curval = eqtb [m + curval ].hh .v.RH ;
	  curvallevel = 0 ;
	} 
      } 
      else {
	  
	if ( ! ischarascii ( curval ) ) 
	{
	  curval = eqtb [m + Hi ( curval ) ].cint ;
	  curvallevel = 0 ;
	} 
	else {
	    
	  curval = eqtb [m + curval ].cint ;
	  curvallevel = 0 ;
	} 
      } 
    } 
    break ;
  case 79 : 
  case 80 : 
  case 97 : 
  case 98 : 
  case 99 : 
  case 100 : 
  case 101 : 
    if ( level != 5 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 705 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 706 ;
	helpline [1 ]= 707 ;
	helpline [0 ]= 708 ;
      } 
      backerror () ;
      {
	curval = 0 ;
	curvallevel = 1 ;
      } 
    } 
    else if ( curcmd <= 80 ) 
    {
      if ( curcmd < 80 ) 
      {
	scaneightbitint () ;
	m = 25070 + curval ;
      } 
      {
	curval = eqtb [m ].hh .v.RH ;
	curvallevel = 5 ;
      } 
    } 
    else {
	
      backinput () ;
      scanfontident () ;
      {
	curval = 15525 + curval ;
	curvallevel = 4 ;
      } 
    } 
    break ;
  case 81 : 
    {
      curval = eqtb [m ].cint ;
      curvallevel = 0 ;
    } 
    break ;
  case 82 : 
    {
      curval = eqtb [m ].cint ;
      curvallevel = 1 ;
    } 
    break ;
  case 83 : 
    {
      curval = eqtb [m ].hh .v.RH ;
      curvallevel = 2 ;
    } 
    break ;
  case 84 : 
    {
      curval = eqtb [m ].hh .v.RH ;
      curvallevel = 3 ;
    } 
    break ;
  case 90 : 
    if ( abs ( curlist .modefield ) != m ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 721 ) ;
      } 
      printcmdchr ( 90 , m ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 722 ;
	helpline [2 ]= 723 ;
	helpline [1 ]= 724 ;
	helpline [0 ]= 725 ;
      } 
      error () ;
      if ( level != 5 ) 
      {
	curval = 0 ;
	curvallevel = 1 ;
      } 
      else {
	  
	curval = 0 ;
	curvallevel = 0 ;
      } 
    } 
    else if ( m == 1 ) 
    {
      curval = curlist .auxfield .cint ;
      curvallevel = 1 ;
    } 
    else {
	
      curval = curlist .auxfield .hh .v.LH ;
      curvallevel = 0 ;
    } 
    break ;
  case 91 : 
    if ( curlist .modefield == 0 ) 
    {
      curval = 0 ;
      curvallevel = 0 ;
    } 
    else {
	
      nest [nestptr ]= curlist ;
      p = nestptr ;
      while ( abs ( nest [p ].modefield ) != 1 ) decr ( p ) ;
      {
	curval = nest [p ].pgfield ;
	curvallevel = 0 ;
      } 
    } 
    break ;
  case 93 : 
    {
      if ( m == 0 ) 
      curval = deadcycles ;
      else curval = insertpenalties ;
      curvallevel = 0 ;
    } 
    break ;
  case 92 : 
    {
      if ( ( pagecontents == 0 ) && ( ! outputactive ) ) {
	  
	if ( m == 0 ) 
	curval = 1073741823L ;
	else curval = 0 ;
      } 
      else curval = pagesofar [m ];
      curvallevel = 1 ;
    } 
    break ;
  case 95 : 
    {
      if ( eqtb [25060 ].hh .v.RH == -1073741823L ) 
      curval = 0 ;
      else curval = mem [eqtb [25060 ].hh .v.RH ].hh .v.LH ;
      curvallevel = 0 ;
    } 
    break ;
  case 94 : 
    {
      scaneightbitint () ;
      q = eqtb [25326 + curval ].hh .v.RH ;
      if ( q == -1073741823L ) 
      curval = 0 ;
      else {
	  
	qx = q ;
	while ( ( q != -1073741823L ) && ( ( mem [q ].hh.b1 ) != abs ( 
	curlist .dirfield ) ) ) q = mem [q ].hh .v.RH ;
	if ( q == -1073741823L ) 
	{
	  r = mem [qx ].hh .v.RH ;
	  mem [qx ].hh .v.RH = -1073741823L ;
	  q = newdirnode ( qx , abs ( curlist .dirfield ) ) ;
	  mem [qx ].hh .v.RH = r ;
	  curval = mem [q + m ].cint ;
	  deleteglueref ( mem [q + 7 ].hh .v.RH ) ;
	  deleteglueref ( mem [q + 7 ].hh .v.LH ) ;
	  freenode ( q , 10 ) ;
	} 
	else curval = mem [q + m ].cint ;
      } 
      curvallevel = 1 ;
    } 
    break ;
  case 74 : 
  case 73 : 
  case 75 : 
    {
      curval = curchr ;
      curvallevel = 0 ;
    } 
    break ;
  case 85 : 
    {
      findfontdimen ( false ) ;
      fontinfo [fmemptr ].cint = 0 ;
      {
	curval = fontinfo [curval ].cint ;
	curvallevel = 1 ;
      } 
    } 
    break ;
  case 86 : 
    {
      scanfontident () ;
      if ( m == 0 ) 
      {
	curval = hyphenchar [curval ];
	curvallevel = 0 ;
      } 
      else {
	  
	curval = skewchar [curval ];
	curvallevel = 0 ;
      } 
    } 
    break ;
  case 102 : 
    {
      scaneightbitint () ;
      switch ( m ) 
      {case 0 : 
	curval = eqtb [28526 + curval ].cint ;
	break ;
      case 1 : 
	curval = eqtb [29061 + curval ].cint ;
	break ;
      case 2 : 
	curval = eqtb [24548 + curval ].hh .v.RH ;
	break ;
      case 3 : 
	curval = eqtb [24804 + curval ].hh .v.RH ;
	break ;
      } 
      curvallevel = m ;
    } 
    break ;
  case 76 : 
    if ( curchr > 2 ) 
    {
      if ( curchr == 3 ) 
      curval = line ;
      else curval = lastbadness ;
      curvallevel = 0 ;
    } 
    else {
	
      if ( curchr == 2 ) 
      curval = membot ;
      else curval = 0 ;
      tx = curlist .tailfield ;
      if ( ! ( tx >= himemmin ) ) {
	  
	if ( mem [tx ].hh.b0 == 5 ) 
	{
	  tx = curlist .pnodefield ;
	  if ( ! ( tx >= himemmin ) ) {
	      
	    if ( mem [tx ].hh.b0 == 5 ) 
	    {
	      tx = curlist .headfield ;
	      q = mem [curlist .headfield ].hh .v.RH ;
	      while ( q != curlist .pnodefield ) {
		  
		if ( ( q >= himemmin ) ) 
		tx = q ;
		else if ( mem [q ].hh.b0 != 5 ) 
		tx = q ;
	      } 
	      q = mem [q ].hh .v.RH ;
	    } 
	  } 
	} 
      } 
      curvallevel = curchr ;
      if ( ! ( tx >= himemmin ) && ( tx != curlist .headfield ) && ( curlist 
      .modefield != 0 ) ) 
      switch ( curchr ) 
      {case 0 : 
	if ( mem [tx ].hh.b0 == 14 ) 
	curval = mem [tx + 1 ].cint ;
	break ;
      case 1 : 
	if ( mem [tx ].hh.b0 == 13 ) 
	curval = mem [tx + 1 ].cint ;
	break ;
      case 2 : 
	if ( mem [tx ].hh.b0 == 12 ) 
	{
	  curval = mem [tx + 1 ].hh .v.LH ;
	  if ( mem [tx ].hh.b1 == 99 ) 
	  curvallevel = 3 ;
	} 
	break ;
      } 
      else if ( ( curlist .modefield == 1 ) && ( tx == curlist .headfield ) ) 
      switch ( curchr ) 
      {case 0 : 
	curval = lastpenalty ;
	break ;
      case 1 : 
	curval = lastkern ;
	break ;
      case 2 : 
	if ( lastglue != 1073741823L ) 
	curval = lastglue ;
	break ;
      } 
    } 
    break ;
    default: 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 726 ) ;
      } 
      printcmdchr ( curcmd , curchr ) ;
      print ( 727 ) ;
      printesc ( 575 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 725 ;
      } 
      error () ;
      if ( level != 5 ) 
      {
	curval = 0 ;
	curvallevel = 1 ;
      } 
      else {
	  
	curval = 0 ;
	curvallevel = 0 ;
      } 
    } 
    break ;
  } 
  while ( curvallevel > level ) {
      
    if ( curvallevel == 2 ) 
    curval = mem [curval + 1 ].cint ;
    else if ( curvallevel == 3 ) 
    muerror () ;
    decr ( curvallevel ) ;
  } 
  if ( negative ) {
      
    if ( curvallevel >= 2 ) 
    {
      curval = newspec ( curval ) ;
      {
	mem [curval + 1 ].cint = - (integer) mem [curval + 1 ].cint ;
	mem [curval + 2 ].cint = - (integer) mem [curval + 2 ].cint ;
	mem [curval + 3 ].cint = - (integer) mem [curval + 3 ].cint ;
      } 
    } 
    else curval = - (integer) curval ;
  } 
  else if ( ( curvallevel >= 2 ) && ( curvallevel <= 3 ) ) 
  incr ( mem [curval ].hh .v.RH ) ;
} 
void 
scanint ( void ) 
{
  /* 30 */ scanint_regmem 
  boolean negative  ;
  integer m  ;
  smallnumber d  ;
  boolean vacuous  ;
  boolean OKsofar  ;
  radix = 0 ;
  OKsofar = true ;
  negative = false ;
  do {
      do { getxtoken () ;
    } while ( ! ( curcmd != 10 ) ) ;
    if ( curtok == 3117 ) 
    {
      negative = ! negative ;
      curtok = 3115 ;
    } 
  } while ( ! ( curtok != 3115 ) ) ;
  if ( curtok == 3168 ) 
  {
    gettoken () ;
    if ( curtok < 536870911L ) {
	
      if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
      {
	skipmode = false ;
	curval = curchr ;
      } 
      else {
	  
	curval = curchr ;
	if ( curcmd <= 2 ) {
	    
	  if ( curcmd == 2 ) 
	  incr ( alignstate ) ;
	  else decr ( alignstate ) ;
	} 
      } 
    } 
    else if ( curtok < 536871168L ) 
    curval = curtok - 536870912L ;
    else curval = curtok - 536871168L ;
    if ( ( curval > 255 ) && ( ( curcmd < 16 ) || ( curcmd > 19 ) ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 739 ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 740 ;
	helpline [0 ]= 741 ;
      } 
      curval = 48 ;
      backerror () ;
    } 
    else {
	
      getxtoken () ;
      if ( curcmd != 10 ) 
      backinput () ;
    } 
    skipmode = true ;
  } 
  else if ( ( curcmd >= 73 ) && ( curcmd <= 102 ) ) 
  scansomethinginternal ( 0 , false ) ;
  else {
      
    radix = 10 ;
    m = 214748364L ;
    if ( curtok == 3111 ) 
    {
      radix = 8 ;
      m = 268435456L ;
      getxtoken () ;
    } 
    else if ( curtok == 3106 ) 
    {
      radix = 16 ;
      m = 134217728L ;
      getxtoken () ;
    } 
    vacuous = true ;
    curval = 0 ;
    while ( true ) {
	
      if ( ( curtok < 3120 + radix ) && ( curtok >= 3120 ) && ( curtok <= 3129 
      ) ) 
      d = curtok - 3120 ;
      else if ( radix == 16 ) {
	  
	if ( ( curtok <= 2886 ) && ( curtok >= 2881 ) ) 
	d = curtok - 2871 ;
	else if ( ( curtok <= 3142 ) && ( curtok >= 3137 ) ) 
	d = curtok - 3127 ;
	else goto lab30 ;
      } 
      else goto lab30 ;
      vacuous = false ;
      if ( ( curval >= m ) && ( ( curval > m ) || ( d > 7 ) || ( radix != 10 ) 
      ) ) 
      {
	if ( OKsofar ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 742 ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 743 ;
	    helpline [0 ]= 744 ;
	  } 
	  error () ;
	  curval = 2147483647L ;
	  OKsofar = false ;
	} 
      } 
      else curval = curval * radix + d ;
      getxtoken () ;
    } 
    lab30: ;
    if ( vacuous ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 705 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 706 ;
	helpline [1 ]= 707 ;
	helpline [0 ]= 708 ;
      } 
      backerror () ;
    } 
    else if ( curcmd != 10 ) 
    backinput () ;
  } 
  if ( negative ) 
  curval = - (integer) curval ;
} 
void 
zscandimen ( boolean mu , boolean inf , boolean shortcut ) 
{
  /* 30 31 32 40 45 88 89 */ scandimen_regmem 
  boolean negative  ;
  integer f  ;
  integer num, denom  ;
  smallnumber k, kk  ;
  halfword p, q  ;
  scaled v  ;
  integer savecurval  ;
  eightbits t  ;
  f = 0 ;
  aritherror = false ;
  curorder = 0 ;
  negative = false ;
  if ( ! shortcut ) 
  {
    negative = false ;
    do {
	do { getxtoken () ;
      } while ( ! ( curcmd != 10 ) ) ;
      if ( curtok == 3117 ) 
      {
	negative = ! negative ;
	curtok = 3115 ;
      } 
    } while ( ! ( curtok != 3115 ) ) ;
    if ( ( curcmd >= 73 ) && ( curcmd <= 102 ) ) {
	
      if ( mu ) 
      {
	scansomethinginternal ( 3 , false ) ;
	if ( curvallevel >= 2 ) 
	{
	  v = mem [curval + 1 ].cint ;
	  deleteglueref ( curval ) ;
	  curval = v ;
	} 
	if ( curvallevel == 3 ) 
	goto lab89 ;
	if ( curvallevel != 0 ) 
	muerror () ;
      } 
      else {
	  
	scansomethinginternal ( 1 , false ) ;
	if ( curvallevel == 1 ) 
	goto lab89 ;
      } 
    } 
    else {
	
      backinput () ;
      if ( curtok == 3116 ) 
      curtok = 3118 ;
      if ( curtok != 3118 ) 
      scanint () ;
      else {
	  
	radix = 10 ;
	curval = 0 ;
      } 
      if ( curtok == 3116 ) 
      curtok = 3118 ;
      if ( ( radix == 10 ) && ( curtok == 3118 ) ) 
      {
	k = 0 ;
	p = -1073741823L ;
	gettoken () ;
	while ( true ) {
	    
	  getxtoken () ;
	  if ( ( curtok > 3129 ) || ( curtok < 3120 ) ) 
	  goto lab31 ;
	  if ( k < 17 ) 
	  {
	    q = getavail () ;
	    mem [q ].hh .v.RH = p ;
	    mem [q ].hh .v.LH = curtok - 3120 ;
	    p = q ;
	    incr ( k ) ;
	  } 
	} 
	lab31: {
	    register integer for_end; kk = k ;for_end = 1 ; if ( kk >= 
	for_end) do 
	  {
	    dig [kk - 1 ]= mem [p ].hh .v.LH ;
	    q = p ;
	    p = mem [p ].hh .v.RH ;
	    {
	      mem [q ].hh .v.RH = avail ;
	      avail = q ;
	;
#ifdef STAT
	      decr ( dynused ) ;
#endif /* STAT */
	    } 
	  } 
	while ( kk-- > for_end ) ;} 
	f = rounddecimals ( k ) ;
	if ( curcmd != 10 ) 
	backinput () ;
      } 
    } 
  } 
  if ( curval < 0 ) 
  {
    negative = ! negative ;
    curval = - (integer) curval ;
  } 
  if ( inf ) {
      
    if ( scankeyword ( 315 ) ) 
    {
      curorder = 1 ;
      while ( scankeyword ( 108 ) ) {
	  
	if ( curorder == 3 ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 746 ) ;
	  } 
	  print ( 747 ) ;
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 748 ;
	  } 
	  error () ;
	} 
	else incr ( curorder ) ;
      } 
      goto lab88 ;
    } 
  } 
  savecurval = curval ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( ( curcmd < 73 ) || ( curcmd > 102 ) ) 
  backinput () ;
  else {
      
    if ( mu ) 
    {
      scansomethinginternal ( 3 , false ) ;
      if ( curvallevel >= 2 ) 
      {
	v = mem [curval + 1 ].cint ;
	deleteglueref ( curval ) ;
	curval = v ;
      } 
      if ( curvallevel != 3 ) 
      muerror () ;
    } 
    else scansomethinginternal ( 1 , false ) ;
    v = curval ;
    goto lab40 ;
  } 
  if ( mu ) 
  goto lab45 ;
  if ( scankeyword ( 749 ) ) 
  v = ( fontinfo [6 + parambase [eqtb [25582 ].hh .v.RH ]].cint ) ;
  else if ( scankeyword ( 750 ) ) 
  v = ( fontinfo [5 + parambase [eqtb [25582 ].hh .v.RH ]].cint ) ;
  else if ( scankeyword ( 751 ) ) {
      
    if ( curlist .dirfield == 3 ) 
    v = fontinfo [widthbase [eqtb [25632 ].hh .v.RH ]+ fontinfo [
    charbase [eqtb [25632 ].hh .v.RH ]+ 0 ].qqqq .b0 ].cint ;
    else v = fontinfo [widthbase [eqtb [25631 ].hh .v.RH ]+ fontinfo [
    charbase [eqtb [25631 ].hh .v.RH ]+ 0 ].qqqq .b0 ].cint ;
  } 
  else if ( scankeyword ( 752 ) ) {
      
    if ( curlist .dirfield == 3 ) 
    {
      t = fontinfo [charbase [eqtb [25632 ].hh .v.RH ]+ 0 ].qqqq .b1 ;
      v = fontinfo [heightbase [eqtb [25632 ].hh .v.RH ]+ ( t ) / 16 ]
      .cint + fontinfo [depthbase [eqtb [25632 ].hh .v.RH ]+ ( t ) % 16 ]
      .cint ;
    } 
    else {
	
      t = fontinfo [charbase [eqtb [25631 ].hh .v.RH ]+ 0 ].qqqq .b1 ;
      v = fontinfo [heightbase [eqtb [25631 ].hh .v.RH ]+ ( t ) / 16 ]
      .cint + fontinfo [depthbase [eqtb [25631 ].hh .v.RH ]+ ( t ) % 16 ]
      .cint ;
    } 
  } 
  else goto lab45 ;
  {
    getxtoken () ;
    if ( curcmd != 10 ) 
    backinput () ;
  } 
  lab40: curval = multandadd ( savecurval , v , xnoverd ( v , f , 65536L ) , 
  1073741823L ) ;
  goto lab89 ;
  lab45: ;
  if ( mu ) {
      
    if ( scankeyword ( 343 ) ) 
    goto lab88 ;
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 746 ) ;
      } 
      print ( 753 ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 754 ;
	helpline [2 ]= 755 ;
	helpline [1 ]= 756 ;
	helpline [0 ]= 757 ;
      } 
      error () ;
      goto lab88 ;
    } 
  } 
  if ( scankeyword ( 745 ) ) 
  {
    preparemag () ;
    if ( eqtb [28479 ].cint != 1000 ) 
    {
      curval = xnoverd ( curval , 1000 , eqtb [28479 ].cint ) ;
      f = ( 1000 * f + 65536L * texremainder ) / eqtb [28479 ].cint ;
      curval = curval + ( f / 65536L ) ;
      f = f % 65536L ;
    } 
  } 
  if ( scankeyword ( 416 ) ) 
  goto lab88 ;
  if ( scankeyword ( 758 ) ) 
  {
    num = 7227 ;
    denom = 100 ;
  } 
  else if ( scankeyword ( 759 ) ) 
  {
    num = 12 ;
    denom = 1 ;
  } 
  else if ( scankeyword ( 760 ) ) 
  {
    num = 7227 ;
    denom = 254 ;
  } 
  else if ( scankeyword ( 761 ) ) 
  {
    num = 7227 ;
    denom = 2540 ;
  } 
  else if ( scankeyword ( 762 ) ) 
  {
    num = 7227 ;
    denom = 7200 ;
  } 
  else if ( scankeyword ( 763 ) ) 
  {
    num = 1238 ;
    denom = 1157 ;
  } 
  else if ( scankeyword ( 764 ) ) 
  {
    num = 14856 ;
    denom = 1157 ;
  } 
  else if ( scankeyword ( 72 ) ) 
  {
    num = 7227 ;
    denom = 10160 ;
  } 
  else if ( scankeyword ( 81 ) ) 
  {
    num = 7227 ;
    denom = 10160 ;
  } 
  else if ( scankeyword ( 765 ) ) 
  goto lab30 ;
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 746 ) ;
    } 
    print ( 766 ) ;
    {
      helpptr = 6 ;
      helpline [5 ]= 767 ;
      helpline [4 ]= 768 ;
      helpline [3 ]= 769 ;
      helpline [2 ]= 755 ;
      helpline [1 ]= 756 ;
      helpline [0 ]= 757 ;
    } 
    error () ;
    goto lab32 ;
  } 
  curval = xnoverd ( curval , num , denom ) ;
  f = ( num * f + 65536L * texremainder ) / denom ;
  curval = curval + ( f / 65536L ) ;
  f = f % 65536L ;
  lab32: ;
  lab88: if ( curval >= 16384 ) 
  aritherror = true ;
  else curval = curval * 65536L + f ;
  lab30: ;
  {
    getxtoken () ;
    if ( curcmd != 10 ) 
    backinput () ;
  } 
  lab89: if ( aritherror || ( abs ( curval ) >= 1073741824L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 770 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 771 ;
      helpline [0 ]= 772 ;
    } 
    error () ;
    curval = 1073741823L ;
    aritherror = false ;
  } 
  if ( negative ) 
  curval = - (integer) curval ;
} 
void 
zscanglue ( smallnumber level ) 
{
  /* 10 */ scanglue_regmem 
  boolean negative  ;
  halfword q  ;
  boolean mu  ;
  mu = ( level == 3 ) ;
  negative = false ;
  do {
      do { getxtoken () ;
    } while ( ! ( curcmd != 10 ) ) ;
    if ( curtok == 3117 ) 
    {
      negative = ! negative ;
      curtok = 3115 ;
    } 
  } while ( ! ( curtok != 3115 ) ) ;
  if ( ( curcmd >= 73 ) && ( curcmd <= 102 ) ) 
  {
    scansomethinginternal ( level , negative ) ;
    if ( curvallevel >= 2 ) 
    {
      if ( curvallevel != level ) 
      muerror () ;
      return ;
    } 
    if ( curvallevel == 0 ) 
    scandimen ( mu , false , true ) ;
    else if ( level == 3 ) 
    muerror () ;
  } 
  else {
      
    backinput () ;
    scandimen ( mu , false , false ) ;
    if ( negative ) 
    curval = - (integer) curval ;
  } 
  q = newspec ( membot ) ;
  mem [q + 1 ].cint = curval ;
  if ( scankeyword ( 773 ) ) 
  {
    scandimen ( mu , true , false ) ;
    mem [q + 2 ].cint = curval ;
    mem [q ].hh.b0 = curorder ;
  } 
  if ( scankeyword ( 774 ) ) 
  {
    scandimen ( mu , true , false ) ;
    mem [q + 3 ].cint = curval ;
    mem [q ].hh.b1 = curorder ;
  } 
  curval = q ;
} 
halfword 
scanrulespec ( void ) 
{
  /* 21 */ register halfword Result; scanrulespec_regmem 
  halfword q  ;
  q = newrule () ;
  if ( curcmd == 39 ) 
  mem [q + 1 ].cint = 26214 ;
  else {
      
    mem [q + 3 ].cint = 26214 ;
    mem [q + 2 ].cint = 0 ;
  } 
  lab21: if ( scankeyword ( 775 ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [q + 1 ].cint = curval ;
    goto lab21 ;
  } 
  if ( scankeyword ( 776 ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [q + 3 ].cint = curval ;
    goto lab21 ;
  } 
  if ( scankeyword ( 777 ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [q + 2 ].cint = curval ;
    goto lab21 ;
  } 
  Result = q ;
  return Result ;
} 
halfword 
zstrtoks ( poolpointer b ) 
{
  register halfword Result; strtoks_regmem 
  halfword p  ;
  halfword q  ;
  halfword t  ;
  poolpointer k  ;
  unsigned char cc  ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 258 , poolsize - initpoolptr ) ;
  } 
  p = memtop - 3 ;
  mem [p ].hh .v.RH = -1073741823L ;
  k = b ;
  while ( k < poolptr ) {
      
    t = fromBUFF ( ustringcast ( strpool ) , poolptr , k ) ;
    cc = eqtb [25892 + kcatcodekey ( t ) ].hh .v.RH ;
    if ( ( multistrlen ( ustringcast ( strpool ) , poolptr , k ) > 1 ) && 
    checkkcatcode ( cc ) ) 
    {
      if ( ( cc == 15 ) ) 
      cc = 18 ;
      t = t + cc * 16777216L ;
      k = k + multistrlen ( ustringcast ( strpool ) , poolptr , k ) - 1 ;
    } 
    else {
	
      t = strpool [k ];
      if ( t == 32 ) 
      t = 2592 ;
      else t = 3072 + t ;
    } 
    {
      {
	q = avail ;
	if ( q == -1073741823L ) 
	q = getavail () ;
	else {
	    
	  avail = mem [q ].hh .v.RH ;
	  mem [q ].hh .v.RH = -1073741823L ;
	;
#ifdef STAT
	  incr ( dynused ) ;
#endif /* STAT */
	} 
      } 
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = t ;
      p = q ;
    } 
    incr ( k ) ;
  } 
  poolptr = b ;
  Result = p ;
  return Result ;
} 
halfword 
thetoks ( void ) 
{
  register halfword Result; thetoks_regmem 
  unsigned char oldsetting  ;
  halfword p, q, r  ;
  poolpointer b  ;
  getxtoken () ;
  scansomethinginternal ( 5 , false ) ;
  if ( curvallevel >= 4 ) 
  {
    p = memtop - 3 ;
    mem [p ].hh .v.RH = -1073741823L ;
    if ( curvallevel == 4 ) 
    {
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = 536870911L + curval ;
      p = q ;
    } 
    else if ( curval != -1073741823L ) 
    {
      r = mem [curval ].hh .v.RH ;
      while ( r != -1073741823L ) {
	  
	{
	  {
	    q = avail ;
	    if ( q == -1073741823L ) 
	    q = getavail () ;
	    else {
		
	      avail = mem [q ].hh .v.RH ;
	      mem [q ].hh .v.RH = -1073741823L ;
	;
#ifdef STAT
	      incr ( dynused ) ;
#endif /* STAT */
	    } 
	  } 
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = mem [r ].hh .v.LH ;
	  p = q ;
	} 
	r = mem [r ].hh .v.RH ;
      } 
    } 
    Result = p ;
  } 
  else {
      
    oldsetting = selector ;
    selector = 21 ;
    b = poolptr ;
    switch ( curvallevel ) 
    {case 0 : 
      printint ( curval ) ;
      break ;
    case 1 : 
      {
	printscaled ( curval ) ;
	print ( 416 ) ;
      } 
      break ;
    case 2 : 
      {
	printspec ( curval , 416 ) ;
	deleteglueref ( curval ) ;
      } 
      break ;
    case 3 : 
      {
	printspec ( curval , 343 ) ;
	deleteglueref ( curval ) ;
      } 
      break ;
    } 
    selector = oldsetting ;
    Result = strtoks ( b ) ;
  } 
  return Result ;
} 
void 
insthetoks ( void ) 
{
  insthetoks_regmem 
  mem [memtop - 12 ].hh .v.RH = thetoks () ;
  begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
} 
void 
convtoks ( void ) 
{
  convtoks_regmem 
  unsigned char oldsetting  ;
  KANJIcode cx  ;
  unsigned char c  ;
  smallnumber savescannerstatus  ;
  poolpointer b  ;
  c = curchr ;
  cx = 0 ;
  switch ( c ) 
  {case 0 : 
  case 1 : 
  case 2 : 
  case 6 : 
  case 7 : 
  case 8 : 
  case 9 : 
  case 10 : 
    scanint () ;
    break ;
  case 3 : 
  case 4 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      gettoken () ;
      if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
      cx = curtok ;
      scannerstatus = savescannerstatus ;
    } 
    break ;
  case 5 : 
    scanfontident () ;
    break ;
  case 11 : 
    if ( jobname == 0 ) 
    openlogfile () ;
    break ;
  } 
  oldsetting = selector ;
  selector = 21 ;
  b = poolptr ;
  switch ( c ) 
  {case 0 : 
    printint ( curval ) ;
    break ;
  case 1 : 
    printromanint ( curval ) ;
    break ;
  case 8 : 
    printint ( fromJIS ( curval ) ) ;
    break ;
  case 6 : 
    printint ( fromEUC ( curval ) ) ;
    break ;
  case 7 : 
    printint ( fromSJIS ( curval ) ) ;
    break ;
  case 9 : 
    printint ( fromKUTEN ( curval ) ) ;
    break ;
  case 10 : 
    printint ( fromUCS ( curval ) ) ;
    break ;
  case 2 : 
    printkansuji ( curval ) ;
    break ;
  case 3 : 
    if ( curcs != 0 ) 
    sprintcs ( curcs ) ;
    else if ( cx == 0 ) 
    printchar ( curchr ) ;
    else printkanji ( cx ) ;
    break ;
  case 4 : 
    printmeaning () ;
    break ;
  case 5 : 
    {
      print ( fontname [curval ]) ;
      if ( fontsize [curval ]!= fontdsize [curval ]) 
      {
	print ( 790 ) ;
	printscaled ( fontsize [curval ]) ;
	print ( 416 ) ;
      } 
    } 
    break ;
  case 11 : 
    print ( jobname ) ;
    break ;
  } 
  selector = oldsetting ;
  mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
  begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
} 
halfword 
zscantoks ( boolean macrodef , boolean xpand ) 
{
  /* 40 30 31 32 */ register halfword Result; scantoks_regmem 
  halfword t  ;
  halfword s  ;
  halfword p  ;
  halfword q  ;
  halfword unbalance  ;
  halfword hashbrace  ;
  if ( macrodef ) 
  scannerstatus = 2 ;
  else scannerstatus = 5 ;
  warningindex = curcs ;
  defref = getavail () ;
  mem [defref ].hh .v.LH = -1073741823L ;
  p = defref ;
  hashbrace = 0 ;
  t = 3120 ;
  if ( macrodef ) 
  {
    while ( true ) {
	
      gettoken () ;
      if ( curtok < 768 ) 
      goto lab31 ;
      if ( curcmd == 6 ) 
      {
	s = 3328 + curchr ;
	gettoken () ;
	if ( curcmd == 1 ) 
	{
	  hashbrace = curtok ;
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = curtok ;
	    p = q ;
	  } 
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = 3584 ;
	    p = q ;
	  } 
	  goto lab30 ;
	} 
	if ( t == 3129 ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 793 ) ;
	  } 
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 794 ;
	  } 
	  error () ;
	} 
	else {
	    
	  incr ( t ) ;
	  if ( curtok != t ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 263 ) ;
	      print ( 795 ) ;
	    } 
	    {
	      helpptr = 2 ;
	      helpline [1 ]= 796 ;
	      helpline [0 ]= 797 ;
	    } 
	    backerror () ;
	  } 
	  curtok = s ;
	} 
      } 
      {
	q = getavail () ;
	mem [p ].hh .v.RH = q ;
	mem [q ].hh .v.LH = curtok ;
	p = q ;
      } 
    } 
    lab31: {
	
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = 3584 ;
      p = q ;
    } 
    if ( curcmd == 2 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 698 ) ;
      } 
      incr ( alignstate ) ;
      {
	helpptr = 2 ;
	helpline [1 ]= 791 ;
	helpline [0 ]= 792 ;
      } 
      error () ;
      goto lab40 ;
    } 
    lab30: ;
  } 
  else scanleftbrace () ;
  unbalance = 1 ;
  while ( true ) {
      
    if ( xpand ) 
    {
      while ( true ) {
	  
	getnext () ;
	if ( curcmd <= 115 ) 
	goto lab32 ;
	if ( curcmd != 124 ) 
	expand () ;
	else {
	    
	  q = thetoks () ;
	  if ( mem [memtop - 3 ].hh .v.RH != -1073741823L ) 
	  {
	    mem [p ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
	    p = q ;
	  } 
	} 
      } 
      lab32: xtoken () ;
    } 
    else gettoken () ;
    if ( curtok < 768 ) {
	
      if ( curcmd < 2 ) 
      incr ( unbalance ) ;
      else {
	  
	decr ( unbalance ) ;
	if ( unbalance == 0 ) 
	goto lab40 ;
      } 
    } 
    else if ( curcmd == 6 ) {
	
      if ( macrodef ) 
      {
	s = curtok ;
	if ( xpand ) 
	getxtoken () ;
	else gettoken () ;
	if ( curcmd != 6 ) {
	    
	  if ( ( curtok <= 3120 ) || ( curtok > t ) ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 263 ) ;
	      print ( 798 ) ;
	    } 
	    sprintcs ( warningindex ) ;
	    {
	      helpptr = 3 ;
	      helpline [2 ]= 799 ;
	      helpline [1 ]= 800 ;
	      helpline [0 ]= 801 ;
	    } 
	    backerror () ;
	    curtok = s ;
	  } 
	  else curtok = 1232 + curchr ;
	} 
      } 
    } 
    {
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = curtok ;
      p = q ;
    } 
  } 
  lab40: scannerstatus = 0 ;
  if ( hashbrace != 0 ) 
  {
    q = getavail () ;
    mem [p ].hh .v.RH = q ;
    mem [q ].hh .v.LH = hashbrace ;
    p = q ;
  } 
  Result = p ;
  return Result ;
} 
void 
zreadtoks ( integer n , halfword r ) 
{
  /* 30 */ readtoks_regmem 
  halfword p  ;
  halfword q  ;
  integer s  ;
  smallnumber m  ;
  scannerstatus = 2 ;
  warningindex = r ;
  defref = getavail () ;
  mem [defref ].hh .v.LH = -1073741823L ;
  p = defref ;
  {
    q = getavail () ;
    mem [p ].hh .v.RH = q ;
    mem [q ].hh .v.LH = 3584 ;
    p = q ;
  } 
  if ( ( n < 0 ) || ( n > 15 ) ) 
  m = 16 ;
  else m = n ;
  s = alignstate ;
  alignstate = 1000000L ;
  do {
      beginfilereading () ;
    curinput .namefield = m + 1 ;
    if ( readopen [m ]== 2 ) {
	
      if ( interaction > 1 ) {
	  
	if ( n < 0 ) 
	{
	  ;
	  print ( 344 ) ;
	  terminput () ;
	} 
	else {
	    
	  ;
	  println () ;
	  sprintcs ( r ) ;
	  {
	    ;
	    print ( 61 ) ;
	    terminput () ;
	  } 
	  n = -1 ;
	} 
      } 
      else fatalerror ( 802 ) ;
    } 
    else if ( readopen [m ]== 1 ) {
	
      if ( inputln ( readfile [m ], false ) ) 
      readopen [m ]= 0 ;
      else {
	  
	aclose ( readfile [m ]) ;
	readopen [m ]= 2 ;
      } 
    } 
    else {
	
      if ( ! inputln ( readfile [m ], true ) ) 
      {
	aclose ( readfile [m ]) ;
	readopen [m ]= 2 ;
	if ( alignstate != 1000000L ) 
	{
	  runaway () ;
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 803 ) ;
	  } 
	  printesc ( 572 ) ;
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 804 ;
	  } 
	  alignstate = 1000000L ;
	  error () ;
	} 
      } 
    } 
    curinput .limitfield = last ;
    if ( ( eqtb [28511 ].cint < 0 ) || ( eqtb [28511 ].cint > 255 ) ) 
    decr ( curinput .limitfield ) ;
    else buffer [curinput .limitfield ]= eqtb [28511 ].cint ;
    first = curinput .limitfield + 1 ;
    curinput .locfield = curinput .startfield ;
    curinput .statefield = 61 ;
    while ( true ) {
	
      gettoken () ;
      if ( curtok == 0 ) 
      goto lab30 ;
      if ( alignstate < 1000000L ) 
      {
	do {
	    gettoken () ;
	} while ( ! ( curtok == 0 ) ) ;
	alignstate = 1000000L ;
	goto lab30 ;
      } 
      {
	q = getavail () ;
	mem [p ].hh .v.RH = q ;
	mem [q ].hh .v.LH = curtok ;
	p = q ;
      } 
    } 
    lab30: endfilereading () ;
  } while ( ! ( alignstate == 1000000L ) ) ;
  curval = defref ;
  scannerstatus = 0 ;
  alignstate = s ;
} 
void 
passtext ( void ) 
{
  /* 30 */ passtext_regmem 
  integer l  ;
  smallnumber savescannerstatus  ;
  savescannerstatus = scannerstatus ;
  scannerstatus = 1 ;
  l = 0 ;
  skipline = line ;
  while ( true ) {
      
    getnext () ;
    if ( curcmd == 121 ) 
    {
      if ( l == 0 ) 
      goto lab30 ;
      if ( curchr == 2 ) 
      decr ( l ) ;
    } 
    else if ( curcmd == 120 ) 
    incr ( l ) ;
  } 
  lab30: scannerstatus = savescannerstatus ;
} 
void 
zchangeiflimit ( smallnumber l , halfword p ) 
{
  /* 10 */ changeiflimit_regmem 
  halfword q  ;
  if ( p == condptr ) 
  iflimit = l ;
  else {
      
    q = condptr ;
    while ( true ) {
	
      if ( q == -1073741823L ) 
      confusion ( 805 ) ;
      if ( mem [q ].hh .v.RH == p ) 
      {
	mem [q ].hh.b0 = l ;
	return ;
      } 
      q = mem [q ].hh .v.RH ;
    } 
  } 
} 
void 
conditional ( void ) 
{
  /* 10 50 */ conditional_regmem 
  boolean b  ;
  unsigned char r  ;
  integer m, n  ;
  halfword p, q  ;
  smallnumber savescannerstatus  ;
  halfword savecondptr  ;
  smallnumber thisif  ;
  {
    p = getnode ( 2 ) ;
    mem [p ].hh .v.RH = condptr ;
    mem [p ].hh.b0 = iflimit ;
    mem [p ].hh.b1 = curif ;
    mem [p + 1 ].cint = ifline ;
    condptr = p ;
    curif = curchr ;
    iflimit = 1 ;
    ifline = line ;
  } 
  savecondptr = condptr ;
  thisif = curchr ;
  switch ( thisif ) 
  {case 0 : 
  case 1 : 
    {
      {
	getxtoken () ;
	if ( curcmd == 0 ) {
	    
	  if ( curchr == 257 ) 
	  {
	    curcmd = 13 ;
	    curchr = curtok - 536870912L ;
	  } 
	} 
      } 
      if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
      {
	m = curcmd ;
	n = curchr ;
      } 
      else if ( ( curcmd > 13 ) || ( curchr > 255 ) ) 
      {
	m = 0 ;
	n = 256 ;
      } 
      else {
	  
	m = curcmd ;
	n = curchr ;
      } 
      {
	getxtoken () ;
	if ( curcmd == 0 ) {
	    
	  if ( curchr == 257 ) 
	  {
	    curcmd = 13 ;
	    curchr = curtok - 536870912L ;
	  } 
	} 
      } 
      if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
      {
	curcmd = curcmd ;
      } 
      else if ( ( curcmd > 13 ) || ( curchr > 255 ) ) 
      {
	curcmd = 0 ;
	curchr = 256 ;
      } 
      if ( thisif == 0 ) 
      b = ( n == curchr ) ;
      else b = ( m == curcmd ) ;
    } 
    break ;
  case 2 : 
  case 3 : 
    {
      if ( thisif == 2 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      n = curval ;
      do {
	  getxtoken () ;
      } while ( ! ( curcmd != 10 ) ) ;
      if ( ( curtok >= 3132 ) && ( curtok <= 3134 ) ) 
      r = curtok - 3072 ;
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 836 ) ;
	} 
	printcmdchr ( 120 , thisif ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 837 ;
	} 
	backerror () ;
	r = 61 ;
      } 
      if ( thisif == 2 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      switch ( r ) 
      {case 60 : 
	b = ( n < curval ) ;
	break ;
      case 61 : 
	b = ( n == curval ) ;
	break ;
      case 62 : 
	b = ( n > curval ) ;
	break ;
      } 
    } 
    break ;
  case 4 : 
    {
      scanint () ;
      b = odd ( curval ) ;
    } 
    break ;
  case 5 : 
    b = ( abs ( curlist .modefield ) == 1 ) ;
    break ;
  case 6 : 
    b = ( abs ( curlist .modefield ) == 117 ) ;
    break ;
  case 7 : 
    b = ( abs ( curlist .modefield ) == 233 ) ;
    break ;
  case 8 : 
    b = ( curlist .modefield < 0 ) ;
    break ;
  case 17 : 
    b = ( abs ( curlist .dirfield ) == 3 ) ;
    break ;
  case 18 : 
    b = ( abs ( curlist .dirfield ) == 4 ) ;
    break ;
  case 19 : 
    b = ( abs ( curlist .dirfield ) == 1 ) ;
    break ;
  case 20 : 
    b = ( curlist .dirfield < 0 ) ;
    break ;
  case 9 : 
  case 10 : 
  case 11 : 
  case 21 : 
  case 22 : 
  case 23 : 
    {
      scaneightbitint () ;
      p = eqtb [25326 + curval ].hh .v.RH ;
      if ( thisif == 9 ) 
      b = ( p == -1073741823L ) ;
      else if ( p == -1073741823L ) 
      b = false ;
      else {
	  
	if ( mem [p ].hh.b0 == 2 ) 
	p = mem [p + 5 ].hh .v.RH ;
	if ( thisif == 10 ) 
	b = ( mem [p ].hh.b0 == 0 ) ;
	else if ( thisif == 11 ) 
	b = ( mem [p ].hh.b0 == 1 ) ;
	else if ( thisif == 21 ) 
	b = ( ( mem [p ].hh.b1 ) == 3 ) ;
	else if ( thisif == 22 ) 
	b = ( ( mem [p ].hh.b1 ) == 4 ) ;
	else b = ( ( mem [p ].hh.b1 ) == 1 ) ;
      } 
    } 
    break ;
  case 12 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      getnext () ;
      n = curcs ;
      p = curcmd ;
      q = curchr ;
      getnext () ;
      if ( curcmd != p ) 
      b = false ;
      else if ( curcmd < 126 ) 
      b = ( curchr == q ) ;
      else {
	  
	p = mem [curchr ].hh .v.RH ;
	q = mem [eqtb [n ].hh .v.RH ].hh .v.RH ;
	if ( p == q ) 
	b = true ;
	else {
	    
	  while ( ( p != -1073741823L ) && ( q != -1073741823L ) ) if ( mem [
	  p ].hh .v.LH != mem [q ].hh .v.LH ) 
	  p = -1073741823L ;
	  else {
	      
	    p = mem [p ].hh .v.RH ;
	    q = mem [q ].hh .v.RH ;
	  } 
	  b = ( ( p == -1073741823L ) && ( q == -1073741823L ) ) ;
	} 
      } 
      scannerstatus = savescannerstatus ;
    } 
    break ;
  case 13 : 
    {
      scanfourbitintor18 () ;
      if ( curval == 18 ) 
      b = ! shellenabledp ;
      else b = ( readopen [curval ]== 2 ) ;
    } 
    break ;
  case 14 : 
    b = true ;
    break ;
  case 15 : 
    b = false ;
    break ;
  case 16 : 
    {
      scanint () ;
      n = curval ;
      if ( eqtb [28498 ].cint > 1 ) 
      {
	begindiagnostic () ;
	print ( 838 ) ;
	printint ( n ) ;
	printchar ( 125 ) ;
	enddiagnostic ( false ) ;
      } 
      while ( n != 0 ) {
	  
	passtext () ;
	if ( condptr == savecondptr ) {
	    
	  if ( curchr == 4 ) 
	  decr ( n ) ;
	  else goto lab50 ;
	} 
	else if ( curchr == 2 ) 
	{
	  p = condptr ;
	  ifline = mem [p + 1 ].cint ;
	  curif = mem [p ].hh.b1 ;
	  iflimit = mem [p ].hh.b0 ;
	  condptr = mem [p ].hh .v.RH ;
	  freenode ( p , 2 ) ;
	} 
      } 
      changeiflimit ( 4 , savecondptr ) ;
      return ;
    } 
    break ;
  } 
  if ( eqtb [28498 ].cint > 1 ) 
  {
    begindiagnostic () ;
    if ( b ) 
    print ( 834 ) ;
    else print ( 835 ) ;
    enddiagnostic ( false ) ;
  } 
  if ( b ) 
  {
    changeiflimit ( 3 , savecondptr ) ;
    return ;
  } 
  while ( true ) {
      
    passtext () ;
    if ( condptr == savecondptr ) 
    {
      if ( curchr != 4 ) 
      goto lab50 ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 832 ) ;
      } 
      printesc ( 830 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 833 ;
      } 
      error () ;
    } 
    else if ( curchr == 2 ) 
    {
      p = condptr ;
      ifline = mem [p + 1 ].cint ;
      curif = mem [p ].hh.b1 ;
      iflimit = mem [p ].hh.b0 ;
      condptr = mem [p ].hh .v.RH ;
      freenode ( p , 2 ) ;
    } 
  } 
  lab50: if ( curchr == 2 ) 
  {
    p = condptr ;
    ifline = mem [p + 1 ].cint ;
    curif = mem [p ].hh.b1 ;
    iflimit = mem [p ].hh.b0 ;
    condptr = mem [p ].hh .v.RH ;
    freenode ( p , 2 ) ;
  } 
  else iflimit = 2 ;
} 
void 
beginname ( void ) 
{
  beginname_regmem 
  areadelimiter = 0 ;
  extdelimiter = 0 ;
  quotedfilename = false ;
  prevchar = 0 ;
} 
boolean 
zmorename ( ASCIIcode c ) 
{
  register boolean Result; morename_regmem 
  if ( ( c == 32 ) && stopatspace && ( ! quotedfilename ) ) 
  Result = false ;
  else if ( c == 34 ) 
  {
    quotedfilename = ! quotedfilename ;
    Result = true ;
  } 
  else {
      
    {
      if ( poolptr + 1 > poolsize ) 
      overflow ( 258 , poolsize - initpoolptr ) ;
    } 
    {
      strpool [poolptr ]= c ;
      incr ( poolptr ) ;
    } 
    if ( ( ISDIRSEP ( c ) && ( notkanjicharseq ( prevchar , c ) ) ) ) 
    {
      areadelimiter = ( poolptr - strstart [strptr ]) ;
      extdelimiter = 0 ;
    } 
    else if ( c == 46 ) 
    extdelimiter = ( poolptr - strstart [strptr ]) ;
    Result = true ;
  } 
  prevchar = c ;
  return Result ;
} 
void 
endname ( void ) 
{
  endname_regmem 
  strnumber tempstr  ;
  poolpointer j, s, t  ;
  boolean mustquote  ;
  if ( strptr + 3 > maxstrings ) 
  overflow ( 259 , maxstrings - initstrptr ) ;
  {
    if ( poolptr + 6 > poolsize ) 
    overflow ( 258 , poolsize - initpoolptr ) ;
  } 
  if ( areadelimiter != 0 ) 
  {
    mustquote = false ;
    s = strstart [strptr ];
    t = strstart [strptr ]+ areadelimiter ;
    j = s ;
    while ( ( ! mustquote ) && ( j < t ) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
    if ( mustquote ) 
    {
      {register integer for_end; j = poolptr - 1 ;for_end = t ; if ( j >= 
      for_end) do 
	strpool [j + 2 ]= strpool [j ];
      while ( j-- > for_end ) ;} 
      strpool [t + 1 ]= 34 ;
      {register integer for_end; j = t - 1 ;for_end = s ; if ( j >= for_end) 
      do 
	strpool [j + 1 ]= strpool [j ];
      while ( j-- > for_end ) ;} 
      strpool [s ]= 34 ;
      if ( extdelimiter != 0 ) 
      extdelimiter = extdelimiter + 2 ;
      areadelimiter = areadelimiter + 2 ;
      poolptr = poolptr + 2 ;
    } 
  } 
  s = strstart [strptr ]+ areadelimiter ;
  if ( extdelimiter == 0 ) 
  t = poolptr ;
  else t = strstart [strptr ]+ extdelimiter - 1 ;
  mustquote = false ;
  j = s ;
  while ( ( ! mustquote ) && ( j < t ) ) {
      
    mustquote = strpool [j ]== 32 ;
    incr ( j ) ;
  } 
  if ( mustquote ) 
  {
    {register integer for_end; j = poolptr - 1 ;for_end = t ; if ( j >= 
    for_end) do 
      strpool [j + 2 ]= strpool [j ];
    while ( j-- > for_end ) ;} 
    strpool [t + 1 ]= 34 ;
    {register integer for_end; j = t - 1 ;for_end = s ; if ( j >= for_end) 
    do 
      strpool [j + 1 ]= strpool [j ];
    while ( j-- > for_end ) ;} 
    strpool [s ]= 34 ;
    if ( extdelimiter != 0 ) 
    extdelimiter = extdelimiter + 2 ;
    poolptr = poolptr + 2 ;
  } 
  if ( extdelimiter != 0 ) 
  {
    s = strstart [strptr ]+ extdelimiter - 1 ;
    t = poolptr ;
    mustquote = false ;
    j = s ;
    while ( ( ! mustquote ) && ( j < t ) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
    if ( mustquote ) 
    {
      strpool [t + 1 ]= 34 ;
      {register integer for_end; j = t - 1 ;for_end = s ; if ( j >= for_end) 
      do 
	strpool [j + 1 ]= strpool [j ];
      while ( j-- > for_end ) ;} 
      strpool [s ]= 34 ;
      poolptr = poolptr + 2 ;
    } 
  } 
  if ( areadelimiter == 0 ) 
  curarea = 344 ;
  else {
      
    curarea = strptr ;
    strstart [strptr + 1 ]= strstart [strptr ]+ areadelimiter ;
    incr ( strptr ) ;
    tempstr = searchstring ( curarea ) ;
    if ( tempstr > 0 ) 
    {
      curarea = tempstr ;
      decr ( strptr ) ;
      {register integer for_end; j = strstart [strptr + 1 ];for_end = 
      poolptr - 1 ; if ( j <= for_end) do 
	{
	  strpool [j - areadelimiter ]= strpool [j ];
	} 
      while ( j++ < for_end ) ;} 
      poolptr = poolptr - areadelimiter ;
    } 
  } 
  if ( extdelimiter == 0 ) 
  {
    curext = 344 ;
    curname = slowmakestring () ;
  } 
  else {
      
    curname = strptr ;
    strstart [strptr + 1 ]= strstart [strptr ]+ extdelimiter - 
    areadelimiter - 1 ;
    incr ( strptr ) ;
    curext = makestring () ;
    decr ( strptr ) ;
    tempstr = searchstring ( curname ) ;
    if ( tempstr > 0 ) 
    {
      curname = tempstr ;
      decr ( strptr ) ;
      {register integer for_end; j = strstart [strptr + 1 ];for_end = 
      poolptr - 1 ; if ( j <= for_end) do 
	{
	  strpool [j - extdelimiter + areadelimiter + 1 ]= strpool [j ];
	} 
      while ( j++ < for_end ) ;} 
      poolptr = poolptr - extdelimiter + areadelimiter + 1 ;
    } 
    curext = slowmakestring () ;
  } 
} 
void 
zpackfilename ( strnumber n , strnumber a , strnumber e ) 
{
  packfilename_regmem 
  integer k  ;
  ASCIIcode c  ;
  poolpointer j  ;
  k = 0 ;
  if ( nameoffile ) 
  libcfree ( nameoffile ) ;
  nameoffile = xmallocarray ( ASCIIcode , ( strstart [a + 1 ]- strstart [a 
  ]) + ( strstart [n + 1 ]- strstart [n ]) + ( strstart [e + 1 ]- 
  strstart [e ]) + 1 ) ;
  {register integer for_end; j = strstart [a ];for_end = strstart [a + 1 
  ]- 1 ; if ( j <= for_end) do 
    {
      c = strpool [j ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = strstart [n ];for_end = strstart [n + 1 
  ]- 1 ; if ( j <= for_end) do 
    {
      c = strpool [j ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = strstart [e ];for_end = strstart [e + 1 
  ]- 1 ; if ( j <= for_end) do 
    {
      c = strpool [j ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  if ( k <= maxint ) 
  namelength = k ;
  else namelength = maxint ;
  nameoffile [namelength + 1 ]= 0 ;
} 
void 
zpackbufferedname ( smallnumber n , integer a , integer b ) 
{
  packbufferedname_regmem 
  integer k  ;
  ASCIIcode c  ;
  integer j  ;
  if ( n + b - a + 5 > maxint ) 
  b = a + maxint - n - 5 ;
  k = 0 ;
  if ( nameoffile ) 
  libcfree ( nameoffile ) ;
  nameoffile = xmallocarray ( ASCIIcode , n + ( b - a + 1 ) + 5 ) ;
  {register integer for_end; j = 1 ;for_end = n ; if ( j <= for_end) do 
    {
      c = xord [ucharcast ( TEXformatdefault [j ]) ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = a ;for_end = b ; if ( j <= for_end) do 
    {
      c = buffer [j ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = formatdefaultlength - 3 ;for_end = 
  formatdefaultlength ; if ( j <= for_end) do 
    {
      c = xord [ucharcast ( TEXformatdefault [j ]) ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  if ( k <= maxint ) 
  namelength = k ;
  else namelength = maxint ;
  nameoffile [namelength + 1 ]= 0 ;
} 
strnumber 
makenamestring ( void ) 
{
  register strnumber Result; makenamestring_regmem 
  integer k  ;
  poolpointer saveareadelimiter, saveextdelimiter  ;
  boolean savenameinprogress, savestopatspace  ;
  if ( ( poolptr + namelength > poolsize ) || ( strptr == maxstrings ) || ( ( 
  poolptr - strstart [strptr ]) > 0 ) ) 
  Result = 63 ;
  else {
      
    {register integer for_end; k = 1 ;for_end = namelength ; if ( k <= 
    for_end) do 
      {
	strpool [poolptr ]= xord [nameoffile [k ]];
	incr ( poolptr ) ;
      } 
    while ( k++ < for_end ) ;} 
    Result = makestring () ;
    saveareadelimiter = areadelimiter ;
    saveextdelimiter = extdelimiter ;
    savenameinprogress = nameinprogress ;
    savestopatspace = stopatspace ;
    nameinprogress = true ;
    beginname () ;
    stopatspace = false ;
    k = 1 ;
    while ( ( k <= namelength ) && ( morename ( nameoffile [k ]) ) ) incr ( 
    k ) ;
    stopatspace = savestopatspace ;
    endname () ;
    nameinprogress = savenameinprogress ;
    areadelimiter = saveareadelimiter ;
    extdelimiter = saveextdelimiter ;
  } 
  return Result ;
} 
strnumber 
zamakenamestring ( alphafile f ) 
{
  register strnumber Result; amakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
strnumber 
zbmakenamestring ( bytefile f ) 
{
  register strnumber Result; bmakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
strnumber 
zwmakenamestring ( wordfile f ) 
{
  register strnumber Result; wmakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
void 
scanfilename ( void ) 
{
  /* 30 */ scanfilename_regmem 
  nameinprogress = true ;
  beginname () ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  skipmode = false ;
  while ( true ) {
      
    if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
    {
      {
	if ( poolptr + 4 > poolsize ) 
	overflow ( 258 , poolsize - initpoolptr ) ;
      } 
      curchr = toBUFF ( curchr ) ;
      if ( BYTE1 ( curchr ) != 0 ) 
      {
	strpool [poolptr ]= BYTE1 ( curchr ) ;
	incr ( poolptr ) ;
      } 
      if ( BYTE2 ( curchr ) != 0 ) 
      {
	strpool [poolptr ]= BYTE2 ( curchr ) ;
	incr ( poolptr ) ;
      } 
      if ( BYTE3 ( curchr ) != 0 ) 
      {
	strpool [poolptr ]= BYTE3 ( curchr ) ;
	incr ( poolptr ) ;
      } 
      {
	strpool [poolptr ]= BYTE4 ( curchr ) ;
	incr ( poolptr ) ;
      } 
    } 
    else if ( ( curcmd > 12 ) || ( curchr > 255 ) ) 
    {
      backinput () ;
      goto lab30 ;
    } 
    else if ( ( ( curchr == 32 ) && ( curinput .statefield != 0 ) && ( 
    curinput .locfield > curinput .limitfield ) ) || ! morename ( curchr ) ) 
    goto lab30 ;
    getxtoken () ;
  } 
  lab30: endname () ;
  nameinprogress = false ;
  skipmode = true ;
} 
void 
zpackjobname ( strnumber s ) 
{
  packjobname_regmem 
  curarea = 344 ;
  curext = s ;
  curname = jobname ;
  packfilename ( curname , curarea , curext ) ;
} 
void 
zpromptfilename ( strnumber s , strnumber e ) 
{
  /* 30 */ promptfilename_regmem 
  integer k  ;
  strnumber savedcurname  ;
  strnumber savedcurext  ;
  strnumber savedcurarea  ;
  if ( interaction == 2 ) 
  ;
  if ( s == 840 ) 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 841 ) ;
  } 
  else {
      
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 842 ) ;
  } 
  printfilename ( curname , curarea , curext ) ;
  print ( 843 ) ;
  if ( ( e == 844 ) || ( e == 344 ) ) 
  showcontext () ;
  println () ;
  printcstring ( promptfilenamehelpmsg ) ;
  if ( ( e != 344 ) ) 
  {
    print ( 845 ) ;
    print ( e ) ;
    print ( 39 ) ;
  } 
  print ( 41 ) ;
  println () ;
  printnl ( 846 ) ;
  print ( s ) ;
  if ( interaction < 2 ) 
  fatalerror ( 847 ) ;
  savedcurname = curname ;
  savedcurext = curext ;
  savedcurarea = curarea ;
  {
    ;
    print ( 607 ) ;
    terminput () ;
  } 
  {
    beginname () ;
    k = first ;
    while ( ( buffer [k ]== 32 ) && ( k < last ) ) incr ( k ) ;
    while ( true ) {
	
      if ( k == last ) 
      goto lab30 ;
      if ( ! morename ( buffer [k ]) ) 
      goto lab30 ;
      incr ( k ) ;
    } 
    lab30: endname () ;
  } 
  if ( ( ( strstart [curname + 1 ]- strstart [curname ]) == 0 ) && ( 
  curext == 344 ) && ( curarea == 344 ) ) 
  {
    curname = savedcurname ;
    curext = savedcurext ;
    curarea = savedcurarea ;
  } 
  else if ( curext == 344 ) 
  curext = e ;
  packfilename ( curname , curarea , curext ) ;
} 
void 
openlogfile ( void ) 
{
  openlogfile_regmem 
  unsigned char oldsetting  ;
  integer k  ;
  integer l  ;
  constcstring months  ;
  oldsetting = selector ;
  if ( jobname == 0 ) 
  jobname = getjobname ( 850 ) ;
  packjobname ( 851 ) ;
  recorderchangefilename ( stringcast ( nameoffile + 1 ) ) ;
  packjobname ( 852 ) ;
  while ( ! aopenout ( logfile ) ) {
      
    selector = 17 ;
    promptfilename ( 854 , 852 ) ;
  } 
  texmflogname = amakenamestring ( logfile ) ;
  selector = 18 ;
  logopened = true ;
  {
    if ( srcspecialsp || filelineerrorstylep || parsefirstlinep ) 
    fprintf ( logfile , "%s%s%s",  "This is upTeX, Version 3.14159265" , "-p3.7.1" ,     "-u1.21" ) ;
    else
    fprintf ( logfile , "%s%s%s",  "This is upTeX, Version 3.14159265" , "-p3.7.1" ,     "-u1.21" ) ;
    Fputs ( logfile ,  " (" ) ;
    Fputs ( logfile ,  conststringcast ( getencstring () ) ) ;
    putc ( ')' ,  logfile );
    Fputs ( logfile ,  versionstring ) ;
    slowprint ( formatident ) ;
    print ( 855 ) ;
    printint ( eqtb [28483 ].cint ) ;
    printchar ( 32 ) ;
    months = " JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC" ;
    {register integer for_end; k = 3 * eqtb [28484 ].cint - 2 ;for_end = 3 
    * eqtb [28484 ].cint ; if ( k <= for_end) do 
      putc ( months [k ],  logfile );
    while ( k++ < for_end ) ;} 
    printchar ( 32 ) ;
    printint ( eqtb [28485 ].cint ) ;
    printchar ( 32 ) ;
    printtwo ( eqtb [28482 ].cint / 60 ) ;
    printchar ( 58 ) ;
    printtwo ( eqtb [28482 ].cint % 60 ) ;
    if ( shellenabledp ) 
    {
      putc ('\n',  logfile );
      putc ( ' ' ,  logfile );
      if ( restrictedshell ) 
      {
	Fputs ( logfile ,  "restricted " ) ;
      } 
      Fputs ( logfile ,  "\\write18 enabled." ) ;
    } 
    if ( srcspecialsp ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " Source specials enabled." ) ;
    } 
    if ( filelineerrorstylep ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " file:line:error style messages enabled." ) ;
    } 
    if ( parsefirstlinep ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " %&-line parsing enabled." ) ;
    } 
    if ( translatefilename ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " (" ) ;
      fputs ( translatefilename , logfile ) ;
      putc ( ')' ,  logfile );
    } 
  } 
  if ( mltexenabledp ) 
  {
    putc ('\n',  logfile );
    Fputs ( logfile ,  "MLTeX v2.2 enabled" ) ;
  } 
  inputstack [inputptr ]= curinput ;
  printnl ( 853 ) ;
  l = inputstack [0 ].limitfield ;
  if ( buffer [l ]== eqtb [28511 ].cint ) 
  decr ( l ) ;
  {register integer for_end; k = 1 ;for_end = l ; if ( k <= for_end) do 
    print ( buffer [k ]) ;
  while ( k++ < for_end ) ;} 
  println () ;
  selector = oldsetting + 2 ;
} 
void 
startinput ( void ) 
{
  /* 30 */ startinput_regmem 
  strnumber tempstr  ;
  scanfilename () ;
  packfilename ( curname , curarea , curext ) ;
  while ( true ) {
      
    beginfilereading () ;
    texinputtype = 1 ;
    if ( kpseinnameok ( stringcast ( nameoffile + 1 ) ) && aopenin ( inputfile 
    [curinput .indexfield ], kpsetexformat ) ) 
    goto lab30 ;
    endfilereading () ;
    promptfilename ( 840 , 344 ) ;
  } 
  lab30: curinput .namefield = amakenamestring ( inputfile [curinput 
  .indexfield ]) ;
  sourcefilenamestack [inopen ]= curinput .namefield ;
  fullsourcefilenamestack [inopen ]= makefullnamestring () ;
  if ( curinput .namefield == strptr - 1 ) 
  {
    tempstr = searchstring ( curinput .namefield ) ;
    if ( tempstr > 0 ) 
    {
      curinput .namefield = tempstr ;
      {
	decr ( strptr ) ;
	poolptr = strstart [strptr ];
      } 
    } 
  } 
  if ( jobname == 0 ) 
  {
    jobname = getjobname ( curname ) ;
    openlogfile () ;
  } 
  if ( termoffset + ( strstart [fullsourcefilenamestack [inopen ]+ 1 ]- 
  strstart [fullsourcefilenamestack [inopen ]]) > maxprintline - 2 ) 
  println () ;
  else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
  printchar ( 32 ) ;
  printchar ( 40 ) ;
  incr ( openparens ) ;
  slowprint ( fullsourcefilenamestack [inopen ]) ;
  fflush ( stdout ) ;
  curinput .statefield = 61 ;
  synctexstartinput () ;
  {
    line = 1 ;
    if ( inputln ( inputfile [curinput .indexfield ], false ) ) 
    ;
    firmuptheline () ;
    if ( ( eqtb [28511 ].cint < 0 ) || ( eqtb [28511 ].cint > 255 ) ) 
    decr ( curinput .limitfield ) ;
    else buffer [curinput .limitfield ]= eqtb [28511 ].cint ;
    first = curinput .limitfield + 1 ;
    curinput .locfield = curinput .startfield ;
  } 
} 
integer 
zeffectivechar ( boolean errp , internalfontnumber f , quarterword c ) 
{
  /* 40 */ register integer Result; effectivechar_regmem 
  integer basec  ;
  integer result  ;
  result = c ;
  if ( ! mltexenabledp ) 
  goto lab40 ;
  if ( fontec [f ]>= c ) {
      
    if ( fontbc [f ]<= c ) {
	
      if ( ( fontinfo [charbase [f ]+ c ].qqqq .b0 > 0 ) ) 
      goto lab40 ;
    } 
  } 
  if ( c >= eqtb [28522 ].cint ) {
      
    if ( c <= eqtb [28523 ].cint ) {
	
      if ( ( eqtb [28206 + c ].hh .v.RH > 0 ) ) 
      {
	basec = ( eqtb [28206 + c ].hh .v.RH % 256 ) ;
	result = basec ;
	if ( ! errp ) 
	goto lab40 ;
	if ( fontec [f ]>= basec ) {
	    
	  if ( fontbc [f ]<= basec ) {
	      
	    if ( ( fontinfo [charbase [f ]+ basec ].qqqq .b0 > 0 ) ) 
	    goto lab40 ;
	  } 
	} 
      } 
    } 
  } 
  if ( errp ) 
  {
    begindiagnostic () ;
    printnl ( 880 ) ;
    print ( 1396 ) ;
    print ( c ) ;
    print ( 881 ) ;
    slowprint ( fontname [f ]) ;
    printchar ( 33 ) ;
    enddiagnostic ( false ) ;
    result = fontbc [f ];
  } 
  lab40: Result = result ;
  return Result ;
} 
fourquarters 
zeffectivecharinfo ( internalfontnumber f , quarterword c ) 
{
  /* 10 */ register fourquarters Result; effectivecharinfo_regmem 
  fourquarters ci  ;
  integer basec  ;
  if ( ! mltexenabledp ) 
  {
    Result = fontinfo [charbase [f ]+ c ].qqqq ;
    return Result ;
  } 
  if ( fontec [f ]>= c ) {
      
    if ( fontbc [f ]<= c ) 
    {
      ci = fontinfo [charbase [f ]+ c ].qqqq ;
      if ( ( ci .b0 > 0 ) ) 
      {
	Result = ci ;
	return Result ;
      } 
    } 
  } 
  if ( c >= eqtb [28522 ].cint ) {
      
    if ( c <= eqtb [28523 ].cint ) {
	
      if ( ( eqtb [28206 + c ].hh .v.RH > 0 ) ) 
      {
	basec = ( eqtb [28206 + c ].hh .v.RH % 256 ) ;
	if ( fontec [f ]>= basec ) {
	    
	  if ( fontbc [f ]<= basec ) 
	  {
	    ci = fontinfo [charbase [f ]+ basec ].qqqq ;
	    if ( ( ci .b0 > 0 ) ) 
	    {
	      Result = ci ;
	      return Result ;
	    } 
	  } 
	} 
      } 
    } 
  } 
  Result = nullcharacter ;
  return Result ;
} 
internalfontnumber 
zreadfontinfo ( halfword u , strnumber nom , strnumber aire , scaled s ) 
{
  /* 30 11 45 */ register internalfontnumber Result; readfontinfo_regmem 
  fontindex k  ;
  unsigned char jfmflag  ;
  halfword nt  ;
  KANJIcode cx  ;
  boolean nametoolong  ;
  boolean fileopened  ;
  halfword lf, lh, bc, ec, nw, nh, nd, ni, nl, nk, ne, np  ;
  internalfontnumber f  ;
  internalfontnumber g  ;
  eightbits a, b, c, d  ;
  fourquarters qw  ;
  scaled sw  ;
  integer bchlabel  ;
  short bchar  ;
  scaled z  ;
  integer alpha  ;
  unsigned char beta  ;
  g = 0 ;
  fileopened = false ;
  nametoolong = ( ( strstart [nom + 1 ]- strstart [nom ]) > 255 ) || ( ( 
  strstart [aire + 1 ]- strstart [aire ]) > 255 ) ;
  if ( nametoolong ) 
  goto lab11 ;
  packfilename ( nom , aire , 344 ) ;
  if ( ! bopenin ( tfmfile ) ) 
  goto lab11 ;
  fileopened = true ;
  {
    {
      lf = tfmtemp ;
      if ( lf > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      lf = lf * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      lh = tfmtemp ;
      if ( lh > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      lh = lh * 256 + tfmtemp ;
    } 
    if ( lf == 11 ) 
    {
      jfmflag = 4 ;
      nt = lh ;
      tfmtemp = getc ( tfmfile ) ;
      {
	lf = tfmtemp ;
	if ( lf > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	lf = lf * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	lh = tfmtemp ;
	if ( lh > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	lh = lh * 256 + tfmtemp ;
      } 
    } 
    else if ( lf == 9 ) 
    {
      jfmflag = 3 ;
      nt = lh ;
      tfmtemp = getc ( tfmfile ) ;
      {
	lf = tfmtemp ;
	if ( lf > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	lf = lf * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	lh = tfmtemp ;
	if ( lh > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	lh = lh * 256 + tfmtemp ;
      } 
    } 
    else {
	
      jfmflag = 0 ;
      nt = 0 ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      bc = tfmtemp ;
      if ( bc > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      bc = bc * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      ec = tfmtemp ;
      if ( ec > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      ec = ec * 256 + tfmtemp ;
    } 
    if ( ( bc > ec + 1 ) || ( ec > 255 ) ) 
    goto lab11 ;
    if ( bc > 255 ) 
    {
      bc = 1 ;
      ec = 0 ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nw = tfmtemp ;
      if ( nw > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nw = nw * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nh = tfmtemp ;
      if ( nh > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nh = nh * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nd = tfmtemp ;
      if ( nd > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nd = nd * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      ni = tfmtemp ;
      if ( ni > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      ni = ni * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nl = tfmtemp ;
      if ( nl > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nl = nl * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nk = tfmtemp ;
      if ( nk > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nk = nk * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      ne = tfmtemp ;
      if ( ne > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      ne = ne * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      np = tfmtemp ;
      if ( np > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      np = np * 256 + tfmtemp ;
    } 
    if ( jfmflag != 0 ) 
    {
      if ( lf != 7 + lh + nt + ( ec - bc + 1 ) + nw + nh + nd + ni + nl + nk + 
      ne + np ) 
      goto lab11 ;
    } 
    else {
	
      if ( lf != 6 + lh + ( ec - bc + 1 ) + nw + nh + nd + ni + nl + nk + ne + 
      np ) 
      goto lab11 ;
    } 
    if ( ( nw == 0 ) || ( nh == 0 ) || ( nd == 0 ) || ( ni == 0 ) ) 
    goto lab11 ;
  } 
  if ( jfmflag != 0 ) 
  lf = lf - 7 - lh ;
  else lf = lf - 6 - lh ;
  if ( np < 7 ) 
  lf = lf + 7 - np ;
  if ( ( fontptr == fontmax ) || ( fmemptr + lf > fontmemsize ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 857 ) ;
    } 
    sprintcs ( u ) ;
    printchar ( 61 ) ;
    printfilename ( nom , aire , 344 ) ;
    if ( s >= 0 ) 
    {
      print ( 790 ) ;
      printscaled ( s ) ;
      print ( 416 ) ;
    } 
    else if ( s != -1000 ) 
    {
      print ( 858 ) ;
      printint ( - (integer) s ) ;
    } 
    print ( 867 ) ;
    {
      helpptr = 4 ;
      helpline [3 ]= 868 ;
      helpline [2 ]= 869 ;
      helpline [1 ]= 870 ;
      helpline [0 ]= 871 ;
    } 
    error () ;
    goto lab30 ;
  } 
  f = fontptr + 1 ;
  fontdir [f ]= jfmflag ;
  fontnumext [f ]= nt ;
  ctypebase [f ]= fmemptr ;
  charbase [f ]= ctypebase [f ]+ nt - bc ;
  widthbase [f ]= charbase [f ]+ ec + 1 ;
  heightbase [f ]= widthbase [f ]+ nw ;
  depthbase [f ]= heightbase [f ]+ nh ;
  italicbase [f ]= depthbase [f ]+ nd ;
  ligkernbase [f ]= italicbase [f ]+ ni ;
  kernbase [f ]= ligkernbase [f ]+ nl - 256 * ( 128 ) ;
  extenbase [f ]= kernbase [f ]+ 256 * ( 128 ) + nk ;
  parambase [f ]= extenbase [f ]+ ne ;
  {
    if ( lh < 2 ) 
    goto lab11 ;
    {
      tfmtemp = getc ( tfmfile ) ;
      a = tfmtemp ;
      qw .b0 = a ;
      tfmtemp = getc ( tfmfile ) ;
      b = tfmtemp ;
      qw .b1 = b ;
      tfmtemp = getc ( tfmfile ) ;
      c = tfmtemp ;
      qw .b2 = c ;
      tfmtemp = getc ( tfmfile ) ;
      d = tfmtemp ;
      qw .b3 = d ;
      fontcheck [f ]= qw ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      z = tfmtemp ;
      if ( z > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      z = z * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    z = z * 256 + tfmtemp ;
    tfmtemp = getc ( tfmfile ) ;
    z = ( z * 16 ) + ( tfmtemp / 16 ) ;
    if ( z < 65536L ) 
    goto lab11 ;
    while ( lh > 2 ) {
	
      tfmtemp = getc ( tfmfile ) ;
      tfmtemp = getc ( tfmfile ) ;
      tfmtemp = getc ( tfmfile ) ;
      tfmtemp = getc ( tfmfile ) ;
      decr ( lh ) ;
    } 
    fontdsize [f ]= z ;
    if ( s != -1000 ) {
	
      if ( s >= 0 ) 
      z = s ;
      else z = xnoverd ( z , - (integer) s , 1000 ) ;
    } 
    fontsize [f ]= z ;
  } 
  if ( jfmflag != 0 ) 
  {register integer for_end; k = ctypebase [f ];for_end = ctypebase [f ]
  + nt - 1 ; if ( k <= for_end) do 
    {
      tfmtemp = getc ( tfmfile ) ;
      {
	cx = tfmtemp ;
	if ( cx > 255 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	cx = cx * 256 + tfmtemp ;
      } 
      fontinfo [k ].hh .v.RH = cx ;
      tfmtemp = getc ( tfmfile ) ;
      {
	cx = tfmtemp ;
	if ( cx > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	cx = cx * 256 + tfmtemp ;
      } 
      fontinfo [k ].hh .lhfield = cx ;
    } 
  while ( k++ < for_end ) ;} 
  {register integer for_end; k = charbase [f ]+ bc ;for_end = widthbase [
  f ]- 1 ; if ( k <= for_end) do 
    {
      {
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	qw .b0 = a ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	qw .b1 = b ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	qw .b2 = c ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	qw .b3 = d ;
	fontinfo [k ].qqqq = qw ;
      } 
      if ( ( a >= nw ) || ( b / 16 >= nh ) || ( b % 16 >= nd ) || ( c / 4 >= 
      ni ) ) 
      goto lab11 ;
      switch ( c % 4 ) 
      {case 1 : 
	if ( d >= nl ) 
	goto lab11 ;
	break ;
      case 3 : 
	if ( d >= ne ) 
	goto lab11 ;
	break ;
      case 2 : 
	{
	  {
	    if ( ( d < bc ) || ( d > ec ) ) 
	    goto lab11 ;
	  } 
	  while ( d < k - charbase [f ]) {
	      
	    qw = fontinfo [charbase [f ]+ d ].qqqq ;
	    if ( ( ( qw .b2 ) % 4 ) != 2 ) 
	    goto lab45 ;
	    d = qw .b3 ;
	  } 
	  if ( d == k - charbase [f ]) 
	  goto lab11 ;
	  lab45: ;
	} 
	break ;
	default: 
	;
	break ;
      } 
    } 
  while ( k++ < for_end ) ;} 
  {
    {
      alpha = 16 ;
      while ( z >= 8388608L ) {
	  
	z = z / 2 ;
	alpha = alpha + alpha ;
      } 
      beta = 256 / alpha ;
      alpha = alpha * z ;
    } 
    {register integer for_end; k = widthbase [f ];for_end = ligkernbase [
    f ]- 1 ; if ( k <= for_end) do 
      {
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
	beta ;
	if ( a == 0 ) 
	fontinfo [k ].cint = sw ;
	else if ( a == 255 ) 
	fontinfo [k ].cint = sw - alpha ;
	else goto lab11 ;
      } 
    while ( k++ < for_end ) ;} 
    if ( fontinfo [widthbase [f ]].cint != 0 ) 
    goto lab11 ;
    if ( fontinfo [heightbase [f ]].cint != 0 ) 
    goto lab11 ;
    if ( fontinfo [depthbase [f ]].cint != 0 ) 
    goto lab11 ;
    if ( fontinfo [italicbase [f ]].cint != 0 ) 
    goto lab11 ;
  } 
  bchlabel = 32767 ;
  bchar = 256 ;
  if ( nl > 0 ) 
  {
    {register integer for_end; k = ligkernbase [f ];for_end = kernbase [f 
    ]+ 256 * ( 128 ) - 1 ; if ( k <= for_end) do 
      {
	{
	  tfmtemp = getc ( tfmfile ) ;
	  a = tfmtemp ;
	  qw .b0 = a ;
	  tfmtemp = getc ( tfmfile ) ;
	  b = tfmtemp ;
	  qw .b1 = b ;
	  tfmtemp = getc ( tfmfile ) ;
	  c = tfmtemp ;
	  qw .b2 = c ;
	  tfmtemp = getc ( tfmfile ) ;
	  d = tfmtemp ;
	  qw .b3 = d ;
	  fontinfo [k ].qqqq = qw ;
	} 
	if ( a > 128 ) 
	{
	  if ( 256 * c + d >= nl ) 
	  goto lab11 ;
	  if ( a == 255 ) {
	      
	    if ( k == ligkernbase [f ]) 
	    bchar = b ;
	  } 
	} 
	else {
	    
	  if ( b != bchar ) 
	  {
	    {
	      if ( ( b < bc ) || ( b > ec ) ) 
	      goto lab11 ;
	    } 
	    qw = fontinfo [charbase [f ]+ b ].qqqq ;
	    if ( ! ( qw .b0 > 0 ) ) 
	    goto lab11 ;
	  } 
	  if ( c < 128 ) 
	  {
	    if ( jfmflag != 0 ) 
	    {
	      if ( d >= ne ) 
	      goto lab11 ;
	    } 
	    else {
		
	      {
		if ( ( d < bc ) || ( d > ec ) ) 
		goto lab11 ;
	      } 
	      qw = fontinfo [charbase [f ]+ d ].qqqq ;
	      if ( ! ( qw .b0 > 0 ) ) 
	      goto lab11 ;
	    } 
	  } 
	  else if ( 256 * ( c - 128 ) + d >= nk ) 
	  goto lab11 ;
	  if ( a < 128 ) {
	      
	    if ( k - ligkernbase [f ]+ a + 1 >= nl ) 
	    goto lab11 ;
	  } 
	} 
      } 
    while ( k++ < for_end ) ;} 
    if ( a == 255 ) 
    bchlabel = 256 * c + d ;
  } 
  {register integer for_end; k = kernbase [f ]+ 256 * ( 128 ) ;for_end = 
  extenbase [f ]- 1 ; if ( k <= for_end) do 
    {
      tfmtemp = getc ( tfmfile ) ;
      a = tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      b = tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      c = tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      d = tfmtemp ;
      sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
      beta ;
      if ( a == 0 ) 
      fontinfo [k ].cint = sw ;
      else if ( a == 255 ) 
      fontinfo [k ].cint = sw - alpha ;
      else goto lab11 ;
    } 
  while ( k++ < for_end ) ;} 
  if ( jfmflag != 0 ) 
  {register integer for_end; k = extenbase [f ];for_end = parambase [f ]
  - 1 ; if ( k <= for_end) do 
    {
      tfmtemp = getc ( tfmfile ) ;
      a = tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      b = tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      c = tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      d = tfmtemp ;
      sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
      beta ;
      if ( a == 0 ) 
      fontinfo [k ].cint = sw ;
      else if ( a == 255 ) 
      fontinfo [k ].cint = sw - alpha ;
      else goto lab11 ;
    } 
  while ( k++ < for_end ) ;} 
  else {
      register integer for_end; k = extenbase [f ];for_end = parambase [
  f ]- 1 ; if ( k <= for_end) do 
    {
      {
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	qw .b0 = a ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	qw .b1 = b ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	qw .b2 = c ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	qw .b3 = d ;
	fontinfo [k ].qqqq = qw ;
      } 
      if ( a != 0 ) 
      {
	{
	  if ( ( a < bc ) || ( a > ec ) ) 
	  goto lab11 ;
	} 
	qw = fontinfo [charbase [f ]+ a ].qqqq ;
	if ( ! ( qw .b0 > 0 ) ) 
	goto lab11 ;
      } 
      if ( b != 0 ) 
      {
	{
	  if ( ( b < bc ) || ( b > ec ) ) 
	  goto lab11 ;
	} 
	qw = fontinfo [charbase [f ]+ b ].qqqq ;
	if ( ! ( qw .b0 > 0 ) ) 
	goto lab11 ;
      } 
      if ( c != 0 ) 
      {
	{
	  if ( ( c < bc ) || ( c > ec ) ) 
	  goto lab11 ;
	} 
	qw = fontinfo [charbase [f ]+ c ].qqqq ;
	if ( ! ( qw .b0 > 0 ) ) 
	goto lab11 ;
      } 
      {
	{
	  if ( ( d < bc ) || ( d > ec ) ) 
	  goto lab11 ;
	} 
	qw = fontinfo [charbase [f ]+ d ].qqqq ;
	if ( ! ( qw .b0 > 0 ) ) 
	goto lab11 ;
      } 
    } 
  while ( k++ < for_end ) ;} 
  {
    {register integer for_end; k = 1 ;for_end = np ; if ( k <= for_end) do 
      if ( k == 1 ) 
      {
	tfmtemp = getc ( tfmfile ) ;
	sw = tfmtemp ;
	if ( sw > 127 ) 
	sw = sw - 256 ;
	tfmtemp = getc ( tfmfile ) ;
	sw = sw * 256 + tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	sw = sw * 256 + tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	fontinfo [parambase [f ]].cint = ( sw * 16 ) + ( tfmtemp / 16 ) ;
      } 
      else {
	  
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
	beta ;
	if ( a == 0 ) 
	fontinfo [parambase [f ]+ k - 1 ].cint = sw ;
	else if ( a == 255 ) 
	fontinfo [parambase [f ]+ k - 1 ].cint = sw - alpha ;
	else goto lab11 ;
      } 
    while ( k++ < for_end ) ;} 
    if ( feof ( tfmfile ) ) 
    goto lab11 ;
    {register integer for_end; k = np + 1 ;for_end = 7 ; if ( k <= for_end) 
    do 
      fontinfo [parambase [f ]+ k - 1 ].cint = 0 ;
    while ( k++ < for_end ) ;} 
  } 
  if ( np >= 7 ) 
  fontparams [f ]= np ;
  else fontparams [f ]= 7 ;
  hyphenchar [f ]= eqtb [28509 ].cint ;
  skewchar [f ]= eqtb [28510 ].cint ;
  if ( bchlabel < nl ) 
  bcharlabel [f ]= bchlabel + ligkernbase [f ];
  else bcharlabel [f ]= 0 ;
  fontbchar [f ]= bchar ;
  fontfalsebchar [f ]= bchar ;
  if ( bchar <= ec ) {
      
    if ( bchar >= bc ) 
    {
      qw = fontinfo [charbase [f ]+ bchar ].qqqq ;
      if ( ( qw .b0 > 0 ) ) 
      fontfalsebchar [f ]= 256 ;
    } 
  } 
  fontname [f ]= nom ;
  fontarea [f ]= aire ;
  fontbc [f ]= bc ;
  fontec [f ]= ec ;
  fontglue [f ]= -1073741823L ;
  ctypebase [f ]= ctypebase [f ];
  charbase [f ]= charbase [f ];
  widthbase [f ]= widthbase [f ];
  ligkernbase [f ]= ligkernbase [f ];
  kernbase [f ]= kernbase [f ];
  extenbase [f ]= extenbase [f ];
  decr ( parambase [f ]) ;
  fmemptr = fmemptr + lf ;
  fontptr = f ;
  g = f ;
  goto lab30 ;
  lab11: {
      
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 857 ) ;
  } 
  sprintcs ( u ) ;
  printchar ( 61 ) ;
  printfilename ( nom , aire , 344 ) ;
  if ( s >= 0 ) 
  {
    print ( 790 ) ;
    printscaled ( s ) ;
    print ( 416 ) ;
  } 
  else if ( s != -1000 ) 
  {
    print ( 858 ) ;
    printint ( - (integer) s ) ;
  } 
  if ( fileopened ) 
  print ( 859 ) ;
  else if ( nametoolong ) 
  print ( 860 ) ;
  else print ( 861 ) ;
  {
    helpptr = 5 ;
    helpline [4 ]= 862 ;
    helpline [3 ]= 863 ;
    helpline [2 ]= 864 ;
    helpline [1 ]= 865 ;
    helpline [0 ]= 866 ;
  } 
  error () ;
  lab30: if ( fileopened ) 
  bclose ( tfmfile ) ;
  Result = g ;
  return Result ;
} 
void 
zcharwarning ( internalfontnumber f , eightbits c ) 
{
  charwarning_regmem 
  unsigned char l  ;
  if ( eqtb [28497 ].cint > 0 ) 
  {
    begindiagnostic () ;
    printnl ( 880 ) ;
    if ( ( c < 32 ) || ( c > 126 ) ) 
    {
      printchar ( 94 ) ;
      printchar ( 94 ) ;
      if ( c < 64 ) 
      printchar ( c + 64 ) ;
      else if ( c < 128 ) 
      printchar ( c - 64 ) ;
      else {
	  
	l = c / 16 ;
	if ( l < 10 ) 
	printchar ( l + 48 ) ;
	else printchar ( l + 87 ) ;
	l = c % 16 ;
	if ( l < 10 ) 
	printchar ( l + 48 ) ;
	else printchar ( l + 87 ) ;
      } 
    } 
    else print ( c ) ;
    print ( 881 ) ;
    slowprint ( fontname [f ]) ;
    printchar ( 33 ) ;
    enddiagnostic ( false ) ;
  } 
} 
halfword 
znewcharacter ( internalfontnumber f , eightbits c ) 
{
  /* 10 */ register halfword Result; newcharacter_regmem 
  halfword p  ;
  quarterword ec  ;
  ec = effectivechar ( false , f , c ) ;
  if ( fontbc [f ]<= ec ) {
      
    if ( fontec [f ]>= ec ) {
	
      if ( ( fontinfo [charbase [f ]+ ec ].qqqq .b0 > 0 ) ) 
      {
	p = getavail () ;
	mem [p ].hh.b0 = f ;
	mem [p ].hh.b1 = c ;
	Result = p ;
	return Result ;
      } 
    } 
  } 
  charwarning ( f , c ) ;
  Result = -1073741823L ;
  return Result ;
} 
void 
dviswap ( void ) 
{
  dviswap_regmem 
  if ( dviptr > ( 2147483647L - dvioffset ) ) 
  {
    curs = -2 ;
    fatalerror ( 882 ) ;
  } 
  if ( dvilimit == dvibufsize ) 
  {
    writedvi ( 0 , halfbuf - 1 ) ;
    dvilimit = halfbuf ;
    dvioffset = dvioffset + dvibufsize ;
    dviptr = 0 ;
  } 
  else {
      
    writedvi ( halfbuf , dvibufsize - 1 ) ;
    dvilimit = dvibufsize ;
  } 
  dvigone = dvigone + halfbuf ;
} 
void 
zdvifour ( integer x ) 
{
  dvifour_regmem 
  if ( x >= 0 ) 
  {
    dvibuf [dviptr ]= x / 16777216L ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  else {
      
    x = x + 1073741824L ;
    x = x + 1073741824L ;
    {
      dvibuf [dviptr ]= ( x / 16777216L ) + 128 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  x = x % 16777216L ;
  {
    dvibuf [dviptr ]= x / 65536L ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  x = x % 65536L ;
  {
    dvibuf [dviptr ]= x / 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= x % 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
} 
void 
zdvipop ( integer l ) 
{
  dvipop_regmem 
  if ( ( l == dvioffset + dviptr ) && ( dviptr > 0 ) ) 
  decr ( dviptr ) ;
  else {
      
    dvibuf [dviptr ]= 142 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
} 
void 
zdvifontdef ( internalfontnumber f ) 
{
  dvifontdef_regmem 
  poolpointer k  ;
  if ( f <= 256 ) 
  {
    {
      dvibuf [dviptr ]= 243 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= f - 1 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  else {
      
    {
      dvibuf [dviptr ]= 244 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( f - 1 ) / 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( f - 1 ) % 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  {
    dvibuf [dviptr ]= fontcheck [f ].b0 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= fontcheck [f ].b1 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= fontcheck [f ].b2 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= fontcheck [f ].b3 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  dvifour ( fontsize [f ]) ;
  dvifour ( fontdsize [f ]) ;
  {
    dvibuf [dviptr ]= ( strstart [fontarea [f ]+ 1 ]- strstart [
    fontarea [f ]]) ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= ( strstart [fontname [f ]+ 1 ]- strstart [
    fontname [f ]]) ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {register integer for_end; k = strstart [fontarea [f ]];for_end = 
  strstart [fontarea [f ]+ 1 ]- 1 ; if ( k <= for_end) do 
    {
      dvibuf [dviptr ]= strpool [k ];
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  while ( k++ < for_end ) ;} 
  {register integer for_end; k = strstart [fontname [f ]];for_end = 
  strstart [fontname [f ]+ 1 ]- 1 ; if ( k <= for_end) do 
    {
      dvibuf [dviptr ]= strpool [k ];
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  while ( k++ < for_end ) ;} 
} 
void 
zmovement ( scaled w , eightbits o ) 
{
  /* 10 40 45 2 1 */ movement_regmem 
  smallnumber mstate  ;
  halfword p, q  ;
  integer k  ;
  q = getnode ( 3 ) ;
  mem [q + 1 ].cint = w ;
  mem [q + 2 ].cint = dvioffset + dviptr ;
  if ( o == 157 ) 
  {
    mem [q ].hh .v.RH = downptr ;
    downptr = q ;
  } 
  else {
      
    mem [q ].hh .v.RH = rightptr ;
    rightptr = q ;
  } 
  p = mem [q ].hh .v.RH ;
  mstate = 0 ;
  while ( p != -1073741823L ) {
      
    if ( mem [p + 1 ].cint == w ) 
    switch ( mstate + mem [p ].hh .v.LH ) 
    {case 3 : 
    case 4 : 
    case 15 : 
    case 16 : 
      if ( mem [p + 2 ].cint < dvigone ) 
      goto lab45 ;
      else {
	  
	k = mem [p + 2 ].cint - dvioffset ;
	if ( k < 0 ) 
	k = k + dvibufsize ;
	dvibuf [k ]= dvibuf [k ]+ 5 ;
	mem [p ].hh .v.LH = 1 ;
	goto lab40 ;
      } 
      break ;
    case 5 : 
    case 9 : 
    case 11 : 
      if ( mem [p + 2 ].cint < dvigone ) 
      goto lab45 ;
      else {
	  
	k = mem [p + 2 ].cint - dvioffset ;
	if ( k < 0 ) 
	k = k + dvibufsize ;
	dvibuf [k ]= dvibuf [k ]+ 10 ;
	mem [p ].hh .v.LH = 2 ;
	goto lab40 ;
      } 
      break ;
    case 1 : 
    case 2 : 
    case 8 : 
    case 13 : 
      goto lab40 ;
      break ;
      default: 
      ;
      break ;
    } 
    else switch ( mstate + mem [p ].hh .v.LH ) 
    {case 1 : 
      mstate = 6 ;
      break ;
    case 2 : 
      mstate = 12 ;
      break ;
    case 8 : 
    case 13 : 
      goto lab45 ;
      break ;
      default: 
      ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  lab45: ;
  mem [q ].hh .v.LH = 3 ;
  if ( abs ( w ) >= 8388608L ) 
  {
    {
      dvibuf [dviptr ]= o + 3 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( w ) ;
    return ;
  } 
  if ( abs ( w ) >= 32768L ) 
  {
    {
      dvibuf [dviptr ]= o + 2 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    if ( w < 0 ) 
    w = w + 16777216L ;
    {
      dvibuf [dviptr ]= w / 65536L ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    w = w % 65536L ;
    goto lab2 ;
  } 
  if ( abs ( w ) >= 128 ) 
  {
    {
      dvibuf [dviptr ]= o + 1 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    if ( w < 0 ) 
    w = w + 65536L ;
    goto lab2 ;
  } 
  {
    dvibuf [dviptr ]= o ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  if ( w < 0 ) 
  w = w + 256 ;
  goto lab1 ;
  lab2: {
      
    dvibuf [dviptr ]= w / 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  lab1: {
      
    dvibuf [dviptr ]= w % 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  return ;
  lab40: mem [q ].hh .v.LH = mem [p ].hh .v.LH ;
  if ( mem [q ].hh .v.LH == 1 ) 
  {
    {
      dvibuf [dviptr ]= o + 4 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    while ( mem [q ].hh .v.RH != p ) {
	
      q = mem [q ].hh .v.RH ;
      switch ( mem [q ].hh .v.LH ) 
      {case 3 : 
	mem [q ].hh .v.LH = 5 ;
	break ;
      case 4 : 
	mem [q ].hh .v.LH = 6 ;
	break ;
	default: 
	;
	break ;
      } 
    } 
  } 
  else {
      
    {
      dvibuf [dviptr ]= o + 9 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    while ( mem [q ].hh .v.RH != p ) {
	
      q = mem [q ].hh .v.RH ;
      switch ( mem [q ].hh .v.LH ) 
      {case 3 : 
	mem [q ].hh .v.LH = 4 ;
	break ;
      case 5 : 
	mem [q ].hh .v.LH = 6 ;
	break ;
	default: 
	;
	break ;
      } 
    } 
  } 
} 
void 
zprunemovements ( integer l ) 
{
  /* 30 10 */ prunemovements_regmem 
  halfword p  ;
  while ( downptr != -1073741823L ) {
      
    if ( mem [downptr + 2 ].cint < l ) 
    goto lab30 ;
    p = downptr ;
    downptr = mem [p ].hh .v.RH ;
    freenode ( p , 3 ) ;
  } 
  lab30: while ( rightptr != -1073741823L ) {
      
    if ( mem [rightptr + 2 ].cint < l ) 
    return ;
    p = rightptr ;
    rightptr = mem [p ].hh .v.RH ;
    freenode ( p , 3 ) ;
  } 
} 
void 
zspecialout ( halfword p ) 
{
  specialout_regmem 
  unsigned char oldsetting  ;
  poolpointer k  ;
  if ( curh != dvih ) 
  {
    movement ( curh - dvih , 143 ) ;
    dvih = curh ;
  } 
  if ( curv != dviv ) 
  {
    movement ( curv - dviv , 157 ) ;
    dviv = curv ;
  } 
  oldsetting = selector ;
  selector = 21 ;
  showtokenlist ( mem [mem [p + 1 ].hh .v.RH ].hh .v.RH , -1073741823L , 
  poolsize - poolptr ) ;
  selector = oldsetting ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 258 , poolsize - initpoolptr ) ;
  } 
  if ( ( poolptr - strstart [strptr ]) < 256 ) 
  {
    {
      dvibuf [dviptr ]= 239 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( poolptr - strstart [strptr ]) ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  else {
      
    {
      dvibuf [dviptr ]= 242 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( ( poolptr - strstart [strptr ]) ) ;
  } 
  {register integer for_end; k = strstart [strptr ];for_end = poolptr - 1 
  ; if ( k <= for_end) do 
    {
      dvibuf [dviptr ]= strpool [k ];
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  while ( k++ < for_end ) ;} 
  poolptr = strstart [strptr ];
} 
void 
zwriteout ( halfword p ) 
{
  writeout_regmem 
  unsigned char oldsetting  ;
  integer oldmode  ;
  smallnumber j  ;
  halfword q, r  ;
  integer d  ;
  boolean clobbered  ;
  integer runsystemret  ;
  q = getavail () ;
  mem [q ].hh .v.LH = 637 ;
  r = getavail () ;
  mem [q ].hh .v.RH = r ;
  mem [r ].hh .v.LH = 536886433L ;
  begintokenlist ( q , 4 ) ;
  begintokenlist ( mem [p + 1 ].hh .v.RH , 15 ) ;
  q = getavail () ;
  mem [q ].hh .v.LH = 379 ;
  begintokenlist ( q , 4 ) ;
  oldmode = curlist .modefield ;
  curlist .modefield = 0 ;
  curcs = writeloc ;
  q = scantoks ( false , true ) ;
  gettoken () ;
  if ( curtok != 536886433L ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1390 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 1391 ;
      helpline [0 ]= 1071 ;
    } 
    error () ;
    do {
	gettoken () ;
    } while ( ! ( curtok == 536886433L ) ) ;
  } 
  curlist .modefield = oldmode ;
  endtokenlist () ;
  oldsetting = selector ;
  j = mem [p + 1 ].hh .v.LH ;
  if ( j == 18 ) 
  selector = 21 ;
  else if ( writeopen [j ]) 
  selector = j ;
  else {
      
    if ( ( j == 17 ) && ( selector == 19 ) ) 
    selector = 18 ;
    printnl ( 344 ) ;
  } 
  tokenshow ( defref ) ;
  println () ;
  flushlist ( defref ) ;
  if ( j == 18 ) 
  {
    if ( ( eqtb [28491 ].cint <= 0 ) ) 
    selector = 18 ;
    else selector = 19 ;
    if ( ! logopened ) 
    selector = 17 ;
    printnl ( 1382 ) ;
    {register integer for_end; d = 0 ;for_end = ( poolptr - strstart [
    strptr ]) - 1 ; if ( d <= for_end) do 
      {
	print ( strpool [strstart [strptr ]+ d ]) ;
      } 
    while ( d++ < for_end ) ;} 
    print ( 1383 ) ;
    if ( shellenabledp ) 
    {
      {
	if ( poolptr + 1 > poolsize ) 
	overflow ( 258 , poolsize - initpoolptr ) ;
      } 
      {
	strpool [poolptr ]= 0 ;
	incr ( poolptr ) ;
      } 
      clobbered = false ;
      {register integer for_end; d = 0 ;for_end = ( poolptr - strstart [
      strptr ]) - 1 ; if ( d <= for_end) do 
	{
	  strpool [strstart [strptr ]+ d ]= xchr [strpool [strstart [
	  strptr ]+ d ]];
	  if ( ( strpool [strstart [strptr ]+ d ]== 0 ) && ( d < ( poolptr 
	  - strstart [strptr ]) - 1 ) ) 
	  clobbered = true ;
	} 
      while ( d++ < for_end ) ;} 
      if ( clobbered ) 
      print ( 1384 ) ;
      else {
	  
	runsystemret = runsystem ( conststringcast ( addressof ( strpool [
	strstart [strptr ]]) ) ) ;
	if ( runsystemret == -1 ) 
	print ( 1385 ) ;
	else if ( runsystemret == 0 ) 
	print ( 1386 ) ;
	else if ( runsystemret == 1 ) 
	print ( 1387 ) ;
	else if ( runsystemret == 2 ) 
	print ( 1388 ) ;
      } 
    } 
    else {
	
      print ( 1389 ) ;
    } 
    printchar ( 46 ) ;
    printnl ( 344 ) ;
    println () ;
    poolptr = strstart [strptr ];
  } 
  selector = oldsetting ;
} 
void 
zoutwhat ( halfword p ) 
{
  outwhat_regmem 
  smallnumber j  ;
  unsigned char oldsetting  ;
  switch ( mem [p ].hh.b1 ) 
  {case 0 : 
  case 1 : 
  case 2 : 
    if ( ! doingleaders ) 
    {
      j = mem [p + 1 ].hh .v.LH ;
      if ( mem [p ].hh.b1 == 1 ) 
      writeout ( p ) ;
      else {
	  
	if ( writeopen [j ]) 
	aclose ( writefile [j ]) ;
	if ( mem [p ].hh.b1 == 2 ) 
	writeopen [j ]= false ;
	else if ( j < 16 ) 
	{
	  curname = mem [p + 1 ].hh .v.RH ;
	  curarea = mem [p + 2 ].hh .v.LH ;
	  curext = mem [p + 2 ].hh .v.RH ;
	  if ( curext == 344 ) 
	  curext = 844 ;
	  packfilename ( curname , curarea , curext ) ;
	  while ( ! kpseoutnameok ( stringcast ( nameoffile + 1 ) ) || ! 
	  aopenout ( writefile [j ]) ) promptfilename ( 1393 , 844 ) ;
	  writeopen [j ]= true ;
	  if ( logopened ) 
	  {
	    oldsetting = selector ;
	    if ( ( eqtb [28491 ].cint <= 0 ) ) 
	    selector = 18 ;
	    else selector = 19 ;
	    printnl ( 1394 ) ;
	    printint ( j ) ;
	    print ( 1395 ) ;
	    printfilename ( curname , curarea , curext ) ;
	    print ( 843 ) ;
	    printnl ( 344 ) ;
	    println () ;
	    selector = oldsetting ;
	  } 
	} 
      } 
    } 
    break ;
  case 3 : 
    specialout ( p ) ;
    break ;
  case 4 : 
    ;
    break ;
    default: 
    confusion ( 1392 ) ;
    break ;
  } 
} 
void 
synchdir ( void ) 
{
  synchdir_regmem 
  scaled tmp  ;
  switch ( curdirhv ) 
  {case 4 : 
    if ( dvidir != curdirhv ) 
    {
      if ( curh != dvih ) 
      {
	movement ( curh - dvih , 143 ) ;
	dvih = curh ;
      } 
      if ( curv != dviv ) 
      {
	movement ( curv - dviv , 157 ) ;
	dviv = curv ;
      } 
      {
	dvibuf [dviptr ]= 255 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= 0 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dirused = true ;
      switch ( dvidir ) 
      {case 3 : 
	{
	  tmp = curh ;
	  curh = - (integer) curv ;
	  curv = tmp ;
	} 
	break ;
      case 1 : 
	{
	  tmp = curh ;
	  curh = curv ;
	  curv = - (integer) tmp ;
	} 
	break ;
      } 
      dvih = curh ;
      dviv = curv ;
      dvidir = curdirhv ;
    } 
    break ;
  case 3 : 
    if ( dvidir != curdirhv ) 
    {
      if ( curh != dvih ) 
      {
	movement ( curh - dvih , 143 ) ;
	dvih = curh ;
      } 
      if ( curv != dviv ) 
      {
	movement ( curv - dviv , 157 ) ;
	dviv = curv ;
      } 
      {
	dvibuf [dviptr ]= 255 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= 1 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dirused = true ;
      switch ( dvidir ) 
      {case 4 : 
	{
	  tmp = curh ;
	  curh = curv ;
	  curv = - (integer) tmp ;
	} 
	break ;
      case 1 : 
	{
	  curv = - (integer) curv ;
	  curh = - (integer) curh ;
	} 
	break ;
      } 
      dvih = curh ;
      dviv = curv ;
      dvidir = curdirhv ;
    } 
    break ;
  case 1 : 
    if ( dvidir != curdirhv ) 
    {
      if ( curh != dvih ) 
      {
	movement ( curh - dvih , 143 ) ;
	dvih = curh ;
      } 
      if ( curv != dviv ) 
      {
	movement ( curv - dviv , 157 ) ;
	dviv = curv ;
      } 
      {
	dvibuf [dviptr ]= 255 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= 3 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dirused = true ;
      switch ( dvidir ) 
      {case 4 : 
	{
	  tmp = curh ;
	  curh = - (integer) curv ;
	  curv = tmp ;
	} 
	break ;
      case 3 : 
	{
	  curv = - (integer) curv ;
	  curh = - (integer) curh ;
	} 
	break ;
      } 
      dvih = curh ;
      dviv = curv ;
      dvidir = curdirhv ;
    } 
    break ;
    default: 
    confusion ( 1436 ) ;
    break ;
  } 
} 
boolean 
zcheckbox ( halfword boxp ) 
{
  /* 30 */ register boolean Result; checkbox_regmem 
  halfword p  ;
  boolean flag  ;
  flag = false ;
  p = boxp ;
  while ( p != -1073741823L ) {
      
    if ( ( p >= himemmin ) ) 
    do {
	if ( findfirstchar ) 
      {
	firstchar = p ;
	findfirstchar = false ;
      } 
      lastchar = p ;
      flag = true ;
      if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
      p = mem [p ].hh .v.RH ;
      p = mem [p ].hh .v.RH ;
      if ( p == -1073741823L ) 
      goto lab30 ;
    } while ( ! ( ! ( p >= himemmin ) ) ) ;
    switch ( mem [p ].hh.b0 ) 
    {case 0 : 
      {
	flag = true ;
	if ( mem [p + 4 ].cint == 0 ) 
	{
	  if ( checkbox ( mem [p + 5 ].hh .v.RH ) ) 
	  flag = true ;
	} 
	else if ( findfirstchar ) 
	findfirstchar = false ;
	else lastchar = -1073741823L ;
      } 
      break ;
    case 8 : 
      if ( checkbox ( mem [p + 1 ].hh .v.RH ) ) 
      flag = true ;
      break ;
    case 4 : 
    case 5 : 
    case 6 : 
    case 7 : 
    case 10 : 
    case 14 : 
      ;
      break ;
    case 11 : 
      if ( ( mem [p ].hh.b1 == 0 ) || ( mem [p ].hh.b1 == 1 ) ) 
      {
	if ( findfirstchar ) 
	{
	  findfirstchar = false ;
	  firstchar = p ;
	} 
	lastchar = p ;
	flag = true ;
      } 
      else ;
      break ;
    case 13 : 
      if ( mem [p ].hh.b1 == 2 ) 
      {
	p = mem [p ].hh .v.RH ;
	if ( ( p >= himemmin ) ) {
	    
	  if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
	  p = mem [p ].hh .v.RH ;
	} 
	p = mem [mem [p ].hh .v.RH ].hh .v.RH ;
	if ( findfirstchar ) 
	{
	  findfirstchar = false ;
	  firstchar = p ;
	} 
	lastchar = p ;
	flag = true ;
	if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
	p = mem [p ].hh .v.RH ;
      } 
      else {
	  
	flag = true ;
	if ( findfirstchar ) 
	findfirstchar = false ;
	else lastchar = -1073741823L ;
      } 
      break ;
      default: 
      {
	flag = true ;
	if ( findfirstchar ) 
	findfirstchar = false ;
	else lastchar = -1073741823L ;
      } 
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  lab30: Result = flag ;
  return Result ;
} 
void 
zadjusthlist ( halfword p , boolean pf ) 
{
  /* 10 */ adjusthlist_regmem 
  halfword q, s, t, u, v, x, z  ;
  halfword i, k  ;
  halfword a  ;
  unsigned char insertskip  ;
  KANJIcode cx  ;
  ASCIIcode ax  ;
  boolean doins  ;
  if ( mem [p ].hh .v.RH == -1073741823L ) 
  return ;
  if ( eqtb [25633 ].hh .v.RH > 0 ) 
  {
    deleteglueref ( mem [p + 7 ].hh .v.RH ) ;
    mem [p + 7 ].hh .v.RH = eqtb [24542 ].hh .v.RH ;
    incr ( mem [eqtb [24542 ].hh .v.RH ].hh .v.RH ) ;
  } 
  if ( eqtb [25634 ].hh .v.RH > 0 ) 
  {
    deleteglueref ( mem [p + 7 ].hh .v.LH ) ;
    mem [p + 7 ].hh .v.LH = eqtb [24543 ].hh .v.RH ;
    incr ( mem [eqtb [24543 ].hh .v.RH ].hh .v.RH ) ;
  } 
  u = mem [p + 7 ].hh .v.RH ;
  incr ( mem [u ].hh .v.RH ) ;
  s = mem [p + 7 ].hh .v.LH ;
  incr ( mem [s ].hh .v.RH ) ;
  if ( ! ( mem [p ].hh .v.RH >= himemmin ) && ( mem [mem [p ].hh .v.RH ]
  .hh.b0 == 12 ) && ( mem [mem [p ].hh .v.RH ].hh.b1 == 21 ) ) 
  {
    v = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = mem [v ].hh .v.RH ;
    {
      if ( mem [mem [v + 1 ].hh .v.LH ].hh .v.RH == -1073741823L ) 
      freenode ( mem [v + 1 ].hh .v.LH , 4 ) ;
      else decr ( mem [mem [v + 1 ].hh .v.LH ].hh .v.RH ) ;
    } 
    freenode ( v , 2 ) ;
  } 
  i = 0 ;
  insertskip = 0 ;
  p = mem [p ].hh .v.RH ;
  v = p ;
  q = p ;
  while ( p != -1073741823L ) {
      
    if ( ( p >= himemmin ) ) 
    {
      do {
	  if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
	{
	  cx = mem [mem [p ].hh .v.RH ].hh .v.LH % 16777216L ;
	  if ( insertskip == 1 ) 
	  {
	    {
	      x = getinhibitpos ( cx , 1 ) ;
	      if ( x != 1000 ) {
		  
		if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [26660 + x 
		].hh.b0 == 1 ) ) 
		doins = false ;
		else doins = true ;
	      } 
	      else doins = true ;
	    } 
	    if ( doins ) 
	    {
	      z = newglue ( s ) ;
	      mem [z ].hh.b1 = 17 ;
	      mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
	      mem [q ].hh .v.RH = z ;
	      q = z ;
	    } 
	  } 
	  p = mem [p ].hh .v.RH ;
	  insertskip = 2 ;
	} 
	else {
	    
	  ax = mem [p ].hh.b1 ;
	  if ( insertskip == 2 ) 
	  {
	    if ( ( eqtb [26404 + ax ].hh .v.RH % 2 ) == 1 ) 
	    {
	      x = getinhibitpos ( cx , 1 ) ;
	      if ( x != 1000 ) {
		  
		if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [26660 + x 
		].hh.b0 == 2 ) ) 
		doins = false ;
		else doins = true ;
	      } 
	      else doins = true ;
	    } 
	    else doins = false ;
	    if ( doins ) 
	    {
	      z = newglue ( s ) ;
	      mem [z ].hh.b1 = 17 ;
	      mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
	      mem [q ].hh .v.RH = z ;
	      q = z ;
	    } 
	  } 
	  if ( eqtb [26404 + ax ].hh .v.RH >= 2 ) 
	  insertskip = 1 ;
	  else insertskip = 0 ;
	} 
	q = p ;
	p = mem [p ].hh .v.RH ;
	incr ( i ) ;
	if ( ( i > 5 ) && pf ) 
	{
	  if ( ( v >= himemmin ) ) {
	      
	    if ( fontdir [mem [v ].hh.b0 ]!= 0 ) 
	    v = mem [v ].hh .v.RH ;
	  } 
	  v = mem [v ].hh .v.RH ;
	} 
      } while ( ! ( ! ( p >= himemmin ) ) ) ;
    } 
    else {
	
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
	{
	  findfirstchar = true ;
	  firstchar = -1073741823L ;
	  lastchar = -1073741823L ;
	  if ( mem [p + 4 ].cint == 0 ) 
	  {
	    if ( checkbox ( mem [p + 5 ].hh .v.RH ) ) 
	    {
	      if ( firstchar != -1073741823L ) {
		  
		if ( mem [firstchar ].hh.b0 == 11 ) 
		{
		  ax = 48 ;
		  if ( insertskip == 2 ) 
		  {
		    if ( ( eqtb [26404 + ax ].hh .v.RH % 2 ) == 1 ) 
		    {
		      x = getinhibitpos ( cx , 1 ) ;
		      if ( x != 1000 ) {
			  
			if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [
			26660 + x ].hh.b0 == 2 ) ) 
			doins = false ;
			else doins = true ;
		      } 
		      else doins = true ;
		    } 
		    else doins = false ;
		    if ( doins ) 
		    {
		      z = newglue ( s ) ;
		      mem [z ].hh.b1 = 17 ;
		      mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		      mem [q ].hh .v.RH = z ;
		      q = z ;
		    } 
		  } 
		} 
		else if ( fontdir [mem [firstchar ].hh.b0 ]!= 0 ) 
		{
		  cx = mem [mem [firstchar ].hh .v.RH ].hh .v.LH % 
		  16777216L ;
		  if ( insertskip == 1 ) 
		  {
		    {
		      x = getinhibitpos ( cx , 1 ) ;
		      if ( x != 1000 ) {
			  
			if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [
			26660 + x ].hh.b0 == 1 ) ) 
			doins = false ;
			else doins = true ;
		      } 
		      else doins = true ;
		    } 
		    if ( doins ) 
		    {
		      z = newglue ( s ) ;
		      mem [z ].hh.b1 = 17 ;
		      mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		      mem [q ].hh .v.RH = z ;
		      q = z ;
		    } 
		  } 
		  else if ( insertskip == 2 ) 
		  {
		    z = newglue ( u ) ;
		    mem [z ].hh.b1 = 16 ;
		    mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		    mem [q ].hh .v.RH = z ;
		    q = z ;
		  } 
		} 
		else {
		    
		  ax = mem [firstchar ].hh.b1 ;
		  if ( insertskip == 2 ) 
		  {
		    if ( ( eqtb [26404 + ax ].hh .v.RH % 2 ) == 1 ) 
		    {
		      x = getinhibitpos ( cx , 1 ) ;
		      if ( x != 1000 ) {
			  
			if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [
			26660 + x ].hh.b0 == 2 ) ) 
			doins = false ;
			else doins = true ;
		      } 
		      else doins = true ;
		    } 
		    else doins = false ;
		    if ( doins ) 
		    {
		      z = newglue ( s ) ;
		      mem [z ].hh.b1 = 17 ;
		      mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		      mem [q ].hh .v.RH = z ;
		      q = z ;
		    } 
		  } 
		} 
	      } 
	      if ( lastchar != -1073741823L ) 
	      {
		if ( mem [lastchar ].hh.b0 == 11 ) 
		{
		  ax = 48 ;
		  if ( eqtb [26404 + ax ].hh .v.RH >= 2 ) 
		  insertskip = 1 ;
		  else insertskip = 0 ;
		} 
		else if ( fontdir [mem [lastchar ].hh.b0 ]!= 0 ) 
		{
		  insertskip = 2 ;
		  cx = mem [mem [lastchar ].hh .v.RH ].hh .v.LH ;
		  if ( ( mem [p ].hh .v.RH >= himemmin ) && ( fontdir [mem 
		  [mem [p ].hh .v.RH ].hh.b0 ]!= 0 ) ) 
		  {
		    {
		      z = newglue ( u ) ;
		      mem [z ].hh.b1 = 16 ;
		      mem [z ].hh .v.RH = mem [p ].hh .v.RH ;
		      mem [p ].hh .v.RH = z ;
		      p = mem [z ].hh .v.RH ;
		      q = z ;
		    } 
		    p = mem [p ].hh .v.RH ;
		  } 
		} 
		else {
		    
		  ax = mem [lastchar ].hh.b1 ;
		  if ( eqtb [26404 + ax ].hh .v.RH >= 2 ) 
		  insertskip = 1 ;
		  else insertskip = 0 ;
		} 
	      } 
	      else insertskip = 0 ;
	    } 
	    else insertskip = 0 ;
	  } 
	  else insertskip = 0 ;
	} 
	break ;
      case 8 : 
	{
	  t = mem [p + 1 ].hh .v.RH ;
	  if ( ( t >= himemmin ) ) 
	  {
	    ax = mem [t ].hh.b1 ;
	    if ( insertskip == 2 ) 
	    {
	      if ( ( eqtb [26404 + ax ].hh .v.RH % 2 ) == 1 ) 
	      {
		x = getinhibitpos ( cx , 1 ) ;
		if ( x != 1000 ) {
		    
		  if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [26660 + 
		  x ].hh.b0 == 2 ) ) 
		  doins = false ;
		  else doins = true ;
		} 
		else doins = true ;
	      } 
	      else doins = false ;
	      if ( doins ) 
	      {
		z = newglue ( s ) ;
		mem [z ].hh.b1 = 17 ;
		mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		mem [q ].hh .v.RH = z ;
		q = z ;
	      } 
	    } 
	    while ( mem [t ].hh .v.RH != -1073741823L ) t = mem [t ].hh 
	    .v.RH ;
	    if ( ( t >= himemmin ) ) 
	    {
	      ax = mem [t ].hh.b1 ;
	      if ( eqtb [26404 + ax ].hh .v.RH >= 2 ) 
	      insertskip = 1 ;
	      else insertskip = 0 ;
	    } 
	  } 
	} 
	break ;
      case 14 : 
      case 5 : 
	{
	  if ( ( mem [p ].hh .v.RH >= himemmin ) ) 
	  {
	    q = p ;
	    p = mem [p ].hh .v.RH ;
	    if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
	    {
	      cx = mem [mem [p ].hh .v.RH ].hh .v.LH % 16777216L ;
	      if ( insertskip == 1 ) 
	      {
		{
		  x = getinhibitpos ( cx , 1 ) ;
		  if ( x != 1000 ) {
		      
		    if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [26660 
		    + x ].hh.b0 == 1 ) ) 
		    doins = false ;
		    else doins = true ;
		  } 
		  else doins = true ;
		} 
		if ( doins ) 
		{
		  z = newglue ( s ) ;
		  mem [z ].hh.b1 = 17 ;
		  mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		  mem [q ].hh .v.RH = z ;
		  q = z ;
		} 
	      } 
	      else if ( insertskip == 2 ) 
	      {
		z = newglue ( u ) ;
		mem [z ].hh.b1 = 16 ;
		mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		mem [q ].hh .v.RH = z ;
		q = z ;
	      } 
	      p = mem [p ].hh .v.RH ;
	      insertskip = 2 ;
	    } 
	    else {
		
	      ax = mem [p ].hh.b1 ;
	      if ( insertskip == 2 ) 
	      {
		if ( ( eqtb [26404 + ax ].hh .v.RH % 2 ) == 1 ) 
		{
		  x = getinhibitpos ( cx , 1 ) ;
		  if ( x != 1000 ) {
		      
		    if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [26660 
		    + x ].hh.b0 == 2 ) ) 
		    doins = false ;
		    else doins = true ;
		  } 
		  else doins = true ;
		} 
		else doins = false ;
		if ( doins ) 
		{
		  z = newglue ( s ) ;
		  mem [z ].hh.b1 = 17 ;
		  mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		  mem [q ].hh .v.RH = z ;
		  q = z ;
		} 
	      } 
	      if ( eqtb [26404 + ax ].hh .v.RH >= 2 ) 
	      insertskip = 1 ;
	      else insertskip = 0 ;
	    } 
	  } 
	} 
	break ;
      case 13 : 
	if ( mem [p ].hh.b1 == 1 ) 
	insertskip = 0 ;
	else if ( mem [p ].hh.b1 == 2 ) 
	{
	  if ( q == p ) 
	  {
	    t = mem [p ].hh .v.RH ;
	    if ( ( t >= himemmin ) ) {
		
	      if ( fontdir [mem [t ].hh.b0 ]!= 0 ) 
	      t = mem [t ].hh .v.RH ;
	    } 
	    p = mem [mem [t ].hh .v.RH ].hh .v.RH ;
	    if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
	    {
	      p = mem [p ].hh .v.RH ;
	      insertskip = 2 ;
	    } 
	    else insertskip = 1 ;
	  } 
	  else {
	      
	    a = p ;
	    t = mem [p ].hh .v.RH ;
	    if ( ( t >= himemmin ) ) {
		
	      if ( fontdir [mem [t ].hh.b0 ]!= 0 ) 
	      t = mem [t ].hh .v.RH ;
	    } 
	    t = mem [mem [t ].hh .v.RH ].hh .v.RH ;
	    mem [q ].hh .v.RH = t ;
	    p = t ;
	    if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
	    {
	      cx = mem [mem [p ].hh .v.RH ].hh .v.LH % 16777216L ;
	      if ( insertskip == 1 ) 
	      {
		{
		  x = getinhibitpos ( cx , 1 ) ;
		  if ( x != 1000 ) {
		      
		    if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [26660 
		    + x ].hh.b0 == 1 ) ) 
		    doins = false ;
		    else doins = true ;
		  } 
		  else doins = true ;
		} 
		if ( doins ) 
		{
		  z = newglue ( s ) ;
		  mem [z ].hh.b1 = 17 ;
		  mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		  mem [q ].hh .v.RH = z ;
		  q = z ;
		} 
	      } 
	      p = mem [p ].hh .v.RH ;
	      insertskip = 2 ;
	    } 
	    else {
		
	      ax = mem [p ].hh.b1 ;
	      if ( insertskip == 2 ) 
	      {
		if ( ( eqtb [26404 + ax ].hh .v.RH % 2 ) == 1 ) 
		{
		  x = getinhibitpos ( cx , 1 ) ;
		  if ( x != 1000 ) {
		      
		    if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [26660 
		    + x ].hh.b0 == 2 ) ) 
		    doins = false ;
		    else doins = true ;
		  } 
		  else doins = true ;
		} 
		else doins = false ;
		if ( doins ) 
		{
		  z = newglue ( s ) ;
		  mem [z ].hh.b1 = 17 ;
		  mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		  mem [q ].hh .v.RH = z ;
		  q = z ;
		} 
	      } 
	      if ( eqtb [26404 + ax ].hh .v.RH >= 2 ) 
	      insertskip = 1 ;
	      else insertskip = 0 ;
	    } 
	    incr ( i ) ;
	    if ( ( i > 5 ) && pf ) 
	    {
	      if ( ( v >= himemmin ) ) {
		  
		if ( fontdir [mem [v ].hh.b0 ]!= 0 ) 
		v = mem [v ].hh .v.RH ;
	      } 
	      v = mem [v ].hh .v.RH ;
	    } 
	    if ( mem [q ].hh .v.RH != t ) 
	    mem [mem [q ].hh .v.RH ].hh .v.RH = a ;
	    else mem [q ].hh .v.RH = a ;
	  } 
	} 
	break ;
      case 11 : 
	{
	  if ( ( mem [p ].hh.b1 == 0 ) && ( insertskip == 2 ) ) 
	  {
	    ax = 48 ;
	    {
	      if ( ( eqtb [26404 + ax ].hh .v.RH % 2 ) == 1 ) 
	      {
		x = getinhibitpos ( cx , 1 ) ;
		if ( x != 1000 ) {
		    
		  if ( ( eqtb [26660 + x ].hh.b0 == 0 ) || ( eqtb [26660 + 
		  x ].hh.b0 == 2 ) ) 
		  doins = false ;
		  else doins = true ;
		} 
		else doins = true ;
	      } 
	      else doins = false ;
	      if ( doins ) 
	      {
		z = newglue ( s ) ;
		mem [z ].hh.b1 = 17 ;
		mem [z ].hh .v.RH = mem [q ].hh .v.RH ;
		mem [q ].hh .v.RH = z ;
		q = z ;
	      } 
	    } 
	    insertskip = 0 ;
	  } 
	  else if ( mem [p ].hh.b1 == 1 ) 
	  {
	    ax = 48 ;
	    if ( eqtb [26404 + ax ].hh .v.RH >= 2 ) 
	    insertskip = 1 ;
	    else insertskip = 0 ;
	  } 
	  else insertskip = 0 ;
	} 
	break ;
      case 6 : 
      case 7 : 
      case 4 : 
      case 10 : 
	;
	break ;
	default: 
	insertskip = 0 ;
	break ;
      } 
      q = p ;
      p = mem [p ].hh .v.RH ;
    } 
  } 
  if ( ! ( q >= himemmin ) && ( mem [q ].hh.b0 == 12 ) && ( mem [q ].hh.b1 
  == 21 ) ) 
  {
    {
      if ( mem [mem [q + 1 ].hh .v.LH ].hh .v.RH == -1073741823L ) 
      freenode ( mem [q + 1 ].hh .v.LH , 4 ) ;
      else decr ( mem [mem [q + 1 ].hh .v.LH ].hh .v.RH ) ;
    } 
    mem [q + 1 ].hh .v.LH = membot ;
    incr ( mem [membot ].hh .v.RH ) ;
  } 
  deleteglueref ( u ) ;
  deleteglueref ( s ) ;
  if ( ( v != -1073741823L ) && pf && ( i > 5 ) ) 
  {
    q = v ;
    p = mem [v ].hh .v.RH ;
    if ( ( v >= himemmin ) && ( fontdir [mem [v ].hh.b0 ]!= 0 ) ) 
    {
      q = p ;
      p = mem [p ].hh .v.RH ;
    } 
    t = q ;
    s = -1073741823L ;
    while ( ( p != -1073741823L ) ) {
	
      if ( ( p >= himemmin ) ) 
      {
	if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
	{
	  cx = mem [mem [p ].hh .v.RH ].hh .v.LH % 16777216L ;
	  i = mem [mem [p ].hh .v.RH ].hh .v.LH / 16777216L ;
	  k = 0 ;
	  if ( ( i == 16 ) || ( i == 17 ) || ( i == 19 ) ) 
	  {
	    t = q ;
	    s = p ;
	  } 
	  p = mem [p ].hh .v.RH ;
	  q = p ;
	} 
	else {
	    
	  k = k + 1 ;
	  if ( k > 1 ) 
	  {
	    q = p ;
	    s = -1073741823L ;
	  } 
	} 
      } 
      else {
	  
	switch ( mem [p ].hh.b0 ) 
	{case 14 : 
	case 6 : 
	case 7 : 
	case 10 : 
	case 12 : 
	case 13 : 
	case 11 : 
	case 5 : 
	  ;
	  break ;
	  default: 
	  {
	    q = p ;
	    s = -1073741823L ;
	  } 
	  break ;
	} 
      } 
      p = mem [p ].hh .v.RH ;
    } 
    if ( s != -1073741823L ) 
    {
      s = mem [t ].hh .v.RH ;
      if ( ! ( s >= himemmin ) && ( mem [s ].hh.b0 == 14 ) ) 
      mem [s + 1 ].cint = mem [s + 1 ].cint + eqtb [28518 ].cint ;
      else if ( eqtb [28518 ].cint != 0 ) 
      {
	s = newpenalty ( eqtb [28518 ].cint ) ;
	mem [s ].hh.b1 = 1 ;
	mem [s ].hh .v.RH = mem [t ].hh .v.RH ;
	mem [t ].hh .v.RH = s ;
	t = mem [s ].hh .v.RH ;
	while ( ( ! ( t >= himemmin ) ) ) {
	    
	  if ( ( mem [t ].hh.b0 == 12 ) || ( mem [t ].hh.b0 == 13 ) ) 
	  return ;
	  t = mem [t ].hh .v.RH ;
	} 
	z = newglue ( u ) ;
	mem [z ].hh.b1 = 16 ;
	mem [z ].hh .v.RH = mem [s ].hh .v.RH ;
	mem [s ].hh .v.RH = z ;
      } 
    } 
  } 
} 
void 
dirout ( void ) 
{
  dirout_regmem 
  halfword thisbox  ;
  thisbox = tempptr ;
  tempptr = mem [thisbox + 5 ].hh .v.RH ;
  if ( ( mem [tempptr ].hh.b0 != 0 ) && ( mem [tempptr ].hh.b0 != 1 ) ) 
  confusion ( 1437 ) ;
  switch ( ( mem [thisbox ].hh.b1 ) ) 
  {case 4 : 
    switch ( ( mem [tempptr ].hh.b1 ) ) 
    {case 3 : 
      {
	curv = curv - mem [thisbox + 3 ].cint ;
	curh = curh + mem [tempptr + 2 ].cint ;
      } 
      break ;
    case 1 : 
      {
	curv = curv + mem [thisbox + 2 ].cint ;
	curh = curh + mem [tempptr + 3 ].cint ;
      } 
      break ;
    } 
    break ;
  case 3 : 
    switch ( ( mem [tempptr ].hh.b1 ) ) 
    {case 4 : 
      {
	curv = curv + mem [thisbox + 2 ].cint ;
	curh = curh + mem [tempptr + 3 ].cint ;
      } 
      break ;
    case 1 : 
      {
	curv = curv + mem [thisbox + 2 ].cint - mem [tempptr + 3 ].cint ;
	curh = curh + mem [tempptr + 1 ].cint ;
      } 
      break ;
    } 
    break ;
  case 1 : 
    switch ( ( mem [tempptr ].hh.b1 ) ) 
    {case 4 : 
      {
	curv = curv - mem [thisbox + 3 ].cint ;
	curh = curh + mem [tempptr + 2 ].cint ;
      } 
      break ;
    case 3 : 
      {
	curv = curv + mem [thisbox + 2 ].cint - mem [tempptr + 3 ].cint ;
	curh = curh + mem [tempptr + 1 ].cint ;
      } 
      break ;
    } 
    break ;
  } 
  curdirhv = ( mem [tempptr ].hh.b1 ) ;
  if ( mem [tempptr ].hh.b0 == 1 ) 
  vlistout () ;
  else hlistout () ;
} 
void 
hlistout ( void ) 
{
  /* 21 13 14 15 22 40 */ hlistout_regmem 
  scaled baseline  ;
  scaled disp  ;
  eightbits savedir  ;
  KANJIcode jc  ;
  halfword kspptr  ;
  scaled leftedge  ;
  scaled saveh, savev  ;
  halfword thisbox  ;
  glueord gorder  ;
  unsigned char gsign  ;
  halfword p  ;
  integer saveloc  ;
  halfword leaderbox  ;
  scaled leaderwd  ;
  scaled lx  ;
  boolean outerdoingleaders  ;
  scaled edge  ;
  real gluetemp  ;
  real curglue  ;
  scaled curg  ;
  curg = 0 ;
  curglue = 0.0 ;
  thisbox = tempptr ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  p = mem [thisbox + 5 ].hh .v.RH ;
  kspptr = mem [thisbox + 7 ].hh .v.RH ;
  incr ( curs ) ;
  if ( curs > 0 ) 
  {
    dvibuf [dviptr ]= 141 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  if ( curs > maxpush ) 
  maxpush = curs ;
  saveloc = dvioffset + dviptr ;
  synchdir () ;
  baseline = curv ;
  leftedge = curh ;
  disp = 0 ;
  synctexhlist ( thisbox ) ;
  while ( p != -1073741823L ) lab21: if ( ( p >= himemmin ) ) 
  {
    if ( curh != dvih ) 
    {
      movement ( curh - dvih , 143 ) ;
      dvih = curh ;
    } 
    if ( curv != dviv ) 
    {
      movement ( curv - dviv , 157 ) ;
      dviv = curv ;
    } 
    chain = false ;
    do {
	f = mem [p ].hh.b0 ;
      c = mem [p ].hh.b1 ;
      if ( f != dvif ) 
      {
	if ( ! fontused [f ]) 
	{
	  dvifontdef ( f ) ;
	  fontused [f ]= true ;
	} 
	if ( f <= 64 ) 
	{
	  dvibuf [dviptr ]= f + 170 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	else if ( f <= 256 ) 
	{
	  {
	    dvibuf [dviptr ]= 235 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= f - 1 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	else {
	    
	  {
	    dvibuf [dviptr ]= 236 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= ( f - 1 ) / 256 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= ( f - 1 ) % 256 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	dvif = f ;
      } 
      if ( fontdir [f ]== 0 ) 
      {
	chain = false ;
	if ( fontec [f ]>= c ) {
	    
	  if ( fontbc [f ]<= c ) {
	      
	    if ( ( fontinfo [charbase [f ]+ c ].qqqq .b0 > 0 ) ) 
	    {
	      if ( c >= 128 ) 
	      {
		dvibuf [dviptr ]= 128 ;
		incr ( dviptr ) ;
		if ( dviptr == dvilimit ) 
		dviswap () ;
	      } 
	      {
		dvibuf [dviptr ]= c ;
		incr ( dviptr ) ;
		if ( dviptr == dvilimit ) 
		dviswap () ;
	      } 
	      curh = curh + fontinfo [widthbase [f ]+ fontinfo [charbase [
	      f ]+ c ].qqqq .b0 ].cint ;
	      goto lab22 ;
	    } 
	  } 
	} 
	if ( mltexenabledp ) 
	{
	  if ( c >= eqtb [28522 ].cint ) {
	      
	    if ( c <= eqtb [28523 ].cint ) {
		
	      if ( ( eqtb [28206 + c ].hh .v.RH > 0 ) ) 
	      {
		basec = ( eqtb [28206 + c ].hh .v.RH % 256 ) ;
		accentc = ( eqtb [28206 + c ].hh .v.RH / 256 ) ;
		if ( ( fontec [f ]>= basec ) ) {
		    
		  if ( ( fontbc [f ]<= basec ) ) {
		      
		    if ( ( fontec [f ]>= accentc ) ) {
			
		      if ( ( fontbc [f ]<= accentc ) ) 
		      {
			iac = fontinfo [charbase [f ]+ effectivechar ( true 
			, f , accentc ) ].qqqq ;
			ibc = fontinfo [charbase [f ]+ effectivechar ( true 
			, f , basec ) ].qqqq ;
			if ( ( ibc .b0 > 0 ) ) {
			    
			  if ( ( iac .b0 > 0 ) ) 
			  goto lab40 ;
			} 
		      } 
		    } 
		  } 
		} 
		begindiagnostic () ;
		printnl ( 1397 ) ;
		print ( c ) ;
		print ( 1278 ) ;
		print ( accentc ) ;
		print ( 32 ) ;
		print ( basec ) ;
		print ( 881 ) ;
		slowprint ( fontname [f ]) ;
		printchar ( 33 ) ;
		enddiagnostic ( false ) ;
		goto lab22 ;
	      } 
	    } 
	  } 
	  begindiagnostic () ;
	  printnl ( 880 ) ;
	  print ( 1396 ) ;
	  print ( c ) ;
	  print ( 881 ) ;
	  slowprint ( fontname [f ]) ;
	  printchar ( 33 ) ;
	  enddiagnostic ( false ) ;
	  goto lab22 ;
	  lab40: if ( eqtb [28497 ].cint > 99 ) 
	  {
	    begindiagnostic () ;
	    printnl ( 1398 ) ;
	    print ( c ) ;
	    print ( 1278 ) ;
	    print ( accentc ) ;
	    print ( 32 ) ;
	    print ( basec ) ;
	    print ( 881 ) ;
	    slowprint ( fontname [f ]) ;
	    printchar ( 46 ) ;
	    enddiagnostic ( false ) ;
	  } 
	  basexheight = fontinfo [5 + parambase [f ]].cint ;
	  baseslant = fontinfo [1 + parambase [f ]].cint / ((double) 
	  65536.0 ) ;
	  accentslant = baseslant ;
	  basewidth = fontinfo [widthbase [f ]+ ibc .b0 ].cint ;
	  baseheight = fontinfo [heightbase [f ]+ ( ibc .b1 ) / 16 ].cint 
	  ;
	  accentwidth = fontinfo [widthbase [f ]+ iac .b0 ].cint ;
	  accentheight = fontinfo [heightbase [f ]+ ( iac .b1 ) / 16 ]
	  .cint ;
	  delta = round ( ( basewidth - accentwidth ) / ((double) 2.0 ) + 
	  baseheight * baseslant - basexheight * accentslant ) ;
	  dvih = curh ;
	  curh = curh + delta ;
	  if ( curh != dvih ) 
	  {
	    movement ( curh - dvih , 143 ) ;
	    dvih = curh ;
	  } 
	  if ( ( ( baseheight != basexheight ) && ( accentheight > 0 ) ) ) 
	  {
	    curv = baseline + ( basexheight - baseheight ) ;
	    if ( curv != dviv ) 
	    {
	      movement ( curv - dviv , 157 ) ;
	      dviv = curv ;
	    } 
	    if ( accentc >= 128 ) 
	    {
	      dvibuf [dviptr ]= 128 ;
	      incr ( dviptr ) ;
	      if ( dviptr == dvilimit ) 
	      dviswap () ;
	    } 
	    {
	      dvibuf [dviptr ]= accentc ;
	      incr ( dviptr ) ;
	      if ( dviptr == dvilimit ) 
	      dviswap () ;
	    } 
	    curv = baseline ;
	  } 
	  else {
	      
	    if ( curv != dviv ) 
	    {
	      movement ( curv - dviv , 157 ) ;
	      dviv = curv ;
	    } 
	    if ( accentc >= 128 ) 
	    {
	      dvibuf [dviptr ]= 128 ;
	      incr ( dviptr ) ;
	      if ( dviptr == dvilimit ) 
	      dviswap () ;
	    } 
	    {
	      dvibuf [dviptr ]= accentc ;
	      incr ( dviptr ) ;
	      if ( dviptr == dvilimit ) 
	      dviswap () ;
	    } 
	  } 
	  curh = curh + accentwidth ;
	  dvih = curh ;
	  curh = curh + ( - (integer) accentwidth - delta ) ;
	  if ( curh != dvih ) 
	  {
	    movement ( curh - dvih , 143 ) ;
	    dvih = curh ;
	  } 
	  if ( curv != dviv ) 
	  {
	    movement ( curv - dviv , 157 ) ;
	    dviv = curv ;
	  } 
	  if ( basec >= 128 ) 
	  {
	    dvibuf [dviptr ]= 128 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= basec ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  curh = curh + basewidth ;
	  dvih = curh ;
	} 
	lab22: ;
      } 
      else {
	  
	if ( chain == false ) 
	chain = true ;
	else {
	    
	  curh = curh + mem [kspptr + 1 ].cint ;
	  if ( gsign != 0 ) 
	  {
	    if ( gsign == 1 ) 
	    {
	      if ( mem [kspptr ].hh.b0 == gorder ) 
	      curh = curh + round ( mem [thisbox + 6 ].gr * mem [kspptr + 2 
	      ].cint ) ;
	    } 
	    else {
		
	      if ( mem [kspptr ].hh.b1 == gorder ) 
	      curh = curh - round ( mem [thisbox + 6 ].gr * mem [kspptr + 3 
	      ].cint ) ;
	    } 
	  } 
	  if ( curh != dvih ) 
	  {
	    movement ( curh - dvih , 143 ) ;
	    dvih = curh ;
	  } 
	} 
	p = mem [p ].hh .v.RH ;
	jc = toDVI ( mem [p ].hh .v.LH % 16777216L ) ;
	if ( ( jc < 65536L ) ) 
	{
	  {
	    dvibuf [dviptr ]= 129 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	else {
	    
	  {
	    dvibuf [dviptr ]= 130 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= BYTE2 ( jc ) ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	{
	  dvibuf [dviptr ]= BYTE3 ( jc ) ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	{
	  dvibuf [dviptr ]= BYTE4 ( jc ) ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	curh = curh + fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
	c ].qqqq .b0 ].cint ;
      } 
      dvih = curh ;
      p = mem [p ].hh .v.RH ;
    } while ( ! ( ! ( p >= himemmin ) ) ) ;
    synctexcurrent () ;
    chain = false ;
  } 
  else {
      
    switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
      if ( mem [p + 5 ].hh .v.RH == -1073741823L ) 
      {
	if ( mem [p ].hh.b0 != 2 ) {
	    
	  if ( mem [p ].hh.b0 == 1 ) 
	  {
	    synctexvoidvlist ( p , thisbox ) ;
	  } 
	  else {
	      
	    synctexvoidhlist ( p , thisbox ) ;
	  } 
	} 
	curh = curh + mem [p + 1 ].cint ;
      } 
      else {
	  
	saveh = dvih ;
	savev = dviv ;
	savedir = dvidir ;
	curv = baseline + disp + mem [p + 4 ].cint ;
	tempptr = p ;
	edge = curh ;
	switch ( mem [p ].hh.b0 ) 
	{case 0 : 
	  hlistout () ;
	  break ;
	case 1 : 
	  vlistout () ;
	  break ;
	case 2 : 
	  dirout () ;
	  break ;
	} 
	dvih = saveh ;
	dviv = savev ;
	dvidir = savedir ;
	curh = edge + mem [p + 1 ].cint ;
	curv = baseline + disp ;
	curdirhv = savedir ;
      } 
      break ;
    case 3 : 
      {
	ruleht = mem [p + 3 ].cint ;
	ruledp = mem [p + 2 ].cint ;
	rulewd = mem [p + 1 ].cint ;
	goto lab14 ;
      } 
      break ;
    case 10 : 
      outwhat ( p ) ;
      break ;
    case 5 : 
      {
	disp = mem [p + 1 ].cint ;
	curv = baseline + disp ;
      } 
      break ;
    case 12 : 
      {
	g = mem [p + 1 ].hh .v.LH ;
	rulewd = mem [g + 1 ].cint - curg ;
	if ( gsign != 0 ) 
	{
	  if ( gsign == 1 ) 
	  {
	    if ( mem [g ].hh.b0 == gorder ) 
	    {
	      curglue = curglue + mem [g + 2 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
	      curg = round ( gluetemp ) ;
	    } 
	  } 
	  else if ( mem [g ].hh.b1 == gorder ) 
	  {
	    curglue = curglue - mem [g + 3 ].cint ;
	    gluetemp = mem [thisbox + 6 ].gr * curglue ;
	    if ( gluetemp > 1000000000.0 ) 
	    gluetemp = 1000000000.0 ;
	    else if ( gluetemp < -1000000000.0 ) 
	    gluetemp = -1000000000.0 ;
	    curg = round ( gluetemp ) ;
	  } 
	} 
	rulewd = rulewd + curg ;
	if ( mem [p ].hh.b1 >= 100 ) 
	{
	  leaderbox = mem [p + 1 ].hh .v.RH ;
	  if ( mem [leaderbox ].hh.b0 == 3 ) 
	  {
	    ruleht = mem [leaderbox + 3 ].cint ;
	    ruledp = mem [leaderbox + 2 ].cint ;
	    goto lab14 ;
	  } 
	  leaderwd = mem [leaderbox + 1 ].cint ;
	  if ( ( leaderwd > 0 ) && ( rulewd > 0 ) ) 
	  {
	    rulewd = rulewd + 10 ;
	    edge = curh + rulewd ;
	    lx = 0 ;
	    if ( mem [p ].hh.b1 == 100 ) 
	    {
	      saveh = curh ;
	      curh = leftedge + leaderwd * ( ( curh - leftedge ) / leaderwd ) 
	      ;
	      if ( curh < saveh ) 
	      curh = curh + leaderwd ;
	    } 
	    else {
		
	      lq = rulewd / leaderwd ;
	      lr = rulewd % leaderwd ;
	      if ( mem [p ].hh.b1 == 101 ) 
	      curh = curh + ( lr / 2 ) ;
	      else {
		  
		lx = lr / ( lq + 1 ) ;
		curh = curh + ( ( lr - ( lq - 1 ) * lx ) / 2 ) ;
	      } 
	    } 
	    while ( curh + leaderwd <= edge ) {
		
	      curv = baseline + disp + mem [leaderbox + 4 ].cint ;
	      if ( curv != dviv ) 
	      {
		movement ( curv - dviv , 157 ) ;
		dviv = curv ;
	      } 
	      savev = dviv ;
	      if ( curh != dvih ) 
	      {
		movement ( curh - dvih , 143 ) ;
		dvih = curh ;
	      } 
	      saveh = dvih ;
	      savedir = dvidir ;
	      tempptr = leaderbox ;
	      outerdoingleaders = doingleaders ;
	      doingleaders = true ;
	      switch ( mem [leaderbox ].hh.b0 ) 
	      {case 0 : 
		hlistout () ;
		break ;
	      case 1 : 
		vlistout () ;
		break ;
	      case 2 : 
		dirout () ;
		break ;
	      } 
	      doingleaders = outerdoingleaders ;
	      dviv = savev ;
	      dvih = saveh ;
	      dvidir = savedir ;
	      curv = baseline ;
	      curh = saveh + leaderwd + lx ;
	      curdirhv = savedir ;
	    } 
	    curh = edge - 10 ;
	    goto lab15 ;
	  } 
	} 
	goto lab13 ;
      } 
      break ;
    case 13 : 
      {
	synctexkern ( p , thisbox ) ;
	curh = curh + mem [p + 1 ].cint ;
      } 
      break ;
    case 11 : 
      {
	synctexmath ( p , thisbox ) ;
	curh = curh + mem [p + 1 ].cint ;
      } 
      break ;
    case 8 : 
      {
	mem [memtop - 12 ]= mem [p + 1 ];
	mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	p = memtop - 12 ;
	goto lab21 ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    goto lab15 ;
    lab14: if ( ( ruleht == -1073741824L ) ) 
    ruleht = mem [thisbox + 3 ].cint + disp ;
    if ( ( ruledp == -1073741824L ) ) 
    ruledp = mem [thisbox + 2 ].cint - disp ;
    ruleht = ruleht + ruledp ;
    if ( ( ruleht > 0 ) && ( rulewd > 0 ) ) 
    {
      if ( curh != dvih ) 
      {
	movement ( curh - dvih , 143 ) ;
	dvih = curh ;
      } 
      curv = baseline + ruledp ;
      if ( curv != dviv ) 
      {
	movement ( curv - dviv , 157 ) ;
	dviv = curv ;
      } 
      {
	dvibuf [dviptr ]= 132 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dvifour ( ruleht ) ;
      dvifour ( rulewd ) ;
      curv = baseline ;
      dvih = dvih + rulewd ;
    } 
    lab13: {
	
      curh = curh + rulewd ;
      synctexhorizontalruleorglue ( p , thisbox ) ;
    } 
    lab15: p = mem [p ].hh .v.RH ;
  } 
  synctextsilh ( thisbox ) ;
  prunemovements ( saveloc ) ;
  if ( curs > 0 ) 
  dvipop ( saveloc ) ;
  decr ( curs ) ;
} 
void 
vlistout ( void ) 
{
  /* 13 14 15 */ vlistout_regmem 
  scaled leftedge  ;
  scaled topedge  ;
  scaled saveh, savev  ;
  halfword thisbox  ;
  glueord gorder  ;
  unsigned char gsign  ;
  halfword p  ;
  integer saveloc  ;
  halfword leaderbox  ;
  scaled leaderht  ;
  scaled lx  ;
  boolean outerdoingleaders  ;
  scaled edge  ;
  real gluetemp  ;
  real curglue  ;
  scaled curg  ;
  integer savedir  ;
  curg = 0 ;
  curglue = 0.0 ;
  thisbox = tempptr ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  p = mem [thisbox + 5 ].hh .v.RH ;
  incr ( curs ) ;
  if ( curs > 0 ) 
  {
    dvibuf [dviptr ]= 141 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  if ( curs > maxpush ) 
  maxpush = curs ;
  saveloc = dvioffset + dviptr ;
  synchdir () ;
  leftedge = curh ;
  synctexvlist ( thisbox ) ;
  curv = curv - mem [thisbox + 3 ].cint ;
  topedge = curv ;
  while ( p != -1073741823L ) {
      
    if ( ( p >= himemmin ) ) 
    confusion ( 884 ) ;
    else {
	
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 2 : 
	if ( mem [p + 5 ].hh .v.RH == -1073741823L ) 
	{
	  curv = curv + mem [p + 3 ].cint ;
	  if ( mem [p ].hh.b0 != 2 ) {
	      
	    if ( mem [p ].hh.b0 == 1 ) 
	    {
	      synctexvoidvlist ( p , thisbox ) ;
	    } 
	    else {
		
	      synctexvoidhlist ( p , thisbox ) ;
	    } 
	  } 
	  curv = curv + mem [p + 2 ].cint ;
	} 
	else {
	    
	  curv = curv + mem [p + 3 ].cint ;
	  if ( curv != dviv ) 
	  {
	    movement ( curv - dviv , 157 ) ;
	    dviv = curv ;
	  } 
	  saveh = dvih ;
	  savev = dviv ;
	  savedir = dvidir ;
	  curh = leftedge + mem [p + 4 ].cint ;
	  tempptr = p ;
	  switch ( mem [p ].hh.b0 ) 
	  {case 0 : 
	    hlistout () ;
	    break ;
	  case 1 : 
	    vlistout () ;
	    break ;
	  case 2 : 
	    dirout () ;
	    break ;
	  } 
	  dvih = saveh ;
	  dviv = savev ;
	  dvidir = savedir ;
	  curv = savev + mem [p + 2 ].cint ;
	  curh = leftedge ;
	  curdirhv = savedir ;
	} 
	break ;
      case 3 : 
	{
	  ruleht = mem [p + 3 ].cint ;
	  ruledp = mem [p + 2 ].cint ;
	  rulewd = mem [p + 1 ].cint ;
	  goto lab14 ;
	} 
	break ;
      case 10 : 
	outwhat ( p ) ;
	break ;
      case 12 : 
	{
	  g = mem [p + 1 ].hh .v.LH ;
	  ruleht = mem [g + 1 ].cint - curg ;
	  if ( gsign != 0 ) 
	  {
	    if ( gsign == 1 ) 
	    {
	      if ( mem [g ].hh.b0 == gorder ) 
	      {
		curglue = curglue + mem [g + 2 ].cint ;
		gluetemp = mem [thisbox + 6 ].gr * curglue ;
		if ( gluetemp > 1000000000.0 ) 
		gluetemp = 1000000000.0 ;
		else if ( gluetemp < -1000000000.0 ) 
		gluetemp = -1000000000.0 ;
		curg = round ( gluetemp ) ;
	      } 
	    } 
	    else if ( mem [g ].hh.b1 == gorder ) 
	    {
	      curglue = curglue - mem [g + 3 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
	      curg = round ( gluetemp ) ;
	    } 
	  } 
	  ruleht = ruleht + curg ;
	  if ( mem [p ].hh.b1 >= 100 ) 
	  {
	    leaderbox = mem [p + 1 ].hh .v.RH ;
	    if ( mem [leaderbox ].hh.b0 == 3 ) 
	    {
	      rulewd = mem [leaderbox + 1 ].cint ;
	      ruledp = 0 ;
	      goto lab14 ;
	    } 
	    leaderht = mem [leaderbox + 3 ].cint + mem [leaderbox + 2 ]
	    .cint ;
	    if ( ( leaderht > 0 ) && ( ruleht > 0 ) ) 
	    {
	      ruleht = ruleht + 10 ;
	      edge = curv + ruleht ;
	      lx = 0 ;
	      if ( mem [p ].hh.b1 == 100 ) 
	      {
		savev = curv ;
		curv = topedge + leaderht * ( ( curv - topedge ) / leaderht ) 
		;
		if ( curv < savev ) 
		curv = curv + leaderht ;
	      } 
	      else {
		  
		lq = ruleht / leaderht ;
		lr = ruleht % leaderht ;
		if ( mem [p ].hh.b1 == 101 ) 
		curv = curv + ( lr / 2 ) ;
		else {
		    
		  lx = lr / ( lq + 1 ) ;
		  curv = curv + ( ( lr - ( lq - 1 ) * lx ) / 2 ) ;
		} 
	      } 
	      while ( curv + leaderht <= edge ) {
		  
		curh = leftedge + mem [leaderbox + 4 ].cint ;
		if ( curh != dvih ) 
		{
		  movement ( curh - dvih , 143 ) ;
		  dvih = curh ;
		} 
		saveh = dvih ;
		curv = curv + mem [leaderbox + 3 ].cint ;
		if ( curv != dviv ) 
		{
		  movement ( curv - dviv , 157 ) ;
		  dviv = curv ;
		} 
		savev = dviv ;
		savedir = dvidir ;
		tempptr = leaderbox ;
		outerdoingleaders = doingleaders ;
		doingleaders = true ;
		switch ( mem [leaderbox ].hh.b0 ) 
		{case 0 : 
		  hlistout () ;
		  break ;
		case 1 : 
		  vlistout () ;
		  break ;
		case 2 : 
		  dirout () ;
		  break ;
		} 
		doingleaders = outerdoingleaders ;
		dviv = savev ;
		dvih = saveh ;
		dvidir = savedir ;
		curh = leftedge ;
		curv = savev - mem [leaderbox + 3 ].cint + leaderht + lx ;
		curdirhv = savedir ;
	      } 
	      curv = edge - 10 ;
	      goto lab15 ;
	    } 
	  } 
	  goto lab13 ;
	} 
	break ;
      case 13 : 
	curv = curv + mem [p + 1 ].cint ;
	break ;
	default: 
	;
	break ;
      } 
      goto lab15 ;
      lab14: if ( ( rulewd == -1073741824L ) ) 
      rulewd = mem [thisbox + 1 ].cint ;
      ruleht = ruleht + ruledp ;
      curv = curv + ruleht ;
      if ( ( ruleht > 0 ) && ( rulewd > 0 ) ) 
      {
	if ( curh != dvih ) 
	{
	  movement ( curh - dvih , 143 ) ;
	  dvih = curh ;
	} 
	if ( curv != dviv ) 
	{
	  movement ( curv - dviv , 157 ) ;
	  dviv = curv ;
	} 
	{
	  dvibuf [dviptr ]= 137 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	dvifour ( ruleht ) ;
	dvifour ( rulewd ) ;
      } 
      goto lab15 ;
      lab13: curv = curv + ruleht ;
    } 
    lab15: p = mem [p ].hh .v.RH ;
  } 
  synctextsilv ( thisbox ) ;
  prunemovements ( saveloc ) ;
  if ( curs > 0 ) 
  dvipop ( saveloc ) ;
  decr ( curs ) ;
} 
void 
zshipout ( halfword p ) 
{
  /* 30 */ shipout_regmem 
  integer pageloc  ;
  halfword delnode  ;
  unsigned char j, k  ;
  poolpointer s  ;
  unsigned char oldsetting  ;
  synctexsheet ( eqtb [28479 ].cint ) ;
  {
    if ( eqtb [28496 ].cint > 0 ) 
    {
      printnl ( 344 ) ;
      println () ;
      print ( 885 ) ;
    } 
    if ( termoffset > maxprintline - 9 ) 
    println () ;
    else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
    printchar ( 32 ) ;
    printchar ( 91 ) ;
    j = 9 ;
    while ( ( eqtb [28526 + j ].cint == 0 ) && ( j > 0 ) ) decr ( j ) ;
    {register integer for_end; k = 0 ;for_end = j ; if ( k <= for_end) do 
      {
	printint ( eqtb [28526 + k ].cint ) ;
	if ( k < j ) 
	printchar ( 46 ) ;
      } 
    while ( k++ < for_end ) ;} 
    fflush ( stdout ) ;
    if ( eqtb [28496 ].cint > 0 ) 
    {
      printchar ( 93 ) ;
      begindiagnostic () ;
      showbox ( p ) ;
      enddiagnostic ( true ) ;
    } 
    if ( mem [p ].hh.b0 == 2 ) 
    {
      delnode = p ;
      p = mem [p + 5 ].hh .v.RH ;
      deleteglueref ( mem [delnode + 7 ].hh .v.RH ) ;
      deleteglueref ( mem [delnode + 7 ].hh .v.LH ) ;
      freenode ( delnode , 10 ) ;
    } 
    flushnodelist ( mem [p ].hh .v.RH ) ;
    mem [p ].hh .v.RH = -1073741823L ;
    if ( ( mem [p ].hh.b1 ) != 4 ) 
    p = newdirnode ( p , 4 ) ;
    if ( ( mem [p + 3 ].cint > 1073741823L ) || ( mem [p + 2 ].cint > 
    1073741823L ) || ( mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [
    29057 ].cint > 1073741823L ) || ( mem [p + 1 ].cint + eqtb [29056 ]
    .cint > 1073741823L ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 889 ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 890 ;
	helpline [0 ]= 891 ;
      } 
      error () ;
      if ( eqtb [28496 ].cint <= 0 ) 
      {
	begindiagnostic () ;
	printnl ( 892 ) ;
	showbox ( p ) ;
	enddiagnostic ( true ) ;
      } 
      goto lab30 ;
    } 
    if ( mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [29057 ].cint > 
    maxv ) 
    maxv = mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [29057 ].cint ;
    if ( mem [p + 1 ].cint + eqtb [29056 ].cint > maxh ) 
    maxh = mem [p + 1 ].cint + eqtb [29056 ].cint ;
    dvih = 0 ;
    dviv = 0 ;
    curh = eqtb [29056 ].cint ;
    dvif = 0 ;
    dvidir = 4 ;
    curdirhv = dvidir ;
    if ( outputfilename == 0 ) 
    {
      if ( jobname == 0 ) 
      openlogfile () ;
      packjobname ( 848 ) ;
      while ( ! bopenout ( dvifile ) ) promptfilename ( 849 , 848 ) ;
      outputfilename = bmakenamestring ( dvifile ) ;
    } 
    if ( totalpages == 0 ) 
    {
      {
	dvibuf [dviptr ]= 247 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= 2 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dvifour ( 25400000L ) ;
      dvifour ( 473628672L ) ;
      preparemag () ;
      dvifour ( eqtb [28479 ].cint ) ;
      if ( outputcomment ) 
      {
	l = strlen ( outputcomment ) ;
	{
	  dvibuf [dviptr ]= l ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	{register integer for_end; s = 0 ;for_end = l - 1 ; if ( s <= 
	for_end) do 
	  {
	    dvibuf [dviptr ]= outputcomment [s ];
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	while ( s++ < for_end ) ;} 
      } 
      else {
	  
	oldsetting = selector ;
	selector = 21 ;
	print ( 883 ) ;
	printint ( eqtb [28485 ].cint ) ;
	printchar ( 46 ) ;
	printtwo ( eqtb [28484 ].cint ) ;
	printchar ( 46 ) ;
	printtwo ( eqtb [28483 ].cint ) ;
	printchar ( 58 ) ;
	printtwo ( eqtb [28482 ].cint / 60 ) ;
	printtwo ( eqtb [28482 ].cint % 60 ) ;
	selector = oldsetting ;
	{
	  dvibuf [dviptr ]= ( poolptr - strstart [strptr ]) ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	{register integer for_end; s = strstart [strptr ];for_end = 
	poolptr - 1 ; if ( s <= for_end) do 
	  {
	    dvibuf [dviptr ]= strpool [s ];
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	while ( s++ < for_end ) ;} 
	poolptr = strstart [strptr ];
      } 
    } 
    pageloc = dvioffset + dviptr ;
    {
      dvibuf [dviptr ]= 139 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {register integer for_end; k = 0 ;for_end = 9 ; if ( k <= for_end) do 
      dvifour ( eqtb [28526 + k ].cint ) ;
    while ( k++ < for_end ) ;} 
    dvifour ( lastbop ) ;
    lastbop = pageloc ;
    curv = mem [p + 3 ].cint + eqtb [29057 ].cint ;
    tempptr = p ;
    switch ( mem [p ].hh.b0 ) 
    {case 0 : 
      hlistout () ;
      break ;
    case 1 : 
      vlistout () ;
      break ;
    case 2 : 
      dirout () ;
      break ;
    } 
    {
      dvibuf [dviptr ]= 140 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    incr ( totalpages ) ;
    curs = -1 ;
	;
#ifdef IPC
    if ( ipcon > 0 ) 
    {
      if ( dvilimit == halfbuf ) 
      {
	writedvi ( halfbuf , dvibufsize - 1 ) ;
	flushdvi () ;
	dvigone = dvigone + halfbuf ;
      } 
      if ( dviptr > ( 2147483647L - dvioffset ) ) 
      {
	curs = -2 ;
	fatalerror ( 882 ) ;
      } 
      if ( dviptr > 0 ) 
      {
	writedvi ( 0 , dviptr - 1 ) ;
	flushdvi () ;
	dvioffset = dvioffset + dviptr ;
	dvigone = dvigone + dviptr ;
      } 
      dviptr = 0 ;
      dvilimit = dvibufsize ;
      ipcpage ( dvigone ) ;
    } 
#endif /* IPC */
    lab30: ;
    if ( eqtb [28496 ].cint <= 0 ) 
    printchar ( 93 ) ;
    deadcycles = 0 ;
    fflush ( stdout ) ;
	;
#ifdef STAT
    if ( eqtb [28493 ].cint > 1 ) 
    {
      printnl ( 886 ) ;
      printint ( varused ) ;
      printchar ( 38 ) ;
      printint ( dynused ) ;
      printchar ( 59 ) ;
    } 
#endif /* STAT */
    flushnodelist ( p ) ;
	;
#ifdef STAT
    if ( eqtb [28493 ].cint > 1 ) 
    {
      print ( 887 ) ;
      printint ( varused ) ;
      printchar ( 38 ) ;
      printint ( dynused ) ;
      print ( 888 ) ;
      printint ( himemmin - lomemmax - 1 ) ;
      println () ;
    } 
#endif /* STAT */
  } 
  synctexteehs () ;
} 
void 
zscanspec ( groupcode c , boolean threecodes ) 
{
  /* 40 */ scanspec_regmem 
  integer s  ;
  unsigned char speccode  ;
  if ( threecodes ) 
  s = savestack [saveptr + 0 ].cint ;
  if ( scankeyword ( 898 ) ) 
  speccode = 0 ;
  else if ( scankeyword ( 899 ) ) 
  speccode = 1 ;
  else {
      
    speccode = 1 ;
    curval = 0 ;
    goto lab40 ;
  } 
  scandimen ( false , false , false ) ;
  lab40: if ( threecodes ) 
  {
    savestack [saveptr + 0 ].cint = s ;
    incr ( saveptr ) ;
  } 
  savestack [saveptr + 0 ].cint = speccode ;
  savestack [saveptr + 1 ].cint = curval ;
  saveptr = saveptr + 2 ;
  newsavelevel ( c ) ;
  scanleftbrace () ;
} 
halfword 
zhpack ( halfword p , scaled w , smallnumber m ) 
{
  /* 21 50 10 */ register halfword Result; hpack_regmem 
  halfword r  ;
  halfword k  ;
  scaled disp  ;
  halfword q  ;
  scaled h, d, x  ;
  scaled s  ;
  halfword g  ;
  glueord o  ;
  internalfontnumber f  ;
  fourquarters i  ;
  eightbits hd  ;
  lastbadness = 0 ;
  r = getnode ( 10 ) ;
  mem [r ].hh.b0 = 0 ;
  mem [r ].hh.b1 = 0 ;
  mem [r + 4 ].cint = 0 ;
  mem [r + 7 ].hh .v.RH = curkanjiskip ;
  mem [r + 7 ].hh .v.LH = curxkanjiskip ;
  incr ( mem [curkanjiskip ].hh .v.RH ) ;
  incr ( mem [curxkanjiskip ].hh .v.RH ) ;
  k = curkanjiskip ;
  q = r + 5 ;
  mem [q ].hh .v.RH = p ;
  h = 0 ;
  d = 0 ;
  x = 0 ;
  totalstretch [0 ]= 0 ;
  totalshrink [0 ]= 0 ;
  totalstretch [1 ]= 0 ;
  totalshrink [1 ]= 0 ;
  totalstretch [2 ]= 0 ;
  totalshrink [2 ]= 0 ;
  totalstretch [3 ]= 0 ;
  totalshrink [3 ]= 0 ;
  disp = 0 ;
  while ( p != -1073741823L ) {
      
    lab21: chain = false ;
    while ( ( p >= himemmin ) ) {
	
      f = mem [p ].hh.b0 ;
      i = fontinfo [charbase [f ]+ effectivechar ( true , f , mem [p ]
      .hh.b1 ) ].qqqq ;
      hd = i .b1 ;
      x = x + fontinfo [widthbase [f ]+ i .b0 ].cint ;
      s = fontinfo [heightbase [f ]+ ( hd ) / 16 ].cint - disp ;
      if ( s > h ) 
      h = s ;
      s = fontinfo [depthbase [f ]+ ( hd ) % 16 ].cint + disp ;
      if ( s > d ) 
      d = s ;
      if ( fontdir [f ]!= 0 ) 
      {
	p = mem [p ].hh .v.RH ;
	if ( chain ) 
	{
	  x = x + mem [k + 1 ].cint ;
	  o = mem [k ].hh.b0 ;
	  totalstretch [o ]= totalstretch [o ]+ mem [k + 2 ].cint ;
	  o = mem [k ].hh.b1 ;
	  totalshrink [o ]= totalshrink [o ]+ mem [k + 3 ].cint ;
	} 
	else chain = true ;
      } 
      else chain = false ;
      p = mem [p ].hh .v.RH ;
    } 
    if ( p != -1073741823L ) 
    {
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 2 : 
      case 3 : 
      case 15 : 
	{
	  x = x + mem [p + 1 ].cint ;
	  if ( mem [p ].hh.b0 >= 3 ) 
	  s = disp ;
	  else s = mem [p + 4 ].cint + disp ;
	  if ( mem [p + 3 ].cint - s > h ) 
	  h = mem [p + 3 ].cint - s ;
	  if ( mem [p + 2 ].cint + s > d ) 
	  d = mem [p + 2 ].cint + s ;
	} 
	break ;
      case 4 : 
      case 6 : 
      case 7 : 
	if ( adjusttail != -1073741823L ) 
	{
	  while ( mem [q ].hh .v.RH != p ) q = mem [q ].hh .v.RH ;
	  if ( mem [p ].hh.b0 == 7 ) 
	  {
	    mem [adjusttail ].hh .v.RH = mem [p + 1 ].cint ;
	    while ( mem [adjusttail ].hh .v.RH != -1073741823L ) adjusttail 
	    = mem [adjusttail ].hh .v.RH ;
	    p = mem [p ].hh .v.RH ;
	    freenode ( mem [q ].hh .v.RH , 2 ) ;
	  } 
	  else {
	      
	    mem [adjusttail ].hh .v.RH = p ;
	    adjusttail = p ;
	    p = mem [p ].hh .v.RH ;
	  } 
	  mem [q ].hh .v.RH = p ;
	  p = q ;
	} 
	break ;
      case 10 : 
	;
	break ;
      case 5 : 
	disp = mem [p + 1 ].cint ;
	break ;
      case 12 : 
	{
	  g = mem [p + 1 ].hh .v.LH ;
	  x = x + mem [g + 1 ].cint ;
	  o = mem [g ].hh.b0 ;
	  totalstretch [o ]= totalstretch [o ]+ mem [g + 2 ].cint ;
	  o = mem [g ].hh.b1 ;
	  totalshrink [o ]= totalshrink [o ]+ mem [g + 3 ].cint ;
	  if ( mem [p ].hh.b1 >= 100 ) 
	  {
	    g = mem [p + 1 ].hh .v.RH ;
	    if ( mem [g + 3 ].cint > h ) 
	    h = mem [g + 3 ].cint ;
	    if ( mem [g + 2 ].cint > d ) 
	    d = mem [g + 2 ].cint ;
	  } 
	} 
	break ;
      case 13 : 
      case 11 : 
	x = x + mem [p + 1 ].cint ;
	break ;
      case 8 : 
	{
	  mem [memtop - 12 ]= mem [p + 1 ];
	  mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	  p = memtop - 12 ;
	  goto lab21 ;
	} 
	break ;
	default: 
	;
	break ;
      } 
      p = mem [p ].hh .v.RH ;
    } 
  } 
  if ( adjusttail != -1073741823L ) 
  mem [adjusttail ].hh .v.RH = -1073741823L ;
  mem [r + 3 ].cint = h ;
  mem [r + 2 ].cint = d ;
  if ( m == 1 ) 
  w = x + w ;
  mem [r + 1 ].cint = w ;
  x = w - x ;
  if ( x == 0 ) 
  {
    mem [r + 5 ].hh.b0 = 0 ;
    mem [r + 5 ].hh.b1 = 0 ;
    mem [r + 6 ].gr = 0.0 ;
    goto lab10 ;
  } 
  else if ( x > 0 ) 
  {
    if ( totalstretch [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalstretch [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalstretch [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 1 ;
    if ( totalstretch [o ]!= 0 ) 
    mem [r + 6 ].gr = x / ((double) totalstretch [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -1073741823L ) 
      {
	lastbadness = badness ( x , totalstretch [0 ]) ;
	if ( lastbadness > eqtb [28488 ].cint ) 
	{
	  println () ;
	  if ( lastbadness > 100 ) 
	  printnl ( 900 ) ;
	  else printnl ( 901 ) ;
	  print ( 902 ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  else {
      
    if ( totalshrink [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalshrink [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalshrink [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 2 ;
    if ( totalshrink [o ]!= 0 ) 
    mem [r + 6 ].gr = ( - (integer) x ) / ((double) totalshrink [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( ( totalshrink [o ]< - (integer) x ) && ( o == 0 ) && ( mem [r + 5 
    ].hh .v.RH != -1073741823L ) ) 
    {
      lastbadness = 1000000L ;
      mem [r + 6 ].gr = 1.0 ;
      if ( ( - (integer) x - totalshrink [0 ]> eqtb [29046 ].cint ) || ( 
      eqtb [28488 ].cint < 100 ) ) 
      {
	if ( ( eqtb [29054 ].cint > 0 ) && ( - (integer) x - totalshrink [0 
	]> eqtb [29046 ].cint ) ) 
	{
	  while ( mem [q ].hh .v.RH != -1073741823L ) q = mem [q ].hh 
	  .v.RH ;
	  mem [q ].hh .v.RH = newrule () ;
	  mem [mem [q ].hh .v.RH + 1 ].cint = eqtb [29054 ].cint ;
	} 
	println () ;
	printnl ( 908 ) ;
	printscaled ( - (integer) x - totalshrink [0 ]) ;
	print ( 909 ) ;
	goto lab50 ;
      } 
    } 
    else if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -1073741823L ) 
      {
	lastbadness = badness ( - (integer) x , totalshrink [0 ]) ;
	if ( lastbadness > eqtb [28488 ].cint ) 
	{
	  println () ;
	  printnl ( 910 ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  lab50: if ( outputactive ) 
  print ( 903 ) ;
  else {
      
    if ( packbeginline != 0 ) 
    {
      if ( packbeginline > 0 ) 
      print ( 904 ) ;
      else print ( 905 ) ;
      printint ( abs ( packbeginline ) ) ;
      print ( 906 ) ;
    } 
    else print ( 907 ) ;
    printint ( line ) ;
  } 
  println () ;
  fontinshortdisplay = 0 ;
  shortdisplay ( mem [r + 5 ].hh .v.RH ) ;
  println () ;
  begindiagnostic () ;
  showbox ( r ) ;
  enddiagnostic ( true ) ;
  lab10: lastdisp = disp ;
  Result = r ;
  return Result ;
} 
halfword 
zvpackage ( halfword p , scaled h , smallnumber m , scaled l ) 
{
  /* 50 10 */ register halfword Result; vpackage_regmem 
  halfword r  ;
  scaled w, d, x  ;
  scaled s  ;
  halfword g  ;
  glueord o  ;
  lastbadness = 0 ;
  r = getnode ( 10 ) ;
  mem [r ].hh.b0 = 1 ;
  mem [r ].hh.b1 = 0 ;
  mem [r + 4 ].cint = 0 ;
  mem [r + 7 ].hh .v.RH = membot ;
  mem [r + 7 ].hh .v.LH = membot ;
  incr ( mem [membot ].hh .v.RH ) ;
  incr ( mem [membot ].hh .v.RH ) ;
  mem [r + 5 ].hh .v.RH = p ;
  w = 0 ;
  d = 0 ;
  x = 0 ;
  totalstretch [0 ]= 0 ;
  totalshrink [0 ]= 0 ;
  totalstretch [1 ]= 0 ;
  totalshrink [1 ]= 0 ;
  totalstretch [2 ]= 0 ;
  totalshrink [2 ]= 0 ;
  totalstretch [3 ]= 0 ;
  totalshrink [3 ]= 0 ;
  while ( p != -1073741823L ) {
      
    if ( ( p >= himemmin ) ) 
    confusion ( 911 ) ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
    case 3 : 
    case 15 : 
      {
	x = x + d + mem [p + 3 ].cint ;
	d = mem [p + 2 ].cint ;
	if ( mem [p ].hh.b0 >= 3 ) 
	s = 0 ;
	else s = mem [p + 4 ].cint ;
	if ( mem [p + 1 ].cint + s > w ) 
	w = mem [p + 1 ].cint + s ;
      } 
      break ;
    case 10 : 
      ;
      break ;
    case 12 : 
      {
	x = x + d ;
	d = 0 ;
	g = mem [p + 1 ].hh .v.LH ;
	x = x + mem [g + 1 ].cint ;
	o = mem [g ].hh.b0 ;
	totalstretch [o ]= totalstretch [o ]+ mem [g + 2 ].cint ;
	o = mem [g ].hh.b1 ;
	totalshrink [o ]= totalshrink [o ]+ mem [g + 3 ].cint ;
	if ( mem [p ].hh.b1 >= 100 ) 
	{
	  g = mem [p + 1 ].hh .v.RH ;
	  if ( mem [g + 1 ].cint > w ) 
	  w = mem [g + 1 ].cint ;
	} 
      } 
      break ;
    case 13 : 
      {
	x = x + d + mem [p + 1 ].cint ;
	d = 0 ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  mem [r + 1 ].cint = w ;
  if ( d > l ) 
  {
    x = x + d - l ;
    mem [r + 2 ].cint = l ;
  } 
  else mem [r + 2 ].cint = d ;
  if ( m == 1 ) 
  h = x + h ;
  mem [r + 3 ].cint = h ;
  x = h - x ;
  if ( x == 0 ) 
  {
    mem [r + 5 ].hh.b0 = 0 ;
    mem [r + 5 ].hh.b1 = 0 ;
    mem [r + 6 ].gr = 0.0 ;
    goto lab10 ;
  } 
  else if ( x > 0 ) 
  {
    if ( totalstretch [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalstretch [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalstretch [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 1 ;
    if ( totalstretch [o ]!= 0 ) 
    mem [r + 6 ].gr = x / ((double) totalstretch [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -1073741823L ) 
      {
	lastbadness = badness ( x , totalstretch [0 ]) ;
	if ( lastbadness > eqtb [28489 ].cint ) 
	{
	  println () ;
	  if ( lastbadness > 100 ) 
	  printnl ( 900 ) ;
	  else printnl ( 901 ) ;
	  print ( 912 ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  else {
      
    if ( totalshrink [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalshrink [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalshrink [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 2 ;
    if ( totalshrink [o ]!= 0 ) 
    mem [r + 6 ].gr = ( - (integer) x ) / ((double) totalshrink [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( ( totalshrink [o ]< - (integer) x ) && ( o == 0 ) && ( mem [r + 5 
    ].hh .v.RH != -1073741823L ) ) 
    {
      lastbadness = 1000000L ;
      mem [r + 6 ].gr = 1.0 ;
      if ( ( - (integer) x - totalshrink [0 ]> eqtb [29047 ].cint ) || ( 
      eqtb [28489 ].cint < 100 ) ) 
      {
	println () ;
	printnl ( 913 ) ;
	printscaled ( - (integer) x - totalshrink [0 ]) ;
	print ( 914 ) ;
	goto lab50 ;
      } 
    } 
    else if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -1073741823L ) 
      {
	lastbadness = badness ( - (integer) x , totalshrink [0 ]) ;
	if ( lastbadness > eqtb [28489 ].cint ) 
	{
	  println () ;
	  printnl ( 915 ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  lab50: if ( outputactive ) 
  print ( 903 ) ;
  else {
      
    if ( packbeginline != 0 ) 
    {
      print ( 905 ) ;
      printint ( abs ( packbeginline ) ) ;
      print ( 906 ) ;
    } 
    else print ( 907 ) ;
    printint ( line ) ;
    println () ;
  } 
  begindiagnostic () ;
  showbox ( r ) ;
  enddiagnostic ( true ) ;
  lab10: Result = r ;
  return Result ;
} 
void 
zappendtovlist ( halfword b ) 
{
  appendtovlist_regmem 
  scaled d  ;
  halfword p  ;
  if ( curlist .auxfield .cint > -65536000L ) 
  {
    d = mem [eqtb [24528 ].hh .v.RH + 1 ].cint - curlist .auxfield .cint - 
    mem [b + 3 ].cint ;
    if ( d < eqtb [29040 ].cint ) 
    p = newparamglue ( 0 ) ;
    else {
	
      p = newskipparam ( 1 ) ;
      mem [tempptr + 1 ].cint = d ;
    } 
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
  } 
  mem [curlist .tailfield ].hh .v.RH = b ;
  curlist .tailfield = b ;
  curlist .auxfield .cint = mem [b + 2 ].cint ;
} 
halfword 
newnoad ( void ) 
{
  register halfword Result; newnoad_regmem 
  halfword p  ;
  p = getnode ( 5 ) ;
  mem [p ].hh.b0 = 18 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh = emptyfield ;
  mem [p + 3 ].hh = emptyfield ;
  mem [p + 2 ].hh = emptyfield ;
  mem [p + 4 ].hh = emptyfield ;
  Result = p ;
  return Result ;
} 
halfword 
znewstyle ( smallnumber s ) 
{
  register halfword Result; newstyle_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 16 ;
  mem [p ].hh.b1 = s ;
  mem [p + 1 ].cint = 0 ;
  mem [p + 2 ].cint = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
newchoice ( void ) 
{
  register halfword Result; newchoice_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 17 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.LH = -1073741823L ;
  mem [p + 1 ].hh .v.RH = -1073741823L ;
  mem [p + 2 ].hh .v.LH = -1073741823L ;
  mem [p + 2 ].hh .v.RH = -1073741823L ;
  Result = p ;
  return Result ;
} 
void 
showinfo ( void ) 
{
  showinfo_regmem 
  shownodelist ( mem [tempptr ].hh .v.LH ) ;
} 
halfword 
zfractionrule ( scaled t ) 
{
  register halfword Result; fractionrule_regmem 
  halfword p  ;
  p = newrule () ;
  mem [p + 3 ].cint = t ;
  mem [p + 2 ].cint = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
zoverbar ( halfword b , scaled k , scaled t ) 
{
  register halfword Result; overbar_regmem 
  halfword p, q  ;
  p = newkern ( k ) ;
  mem [p ].hh .v.RH = b ;
  q = fractionrule ( t ) ;
  mem [q ].hh .v.RH = p ;
  p = newkern ( t ) ;
  mem [p ].hh .v.RH = q ;
  Result = vpackage ( p , 0 , 1 , 1073741823L ) ;
  return Result ;
} 
halfword 
zcharbox ( internalfontnumber f , quarterword c ) 
{
  register halfword Result; charbox_regmem 
  fourquarters q  ;
  eightbits hd  ;
  halfword b, p  ;
  q = fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq ;
  hd = q .b1 ;
  b = newnullbox () ;
  mem [b + 1 ].cint = fontinfo [widthbase [f ]+ q .b0 ].cint + fontinfo 
  [italicbase [f ]+ ( q .b2 ) / 4 ].cint ;
  mem [b + 3 ].cint = fontinfo [heightbase [f ]+ ( hd ) / 16 ].cint ;
  mem [b + 2 ].cint = fontinfo [depthbase [f ]+ ( hd ) % 16 ].cint ;
  p = getavail () ;
  mem [p ].hh.b1 = c ;
  mem [p ].hh.b0 = f ;
  mem [b + 5 ].hh .v.RH = p ;
  Result = b ;
  return Result ;
} 
void 
zstackintobox ( halfword b , internalfontnumber f , quarterword c ) 
{
  stackintobox_regmem 
  halfword p  ;
  p = charbox ( f , c ) ;
  mem [p ].hh .v.RH = mem [b + 5 ].hh .v.RH ;
  mem [b + 5 ].hh .v.RH = p ;
  mem [b + 3 ].cint = mem [p + 3 ].cint ;
} 
scaled 
zheightplusdepth ( internalfontnumber f , quarterword c ) 
{
  register scaled Result; heightplusdepth_regmem 
  fourquarters q  ;
  eightbits hd  ;
  q = fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq ;
  hd = q .b1 ;
  Result = fontinfo [heightbase [f ]+ ( hd ) / 16 ].cint + fontinfo [
  depthbase [f ]+ ( hd ) % 16 ].cint ;
  return Result ;
} 
halfword 
zvardelimiter ( halfword d , smallnumber s , scaled v ) 
{
  /* 40 22 */ register halfword Result; vardelimiter_regmem 
  halfword b  ;
  internalfontnumber f, g  ;
  quarterword c, x, y  ;
  integer m, n  ;
  scaled u  ;
  scaled w  ;
  fourquarters q  ;
  eightbits hd  ;
  fourquarters r  ;
  smallnumber z  ;
  boolean largeattempt  ;
  f = 0 ;
  w = 0 ;
  largeattempt = false ;
  z = mem [d ].qqqq .b0 ;
  x = mem [d ].qqqq .b1 ;
  while ( true ) {
      
    if ( ( z != 0 ) || ( x != 0 ) ) 
    {
      z = z + s + 16 ;
      do {
	  z = z - 16 ;
	g = eqtb [25583 + z ].hh .v.RH ;
	if ( g != 0 ) 
	{
	  y = x ;
	  if ( ( y >= fontbc [g ]) && ( y <= fontec [g ]) ) 
	  {
	    lab22: q = fontinfo [charbase [g ]+ y ].qqqq ;
	    if ( ( q .b0 > 0 ) ) 
	    {
	      if ( ( ( q .b2 ) % 4 ) == 3 ) 
	      {
		f = g ;
		c = y ;
		goto lab40 ;
	      } 
	      hd = q .b1 ;
	      u = fontinfo [heightbase [g ]+ ( hd ) / 16 ].cint + fontinfo 
	      [depthbase [g ]+ ( hd ) % 16 ].cint ;
	      if ( u > w ) 
	      {
		f = g ;
		c = y ;
		w = u ;
		if ( u >= v ) 
		goto lab40 ;
	      } 
	      if ( ( ( q .b2 ) % 4 ) == 2 ) 
	      {
		y = q .b3 ;
		goto lab22 ;
	      } 
	    } 
	  } 
	} 
      } while ( ! ( z < 16 ) ) ;
    } 
    if ( largeattempt ) 
    goto lab40 ;
    largeattempt = true ;
    z = mem [d ].qqqq .b2 ;
    x = mem [d ].qqqq .b3 ;
  } 
  lab40: if ( f != 0 ) {
      
    if ( ( ( q .b2 ) % 4 ) == 3 ) 
    {
      b = newnullbox () ;
      mem [b ].hh.b0 = 1 ;
      r = fontinfo [extenbase [f ]+ q .b3 ].qqqq ;
      c = r .b3 ;
      u = heightplusdepth ( f , c ) ;
      w = 0 ;
      q = fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq ;
      mem [b + 1 ].cint = fontinfo [widthbase [f ]+ q .b0 ].cint + 
      fontinfo [italicbase [f ]+ ( q .b2 ) / 4 ].cint ;
      c = r .b2 ;
      if ( c != 0 ) 
      w = w + heightplusdepth ( f , c ) ;
      c = r .b1 ;
      if ( c != 0 ) 
      w = w + heightplusdepth ( f , c ) ;
      c = r .b0 ;
      if ( c != 0 ) 
      w = w + heightplusdepth ( f , c ) ;
      n = 0 ;
      if ( u > 0 ) 
      while ( w < v ) {
	  
	w = w + u ;
	incr ( n ) ;
	if ( r .b1 != 0 ) 
	w = w + u ;
      } 
      c = r .b2 ;
      if ( c != 0 ) 
      stackintobox ( b , f , c ) ;
      c = r .b3 ;
      {register integer for_end; m = 1 ;for_end = n ; if ( m <= for_end) do 
	stackintobox ( b , f , c ) ;
      while ( m++ < for_end ) ;} 
      c = r .b1 ;
      if ( c != 0 ) 
      {
	stackintobox ( b , f , c ) ;
	c = r .b3 ;
	{register integer for_end; m = 1 ;for_end = n ; if ( m <= for_end) 
	do 
	  stackintobox ( b , f , c ) ;
	while ( m++ < for_end ) ;} 
      } 
      c = r .b0 ;
      if ( c != 0 ) 
      stackintobox ( b , f , c ) ;
      mem [b + 2 ].cint = w - mem [b + 3 ].cint ;
    } 
    else b = charbox ( f , c ) ;
  } 
  else {
      
    b = newnullbox () ;
    mem [b + 1 ].cint = eqtb [29049 ].cint ;
  } 
  mem [b + 4 ].cint = half ( mem [b + 3 ].cint - mem [b + 2 ].cint ) - 
  fontinfo [22 + parambase [eqtb [25585 + s ].hh .v.RH ]].cint ;
  Result = b ;
  return Result ;
} 
halfword 
zrebox ( halfword b , scaled w ) 
{
  register halfword Result; rebox_regmem 
  halfword p  ;
  internalfontnumber f  ;
  scaled v  ;
  if ( ( mem [b + 1 ].cint != w ) && ( mem [b + 5 ].hh .v.RH != 
  -1073741823L ) ) 
  {
    if ( mem [b ].hh.b0 != 0 ) 
    b = hpack ( b , 0 , 1 ) ;
    p = mem [b + 5 ].hh .v.RH ;
    if ( ( p >= himemmin ) ) {
	
      if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
      {
	if ( mem [mem [p ].hh .v.RH ].hh .v.RH == -1073741823L ) 
	{
	  f = mem [p ].hh.b0 ;
	  v = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ mem [p 
	  ].hh.b1 ].qqqq .b0 ].cint ;
	  if ( v != mem [b + 1 ].cint ) 
	  mem [mem [p ].hh .v.RH ].hh .v.RH = newkern ( mem [b + 1 ]
	  .cint - v ) ;
	} 
      } 
      else if ( mem [p ].hh .v.RH == -1073741823L ) 
      {
	f = mem [p ].hh.b0 ;
	v = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ mem [p ]
	.hh.b1 ].qqqq .b0 ].cint ;
	if ( v != mem [b + 1 ].cint ) 
	mem [p ].hh .v.RH = newkern ( mem [b + 1 ].cint - v ) ;
      } 
    } 
    deleteglueref ( mem [b + 7 ].hh .v.RH ) ;
    deleteglueref ( mem [b + 7 ].hh .v.LH ) ;
    freenode ( b , 10 ) ;
    b = newglue ( membot + 12 ) ;
    mem [b ].hh .v.RH = p ;
    while ( mem [p ].hh .v.RH != -1073741823L ) p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = newglue ( membot + 12 ) ;
    Result = hpack ( b , w , 0 ) ;
  } 
  else {
      
    mem [b + 1 ].cint = w ;
    Result = b ;
  } 
  return Result ;
} 
halfword 
zmathglue ( halfword g , scaled m ) 
{
  register halfword Result; mathglue_regmem 
  halfword p  ;
  integer n  ;
  scaled f  ;
  n = xovern ( m , 65536L ) ;
  f = texremainder ;
  if ( f < 0 ) 
  {
    decr ( n ) ;
    f = f + 65536L ;
  } 
  p = getnode ( 4 ) ;
  mem [p + 1 ].cint = multandadd ( n , mem [g + 1 ].cint , xnoverd ( mem [
  g + 1 ].cint , f , 65536L ) , 1073741823L ) ;
  mem [p ].hh.b0 = mem [g ].hh.b0 ;
  if ( mem [p ].hh.b0 == 0 ) 
  mem [p + 2 ].cint = multandadd ( n , mem [g + 2 ].cint , xnoverd ( mem [
  g + 2 ].cint , f , 65536L ) , 1073741823L ) ;
  else mem [p + 2 ].cint = mem [g + 2 ].cint ;
  mem [p ].hh.b1 = mem [g ].hh.b1 ;
  if ( mem [p ].hh.b1 == 0 ) 
  mem [p + 3 ].cint = multandadd ( n , mem [g + 3 ].cint , xnoverd ( mem [
  g + 3 ].cint , f , 65536L ) , 1073741823L ) ;
  else mem [p + 3 ].cint = mem [g + 3 ].cint ;
  Result = p ;
  return Result ;
} 
void 
zmathkern ( halfword p , scaled m ) 
{
  mathkern_regmem 
  integer n  ;
  scaled f  ;
  if ( mem [p ].hh.b1 == 99 ) 
  {
    n = xovern ( m , 65536L ) ;
    f = texremainder ;
    if ( f < 0 ) 
    {
      decr ( n ) ;
      f = f + 65536L ;
    } 
    mem [p + 1 ].cint = multandadd ( n , mem [p + 1 ].cint , xnoverd ( mem 
    [p + 1 ].cint , f , 65536L ) , 1073741823L ) ;
    mem [p ].hh.b1 = 1 ;
  } 
} 
void 
flushmath ( void ) 
{
  flushmath_regmem 
  flushnodelist ( mem [curlist .headfield ].hh .v.RH ) ;
  flushnodelist ( curlist .auxfield .cint ) ;
  mem [curlist .headfield ].hh .v.RH = -1073741823L ;
  curlist .tailfield = curlist .headfield ;
  curlist .auxfield .cint = -1073741823L ;
} 
halfword 
zshiftsubexpbox ( halfword q ) 
{
  register halfword Result; shiftsubexpbox_regmem 
  halfword d  ;
  if ( curlist .dirfield == 3 ) 
  d = eqtb [29059 ].cint ;
  else d = eqtb [29060 ].cint ;
  if ( curstyle < 4 ) 
  d = xnoverd ( d , eqtb [28519 ].cint , 1000 ) ;
  else if ( curstyle < 6 ) 
  d = xnoverd ( d , eqtb [28520 ].cint , 1000 ) ;
  else d = xnoverd ( d , eqtb [28521 ].cint , 1000 ) ;
  mem [mem [q ].hh .v.LH + 4 ].cint = mem [mem [q ].hh .v.LH + 4 ]
  .cint - d ;
  mem [q ].hh .v.RH = 2 ;
  Result = mem [q ].hh .v.LH ;
  return Result ;
} 
halfword 
zcleanbox ( halfword p , smallnumber s , halfword jc ) 
{
  /* 40 */ register halfword Result; cleanbox_regmem 
  halfword q  ;
  smallnumber savestyle  ;
  halfword x  ;
  halfword r  ;
  switch ( mem [p ].hh .v.RH ) 
  {case 1 : 
    {
      curmlist = newnoad () ;
      mem [curmlist + 1 ]= mem [p ];
    } 
    break ;
  case 6 : 
    {
      curmlist = newnoad () ;
      mem [curmlist + 1 ]= mem [p ];
      mem [curmlist + 4 ].hh .v.LH = jc ;
    } 
    break ;
  case 2 : 
    {
      q = mem [p ].hh .v.LH ;
      goto lab40 ;
    } 
    break ;
  case 3 : 
    {
      q = shiftsubexpbox ( p ) ;
      goto lab40 ;
    } 
    break ;
  case 4 : 
    curmlist = mem [p ].hh .v.LH ;
    break ;
    default: 
    {
      q = newnullbox () ;
      goto lab40 ;
    } 
    break ;
  } 
  savestyle = curstyle ;
  curstyle = s ;
  mlistpenalties = false ;
  mlisttohlist () ;
  q = mem [memtop - 3 ].hh .v.RH ;
  curstyle = savestyle ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( fontinfo [6 + parambase [eqtb [25585 + cursize ].hh 
    .v.RH ]].cint , 18 ) ;
  } 
  lab40: if ( ( q >= himemmin ) || ( q == -1073741823L ) ) 
  x = hpack ( q , 0 , 1 ) ;
  else if ( ( mem [q ].hh .v.RH == -1073741823L ) && ( mem [q ].hh.b0 <= 2 
  ) && ( mem [q + 4 ].cint == 0 ) ) 
  x = q ;
  else x = hpack ( q , 0 , 1 ) ;
  q = mem [x + 5 ].hh .v.RH ;
  if ( ( q >= himemmin ) ) 
  {
    if ( fontdir [mem [q ].hh.b0 ]!= 0 ) 
    q = mem [q ].hh .v.RH ;
    r = mem [q ].hh .v.RH ;
    if ( r != -1073741823L ) {
	
      if ( mem [r ].hh .v.RH == -1073741823L ) {
	  
	if ( ! ( r >= himemmin ) ) {
	    
	  if ( mem [r ].hh.b0 == 13 ) 
	  {
	    freenode ( r , 4 ) ;
	    mem [q ].hh .v.RH = -1073741823L ;
	  } 
	} 
      } 
    } 
  } 
  Result = x ;
  return Result ;
} 
void 
zfetch ( halfword a ) 
{
  fetch_regmem 
  curc = mem [a ].hh.b1 ;
  curf = eqtb [25583 + mem [a ].hh.b0 + cursize ].hh .v.RH ;
  if ( curf == 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 344 ) ;
    } 
    printsize ( cursize ) ;
    printchar ( 32 ) ;
    printint ( mem [a ].hh.b0 ) ;
    print ( 940 ) ;
    print ( curc ) ;
    printchar ( 41 ) ;
    {
      helpptr = 4 ;
      helpline [3 ]= 941 ;
      helpline [2 ]= 942 ;
      helpline [1 ]= 943 ;
      helpline [0 ]= 944 ;
    } 
    error () ;
    curi = nullcharacter ;
    mem [a ].hh .v.RH = 0 ;
  } 
  else {
      
    if ( fontdir [curf ]!= 0 ) 
    curc = getjfmpos ( mem [a + 3 ].hh .v.LH , curf ) ;
    if ( ( curc >= fontbc [curf ]) && ( curc <= fontec [curf ]) ) 
    curi = fontinfo [charbase [curf ]+ curc ].qqqq ;
    else curi = nullcharacter ;
    if ( ! ( ( curi .b0 > 0 ) ) ) 
    {
      charwarning ( curf , curc ) ;
      mem [a ].hh .v.RH = 0 ;
    } 
  } 
} 
void 
zmakeover ( halfword q ) 
{
  makeover_regmem 
  mem [q + 1 ].hh .v.LH = overbar ( cleanbox ( q + 1 , 2 * ( curstyle / 2 ) 
  + 1 , mem [q + 4 ].hh .v.LH ) , 3 * fontinfo [8 + parambase [eqtb [
  25586 + cursize ].hh .v.RH ]].cint , fontinfo [8 + parambase [eqtb [
  25586 + cursize ].hh .v.RH ]].cint ) ;
  mem [q + 1 ].hh .v.RH = 2 ;
} 
void 
zmakeunder ( halfword q ) 
{
  makeunder_regmem 
  halfword p, x, y  ;
  scaled delta  ;
  x = cleanbox ( q + 1 , curstyle , mem [q + 4 ].hh .v.LH ) ;
  p = newkern ( 3 * fontinfo [8 + parambase [eqtb [25586 + cursize ].hh 
  .v.RH ]].cint ) ;
  mem [x ].hh .v.RH = p ;
  mem [p ].hh .v.RH = fractionrule ( fontinfo [8 + parambase [eqtb [25586 
  + cursize ].hh .v.RH ]].cint ) ;
  y = vpackage ( x , 0 , 1 , 1073741823L ) ;
  delta = mem [y + 3 ].cint + mem [y + 2 ].cint + fontinfo [8 + parambase 
  [eqtb [25586 + cursize ].hh .v.RH ]].cint ;
  mem [y + 3 ].cint = mem [x + 3 ].cint ;
  mem [y + 2 ].cint = delta - mem [y + 3 ].cint ;
  mem [q + 1 ].hh .v.LH = y ;
  mem [q + 1 ].hh .v.RH = 2 ;
} 
void 
zmakevcenter ( halfword q ) 
{
  makevcenter_regmem 
  halfword v  ;
  scaled delta  ;
  v = mem [q + 1 ].hh .v.LH ;
  if ( mem [v ].hh.b0 == 2 ) 
  {
    if ( mem [mem [v + 5 ].hh .v.RH ].hh.b0 != 1 ) 
    confusion ( 946 ) ;
  } 
  else {
      
    if ( mem [v ].hh.b0 != 1 ) 
    confusion ( 577 ) ;
  } 
  delta = mem [v + 3 ].cint + mem [v + 2 ].cint ;
  mem [v + 3 ].cint = fontinfo [22 + parambase [eqtb [25585 + cursize ]
  .hh .v.RH ]].cint + half ( delta ) ;
  mem [v + 2 ].cint = delta - mem [v + 3 ].cint ;
} 
void 
zmakeradical ( halfword q ) 
{
  makeradical_regmem 
  halfword x, y  ;
  scaled delta, clr  ;
  x = cleanbox ( q + 1 , 2 * ( curstyle / 2 ) + 1 , mem [q + 4 ].hh .v.LH ) 
  ;
  if ( curstyle < 2 ) 
  clr = fontinfo [8 + parambase [eqtb [25586 + cursize ].hh .v.RH ]]
  .cint + ( abs ( fontinfo [5 + parambase [eqtb [25585 + cursize ].hh 
  .v.RH ]].cint ) / 4 ) ;
  else {
      
    clr = fontinfo [8 + parambase [eqtb [25586 + cursize ].hh .v.RH ]]
    .cint ;
    clr = clr + ( abs ( clr ) / 4 ) ;
  } 
  y = vardelimiter ( q + 5 , cursize , mem [x + 3 ].cint + mem [x + 2 ]
  .cint + clr + fontinfo [8 + parambase [eqtb [25586 + cursize ].hh .v.RH 
  ]].cint ) ;
  delta = mem [y + 2 ].cint - ( mem [x + 3 ].cint + mem [x + 2 ].cint + 
  clr ) ;
  if ( delta > 0 ) 
  clr = clr + half ( delta ) ;
  mem [y + 4 ].cint = - (integer) ( mem [x + 3 ].cint + clr ) ;
  mem [y ].hh .v.RH = overbar ( x , clr , mem [y + 3 ].cint ) ;
  mem [q + 1 ].hh .v.LH = hpack ( y , 0 , 1 ) ;
  mem [q + 1 ].hh .v.RH = 2 ;
} 
void 
zmakemathaccent ( halfword q ) 
{
  /* 30 31 */ makemathaccent_regmem 
  halfword p, x, y  ;
  integer a  ;
  quarterword c  ;
  internalfontnumber f  ;
  fourquarters i  ;
  scaled s  ;
  scaled h  ;
  scaled delta  ;
  scaled w  ;
  fetch ( q + 5 ) ;
  if ( ( curi .b0 > 0 ) ) 
  {
    i = curi ;
    c = curc ;
    f = curf ;
    s = 0 ;
    if ( mem [q + 1 ].hh .v.RH == 1 ) 
    {
      fetch ( q + 1 ) ;
      if ( ( ( curi .b2 ) % 4 ) == 1 ) 
      {
	a = ligkernbase [curf ]+ curi .b3 ;
	curi = fontinfo [a ].qqqq ;
	if ( curi .b0 > 128 ) 
	{
	  a = ligkernbase [curf ]+ 256 * curi .b2 + curi .b3 + 32768L - 256 
	  * ( 128 ) ;
	  curi = fontinfo [a ].qqqq ;
	} 
	while ( true ) {
	    
	  if ( curi .b1 == skewchar [curf ]) 
	  {
	    if ( curi .b2 >= 128 ) {
		
	      if ( curi .b0 <= 128 ) 
	      s = fontinfo [kernbase [curf ]+ 256 * curi .b2 + curi .b3 ]
	      .cint ;
	    } 
	    goto lab31 ;
	  } 
	  if ( curi .b0 >= 128 ) 
	  goto lab31 ;
	  a = a + curi .b0 + 1 ;
	  curi = fontinfo [a ].qqqq ;
	} 
      } 
    } 
    lab31: ;
    x = cleanbox ( q + 1 , 2 * ( curstyle / 2 ) + 1 , mem [q + 4 ].hh .v.LH 
    ) ;
    w = mem [x + 1 ].cint ;
    h = mem [x + 3 ].cint ;
    while ( true ) {
	
      if ( ( ( i .b2 ) % 4 ) != 2 ) 
      goto lab30 ;
      y = i .b3 ;
      i = fontinfo [charbase [f ]+ y ].qqqq ;
      if ( ! ( i .b0 > 0 ) ) 
      goto lab30 ;
      if ( fontinfo [widthbase [f ]+ i .b0 ].cint > w ) 
      goto lab30 ;
      c = y ;
    } 
    lab30: ;
    if ( h < fontinfo [5 + parambase [f ]].cint ) 
    delta = h ;
    else delta = fontinfo [5 + parambase [f ]].cint ;
    if ( ( mem [q + 2 ].hh .v.RH != 0 ) || ( mem [q + 3 ].hh .v.RH != 0 ) 
    ) {
	
      if ( mem [q + 1 ].hh .v.RH == 1 ) 
      {
	flushnodelist ( x ) ;
	x = newnoad () ;
	mem [x + 1 ]= mem [q + 1 ];
	mem [x + 2 ]= mem [q + 2 ];
	mem [x + 3 ]= mem [q + 3 ];
	mem [q + 2 ].hh = emptyfield ;
	mem [q + 3 ].hh = emptyfield ;
	mem [q + 1 ].hh .v.RH = 4 ;
	mem [q + 1 ].hh .v.LH = x ;
	x = cleanbox ( q + 1 , curstyle , mem [q + 4 ].hh .v.LH ) ;
	delta = delta + mem [x + 3 ].cint - h ;
	h = mem [x + 3 ].cint ;
      } 
    } 
    y = charbox ( f , c ) ;
    mem [y + 4 ].cint = s + half ( w - mem [y + 1 ].cint ) ;
    mem [y + 1 ].cint = 0 ;
    p = newkern ( - (integer) delta ) ;
    mem [p ].hh .v.RH = x ;
    mem [y ].hh .v.RH = p ;
    y = vpackage ( y , 0 , 1 , 1073741823L ) ;
    mem [y + 1 ].cint = mem [x + 1 ].cint ;
    if ( mem [y + 3 ].cint < h ) 
    {
      p = newkern ( h - mem [y + 3 ].cint ) ;
      mem [p ].hh .v.RH = mem [y + 5 ].hh .v.RH ;
      mem [y + 5 ].hh .v.RH = p ;
      mem [y + 3 ].cint = h ;
    } 
    mem [q + 1 ].hh .v.LH = y ;
    mem [q + 1 ].hh .v.RH = 2 ;
  } 
} 
void 
zmakefraction ( halfword q ) 
{
  makefraction_regmem 
  halfword p, v, x, y, z  ;
  scaled delta, delta1, delta2, shiftup, shiftdown, clr  ;
  if ( mem [q + 1 ].cint == 1073741824L ) 
  mem [q + 1 ].cint = fontinfo [8 + parambase [eqtb [25586 + cursize ]
  .hh .v.RH ]].cint ;
  x = cleanbox ( q + 2 , curstyle + 2 - 2 * ( curstyle / 6 ) , mem [q + 4 ]
  .hh .v.LH ) ;
  z = cleanbox ( q + 3 , 2 * ( curstyle / 2 ) + 3 - 2 * ( curstyle / 6 ) , mem 
  [q + 4 ].hh .v.LH ) ;
  if ( mem [x + 1 ].cint < mem [z + 1 ].cint ) 
  x = rebox ( x , mem [z + 1 ].cint ) ;
  else z = rebox ( z , mem [x + 1 ].cint ) ;
  if ( curstyle < 2 ) 
  {
    shiftup = fontinfo [8 + parambase [eqtb [25585 + cursize ].hh .v.RH ]
    ].cint ;
    shiftdown = fontinfo [11 + parambase [eqtb [25585 + cursize ].hh .v.RH 
    ]].cint ;
  } 
  else {
      
    shiftdown = fontinfo [12 + parambase [eqtb [25585 + cursize ].hh .v.RH 
    ]].cint ;
    if ( mem [q + 1 ].cint != 0 ) 
    shiftup = fontinfo [9 + parambase [eqtb [25585 + cursize ].hh .v.RH ]
    ].cint ;
    else shiftup = fontinfo [10 + parambase [eqtb [25585 + cursize ].hh 
    .v.RH ]].cint ;
  } 
  if ( mem [q + 1 ].cint == 0 ) 
  {
    if ( curstyle < 2 ) 
    clr = 7 * fontinfo [8 + parambase [eqtb [25586 + cursize ].hh .v.RH ]
    ].cint ;
    else clr = 3 * fontinfo [8 + parambase [eqtb [25586 + cursize ].hh 
    .v.RH ]].cint ;
    delta = half ( clr - ( ( shiftup - mem [x + 2 ].cint ) - ( mem [z + 3 ]
    .cint - shiftdown ) ) ) ;
    if ( delta > 0 ) 
    {
      shiftup = shiftup + delta ;
      shiftdown = shiftdown + delta ;
    } 
  } 
  else {
      
    if ( curstyle < 2 ) 
    clr = 3 * mem [q + 1 ].cint ;
    else clr = mem [q + 1 ].cint ;
    delta = half ( mem [q + 1 ].cint ) ;
    delta1 = clr - ( ( shiftup - mem [x + 2 ].cint ) - ( fontinfo [22 + 
    parambase [eqtb [25585 + cursize ].hh .v.RH ]].cint + delta ) ) ;
    delta2 = clr - ( ( fontinfo [22 + parambase [eqtb [25585 + cursize ]
    .hh .v.RH ]].cint - delta ) - ( mem [z + 3 ].cint - shiftdown ) ) ;
    if ( delta1 > 0 ) 
    shiftup = shiftup + delta1 ;
    if ( delta2 > 0 ) 
    shiftdown = shiftdown + delta2 ;
  } 
  v = newnullbox () ;
  mem [v ].hh.b0 = 1 ;
  mem [v + 3 ].cint = shiftup + mem [x + 3 ].cint ;
  mem [v + 2 ].cint = mem [z + 2 ].cint + shiftdown ;
  mem [v + 1 ].cint = mem [x + 1 ].cint ;
  if ( mem [q + 1 ].cint == 0 ) 
  {
    p = newkern ( ( shiftup - mem [x + 2 ].cint ) - ( mem [z + 3 ].cint - 
    shiftdown ) ) ;
    mem [p ].hh .v.RH = z ;
  } 
  else {
      
    y = fractionrule ( mem [q + 1 ].cint ) ;
    p = newkern ( ( fontinfo [22 + parambase [eqtb [25585 + cursize ].hh 
    .v.RH ]].cint - delta ) - ( mem [z + 3 ].cint - shiftdown ) ) ;
    mem [y ].hh .v.RH = p ;
    mem [p ].hh .v.RH = z ;
    p = newkern ( ( shiftup - mem [x + 2 ].cint ) - ( fontinfo [22 + 
    parambase [eqtb [25585 + cursize ].hh .v.RH ]].cint + delta ) ) ;
    mem [p ].hh .v.RH = y ;
  } 
  mem [x ].hh .v.RH = p ;
  mem [v + 5 ].hh .v.RH = x ;
  if ( curstyle < 2 ) 
  delta = fontinfo [20 + parambase [eqtb [25585 + cursize ].hh .v.RH ]]
  .cint ;
  else delta = fontinfo [21 + parambase [eqtb [25585 + cursize ].hh .v.RH 
  ]].cint ;
  x = vardelimiter ( q + 5 , cursize , delta ) ;
  mem [x ].hh .v.RH = v ;
  z = vardelimiter ( q + 4 , cursize , delta ) ;
  mem [v ].hh .v.RH = z ;
  mem [q + 1 ].cint = hpack ( x , 0 , 1 ) ;
} 
scaled 
zmakeop ( halfword q ) 
{
  register scaled Result; makeop_regmem 
  scaled delta  ;
  halfword p, v, x, y, z  ;
  quarterword c  ;
  fourquarters i  ;
  scaled shiftup, shiftdown  ;
  if ( ( mem [q ].hh.b1 == 0 ) && ( curstyle < 2 ) ) 
  mem [q ].hh.b1 = 1 ;
  if ( mem [q + 1 ].hh .v.RH == 1 ) 
  {
    fetch ( q + 1 ) ;
    if ( ( curstyle < 2 ) && ( ( ( curi .b2 ) % 4 ) == 2 ) ) 
    {
      c = curi .b3 ;
      i = fontinfo [charbase [curf ]+ c ].qqqq ;
      if ( ( i .b0 > 0 ) ) 
      {
	curc = c ;
	curi = i ;
	mem [q + 1 ].hh.b1 = c ;
      } 
    } 
    delta = fontinfo [italicbase [curf ]+ ( curi .b2 ) / 4 ].cint ;
    x = cleanbox ( q + 1 , curstyle , mem [q + 4 ].hh .v.LH ) ;
    if ( ( mem [q + 3 ].hh .v.RH != 0 ) && ( mem [q ].hh.b1 != 1 ) ) 
    mem [x + 1 ].cint = mem [x + 1 ].cint - delta ;
    mem [x + 4 ].cint = half ( mem [x + 3 ].cint - mem [x + 2 ].cint ) - 
    fontinfo [22 + parambase [eqtb [25585 + cursize ].hh .v.RH ]].cint ;
    mem [q + 1 ].hh .v.RH = 2 ;
    mem [q + 1 ].hh .v.LH = x ;
  } 
  else delta = 0 ;
  if ( mem [q ].hh.b1 == 1 ) 
  {
    x = cleanbox ( q + 2 , 2 * ( curstyle / 4 ) + 4 + ( curstyle % 2 ) , mem [
    q + 4 ].hh .v.LH ) ;
    y = cleanbox ( q + 1 , curstyle , mem [q + 4 ].hh .v.LH ) ;
    z = cleanbox ( q + 3 , 2 * ( curstyle / 4 ) + 5 , mem [q + 4 ].hh .v.LH 
    ) ;
    v = newnullbox () ;
    mem [v ].hh.b0 = 1 ;
    mem [v + 1 ].cint = mem [y + 1 ].cint ;
    if ( mem [x + 1 ].cint > mem [v + 1 ].cint ) 
    mem [v + 1 ].cint = mem [x + 1 ].cint ;
    if ( mem [z + 1 ].cint > mem [v + 1 ].cint ) 
    mem [v + 1 ].cint = mem [z + 1 ].cint ;
    x = rebox ( x , mem [v + 1 ].cint ) ;
    y = rebox ( y , mem [v + 1 ].cint ) ;
    z = rebox ( z , mem [v + 1 ].cint ) ;
    mem [x + 4 ].cint = half ( delta ) ;
    mem [z + 4 ].cint = - (integer) mem [x + 4 ].cint ;
    mem [v + 3 ].cint = mem [y + 3 ].cint ;
    mem [v + 2 ].cint = mem [y + 2 ].cint ;
    if ( mem [q + 2 ].hh .v.RH == 0 ) 
    {
      deleteglueref ( mem [x + 7 ].hh .v.RH ) ;
      deleteglueref ( mem [x + 7 ].hh .v.LH ) ;
      freenode ( x , 10 ) ;
      mem [v + 5 ].hh .v.RH = y ;
    } 
    else {
	
      shiftup = fontinfo [11 + parambase [eqtb [25586 + cursize ].hh .v.RH 
      ]].cint - mem [x + 2 ].cint ;
      if ( shiftup < fontinfo [9 + parambase [eqtb [25586 + cursize ].hh 
      .v.RH ]].cint ) 
      shiftup = fontinfo [9 + parambase [eqtb [25586 + cursize ].hh .v.RH 
      ]].cint ;
      p = newkern ( shiftup ) ;
      mem [p ].hh .v.RH = y ;
      mem [x ].hh .v.RH = p ;
      p = newkern ( fontinfo [13 + parambase [eqtb [25586 + cursize ].hh 
      .v.RH ]].cint ) ;
      mem [p ].hh .v.RH = x ;
      mem [v + 5 ].hh .v.RH = p ;
      mem [v + 3 ].cint = mem [v + 3 ].cint + fontinfo [13 + parambase [
      eqtb [25586 + cursize ].hh .v.RH ]].cint + mem [x + 3 ].cint + mem 
      [x + 2 ].cint + shiftup ;
    } 
    if ( mem [q + 3 ].hh .v.RH == 0 ) 
    {
      deleteglueref ( mem [z + 7 ].hh .v.RH ) ;
      deleteglueref ( mem [z + 7 ].hh .v.LH ) ;
      freenode ( z , 10 ) ;
    } 
    else {
	
      shiftdown = fontinfo [12 + parambase [eqtb [25586 + cursize ].hh 
      .v.RH ]].cint - mem [z + 3 ].cint ;
      if ( shiftdown < fontinfo [10 + parambase [eqtb [25586 + cursize ]
      .hh .v.RH ]].cint ) 
      shiftdown = fontinfo [10 + parambase [eqtb [25586 + cursize ].hh 
      .v.RH ]].cint ;
      p = newkern ( shiftdown ) ;
      mem [y ].hh .v.RH = p ;
      mem [p ].hh .v.RH = z ;
      p = newkern ( fontinfo [13 + parambase [eqtb [25586 + cursize ].hh 
      .v.RH ]].cint ) ;
      mem [z ].hh .v.RH = p ;
      mem [v + 2 ].cint = mem [v + 2 ].cint + fontinfo [13 + parambase [
      eqtb [25586 + cursize ].hh .v.RH ]].cint + mem [z + 3 ].cint + mem 
      [z + 2 ].cint + shiftdown ;
    } 
    mem [q + 1 ].cint = v ;
  } 
  Result = delta ;
  return Result ;
} 
void 
zmakeord ( halfword q ) 
{
  /* 20 10 */ makeord_regmem 
  integer a  ;
  halfword gp, gq, p, r  ;
  halfword rr  ;
  lab20: if ( ( mem [q + 3 ].hh .v.RH == 0 ) && ( mem [q + 2 ].hh .v.RH == 
  0 ) && ( ( mem [q + 1 ].hh .v.RH == 1 ) || ( mem [q + 1 ].hh .v.RH == 6 
  ) ) ) 
  {
    p = mem [q ].hh .v.RH ;
    if ( p != -1073741823L ) {
	
      if ( ( mem [p ].hh.b0 >= 18 ) && ( mem [p ].hh.b0 <= 24 ) ) {
	  
	if ( mem [p + 1 ].hh.b0 == mem [q + 1 ].hh.b0 ) {
	    
	  if ( mem [p + 1 ].hh .v.RH == 1 ) 
	  {
	    mem [q + 1 ].hh .v.RH = 5 ;
	    fetch ( q + 1 ) ;
	    if ( ( ( curi .b2 ) % 4 ) == 1 ) 
	    {
	      a = ligkernbase [curf ]+ curi .b3 ;
	      curc = mem [p + 1 ].hh.b1 ;
	      curi = fontinfo [a ].qqqq ;
	      if ( curi .b0 > 128 ) 
	      {
		a = ligkernbase [curf ]+ 256 * curi .b2 + curi .b3 + 32768L 
		- 256 * ( 128 ) ;
		curi = fontinfo [a ].qqqq ;
	      } 
	      while ( true ) {
		  
		if ( curi .b1 == curc ) {
		    
		  if ( curi .b0 <= 128 ) {
		      
		    if ( curi .b2 >= 128 ) 
		    {
		      p = newkern ( fontinfo [kernbase [curf ]+ 256 * curi 
		      .b2 + curi .b3 ].cint ) ;
		      mem [p ].hh .v.RH = mem [q ].hh .v.RH ;
		      mem [q ].hh .v.RH = p ;
		      return ;
		    } 
		    else {
			
		      {
			if ( interrupt != 0 ) 
			pauseforinstructions () ;
		      } 
		      switch ( curi .b2 ) 
		      {case 1 : 
		      case 5 : 
			mem [q + 1 ].hh.b1 = curi .b3 ;
			break ;
		      case 2 : 
		      case 6 : 
			mem [p + 1 ].hh.b1 = curi .b3 ;
			break ;
		      case 3 : 
		      case 7 : 
		      case 11 : 
			{
			  r = newnoad () ;
			  mem [r + 1 ].hh.b1 = curi .b3 ;
			  mem [r + 1 ].hh.b0 = mem [q + 1 ].hh.b0 ;
			  mem [q ].hh .v.RH = r ;
			  mem [r ].hh .v.RH = p ;
			  if ( curi .b2 < 11 ) 
			  mem [r + 1 ].hh .v.RH = 1 ;
			  else mem [r + 1 ].hh .v.RH = 5 ;
			} 
			break ;
			default: 
			{
			  mem [q ].hh .v.RH = mem [p ].hh .v.RH ;
			  mem [q + 1 ].hh.b1 = curi .b3 ;
			  mem [q + 3 ]= mem [p + 3 ];
			  mem [q + 2 ]= mem [p + 2 ];
			  freenode ( p , 5 ) ;
			} 
			break ;
		      } 
		      if ( curi .b2 > 3 ) 
		      return ;
		      mem [q + 1 ].hh .v.RH = 1 ;
		      goto lab20 ;
		    } 
		  } 
		} 
		if ( curi .b0 >= 128 ) 
		return ;
		a = a + curi .b0 + 1 ;
		curi = fontinfo [a ].qqqq ;
	      } 
	    } 
	  } 
	  else if ( mem [p + 1 ].hh .v.RH == 6 ) 
	  {
	    mem [q + 1 ].hh .v.RH = 7 ;
	    fetch ( p + 1 ) ;
	    a = curc ;
	    fetch ( q + 1 ) ;
	    if ( ( ( curi .b2 ) % 4 ) == 1 ) 
	    {
	      curc = a ;
	      a = ligkernbase [curf ]+ curi .b3 ;
	      do {
		  curi = fontinfo [a ].qqqq ;
		if ( curi .b1 == curc ) {
		    
		  if ( curi .b2 < 128 ) 
		  {
		    gp = fontglue [curf ];
		    rr = curi .b3 ;
		    if ( gp != -1073741823L ) 
		    {
		      while ( ( ( mem [gp ].hh.b0 != rr ) && ( mem [gp ]
		      .hh .v.RH != -1073741823L ) ) ) {
			  
			gp = mem [gp ].hh .v.RH ;
		      } 
		      gq = mem [gp + 1 ].hh .v.LH ;
		    } 
		    else {
			
		      gp = getnode ( 2 ) ;
		      fontglue [curf ]= gp ;
		      gq = -1073741823L ;
		    } 
		    if ( gq == -1073741823L ) 
		    {
		      mem [gp ].hh.b0 = rr ;
		      gq = newspec ( membot ) ;
		      mem [gp + 1 ].hh .v.LH = gq ;
		      a = extenbase [curf ]+ ( rr ) * 3 ;
		      mem [gq + 1 ].cint = fontinfo [a ].cint ;
		      mem [gq + 2 ].cint = fontinfo [a + 1 ].cint ;
		      mem [gq + 3 ].cint = fontinfo [a + 2 ].cint ;
		      incr ( mem [gq ].hh .v.RH ) ;
		      mem [gp ].hh .v.RH = getnode ( 2 ) ;
		      gp = mem [gp ].hh .v.RH ;
		      mem [gp + 1 ].hh .v.LH = -1073741823L ;
		      mem [gp ].hh .v.RH = -1073741823L ;
		    } 
		    p = newglue ( gq ) ;
		    mem [p ].hh .v.RH = mem [q ].hh .v.RH ;
		    mem [q ].hh .v.RH = p ;
		    return ;
		  } 
		  else {
		      
		    p = newkern ( fontinfo [kernbase [curf ]+ 256 * curi 
		    .b2 + curi .b3 ].cint ) ;
		    mem [p ].hh .v.RH = mem [q ].hh .v.RH ;
		    mem [q ].hh .v.RH = p ;
		    return ;
		  } 
		} 
		incr ( a ) ;
	      } while ( ! ( curi .b0 >= 128 ) ) ;
	    } 
	  } 
	} 
      } 
    } 
  } 
} 
void 
zmakescripts ( halfword q , scaled delta ) 
{
  makescripts_regmem 
  halfword p, x, y, z  ;
  scaled shiftup, shiftdown, clr  ;
  smallnumber t  ;
  p = mem [q + 1 ].cint ;
  if ( ( p >= himemmin ) ) 
  {
    shiftup = 0 ;
    shiftdown = 0 ;
  } 
  else {
      
    z = hpack ( p , 0 , 1 ) ;
    if ( curstyle < 4 ) 
    t = 16 ;
    else t = 32 ;
    shiftup = mem [z + 3 ].cint - fontinfo [18 + parambase [eqtb [25585 + 
    t ].hh .v.RH ]].cint ;
    shiftdown = mem [z + 2 ].cint + fontinfo [19 + parambase [eqtb [25585 
    + t ].hh .v.RH ]].cint ;
    deleteglueref ( mem [z + 7 ].hh .v.RH ) ;
    deleteglueref ( mem [z + 7 ].hh .v.LH ) ;
    freenode ( z , 10 ) ;
  } 
  if ( mem [q + 2 ].hh .v.RH == 0 ) 
  {
    x = cleanbox ( q + 3 , 2 * ( curstyle / 4 ) + 5 , mem [q + 4 ].hh .v.LH 
    ) ;
    mem [x + 1 ].cint = mem [x + 1 ].cint + eqtb [29050 ].cint ;
    if ( shiftdown < fontinfo [16 + parambase [eqtb [25585 + cursize ].hh 
    .v.RH ]].cint ) 
    shiftdown = fontinfo [16 + parambase [eqtb [25585 + cursize ].hh .v.RH 
    ]].cint ;
    clr = mem [x + 3 ].cint - ( abs ( fontinfo [5 + parambase [eqtb [
    25585 + cursize ].hh .v.RH ]].cint * 4 ) / 5 ) ;
    if ( shiftdown < clr ) 
    shiftdown = clr ;
    mem [x + 4 ].cint = shiftdown ;
  } 
  else {
      
    {
      x = cleanbox ( q + 2 , 2 * ( curstyle / 4 ) + 4 + ( curstyle % 2 ) , mem 
      [q + 4 ].hh .v.LH ) ;
      mem [x + 1 ].cint = mem [x + 1 ].cint + eqtb [29050 ].cint ;
      if ( odd ( curstyle ) ) 
      clr = fontinfo [15 + parambase [eqtb [25585 + cursize ].hh .v.RH ]]
      .cint ;
      else if ( curstyle < 2 ) 
      clr = fontinfo [13 + parambase [eqtb [25585 + cursize ].hh .v.RH ]]
      .cint ;
      else clr = fontinfo [14 + parambase [eqtb [25585 + cursize ].hh 
      .v.RH ]].cint ;
      if ( shiftup < clr ) 
      shiftup = clr ;
      clr = mem [x + 2 ].cint + ( abs ( fontinfo [5 + parambase [eqtb [
      25585 + cursize ].hh .v.RH ]].cint ) / 4 ) ;
      if ( shiftup < clr ) 
      shiftup = clr ;
    } 
    if ( mem [q + 3 ].hh .v.RH == 0 ) 
    mem [x + 4 ].cint = - (integer) shiftup ;
    else {
	
      y = cleanbox ( q + 3 , 2 * ( curstyle / 4 ) + 5 , mem [q + 4 ].hh 
      .v.LH ) ;
      mem [y + 1 ].cint = mem [y + 1 ].cint + eqtb [29050 ].cint ;
      if ( shiftdown < fontinfo [17 + parambase [eqtb [25585 + cursize ]
      .hh .v.RH ]].cint ) 
      shiftdown = fontinfo [17 + parambase [eqtb [25585 + cursize ].hh 
      .v.RH ]].cint ;
      clr = 4 * fontinfo [8 + parambase [eqtb [25586 + cursize ].hh .v.RH 
      ]].cint - ( ( shiftup - mem [x + 2 ].cint ) - ( mem [y + 3 ].cint 
      - shiftdown ) ) ;
      if ( clr > 0 ) 
      {
	shiftdown = shiftdown + clr ;
	clr = ( abs ( fontinfo [5 + parambase [eqtb [25585 + cursize ].hh 
	.v.RH ]].cint * 4 ) / 5 ) - ( shiftup - mem [x + 2 ].cint ) ;
	if ( clr > 0 ) 
	{
	  shiftup = shiftup + clr ;
	  shiftdown = shiftdown - clr ;
	} 
      } 
      mem [x + 4 ].cint = delta ;
      p = newkern ( ( shiftup - mem [x + 2 ].cint ) - ( mem [y + 3 ].cint 
      - shiftdown ) ) ;
      mem [x ].hh .v.RH = p ;
      mem [p ].hh .v.RH = y ;
      x = vpackage ( x , 0 , 1 , 1073741823L ) ;
      mem [x + 4 ].cint = shiftdown ;
    } 
  } 
  if ( mem [q + 1 ].cint == -1073741823L ) 
  mem [q + 1 ].cint = x ;
  else {
      
    p = mem [q + 1 ].cint ;
    while ( mem [p ].hh .v.RH != -1073741823L ) p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = x ;
  } 
} 
smallnumber 
zmakeleftright ( halfword q , smallnumber style , scaled maxd , scaled maxh ) 
{
  register smallnumber Result; makeleftright_regmem 
  scaled delta, delta1, delta2  ;
  if ( style < 4 ) 
  cursize = 0 ;
  else cursize = 16 * ( ( style - 2 ) / 2 ) ;
  delta2 = maxd + fontinfo [22 + parambase [eqtb [25585 + cursize ].hh 
  .v.RH ]].cint ;
  delta1 = maxh + maxd - delta2 ;
  if ( delta2 > delta1 ) 
  delta1 = delta2 ;
  delta = ( delta1 / 500 ) * eqtb [28480 ].cint ;
  delta2 = delta1 + delta1 - eqtb [29048 ].cint ;
  if ( delta < delta2 ) 
  delta = delta2 ;
  mem [q + 1 ].cint = vardelimiter ( q + 1 , cursize , delta ) ;
  Result = mem [q ].hh.b0 - ( 10 ) ;
  return Result ;
} 
void 
mlisttohlist ( void ) 
{
  /* 21 82 80 81 83 30 */ mlisttohlist_regmem 
  halfword mlist  ;
  boolean penalties  ;
  smallnumber style  ;
  halfword u  ;
  smallnumber savestyle  ;
  halfword q  ;
  halfword r  ;
  smallnumber rtype  ;
  smallnumber t  ;
  halfword p, x, y, z  ;
  integer pen  ;
  smallnumber s  ;
  scaled maxh, maxd  ;
  scaled delta  ;
  mlist = curmlist ;
  penalties = mlistpenalties ;
  style = curstyle ;
  q = mlist ;
  r = -1073741823L ;
  rtype = 19 ;
  maxh = 0 ;
  maxd = 0 ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( fontinfo [6 + parambase [eqtb [25585 + cursize ].hh 
    .v.RH ]].cint , 18 ) ;
  } 
  while ( q != -1073741823L ) {
      
    lab21: delta = 0 ;
    switch ( mem [q ].hh.b0 ) 
    {case 20 : 
      switch ( rtype ) 
      {case 20 : 
      case 19 : 
      case 21 : 
      case 22 : 
      case 24 : 
      case 32 : 
	{
	  mem [q ].hh.b0 = 18 ;
	  goto lab21 ;
	} 
	break ;
	default: 
	;
	break ;
      } 
      break ;
    case 21 : 
    case 23 : 
    case 24 : 
    case 33 : 
      {
	if ( rtype == 20 ) 
	mem [r ].hh.b0 = 18 ;
	if ( mem [q ].hh.b0 == 33 ) 
	goto lab80 ;
      } 
      break ;
    case 32 : 
      goto lab80 ;
      break ;
    case 27 : 
      {
	makefraction ( q ) ;
	goto lab82 ;
      } 
      break ;
    case 19 : 
      {
	delta = makeop ( q ) ;
	if ( mem [q ].hh.b1 == 1 ) 
	goto lab82 ;
      } 
      break ;
    case 18 : 
      makeord ( q ) ;
      break ;
    case 22 : 
    case 25 : 
      ;
      break ;
    case 26 : 
      makeradical ( q ) ;
      break ;
    case 29 : 
      makeover ( q ) ;
      break ;
    case 28 : 
      makeunder ( q ) ;
      break ;
    case 30 : 
      makemathaccent ( q ) ;
      break ;
    case 31 : 
      makevcenter ( q ) ;
      break ;
    case 16 : 
      {
	curstyle = mem [q ].hh.b1 ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( fontinfo [6 + parambase [eqtb [25585 + cursize ]
	  .hh .v.RH ]].cint , 18 ) ;
	} 
	goto lab81 ;
      } 
      break ;
    case 17 : 
      {
	switch ( curstyle / 2 ) 
	{case 0 : 
	  {
	    p = mem [q + 1 ].hh .v.LH ;
	    mem [q + 1 ].hh .v.LH = -1073741823L ;
	  } 
	  break ;
	case 1 : 
	  {
	    p = mem [q + 1 ].hh .v.RH ;
	    mem [q + 1 ].hh .v.RH = -1073741823L ;
	  } 
	  break ;
	case 2 : 
	  {
	    p = mem [q + 2 ].hh .v.LH ;
	    mem [q + 2 ].hh .v.LH = -1073741823L ;
	  } 
	  break ;
	case 3 : 
	  {
	    p = mem [q + 2 ].hh .v.RH ;
	    mem [q + 2 ].hh .v.RH = -1073741823L ;
	  } 
	  break ;
	} 
	flushnodelist ( mem [q + 1 ].hh .v.LH ) ;
	flushnodelist ( mem [q + 1 ].hh .v.RH ) ;
	flushnodelist ( mem [q + 2 ].hh .v.LH ) ;
	flushnodelist ( mem [q + 2 ].hh .v.RH ) ;
	mem [q ].hh.b0 = 16 ;
	mem [q ].hh.b1 = curstyle ;
	mem [q + 1 ].cint = 0 ;
	mem [q + 2 ].cint = 0 ;
	if ( p != -1073741823L ) 
	{
	  z = mem [q ].hh .v.RH ;
	  mem [q ].hh .v.RH = p ;
	  while ( mem [p ].hh .v.RH != -1073741823L ) p = mem [p ].hh 
	  .v.RH ;
	  mem [p ].hh .v.RH = z ;
	} 
	goto lab81 ;
      } 
      break ;
    case 4 : 
    case 6 : 
    case 7 : 
    case 10 : 
    case 14 : 
    case 9 : 
      goto lab81 ;
      break ;
    case 3 : 
      {
	if ( mem [q + 3 ].cint > maxh ) 
	maxh = mem [q + 3 ].cint ;
	if ( mem [q + 2 ].cint > maxd ) 
	maxd = mem [q + 2 ].cint ;
	goto lab81 ;
      } 
      break ;
    case 12 : 
      {
	if ( mem [q ].hh.b1 == 99 ) 
	{
	  x = mem [q + 1 ].hh .v.LH ;
	  y = mathglue ( x , curmu ) ;
	  deleteglueref ( x ) ;
	  mem [q + 1 ].hh .v.LH = y ;
	  mem [q ].hh.b1 = 0 ;
	} 
	else if ( ( cursize != 0 ) && ( mem [q ].hh.b1 == 98 ) ) 
	{
	  p = mem [q ].hh .v.RH ;
	  if ( p != -1073741823L ) {
	      
	    if ( ( mem [p ].hh.b0 == 12 ) || ( mem [p ].hh.b0 == 13 ) ) 
	    {
	      mem [q ].hh .v.RH = mem [p ].hh .v.RH ;
	      mem [p ].hh .v.RH = -1073741823L ;
	      flushnodelist ( p ) ;
	    } 
	  } 
	} 
	goto lab81 ;
      } 
      break ;
    case 13 : 
      {
	mathkern ( q , curmu ) ;
	goto lab81 ;
      } 
      break ;
    case 5 : 
      goto lab81 ;
      break ;
      default: 
      confusion ( 945 ) ;
      break ;
    } 
    switch ( mem [q + 1 ].hh .v.RH ) 
    {case 1 : 
    case 5 : 
    case 6 : 
    case 7 : 
      {
	fetch ( q + 1 ) ;
	if ( ( curi .b0 > 0 ) ) 
	{
	  delta = fontinfo [italicbase [curf ]+ ( curi .b2 ) / 4 ].cint ;
	  p = newcharacter ( curf , curc ) ;
	  u = p ;
	  if ( fontdir [curf ]!= 0 ) 
	  {
	    mem [u ].hh .v.RH = getavail () ;
	    u = mem [u ].hh .v.RH ;
	    mem [u ].hh .v.LH = mem [q + 4 ].hh .v.LH ;
	  } 
	  if ( ( ( mem [q + 1 ].hh .v.RH == 5 ) || ( mem [q + 1 ].hh .v.RH 
	  == 7 ) ) && ( fontinfo [2 + parambase [curf ]].cint != 0 ) ) 
	  delta = 0 ;
	  if ( ( mem [q + 3 ].hh .v.RH == 0 ) && ( delta != 0 ) ) 
	  {
	    mem [u ].hh .v.RH = newkern ( delta ) ;
	    delta = 0 ;
	  } 
	} 
	else p = -1073741823L ;
      } 
      break ;
    case 0 : 
      p = -1073741823L ;
      break ;
    case 2 : 
      p = mem [q + 1 ].hh .v.LH ;
      break ;
    case 3 : 
      p = shiftsubexpbox ( q + 1 ) ;
      break ;
    case 4 : 
      {
	curmlist = mem [q + 1 ].hh .v.LH ;
	savestyle = curstyle ;
	mlistpenalties = false ;
	mlisttohlist () ;
	curstyle = savestyle ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( fontinfo [6 + parambase [eqtb [25585 + cursize ]
	  .hh .v.RH ]].cint , 18 ) ;
	} 
	p = hpack ( mem [memtop - 3 ].hh .v.RH , 0 , 1 ) ;
      } 
      break ;
      default: 
      confusion ( 947 ) ;
      break ;
    } 
    mem [q + 1 ].cint = p ;
    if ( ( mem [q + 3 ].hh .v.RH == 0 ) && ( mem [q + 2 ].hh .v.RH == 0 ) 
    ) 
    goto lab82 ;
    makescripts ( q , delta ) ;
    lab82: z = hpack ( mem [q + 1 ].cint , 0 , 1 ) ;
    if ( mem [z + 3 ].cint > maxh ) 
    maxh = mem [z + 3 ].cint ;
    if ( mem [z + 2 ].cint > maxd ) 
    maxd = mem [z + 2 ].cint ;
    deleteglueref ( mem [z + 7 ].hh .v.RH ) ;
    deleteglueref ( mem [z + 7 ].hh .v.LH ) ;
    freenode ( z , 10 ) ;
    lab80: r = q ;
    rtype = mem [r ].hh.b0 ;
    lab81: q = mem [q ].hh .v.RH ;
  } 
  if ( rtype == 20 ) 
  mem [r ].hh.b0 = 18 ;
  p = memtop - 3 ;
  mem [p ].hh .v.RH = -1073741823L ;
  q = mlist ;
  rtype = 0 ;
  curstyle = style ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( fontinfo [6 + parambase [eqtb [25585 + cursize ].hh 
    .v.RH ]].cint , 18 ) ;
  } 
  while ( q != -1073741823L ) {
      
    t = 18 ;
    s = 5 ;
    pen = 10000 ;
    switch ( mem [q ].hh.b0 ) 
    {case 19 : 
    case 22 : 
    case 23 : 
    case 24 : 
    case 25 : 
      t = mem [q ].hh.b0 ;
      break ;
    case 20 : 
      {
	t = 20 ;
	pen = eqtb [28471 ].cint ;
      } 
      break ;
    case 21 : 
      {
	t = 21 ;
	pen = eqtb [28472 ].cint ;
      } 
      break ;
    case 18 : 
    case 31 : 
    case 29 : 
    case 28 : 
      ;
      break ;
    case 26 : 
      s = 6 ;
      break ;
    case 30 : 
      s = 6 ;
      break ;
    case 27 : 
      {
	t = 25 ;
	s = 6 ;
      } 
      break ;
    case 32 : 
    case 33 : 
      t = makeleftright ( q , style , maxd , maxh ) ;
      break ;
    case 16 : 
      {
	curstyle = mem [q ].hh.b1 ;
	s = 3 ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( fontinfo [6 + parambase [eqtb [25585 + cursize ]
	  .hh .v.RH ]].cint , 18 ) ;
	} 
	goto lab83 ;
      } 
      break ;
    case 10 : 
    case 14 : 
    case 3 : 
    case 9 : 
    case 7 : 
    case 4 : 
    case 6 : 
    case 12 : 
    case 13 : 
      {
	mem [p ].hh .v.RH = q ;
	p = q ;
	q = mem [q ].hh .v.RH ;
	mem [p ].hh .v.RH = -1073741823L ;
	goto lab30 ;
      } 
      break ;
    case 5 : 
      {
	mem [p ].hh .v.RH = q ;
	p = q ;
	q = mem [q ].hh .v.RH ;
	mem [p ].hh .v.RH = -1073741823L ;
	goto lab30 ;
      } 
      break ;
      default: 
      confusion ( 948 ) ;
      break ;
    } 
    if ( rtype > 0 ) 
    {
      switch ( strpool [rtype * 8 + t + magicoffset ]) 
      {case 48 : 
	x = 0 ;
	break ;
      case 49 : 
	if ( curstyle < 4 ) 
	x = 17 ;
	else x = 0 ;
	break ;
      case 50 : 
	x = 17 ;
	break ;
      case 51 : 
	if ( curstyle < 4 ) 
	x = 18 ;
	else x = 0 ;
	break ;
      case 52 : 
	if ( curstyle < 4 ) 
	x = 19 ;
	else x = 0 ;
	break ;
	default: 
	confusion ( 950 ) ;
	break ;
      } 
      if ( x != 0 ) 
      {
	y = mathglue ( eqtb [24527 + x ].hh .v.RH , curmu ) ;
	z = newglue ( y ) ;
	mem [y ].hh .v.RH = -1073741823L ;
	mem [p ].hh .v.RH = z ;
	p = z ;
	mem [z ].hh.b1 = x + 1 ;
      } 
    } 
    if ( mem [q + 1 ].cint != -1073741823L ) 
    {
      mem [p ].hh .v.RH = mem [q + 1 ].cint ;
      do {
	  p = mem [p ].hh .v.RH ;
      } while ( ! ( mem [p ].hh .v.RH == -1073741823L ) ) ;
    } 
    if ( penalties ) {
	
      if ( mem [q ].hh .v.RH != -1073741823L ) {
	  
	if ( pen < 10000 ) 
	{
	  rtype = mem [mem [q ].hh .v.RH ].hh.b0 ;
	  if ( rtype != 14 ) {
	      
	    if ( rtype != 21 ) 
	    {
	      z = newpenalty ( pen ) ;
	      mem [p ].hh .v.RH = z ;
	      p = z ;
	    } 
	  } 
	} 
      } 
    } 
    rtype = t ;
    lab83: r = q ;
    q = mem [q ].hh .v.RH ;
    freenode ( r , s ) ;
    lab30: ;
  } 
  p = newnullbox () ;
  mem [p ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
  adjusthlist ( p , false ) ;
  mem [memtop - 3 ].hh .v.RH = mem [p ].hh .v.RH ;
  deleteglueref ( mem [p + 7 ].hh .v.RH ) ;
  deleteglueref ( mem [p + 7 ].hh .v.LH ) ;
  freenode ( p , 10 ) ;
} 
void 
pushalignment ( void ) 
{
  pushalignment_regmem 
  halfword p  ;
  p = getnode ( 5 ) ;
  mem [p ].hh .v.RH = alignptr ;
  mem [p ].hh .v.LH = curalign ;
  mem [p + 1 ].hh .v.LH = mem [memtop - 8 ].hh .v.RH ;
  mem [p + 1 ].hh .v.RH = curspan ;
  mem [p + 2 ].cint = curloop ;
  mem [p + 3 ].cint = alignstate ;
  mem [p + 4 ].hh .v.LH = curhead ;
  mem [p + 4 ].hh .v.RH = curtail ;
  alignptr = p ;
  curhead = getavail () ;
} 
void 
popalignment ( void ) 
{
  popalignment_regmem 
  halfword p  ;
  {
    mem [curhead ].hh .v.RH = avail ;
    avail = curhead ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  p = alignptr ;
  curtail = mem [p + 4 ].hh .v.RH ;
  curhead = mem [p + 4 ].hh .v.LH ;
  alignstate = mem [p + 3 ].cint ;
  curloop = mem [p + 2 ].cint ;
  curspan = mem [p + 1 ].hh .v.RH ;
  mem [memtop - 8 ].hh .v.RH = mem [p + 1 ].hh .v.LH ;
  curalign = mem [p ].hh .v.LH ;
  alignptr = mem [p ].hh .v.RH ;
  freenode ( p , 5 ) ;
} 
void 
getpreambletoken ( void ) 
{
  /* 20 */ getpreambletoken_regmem 
  lab20: gettoken () ;
  while ( ( curchr == 256 ) && ( curcmd == 4 ) ) {
      
    gettoken () ;
    if ( curcmd > 115 ) 
    {
      expand () ;
      gettoken () ;
    } 
  } 
  if ( curcmd == 9 ) 
  fatalerror ( 633 ) ;
  if ( ( curcmd == 83 ) && ( curchr == 24538 ) ) 
  {
    scanoptionalequals () ;
    scanglue ( 2 ) ;
    if ( eqtb [28505 ].cint > 0 ) 
    geqdefine ( 24538 , 132 , curval ) ;
    else eqdefine ( 24538 , 132 , curval ) ;
    goto lab20 ;
  } 
} 
void 
initalign ( void ) 
{
  /* 30 31 32 22 */ initalign_regmem 
  halfword savecsptr  ;
  halfword p  ;
  savecsptr = curcs ;
  pushalignment () ;
  alignstate = -1000000L ;
  if ( ( curlist .modefield == 233 ) && ( ( curlist .tailfield != curlist 
  .headfield ) || ( curlist .auxfield .cint != -1073741823L ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 721 ) ;
    } 
    printesc ( 558 ) ;
    print ( 951 ) ;
    {
      helpptr = 3 ;
      helpline [2 ]= 952 ;
      helpline [1 ]= 953 ;
      helpline [0 ]= 954 ;
    } 
    error () ;
    flushmath () ;
  } 
  pushnest () ;
  if ( curlist .modefield == 233 ) 
  {
    curlist .modefield = -1 ;
    curlist .auxfield .cint = nest [nestptr - 2 ].auxfield .cint ;
  } 
  else if ( curlist .modefield > 0 ) 
  curlist .modefield = - (integer) curlist .modefield ;
  scanspec ( 6 , false ) ;
  mem [memtop - 8 ].hh .v.RH = -1073741823L ;
  curalign = memtop - 8 ;
  curloop = -1073741823L ;
  scannerstatus = 4 ;
  warningindex = savecsptr ;
  alignstate = -1000000L ;
  while ( true ) {
      
    mem [curalign ].hh .v.RH = newparamglue ( 11 ) ;
    curalign = mem [curalign ].hh .v.RH ;
    if ( curcmd == 5 ) 
    goto lab30 ;
    p = memtop - 4 ;
    mem [p ].hh .v.RH = -1073741823L ;
    while ( true ) {
	
      getpreambletoken () ;
      if ( curcmd == 6 ) 
      goto lab31 ;
      if ( ( curcmd <= 5 ) && ( curcmd >= 4 ) && ( alignstate == -1000000L ) ) 
      {
	if ( ( p == memtop - 4 ) && ( curloop == -1073741823L ) && ( curcmd == 
	4 ) ) 
	curloop = curalign ;
	else {
	    
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 960 ) ;
	  } 
	  {
	    helpptr = 3 ;
	    helpline [2 ]= 961 ;
	    helpline [1 ]= 962 ;
	    helpline [0 ]= 963 ;
	  } 
	  backerror () ;
	  goto lab31 ;
	} 
      } 
      else if ( ( curcmd != 10 ) || ( p != memtop - 4 ) ) 
      {
	mem [p ].hh .v.RH = getavail () ;
	p = mem [p ].hh .v.RH ;
	mem [p ].hh .v.LH = curtok ;
      } 
    } 
    lab31: ;
    mem [curalign ].hh .v.RH = newnullbox () ;
    curalign = mem [curalign ].hh .v.RH ;
    mem [curalign ].hh .v.LH = memtop - 9 ;
    mem [curalign + 1 ].cint = -1073741824L ;
    mem [curalign + 3 ].cint = mem [memtop - 4 ].hh .v.RH ;
    p = memtop - 4 ;
    mem [p ].hh .v.RH = -1073741823L ;
    while ( true ) {
	
      lab22: getpreambletoken () ;
      if ( ( curcmd <= 5 ) && ( curcmd >= 4 ) && ( alignstate == -1000000L ) ) 
      goto lab32 ;
      if ( curcmd == 6 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 964 ) ;
	} 
	{
	  helpptr = 3 ;
	  helpline [2 ]= 961 ;
	  helpline [1 ]= 962 ;
	  helpline [0 ]= 965 ;
	} 
	error () ;
	goto lab22 ;
      } 
      mem [p ].hh .v.RH = getavail () ;
      p = mem [p ].hh .v.RH ;
      mem [p ].hh .v.LH = curtok ;
    } 
    lab32: mem [p ].hh .v.RH = getavail () ;
    p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.LH = 536886430L ;
    mem [curalign + 2 ].cint = mem [memtop - 4 ].hh .v.RH ;
  } 
  lab30: scannerstatus = 0 ;
  newsavelevel ( 6 ) ;
  if ( eqtb [25068 ].hh .v.RH != -1073741823L ) 
  begintokenlist ( eqtb [25068 ].hh .v.RH , 13 ) ;
  alignpeek () ;
} 
void 
zinitspan ( halfword p ) 
{
  initspan_regmem 
  pushnest () ;
  if ( curlist .modefield == -117 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else {
      
    curlist .auxfield .cint = -65536000L ;
    normalparagraph () ;
  } 
  curspan = p ;
} 
void 
initrow ( void ) 
{
  initrow_regmem 
  pushnest () ;
  curlist .modefield = ( -118 ) - curlist .modefield ;
  if ( curlist .modefield == -117 ) 
  curlist .auxfield .hh .v.LH = 0 ;
  else curlist .auxfield .cint = 0 ;
  {
    mem [curlist .tailfield ].hh .v.RH = newglue ( mem [mem [memtop - 8 ]
    .hh .v.RH + 1 ].hh .v.LH ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b1 = 12 ;
  curalign = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
  curtail = curhead ;
  initspan ( curalign ) ;
} 
void 
initcol ( void ) 
{
  initcol_regmem 
  mem [curalign + 5 ].hh .v.LH = curcmd ;
  if ( curcmd == 68 ) 
  alignstate = 0 ;
  else {
      
    backinput () ;
    begintokenlist ( mem [curalign + 3 ].cint , 1 ) ;
  } 
} 
boolean 
fincol ( void ) 
{
  /* 10 */ register boolean Result; fincol_regmem 
  halfword p  ;
  halfword q, r  ;
  halfword s  ;
  halfword u  ;
  scaled w  ;
  glueord o  ;
  halfword n  ;
  if ( curalign == -1073741823L ) 
  confusion ( 966 ) ;
  q = mem [curalign ].hh .v.RH ;
  if ( q == -1073741823L ) 
  confusion ( 966 ) ;
  if ( alignstate < 500000L ) 
  fatalerror ( 633 ) ;
  p = mem [q ].hh .v.RH ;
  if ( ( p == -1073741823L ) && ( mem [curalign + 5 ].hh .v.LH < 257 ) ) {
      
    if ( curloop != -1073741823L ) 
    {
      mem [q ].hh .v.RH = newnullbox () ;
      p = mem [q ].hh .v.RH ;
      mem [p ].hh .v.LH = memtop - 9 ;
      mem [p + 1 ].cint = -1073741824L ;
      curloop = mem [curloop ].hh .v.RH ;
      q = memtop - 4 ;
      r = mem [curloop + 3 ].cint ;
      while ( r != -1073741823L ) {
	  
	mem [q ].hh .v.RH = getavail () ;
	q = mem [q ].hh .v.RH ;
	mem [q ].hh .v.LH = mem [r ].hh .v.LH ;
	r = mem [r ].hh .v.RH ;
      } 
      mem [q ].hh .v.RH = -1073741823L ;
      mem [p + 3 ].cint = mem [memtop - 4 ].hh .v.RH ;
      q = memtop - 4 ;
      r = mem [curloop + 2 ].cint ;
      while ( r != -1073741823L ) {
	  
	mem [q ].hh .v.RH = getavail () ;
	q = mem [q ].hh .v.RH ;
	mem [q ].hh .v.LH = mem [r ].hh .v.LH ;
	r = mem [r ].hh .v.RH ;
      } 
      mem [q ].hh .v.RH = -1073741823L ;
      mem [p + 2 ].cint = mem [memtop - 4 ].hh .v.RH ;
      curloop = mem [curloop ].hh .v.RH ;
      mem [p ].hh .v.RH = newglue ( mem [curloop + 1 ].hh .v.LH ) ;
    } 
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 967 ) ;
      } 
      printesc ( 956 ) ;
      {
	helpptr = 3 ;
	helpline [2 ]= 968 ;
	helpline [1 ]= 969 ;
	helpline [0 ]= 970 ;
      } 
      mem [curalign + 5 ].hh .v.LH = 257 ;
      error () ;
    } 
  } 
  if ( mem [curalign + 5 ].hh .v.LH != 256 ) 
  {
    unsave () ;
    newsavelevel ( 6 ) ;
    {
      if ( curlist .modefield == -117 ) 
      {
	adjusttail = curtail ;
	adjusthlist ( curlist .headfield , false ) ;
	deleteglueref ( curkanjiskip ) ;
	deleteglueref ( curxkanjiskip ) ;
	curkanjiskip = mem [curlist .headfield + 7 ].hh .v.RH ;
	curxkanjiskip = mem [curlist .headfield + 7 ].hh .v.LH ;
	incr ( mem [curkanjiskip ].hh .v.RH ) ;
	incr ( mem [curxkanjiskip ].hh .v.RH ) ;
	u = hpack ( mem [curlist .headfield ].hh .v.RH , 0 , 1 ) ;
	w = mem [u + 1 ].cint ;
	curtail = adjusttail ;
	adjusttail = -1073741823L ;
      } 
      else {
	  
	u = vpackage ( mem [curlist .headfield ].hh .v.RH , 0 , 1 , 0 ) ;
	w = mem [u + 3 ].cint ;
      } 
      n = 0 ;
      if ( curspan != curalign ) 
      {
	q = curspan ;
	do {
	    incr ( n ) ;
	  q = mem [mem [q ].hh .v.RH ].hh .v.RH ;
	} while ( ! ( q == curalign ) ) ;
	if ( n > 65535L ) 
	confusion ( 971 ) ;
	q = curspan ;
	while ( mem [mem [q ].hh .v.LH ].hh .v.RH < n ) q = mem [q ].hh 
	.v.LH ;
	if ( mem [mem [q ].hh .v.LH ].hh .v.RH > n ) 
	{
	  s = getnode ( 2 ) ;
	  mem [s ].hh .v.LH = mem [q ].hh .v.LH ;
	  mem [s ].hh .v.RH = n ;
	  mem [q ].hh .v.LH = s ;
	  mem [s + 1 ].cint = w ;
	} 
	else if ( mem [mem [q ].hh .v.LH + 1 ].cint < w ) 
	mem [mem [q ].hh .v.LH + 1 ].cint = w ;
      } 
      else if ( w > mem [curalign + 1 ].cint ) 
      mem [curalign + 1 ].cint = w ;
      mem [u ].hh.b0 = 15 ;
      mem [u ].hh.b1 = n ;
      if ( totalstretch [3 ]!= 0 ) 
      o = 3 ;
      else if ( totalstretch [2 ]!= 0 ) 
      o = 2 ;
      else if ( totalstretch [1 ]!= 0 ) 
      o = 1 ;
      else o = 0 ;
      mem [u + 5 ].hh.b1 = o ;
      mem [u + 6 ].cint = totalstretch [o ];
      if ( totalshrink [3 ]!= 0 ) 
      o = 3 ;
      else if ( totalshrink [2 ]!= 0 ) 
      o = 2 ;
      else if ( totalshrink [1 ]!= 0 ) 
      o = 1 ;
      else o = 0 ;
      mem [u + 5 ].hh.b0 = o ;
      mem [u + 4 ].cint = totalshrink [o ];
      popnest () ;
      mem [curlist .tailfield ].hh .v.RH = u ;
      curlist .tailfield = u ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newglue ( mem [mem [curalign ]
      .hh .v.RH + 1 ].hh .v.LH ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh.b1 = 12 ;
    if ( mem [curalign + 5 ].hh .v.LH >= 257 ) 
    {
      Result = true ;
      return Result ;
    } 
    initspan ( p ) ;
  } 
  alignstate = 1000000L ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  curalign = p ;
  initcol () ;
  Result = false ;
  return Result ;
} 
void 
finrow ( void ) 
{
  finrow_regmem 
  halfword p  ;
  if ( curlist .modefield == -117 ) 
  {
    adjusthlist ( curlist .headfield , false ) ;
    deleteglueref ( curkanjiskip ) ;
    deleteglueref ( curxkanjiskip ) ;
    curkanjiskip = mem [curlist .headfield + 7 ].hh .v.RH ;
    curxkanjiskip = mem [curlist .headfield + 7 ].hh .v.LH ;
    incr ( mem [curkanjiskip ].hh .v.RH ) ;
    incr ( mem [curxkanjiskip ].hh .v.RH ) ;
    p = hpack ( mem [curlist .headfield ].hh .v.RH , 0 , 1 ) ;
    popnest () ;
    appendtovlist ( p ) ;
    if ( curhead != curtail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [curhead ].hh .v.RH ;
      curlist .tailfield = curtail ;
    } 
  } 
  else {
      
    p = vpackage ( mem [curlist .headfield ].hh .v.RH , 0 , 1 , 1073741823L 
    ) ;
    popnest () ;
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
    curlist .auxfield .hh .v.LH = 1000 ;
  } 
  mem [p ].hh.b0 = 15 ;
  mem [p + 6 ].cint = 0 ;
  if ( eqtb [25068 ].hh .v.RH != -1073741823L ) 
  begintokenlist ( eqtb [25068 ].hh .v.RH , 13 ) ;
  alignpeek () ;
} 
void 
finalign ( void ) 
{
  finalign_regmem 
  halfword p, q, r, s, u, v, z  ;
  scaled t, w  ;
  scaled o  ;
  halfword n  ;
  scaled rulesave  ;
  memoryword auxsave  ;
  if ( curgroup != 6 ) 
  confusion ( 972 ) ;
  unsave () ;
  if ( curgroup != 6 ) 
  confusion ( 973 ) ;
  unsave () ;
  if ( nest [nestptr - 1 ].modefield == 233 ) 
  o = eqtb [29053 ].cint ;
  else o = 0 ;
  q = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
  do {
      flushlist ( mem [q + 3 ].cint ) ;
    flushlist ( mem [q + 2 ].cint ) ;
    p = mem [mem [q ].hh .v.RH ].hh .v.RH ;
    if ( mem [q + 1 ].cint == -1073741824L ) 
    {
      mem [q + 1 ].cint = 0 ;
      r = mem [q ].hh .v.RH ;
      s = mem [r + 1 ].hh .v.LH ;
      if ( s != membot ) 
      {
	incr ( mem [membot ].hh .v.RH ) ;
	deleteglueref ( s ) ;
	mem [r + 1 ].hh .v.LH = membot ;
      } 
    } 
    if ( mem [q ].hh .v.LH != memtop - 9 ) 
    {
      t = mem [q + 1 ].cint + mem [mem [mem [q ].hh .v.RH + 1 ].hh 
      .v.LH + 1 ].cint ;
      r = mem [q ].hh .v.LH ;
      s = memtop - 9 ;
      mem [s ].hh .v.LH = p ;
      n = 1 ;
      do {
	  mem [r + 1 ].cint = mem [r + 1 ].cint - t ;
	u = mem [r ].hh .v.LH ;
	while ( mem [r ].hh .v.RH > n ) {
	    
	  s = mem [s ].hh .v.LH ;
	  n = mem [mem [s ].hh .v.LH ].hh .v.RH + 1 ;
	} 
	if ( mem [r ].hh .v.RH < n ) 
	{
	  mem [r ].hh .v.LH = mem [s ].hh .v.LH ;
	  mem [s ].hh .v.LH = r ;
	  decr ( mem [r ].hh .v.RH ) ;
	  s = r ;
	} 
	else {
	    
	  if ( mem [r + 1 ].cint > mem [mem [s ].hh .v.LH + 1 ].cint ) 
	  mem [mem [s ].hh .v.LH + 1 ].cint = mem [r + 1 ].cint ;
	  freenode ( r , 2 ) ;
	} 
	r = u ;
      } while ( ! ( r == memtop - 9 ) ) ;
    } 
    mem [q ].hh.b0 = 15 ;
    mem [q ].hh.b1 = 0 ;
    mem [q + 3 ].cint = 0 ;
    mem [q + 2 ].cint = 0 ;
    mem [q + 5 ].hh.b1 = 0 ;
    mem [q + 5 ].hh.b0 = 0 ;
    mem [q + 6 ].cint = 0 ;
    mem [q + 4 ].cint = 0 ;
    q = p ;
  } while ( ! ( q == -1073741823L ) ) ;
  saveptr = saveptr - 2 ;
  packbeginline = - (integer) curlist .mlfield ;
  if ( curlist .modefield == -1 ) 
  {
    rulesave = eqtb [29054 ].cint ;
    eqtb [29054 ].cint = 0 ;
    z = newnullbox () ;
    mem [z ].hh .v.RH = mem [memtop - 8 ].hh .v.RH ;
    adjusthlist ( z , false ) ;
    deleteglueref ( curkanjiskip ) ;
    deleteglueref ( curxkanjiskip ) ;
    curkanjiskip = mem [z + 7 ].hh .v.RH ;
    curxkanjiskip = mem [z + 7 ].hh .v.LH ;
    incr ( mem [curkanjiskip ].hh .v.RH ) ;
    incr ( mem [curxkanjiskip ].hh .v.RH ) ;
    p = hpack ( mem [memtop - 8 ].hh .v.RH , savestack [saveptr + 1 ].cint 
    , savestack [saveptr + 0 ].cint ) ;
    eqtb [29054 ].cint = rulesave ;
    deleteglueref ( mem [z + 7 ].hh .v.RH ) ;
    deleteglueref ( mem [z + 7 ].hh .v.LH ) ;
    freenode ( z , 10 ) ;
  } 
  else {
      
    q = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
    do {
	mem [q + 3 ].cint = mem [q + 1 ].cint ;
      mem [q + 1 ].cint = 0 ;
      q = mem [mem [q ].hh .v.RH ].hh .v.RH ;
    } while ( ! ( q == -1073741823L ) ) ;
    p = vpackage ( mem [memtop - 8 ].hh .v.RH , savestack [saveptr + 1 ]
    .cint , savestack [saveptr + 0 ].cint , 1073741823L ) ;
    q = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
    do {
	mem [q + 1 ].cint = mem [q + 3 ].cint ;
      mem [q + 3 ].cint = 0 ;
      q = mem [mem [q ].hh .v.RH ].hh .v.RH ;
    } while ( ! ( q == -1073741823L ) ) ;
  } 
  packbeginline = 0 ;
  q = mem [curlist .headfield ].hh .v.RH ;
  s = curlist .headfield ;
  while ( q != -1073741823L ) {
      
    if ( ! ( q >= himemmin ) ) {
	
      if ( mem [q ].hh.b0 == 15 ) 
      {
	if ( curlist .modefield == -1 ) 
	{
	  mem [q ].hh.b0 = 0 ;
	  mem [q + 1 ].cint = mem [p + 1 ].cint ;
	} 
	else {
	    
	  mem [q ].hh.b0 = 1 ;
	  mem [q + 3 ].cint = mem [p + 3 ].cint ;
	} 
	mem [q ].hh.b1 = abs ( curlist .dirfield ) ;
	mem [q + 5 ].hh.b1 = mem [p + 5 ].hh.b1 ;
	mem [q + 5 ].hh.b0 = mem [p + 5 ].hh.b0 ;
	mem [q + 6 ].gr = mem [p + 6 ].gr ;
	mem [q + 4 ].cint = o ;
	r = mem [mem [q + 5 ].hh .v.RH ].hh .v.RH ;
	s = mem [mem [p + 5 ].hh .v.RH ].hh .v.RH ;
	do {
	    n = mem [r ].hh.b1 ;
	  t = mem [s + 1 ].cint ;
	  w = t ;
	  u = memtop - 4 ;
	  while ( n > 0 ) {
	      
	    decr ( n ) ;
	    s = mem [s ].hh .v.RH ;
	    v = mem [s + 1 ].hh .v.LH ;
	    mem [u ].hh .v.RH = newglue ( v ) ;
	    u = mem [u ].hh .v.RH ;
	    mem [u ].hh.b1 = 12 ;
	    t = t + mem [v + 1 ].cint ;
	    if ( mem [p + 5 ].hh.b0 == 1 ) 
	    {
	      if ( mem [v ].hh.b0 == mem [p + 5 ].hh.b1 ) 
	      t = t + round ( mem [p + 6 ].gr * mem [v + 2 ].cint ) ;
	    } 
	    else if ( mem [p + 5 ].hh.b0 == 2 ) 
	    {
	      if ( mem [v ].hh.b1 == mem [p + 5 ].hh.b1 ) 
	      t = t - round ( mem [p + 6 ].gr * mem [v + 3 ].cint ) ;
	    } 
	    s = mem [s ].hh .v.RH ;
	    mem [u ].hh .v.RH = newnullbox () ;
	    u = mem [u ].hh .v.RH ;
	    t = t + mem [s + 1 ].cint ;
	    if ( curlist .modefield == -1 ) 
	    mem [u + 1 ].cint = mem [s + 1 ].cint ;
	    else {
		
	      mem [u ].hh.b0 = 1 ;
	      mem [u + 3 ].cint = mem [s + 1 ].cint ;
	    } 
	    mem [u ].hh.b1 = abs ( curlist .dirfield ) ;
	  } 
	  if ( curlist .modefield == -1 ) 
	  {
	    mem [r + 3 ].cint = mem [q + 3 ].cint ;
	    mem [r + 2 ].cint = mem [q + 2 ].cint ;
	    if ( t == mem [r + 1 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 0 ;
	      mem [r + 5 ].hh.b1 = 0 ;
	      mem [r + 6 ].gr = 0.0 ;
	    } 
	    else if ( t > mem [r + 1 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 1 ;
	      if ( mem [r + 6 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else mem [r + 6 ].gr = ( t - mem [r + 1 ].cint ) / ((double) 
	      mem [r + 6 ].cint ) ;
	    } 
	    else {
		
	      mem [r + 5 ].hh.b1 = mem [r + 5 ].hh.b0 ;
	      mem [r + 5 ].hh.b0 = 2 ;
	      if ( mem [r + 4 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else if ( ( mem [r + 5 ].hh.b1 == 0 ) && ( mem [r + 1 ].cint 
	      - t > mem [r + 4 ].cint ) ) 
	      mem [r + 6 ].gr = 1.0 ;
	      else mem [r + 6 ].gr = ( mem [r + 1 ].cint - t ) / ((double) 
	      mem [r + 4 ].cint ) ;
	    } 
	    mem [r + 1 ].cint = w ;
	    mem [r ].hh.b0 = 0 ;
	    mem [r ].hh.b1 = abs ( curlist .dirfield ) ;
	  } 
	  else {
	      
	    mem [r + 1 ].cint = mem [q + 1 ].cint ;
	    if ( t == mem [r + 3 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 0 ;
	      mem [r + 5 ].hh.b1 = 0 ;
	      mem [r + 6 ].gr = 0.0 ;
	    } 
	    else if ( t > mem [r + 3 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 1 ;
	      if ( mem [r + 6 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else mem [r + 6 ].gr = ( t - mem [r + 3 ].cint ) / ((double) 
	      mem [r + 6 ].cint ) ;
	    } 
	    else {
		
	      mem [r + 5 ].hh.b1 = mem [r + 5 ].hh.b0 ;
	      mem [r + 5 ].hh.b0 = 2 ;
	      if ( mem [r + 4 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else if ( ( mem [r + 5 ].hh.b1 == 0 ) && ( mem [r + 3 ].cint 
	      - t > mem [r + 4 ].cint ) ) 
	      mem [r + 6 ].gr = 1.0 ;
	      else mem [r + 6 ].gr = ( mem [r + 3 ].cint - t ) / ((double) 
	      mem [r + 4 ].cint ) ;
	    } 
	    mem [r + 3 ].cint = w ;
	    mem [r ].hh.b0 = 1 ;
	    mem [r ].hh.b1 = abs ( curlist .dirfield ) ;
	  } 
	  mem [r + 4 ].cint = 0 ;
	  if ( u != memtop - 4 ) 
	  {
	    mem [u ].hh .v.RH = mem [r ].hh .v.RH ;
	    mem [r ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	    r = u ;
	  } 
	  r = mem [mem [r ].hh .v.RH ].hh .v.RH ;
	  s = mem [mem [s ].hh .v.RH ].hh .v.RH ;
	} while ( ! ( r == -1073741823L ) ) ;
      } 
      else if ( mem [q ].hh.b0 == 3 ) 
      {
	if ( ( mem [q + 1 ].cint == -1073741824L ) ) 
	mem [q + 1 ].cint = mem [p + 1 ].cint ;
	if ( ( mem [q + 3 ].cint == -1073741824L ) ) 
	mem [q + 3 ].cint = mem [p + 3 ].cint ;
	if ( ( mem [q + 2 ].cint == -1073741824L ) ) 
	mem [q + 2 ].cint = mem [p + 2 ].cint ;
	if ( o != 0 ) 
	{
	  r = mem [q ].hh .v.RH ;
	  mem [q ].hh .v.RH = -1073741823L ;
	  q = hpack ( q , 0 , 1 ) ;
	  mem [q + 4 ].cint = o ;
	  mem [q ].hh .v.RH = r ;
	  mem [s ].hh .v.RH = q ;
	} 
      } 
    } 
    s = q ;
    q = mem [q ].hh .v.RH ;
  } 
  flushnodelist ( p ) ;
  popalignment () ;
  auxsave = curlist .auxfield ;
  p = mem [curlist .headfield ].hh .v.RH ;
  q = curlist .tailfield ;
  popnest () ;
  if ( curlist .modefield == 233 ) 
  {
    doassignments () ;
    if ( curcmd != 3 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1245 ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 952 ;
	helpline [0 ]= 953 ;
      } 
      backerror () ;
    } 
    else {
	
      getxtoken () ;
      if ( curcmd != 3 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1241 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1242 ;
	  helpline [0 ]= 1243 ;
	} 
	backerror () ;
      } 
    } 
    popnest () ;
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [28473 ].cint 
      ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( 3 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh .v.RH = p ;
    if ( p != -1073741823L ) 
    curlist .tailfield = q ;
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [28474 ].cint 
      ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( 4 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    curlist .auxfield .cint = auxsave .cint ;
    resumeafterdisplay () ;
  } 
  else {
      
    curlist .auxfield = auxsave ;
    mem [curlist .tailfield ].hh .v.RH = p ;
    if ( p != -1073741823L ) 
    curlist .tailfield = q ;
    if ( curlist .modefield == 1 ) 
    buildpage () ;
  } 
} 
void 
alignpeek ( void ) 
{
  /* 20 */ alignpeek_regmem 
  lab20: alignstate = 1000000L ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curcmd == 38 ) 
  {
    scanleftbrace () ;
    newsavelevel ( 7 ) ;
    if ( curlist .modefield == -1 ) 
    normalparagraph () ;
  } 
  else if ( curcmd == 2 ) 
  finalign () ;
  else if ( ( curcmd == 5 ) && ( curchr == 258 ) ) 
  goto lab20 ;
  else {
      
    initrow () ;
    initcol () ;
  } 
} 
halfword 
zfiniteshrink ( halfword p ) 
{
  register halfword Result; finiteshrink_regmem 
  halfword q  ;
  if ( noshrinkerroryet ) 
  {
    noshrinkerroryet = false ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 974 ) ;
    } 
    {
      helpptr = 5 ;
      helpline [4 ]= 975 ;
      helpline [3 ]= 976 ;
      helpline [2 ]= 977 ;
      helpline [1 ]= 978 ;
      helpline [0 ]= 979 ;
    } 
    error () ;
  } 
  q = newspec ( p ) ;
  mem [q ].hh.b1 = 0 ;
  deleteglueref ( p ) ;
  Result = q ;
  return Result ;
} 
void 
ztrybreak ( integer pi , smallnumber breaktype ) 
{
  /* 10 30 31 22 60 */ trybreak_regmem 
  halfword r  ;
  halfword prevr  ;
  halfword oldl  ;
  boolean nobreakyet  ;
  halfword prevprevr  ;
  halfword s  ;
  halfword q  ;
  halfword v  ;
  integer t  ;
  internalfontnumber f  ;
  halfword l  ;
  boolean noderstaysactive  ;
  scaled linewidth  ;
  unsigned char fitclass  ;
  halfword b  ;
  integer d  ;
  boolean artificialdemerits  ;
  halfword savelink  ;
  scaled shortfall  ;
  if ( abs ( pi ) >= 10000 ) {
      
    if ( pi > 0 ) 
    goto lab10 ;
    else pi = -10000 ;
  } 
  nobreakyet = true ;
  prevr = memtop - 7 ;
  oldl = 0 ;
  curactivewidth [1 ]= activewidth [1 ];
  curactivewidth [2 ]= activewidth [2 ];
  curactivewidth [3 ]= activewidth [3 ];
  curactivewidth [4 ]= activewidth [4 ];
  curactivewidth [5 ]= activewidth [5 ];
  curactivewidth [6 ]= activewidth [6 ];
  while ( true ) {
      
    lab22: r = mem [prevr ].hh .v.RH ;
    if ( mem [r ].hh.b0 == 2 ) 
    {
      curactivewidth [1 ]= curactivewidth [1 ]+ mem [r + 1 ].cint ;
      curactivewidth [2 ]= curactivewidth [2 ]+ mem [r + 2 ].cint ;
      curactivewidth [3 ]= curactivewidth [3 ]+ mem [r + 3 ].cint ;
      curactivewidth [4 ]= curactivewidth [4 ]+ mem [r + 4 ].cint ;
      curactivewidth [5 ]= curactivewidth [5 ]+ mem [r + 5 ].cint ;
      curactivewidth [6 ]= curactivewidth [6 ]+ mem [r + 6 ].cint ;
      prevprevr = prevr ;
      prevr = r ;
      goto lab22 ;
    } 
    {
      l = mem [r + 1 ].hh .v.LH ;
      if ( l > oldl ) 
      {
	if ( ( minimumdemerits < 1073741823L ) && ( ( oldl != easyline ) || ( 
	r == memtop - 7 ) ) ) 
	{
	  if ( nobreakyet ) 
	  {
	    nobreakyet = false ;
	    breakwidth [1 ]= background [1 ];
	    breakwidth [2 ]= background [2 ];
	    breakwidth [3 ]= background [3 ];
	    breakwidth [4 ]= background [4 ];
	    breakwidth [5 ]= background [5 ];
	    breakwidth [6 ]= background [6 ];
	    s = curp ;
	    if ( breaktype > 0 ) {
		
	      if ( curp != -1073741823L ) 
	      {
		t = mem [curp ].hh.b1 ;
		v = curp ;
		s = mem [curp + 1 ].hh .v.RH ;
		while ( t > 0 ) {
		    
		  decr ( t ) ;
		  v = mem [v ].hh .v.RH ;
		  if ( ( v >= himemmin ) ) 
		  {
		    f = mem [v ].hh.b0 ;
		    breakwidth [1 ]= breakwidth [1 ]- fontinfo [widthbase 
		    [f ]+ fontinfo [charbase [f ]+ mem [v ].hh.b1 ]
		    .qqqq .b0 ].cint ;
		    if ( fontdir [f ]!= 0 ) 
		    v = mem [v ].hh .v.RH ;
		  } 
		  else switch ( mem [v ].hh.b0 ) 
		  {case 8 : 
		    {
		      f = mem [v + 1 ].hh.b0 ;
		      breakwidth [1 ]= breakwidth [1 ]- fontinfo [
		      widthbase [f ]+ fontinfo [charbase [f ]+ mem [v + 
		      1 ].hh.b1 ].qqqq .b0 ].cint ;
		    } 
		    break ;
		  case 0 : 
		  case 1 : 
		  case 2 : 
		  case 3 : 
		  case 13 : 
		    breakwidth [1 ]= breakwidth [1 ]- mem [v + 1 ].cint 
		    ;
		    break ;
		  case 5 : 
		    ;
		    break ;
		    default: 
		    confusion ( 980 ) ;
		    break ;
		  } 
		} 
		while ( s != -1073741823L ) {
		    
		  if ( ( s >= himemmin ) ) 
		  {
		    f = mem [s ].hh.b0 ;
		    breakwidth [1 ]= breakwidth [1 ]+ fontinfo [widthbase 
		    [f ]+ fontinfo [charbase [f ]+ mem [s ].hh.b1 ]
		    .qqqq .b0 ].cint ;
		    if ( fontdir [f ]!= 0 ) 
		    s = mem [s ].hh .v.RH ;
		  } 
		  else switch ( mem [s ].hh.b0 ) 
		  {case 8 : 
		    {
		      f = mem [s + 1 ].hh.b0 ;
		      breakwidth [1 ]= breakwidth [1 ]+ fontinfo [
		      widthbase [f ]+ fontinfo [charbase [f ]+ mem [s + 
		      1 ].hh.b1 ].qqqq .b0 ].cint ;
		    } 
		    break ;
		  case 0 : 
		  case 1 : 
		  case 2 : 
		  case 3 : 
		  case 13 : 
		    breakwidth [1 ]= breakwidth [1 ]+ mem [s + 1 ].cint 
		    ;
		    break ;
		  case 5 : 
		    ;
		    break ;
		    default: 
		    confusion ( 981 ) ;
		    break ;
		  } 
		  s = mem [s ].hh .v.RH ;
		} 
		breakwidth [1 ]= breakwidth [1 ]+ discwidth ;
		if ( mem [curp + 1 ].hh .v.RH == -1073741823L ) 
		s = mem [v ].hh .v.RH ;
	      } 
	    } 
	    while ( s != -1073741823L ) {
		
	      if ( ( s >= himemmin ) ) 
	      {
		if ( chain ) 
		{
		  breakwidth [1 ]= breakwidth [1 ]- mem [curkanjiskip + 1 
		  ].cint ;
		  breakwidth [2 + mem [curkanjiskip ].hh.b0 ]= breakwidth 
		  [2 + mem [curkanjiskip ].hh.b0 ]- mem [curkanjiskip + 2 
		  ].cint ;
		  breakwidth [6 ]= breakwidth [6 ]- mem [curkanjiskip + 3 
		  ].cint ;
		} 
		goto lab30 ;
	      } 
	      switch ( mem [s ].hh.b0 ) 
	      {case 12 : 
		{
		  v = mem [s + 1 ].hh .v.LH ;
		  breakwidth [1 ]= breakwidth [1 ]- mem [v + 1 ].cint ;
		  breakwidth [2 + mem [v ].hh.b0 ]= breakwidth [2 + mem [
		  v ].hh.b0 ]- mem [v + 2 ].cint ;
		  breakwidth [6 ]= breakwidth [6 ]- mem [v + 3 ].cint ;
		} 
		break ;
	      case 14 : 
		;
		break ;
	      case 11 : 
		breakwidth [1 ]= breakwidth [1 ]- mem [s + 1 ].cint ;
		break ;
	      case 13 : 
		if ( ( mem [s ].hh.b1 != 1 ) && ( mem [s ].hh.b1 != 3 ) ) 
		goto lab30 ;
		else breakwidth [1 ]= breakwidth [1 ]- mem [s + 1 ].cint 
		;
		break ;
		default: 
		goto lab30 ;
		break ;
	      } 
	      s = mem [s ].hh .v.RH ;
	    } 
	    lab30: ;
	  } 
	  if ( mem [prevr ].hh.b0 == 2 ) 
	  {
	    mem [prevr + 1 ].cint = mem [prevr + 1 ].cint - curactivewidth 
	    [1 ]+ breakwidth [1 ];
	    mem [prevr + 2 ].cint = mem [prevr + 2 ].cint - curactivewidth 
	    [2 ]+ breakwidth [2 ];
	    mem [prevr + 3 ].cint = mem [prevr + 3 ].cint - curactivewidth 
	    [3 ]+ breakwidth [3 ];
	    mem [prevr + 4 ].cint = mem [prevr + 4 ].cint - curactivewidth 
	    [4 ]+ breakwidth [4 ];
	    mem [prevr + 5 ].cint = mem [prevr + 5 ].cint - curactivewidth 
	    [5 ]+ breakwidth [5 ];
	    mem [prevr + 6 ].cint = mem [prevr + 6 ].cint - curactivewidth 
	    [6 ]+ breakwidth [6 ];
	  } 
	  else if ( prevr == memtop - 7 ) 
	  {
	    activewidth [1 ]= breakwidth [1 ];
	    activewidth [2 ]= breakwidth [2 ];
	    activewidth [3 ]= breakwidth [3 ];
	    activewidth [4 ]= breakwidth [4 ];
	    activewidth [5 ]= breakwidth [5 ];
	    activewidth [6 ]= breakwidth [6 ];
	  } 
	  else {
	      
	    q = getnode ( 7 ) ;
	    mem [q ].hh .v.RH = r ;
	    mem [q ].hh.b0 = 2 ;
	    mem [q ].hh.b1 = 0 ;
	    mem [q + 1 ].cint = breakwidth [1 ]- curactivewidth [1 ];
	    mem [q + 2 ].cint = breakwidth [2 ]- curactivewidth [2 ];
	    mem [q + 3 ].cint = breakwidth [3 ]- curactivewidth [3 ];
	    mem [q + 4 ].cint = breakwidth [4 ]- curactivewidth [4 ];
	    mem [q + 5 ].cint = breakwidth [5 ]- curactivewidth [5 ];
	    mem [q + 6 ].cint = breakwidth [6 ]- curactivewidth [6 ];
	    mem [prevr ].hh .v.RH = q ;
	    prevprevr = prevr ;
	    prevr = q ;
	  } 
	  if ( abs ( eqtb [28478 ].cint ) >= 1073741823L - minimumdemerits ) 
	  minimumdemerits = 1073741822L ;
	  else minimumdemerits = minimumdemerits + abs ( eqtb [28478 ].cint 
	  ) ;
	  {register integer for_end; fitclass = 0 ;for_end = 3 ; if ( 
	  fitclass <= for_end) do 
	    {
	      if ( minimaldemerits [fitclass ]<= minimumdemerits ) 
	      {
		q = getnode ( 2 ) ;
		mem [q ].hh .v.RH = passive ;
		passive = q ;
		mem [q + 1 ].hh .v.RH = curp ;
	;
#ifdef STAT
		incr ( passnumber ) ;
		mem [q ].hh .v.LH = passnumber ;
#endif /* STAT */
		mem [q + 1 ].hh .v.LH = bestplace [fitclass ];
		q = getnode ( 3 ) ;
		mem [q + 1 ].hh .v.RH = passive ;
		mem [q + 1 ].hh .v.LH = bestplline [fitclass ]+ 1 ;
		mem [q ].hh.b1 = fitclass ;
		mem [q ].hh.b0 = breaktype ;
		mem [q + 2 ].cint = minimaldemerits [fitclass ];
		mem [q ].hh .v.RH = r ;
		mem [prevr ].hh .v.RH = q ;
		prevr = q ;
	;
#ifdef STAT
		if ( eqtb [28494 ].cint > 0 ) 
		{
		  printnl ( 982 ) ;
		  printint ( mem [passive ].hh .v.LH ) ;
		  print ( 983 ) ;
		  printint ( mem [q + 1 ].hh .v.LH - 1 ) ;
		  printchar ( 46 ) ;
		  printint ( fitclass ) ;
		  if ( breaktype == 1 ) 
		  printchar ( 45 ) ;
		  print ( 984 ) ;
		  printint ( mem [q + 2 ].cint ) ;
		  print ( 985 ) ;
		  if ( mem [passive + 1 ].hh .v.LH == -1073741823L ) 
		  printchar ( 48 ) ;
		  else printint ( mem [mem [passive + 1 ].hh .v.LH ].hh 
		  .v.LH ) ;
		} 
#endif /* STAT */
	      } 
	      minimaldemerits [fitclass ]= 1073741823L ;
	    } 
	  while ( fitclass++ < for_end ) ;} 
	  minimumdemerits = 1073741823L ;
	  if ( r != memtop - 7 ) 
	  {
	    q = getnode ( 7 ) ;
	    mem [q ].hh .v.RH = r ;
	    mem [q ].hh.b0 = 2 ;
	    mem [q ].hh.b1 = 0 ;
	    mem [q + 1 ].cint = curactivewidth [1 ]- breakwidth [1 ];
	    mem [q + 2 ].cint = curactivewidth [2 ]- breakwidth [2 ];
	    mem [q + 3 ].cint = curactivewidth [3 ]- breakwidth [3 ];
	    mem [q + 4 ].cint = curactivewidth [4 ]- breakwidth [4 ];
	    mem [q + 5 ].cint = curactivewidth [5 ]- breakwidth [5 ];
	    mem [q + 6 ].cint = curactivewidth [6 ]- breakwidth [6 ];
	    mem [prevr ].hh .v.RH = q ;
	    prevprevr = prevr ;
	    prevr = q ;
	  } 
	} 
	if ( r == memtop - 7 ) 
	goto lab10 ;
	if ( l > easyline ) 
	{
	  linewidth = secondwidth ;
	  oldl = 1073741822L ;
	} 
	else {
	    
	  oldl = l ;
	  if ( l > lastspecialline ) 
	  linewidth = secondwidth ;
	  else if ( eqtb [25060 ].hh .v.RH == -1073741823L ) 
	  linewidth = firstwidth ;
	  else linewidth = mem [eqtb [25060 ].hh .v.RH + 2 * l ].cint ;
	} 
      } 
    } 
    {
      artificialdemerits = false ;
      shortfall = linewidth - curactivewidth [1 ];
      if ( shortfall > 0 ) {
	  
	if ( ( curactivewidth [3 ]!= 0 ) || ( curactivewidth [4 ]!= 0 ) || 
	( curactivewidth [5 ]!= 0 ) ) 
	{
	  b = 0 ;
	  fitclass = 2 ;
	} 
	else {
	    
	  if ( shortfall > 7230584L ) {
	      
	    if ( curactivewidth [2 ]< 1663497L ) 
	    {
	      b = 10000 ;
	      fitclass = 0 ;
	      goto lab31 ;
	    } 
	  } 
	  b = badness ( shortfall , curactivewidth [2 ]) ;
	  if ( b > 12 ) {
	      
	    if ( b > 99 ) 
	    fitclass = 0 ;
	    else fitclass = 1 ;
	  } 
	  else fitclass = 2 ;
	  lab31: ;
	} 
      } 
      else {
	  
	if ( - (integer) shortfall > curactivewidth [6 ]) 
	b = 10001 ;
	else b = badness ( - (integer) shortfall , curactivewidth [6 ]) ;
	if ( b > 12 ) 
	fitclass = 3 ;
	else fitclass = 2 ;
      } 
      if ( ( b > 10000 ) || ( pi == -10000 ) ) 
      {
	if ( finalpass && ( minimumdemerits == 1073741823L ) && ( mem [r ]
	.hh .v.RH == memtop - 7 ) && ( prevr == memtop - 7 ) ) 
	artificialdemerits = true ;
	else if ( b > threshold ) 
	goto lab60 ;
	noderstaysactive = false ;
      } 
      else {
	  
	prevr = r ;
	if ( b > threshold ) 
	goto lab22 ;
	noderstaysactive = true ;
      } 
      if ( artificialdemerits ) 
      d = 0 ;
      else {
	  
	d = eqtb [28464 ].cint + b ;
	if ( abs ( d ) >= 10000 ) 
	d = 100000000L ;
	else d = d * d ;
	if ( pi != 0 ) {
	    
	  if ( pi > 0 ) 
	  d = d + pi * pi ;
	  else if ( pi > -10000 ) 
	  d = d - pi * pi ;
	} 
	if ( ( breaktype == 1 ) && ( mem [r ].hh.b0 == 1 ) ) {
	    
	  if ( curp != -1073741823L ) 
	  d = d + eqtb [28476 ].cint ;
	  else d = d + eqtb [28477 ].cint ;
	} 
	if ( abs ( fitclass - mem [r ].hh.b1 ) > 1 ) 
	d = d + eqtb [28478 ].cint ;
      } 
	;
#ifdef STAT
      if ( eqtb [28494 ].cint > 0 ) 
      {
	if ( printednode != curp ) 
	{
	  printnl ( 344 ) ;
	  if ( curp == -1073741823L ) 
	  shortdisplay ( mem [printednode ].hh .v.RH ) ;
	  else {
	      
	    savelink = mem [curp ].hh .v.RH ;
	    mem [curp ].hh .v.RH = -1073741823L ;
	    printnl ( 344 ) ;
	    shortdisplay ( mem [printednode ].hh .v.RH ) ;
	    mem [curp ].hh .v.RH = savelink ;
	  } 
	  printednode = curp ;
	} 
	printnl ( 64 ) ;
	if ( curp == -1073741823L ) 
	printesc ( 635 ) ;
	else if ( ( mem [curp ].hh.b0 != 12 ) && ( ! ( curp >= himemmin ) ) 
	) 
	{
	  if ( mem [curp ].hh.b0 == 14 ) 
	  printesc ( 569 ) ;
	  else if ( mem [curp ].hh.b0 == 9 ) 
	  printesc ( 357 ) ;
	  else if ( mem [curp ].hh.b0 == 13 ) 
	  printesc ( 346 ) ;
	  else printesc ( 349 ) ;
	} 
	print ( 986 ) ;
	if ( mem [r + 1 ].hh .v.RH == -1073741823L ) 
	printchar ( 48 ) ;
	else printint ( mem [mem [r + 1 ].hh .v.RH ].hh .v.LH ) ;
	print ( 987 ) ;
	if ( b > 10000 ) 
	printchar ( 42 ) ;
	else printint ( b ) ;
	print ( 988 ) ;
	printint ( pi ) ;
	print ( 989 ) ;
	if ( artificialdemerits ) 
	printchar ( 42 ) ;
	else printint ( d ) ;
      } 
#endif /* STAT */
      d = d + mem [r + 2 ].cint ;
      if ( d <= minimaldemerits [fitclass ]) 
      {
	minimaldemerits [fitclass ]= d ;
	bestplace [fitclass ]= mem [r + 1 ].hh .v.RH ;
	bestplline [fitclass ]= l ;
	if ( d < minimumdemerits ) 
	minimumdemerits = d ;
      } 
      if ( noderstaysactive ) 
      goto lab22 ;
      lab60: mem [prevr ].hh .v.RH = mem [r ].hh .v.RH ;
      freenode ( r , 3 ) ;
      if ( prevr == memtop - 7 ) 
      {
	r = mem [memtop - 7 ].hh .v.RH ;
	if ( mem [r ].hh.b0 == 2 ) 
	{
	  activewidth [1 ]= activewidth [1 ]+ mem [r + 1 ].cint ;
	  activewidth [2 ]= activewidth [2 ]+ mem [r + 2 ].cint ;
	  activewidth [3 ]= activewidth [3 ]+ mem [r + 3 ].cint ;
	  activewidth [4 ]= activewidth [4 ]+ mem [r + 4 ].cint ;
	  activewidth [5 ]= activewidth [5 ]+ mem [r + 5 ].cint ;
	  activewidth [6 ]= activewidth [6 ]+ mem [r + 6 ].cint ;
	  curactivewidth [1 ]= activewidth [1 ];
	  curactivewidth [2 ]= activewidth [2 ];
	  curactivewidth [3 ]= activewidth [3 ];
	  curactivewidth [4 ]= activewidth [4 ];
	  curactivewidth [5 ]= activewidth [5 ];
	  curactivewidth [6 ]= activewidth [6 ];
	  mem [memtop - 7 ].hh .v.RH = mem [r ].hh .v.RH ;
	  freenode ( r , 7 ) ;
	} 
      } 
      else if ( mem [prevr ].hh.b0 == 2 ) 
      {
	r = mem [prevr ].hh .v.RH ;
	if ( r == memtop - 7 ) 
	{
	  curactivewidth [1 ]= curactivewidth [1 ]- mem [prevr + 1 ]
	  .cint ;
	  curactivewidth [2 ]= curactivewidth [2 ]- mem [prevr + 2 ]
	  .cint ;
	  curactivewidth [3 ]= curactivewidth [3 ]- mem [prevr + 3 ]
	  .cint ;
	  curactivewidth [4 ]= curactivewidth [4 ]- mem [prevr + 4 ]
	  .cint ;
	  curactivewidth [5 ]= curactivewidth [5 ]- mem [prevr + 5 ]
	  .cint ;
	  curactivewidth [6 ]= curactivewidth [6 ]- mem [prevr + 6 ]
	  .cint ;
	  mem [prevprevr ].hh .v.RH = memtop - 7 ;
	  freenode ( prevr , 7 ) ;
	  prevr = prevprevr ;
	} 
	else if ( mem [r ].hh.b0 == 2 ) 
	{
	  curactivewidth [1 ]= curactivewidth [1 ]+ mem [r + 1 ].cint ;
	  curactivewidth [2 ]= curactivewidth [2 ]+ mem [r + 2 ].cint ;
	  curactivewidth [3 ]= curactivewidth [3 ]+ mem [r + 3 ].cint ;
	  curactivewidth [4 ]= curactivewidth [4 ]+ mem [r + 4 ].cint ;
	  curactivewidth [5 ]= curactivewidth [5 ]+ mem [r + 5 ].cint ;
	  curactivewidth [6 ]= curactivewidth [6 ]+ mem [r + 6 ].cint ;
	  mem [prevr + 1 ].cint = mem [prevr + 1 ].cint + mem [r + 1 ]
	  .cint ;
	  mem [prevr + 2 ].cint = mem [prevr + 2 ].cint + mem [r + 2 ]
	  .cint ;
	  mem [prevr + 3 ].cint = mem [prevr + 3 ].cint + mem [r + 3 ]
	  .cint ;
	  mem [prevr + 4 ].cint = mem [prevr + 4 ].cint + mem [r + 4 ]
	  .cint ;
	  mem [prevr + 5 ].cint = mem [prevr + 5 ].cint + mem [r + 5 ]
	  .cint ;
	  mem [prevr + 6 ].cint = mem [prevr + 6 ].cint + mem [r + 6 ]
	  .cint ;
	  mem [prevr ].hh .v.RH = mem [r ].hh .v.RH ;
	  freenode ( r , 7 ) ;
	} 
      } 
    } 
  } 
  lab10: 
	;
#ifdef STAT
  if ( curp == printednode ) {
      
    if ( curp != -1073741823L ) {
	
      if ( mem [curp ].hh.b0 == 9 ) 
      {
	t = mem [curp ].hh.b1 ;
	while ( t > 0 ) {
	    
	  decr ( t ) ;
	  printednode = mem [printednode ].hh .v.RH ;
	} 
      } 
#endif /* STAT */
    } 
  } 
} 
void 
zpostlinebreak ( integer finalwidowpenalty ) 
{
  /* 30 31 */ postlinebreak_regmem 
  halfword q, r, s  ;
  boolean discbreak  ;
  boolean postdiscbreak  ;
  scaled curwidth  ;
  scaled curindent  ;
  quarterword t  ;
  integer pen  ;
  halfword curline  ;
  q = mem [bestbet + 1 ].hh .v.RH ;
  curp = -1073741823L ;
  do {
      r = q ;
    q = mem [q + 1 ].hh .v.LH ;
    mem [r + 1 ].hh .v.LH = curp ;
    curp = r ;
  } while ( ! ( q == -1073741823L ) ) ;
  curline = curlist .pgfield + 1 ;
  lastdisp = 0 ;
  do {
      q = mem [curp + 1 ].hh .v.RH ;
    discbreak = false ;
    postdiscbreak = false ;
    if ( q != -1073741823L ) 
    {
      if ( ! ( q >= himemmin ) ) {
	  
	if ( mem [q ].hh.b0 == 12 ) 
	{
	  deleteglueref ( mem [q + 1 ].hh .v.LH ) ;
	  mem [q + 1 ].hh .v.LH = eqtb [24535 ].hh .v.RH ;
	  mem [q ].hh.b1 = 9 ;
	  incr ( mem [eqtb [24535 ].hh .v.RH ].hh .v.RH ) ;
	  goto lab30 ;
	} 
	else {
	    
	  if ( mem [q ].hh.b0 == 9 ) 
	  {
	    t = mem [q ].hh.b1 ;
	    if ( t == 0 ) 
	    r = mem [q ].hh .v.RH ;
	    else {
		
	      r = q ;
	      while ( t > 1 ) {
		  
		r = mem [r ].hh .v.RH ;
		decr ( t ) ;
	      } 
	      s = mem [r ].hh .v.RH ;
	      r = mem [s ].hh .v.RH ;
	      mem [s ].hh .v.RH = -1073741823L ;
	      flushnodelist ( mem [q ].hh .v.RH ) ;
	      mem [q ].hh.b1 = 0 ;
	    } 
	    if ( mem [q + 1 ].hh .v.RH != -1073741823L ) 
	    {
	      s = mem [q + 1 ].hh .v.RH ;
	      while ( mem [s ].hh .v.RH != -1073741823L ) s = mem [s ].hh 
	      .v.RH ;
	      mem [s ].hh .v.RH = r ;
	      r = mem [q + 1 ].hh .v.RH ;
	      mem [q + 1 ].hh .v.RH = -1073741823L ;
	      postdiscbreak = true ;
	    } 
	    if ( mem [q + 1 ].hh .v.LH != -1073741823L ) 
	    {
	      s = mem [q + 1 ].hh .v.LH ;
	      mem [q ].hh .v.RH = s ;
	      while ( mem [s ].hh .v.RH != -1073741823L ) s = mem [s ].hh 
	      .v.RH ;
	      mem [q + 1 ].hh .v.LH = -1073741823L ;
	      q = s ;
	    } 
	    mem [q ].hh .v.RH = r ;
	    discbreak = true ;
	  } 
	  else if ( ( mem [q ].hh.b0 == 11 ) || ( mem [q ].hh.b0 == 13 ) ) 
	  mem [q + 1 ].cint = 0 ;
	} 
      } 
    } 
    else {
	
      q = memtop - 3 ;
      while ( mem [q ].hh .v.RH != -1073741823L ) q = mem [q ].hh .v.RH ;
    } 
    r = newparamglue ( 8 ) ;
    mem [r ].hh .v.RH = mem [q ].hh .v.RH ;
    mem [q ].hh .v.RH = r ;
    q = r ;
    lab30: ;
    r = mem [q ].hh .v.RH ;
    mem [q ].hh .v.RH = -1073741823L ;
    q = mem [memtop - 3 ].hh .v.RH ;
    mem [memtop - 3 ].hh .v.RH = r ;
    if ( lastdisp != 0 ) 
    {
      r = getnode ( 2 ) ;
      mem [r ].hh.b0 = 5 ;
      mem [r + 1 ].cint = lastdisp ;
      mem [r ].hh .v.RH = q ;
      q = r ;
    } 
    if ( eqtb [24534 ].hh .v.RH != membot ) 
    {
      r = newparamglue ( 7 ) ;
      mem [r ].hh .v.RH = q ;
      q = r ;
    } 
    if ( curline > lastspecialline ) 
    {
      curwidth = secondwidth ;
      curindent = secondindent ;
    } 
    else if ( eqtb [25060 ].hh .v.RH == -1073741823L ) 
    {
      curwidth = firstwidth ;
      curindent = firstindent ;
    } 
    else {
	
      curwidth = mem [eqtb [25060 ].hh .v.RH + 2 * curline ].cint ;
      curindent = mem [eqtb [25060 ].hh .v.RH + 2 * curline - 1 ].cint ;
    } 
    adjusttail = memtop - 5 ;
    justbox = hpack ( q , curwidth , 0 ) ;
    mem [justbox + 4 ].cint = curindent ;
    appendtovlist ( justbox ) ;
    if ( memtop - 5 != adjusttail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 5 ].hh .v.RH ;
      curlist .tailfield = adjusttail ;
    } 
    adjusttail = -1073741823L ;
    if ( curline + 1 != bestline ) 
    {
      pen = eqtb [28475 ].cint ;
      if ( curline == curlist .pgfield + 1 ) 
      pen = pen + eqtb [28467 ].cint ;
      if ( curline + 2 == bestline ) 
      pen = pen + finalwidowpenalty ;
      if ( discbreak ) 
      pen = pen + eqtb [28470 ].cint ;
      if ( pen != 0 ) 
      {
	r = newpenalty ( pen ) ;
	mem [curlist .tailfield ].hh .v.RH = r ;
	curlist .tailfield = r ;
      } 
    } 
    incr ( curline ) ;
    curp = mem [curp + 1 ].hh .v.LH ;
    if ( curp != -1073741823L ) {
	
      if ( ! postdiscbreak ) 
      {
	r = memtop - 3 ;
	while ( true ) {
	    
	  q = mem [r ].hh .v.RH ;
	  if ( q == mem [curp + 1 ].hh .v.RH ) 
	  goto lab31 ;
	  if ( ( q >= himemmin ) ) 
	  goto lab31 ;
	  if ( ( mem [q ].hh.b0 < 11 ) ) 
	  goto lab31 ;
	  if ( mem [q ].hh.b0 == 13 ) {
	      
	    if ( ( mem [q ].hh.b1 != 1 ) && ( mem [q ].hh.b1 != 3 ) ) 
	    goto lab31 ;
	  } 
	  r = q ;
	} 
	lab31: if ( r != memtop - 3 ) 
	{
	  mem [r ].hh .v.RH = -1073741823L ;
	  flushnodelist ( mem [memtop - 3 ].hh .v.RH ) ;
	  mem [memtop - 3 ].hh .v.RH = q ;
	} 
      } 
    } 
  } while ( ! ( curp == -1073741823L ) ) ;
  if ( ( curline != bestline ) || ( mem [memtop - 3 ].hh .v.RH != 
  -1073741823L ) ) 
  confusion ( 996 ) ;
  curlist .pgfield = bestline - 1 ;
} 
smallnumber 
zreconstitute ( smallnumber j , smallnumber n , halfword bchar , halfword 
hchar ) 
{
  /* 22 30 */ register smallnumber Result; reconstitute_regmem 
  halfword p  ;
  halfword t  ;
  fourquarters q  ;
  halfword currh  ;
  halfword testchar  ;
  scaled w  ;
  fontindex k  ;
  hyphenpassed = 0 ;
  t = memtop - 4 ;
  w = 0 ;
  mem [memtop - 4 ].hh .v.RH = -1073741823L ;
  curl = hu [j ];
  curq = t ;
  if ( j == 0 ) 
  {
    ligaturepresent = initlig ;
    p = initlist ;
    if ( ligaturepresent ) 
    lfthit = initlft ;
    while ( p > -1073741823L ) {
	
      {
	mem [t ].hh .v.RH = getavail () ;
	t = mem [t ].hh .v.RH ;
	mem [t ].hh.b0 = hf ;
	mem [t ].hh.b1 = mem [p ].hh.b1 ;
      } 
      p = mem [p ].hh .v.RH ;
    } 
  } 
  else if ( curl < 256 ) 
  {
    mem [t ].hh .v.RH = getavail () ;
    t = mem [t ].hh .v.RH ;
    mem [t ].hh.b0 = hf ;
    mem [t ].hh.b1 = curl ;
  } 
  ligstack = -1073741823L ;
  {
    if ( j < n ) 
    curr = hu [j + 1 ];
    else curr = bchar ;
    if ( odd ( hyf [j ]) ) 
    currh = hchar ;
    else currh = 256 ;
  } 
  lab22: if ( curl == 256 ) 
  {
    k = bcharlabel [hf ];
    if ( k == 0 ) 
    goto lab30 ;
    else q = fontinfo [k ].qqqq ;
  } 
  else {
      
    q = fontinfo [charbase [hf ]+ effectivechar ( true , hf , curl ) ]
    .qqqq ;
    if ( ( ( q .b2 ) % 4 ) != 1 ) 
    goto lab30 ;
    k = ligkernbase [hf ]+ q .b3 ;
    q = fontinfo [k ].qqqq ;
    if ( q .b0 > 128 ) 
    {
      k = ligkernbase [hf ]+ 256 * q .b2 + q .b3 + 32768L - 256 * ( 128 ) ;
      q = fontinfo [k ].qqqq ;
    } 
  } 
  if ( currh < 256 ) 
  testchar = currh ;
  else testchar = curr ;
  while ( true ) {
      
    if ( q .b1 == testchar ) {
	
      if ( q .b0 <= 128 ) {
	  
	if ( currh < 256 ) 
	{
	  hyphenpassed = j ;
	  hchar = 256 ;
	  currh = 256 ;
	  goto lab22 ;
	} 
	else {
	    
	  if ( hchar < 256 ) {
	      
	    if ( odd ( hyf [j ]) ) 
	    {
	      hyphenpassed = j ;
	      hchar = 256 ;
	    } 
	  } 
	  if ( q .b2 < 128 ) 
	  {
	    if ( curl == 256 ) 
	    lfthit = true ;
	    if ( j == n ) {
		
	      if ( ligstack == -1073741823L ) 
	      rthit = true ;
	    } 
	    {
	      if ( interrupt != 0 ) 
	      pauseforinstructions () ;
	    } 
	    switch ( q .b2 ) 
	    {case 1 : 
	    case 5 : 
	      {
		curl = q .b3 ;
		ligaturepresent = true ;
	      } 
	      break ;
	    case 2 : 
	    case 6 : 
	      {
		curr = q .b3 ;
		if ( ligstack > -1073741823L ) 
		mem [ligstack ].hh.b1 = curr ;
		else {
		    
		  ligstack = newligitem ( curr ) ;
		  if ( j == n ) 
		  bchar = 256 ;
		  else {
		      
		    p = getavail () ;
		    mem [ligstack + 1 ].hh .v.RH = p ;
		    mem [p ].hh.b1 = hu [j + 1 ];
		    mem [p ].hh.b0 = hf ;
		  } 
		} 
	      } 
	      break ;
	    case 3 : 
	      {
		curr = q .b3 ;
		p = ligstack ;
		ligstack = newligitem ( curr ) ;
		mem [ligstack ].hh .v.RH = p ;
	      } 
	      break ;
	    case 7 : 
	    case 11 : 
	      {
		if ( ligaturepresent ) 
		{
		  p = newligature ( hf , curl , mem [curq ].hh .v.RH ) ;
		  if ( lfthit ) 
		  {
		    mem [p ].hh.b1 = 2 ;
		    lfthit = false ;
		  } 
		  if ( false ) {
		      
		    if ( ligstack == -1073741823L ) 
		    {
		      incr ( mem [p ].hh.b1 ) ;
		      rthit = false ;
		    } 
		  } 
		  mem [curq ].hh .v.RH = p ;
		  t = p ;
		  ligaturepresent = false ;
		} 
		curq = t ;
		curl = q .b3 ;
		ligaturepresent = true ;
	      } 
	      break ;
	      default: 
	      {
		curl = q .b3 ;
		ligaturepresent = true ;
		if ( ligstack > -1073741823L ) 
		{
		  if ( mem [ligstack + 1 ].hh .v.RH > -1073741823L ) 
		  {
		    mem [t ].hh .v.RH = mem [ligstack + 1 ].hh .v.RH ;
		    t = mem [t ].hh .v.RH ;
		    incr ( j ) ;
		  } 
		  p = ligstack ;
		  ligstack = mem [p ].hh .v.RH ;
		  freenode ( p , 2 ) ;
		  if ( ligstack == -1073741823L ) 
		  {
		    if ( j < n ) 
		    curr = hu [j + 1 ];
		    else curr = bchar ;
		    if ( odd ( hyf [j ]) ) 
		    currh = hchar ;
		    else currh = 256 ;
		  } 
		  else curr = mem [ligstack ].hh.b1 ;
		} 
		else if ( j == n ) 
		goto lab30 ;
		else {
		    
		  {
		    mem [t ].hh .v.RH = getavail () ;
		    t = mem [t ].hh .v.RH ;
		    mem [t ].hh.b0 = hf ;
		    mem [t ].hh.b1 = curr ;
		  } 
		  incr ( j ) ;
		  {
		    if ( j < n ) 
		    curr = hu [j + 1 ];
		    else curr = bchar ;
		    if ( odd ( hyf [j ]) ) 
		    currh = hchar ;
		    else currh = 256 ;
		  } 
		} 
	      } 
	      break ;
	    } 
	    if ( q .b2 > 4 ) {
		
	      if ( q .b2 != 7 ) 
	      goto lab30 ;
	    } 
	    goto lab22 ;
	  } 
	  w = fontinfo [kernbase [hf ]+ 256 * q .b2 + q .b3 ].cint ;
	  goto lab30 ;
	} 
      } 
    } 
    if ( q .b0 >= 128 ) {
	
      if ( currh == 256 ) 
      goto lab30 ;
      else {
	  
	currh = 256 ;
	goto lab22 ;
      } 
    } 
    k = k + q .b0 + 1 ;
    q = fontinfo [k ].qqqq ;
  } 
  lab30: ;
  if ( ligaturepresent ) 
  {
    p = newligature ( hf , curl , mem [curq ].hh .v.RH ) ;
    if ( lfthit ) 
    {
      mem [p ].hh.b1 = 2 ;
      lfthit = false ;
    } 
    if ( rthit ) {
	
      if ( ligstack == -1073741823L ) 
      {
	incr ( mem [p ].hh.b1 ) ;
	rthit = false ;
      } 
    } 
    mem [curq ].hh .v.RH = p ;
    t = p ;
    ligaturepresent = false ;
  } 
  if ( w != 0 ) 
  {
    mem [t ].hh .v.RH = newkern ( w ) ;
    t = mem [t ].hh .v.RH ;
    w = 0 ;
    mem [t + 2 ].cint = 0 ;
  } 
  if ( ligstack > -1073741823L ) 
  {
    curq = t ;
    curl = mem [ligstack ].hh.b1 ;
    ligaturepresent = true ;
    {
      if ( mem [ligstack + 1 ].hh .v.RH > -1073741823L ) 
      {
	mem [t ].hh .v.RH = mem [ligstack + 1 ].hh .v.RH ;
	t = mem [t ].hh .v.RH ;
	incr ( j ) ;
      } 
      p = ligstack ;
      ligstack = mem [p ].hh .v.RH ;
      freenode ( p , 2 ) ;
      if ( ligstack == -1073741823L ) 
      {
	if ( j < n ) 
	curr = hu [j + 1 ];
	else curr = bchar ;
	if ( odd ( hyf [j ]) ) 
	currh = hchar ;
	else currh = 256 ;
      } 
      else curr = mem [ligstack ].hh.b1 ;
    } 
    goto lab22 ;
  } 
  Result = j ;
  return Result ;
} 
void 
hyphenate ( void ) 
{
  /* 50 30 40 41 42 45 10 */ hyphenate_regmem 
  unsigned char i, j, l  ;
  halfword q, r, s  ;
  halfword bchar  ;
  halfword majortail, minortail  ;
  ASCIIcode c  ;
  unsigned char cloc  ;
  integer rcount  ;
  halfword hyfnode  ;
  triepointer z  ;
  integer v  ;
  hyphpointer h  ;
  strnumber k  ;
  poolpointer u  ;
  {register integer for_end; j = 0 ;for_end = hn ; if ( j <= for_end) do 
    hyf [j ]= 0 ;
  while ( j++ < for_end ) ;} 
  h = hc [1 ];
  incr ( hn ) ;
  hc [hn ]= curlang ;
  {register integer for_end; j = 2 ;for_end = hn ; if ( j <= for_end) do 
    h = ( h + h + hc [j ]) % 607 ;
  while ( j++ < for_end ) ;} 
  while ( true ) {
      
    k = hyphword [h ];
    if ( k == 0 ) 
    goto lab45 ;
    if ( ( strstart [k + 1 ]- strstart [k ]) == hn ) 
    {
      j = 1 ;
      u = strstart [k ];
      do {
	  if ( strpool [u ]!= hc [j ]) 
	goto lab30 ;
	incr ( j ) ;
	incr ( u ) ;
      } while ( ! ( j > hn ) ) ;
      s = hyphlist [h ];
      while ( s != -1073741823L ) {
	  
	hyf [mem [s ].hh .v.LH ]= 1 ;
	s = mem [s ].hh .v.RH ;
      } 
      decr ( hn ) ;
      goto lab40 ;
    } 
    lab30: ;
    h = hyphlink [h ];
    if ( h == 0 ) 
    goto lab45 ;
    decr ( h ) ;
  } 
  lab45: decr ( hn ) ;
  if ( trietrc [curlang + 1 ]!= curlang ) 
  return ;
  hc [0 ]= 0 ;
  hc [hn + 1 ]= 0 ;
  hc [hn + 2 ]= 256 ;
  {register integer for_end; j = 0 ;for_end = hn - rhyf + 1 ; if ( j <= 
  for_end) do 
    {
      z = trietrl [curlang + 1 ]+ hc [j ];
      l = j ;
      while ( hc [l ]== trietrc [z ]) {
	  
	if ( trietro [z ]!= mintrieop ) 
	{
	  v = trietro [z ];
	  do {
	      v = v + opstart [curlang ];
	    i = l - hyfdistance [v ];
	    if ( hyfnum [v ]> hyf [i ]) 
	    hyf [i ]= hyfnum [v ];
	    v = hyfnext [v ];
	  } while ( ! ( v == mintrieop ) ) ;
	} 
	incr ( l ) ;
	z = trietrl [z ]+ hc [l ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  lab40: {
      register integer for_end; j = 0 ;for_end = lhyf - 1 ; if ( j <= 
  for_end) do 
    hyf [j ]= 0 ;
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = 0 ;for_end = rhyf - 1 ; if ( j <= for_end) 
  do 
    hyf [hn - j ]= 0 ;
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = lhyf ;for_end = hn - rhyf ; if ( j <= 
  for_end) do 
    if ( odd ( hyf [j ]) ) 
    goto lab41 ;
  while ( j++ < for_end ) ;} 
  return ;
  lab41: ;
  q = mem [hb ].hh .v.RH ;
  mem [hb ].hh .v.RH = -1073741823L ;
  r = mem [ha ].hh .v.RH ;
  mem [ha ].hh .v.RH = -1073741823L ;
  bchar = hyfbchar ;
  if ( ( ha >= himemmin ) ) {
      
    if ( mem [ha ].hh.b0 != hf ) 
    goto lab42 ;
    else {
	
      initlist = ha ;
      initlig = false ;
      hu [0 ]= mem [ha ].hh.b1 ;
    } 
  } 
  else if ( mem [ha ].hh.b0 == 8 ) {
      
    if ( mem [ha + 1 ].hh.b0 != hf ) 
    goto lab42 ;
    else {
	
      initlist = mem [ha + 1 ].hh .v.RH ;
      initlig = true ;
      initlft = ( mem [ha ].hh.b1 > 1 ) ;
      hu [0 ]= mem [ha + 1 ].hh.b1 ;
      if ( initlist == -1073741823L ) {
	  
	if ( initlft ) 
	{
	  hu [0 ]= 256 ;
	  initlig = false ;
	} 
      } 
      freenode ( ha , 2 ) ;
    } 
  } 
  else {
      
    if ( ! ( r >= himemmin ) ) {
	
      if ( mem [r ].hh.b0 == 8 ) {
	  
	if ( mem [r ].hh.b1 > 1 ) 
	goto lab42 ;
      } 
    } 
    j = 1 ;
    s = ha ;
    initlist = -1073741823L ;
    goto lab50 ;
  } 
  s = curp ;
  while ( mem [s ].hh .v.RH != ha ) s = mem [s ].hh .v.RH ;
  j = 0 ;
  goto lab50 ;
  lab42: s = ha ;
  j = 0 ;
  hu [0 ]= 256 ;
  initlig = false ;
  initlist = -1073741823L ;
  lab50: flushnodelist ( r ) ;
  do {
      l = j ;
    j = reconstitute ( j , hn , bchar , hyfchar ) + 1 ;
    if ( hyphenpassed == 0 ) 
    {
      mem [s ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
      while ( mem [s ].hh .v.RH > -1073741823L ) s = mem [s ].hh .v.RH ;
      if ( odd ( hyf [j - 1 ]) ) 
      {
	l = j ;
	hyphenpassed = j - 1 ;
	mem [memtop - 4 ].hh .v.RH = -1073741823L ;
      } 
    } 
    if ( hyphenpassed > 0 ) 
    do {
	r = getnode ( 2 ) ;
      mem [r ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
      mem [r ].hh.b0 = 9 ;
      majortail = r ;
      rcount = 0 ;
      while ( mem [majortail ].hh .v.RH > -1073741823L ) {
	  
	majortail = mem [majortail ].hh .v.RH ;
	incr ( rcount ) ;
      } 
      i = hyphenpassed ;
      hyf [i ]= 0 ;
      minortail = -1073741823L ;
      mem [r + 1 ].hh .v.LH = -1073741823L ;
      hyfnode = newcharacter ( hf , hyfchar ) ;
      if ( hyfnode != -1073741823L ) 
      {
	incr ( i ) ;
	c = hu [i ];
	hu [i ]= hyfchar ;
	{
	  mem [hyfnode ].hh .v.RH = avail ;
	  avail = hyfnode ;
	;
#ifdef STAT
	  decr ( dynused ) ;
#endif /* STAT */
	} 
      } 
      while ( l <= i ) {
	  
	l = reconstitute ( l , i , fontbchar [hf ], 256 ) + 1 ;
	if ( mem [memtop - 4 ].hh .v.RH > -1073741823L ) 
	{
	  if ( minortail == -1073741823L ) 
	  mem [r + 1 ].hh .v.LH = mem [memtop - 4 ].hh .v.RH ;
	  else mem [minortail ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	  minortail = mem [memtop - 4 ].hh .v.RH ;
	  while ( mem [minortail ].hh .v.RH > -1073741823L ) minortail = mem 
	  [minortail ].hh .v.RH ;
	} 
      } 
      if ( hyfnode != -1073741823L ) 
      {
	hu [i ]= c ;
	l = i ;
	decr ( i ) ;
      } 
      minortail = -1073741823L ;
      mem [r + 1 ].hh .v.RH = -1073741823L ;
      cloc = 0 ;
      if ( bcharlabel [hf ]!= 0 ) 
      {
	decr ( l ) ;
	c = hu [l ];
	cloc = l ;
	hu [l ]= 256 ;
      } 
      while ( l < j ) {
	  
	do {
	    l = reconstitute ( l , hn , bchar , 256 ) + 1 ;
	  if ( cloc > 0 ) 
	  {
	    hu [cloc ]= c ;
	    cloc = 0 ;
	  } 
	  if ( mem [memtop - 4 ].hh .v.RH > -1073741823L ) 
	  {
	    if ( minortail == -1073741823L ) 
	    mem [r + 1 ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	    else mem [minortail ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	    minortail = mem [memtop - 4 ].hh .v.RH ;
	    while ( mem [minortail ].hh .v.RH > -1073741823L ) minortail = 
	    mem [minortail ].hh .v.RH ;
	  } 
	} while ( ! ( l >= j ) ) ;
	while ( l > j ) {
	    
	  j = reconstitute ( j , hn , bchar , 256 ) + 1 ;
	  mem [majortail ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	  while ( mem [majortail ].hh .v.RH > -1073741823L ) {
	      
	    majortail = mem [majortail ].hh .v.RH ;
	    incr ( rcount ) ;
	  } 
	} 
      } 
      if ( rcount > 127 ) 
      {
	mem [s ].hh .v.RH = mem [r ].hh .v.RH ;
	mem [r ].hh .v.RH = -1073741823L ;
	flushnodelist ( r ) ;
      } 
      else {
	  
	mem [s ].hh .v.RH = r ;
	mem [r ].hh.b1 = rcount ;
      } 
      s = majortail ;
      hyphenpassed = j - 1 ;
      mem [memtop - 4 ].hh .v.RH = -1073741823L ;
    } while ( ! ( ! odd ( hyf [j - 1 ]) ) ) ;
  } while ( ! ( j > hn ) ) ;
  mem [s ].hh .v.RH = q ;
  flushlist ( initlist ) ;
} 
void 
newhyphexceptions ( void ) 
{
  /* 21 10 40 45 */ newhyphexceptions_regmem 
  unsigned char n  ;
  unsigned char j  ;
  hyphpointer h  ;
  strnumber k  ;
  halfword p  ;
  halfword q  ;
  strnumber s  ;
  poolpointer u, v  ;
  scanleftbrace () ;
  if ( eqtb [28513 ].cint <= 0 ) 
  curlang = 0 ;
  else if ( eqtb [28513 ].cint > 255 ) 
  curlang = 0 ;
  else curlang = eqtb [28513 ].cint ;
  n = 0 ;
  p = -1073741823L ;
  while ( true ) {
      
    getxtoken () ;
    lab21: switch ( curcmd ) 
    {case 11 : 
    case 12 : 
    case 73 : 
    case 74 : 
      if ( curchr == 45 ) 
      {
	if ( n < 63 ) 
	{
	  q = getavail () ;
	  mem [q ].hh .v.RH = p ;
	  mem [q ].hh .v.LH = n ;
	  p = q ;
	} 
      } 
      else {
	  
	if ( eqtb [27182 + curchr ].hh .v.RH == 0 ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 1002 ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 1003 ;
	    helpline [0 ]= 1004 ;
	  } 
	  error () ;
	} 
	else if ( n < 63 ) 
	{
	  incr ( n ) ;
	  hc [n ]= eqtb [27182 + curchr ].hh .v.RH ;
	} 
      } 
      break ;
    case 20 : 
    case 54 : 
      {
	scancharnum () ;
	curchr = curval ;
	curcmd = 73 ;
	goto lab21 ;
      } 
      break ;
    case 10 : 
    case 2 : 
      {
	if ( n > 1 ) 
	{
	  incr ( n ) ;
	  hc [n ]= curlang ;
	  {
	    if ( poolptr + n > poolsize ) 
	    overflow ( 258 , poolsize - initpoolptr ) ;
	  } 
	  h = 0 ;
	  {register integer for_end; j = 1 ;for_end = n ; if ( j <= for_end) 
	  do 
	    {
	      h = ( h + h + hc [j ]) % 607 ;
	      {
		strpool [poolptr ]= hc [j ];
		incr ( poolptr ) ;
	      } 
	    } 
	  while ( j++ < for_end ) ;} 
	  s = makestring () ;
	  if ( hyphnext <= 607 ) 
	  while ( ( hyphnext > 0 ) && ( hyphword [hyphnext - 1 ]> 0 ) ) decr 
	  ( hyphnext ) ;
	  if ( ( hyphcount == hyphsize ) || ( hyphnext == 0 ) ) 
	  overflow ( 1005 , hyphsize ) ;
	  incr ( hyphcount ) ;
	  while ( hyphword [h ]!= 0 ) {
	      
	    k = hyphword [h ];
	    if ( ( strstart [k + 1 ]- strstart [k ]) != ( strstart [s + 1 
	    ]- strstart [s ]) ) 
	    goto lab45 ;
	    u = strstart [k ];
	    v = strstart [s ];
	    do {
		if ( strpool [u ]!= strpool [v ]) 
	      goto lab45 ;
	      incr ( u ) ;
	      incr ( v ) ;
	    } while ( ! ( u == strstart [k + 1 ]) ) ;
	    {
	      decr ( strptr ) ;
	      poolptr = strstart [strptr ];
	    } 
	    s = hyphword [h ];
	    decr ( hyphcount ) ;
	    goto lab40 ;
	    lab45: ;
	    if ( hyphlink [h ]== 0 ) 
	    {
	      hyphlink [h ]= hyphnext ;
	      if ( hyphnext >= hyphsize ) 
	      hyphnext = 607 ;
	      if ( hyphnext > 607 ) 
	      incr ( hyphnext ) ;
	    } 
	    h = hyphlink [h ]- 1 ;
	  } 
	  lab40: hyphword [h ]= s ;
	  hyphlist [h ]= p ;
	} 
	if ( curcmd == 2 ) 
	return ;
	n = 0 ;
	p = -1073741823L ;
      } 
      break ;
      default: 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 721 ) ;
	} 
	printesc ( 998 ) ;
	print ( 999 ) ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1000 ;
	  helpline [0 ]= 1001 ;
	} 
	error () ;
      } 
      break ;
    } 
  } 
} 
halfword 
zprunepagetop ( halfword p ) 
{
  register halfword Result; prunepagetop_regmem 
  halfword prevp  ;
  halfword q  ;
  prevp = memtop - 3 ;
  mem [memtop - 3 ].hh .v.RH = p ;
  while ( p != -1073741823L ) switch ( mem [p ].hh.b0 ) 
  {case 2 : 
  case 0 : 
  case 1 : 
  case 3 : 
    {
      q = newskipparam ( 10 ) ;
      mem [prevp ].hh .v.RH = q ;
      mem [q ].hh .v.RH = p ;
      if ( mem [tempptr + 1 ].cint > mem [p + 3 ].cint ) 
      mem [tempptr + 1 ].cint = mem [tempptr + 1 ].cint - mem [p + 3 ]
      .cint ;
      else mem [tempptr + 1 ].cint = 0 ;
      p = -1073741823L ;
    } 
    break ;
  case 10 : 
  case 6 : 
  case 4 : 
    {
      prevp = p ;
      p = mem [prevp ].hh .v.RH ;
    } 
    break ;
  case 12 : 
  case 13 : 
  case 14 : 
    {
      q = p ;
      p = mem [q ].hh .v.RH ;
      mem [q ].hh .v.RH = -1073741823L ;
      mem [prevp ].hh .v.RH = p ;
      flushnodelist ( q ) ;
    } 
    break ;
    default: 
    confusion ( 1016 ) ;
    break ;
  } 
  Result = mem [memtop - 3 ].hh .v.RH ;
  return Result ;
} 
halfword 
zvertbreak ( halfword p , scaled h , scaled d ) 
{
  /* 30 45 90 */ register halfword Result; vertbreak_regmem 
  halfword prevp  ;
  halfword q, r  ;
  integer pi  ;
  integer b  ;
  integer leastcost  ;
  halfword bestplace  ;
  scaled prevdp  ;
  smallnumber t  ;
  prevp = p ;
  leastcost = 1073741823L ;
  activewidth [1 ]= 0 ;
  activewidth [2 ]= 0 ;
  activewidth [3 ]= 0 ;
  activewidth [4 ]= 0 ;
  activewidth [5 ]= 0 ;
  activewidth [6 ]= 0 ;
  prevdp = 0 ;
  while ( true ) {
      
    if ( p == -1073741823L ) 
    pi = -10000 ;
    else switch ( mem [p ].hh.b0 ) 
    {case 2 : 
    case 0 : 
    case 1 : 
    case 3 : 
      {
	activewidth [1 ]= activewidth [1 ]+ prevdp + mem [p + 3 ].cint ;
	prevdp = mem [p + 2 ].cint ;
	goto lab45 ;
      } 
      break ;
    case 10 : 
      goto lab45 ;
      break ;
    case 12 : 
      if ( ( mem [prevp ].hh.b0 < 11 ) ) 
      pi = 0 ;
      else goto lab90 ;
      break ;
    case 13 : 
      {
	if ( mem [p ].hh .v.RH == -1073741823L ) 
	t = 14 ;
	else t = mem [mem [p ].hh .v.RH ].hh.b0 ;
	if ( t == 12 ) 
	pi = 0 ;
	else goto lab90 ;
      } 
      break ;
    case 14 : 
      pi = mem [p + 1 ].cint ;
      break ;
    case 6 : 
    case 4 : 
      goto lab45 ;
      break ;
      default: 
      confusion ( 1017 ) ;
      break ;
    } 
    if ( pi < 10000 ) 
    {
      if ( activewidth [1 ]< h ) {
	  
	if ( ( activewidth [3 ]!= 0 ) || ( activewidth [4 ]!= 0 ) || ( 
	activewidth [5 ]!= 0 ) ) 
	b = 0 ;
	else b = badness ( h - activewidth [1 ], activewidth [2 ]) ;
      } 
      else if ( activewidth [1 ]- h > activewidth [6 ]) 
      b = 1073741823L ;
      else b = badness ( activewidth [1 ]- h , activewidth [6 ]) ;
      if ( b < 1073741823L ) {
	  
	if ( pi <= -10000 ) 
	b = pi ;
	else if ( b < 10000 ) 
	b = b + pi ;
	else b = 100000L ;
      } 
      if ( b <= leastcost ) 
      {
	bestplace = p ;
	leastcost = b ;
	bestheightplusdepth = activewidth [1 ]+ prevdp ;
      } 
      if ( ( b == 1073741823L ) || ( pi <= -10000 ) ) 
      goto lab30 ;
    } 
    if ( ( mem [p ].hh.b0 < 12 ) || ( mem [p ].hh.b0 > 13 ) ) 
    goto lab45 ;
    lab90: if ( mem [p ].hh.b0 == 13 ) 
    q = p ;
    else {
	
      q = mem [p + 1 ].hh .v.LH ;
      activewidth [2 + mem [q ].hh.b0 ]= activewidth [2 + mem [q ]
      .hh.b0 ]+ mem [q + 2 ].cint ;
      activewidth [6 ]= activewidth [6 ]+ mem [q + 3 ].cint ;
      if ( ( mem [q ].hh.b1 != 0 ) && ( mem [q + 3 ].cint != 0 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1018 ) ;
	} 
	{
	  helpptr = 4 ;
	  helpline [3 ]= 1019 ;
	  helpline [2 ]= 1020 ;
	  helpline [1 ]= 1021 ;
	  helpline [0 ]= 979 ;
	} 
	error () ;
	r = newspec ( q ) ;
	mem [r ].hh.b1 = 0 ;
	deleteglueref ( q ) ;
	mem [p + 1 ].hh .v.LH = r ;
	q = r ;
      } 
    } 
    activewidth [1 ]= activewidth [1 ]+ prevdp + mem [q + 1 ].cint ;
    prevdp = 0 ;
    lab45: if ( prevdp > d ) 
    {
      activewidth [1 ]= activewidth [1 ]+ prevdp - d ;
      prevdp = d ;
    } 
    prevp = p ;
    p = mem [prevp ].hh .v.RH ;
  } 
  lab30: Result = bestplace ;
  return Result ;
} 
halfword 
zvsplit ( eightbits n , scaled h ) 
{
  /* 10 30 */ register halfword Result; vsplit_regmem 
  halfword v  ;
  halfword w  ;
  halfword p  ;
  halfword q  ;
  v = eqtb [25326 + n ].hh .v.RH ;
  if ( curmark [3 ]!= -1073741823L ) 
  {
    deletetokenref ( curmark [3 ]) ;
    curmark [3 ]= -1073741823L ;
    deletetokenref ( curmark [4 ]) ;
    curmark [4 ]= -1073741823L ;
  } 
  if ( v == -1073741823L ) 
  {
    Result = -1073741823L ;
    return Result ;
  } 
  if ( mem [v ].hh.b0 == 2 ) 
  {
    w = v ;
    v = mem [v + 5 ].hh .v.RH ;
    deleteglueref ( mem [w + 7 ].hh .v.RH ) ;
    deleteglueref ( mem [w + 7 ].hh .v.LH ) ;
    freenode ( w , 10 ) ;
  } 
  if ( mem [v ].hh.b0 != 1 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 344 ) ;
    } 
    printesc ( 1022 ) ;
    print ( 1023 ) ;
    printesc ( 1024 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 1025 ;
      helpline [0 ]= 1026 ;
    } 
    error () ;
    Result = -1073741823L ;
    return Result ;
  } 
  flushnodelist ( mem [v ].hh .v.RH ) ;
  mem [v ].hh .v.RH = -1073741823L ;
  q = vertbreak ( mem [v + 5 ].hh .v.RH , h , eqtb [29044 ].cint ) ;
  p = mem [v + 5 ].hh .v.RH ;
  if ( p == q ) 
  mem [v + 5 ].hh .v.RH = -1073741823L ;
  else while ( true ) {
      
    if ( mem [p ].hh.b0 == 6 ) {
	
      if ( curmark [3 ]== -1073741823L ) 
      {
	curmark [3 ]= mem [p + 1 ].cint ;
	curmark [4 ]= curmark [3 ];
	mem [curmark [3 ]].hh .v.LH = mem [curmark [3 ]].hh .v.LH + 2 
	;
      } 
      else {
	  
	deletetokenref ( curmark [4 ]) ;
	curmark [4 ]= mem [p + 1 ].cint ;
	incr ( mem [curmark [4 ]].hh .v.LH ) ;
      } 
    } 
    if ( mem [p ].hh .v.RH == q ) 
    {
      mem [p ].hh .v.RH = -1073741823L ;
      goto lab30 ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  lab30: ;
  q = prunepagetop ( q ) ;
  p = mem [v + 5 ].hh .v.RH ;
  if ( q == -1073741823L ) 
  eqtb [25326 + n ].hh .v.RH = -1073741823L ;
  else {
      
    eqtb [25326 + n ].hh .v.RH = vpackage ( q , 0 , 1 , 1073741823L ) ;
    mem [eqtb [25326 + n ].hh .v.RH ].hh.b1 = ( mem [v ].hh.b1 ) ;
  } 
  q = vpackage ( p , h , 0 , eqtb [29044 ].cint ) ;
  mem [q ].hh.b1 = ( mem [v ].hh.b1 ) ;
  deleteglueref ( mem [v + 7 ].hh .v.RH ) ;
  deleteglueref ( mem [v + 7 ].hh .v.LH ) ;
  freenode ( v , 10 ) ;
  Result = q ;
  return Result ;
} 
void 
printtotals ( void ) 
{
  printtotals_regmem 
  printscaled ( pagesofar [1 ]) ;
  if ( pagesofar [2 ]!= 0 ) 
  {
    print ( 316 ) ;
    printscaled ( pagesofar [2 ]) ;
    print ( 344 ) ;
  } 
  if ( pagesofar [3 ]!= 0 ) 
  {
    print ( 316 ) ;
    printscaled ( pagesofar [3 ]) ;
    print ( 315 ) ;
  } 
  if ( pagesofar [4 ]!= 0 ) 
  {
    print ( 316 ) ;
    printscaled ( pagesofar [4 ]) ;
    print ( 1035 ) ;
  } 
  if ( pagesofar [5 ]!= 0 ) 
  {
    print ( 316 ) ;
    printscaled ( pagesofar [5 ]) ;
    print ( 1036 ) ;
  } 
  if ( pagesofar [6 ]!= 0 ) 
  {
    print ( 317 ) ;
    printscaled ( pagesofar [6 ]) ;
  } 
} 
void 
zfreezepagespecs ( smallnumber s ) 
{
  freezepagespecs_regmem 
  pagecontents = s ;
  pagesofar [0 ]= eqtb [29042 ].cint ;
  pagemaxdepth = eqtb [29043 ].cint ;
  pagesofar [7 ]= 0 ;
  pagesofar [1 ]= 0 ;
  pagesofar [2 ]= 0 ;
  pagesofar [3 ]= 0 ;
  pagesofar [4 ]= 0 ;
  pagesofar [5 ]= 0 ;
  pagesofar [6 ]= 0 ;
  leastpagecost = 1073741823L ;
	;
#ifdef STAT
  if ( eqtb [28495 ].cint > 0 ) 
  {
    begindiagnostic () ;
    printnl ( 1044 ) ;
    printscaled ( pagesofar [0 ]) ;
    print ( 1045 ) ;
    printscaled ( pagemaxdepth ) ;
    enddiagnostic ( false ) ;
  } 
#endif /* STAT */
} 
void 
zboxerror ( eightbits n ) 
{
  boxerror_regmem 
  error () ;
  begindiagnostic () ;
  printnl ( 892 ) ;
  showbox ( eqtb [25326 + n ].hh .v.RH ) ;
  enddiagnostic ( true ) ;
  flushnodelist ( eqtb [25326 + n ].hh .v.RH ) ;
  eqtb [25326 + n ].hh .v.RH = -1073741823L ;
} 
void 
zensurevbox ( eightbits n ) 
{
  ensurevbox_regmem 
  halfword p  ;
  p = eqtb [25326 + n ].hh .v.RH ;
  if ( p != -1073741823L ) {
      
    if ( mem [p ].hh.b0 == 2 ) 
    {
      p = mem [p + 5 ].hh .v.RH ;
      deleteglueref ( mem [eqtb [25326 + n ].hh .v.RH + 7 ].hh .v.RH ) ;
      deleteglueref ( mem [eqtb [25326 + n ].hh .v.RH + 7 ].hh .v.LH ) ;
      freenode ( eqtb [25326 + n ].hh .v.RH , 10 ) ;
      eqtb [25326 + n ].hh .v.RH = p ;
    } 
  } 
  if ( p != -1073741823L ) {
      
    if ( mem [p ].hh.b0 != 1 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1046 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 1047 ;
	helpline [1 ]= 1048 ;
	helpline [0 ]= 1049 ;
      } 
      boxerror ( n ) ;
    } 
  } 
} 
void 
zfireup ( halfword c ) 
{
  /* 10 */ fireup_regmem 
  halfword p, q, r, s  ;
  halfword prevp  ;
  unsigned char n  ;
  boolean wait  ;
  integer savevbadness  ;
  scaled savevfuzz  ;
  halfword savesplittopskip  ;
  if ( mem [bestpagebreak ].hh.b0 == 14 ) 
  {
    geqworddefine ( 28501 , mem [bestpagebreak + 1 ].cint ) ;
    mem [bestpagebreak + 1 ].cint = 10000 ;
  } 
  else geqworddefine ( 28501 , 10000 ) ;
  if ( curmark [2 ]!= -1073741823L ) 
  {
    if ( curmark [0 ]!= -1073741823L ) 
    deletetokenref ( curmark [0 ]) ;
    curmark [0 ]= curmark [2 ];
    incr ( mem [curmark [0 ]].hh .v.LH ) ;
    deletetokenref ( curmark [1 ]) ;
    curmark [1 ]= -1073741823L ;
  } 
  if ( c == bestpagebreak ) 
  bestpagebreak = -1073741823L ;
  if ( eqtb [25581 ].hh .v.RH != -1073741823L ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 344 ) ;
    } 
    printesc ( 428 ) ;
    print ( 1062 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 1063 ;
      helpline [0 ]= 1049 ;
    } 
    boxerror ( 255 ) ;
  } 
  insertpenalties = 0 ;
  savesplittopskip = eqtb [24537 ].hh .v.RH ;
  if ( eqtb [28516 ].cint <= 0 ) 
  {
    r = mem [memtop ].hh .v.RH ;
    while ( r != memtop ) {
	
      if ( mem [r + 2 ].hh .v.LH != -1073741823L ) 
      {
	n = mem [r ].hh.b1 ;
	ensurevbox ( n ) ;
	if ( eqtb [25326 + n ].hh .v.RH == -1073741823L ) 
	eqtb [25326 + n ].hh .v.RH = newnullbox () ;
	p = eqtb [25326 + n ].hh .v.RH + 5 ;
	while ( mem [p ].hh .v.RH != -1073741823L ) p = mem [p ].hh .v.RH 
	;
	mem [r + 2 ].hh .v.RH = p ;
      } 
      r = mem [r ].hh .v.RH ;
    } 
  } 
  q = memtop - 4 ;
  mem [q ].hh .v.RH = -1073741823L ;
  prevp = memtop - 2 ;
  p = mem [prevp ].hh .v.RH ;
  while ( p != bestpagebreak ) {
      
    if ( mem [p ].hh.b0 == 4 ) 
    {
      if ( eqtb [28516 ].cint <= 0 ) 
      {
	r = mem [memtop ].hh .v.RH ;
	while ( mem [r ].hh.b1 != mem [p ].hh.b1 ) r = mem [r ].hh .v.RH 
	;
	if ( mem [r + 2 ].hh .v.LH == -1073741823L ) 
	wait = true ;
	else {
	    
	  wait = false ;
	  n = mem [p ].hh.b1 ;
	  switch ( ( mem [eqtb [25326 + n ].hh .v.RH ].hh.b1 ) ) 
	  {case 4 : 
	  case 3 : 
	  case 1 : 
	    if ( mem [p + 5 ].hh.b1 != ( mem [eqtb [25326 + n ].hh .v.RH 
	    ].hh.b1 ) ) 
	    {
	      {
		if ( interaction == 3 ) 
		;
		if ( filelineerrorstylep ) 
		printfileline () ;
		else printnl ( 263 ) ;
		print ( 1055 ) ;
	      } 
	      {
		helpptr = 3 ;
		helpline [2 ]= 1047 ;
		helpline [1 ]= 1056 ;
		helpline [0 ]= 1049 ;
	      } 
	      boxerror ( n ) ;
	      eqtb [25326 + n ].hh .v.RH = newnullbox () ;
	      mem [r + 2 ].hh .v.RH = eqtb [25326 + n ].hh .v.RH + 5 ;
	    } 
	    break ;
	    default: 
	    mem [eqtb [25326 + n ].hh .v.RH ].hh.b1 = mem [p + 5 ].hh.b1 
	    ;
	    break ;
	  } 
	  s = mem [r + 2 ].hh .v.RH ;
	  mem [s ].hh .v.RH = mem [p + 4 ].hh .v.LH ;
	  if ( mem [r + 2 ].hh .v.LH == p ) 
	  {
	    if ( mem [r ].hh.b0 == 1 ) {
		
	      if ( ( mem [r + 1 ].hh .v.LH == p ) && ( mem [r + 1 ].hh 
	      .v.RH != -1073741823L ) ) 
	      {
		while ( mem [s ].hh .v.RH != mem [r + 1 ].hh .v.RH ) s = 
		mem [s ].hh .v.RH ;
		mem [s ].hh .v.RH = -1073741823L ;
		eqtb [24537 ].hh .v.RH = mem [p + 4 ].hh .v.RH ;
		mem [p + 4 ].hh .v.LH = prunepagetop ( mem [r + 1 ].hh 
		.v.RH ) ;
		if ( mem [p + 4 ].hh .v.LH != -1073741823L ) 
		{
		  tempptr = vpackage ( mem [p + 4 ].hh .v.LH , 0 , 1 , 
		  1073741823L ) ;
		  mem [p + 3 ].cint = mem [tempptr + 3 ].cint + mem [
		  tempptr + 2 ].cint ;
		  deleteglueref ( mem [tempptr + 7 ].hh .v.RH ) ;
		  deleteglueref ( mem [tempptr + 7 ].hh .v.LH ) ;
		  freenode ( tempptr , 10 ) ;
		  wait = true ;
		} 
	      } 
	    } 
	    mem [r + 2 ].hh .v.LH = -1073741823L ;
	    n = mem [r ].hh.b1 ;
	    tempptr = mem [eqtb [25326 + n ].hh .v.RH + 5 ].hh .v.RH ;
	    deleteglueref ( mem [eqtb [25326 + n ].hh .v.RH + 7 ].hh .v.RH 
	    ) ;
	    deleteglueref ( mem [eqtb [25326 + n ].hh .v.RH + 7 ].hh .v.LH 
	    ) ;
	    flushnodelist ( mem [eqtb [25326 + n ].hh .v.RH ].hh .v.RH ) ;
	    freenode ( eqtb [25326 + n ].hh .v.RH , 10 ) ;
	    eqtb [25326 + n ].hh .v.RH = vpackage ( tempptr , 0 , 1 , 
	    1073741823L ) ;
	    mem [eqtb [25326 + n ].hh .v.RH ].hh.b1 = mem [p + 5 ].hh.b1 
	    ;
	  } 
	  else {
	      
	    while ( mem [s ].hh .v.RH != -1073741823L ) s = mem [s ].hh 
	    .v.RH ;
	    mem [r + 2 ].hh .v.RH = s ;
	  } 
	} 
	mem [prevp ].hh .v.RH = mem [p ].hh .v.RH ;
	mem [p ].hh .v.RH = -1073741823L ;
	if ( wait ) 
	{
	  mem [q ].hh .v.RH = p ;
	  q = p ;
	  incr ( insertpenalties ) ;
	} 
	else {
	    
	  deleteglueref ( mem [p + 4 ].hh .v.RH ) ;
	  freenode ( p , 6 ) ;
	} 
	p = prevp ;
      } 
    } 
    else if ( mem [p ].hh.b0 == 6 ) 
    {
      if ( curmark [1 ]== -1073741823L ) 
      {
	curmark [1 ]= mem [p + 1 ].cint ;
	incr ( mem [curmark [1 ]].hh .v.LH ) ;
      } 
      if ( curmark [2 ]!= -1073741823L ) 
      deletetokenref ( curmark [2 ]) ;
      curmark [2 ]= mem [p + 1 ].cint ;
      incr ( mem [curmark [2 ]].hh .v.LH ) ;
    } 
    prevp = p ;
    p = mem [prevp ].hh .v.RH ;
  } 
  eqtb [24537 ].hh .v.RH = savesplittopskip ;
  if ( p != -1073741823L ) 
  {
    if ( mem [memtop - 1 ].hh .v.RH == -1073741823L ) {
	
      if ( nestptr == 0 ) 
      curlist .tailfield = pagetail ;
      else nest [0 ].tailfield = pagetail ;
    } 
    mem [pagetail ].hh .v.RH = mem [memtop - 1 ].hh .v.RH ;
    mem [memtop - 1 ].hh .v.RH = p ;
    mem [prevp ].hh .v.RH = -1073741823L ;
  } 
  savevbadness = eqtb [28489 ].cint ;
  eqtb [28489 ].cint = 10000 ;
  savevfuzz = eqtb [29047 ].cint ;
  eqtb [29047 ].cint = 1073741823L ;
  eqtb [25581 ].hh .v.RH = vpackage ( mem [memtop - 2 ].hh .v.RH , 
  bestsize , 0 , pagemaxdepth ) ;
  mem [eqtb [25581 ].hh .v.RH ].hh.b1 = pagedir ;
  eqtb [28489 ].cint = savevbadness ;
  eqtb [29047 ].cint = savevfuzz ;
  if ( lastglue != 1073741823L ) 
  deleteglueref ( lastglue ) ;
  pagecontents = 0 ;
  pagetail = memtop - 2 ;
  mem [memtop - 2 ].hh .v.RH = -1073741823L ;
  lastglue = 1073741823L ;
  lastpenalty = 0 ;
  lastkern = 0 ;
  pagesofar [7 ]= 0 ;
  pagemaxdepth = 0 ;
  if ( q != memtop - 4 ) 
  {
    mem [memtop - 2 ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
    pagetail = q ;
  } 
  r = mem [memtop ].hh .v.RH ;
  while ( r != memtop ) {
      
    q = mem [r ].hh .v.RH ;
    freenode ( r , 4 ) ;
    r = q ;
  } 
  mem [memtop ].hh .v.RH = memtop ;
  if ( ( curmark [0 ]!= -1073741823L ) && ( curmark [1 ]== -1073741823L ) 
  ) 
  {
    curmark [1 ]= curmark [0 ];
    incr ( mem [curmark [0 ]].hh .v.LH ) ;
  } 
  if ( eqtb [25061 ].hh .v.RH != -1073741823L ) {
      
    if ( deadcycles >= eqtb [28502 ].cint ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1064 ) ;
      } 
      printint ( deadcycles ) ;
      print ( 1065 ) ;
      {
	helpptr = 3 ;
	helpline [2 ]= 1066 ;
	helpline [1 ]= 1067 ;
	helpline [0 ]= 1068 ;
      } 
      error () ;
    } 
    else {
	
      outputactive = true ;
      incr ( deadcycles ) ;
      pushnest () ;
      curlist .modefield = -1 ;
      curlist .auxfield .cint = -65536000L ;
      curlist .mlfield = - (integer) line ;
      begintokenlist ( eqtb [25061 ].hh .v.RH , 6 ) ;
      newsavelevel ( 8 ) ;
      normalparagraph () ;
      scanleftbrace () ;
      return ;
    } 
  } 
  {
    if ( mem [memtop - 2 ].hh .v.RH != -1073741823L ) 
    {
      if ( mem [memtop - 1 ].hh .v.RH == -1073741823L ) {
	  
	if ( nestptr == 0 ) 
	curlist .tailfield = pagetail ;
	else nest [0 ].tailfield = pagetail ;
      } 
      else mem [pagetail ].hh .v.RH = mem [memtop - 1 ].hh .v.RH ;
      mem [memtop - 1 ].hh .v.RH = mem [memtop - 2 ].hh .v.RH ;
      mem [memtop - 2 ].hh .v.RH = -1073741823L ;
      pagetail = memtop - 2 ;
    } 
    shipout ( eqtb [25581 ].hh .v.RH ) ;
    eqtb [25581 ].hh .v.RH = -1073741823L ;
  } 
} 
void 
buildpage ( void ) 
{
  /* 10 30 31 22 80 90 */ buildpage_regmem 
  halfword p  ;
  halfword q, r  ;
  integer b, c  ;
  integer pi  ;
  unsigned char n  ;
  scaled delta, h, w  ;
  if ( ( mem [memtop - 1 ].hh .v.RH == -1073741823L ) || outputactive ) 
  return ;
  do {
      lab22: p = mem [memtop - 1 ].hh .v.RH ;
    if ( lastglue != 1073741823L ) 
    deleteglueref ( lastglue ) ;
    lastpenalty = 0 ;
    lastkern = 0 ;
    if ( mem [p ].hh.b0 == 12 ) 
    {
      lastglue = mem [p + 1 ].hh .v.LH ;
      incr ( mem [lastglue ].hh .v.RH ) ;
    } 
    else {
	
      lastglue = 1073741823L ;
      if ( mem [p ].hh.b0 == 14 ) 
      lastpenalty = mem [p + 1 ].cint ;
      else if ( mem [p ].hh.b0 == 13 ) 
      lastkern = mem [p + 1 ].cint ;
    } 
    switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
    case 3 : 
      if ( pagecontents < 2 ) 
      {
	if ( pagecontents == 0 ) 
	freezepagespecs ( 2 ) ;
	else pagecontents = 2 ;
	q = newskipparam ( 9 ) ;
	if ( mem [tempptr + 1 ].cint > mem [p + 3 ].cint ) 
	mem [tempptr + 1 ].cint = mem [tempptr + 1 ].cint - mem [p + 3 ]
	.cint ;
	else mem [tempptr + 1 ].cint = 0 ;
	mem [q ].hh .v.RH = p ;
	mem [memtop - 1 ].hh .v.RH = q ;
	goto lab22 ;
      } 
      else {
	  
	pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]+ mem [p + 3 ]
	.cint ;
	pagesofar [7 ]= mem [p + 2 ].cint ;
	goto lab80 ;
      } 
      break ;
    case 10 : 
      goto lab80 ;
      break ;
    case 12 : 
      if ( pagecontents < 2 ) 
      goto lab31 ;
      else if ( ( mem [pagetail ].hh.b0 < 11 ) ) 
      pi = 0 ;
      else goto lab90 ;
      break ;
    case 13 : 
      if ( pagecontents < 2 ) 
      goto lab31 ;
      else if ( mem [p ].hh .v.RH == -1073741823L ) 
      return ;
      else if ( mem [mem [p ].hh .v.RH ].hh.b0 == 12 ) 
      pi = 0 ;
      else goto lab90 ;
      break ;
    case 14 : 
      if ( pagecontents < 2 ) 
      goto lab31 ;
      else pi = mem [p + 1 ].cint ;
      break ;
    case 6 : 
      goto lab80 ;
      break ;
    case 4 : 
      {
	if ( pagecontents == 0 ) 
	freezepagespecs ( 1 ) ;
	n = mem [p ].hh.b1 ;
	r = memtop ;
	while ( n >= mem [mem [r ].hh .v.RH ].hh.b1 ) r = mem [r ].hh 
	.v.RH ;
	n = n ;
	if ( mem [r ].hh.b1 != n ) 
	{
	  q = getnode ( 4 ) ;
	  mem [q ].hh .v.RH = mem [r ].hh .v.RH ;
	  mem [r ].hh .v.RH = q ;
	  r = q ;
	  mem [r ].hh.b1 = n ;
	  mem [r ].hh.b0 = 0 ;
	  ensurevbox ( n ) ;
	  if ( eqtb [25326 + n ].hh .v.RH == -1073741823L ) 
	  mem [r + 3 ].cint = 0 ;
	  else {
	      
	    if ( mem [p + 5 ].hh.b1 != ( mem [eqtb [25326 + n ].hh .v.RH 
	    ].hh.b1 ) ) 
	    {
	      {
		if ( interaction == 3 ) 
		;
		if ( filelineerrorstylep ) 
		printfileline () ;
		else printnl ( 263 ) ;
		print ( 1055 ) ;
	      } 
	      {
		helpptr = 3 ;
		helpline [2 ]= 1047 ;
		helpline [1 ]= 1056 ;
		helpline [0 ]= 1049 ;
	      } 
	      boxerror ( n ) ;
	    } 
	    else mem [r + 3 ].cint = mem [eqtb [25326 + n ].hh .v.RH + 3 
	    ].cint + mem [eqtb [25326 + n ].hh .v.RH + 2 ].cint ;
	  } 
	  mem [r + 2 ].hh .v.LH = -1073741823L ;
	  q = eqtb [24548 + n ].hh .v.RH ;
	  if ( eqtb [28526 + n ].cint == 1000 ) 
	  h = mem [r + 3 ].cint ;
	  else h = xovern ( mem [r + 3 ].cint , 1000 ) * eqtb [28526 + n ]
	  .cint ;
	  pagesofar [0 ]= pagesofar [0 ]- h - mem [q + 1 ].cint ;
	  pagesofar [2 + mem [q ].hh.b0 ]= pagesofar [2 + mem [q ]
	  .hh.b0 ]+ mem [q + 2 ].cint ;
	  pagesofar [6 ]= pagesofar [6 ]+ mem [q + 3 ].cint ;
	  if ( ( mem [q ].hh.b1 != 0 ) && ( mem [q + 3 ].cint != 0 ) ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 263 ) ;
	      print ( 1057 ) ;
	    } 
	    printesc ( 414 ) ;
	    printint ( n ) ;
	    {
	      helpptr = 3 ;
	      helpline [2 ]= 1058 ;
	      helpline [1 ]= 1059 ;
	      helpline [0 ]= 979 ;
	    } 
	    error () ;
	  } 
	} 
	if ( mem [r ].hh.b0 == 1 ) 
	insertpenalties = insertpenalties + mem [p + 1 ].cint ;
	else {
	    
	  mem [r + 2 ].hh .v.RH = p ;
	  delta = pagesofar [0 ]- pagesofar [1 ]- pagesofar [7 ]+ 
	  pagesofar [6 ];
	  if ( eqtb [28526 + n ].cint == 1000 ) 
	  h = mem [p + 3 ].cint ;
	  else h = xovern ( mem [p + 3 ].cint , 1000 ) * eqtb [28526 + n ]
	  .cint ;
	  if ( ( ( h <= 0 ) || ( h <= delta ) ) && ( mem [p + 3 ].cint + mem 
	  [r + 3 ].cint <= eqtb [29061 + n ].cint ) ) 
	  {
	    pagesofar [0 ]= pagesofar [0 ]- h ;
	    mem [r + 3 ].cint = mem [r + 3 ].cint + mem [p + 3 ].cint ;
	  } 
	  else {
	      
	    if ( eqtb [28526 + n ].cint <= 0 ) 
	    w = 1073741823L ;
	    else {
		
	      w = pagesofar [0 ]- pagesofar [1 ]- pagesofar [7 ];
	      if ( eqtb [28526 + n ].cint != 1000 ) 
	      w = xovern ( w , eqtb [28526 + n ].cint ) * 1000 ;
	    } 
	    if ( w > eqtb [29061 + n ].cint - mem [r + 3 ].cint ) 
	    w = eqtb [29061 + n ].cint - mem [r + 3 ].cint ;
	    q = vertbreak ( mem [p + 4 ].hh .v.LH , w , mem [p + 2 ].cint 
	    ) ;
	    mem [r + 3 ].cint = mem [r + 3 ].cint + bestheightplusdepth ;
	;
#ifdef STAT
	    if ( eqtb [28495 ].cint > 0 ) 
	    {
	      begindiagnostic () ;
	      printnl ( 1060 ) ;
	      printint ( n ) ;
	      print ( 1061 ) ;
	      printscaled ( w ) ;
	      printchar ( 44 ) ;
	      printscaled ( bestheightplusdepth ) ;
	      print ( 988 ) ;
	      if ( q == -1073741823L ) 
	      printint ( -10000 ) ;
	      else if ( mem [q ].hh.b0 == 14 ) 
	      printint ( mem [q + 1 ].cint ) ;
	      else printchar ( 48 ) ;
	      enddiagnostic ( false ) ;
	    } 
#endif /* STAT */
	    if ( eqtb [28526 + n ].cint != 1000 ) 
	    bestheightplusdepth = xovern ( bestheightplusdepth , 1000 ) * eqtb 
	    [28526 + n ].cint ;
	    pagesofar [0 ]= pagesofar [0 ]- bestheightplusdepth ;
	    mem [r ].hh.b0 = 1 ;
	    mem [r + 1 ].hh .v.RH = q ;
	    mem [r + 1 ].hh .v.LH = p ;
	    if ( q == -1073741823L ) 
	    insertpenalties = insertpenalties - 10000 ;
	    else if ( mem [q ].hh.b0 == 14 ) 
	    insertpenalties = insertpenalties + mem [q + 1 ].cint ;
	  } 
	} 
	goto lab80 ;
      } 
      break ;
      default: 
      confusion ( 1050 ) ;
      break ;
    } 
    if ( pi < 10000 ) 
    {
      if ( pagesofar [1 ]< pagesofar [0 ]) {
	  
	if ( ( pagesofar [3 ]!= 0 ) || ( pagesofar [4 ]!= 0 ) || ( 
	pagesofar [5 ]!= 0 ) ) 
	b = 0 ;
	else b = badness ( pagesofar [0 ]- pagesofar [1 ], pagesofar [2 ]
	) ;
      } 
      else if ( pagesofar [1 ]- pagesofar [0 ]> pagesofar [6 ]) 
      b = 1073741823L ;
      else b = badness ( pagesofar [1 ]- pagesofar [0 ], pagesofar [6 ]) 
      ;
      if ( b < 1073741823L ) {
	  
	if ( pi <= -10000 ) 
	c = pi ;
	else if ( b < 10000 ) 
	c = b + pi + insertpenalties ;
	else c = 100000L ;
      } 
      else c = b ;
      if ( insertpenalties >= 10000 ) 
      c = 1073741823L ;
	;
#ifdef STAT
      if ( eqtb [28495 ].cint > 0 ) 
      {
	begindiagnostic () ;
	printnl ( 37 ) ;
	print ( 984 ) ;
	printtotals () ;
	print ( 1053 ) ;
	printscaled ( pagesofar [0 ]) ;
	print ( 987 ) ;
	if ( b == 1073741823L ) 
	printchar ( 42 ) ;
	else printint ( b ) ;
	print ( 988 ) ;
	printint ( pi ) ;
	print ( 1054 ) ;
	if ( c == 1073741823L ) 
	printchar ( 42 ) ;
	else printint ( c ) ;
	if ( c <= leastpagecost ) 
	printchar ( 35 ) ;
	enddiagnostic ( false ) ;
      } 
#endif /* STAT */
      if ( c <= leastpagecost ) 
      {
	bestpagebreak = p ;
	bestsize = pagesofar [0 ];
	leastpagecost = c ;
	r = mem [memtop ].hh .v.RH ;
	while ( r != memtop ) {
	    
	  mem [r + 2 ].hh .v.LH = mem [r + 2 ].hh .v.RH ;
	  r = mem [r ].hh .v.RH ;
	} 
      } 
      if ( ( c == 1073741823L ) || ( pi <= -10000 ) ) 
      {
	fireup ( p ) ;
	if ( outputactive ) 
	return ;
	goto lab30 ;
      } 
    } 
    if ( ( mem [p ].hh.b0 < 12 ) || ( mem [p ].hh.b0 > 13 ) ) 
    goto lab80 ;
    lab90: if ( mem [p ].hh.b0 == 13 ) 
    q = p ;
    else {
	
      q = mem [p + 1 ].hh .v.LH ;
      pagesofar [2 + mem [q ].hh.b0 ]= pagesofar [2 + mem [q ].hh.b0 ]
      + mem [q + 2 ].cint ;
      pagesofar [6 ]= pagesofar [6 ]+ mem [q + 3 ].cint ;
      if ( ( mem [q ].hh.b1 != 0 ) && ( mem [q + 3 ].cint != 0 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1051 ) ;
	} 
	{
	  helpptr = 4 ;
	  helpline [3 ]= 1052 ;
	  helpline [2 ]= 1020 ;
	  helpline [1 ]= 1021 ;
	  helpline [0 ]= 979 ;
	} 
	error () ;
	r = newspec ( q ) ;
	mem [r ].hh.b1 = 0 ;
	deleteglueref ( q ) ;
	mem [p + 1 ].hh .v.LH = r ;
	q = r ;
      } 
    } 
    pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]+ mem [q + 1 ].cint 
    ;
    pagesofar [7 ]= 0 ;
    lab80: if ( pagesofar [7 ]> pagemaxdepth ) 
    {
      pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]- pagemaxdepth ;
      pagesofar [7 ]= pagemaxdepth ;
    } 
    mem [pagetail ].hh .v.RH = p ;
    pagetail = p ;
    mem [memtop - 1 ].hh .v.RH = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = -1073741823L ;
    goto lab30 ;
    lab31: mem [memtop - 1 ].hh .v.RH = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = -1073741823L ;
    flushnodelist ( p ) ;
    lab30: ;
  } while ( ! ( mem [memtop - 1 ].hh .v.RH == -1073741823L ) ) ;
  if ( nestptr == 0 ) 
  curlist .tailfield = memtop - 1 ;
  else nest [0 ].tailfield = memtop - 1 ;
} 
void 
appspace ( void ) 
{
  appspace_regmem 
  halfword q  ;
  if ( ( curlist .auxfield .hh .v.LH >= 2000 ) && ( eqtb [24540 ].hh .v.RH 
  != membot ) ) 
  q = newparamglue ( 13 ) ;
  else {
      
    if ( eqtb [24539 ].hh .v.RH != membot ) 
    mainp = eqtb [24539 ].hh .v.RH ;
    else {
	
      mainp = fontglue [eqtb [25582 ].hh .v.RH ];
      if ( mainp == -1073741823L ) 
      {
	mainp = newspec ( membot ) ;
	maink = parambase [eqtb [25582 ].hh .v.RH ]+ 2 ;
	mem [mainp + 1 ].cint = fontinfo [maink ].cint ;
	mem [mainp + 2 ].cint = fontinfo [maink + 1 ].cint ;
	mem [mainp + 3 ].cint = fontinfo [maink + 2 ].cint ;
	fontglue [eqtb [25582 ].hh .v.RH ]= mainp ;
      } 
    } 
    mainp = newspec ( mainp ) ;
    if ( curlist .auxfield .hh .v.LH >= 2000 ) 
    mem [mainp + 1 ].cint = mem [mainp + 1 ].cint + fontinfo [7 + 
    parambase [eqtb [25582 ].hh .v.RH ]].cint ;
    mem [mainp + 2 ].cint = xnoverd ( mem [mainp + 2 ].cint , curlist 
    .auxfield .hh .v.LH , 1000 ) ;
    mem [mainp + 3 ].cint = xnoverd ( mem [mainp + 3 ].cint , 1000 , 
    curlist .auxfield .hh .v.LH ) ;
    q = newglue ( mainp ) ;
    mem [mainp ].hh .v.RH = -1073741823L ;
  } 
  if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield ]
  .hh.b0 == 5 ) ) 
  {
    mem [curlist .pnodefield ].hh .v.RH = q ;
    mem [q ].hh .v.RH = curlist .tailfield ;
    curlist .pnodefield = q ;
  } 
  else {
      
    mem [curlist .tailfield ].hh .v.RH = q ;
    curlist .tailfield = q ;
  } 
} 
void 
insertdollarsign ( void ) 
{
  insertdollarsign_regmem 
  backinput () ;
  curtok = 804 ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 1076 ) ;
  } 
  {
    helpptr = 2 ;
    helpline [1 ]= 1077 ;
    helpline [0 ]= 1078 ;
  } 
  inserror () ;
} 
void 
youcant ( void ) 
{
  youcant_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 726 ) ;
  } 
  printcmdchr ( curcmd , curchr ) ;
  printinmode ( curlist .modefield ) ;
} 
void 
reportillegalcase ( void ) 
{
  reportillegalcase_regmem 
  youcant () ;
  {
    helpptr = 4 ;
    helpline [3 ]= 1079 ;
    helpline [2 ]= 1080 ;
    helpline [1 ]= 1081 ;
    helpline [0 ]= 1082 ;
  } 
  error () ;
} 
boolean 
privileged ( void ) 
{
  register boolean Result; privileged_regmem 
  if ( curlist .modefield > 0 ) 
  Result = true ;
  else {
      
    reportillegalcase () ;
    Result = false ;
  } 
  return Result ;
} 
boolean 
itsallover ( void ) 
{
  /* 10 */ register boolean Result; itsallover_regmem 
  if ( privileged () ) 
  {
    if ( ( memtop - 2 == pagetail ) && ( curlist .headfield == curlist 
    .tailfield ) && ( deadcycles == 0 ) ) 
    {
      Result = true ;
      return Result ;
    } 
    backinput () ;
    {
      mem [curlist .tailfield ].hh .v.RH = newnullbox () ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield + 1 ].cint = eqtb [29041 ].cint ;
    {
      mem [curlist .tailfield ].hh .v.RH = newglue ( membot + 8 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( -1073741824L ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    buildpage () ;
  } 
  Result = false ;
  return Result ;
} 
void 
appendglue ( void ) 
{
  appendglue_regmem 
  smallnumber s  ;
  s = curchr ;
  switch ( s ) 
  {case 0 : 
    curval = membot + 4 ;
    break ;
  case 1 : 
    curval = membot + 8 ;
    break ;
  case 2 : 
    curval = membot + 12 ;
    break ;
  case 3 : 
    curval = membot + 16 ;
    break ;
  case 4 : 
    scanglue ( 2 ) ;
    break ;
  case 5 : 
    scanglue ( 3 ) ;
    break ;
  } 
  {
    mem [curlist .tailfield ].hh .v.RH = newglue ( curval ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  inhibitglueflag = false ;
  if ( s >= 4 ) 
  {
    decr ( mem [curval ].hh .v.RH ) ;
    if ( s > 4 ) 
    mem [curlist .tailfield ].hh.b1 = 99 ;
  } 
} 
void 
appendkern ( void ) 
{
  appendkern_regmem 
  quarterword s  ;
  s = curchr ;
  scandimen ( s == 99 , false , false ) ;
  inhibitglueflag = false ;
  if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield ]
  .hh.b0 == 5 ) ) 
  {
    {
      mem [curlist .pnodefield ].hh .v.RH = newkern ( curval ) ;
      mem [mem [curlist .pnodefield ].hh .v.RH ].hh .v.RH = curlist 
      .tailfield ;
      curlist .pnodefield = mem [curlist .pnodefield ].hh .v.RH ;
    } 
    mem [curlist .pnodefield ].hh.b1 = s ;
  } 
  else {
      
    {
      mem [curlist .tailfield ].hh .v.RH = newkern ( curval ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh.b1 = s ;
  } 
} 
void 
offsave ( void ) 
{
  offsave_regmem 
  halfword p  ;
  if ( curgroup == 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 832 ) ;
    } 
    printcmdchr ( curcmd , curchr ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 1101 ;
    } 
    error () ;
  } 
  else {
      
    backinput () ;
    p = getavail () ;
    mem [memtop - 3 ].hh .v.RH = p ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 666 ) ;
    } 
    switch ( curgroup ) 
    {case 14 : 
      {
	mem [p ].hh .v.LH = 536886427L ;
	printesc ( 552 ) ;
      } 
      break ;
    case 15 : 
      {
	mem [p ].hh .v.LH = 804 ;
	printchar ( 36 ) ;
      } 
      break ;
    case 16 : 
      {
	mem [p ].hh .v.LH = 536886428L ;
	mem [p ].hh .v.RH = getavail () ;
	p = mem [p ].hh .v.RH ;
	mem [p ].hh .v.LH = 3118 ;
	printesc ( 1100 ) ;
      } 
      break ;
      default: 
      {
	mem [p ].hh .v.LH = 637 ;
	printchar ( 125 ) ;
      } 
      break ;
    } 
    print ( 667 ) ;
    begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
    {
      helpptr = 5 ;
      helpline [4 ]= 1095 ;
      helpline [3 ]= 1096 ;
      helpline [2 ]= 1097 ;
      helpline [1 ]= 1098 ;
      helpline [0 ]= 1099 ;
    } 
    error () ;
  } 
} 
void 
extrarightbrace ( void ) 
{
  extrarightbrace_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 1106 ) ;
  } 
  switch ( curgroup ) 
  {case 14 : 
    printesc ( 552 ) ;
    break ;
  case 15 : 
    printchar ( 36 ) ;
    break ;
  case 16 : 
    printesc ( 933 ) ;
    break ;
  } 
  {
    helpptr = 5 ;
    helpline [4 ]= 1107 ;
    helpline [3 ]= 1108 ;
    helpline [2 ]= 1109 ;
    helpline [1 ]= 1110 ;
    helpline [0 ]= 1111 ;
  } 
  error () ;
  incr ( alignstate ) ;
} 
void 
normalparagraph ( void ) 
{
  normalparagraph_regmem 
  if ( eqtb [28481 ].cint != 0 ) 
  eqworddefine ( 28481 , 0 ) ;
  if ( eqtb [29055 ].cint != 0 ) 
  eqworddefine ( 29055 , 0 ) ;
  if ( eqtb [28503 ].cint != 1 ) 
  eqworddefine ( 28503 , 1 ) ;
  if ( eqtb [25060 ].hh .v.RH != -1073741823L ) 
  eqdefine ( 25060 , 133 , -1073741823L ) ;
} 
void 
zboxend ( integer boxcontext ) 
{
  boxend_regmem 
  halfword p  ;
  halfword q  ;
  if ( boxcontext < 1073741824L ) 
  {
    if ( curbox != -1073741823L ) 
    {
      p = mem [curbox ].hh .v.RH ;
      mem [curbox ].hh .v.RH = -1073741823L ;
      while ( p != -1073741823L ) {
	  
	q = p ;
	p = mem [p ].hh .v.RH ;
	if ( ( mem [q ].hh.b1 ) == abs ( curlist .dirfield ) ) 
	{
	  mem [q + 5 ].hh .v.RH = curbox ;
	  curbox = q ;
	  mem [curbox ].hh .v.RH = -1073741823L ;
	} 
	else {
	    
	  deleteglueref ( mem [q + 7 ].hh .v.RH ) ;
	  deleteglueref ( mem [q + 7 ].hh .v.LH ) ;
	  freenode ( q , 10 ) ;
	} 
      } 
      if ( ( mem [curbox ].hh.b1 ) != abs ( curlist .dirfield ) ) 
      curbox = newdirnode ( curbox , abs ( curlist .dirfield ) ) ;
      mem [curbox + 4 ].cint = boxcontext ;
      if ( abs ( curlist .modefield ) == 1 ) 
      {
	appendtovlist ( curbox ) ;
	if ( adjusttail != -1073741823L ) 
	{
	  if ( memtop - 5 != adjusttail ) 
	  {
	    mem [curlist .tailfield ].hh .v.RH = mem [memtop - 5 ].hh 
	    .v.RH ;
	    curlist .tailfield = adjusttail ;
	  } 
	  adjusttail = -1073741823L ;
	} 
	if ( curlist .modefield > 0 ) 
	buildpage () ;
      } 
      else {
	  
	if ( abs ( curlist .modefield ) == 117 ) 
	curlist .auxfield .hh .v.LH = 1000 ;
	else {
	    
	  p = newnoad () ;
	  mem [p + 1 ].hh .v.RH = 3 ;
	  mem [p + 1 ].hh .v.LH = curbox ;
	  curbox = p ;
	} 
	mem [curlist .tailfield ].hh .v.RH = curbox ;
	curlist .tailfield = curbox ;
      } 
    } 
  } 
  else if ( boxcontext < 1073742336L ) {
      
    if ( boxcontext < 1073742080L ) 
    eqdefine ( -1073716498L + boxcontext , 134 , curbox ) ;
    else geqdefine ( -1073716754L + boxcontext , 134 , curbox ) ;
  } 
  else if ( curbox != -1073741823L ) {
      
    if ( boxcontext > 1073742336L ) 
    {
      do {
	  getxtoken () ;
      } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
      if ( ( ( curcmd == 30 ) && ( abs ( curlist .modefield ) != 1 ) ) || ( ( 
      curcmd == 31 ) && ( abs ( curlist .modefield ) == 1 ) ) ) 
      {
	appendglue () ;
	mem [curlist .tailfield ].hh.b1 = boxcontext - ( 1073742237L ) ;
	if ( mem [curbox ].hh.b0 <= 2 ) 
	{
	  p = mem [curbox ].hh .v.RH ;
	  mem [curbox ].hh .v.RH = -1073741823L ;
	  while ( p != -1073741823L ) {
	      
	    q = p ;
	    p = mem [p ].hh .v.RH ;
	    if ( ( mem [q ].hh.b1 ) == abs ( curlist .dirfield ) ) 
	    {
	      mem [q + 5 ].hh .v.RH = curbox ;
	      curbox = q ;
	      mem [curbox ].hh .v.RH = -1073741823L ;
	    } 
	    else {
		
	      deleteglueref ( mem [q + 7 ].hh .v.RH ) ;
	      deleteglueref ( mem [q + 7 ].hh .v.LH ) ;
	      freenode ( q , 10 ) ;
	    } 
	  } 
	  if ( ( mem [curbox ].hh.b1 ) != abs ( curlist .dirfield ) ) 
	  curbox = newdirnode ( curbox , abs ( curlist .dirfield ) ) ;
	} 
	mem [curlist .tailfield + 1 ].hh .v.RH = curbox ;
      } 
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1134 ) ;
	} 
	{
	  helpptr = 3 ;
	  helpline [2 ]= 1135 ;
	  helpline [1 ]= 1136 ;
	  helpline [0 ]= 1137 ;
	} 
	backerror () ;
	flushnodelist ( curbox ) ;
      } 
    } 
    else shipout ( curbox ) ;
  } 
} 
void 
zbeginbox ( integer boxcontext ) 
{
  /* 10 30 */ beginbox_regmem 
  halfword p, q  ;
  halfword r  ;
  boolean fd  ;
  scaled disp, pdisp  ;
  eightbits adir  ;
  halfword tx  ;
  quarterword m  ;
  halfword k  ;
  eightbits n  ;
  switch ( curchr ) 
  {case 0 : 
    {
      scaneightbitint () ;
      curbox = eqtb [25326 + curval ].hh .v.RH ;
      eqtb [25326 + curval ].hh .v.RH = -1073741823L ;
    } 
    break ;
  case 1 : 
    {
      scaneightbitint () ;
      curbox = copynodelist ( eqtb [25326 + curval ].hh .v.RH ) ;
    } 
    break ;
  case 2 : 
    {
      curbox = -1073741823L ;
      if ( abs ( curlist .modefield ) == 233 ) 
      {
	youcant () ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1138 ;
	} 
	error () ;
      } 
      else if ( ( curlist .modefield == 1 ) && ( curlist .headfield == curlist 
      .tailfield ) ) 
      {
	youcant () ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1139 ;
	  helpline [0 ]= 1140 ;
	} 
	error () ;
      } 
      else {
	  
	tx = curlist .tailfield ;
	if ( ! ( tx >= himemmin ) ) {
	    
	  if ( mem [tx ].hh.b0 == 5 ) 
	  {
	    tx = curlist .pnodefield ;
	    if ( ! ( tx >= himemmin ) ) {
		
	      if ( mem [tx ].hh.b0 == 5 ) 
	      goto lab30 ;
	    } 
	  } 
	} 
	if ( ! ( tx >= himemmin ) && ( curlist .headfield != tx ) ) {
	    
	  if ( ( mem [tx ].hh.b0 == 0 ) || ( mem [tx ].hh.b0 == 1 ) || ( 
	  mem [tx ].hh.b0 == 2 ) ) 
	  {
	    q = curlist .headfield ;
	    p = -1073741823L ;
	    disp = 0 ;
	    pdisp = 0 ;
	    do {
		r = p ;
	      p = q ;
	      fd = false ;
	      if ( ! ( q >= himemmin ) ) {
		  
		if ( mem [q ].hh.b0 == 9 ) 
		{
		  {register integer for_end; m = 1 ;for_end = mem [q ]
		  .hh.b1 ; if ( m <= for_end) do 
		    p = mem [p ].hh .v.RH ;
		  while ( m++ < for_end ) ;} 
		  if ( p == tx ) 
		  goto lab30 ;
		} 
		else if ( mem [q ].hh.b0 == 5 ) 
		{
		  pdisp = disp ;
		  disp = mem [q + 1 ].cint ;
		  fd = true ;
		} 
	      } 
	      q = mem [p ].hh .v.RH ;
	    } while ( ! ( q == tx ) ) ;
	    q = mem [tx ].hh .v.RH ;
	    mem [p ].hh .v.RH = q ;
	    mem [tx ].hh .v.RH = -1073741823L ;
	    if ( q == -1073741823L ) 
	    curlist .tailfield = p ;
	    else if ( fd ) 
	    {
	      curlist .pnodefield = r ;
	      curlist .pdispfield = pdisp ;
	      mem [p ].hh .v.RH = -1073741823L ;
	      curlist .tailfield = p ;
	      mem [p + 1 ].cint = mem [q + 1 ].cint ;
	      freenode ( q , 2 ) ;
	    } 
	    else curlist .pnodefield = p ;
	    curbox = tx ;
	    mem [curbox + 4 ].cint = 0 ;
	    if ( mem [curbox ].hh.b0 == 2 ) 
	    {
	      mem [mem [curbox + 5 ].hh .v.RH ].hh .v.RH = curbox ;
	      curbox = mem [curbox + 5 ].hh .v.RH ;
	      mem [mem [curbox ].hh .v.RH + 5 ].hh .v.RH = -1073741823L ;
	    } 
	    else if ( ( mem [curbox ].hh.b1 ) == 0 ) 
	    mem [curbox ].hh.b1 = abs ( curlist .dirfield ) ;
	  } 
	} 
	lab30: ;
      } 
    } 
    break ;
  case 3 : 
    {
      scaneightbitint () ;
      n = curval ;
      if ( ! scankeyword ( 898 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1141 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1142 ;
	  helpline [0 ]= 1143 ;
	} 
	error () ;
      } 
      scandimen ( false , false , false ) ;
      curbox = vsplit ( n , curval ) ;
    } 
    break ;
    default: 
    {
      k = curchr - 4 ;
      savestack [saveptr + 0 ].cint = boxcontext ;
      adir = curlist .adjdirfield ;
      if ( k == 117 ) {
	  
	if ( ( boxcontext < 1073741824L ) && ( abs ( curlist .modefield ) == 1 
	) ) 
	{
	  adir = abs ( curlist .dirfield ) ;
	  scanspec ( 3 , true ) ;
	} 
	else scanspec ( 2 , true ) ;
      } 
      else {
	  
	if ( k == 1 ) 
	scanspec ( 4 , true ) ;
	else {
	    
	  scanspec ( 5 , true ) ;
	  k = 1 ;
	} 
	normalparagraph () ;
      } 
      pushnest () ;
      curlist .modefield = - (integer) k ;
      curlist .adjdirfield = adir ;
      if ( k == 1 ) 
      {
	curlist .auxfield .cint = -65536000L ;
	if ( eqtb [25066 ].hh .v.RH != -1073741823L ) 
	begintokenlist ( eqtb [25066 ].hh .v.RH , 11 ) ;
      } 
      else {
	  
	curlist .auxfield .hh .v.LH = 1000 ;
	if ( eqtb [25065 ].hh .v.RH != -1073741823L ) 
	begintokenlist ( eqtb [25065 ].hh .v.RH , 10 ) ;
      } 
      return ;
    } 
    break ;
  } 
  boxend ( boxcontext ) ;
} 
void 
zscanbox ( integer boxcontext ) 
{
  scanbox_regmem 
  do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  if ( curcmd == 24 ) 
  beginbox ( boxcontext ) ;
  else if ( ( boxcontext >= 1073742337L ) && ( ( curcmd == 40 ) || ( curcmd == 
  39 ) ) ) 
  {
    curbox = scanrulespec () ;
    boxend ( boxcontext ) ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1144 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1145 ;
      helpline [1 ]= 1146 ;
      helpline [0 ]= 1147 ;
    } 
    backerror () ;
  } 
} 
void 
zpackage ( smallnumber c ) 
{
  package_regmem 
  scaled h  ;
  halfword p  ;
  scaled d  ;
  d = eqtb [29045 ].cint ;
  deleteglueref ( curkanjiskip ) ;
  deleteglueref ( curxkanjiskip ) ;
  if ( eqtb [25633 ].hh .v.RH > 0 ) 
  curkanjiskip = eqtb [24542 ].hh .v.RH ;
  else curkanjiskip = membot ;
  if ( eqtb [25634 ].hh .v.RH > 0 ) 
  curxkanjiskip = eqtb [24543 ].hh .v.RH ;
  else curxkanjiskip = membot ;
  incr ( mem [curkanjiskip ].hh .v.RH ) ;
  incr ( mem [curxkanjiskip ].hh .v.RH ) ;
  unsave () ;
  saveptr = saveptr - 3 ;
  if ( curlist .modefield == -117 ) 
  {
    curbox = hpack ( mem [curlist .headfield ].hh .v.RH , savestack [
    saveptr + 2 ].cint , savestack [saveptr + 1 ].cint ) ;
    mem [curbox ].hh.b1 = abs ( curlist .dirfield ) ;
    popnest () ;
  } 
  else {
      
    curbox = vpackage ( mem [curlist .headfield ].hh .v.RH , savestack [
    saveptr + 2 ].cint , savestack [saveptr + 1 ].cint , d ) ;
    mem [curbox ].hh.b1 = abs ( curlist .dirfield ) ;
    popnest () ;
    if ( c == 4 ) 
    {
      h = 0 ;
      p = mem [curbox + 5 ].hh .v.RH ;
      if ( p != -1073741823L ) {
	  
	if ( mem [p ].hh.b0 <= 3 ) 
	h = mem [p + 3 ].cint ;
      } 
      mem [curbox + 2 ].cint = mem [curbox + 2 ].cint - h + mem [curbox + 
      3 ].cint ;
      mem [curbox + 3 ].cint = h ;
    } 
  } 
  boxend ( savestack [saveptr + 0 ].cint ) ;
} 
smallnumber 
znormmin ( integer h ) 
{
  register smallnumber Result; normmin_regmem 
  if ( h <= 0 ) 
  Result = 1 ;
  else if ( h >= 63 ) 
  Result = 63 ;
  else Result = h ;
  return Result ;
} 
void 
znewgraf ( boolean indented ) 
{
  newgraf_regmem 
  curlist .pgfield = 0 ;
  if ( ( curlist .modefield == 1 ) || ( curlist .headfield != curlist 
  .tailfield ) ) 
  {
    mem [curlist .tailfield ].hh .v.RH = newparamglue ( 2 ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  inhibitglueflag = false ;
  pushnest () ;
  curlist .adjdirfield = abs ( curlist .dirfield ) ;
  curlist .modefield = 117 ;
  curlist .auxfield .hh .v.LH = 1000 ;
  if ( eqtb [28513 ].cint <= 0 ) 
  curlang = 0 ;
  else if ( eqtb [28513 ].cint > 255 ) 
  curlang = 0 ;
  else curlang = eqtb [28513 ].cint ;
  curlist .auxfield .hh .v.RH = curlang ;
  curlist .pgfield = ( normmin ( eqtb [28514 ].cint ) * 64 + normmin ( eqtb 
  [28515 ].cint ) ) * 65536L + curlang ;
  if ( indented ) 
  {
    curlist .tailfield = newnullbox () ;
    mem [curlist .headfield ].hh .v.RH = curlist .tailfield ;
    mem [curlist .tailfield + 1 ].cint = eqtb [29038 ].cint ;
    if ( ( insertsrcspecialeverypar ) ) 
    insertsrcspecial () ;
  } 
  if ( eqtb [25062 ].hh .v.RH != -1073741823L ) 
  begintokenlist ( eqtb [25062 ].hh .v.RH , 7 ) ;
  if ( nestptr == 1 ) 
  buildpage () ;
} 
void 
indentinhmode ( void ) 
{
  indentinhmode_regmem 
  halfword p, q  ;
  if ( curchr > 0 ) 
  {
    p = newnullbox () ;
    mem [p + 1 ].cint = eqtb [29038 ].cint ;
    if ( abs ( curlist .modefield ) == 117 ) 
    curlist .auxfield .hh .v.LH = 1000 ;
    else {
	
      q = newnoad () ;
      mem [q + 1 ].hh .v.RH = 2 ;
      mem [q + 1 ].hh .v.LH = p ;
      p = q ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = p ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
  } 
} 
void 
headforvmode ( void ) 
{
  headforvmode_regmem 
  if ( curlist .modefield < 0 ) {
      
    if ( curcmd != 40 ) 
    offsave () ;
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 726 ) ;
      } 
      printesc ( 559 ) ;
      print ( 1150 ) ;
      {
	helpptr = 2 ;
	helpline [1 ]= 1151 ;
	helpline [0 ]= 1152 ;
      } 
      error () ;
    } 
  } 
  else {
      
    backinput () ;
    curtok = partoken ;
    backinput () ;
    curinput .indexfield = 4 ;
  } 
} 
void 
endgraf ( void ) 
{
  endgraf_regmem 
  if ( curlist .modefield == 117 ) 
  {
    if ( curlist .headfield == curlist .tailfield ) 
    popnest () ;
    else {
	
      adjusthlist ( curlist .headfield , true ) ;
      linebreak ( eqtb [28468 ].cint ) ;
    } 
    normalparagraph () ;
    errorcount = 0 ;
  } 
} 
void 
begininsertoradjust ( void ) 
{
  begininsertoradjust_regmem 
  if ( curcmd == 42 ) 
  curval = 255 ;
  else {
      
    scaneightbitint () ;
    if ( curval == 255 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1153 ) ;
      } 
      printesc ( 336 ) ;
      printint ( 255 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 1154 ;
      } 
      error () ;
      curval = 0 ;
    } 
  } 
  savestack [saveptr + 0 ].cint = curval ;
  incr ( saveptr ) ;
  newsavelevel ( 11 ) ;
  scanleftbrace () ;
  normalparagraph () ;
  pushnest () ;
  curlist .modefield = -1 ;
  curlist .dirfield = curlist .adjdirfield ;
  curlist .auxfield .cint = -65536000L ;
} 
void 
makemark ( void ) 
{
  makemark_regmem 
  halfword p  ;
  p = scantoks ( false , true ) ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 6 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = defref ;
  if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield ]
  .hh.b0 == 5 ) ) 
  {
    mem [curlist .pnodefield ].hh .v.RH = p ;
    mem [mem [curlist .pnodefield ].hh .v.RH ].hh .v.RH = curlist 
    .tailfield ;
    curlist .pnodefield = mem [curlist .pnodefield ].hh .v.RH ;
  } 
  else {
      
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
} 
void 
appendpenalty ( void ) 
{
  appendpenalty_regmem 
  scanint () ;
  if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield ]
  .hh.b0 == 5 ) ) 
  {
    mem [curlist .pnodefield ].hh .v.RH = newpenalty ( curval ) ;
    mem [mem [curlist .pnodefield ].hh .v.RH ].hh .v.RH = curlist 
    .tailfield ;
    curlist .pnodefield = mem [curlist .pnodefield ].hh .v.RH ;
  } 
  else {
      
    mem [curlist .tailfield ].hh .v.RH = newpenalty ( curval ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  if ( curlist .modefield == 1 ) 
  buildpage () ;
} 
void 
deletelast ( void ) 
{
  /* 10 */ deletelast_regmem 
  halfword p, q  ;
  halfword r  ;
  boolean fd  ;
  scaled disp, pdisp  ;
  halfword tx  ;
  quarterword m  ;
  if ( ( curlist .modefield == 1 ) && ( curlist .tailfield == curlist 
  .headfield ) ) 
  {
    if ( ( curchr != 12 ) || ( lastglue != 1073741823L ) ) 
    {
      youcant () ;
      {
	helpptr = 2 ;
	helpline [1 ]= 1139 ;
	helpline [0 ]= 1157 ;
      } 
      if ( curchr == 13 ) 
      helpline [0 ]= ( 1158 ) ;
      else if ( curchr != 12 ) 
      helpline [0 ]= ( 1159 ) ;
      error () ;
    } 
  } 
  else {
      
    tx = curlist .tailfield ;
    if ( ! ( tx >= himemmin ) ) {
	
      if ( mem [tx ].hh.b0 == 5 ) 
      {
	tx = curlist .pnodefield ;
	if ( ! ( tx >= himemmin ) ) {
	    
	  if ( mem [tx ].hh.b0 == 5 ) 
	  return ;
	} 
      } 
    } 
    if ( ! ( tx >= himemmin ) ) {
	
      if ( mem [tx ].hh.b0 == curchr ) 
      {
	q = curlist .headfield ;
	p = -1073741823L ;
	disp = 0 ;
	pdisp = 0 ;
	do {
	    r = p ;
	  p = q ;
	  fd = false ;
	  if ( ! ( q >= himemmin ) ) {
	      
	    if ( mem [q ].hh.b0 == 9 ) 
	    {
	      {register integer for_end; m = 1 ;for_end = mem [q ].hh.b1 
	      ; if ( m <= for_end) do 
		p = mem [p ].hh .v.RH ;
	      while ( m++ < for_end ) ;} 
	      if ( p == tx ) 
	      return ;
	    } 
	    else if ( mem [q ].hh.b0 == 5 ) 
	    {
	      pdisp = disp ;
	      disp = mem [q + 1 ].cint ;
	      fd = true ;
	    } 
	  } 
	  q = mem [p ].hh .v.RH ;
	} while ( ! ( q == tx ) ) ;
	q = mem [tx ].hh .v.RH ;
	mem [p ].hh .v.RH = q ;
	mem [tx ].hh .v.RH = -1073741823L ;
	if ( q == -1073741823L ) 
	curlist .tailfield = p ;
	else if ( fd ) 
	{
	  curlist .pnodefield = r ;
	  curlist .pdispfield = pdisp ;
	  mem [p ].hh .v.RH = -1073741823L ;
	  curlist .tailfield = p ;
	  mem [p + 1 ].cint = mem [q + 1 ].cint ;
	  freenode ( q , 2 ) ;
	} 
	else curlist .pnodefield = p ;
	flushnodelist ( tx ) ;
      } 
    } 
  } 
} 
void 
unpackage ( void ) 
{
  /* 10 */ unpackage_regmem 
  halfword p  ;
  unsigned char c  ;
  scaled disp  ;
  c = curchr ;
  scaneightbitint () ;
  p = eqtb [25326 + curval ].hh .v.RH ;
  if ( p == -1073741823L ) 
  return ;
  if ( mem [p ].hh.b0 == 2 ) 
  p = mem [p + 5 ].hh .v.RH ;
  if ( ( abs ( curlist .modefield ) == 233 ) || ( ( abs ( curlist .modefield ) 
  == 1 ) && ( mem [p ].hh.b0 != 1 ) ) || ( ( abs ( curlist .modefield ) == 
  117 ) && ( mem [p ].hh.b0 != 0 ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1167 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1168 ;
      helpline [1 ]= 1169 ;
      helpline [0 ]= 1170 ;
    } 
    error () ;
    return ;
  } 
  switch ( ( mem [p ].hh.b1 ) ) 
  {case 4 : 
  case 3 : 
  case 1 : 
    if ( abs ( curlist .dirfield ) != ( mem [p ].hh.b1 ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1171 ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 1168 ;
	helpline [0 ]= 1172 ;
      } 
      error () ;
      return ;
    } 
    break ;
  } 
  disp = 0 ;
  if ( c == 1 ) 
  mem [curlist .tailfield ].hh .v.RH = copynodelist ( mem [p + 5 ].hh 
  .v.RH ) ;
  else {
      
    if ( mem [eqtb [25326 + curval ].hh .v.RH ].hh.b0 == 2 ) 
    {
      deleteglueref ( mem [eqtb [25326 + curval ].hh .v.RH + 7 ].hh .v.RH 
      ) ;
      deleteglueref ( mem [eqtb [25326 + curval ].hh .v.RH + 7 ].hh .v.LH 
      ) ;
      freenode ( eqtb [25326 + curval ].hh .v.RH , 10 ) ;
    } 
    flushnodelist ( mem [p ].hh .v.RH ) ;
    mem [curlist .tailfield ].hh .v.RH = mem [p + 5 ].hh .v.RH ;
    eqtb [25326 + curval ].hh .v.RH = -1073741823L ;
    deleteglueref ( mem [p + 7 ].hh .v.RH ) ;
    deleteglueref ( mem [p + 7 ].hh .v.LH ) ;
    freenode ( p , 10 ) ;
  } 
  while ( mem [curlist .tailfield ].hh .v.RH != -1073741823L ) {
      
    p = curlist .tailfield ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    if ( ! ( curlist .tailfield >= himemmin ) ) 
    switch ( mem [curlist .tailfield ].hh.b0 ) 
    {case 12 : 
      if ( ( mem [curlist .tailfield ].hh.b1 == 16 ) || ( mem [curlist 
      .tailfield ].hh.b1 == 17 ) ) 
      {
	mem [p ].hh .v.RH = mem [curlist .tailfield ].hh .v.RH ;
	deleteglueref ( mem [curlist .tailfield + 1 ].hh .v.LH ) ;
	freenode ( curlist .tailfield , 2 ) ;
	curlist .tailfield = p ;
      } 
      break ;
    case 14 : 
      if ( mem [curlist .tailfield ].hh.b1 == 1 ) 
      {
	mem [p ].hh .v.RH = mem [curlist .tailfield ].hh .v.RH ;
	freenode ( curlist .tailfield , 2 ) ;
	curlist .tailfield = p ;
      } 
      break ;
    case 5 : 
      {
	curlist .pdispfield = disp ;
	disp = mem [curlist .tailfield + 1 ].cint ;
	curlist .pnodefield = p ;
      } 
      break ;
    } 
  } 
} 
void 
appenditaliccorrection ( void ) 
{
  /* 10 */ appenditaliccorrection_regmem 
  halfword p  ;
  internalfontnumber f  ;
  halfword d  ;
  if ( curlist .tailfield != curlist .headfield ) 
  {
    if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield ]
    .hh.b0 == 5 ) ) 
    {
      d = curlist .tailfield ;
      curlist .tailfield = curlist .pnodefield ;
    } 
    else d = -1073741823L ;
    if ( ( curlist .lastjchrfield != -1073741823L ) && ( mem [curlist 
    .lastjchrfield ].hh .v.RH == curlist .tailfield ) && ( ( curlist 
    .tailfield >= himemmin ) ) ) 
    p = curlist .lastjchrfield ;
    else if ( ( curlist .tailfield >= himemmin ) ) 
    p = curlist .tailfield ;
    else if ( mem [curlist .tailfield ].hh.b0 == 8 ) 
    p = curlist .tailfield + 1 ;
    else return ;
    f = mem [p ].hh.b0 ;
    {
      mem [curlist .tailfield ].hh .v.RH = newkern ( fontinfo [italicbase [
      f ]+ ( fontinfo [charbase [f ]+ effectivechar ( true , f , mem [p ]
      .hh.b1 ) ].qqqq .b2 ) / 4 ].cint ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh.b1 = 3 ;
    if ( d != -1073741823L ) 
    {
      curlist .pnodefield = curlist .tailfield ;
      {
	mem [curlist .tailfield ].hh .v.RH = d ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
    } 
  } 
} 
void 
appenddiscretionary ( void ) 
{
  appenddiscretionary_regmem 
  integer c  ;
  {
    mem [curlist .tailfield ].hh .v.RH = newdisc () ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  if ( curchr == 1 ) 
  {
    c = hyphenchar [eqtb [25582 ].hh .v.RH ];
    if ( c >= 0 ) {
	
      if ( c < 256 ) 
      mem [curlist .tailfield + 1 ].hh .v.LH = newcharacter ( eqtb [25582 ]
      .hh .v.RH , c ) ;
    } 
  } 
  else {
      
    incr ( saveptr ) ;
    savestack [saveptr - 1 ].cint = 0 ;
    newsavelevel ( 10 ) ;
    scanleftbrace () ;
    pushnest () ;
    curlist .modefield = -117 ;
    curlist .auxfield .hh .v.LH = 1000 ;
  } 
} 
void 
builddiscretionary ( void ) 
{
  /* 30 10 */ builddiscretionary_regmem 
  halfword p, q  ;
  integer n  ;
  unsave () ;
  q = curlist .headfield ;
  p = mem [q ].hh .v.RH ;
  n = 0 ;
  while ( p != -1073741823L ) {
      
    if ( ! ( p >= himemmin ) ) {
	
      if ( ( mem [p ].hh.b0 > 3 ) && ( mem [p ].hh.b0 != 13 ) && ( mem [p 
      ].hh.b0 != 8 ) && ( mem [p ].hh.b0 != 5 ) ) {
	  
	if ( ( mem [p ].hh.b0 == 14 ) && ( mem [p ].hh.b1 != 0 ) ) 
	{
	  mem [q ].hh .v.RH = mem [p ].hh .v.RH ;
	  freenode ( p , 2 ) ;
	  p = q ;
	} 
	else {
	    
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 1179 ) ;
	  } 
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 1180 ;
	  } 
	  error () ;
	  begindiagnostic () ;
	  printnl ( 1181 ) ;
	  showbox ( p ) ;
	  enddiagnostic ( true ) ;
	  flushnodelist ( p ) ;
	  mem [q ].hh .v.RH = -1073741823L ;
	  goto lab30 ;
	} 
      } 
    } 
    q = p ;
    p = mem [q ].hh .v.RH ;
    incr ( n ) ;
  } 
  lab30: ;
  p = mem [curlist .headfield ].hh .v.RH ;
  popnest () ;
  switch ( savestack [saveptr - 1 ].cint ) 
  {case 0 : 
    mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    break ;
  case 1 : 
    mem [curlist .tailfield + 1 ].hh .v.RH = p ;
    break ;
  case 2 : 
    {
      if ( ( n > 0 ) && ( abs ( curlist .modefield ) == 233 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1173 ) ;
	} 
	printesc ( 357 ) ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1174 ;
	  helpline [0 ]= 1175 ;
	} 
	flushnodelist ( p ) ;
	n = 0 ;
	error () ;
      } 
      else mem [curlist .tailfield ].hh .v.RH = p ;
      if ( n <= 65535L ) 
      mem [curlist .tailfield ].hh.b1 = n ;
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1176 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1177 ;
	  helpline [0 ]= 1178 ;
	} 
	error () ;
      } 
      if ( n > 0 ) 
      curlist .tailfield = q ;
      decr ( saveptr ) ;
      curlist .pnodefield = curlist .tailfield ;
      {
	mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = 5 ;
      mem [curlist .tailfield + 1 ].cint = 0 ;
      curlist .pdispfield = 0 ;
      return ;
    } 
    break ;
  } 
  incr ( savestack [saveptr - 1 ].cint ) ;
  newsavelevel ( 10 ) ;
  scanleftbrace () ;
  pushnest () ;
  curlist .modefield = -117 ;
  curlist .auxfield .hh .v.LH = 1000 ;
} 
void 
makeaccent ( void ) 
{
  makeaccent_regmem 
  real s, t  ;
  scaled disp  ;
  KANJIcode cx  ;
  halfword p, q, r  ;
  internalfontnumber f  ;
  scaled a, h, x, w, delta  ;
  fourquarters i  ;
  scancharnum () ;
  if ( checkecharrange ( curval ) == 0 ) 
  {
    cx = curval ;
    if ( curlist .dirfield == 3 ) 
    f = eqtb [25632 ].hh .v.RH ;
    else f = eqtb [25631 ].hh .v.RH ;
    p = newcharacter ( f , getjfmpos ( cx , f ) ) ;
    if ( p != -1073741823L ) 
    {
      mem [p ].hh .v.RH = getavail () ;
      mem [mem [p ].hh .v.RH ].hh .v.LH = cx + eqtb [25892 + kcatcodekey 
      ( cx ) ].hh .v.RH * 16777216L ;
    } 
  } 
  else {
      
    f = eqtb [25582 ].hh .v.RH ;
    p = newcharacter ( f , curval ) ;
  } 
  if ( p != -1073741823L ) 
  {
    x = fontinfo [5 + parambase [f ]].cint ;
    s = fontinfo [1 + parambase [f ]].cint / ((double) 65536.0 ) ;
    a = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ effectivechar 
    ( true , f , mem [p ].hh.b1 ) ].qqqq .b0 ].cint ;
    doassignments () ;
    q = -1073741823L ;
    f = eqtb [25582 ].hh .v.RH ;
    cx = 0 ;
    if ( ( curcmd == 11 ) || ( curcmd == 12 ) ) 
    q = newcharacter ( f , curchr ) ;
    else if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
    {
      if ( curlist .dirfield == 3 ) 
      f = eqtb [25632 ].hh .v.RH ;
      else f = eqtb [25631 ].hh .v.RH ;
      cx = curchr ;
    } 
    else if ( curcmd == 73 ) {
	
      if ( checkecharrange ( curchr ) ) 
      q = newcharacter ( f , curchr ) ;
      else {
	  
	if ( curlist .dirfield == 3 ) 
	f = eqtb [25632 ].hh .v.RH ;
	else f = eqtb [25631 ].hh .v.RH ;
	cx = curchr ;
      } 
    } 
    else if ( curcmd == 20 ) 
    {
      scancharnum () ;
      if ( checkecharrange ( curval ) ) 
      q = newcharacter ( f , curval ) ;
      else {
	  
	if ( curlist .dirfield == 3 ) 
	f = eqtb [25632 ].hh .v.RH ;
	else f = eqtb [25631 ].hh .v.RH ;
	cx = curval ;
      } 
    } 
    else if ( curcmd == 74 ) 
    {
      if ( curlist .dirfield == 3 ) 
      f = eqtb [25632 ].hh .v.RH ;
      else f = eqtb [25631 ].hh .v.RH ;
      cx = curchr ;
    } 
    else if ( curcmd == 54 ) 
    {
      scancharnum () ;
      if ( curlist .dirfield == 3 ) 
      f = eqtb [25632 ].hh .v.RH ;
      else f = eqtb [25631 ].hh .v.RH ;
      cx = curval ;
    } 
    else backinput () ;
    if ( curlist .dirfield == 3 ) 
    {
      if ( fontdir [f ]== 3 ) 
      disp = 0 ;
      else if ( fontdir [f ]== 4 ) 
      disp = eqtb [29059 ].cint - eqtb [29060 ].cint ;
      else disp = eqtb [29059 ].cint ;
    } 
    else {
	
      if ( fontdir [f ]== 4 ) 
      disp = 0 ;
      else if ( fontdir [f ]== 3 ) 
      disp = eqtb [29060 ].cint - eqtb [29059 ].cint ;
      else disp = eqtb [29060 ].cint ;
    } 
    {
      if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield 
      ].hh.b0 == 5 ) ) 
      {
	if ( curlist .pdispfield == disp ) 
	{
	  freenode ( curlist .tailfield , 2 ) ;
	  curlist .tailfield = curlist .pnodefield ;
	  mem [curlist .tailfield ].hh .v.RH = -1073741823L ;
	} 
	else mem [curlist .tailfield + 1 ].cint = disp ;
      } 
      else if ( disp != 0 ) 
      {
	curlist .pnodefield = curlist .tailfield ;
	{
	  mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b0 = 5 ;
	mem [curlist .tailfield + 1 ].cint = disp ;
	curlist .pdispfield = disp ;
      } 
    } 
    if ( cx != 0 ) 
    {
      q = newcharacter ( f , getjfmpos ( cx , f ) ) ;
      mem [q ].hh .v.RH = getavail () ;
      mem [mem [q ].hh .v.RH ].hh .v.LH = cx + eqtb [25892 + kcatcodekey 
      ( cx ) ].hh .v.RH * 16777216L ;
      curlist .lastjchrfield = q ;
    } 
    if ( q != -1073741823L ) 
    {
      t = fontinfo [1 + parambase [f ]].cint / ((double) 65536.0 ) ;
      i = fontinfo [charbase [f ]+ effectivechar ( true , f , mem [q ]
      .hh.b1 ) ].qqqq ;
      w = fontinfo [widthbase [f ]+ i .b0 ].cint ;
      h = fontinfo [heightbase [f ]+ ( i .b1 ) / 16 ].cint ;
      if ( h != x ) 
      {
	deleteglueref ( curkanjiskip ) ;
	deleteglueref ( curxkanjiskip ) ;
	curkanjiskip = membot ;
	curxkanjiskip = membot ;
	incr ( mem [curkanjiskip ].hh .v.RH ) ;
	incr ( mem [curxkanjiskip ].hh .v.RH ) ;
	p = hpack ( p , 0 , 1 ) ;
	mem [p + 4 ].cint = x - h ;
      } 
      delta = round ( ( w - a ) / ((double) 2.0 ) + h * t - x * s ) ;
      r = newkern ( delta ) ;
      mem [r ].hh.b1 = 2 ;
      mem [curlist .tailfield ].hh .v.RH = r ;
      mem [r ].hh .v.RH = p ;
      curlist .tailfield = newkern ( - (integer) a - delta ) ;
      mem [curlist .tailfield ].hh.b1 = 2 ;
      if ( h == x ) 
      {
	if ( fontdir [mem [p ].hh.b0 ]!= 0 ) 
	mem [mem [p ].hh .v.RH ].hh .v.RH = curlist .tailfield ;
	else mem [p ].hh .v.RH = curlist .tailfield ;
      } 
      else mem [p ].hh .v.RH = curlist .tailfield ;
      p = q ;
    } 
    mem [curlist .tailfield ].hh .v.RH = p ;
    if ( mem [p ].hh .v.RH != -1073741823L ) 
    curlist .tailfield = mem [p ].hh .v.RH ;
    else curlist .tailfield = p ;
    if ( disp != 0 ) 
    {
      if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield 
      ].hh.b0 == 5 ) ) 
      {
	mem [curlist .tailfield + 1 ].cint = 0 ;
      } 
      else {
	  
	curlist .pnodefield = curlist .tailfield ;
	{
	  mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b0 = 5 ;
	mem [curlist .tailfield + 1 ].cint = 0 ;
	curlist .pdispfield = disp ;
      } 
    } 
    curlist .auxfield .hh .v.LH = 1000 ;
  } 
} 
void 
alignerror ( void ) 
{
  alignerror_regmem 
  if ( abs ( alignstate ) > 2 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1186 ) ;
    } 
    printcmdchr ( curcmd , curchr ) ;
    if ( curtok == 1062 ) 
    {
      {
	helpptr = 6 ;
	helpline [5 ]= 1187 ;
	helpline [4 ]= 1188 ;
	helpline [3 ]= 1189 ;
	helpline [2 ]= 1190 ;
	helpline [1 ]= 1191 ;
	helpline [0 ]= 1192 ;
      } 
    } 
    else {
	
      {
	helpptr = 5 ;
	helpline [4 ]= 1187 ;
	helpline [3 ]= 1193 ;
	helpline [2 ]= 1190 ;
	helpline [1 ]= 1191 ;
	helpline [0 ]= 1192 ;
      } 
    } 
    error () ;
  } 
  else {
      
    backinput () ;
    if ( alignstate < 0 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 698 ) ;
      } 
      incr ( alignstate ) ;
      curtok = 379 ;
    } 
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1182 ) ;
      } 
      decr ( alignstate ) ;
      curtok = 637 ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1183 ;
      helpline [1 ]= 1184 ;
      helpline [0 ]= 1185 ;
    } 
    inserror () ;
  } 
} 
void 
noalignerror ( void ) 
{
  noalignerror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 1186 ) ;
  } 
  printesc ( 565 ) ;
  {
    helpptr = 2 ;
    helpline [1 ]= 1194 ;
    helpline [0 ]= 1195 ;
  } 
  error () ;
} 
void 
omiterror ( void ) 
{
  omiterror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 1186 ) ;
  } 
  printesc ( 568 ) ;
  {
    helpptr = 2 ;
    helpline [1 ]= 1196 ;
    helpline [0 ]= 1195 ;
  } 
  error () ;
} 
void 
doendv ( void ) 
{
  doendv_regmem 
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  while ( ( inputstack [baseptr ].indexfield != 2 ) && ( inputstack [
  baseptr ].locfield == -1073741823L ) && ( inputstack [baseptr ]
  .statefield == 0 ) ) decr ( baseptr ) ;
  if ( ( inputstack [baseptr ].indexfield != 2 ) || ( inputstack [baseptr ]
  .locfield != -1073741823L ) || ( inputstack [baseptr ].statefield != 0 ) ) 
  fatalerror ( 633 ) ;
  if ( curgroup == 6 ) 
  {
    endgraf () ;
    if ( fincol () ) 
    finrow () ;
  } 
  else offsave () ;
} 
void 
cserror ( void ) 
{
  cserror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 832 ) ;
  } 
  printesc ( 540 ) ;
  {
    helpptr = 1 ;
    helpline [0 ]= 1198 ;
  } 
  error () ;
} 
void 
zpushmath ( groupcode c ) 
{
  pushmath_regmem 
  pushnest () ;
  curlist .modefield = -233 ;
  curlist .auxfield .cint = -1073741823L ;
  newsavelevel ( c ) ;
} 
void 
initmath ( void ) 
{
  /* 21 40 45 30 */ initmath_regmem 
  scaled w  ;
  scaled l  ;
  scaled s  ;
  halfword p  ;
  halfword q  ;
  internalfontnumber f  ;
  integer n  ;
  scaled v  ;
  scaled d  ;
  gettoken () ;
  if ( ( curcmd == 3 ) && ( curlist .modefield > 0 ) ) 
  {
    if ( curlist .headfield == curlist .tailfield ) 
    {
      popnest () ;
      w = -1073741823L ;
    } 
    else {
	
      adjusthlist ( curlist .headfield , true ) ;
      linebreak ( eqtb [28469 ].cint ) ;
      v = mem [justbox + 4 ].cint + 2 * fontinfo [6 + parambase [eqtb [
      25582 ].hh .v.RH ]].cint ;
      w = -1073741823L ;
      p = mem [justbox + 5 ].hh .v.RH ;
      while ( p != -1073741823L ) {
	  
	lab21: if ( ( p >= himemmin ) ) 
	{
	  f = mem [p ].hh.b0 ;
	  d = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ mem [p 
	  ].hh.b1 ].qqqq .b0 ].cint ;
	  if ( fontdir [f ]!= 0 ) 
	  p = mem [p ].hh .v.RH ;
	  goto lab40 ;
	} 
	switch ( mem [p ].hh.b0 ) 
	{case 0 : 
	case 1 : 
	case 2 : 
	case 3 : 
	  {
	    d = mem [p + 1 ].cint ;
	    goto lab40 ;
	  } 
	  break ;
	case 8 : 
	  {
	    mem [memtop - 12 ]= mem [p + 1 ];
	    mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	    p = memtop - 12 ;
	    goto lab21 ;
	  } 
	  break ;
	case 13 : 
	case 11 : 
	  d = mem [p + 1 ].cint ;
	  break ;
	case 12 : 
	  {
	    q = mem [p + 1 ].hh .v.LH ;
	    d = mem [q + 1 ].cint ;
	    if ( mem [justbox + 5 ].hh.b0 == 1 ) 
	    {
	      if ( ( mem [justbox + 5 ].hh.b1 == mem [q ].hh.b0 ) && ( mem 
	      [q + 2 ].cint != 0 ) ) 
	      v = 1073741823L ;
	    } 
	    else if ( mem [justbox + 5 ].hh.b0 == 2 ) 
	    {
	      if ( ( mem [justbox + 5 ].hh.b1 == mem [q ].hh.b1 ) && ( mem 
	      [q + 3 ].cint != 0 ) ) 
	      v = 1073741823L ;
	    } 
	    if ( mem [p ].hh.b1 >= 100 ) 
	    goto lab40 ;
	  } 
	  break ;
	case 10 : 
	  d = 0 ;
	  break ;
	  default: 
	  d = 0 ;
	  break ;
	} 
	if ( v < 1073741823L ) 
	v = v + d ;
	goto lab45 ;
	lab40: if ( v < 1073741823L ) 
	{
	  v = v + d ;
	  w = v ;
	} 
	else {
	    
	  w = 1073741823L ;
	  goto lab30 ;
	} 
	lab45: p = mem [p ].hh .v.RH ;
      } 
      lab30: ;
    } 
    if ( eqtb [25060 ].hh .v.RH == -1073741823L ) {
	
      if ( ( eqtb [29055 ].cint != 0 ) && ( ( ( eqtb [28503 ].cint >= 0 ) 
      && ( curlist .pgfield + 2 > eqtb [28503 ].cint ) ) || ( curlist 
      .pgfield + 1 < - (integer) eqtb [28503 ].cint ) ) ) 
      {
	l = eqtb [29041 ].cint - abs ( eqtb [29055 ].cint ) ;
	if ( eqtb [29055 ].cint > 0 ) 
	s = eqtb [29055 ].cint ;
	else s = 0 ;
      } 
      else {
	  
	l = eqtb [29041 ].cint ;
	s = 0 ;
      } 
    } 
    else {
	
      n = mem [eqtb [25060 ].hh .v.RH ].hh .v.LH ;
      if ( curlist .pgfield + 2 >= n ) 
      p = eqtb [25060 ].hh .v.RH + 2 * n ;
      else p = eqtb [25060 ].hh .v.RH + 2 * ( curlist .pgfield + 2 ) ;
      s = mem [p - 1 ].cint ;
      l = mem [p ].cint ;
    } 
    pushmath ( 15 ) ;
    curlist .modefield = 233 ;
    eqworddefine ( 28506 , -1 ) ;
    eqworddefine ( 29051 , w ) ;
    eqworddefine ( 29052 , l ) ;
    eqworddefine ( 29053 , s ) ;
    if ( eqtb [25064 ].hh .v.RH != -1073741823L ) 
    begintokenlist ( eqtb [25064 ].hh .v.RH , 9 ) ;
    if ( nestptr == 1 ) 
    buildpage () ;
  } 
  else {
      
    backinput () ;
    {
      pushmath ( 15 ) ;
      eqworddefine ( 28506 , -1 ) ;
      if ( ( insertsrcspecialeverymath ) ) 
      insertsrcspecial () ;
      if ( eqtb [25063 ].hh .v.RH != -1073741823L ) 
      begintokenlist ( eqtb [25063 ].hh .v.RH , 8 ) ;
    } 
  } 
  curlist .dirfield = - (integer) abs ( curlist .dirfield ) ;
} 
void 
starteqno ( void ) 
{
  starteqno_regmem 
  savestack [saveptr + 0 ].cint = curchr ;
  incr ( saveptr ) ;
  {
    pushmath ( 15 ) ;
    eqworddefine ( 28506 , -1 ) ;
    if ( ( insertsrcspecialeverymath ) ) 
    insertsrcspecial () ;
    if ( eqtb [25063 ].hh .v.RH != -1073741823L ) 
    begintokenlist ( eqtb [25063 ].hh .v.RH , 8 ) ;
  } 
} 
void 
zscanmath ( halfword p , halfword q ) 
{
  /* 20 21 10 */ scanmath_regmem 
  integer c  ;
  KANJIcode cx  ;
  cx = 0 ;
  lab20: do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  lab21: switch ( curcmd ) 
  {case 11 : 
  case 12 : 
  case 73 : 
    if ( ( curchr >= 0 ) && ( curchr <= 256 ) ) 
    {
      c = eqtb [27950 + curchr ].hh .v.RH ;
      if ( c == 32768L ) 
      {
	{
	  curcs = curchr + 1 ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  xtoken () ;
	  backinput () ;
	} 
	goto lab20 ;
      } 
    } 
    else cx = curchr ;
    break ;
  case 74 : 
    cx = curchr ;
    break ;
  case 16 : 
  case 17 : 
  case 18 : 
  case 19 : 
    cx = curchr ;
    break ;
  case 20 : 
    {
      scancharnum () ;
      curchr = curval ;
      curcmd = 73 ;
      goto lab21 ;
    } 
    break ;
  case 21 : 
    {
      scanfifteenbitint () ;
      c = curval ;
    } 
    break ;
  case 75 : 
    c = curchr ;
    break ;
  case 15 : 
    {
      scantwentysevenbitint () ;
      c = curval / 4096 ;
    } 
    break ;
    default: 
    {
      backinput () ;
      scanleftbrace () ;
      savestack [saveptr + 0 ].cint = p ;
      incr ( saveptr ) ;
      pushmath ( 9 ) ;
      return ;
    } 
    break ;
  } 
  if ( cx == 0 ) 
  {
    mem [p ].hh .v.RH = 1 ;
    mem [p ].hh.b1 = c % 256 ;
    if ( ( c >= 28672 ) && ( ( ( eqtb [28506 ].cint >= 0 ) && ( eqtb [28506 
    ].cint < 16 ) ) ) ) 
    mem [p ].hh.b0 = eqtb [28506 ].cint ;
    else mem [p ].hh.b0 = ( c / 256 ) % 16 ;
    if ( fontdir [eqtb [25583 + mem [p ].hh.b0 + cursize ].hh .v.RH ]!= 
    0 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1201 ) ;
      } 
      {
	helpptr = 1 ;
	helpline [0 ]= 1202 ;
      } 
      error () ;
    } 
  } 
  else {
      
    if ( q == -1073741823L ) 
    {
      mem [p ].hh .v.RH = 4 ;
      mem [p ].hh .v.LH = newnoad () ;
      p = mem [p ].hh .v.LH + 1 ;
      q = p + 3 ;
    } 
    mem [p ].hh .v.RH = 6 ;
    mem [p ].hh.b0 = eqtb [28507 ].cint ;
    mem [p ].hh.b1 = 0 ;
    mem [p + 3 ].hh .v.LH = cx + eqtb [25892 + kcatcodekey ( cx ) ].hh 
    .v.RH * 16777216L ;
    if ( fontdir [eqtb [25583 + mem [p ].hh.b0 + cursize ].hh .v.RH ]== 
    0 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1203 ) ;
      } 
      {
	helpptr = 1 ;
	helpline [0 ]= 1202 ;
      } 
      error () ;
    } 
  } 
} 
void 
zsetmathchar ( integer c ) 
{
  setmathchar_regmem 
  halfword p  ;
  if ( c >= 32768L ) 
  {
    curcs = curchr + 1 ;
    curcmd = eqtb [curcs ].hh.b0 ;
    curchr = eqtb [curcs ].hh .v.RH ;
    xtoken () ;
    backinput () ;
  } 
  else {
      
    p = newnoad () ;
    mem [p + 1 ].hh .v.RH = 1 ;
    mem [p + 1 ].hh.b1 = c % 256 ;
    mem [p + 1 ].hh.b0 = ( c / 256 ) % 16 ;
    if ( c >= 28672 ) 
    {
      if ( ( ( eqtb [28506 ].cint >= 0 ) && ( eqtb [28506 ].cint < 16 ) ) 
      ) 
      mem [p + 1 ].hh.b0 = eqtb [28506 ].cint ;
      mem [p ].hh.b0 = 18 ;
    } 
    else mem [p ].hh.b0 = 18 + ( c / 4096 ) ;
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
    if ( fontdir [eqtb [25583 + mem [p + 1 ].hh.b0 + cursize ].hh .v.RH ]
    != 0 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1201 ) ;
      } 
      {
	helpptr = 1 ;
	helpline [0 ]= 1202 ;
      } 
      error () ;
    } 
    inhibitglueflag = false ;
  } 
} 
void 
mathlimitswitch ( void ) 
{
  /* 10 */ mathlimitswitch_regmem 
  if ( curlist .headfield != curlist .tailfield ) {
      
    if ( mem [curlist .tailfield ].hh.b0 == 19 ) 
    {
      mem [curlist .tailfield ].hh.b1 = curchr ;
      return ;
    } 
  } 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 1205 ) ;
  } 
  {
    helpptr = 1 ;
    helpline [0 ]= 1206 ;
  } 
  error () ;
} 
void 
zscandelimiter ( halfword p , boolean r ) 
{
  scandelimiter_regmem 
  if ( r ) 
  scantwentysevenbitint () ;
  else {
      
    do {
	getxtoken () ;
    } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
    switch ( curcmd ) 
    {case 11 : 
    case 12 : 
      curval = eqtb [28782 + curchr ].cint ;
      break ;
    case 15 : 
      scantwentysevenbitint () ;
      break ;
      default: 
      curval = -1 ;
      break ;
    } 
  } 
  if ( curval < 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1207 ) ;
    } 
    {
      helpptr = 6 ;
      helpline [5 ]= 1208 ;
      helpline [4 ]= 1209 ;
      helpline [3 ]= 1210 ;
      helpline [2 ]= 1211 ;
      helpline [1 ]= 1212 ;
      helpline [0 ]= 1213 ;
    } 
    backerror () ;
    curval = 0 ;
  } 
  mem [p ].qqqq .b0 = ( curval / 1048576L ) % 16 ;
  mem [p ].qqqq .b1 = ( curval / 4096 ) % 256 ;
  mem [p ].qqqq .b2 = ( curval / 256 ) % 16 ;
  mem [p ].qqqq .b3 = curval % 256 ;
} 
void 
mathradical ( void ) 
{
  mathradical_regmem 
  {
    mem [curlist .tailfield ].hh .v.RH = getnode ( 6 ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b0 = 26 ;
  mem [curlist .tailfield ].hh.b1 = 0 ;
  mem [curlist .tailfield + 1 ].hh = emptyfield ;
  mem [curlist .tailfield + 3 ].hh = emptyfield ;
  mem [curlist .tailfield + 2 ].hh = emptyfield ;
  scandelimiter ( curlist .tailfield + 5 , true ) ;
  scanmath ( curlist .tailfield + 1 , curlist .tailfield + 4 ) ;
} 
void 
mathac ( void ) 
{
  mathac_regmem 
  if ( curcmd == 49 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1214 ) ;
    } 
    printesc ( 561 ) ;
    print ( 1215 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 1216 ;
      helpline [0 ]= 1217 ;
    } 
    error () ;
  } 
  {
    mem [curlist .tailfield ].hh .v.RH = getnode ( 6 ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b0 = 30 ;
  mem [curlist .tailfield ].hh.b1 = 0 ;
  mem [curlist .tailfield + 1 ].hh = emptyfield ;
  mem [curlist .tailfield + 3 ].hh = emptyfield ;
  mem [curlist .tailfield + 2 ].hh = emptyfield ;
  mem [curlist .tailfield + 5 ].hh .v.RH = 1 ;
  scanfifteenbitint () ;
  mem [curlist .tailfield + 5 ].hh.b1 = curval % 256 ;
  if ( ( curval >= 28672 ) && ( ( eqtb [28506 ].cint >= 0 ) && ( eqtb [
  28506 ].cint < 16 ) ) ) 
  mem [curlist .tailfield + 5 ].hh.b0 = eqtb [28506 ].cint ;
  else mem [curlist .tailfield + 5 ].hh.b0 = ( curval / 256 ) % 16 ;
  scanmath ( curlist .tailfield + 1 , curlist .tailfield + 4 ) ;
} 
void 
appendchoices ( void ) 
{
  appendchoices_regmem 
  {
    mem [curlist .tailfield ].hh .v.RH = newchoice () ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  incr ( saveptr ) ;
  savestack [saveptr - 1 ].cint = 0 ;
  pushmath ( 13 ) ;
  scanleftbrace () ;
} 
halfword 
zfinmlist ( halfword p ) 
{
  register halfword Result; finmlist_regmem 
  halfword q  ;
  if ( curlist .auxfield .cint != -1073741823L ) 
  {
    mem [curlist .auxfield .cint + 3 ].hh .v.RH = 4 ;
    mem [curlist .auxfield .cint + 3 ].hh .v.LH = mem [curlist .headfield ]
    .hh .v.RH ;
    if ( p == -1073741823L ) 
    q = curlist .auxfield .cint ;
    else {
	
      q = mem [curlist .auxfield .cint + 2 ].hh .v.LH ;
      if ( mem [q ].hh.b0 != 32 ) 
      confusion ( 933 ) ;
      mem [curlist .auxfield .cint + 2 ].hh .v.LH = mem [q ].hh .v.RH ;
      mem [q ].hh .v.RH = curlist .auxfield .cint ;
      mem [curlist .auxfield .cint ].hh .v.RH = p ;
    } 
  } 
  else {
      
    mem [curlist .tailfield ].hh .v.RH = p ;
    q = mem [curlist .headfield ].hh .v.RH ;
  } 
  popnest () ;
  Result = q ;
  return Result ;
} 
void 
buildchoices ( void ) 
{
  /* 10 */ buildchoices_regmem 
  halfword p  ;
  unsave () ;
  p = finmlist ( -1073741823L ) ;
  switch ( savestack [saveptr - 1 ].cint ) 
  {case 0 : 
    mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    break ;
  case 1 : 
    mem [curlist .tailfield + 1 ].hh .v.RH = p ;
    break ;
  case 2 : 
    mem [curlist .tailfield + 2 ].hh .v.LH = p ;
    break ;
  case 3 : 
    {
      mem [curlist .tailfield + 2 ].hh .v.RH = p ;
      decr ( saveptr ) ;
      return ;
    } 
    break ;
  } 
  incr ( savestack [saveptr - 1 ].cint ) ;
  pushmath ( 13 ) ;
  scanleftbrace () ;
} 
void 
subsup ( void ) 
{
  subsup_regmem 
  smallnumber t  ;
  halfword p  ;
  t = 0 ;
  p = -1073741823L ;
  inhibitglueflag = false ;
  if ( curlist .tailfield != curlist .headfield ) {
      
    if ( ( mem [curlist .tailfield ].hh.b0 >= 18 ) && ( mem [curlist 
    .tailfield ].hh.b0 < 32 ) ) 
    {
      p = curlist .tailfield + 2 + curcmd - 7 ;
      t = mem [p ].hh .v.RH ;
    } 
  } 
  if ( ( p == -1073741823L ) || ( t != 0 ) ) 
  {
    {
      mem [curlist .tailfield ].hh .v.RH = newnoad () ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    p = curlist .tailfield + 2 + curcmd - 7 ;
    if ( t != 0 ) 
    {
      if ( curcmd == 7 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1218 ) ;
	} 
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1219 ;
	} 
      } 
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1220 ) ;
	} 
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1221 ;
	} 
      } 
      error () ;
    } 
  } 
  scanmath ( p , -1073741823L ) ;
} 
void 
mathfraction ( void ) 
{
  mathfraction_regmem 
  smallnumber c  ;
  c = curchr ;
  inhibitglueflag = false ;
  if ( curlist .auxfield .cint != -1073741823L ) 
  {
    if ( c >= 3 ) 
    {
      scandelimiter ( memtop - 12 , false ) ;
      scandelimiter ( memtop - 12 , false ) ;
    } 
    if ( c % 3 == 0 ) 
    scandimen ( false , false , false ) ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1228 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1229 ;
      helpline [1 ]= 1230 ;
      helpline [0 ]= 1231 ;
    } 
    error () ;
  } 
  else {
      
    curlist .auxfield .cint = getnode ( 6 ) ;
    mem [curlist .auxfield .cint ].hh.b0 = 27 ;
    mem [curlist .auxfield .cint ].hh.b1 = 0 ;
    mem [curlist .auxfield .cint + 2 ].hh .v.RH = 4 ;
    mem [curlist .auxfield .cint + 2 ].hh .v.LH = mem [curlist .headfield ]
    .hh .v.RH ;
    mem [curlist .auxfield .cint + 3 ].hh = emptyfield ;
    mem [curlist .auxfield .cint + 5 ].qqqq = nulldelimiter ;
    mem [curlist .auxfield .cint + 4 ].qqqq = nulldelimiter ;
    mem [curlist .headfield ].hh .v.RH = -1073741823L ;
    curlist .tailfield = curlist .headfield ;
    if ( c >= 3 ) 
    {
      scandelimiter ( curlist .auxfield .cint + 5 , false ) ;
      scandelimiter ( curlist .auxfield .cint + 4 , false ) ;
    } 
    switch ( c % 3 ) 
    {case 0 : 
      {
	scandimen ( false , false , false ) ;
	mem [curlist .auxfield .cint + 1 ].cint = curval ;
      } 
      break ;
    case 1 : 
      mem [curlist .auxfield .cint + 1 ].cint = 1073741824L ;
      break ;
    case 2 : 
      mem [curlist .auxfield .cint + 1 ].cint = 0 ;
      break ;
    } 
  } 
} 
void 
mathleftright ( void ) 
{
  mathleftright_regmem 
  smallnumber t  ;
  halfword p  ;
  t = curchr ;
  inhibitglueflag = false ;
  if ( ( t == 33 ) && ( curgroup != 16 ) ) 
  {
    if ( curgroup == 15 ) 
    {
      scandelimiter ( memtop - 12 , false ) ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 832 ) ;
      } 
      printesc ( 933 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 1232 ;
      } 
      error () ;
    } 
    else offsave () ;
  } 
  else {
      
    p = newnoad () ;
    mem [p ].hh.b0 = t ;
    scandelimiter ( p + 1 , false ) ;
    if ( t == 32 ) 
    {
      pushmath ( 16 ) ;
      mem [curlist .headfield ].hh .v.RH = p ;
      curlist .tailfield = p ;
    } 
    else {
	
      p = finmlist ( p ) ;
      unsave () ;
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = 25 ;
      mem [curlist .tailfield + 1 ].hh .v.RH = 4 ;
      mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    } 
  } 
} 
void 
aftermath ( void ) 
{
  aftermath_regmem 
  boolean l  ;
  scaled disp  ;
  boolean danger  ;
  integer m  ;
  halfword p  ;
  halfword a  ;
  halfword b  ;
  scaled w  ;
  scaled z  ;
  scaled e  ;
  scaled q  ;
  scaled d  ;
  scaled s  ;
  smallnumber g1, g2  ;
  halfword r  ;
  halfword t  ;
  danger = false ;
  if ( ( fontparams [eqtb [25585 ].hh .v.RH ]< 22 ) || ( fontparams [eqtb 
  [25601 ].hh .v.RH ]< 22 ) || ( fontparams [eqtb [25617 ].hh .v.RH ]< 
  22 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1233 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1234 ;
      helpline [1 ]= 1235 ;
      helpline [0 ]= 1236 ;
    } 
    error () ;
    flushmath () ;
    danger = true ;
  } 
  else if ( ( fontparams [eqtb [25586 ].hh .v.RH ]< 13 ) || ( fontparams [
  eqtb [25602 ].hh .v.RH ]< 13 ) || ( fontparams [eqtb [25618 ].hh .v.RH 
  ]< 13 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1237 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1238 ;
      helpline [1 ]= 1239 ;
      helpline [0 ]= 1240 ;
    } 
    error () ;
    flushmath () ;
    danger = true ;
  } 
  deleteglueref ( curkanjiskip ) ;
  deleteglueref ( curxkanjiskip ) ;
  if ( eqtb [25633 ].hh .v.RH > 0 ) 
  curkanjiskip = eqtb [24542 ].hh .v.RH ;
  else curkanjiskip = membot ;
  if ( eqtb [25634 ].hh .v.RH > 0 ) 
  curxkanjiskip = eqtb [24543 ].hh .v.RH ;
  else curxkanjiskip = membot ;
  incr ( mem [curkanjiskip ].hh .v.RH ) ;
  incr ( mem [curxkanjiskip ].hh .v.RH ) ;
  m = curlist .modefield ;
  l = false ;
  p = finmlist ( -1073741823L ) ;
  if ( curlist .modefield == - (integer) m ) 
  {
    {
      getxtoken () ;
      if ( curcmd != 3 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1241 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1242 ;
	  helpline [0 ]= 1243 ;
	} 
	backerror () ;
      } 
    } 
    curmlist = p ;
    curstyle = 2 ;
    mlistpenalties = false ;
    mlisttohlist () ;
    a = hpack ( mem [memtop - 3 ].hh .v.RH , 0 , 1 ) ;
    unsave () ;
    decr ( saveptr ) ;
    if ( savestack [saveptr + 0 ].cint == 1 ) 
    l = true ;
    danger = false ;
    if ( ( fontparams [eqtb [25585 ].hh .v.RH ]< 22 ) || ( fontparams [
    eqtb [25601 ].hh .v.RH ]< 22 ) || ( fontparams [eqtb [25617 ].hh 
    .v.RH ]< 22 ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1233 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 1234 ;
	helpline [1 ]= 1235 ;
	helpline [0 ]= 1236 ;
      } 
      error () ;
      flushmath () ;
      danger = true ;
    } 
    else if ( ( fontparams [eqtb [25586 ].hh .v.RH ]< 13 ) || ( fontparams 
    [eqtb [25602 ].hh .v.RH ]< 13 ) || ( fontparams [eqtb [25618 ].hh 
    .v.RH ]< 13 ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1237 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 1238 ;
	helpline [1 ]= 1239 ;
	helpline [0 ]= 1240 ;
      } 
      error () ;
      flushmath () ;
      danger = true ;
    } 
    m = curlist .modefield ;
    p = finmlist ( -1073741823L ) ;
  } 
  else a = -1073741823L ;
  if ( m < 0 ) 
  {
    if ( curlist .dirfield == 3 ) 
    disp = eqtb [29059 ].cint ;
    else disp = eqtb [29060 ].cint ;
    {
      if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield 
      ].hh.b0 == 5 ) ) 
      {
	if ( curlist .pdispfield == disp ) 
	{
	  freenode ( curlist .tailfield , 2 ) ;
	  curlist .tailfield = curlist .pnodefield ;
	  mem [curlist .tailfield ].hh .v.RH = -1073741823L ;
	} 
	else mem [curlist .tailfield + 1 ].cint = disp ;
      } 
      else if ( disp != 0 ) 
      {
	curlist .pnodefield = curlist .tailfield ;
	{
	  mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b0 = 5 ;
	mem [curlist .tailfield + 1 ].cint = disp ;
	curlist .pdispfield = disp ;
      } 
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newmath ( eqtb [29039 ].cint , 
      0 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    curmlist = p ;
    curstyle = 2 ;
    mlistpenalties = ( curlist .modefield > 0 ) ;
    mlisttohlist () ;
    mem [curlist .tailfield ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
    while ( mem [curlist .tailfield ].hh .v.RH != -1073741823L ) curlist 
    .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    {
      mem [curlist .tailfield ].hh .v.RH = newmath ( eqtb [29039 ].cint , 
      1 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( disp != 0 ) 
    {
      if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield 
      ].hh.b0 == 5 ) ) 
      {
	mem [curlist .tailfield + 1 ].cint = 0 ;
      } 
      else {
	  
	curlist .pnodefield = curlist .tailfield ;
	{
	  mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b0 = 5 ;
	mem [curlist .tailfield + 1 ].cint = 0 ;
	curlist .pdispfield = disp ;
      } 
    } 
    curlist .auxfield .hh .v.LH = 1000 ;
    unsave () ;
  } 
  else {
      
    if ( a == -1073741823L ) 
    {
      getxtoken () ;
      if ( curcmd != 3 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1241 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1242 ;
	  helpline [0 ]= 1243 ;
	} 
	backerror () ;
      } 
    } 
    curmlist = p ;
    curstyle = 0 ;
    mlistpenalties = false ;
    mlisttohlist () ;
    p = mem [memtop - 3 ].hh .v.RH ;
    adjusttail = memtop - 5 ;
    b = hpack ( p , 0 , 1 ) ;
    p = mem [b + 5 ].hh .v.RH ;
    t = adjusttail ;
    adjusttail = -1073741823L ;
    w = mem [b + 1 ].cint ;
    z = eqtb [29052 ].cint ;
    s = eqtb [29053 ].cint ;
    if ( ( a == -1073741823L ) || danger ) 
    {
      e = 0 ;
      q = 0 ;
    } 
    else {
	
      e = mem [a + 1 ].cint ;
      q = e + fontinfo [6 + parambase [eqtb [25585 ].hh .v.RH ]].cint ;
    } 
    if ( w + q > z ) 
    {
      if ( ( e != 0 ) && ( ( w - totalshrink [0 ]+ q <= z ) || ( totalshrink 
      [1 ]!= 0 ) || ( totalshrink [2 ]!= 0 ) || ( totalshrink [3 ]!= 0 ) 
      ) ) 
      {
	deleteglueref ( mem [b + 7 ].hh .v.RH ) ;
	deleteglueref ( mem [b + 7 ].hh .v.LH ) ;
	freenode ( b , 10 ) ;
	b = hpack ( p , z - q , 0 ) ;
      } 
      else {
	  
	e = 0 ;
	if ( w > z ) 
	{
	  deleteglueref ( mem [b + 7 ].hh .v.RH ) ;
	  deleteglueref ( mem [b + 7 ].hh .v.LH ) ;
	  freenode ( b , 10 ) ;
	  b = hpack ( p , z , 0 ) ;
	} 
      } 
      w = mem [b + 1 ].cint ;
    } 
    d = half ( z - w ) ;
    if ( ( e > 0 ) && ( d < 2 * e ) ) 
    {
      d = half ( z - w - e ) ;
      if ( p != -1073741823L ) {
	  
	if ( ! ( p >= himemmin ) ) {
	    
	  if ( mem [p ].hh.b0 == 12 ) 
	  d = 0 ;
	} 
      } 
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [28473 ].cint 
      ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( ( d + s <= eqtb [29051 ].cint ) || l ) 
    {
      g1 = 3 ;
      g2 = 4 ;
    } 
    else {
	
      g1 = 5 ;
      g2 = 6 ;
    } 
    if ( l && ( e == 0 ) ) 
    {
      mem [a + 4 ].cint = s ;
      appendtovlist ( a ) ;
      {
	mem [curlist .tailfield ].hh .v.RH = newpenalty ( 10000 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
    } 
    else {
	
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( g1 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( e != 0 ) 
    {
      r = newkern ( z - w - e - d ) ;
      if ( l ) 
      {
	mem [a ].hh .v.RH = r ;
	mem [r ].hh .v.RH = b ;
	b = a ;
	d = 0 ;
      } 
      else {
	  
	mem [b ].hh .v.RH = r ;
	mem [r ].hh .v.RH = a ;
      } 
      b = hpack ( b , 0 , 1 ) ;
    } 
    mem [b + 4 ].cint = s + d ;
    appendtovlist ( b ) ;
    if ( ( a != -1073741823L ) && ( e == 0 ) && ! l ) 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = newpenalty ( 10000 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [a + 4 ].cint = s + z - mem [a + 1 ].cint ;
      appendtovlist ( a ) ;
      g2 = 0 ;
    } 
    if ( t != memtop - 5 ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 5 ].hh .v.RH ;
      curlist .tailfield = t ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [28474 ].cint 
      ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( g2 > 0 ) 
    {
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( g2 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    resumeafterdisplay () ;
  } 
} 
void 
resumeafterdisplay ( void ) 
{
  resumeafterdisplay_regmem 
  if ( curgroup != 15 ) 
  confusion ( 1244 ) ;
  unsave () ;
  curlist .pgfield = curlist .pgfield + 3 ;
  pushnest () ;
  curlist .adjdirfield = abs ( curlist .dirfield ) ;
  curlist .modefield = 117 ;
  curlist .auxfield .hh .v.LH = 1000 ;
  if ( eqtb [28513 ].cint <= 0 ) 
  curlang = 0 ;
  else if ( eqtb [28513 ].cint > 255 ) 
  curlang = 0 ;
  else curlang = eqtb [28513 ].cint ;
  curlist .auxfield .hh .v.RH = curlang ;
  curlist .pgfield = ( normmin ( eqtb [28514 ].cint ) * 64 + normmin ( eqtb 
  [28515 ].cint ) ) * 65536L + curlang ;
  {
    getxtoken () ;
    if ( curcmd != 10 ) 
    backinput () ;
  } 
  if ( nestptr == 1 ) 
  buildpage () ;
} 
void 
getrtoken ( void ) 
{
  /* 20 */ getrtoken_regmem 
  lab20: do {
      gettoken () ;
  } while ( ! ( curtok != 2592 ) ) ;
  if ( ( curcs == 0 ) || ( curcs > eqtbtop ) || ( ( curcs > 15514 ) && ( curcs 
  <= 29572 ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1259 ) ;
    } 
    {
      helpptr = 5 ;
      helpline [4 ]= 1260 ;
      helpline [3 ]= 1261 ;
      helpline [2 ]= 1262 ;
      helpline [1 ]= 1263 ;
      helpline [0 ]= 1264 ;
    } 
    if ( curcs == 0 ) 
    backinput () ;
    curtok = 536886425L ;
    inserror () ;
    goto lab20 ;
  } 
} 
void 
trapzeroglue ( void ) 
{
  trapzeroglue_regmem 
  if ( ( mem [curval + 1 ].cint == 0 ) && ( mem [curval + 2 ].cint == 0 ) 
  && ( mem [curval + 3 ].cint == 0 ) ) 
  {
    incr ( mem [membot ].hh .v.RH ) ;
    deleteglueref ( curval ) ;
    curval = membot ;
  } 
} 
void 
zdoregistercommand ( smallnumber a ) 
{
  /* 40 10 */ doregistercommand_regmem 
  halfword l, q, r, s  ;
  unsigned char p  ;
  q = curcmd ;
  {
    if ( q != 102 ) 
    {
      getxtoken () ;
      if ( ( curcmd >= 81 ) && ( curcmd <= 84 ) ) 
      {
	l = curchr ;
	p = curcmd - 81 ;
	goto lab40 ;
      } 
      if ( curcmd != 102 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 726 ) ;
	} 
	printcmdchr ( curcmd , curchr ) ;
	print ( 727 ) ;
	printcmdchr ( q , 0 ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1291 ;
	} 
	error () ;
	return ;
      } 
    } 
    p = curchr ;
    scaneightbitint () ;
    switch ( p ) 
    {case 0 : 
      l = curval + 28526 ;
      break ;
    case 1 : 
      l = curval + 29061 ;
      break ;
    case 2 : 
      l = curval + 24548 ;
      break ;
    case 3 : 
      l = curval + 24804 ;
      break ;
    } 
  } 
  lab40: ;
  if ( q == 102 ) 
  scanoptionalequals () ;
  else if ( scankeyword ( 1287 ) ) 
  ;
  aritherror = false ;
  if ( q < 104 ) {
      
    if ( p < 2 ) 
    {
      if ( p == 0 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      if ( q == 103 ) 
      curval = curval + eqtb [l ].cint ;
    } 
    else {
	
      scanglue ( p ) ;
      if ( q == 103 ) 
      {
	q = newspec ( curval ) ;
	r = eqtb [l ].hh .v.RH ;
	deleteglueref ( curval ) ;
	mem [q + 1 ].cint = mem [q + 1 ].cint + mem [r + 1 ].cint ;
	if ( mem [q + 2 ].cint == 0 ) 
	mem [q ].hh.b0 = 0 ;
	if ( mem [q ].hh.b0 == mem [r ].hh.b0 ) 
	mem [q + 2 ].cint = mem [q + 2 ].cint + mem [r + 2 ].cint ;
	else if ( ( mem [q ].hh.b0 < mem [r ].hh.b0 ) && ( mem [r + 2 ]
	.cint != 0 ) ) 
	{
	  mem [q + 2 ].cint = mem [r + 2 ].cint ;
	  mem [q ].hh.b0 = mem [r ].hh.b0 ;
	} 
	if ( mem [q + 3 ].cint == 0 ) 
	mem [q ].hh.b1 = 0 ;
	if ( mem [q ].hh.b1 == mem [r ].hh.b1 ) 
	mem [q + 3 ].cint = mem [q + 3 ].cint + mem [r + 3 ].cint ;
	else if ( ( mem [q ].hh.b1 < mem [r ].hh.b1 ) && ( mem [r + 3 ]
	.cint != 0 ) ) 
	{
	  mem [q + 3 ].cint = mem [r + 3 ].cint ;
	  mem [q ].hh.b1 = mem [r ].hh.b1 ;
	} 
	curval = q ;
      } 
    } 
  } 
  else {
      
    scanint () ;
    if ( p < 2 ) {
	
      if ( q == 104 ) {
	  
	if ( p == 0 ) 
	curval = multandadd ( eqtb [l ].cint , curval , 0 , 2147483647L ) ;
	else curval = multandadd ( eqtb [l ].cint , curval , 0 , 1073741823L 
	) ;
      } 
      else curval = xovern ( eqtb [l ].cint , curval ) ;
    } 
    else {
	
      s = eqtb [l ].hh .v.RH ;
      r = newspec ( s ) ;
      if ( q == 104 ) 
      {
	mem [r + 1 ].cint = multandadd ( mem [s + 1 ].cint , curval , 0 , 
	1073741823L ) ;
	mem [r + 2 ].cint = multandadd ( mem [s + 2 ].cint , curval , 0 , 
	1073741823L ) ;
	mem [r + 3 ].cint = multandadd ( mem [s + 3 ].cint , curval , 0 , 
	1073741823L ) ;
      } 
      else {
	  
	mem [r + 1 ].cint = xovern ( mem [s + 1 ].cint , curval ) ;
	mem [r + 2 ].cint = xovern ( mem [s + 2 ].cint , curval ) ;
	mem [r + 3 ].cint = xovern ( mem [s + 3 ].cint , curval ) ;
      } 
      curval = r ;
    } 
  } 
  if ( aritherror ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1288 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 1289 ;
      helpline [0 ]= 1290 ;
    } 
    if ( p >= 2 ) 
    deleteglueref ( curval ) ;
    error () ;
    return ;
  } 
  if ( p < 2 ) {
      
    if ( ( a >= 4 ) ) 
    geqworddefine ( l , curval ) ;
    else eqworddefine ( l , curval ) ;
  } 
  else {
      
    trapzeroglue () ;
    if ( ( a >= 4 ) ) 
    geqdefine ( l , 132 , curval ) ;
    else eqdefine ( l , 132 , curval ) ;
  } 
} 
void 
alteraux ( void ) 
{
  alteraux_regmem 
  halfword c  ;
  if ( curchr != abs ( curlist .modefield ) ) 
  reportillegalcase () ;
  else {
      
    c = curchr ;
    scanoptionalequals () ;
    if ( c == 1 ) 
    {
      scandimen ( false , false , false ) ;
      curlist .auxfield .cint = curval ;
    } 
    else {
	
      scanint () ;
      if ( ( curval <= 0 ) || ( curval > 32767 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1294 ) ;
	} 
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1295 ;
	} 
	interror ( curval ) ;
      } 
      else curlist .auxfield .hh .v.LH = curval ;
    } 
  } 
} 
void 
alterprevgraf ( void ) 
{
  alterprevgraf_regmem 
  integer p  ;
  nest [nestptr ]= curlist ;
  p = nestptr ;
  while ( abs ( nest [p ].modefield ) != 1 ) decr ( p ) ;
  scanoptionalequals () ;
  scanint () ;
  if ( curval < 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1012 ) ;
    } 
    printesc ( 570 ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 1296 ;
    } 
    interror ( curval ) ;
  } 
  else {
      
    nest [p ].pgfield = curval ;
    curlist = nest [nestptr ];
  } 
} 
void 
alterpagesofar ( void ) 
{
  alterpagesofar_regmem 
  unsigned char c  ;
  c = curchr ;
  scanoptionalequals () ;
  scandimen ( false , false , false ) ;
  pagesofar [c ]= curval ;
} 
void 
alterinteger ( void ) 
{
  alterinteger_regmem 
  unsigned char c  ;
  c = curchr ;
  scanoptionalequals () ;
  scanint () ;
  if ( c == 0 ) 
  deadcycles = curval ;
  else insertpenalties = curval ;
} 
void 
alterboxdimen ( void ) 
{
  alterboxdimen_regmem 
  smallnumber c  ;
  halfword p, q  ;
  eightbits b  ;
  c = curchr ;
  scaneightbitint () ;
  b = curval ;
  scanoptionalequals () ;
  scandimen ( false , false , false ) ;
  if ( eqtb [25326 + b ].hh .v.RH != -1073741823L ) 
  {
    q = eqtb [25326 + b ].hh .v.RH ;
    p = mem [q ].hh .v.RH ;
    while ( p != -1073741823L ) {
	
      if ( abs ( curlist .dirfield ) == ( mem [p ].hh.b1 ) ) 
      q = p ;
      p = mem [p ].hh .v.RH ;
    } 
    if ( ( mem [q ].hh.b1 ) != abs ( curlist .dirfield ) ) 
    {
      p = mem [eqtb [25326 + b ].hh .v.RH ].hh .v.RH ;
      mem [eqtb [25326 + b ].hh .v.RH ].hh .v.RH = -1073741823L ;
      q = newdirnode ( q , abs ( curlist .dirfield ) ) ;
      mem [q + 5 ].hh .v.RH = -1073741823L ;
      mem [q ].hh .v.RH = p ;
      mem [eqtb [25326 + b ].hh .v.RH ].hh .v.RH = q ;
    } 
    mem [q + c ].cint = curval ;
  } 
} 
void 
znewfont ( smallnumber a ) 
{
  /* 50 */ newfont_regmem 
  halfword u  ;
  scaled s  ;
  internalfontnumber f  ;
  strnumber t  ;
  unsigned char oldsetting  ;
  if ( jobname == 0 ) 
  openlogfile () ;
  getrtoken () ;
  u = curcs ;
  if ( u >= 514 ) 
  t = hash [u ].v.RH ;
  else if ( u >= 257 ) {
      
    if ( u == 513 ) 
    t = 1300 ;
    else t = u - 257 ;
  } 
  else {
      
    oldsetting = selector ;
    selector = 21 ;
    print ( 1300 ) ;
    print ( u - 1 ) ;
    selector = oldsetting ;
    {
      if ( poolptr + 1 > poolsize ) 
      overflow ( 258 , poolsize - initpoolptr ) ;
    } 
    t = makestring () ;
  } 
  if ( ( a >= 4 ) ) 
  geqdefine ( u , 98 , 0 ) ;
  else eqdefine ( u , 98 , 0 ) ;
  scanoptionalequals () ;
  scanfilename () ;
  nameinprogress = true ;
  if ( scankeyword ( 1301 ) ) 
  {
    scandimen ( false , false , false ) ;
    s = curval ;
    if ( ( s <= 0 ) || ( s >= 134217728L ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1303 ) ;
      } 
      printscaled ( s ) ;
      print ( 1304 ) ;
      {
	helpptr = 2 ;
	helpline [1 ]= 1305 ;
	helpline [0 ]= 1306 ;
      } 
      error () ;
      s = 10 * 65536L ;
    } 
  } 
  else if ( scankeyword ( 1302 ) ) 
  {
    scanint () ;
    s = - (integer) curval ;
    if ( ( curval <= 0 ) || ( curval > 32768L ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 590 ) ;
      } 
      {
	helpptr = 1 ;
	helpline [0 ]= 591 ;
      } 
      interror ( curval ) ;
      s = -1000 ;
    } 
  } 
  else s = -1000 ;
  nameinprogress = false ;
  {register integer for_end; f = 1 ;for_end = fontptr ; if ( f <= for_end) 
  do 
    if ( streqstr ( fontname [f ], curname ) && streqstr ( fontarea [f ], 
    curarea ) ) 
    {
      if ( s > 0 ) 
      {
	if ( s == fontsize [f ]) 
	goto lab50 ;
      } 
      else if ( fontsize [f ]== xnoverd ( fontdsize [f ], - (integer) s , 
      1000 ) ) 
      goto lab50 ;
    } 
  while ( f++ < for_end ) ;} 
  f = readfontinfo ( u , curname , curarea , s ) ;
  lab50: eqtb [u ].hh .v.RH = f ;
  eqtb [15525 + f ]= eqtb [u ];
  hash [15525 + f ].v.RH = t ;
} 
void 
newinteraction ( void ) 
{
  newinteraction_regmem 
  println () ;
  interaction = curchr ;
  if ( interaction == 0 ) 
  kpsemaketexdiscarderrors = 1 ;
  else kpsemaketexdiscarderrors = 0 ;
  if ( interaction == 0 ) 
  selector = 16 ;
  else selector = 17 ;
  if ( logopened ) 
  selector = selector + 2 ;
} 
void 
doassignments ( void ) 
{
  /* 10 */ doassignments_regmem 
  while ( true ) {
      
    do {
	getxtoken () ;
    } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
    if ( curcmd <= 78 ) 
    return ;
    setboxallowed = false ;
    prefixedcommand () ;
    setboxallowed = true ;
  } 
} 
void 
openorclosein ( void ) 
{
  openorclosein_regmem 
  unsigned char c  ;
  unsigned char n  ;
  c = curchr ;
  scanfourbitint () ;
  n = curval ;
  if ( readopen [n ]!= 2 ) 
  {
    aclose ( readfile [n ]) ;
    readopen [n ]= 2 ;
  } 
  if ( c != 0 ) 
  {
    scanoptionalequals () ;
    scanfilename () ;
    packfilename ( curname , curarea , curext ) ;
    texinputtype = 0 ;
    if ( kpseinnameok ( stringcast ( nameoffile + 1 ) ) && aopenin ( readfile 
    [n ], kpsetexformat ) ) 
    readopen [n ]= 1 ;
  } 
} 
void 
issuemessage ( void ) 
{
  issuemessage_regmem 
  unsigned char oldsetting  ;
  unsigned char c  ;
  strnumber s  ;
  c = curchr ;
  mem [memtop - 12 ].hh .v.RH = scantoks ( false , true ) ;
  oldsetting = selector ;
  selector = 21 ;
  tokenshow ( defref ) ;
  selector = oldsetting ;
  flushlist ( defref ) ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 258 , poolsize - initpoolptr ) ;
  } 
  s = makestring () ;
  if ( c == 0 ) 
  {
    if ( termoffset + ( strstart [s + 1 ]- strstart [s ]) > maxprintline - 
    2 ) 
    println () ;
    else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
    printchar ( 32 ) ;
    slowprint ( s ) ;
    fflush ( stdout ) ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 344 ) ;
    } 
    slowprint ( s ) ;
    if ( eqtb [25069 ].hh .v.RH != -1073741823L ) 
    useerrhelp = true ;
    else if ( longhelpseen ) 
    {
      helpptr = 1 ;
      helpline [0 ]= 1313 ;
    } 
    else {
	
      if ( interaction < 3 ) 
      longhelpseen = true ;
      {
	helpptr = 4 ;
	helpline [3 ]= 1314 ;
	helpline [2 ]= 1315 ;
	helpline [1 ]= 1316 ;
	helpline [0 ]= 1317 ;
      } 
    } 
    error () ;
    useerrhelp = false ;
  } 
  {
    decr ( strptr ) ;
    poolptr = strstart [strptr ];
  } 
} 
void 
shiftcase ( void ) 
{
  shiftcase_regmem 
  halfword b  ;
  halfword p  ;
  halfword t  ;
  eightbits c  ;
  b = curchr ;
  p = scantoks ( false , false ) ;
  p = mem [defref ].hh .v.RH ;
  while ( p != -1073741823L ) {
      
    t = mem [p ].hh .v.LH ;
    if ( ( t < 536871168L ) && ( ! checkkanji ( t ) ) ) 
    {
      c = t % 256 ;
      if ( eqtb [b + c ].hh .v.RH != 0 ) 
      mem [p ].hh .v.LH = t - c + eqtb [b + c ].hh .v.RH ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  begintokenlist ( mem [defref ].hh .v.RH , 3 ) ;
  {
    mem [defref ].hh .v.RH = avail ;
    avail = defref ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
} 
void 
showwhatever ( void ) 
{
  /* 50 */ showwhatever_regmem 
  halfword p  ;
  switch ( curchr ) 
  {case 3 : 
    {
      begindiagnostic () ;
      showactivities () ;
    } 
    break ;
  case 1 : 
    {
      scaneightbitint () ;
      begindiagnostic () ;
      printnl ( 1336 ) ;
      printint ( curval ) ;
      printchar ( 61 ) ;
      if ( eqtb [25326 + curval ].hh .v.RH == -1073741823L ) 
      print ( 429 ) ;
      else showbox ( eqtb [25326 + curval ].hh .v.RH ) ;
    } 
    break ;
  case 0 : 
    {
      gettoken () ;
      if ( interaction == 3 ) 
      ;
      printnl ( 1330 ) ;
      if ( curcs != 0 ) 
      {
	sprintcs ( curcs ) ;
	printchar ( 61 ) ;
      } 
      printmeaning () ;
      goto lab50 ;
    } 
    break ;
  case 4 : 
    {
      printnl ( 1330 ) ;
      if ( eqtb [25633 ].hh .v.RH > 0 ) 
      print ( 1418 ) ;
      else print ( 1419 ) ;
      printnl ( 1330 ) ;
      if ( eqtb [25634 ].hh .v.RH > 0 ) 
      print ( 1420 ) ;
      else print ( 1421 ) ;
      goto lab50 ;
    } 
    break ;
    default: 
    {
      p = thetoks () ;
      if ( interaction == 3 ) 
      ;
      printnl ( 1330 ) ;
      tokenshow ( memtop - 3 ) ;
      flushlist ( mem [memtop - 3 ].hh .v.RH ) ;
      goto lab50 ;
    } 
    break ;
  } 
  enddiagnostic ( true ) ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 263 ) ;
    print ( 1337 ) ;
  } 
  if ( selector == 19 ) {
      
    if ( eqtb [28491 ].cint <= 0 ) 
    {
      selector = 17 ;
      print ( 1338 ) ;
      selector = 19 ;
    } 
  } 
  lab50: if ( interaction < 3 ) 
  {
    helpptr = 0 ;
    decr ( errorcount ) ;
  } 
  else if ( eqtb [28491 ].cint > 0 ) 
  {
    {
      helpptr = 3 ;
      helpline [2 ]= 1325 ;
      helpline [1 ]= 1326 ;
      helpline [0 ]= 1327 ;
    } 
  } 
  else {
      
    {
      helpptr = 5 ;
      helpline [4 ]= 1325 ;
      helpline [3 ]= 1326 ;
      helpline [2 ]= 1327 ;
      helpline [1 ]= 1328 ;
      helpline [0 ]= 1329 ;
    } 
  } 
  error () ;
} 
void 
znewwhatsit ( smallnumber s , smallnumber w ) 
{
  newwhatsit_regmem 
  halfword p  ;
  p = getnode ( w ) ;
  mem [p ].hh.b0 = 10 ;
  mem [p ].hh.b1 = s ;
  mem [curlist .tailfield ].hh .v.RH = p ;
  curlist .tailfield = p ;
} 
void 
znewwritewhatsit ( smallnumber w ) 
{
  newwritewhatsit_regmem 
  newwhatsit ( curchr , w ) ;
  if ( w != 2 ) 
  scanfourbitint () ;
  else {
      
    scanint () ;
    if ( curval < 0 ) 
    curval = 17 ;
    else if ( ( curval > 15 ) && ( curval != 18 ) ) 
    curval = 16 ;
  } 
  mem [curlist .tailfield + 1 ].hh .v.LH = curval ;
} 
void 
doextension ( void ) 
{
  doextension_regmem 
  integer k  ;
  halfword p  ;
  switch ( curchr ) 
  {case 0 : 
    {
      newwritewhatsit ( 3 ) ;
      scanoptionalequals () ;
      scanfilename () ;
      mem [curlist .tailfield + 1 ].hh .v.RH = curname ;
      mem [curlist .tailfield + 2 ].hh .v.LH = curarea ;
      mem [curlist .tailfield + 2 ].hh .v.RH = curext ;
    } 
    break ;
  case 1 : 
    {
      k = curcs ;
      newwritewhatsit ( 2 ) ;
      curcs = k ;
      p = scantoks ( false , false ) ;
      mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    } 
    break ;
  case 2 : 
    {
      newwritewhatsit ( 2 ) ;
      mem [curlist .tailfield + 1 ].hh .v.RH = -1073741823L ;
    } 
    break ;
  case 3 : 
    {
      newwhatsit ( 3 , 2 ) ;
      mem [curlist .tailfield + 1 ].hh .v.LH = -1073741823L ;
      p = scantoks ( false , true ) ;
      mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    } 
    break ;
  case 4 : 
    {
      getxtoken () ;
      if ( ( curcmd == 64 ) && ( curchr <= 2 ) ) 
      {
	p = curlist .tailfield ;
	doextension () ;
	outwhat ( curlist .tailfield ) ;
	flushnodelist ( curlist .tailfield ) ;
	curlist .tailfield = p ;
	mem [p ].hh .v.RH = -1073741823L ;
      } 
      else backinput () ;
    } 
    break ;
  case 5 : 
    if ( abs ( curlist .modefield ) != 117 ) 
    reportillegalcase () ;
    else {
	
      newwhatsit ( 4 , 2 ) ;
      scanint () ;
      if ( curval <= 0 ) 
      curlist .auxfield .hh .v.RH = 0 ;
      else if ( curval > 255 ) 
      curlist .auxfield .hh .v.RH = 0 ;
      else curlist .auxfield .hh .v.RH = curval ;
      mem [curlist .tailfield + 1 ].hh .v.RH = curlist .auxfield .hh .v.RH ;
      mem [curlist .tailfield + 1 ].hh.b0 = normmin ( eqtb [28514 ].cint ) 
      ;
      mem [curlist .tailfield + 1 ].hh.b1 = normmin ( eqtb [28515 ].cint ) 
      ;
    } 
    break ;
    default: 
    confusion ( 1376 ) ;
    break ;
  } 
} 
void 
fixlanguage ( void ) 
{
  fixlanguage_regmem 
  ASCIIcode l  ;
  if ( eqtb [28513 ].cint <= 0 ) 
  l = 0 ;
  else if ( eqtb [28513 ].cint > 255 ) 
  l = 0 ;
  else l = eqtb [28513 ].cint ;
  if ( l != curlist .auxfield .hh .v.RH ) 
  {
    newwhatsit ( 4 , 2 ) ;
    mem [curlist .tailfield + 1 ].hh .v.RH = l ;
    curlist .auxfield .hh .v.RH = l ;
    mem [curlist .tailfield + 1 ].hh.b0 = normmin ( eqtb [28514 ].cint ) ;
    mem [curlist .tailfield + 1 ].hh.b1 = normmin ( eqtb [28515 ].cint ) ;
  } 
} 
void 
zsetmathkchar ( integer c ) 
{
  setmathkchar_regmem 
  halfword p  ;
  p = newnoad () ;
  mem [p + 1 ].hh .v.RH = 6 ;
  inhibitglueflag = false ;
  mem [p + 1 ].hh.b1 = 0 ;
  mem [p + 4 ].hh .v.LH = c ;
  mem [p + 1 ].hh.b0 = eqtb [28507 ].cint ;
  if ( fontdir [eqtb [25583 + mem [p + 1 ].hh.b0 + cursize ].hh .v.RH ]
  == 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 263 ) ;
      print ( 1203 ) ;
    } 
    {
      helpptr = 1 ;
      helpline [0 ]= 1202 ;
    } 
    error () ;
  } 
  mem [p ].hh.b0 = 18 ;
  mem [curlist .tailfield ].hh .v.RH = p ;
  curlist .tailfield = p ;
} 
void 
insertsrcspecial ( void ) 
{
  insertsrcspecial_regmem 
  halfword toklist, p, q  ;
  if ( ( sourcefilenamestack [inopen ]> 0 && isnewsource ( 
  sourcefilenamestack [inopen ], line ) ) ) 
  {
    toklist = getavail () ;
    p = toklist ;
    mem [p ].hh .v.LH = 536886435L ;
    mem [p ].hh .v.RH = getavail () ;
    p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.LH = 379 ;
    q = strtoks ( makesrcspecial ( sourcefilenamestack [inopen ], line ) ) ;
    mem [p ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
    p = q ;
    mem [p ].hh .v.RH = getavail () ;
    p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.LH = 637 ;
    begintokenlist ( toklist , 4 ) ;
    remembersourceinfo ( sourcefilenamestack [inopen ], line ) ;
  } 
} 
void 
appendsrcspecial ( void ) 
{
  appendsrcspecial_regmem 
  halfword q  ;
  if ( ( sourcefilenamestack [inopen ]> 0 && isnewsource ( 
  sourcefilenamestack [inopen ], line ) ) ) 
  {
    newwhatsit ( 3 , 2 ) ;
    mem [curlist .tailfield + 1 ].hh .v.LH = 0 ;
    defref = getavail () ;
    mem [defref ].hh .v.LH = -1073741823L ;
    q = strtoks ( makesrcspecial ( sourcefilenamestack [inopen ], line ) ) ;
    mem [defref ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
    mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    remembersourceinfo ( sourcefilenamestack [inopen ], line ) ;
  } 
} 
void 
handlerightbrace ( void ) 
{
  handlerightbrace_regmem 
  halfword p, q  ;
  halfword r  ;
  scaled d  ;
  integer f  ;
  switch ( curgroup ) 
  {case 1 : 
    unsave () ;
    break ;
  case 0 : 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 1102 ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 1103 ;
	helpline [0 ]= 1104 ;
      } 
      error () ;
    } 
    break ;
  case 14 : 
  case 15 : 
  case 16 : 
    extrarightbrace () ;
    break ;
  case 2 : 
    {
      adjusthlist ( curlist .headfield , false ) ;
      package ( 0 ) ;
    } 
    break ;
  case 3 : 
    {
      adjusthlist ( curlist .headfield , false ) ;
      adjusttail = memtop - 5 ;
      package ( 0 ) ;
    } 
    break ;
  case 4 : 
    {
      endgraf () ;
      package ( 0 ) ;
    } 
    break ;
  case 5 : 
    {
      endgraf () ;
      package ( 4 ) ;
    } 
    break ;
  case 11 : 
    {
      endgraf () ;
      q = eqtb [24537 ].hh .v.RH ;
      incr ( mem [q ].hh .v.RH ) ;
      d = eqtb [29044 ].cint ;
      f = eqtb [28504 ].cint ;
      unsave () ;
      decr ( saveptr ) ;
      p = vpackage ( mem [curlist .headfield ].hh .v.RH , 0 , 1 , 
      1073741823L ) ;
      mem [p ].hh.b1 = abs ( curlist .dirfield ) ;
      popnest () ;
      if ( savestack [saveptr + 0 ].cint < 255 ) 
      {
	r = getnode ( 6 ) ;
	mem [r ].hh.b0 = 4 ;
	mem [r ].hh.b1 = savestack [saveptr + 0 ].cint ;
	mem [r + 3 ].cint = mem [p + 3 ].cint + mem [p + 2 ].cint ;
	mem [r + 4 ].hh .v.LH = mem [p + 5 ].hh .v.RH ;
	mem [r + 4 ].hh .v.RH = q ;
	mem [r + 2 ].cint = d ;
	mem [r + 1 ].cint = f ;
	mem [r + 5 ].hh.b1 = ( mem [p ].hh.b1 ) ;
	if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist 
	.tailfield ].hh.b0 == 5 ) ) 
	{
	  mem [curlist .pnodefield ].hh .v.RH = r ;
	  mem [mem [curlist .pnodefield ].hh .v.RH ].hh .v.RH = curlist 
	  .tailfield ;
	  curlist .pnodefield = mem [curlist .pnodefield ].hh .v.RH ;
	} 
	else {
	    
	  mem [curlist .tailfield ].hh .v.RH = r ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
      } 
      else {
	  
	if ( ( mem [p ].hh.b1 ) != curlist .adjdirfield ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 1155 ) ;
	  } 
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 1156 ;
	  } 
	  error () ;
	  flushnodelist ( mem [p + 5 ].hh .v.RH ) ;
	} 
	else {
	    
	  r = getnode ( 2 ) ;
	  mem [r ].hh.b0 = 7 ;
	  mem [r + 1 ].cint = mem [p + 5 ].hh .v.RH ;
	  deleteglueref ( q ) ;
	  if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist 
	  .tailfield ].hh.b0 == 5 ) ) 
	  {
	    mem [curlist .pnodefield ].hh .v.RH = r ;
	    mem [mem [curlist .pnodefield ].hh .v.RH ].hh .v.RH = curlist 
	    .tailfield ;
	    curlist .pnodefield = mem [curlist .pnodefield ].hh .v.RH ;
	  } 
	  else {
	      
	    mem [curlist .tailfield ].hh .v.RH = r ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	} 
      } 
      deleteglueref ( mem [p + 7 ].hh .v.RH ) ;
      deleteglueref ( mem [p + 7 ].hh .v.LH ) ;
      freenode ( p , 10 ) ;
      if ( nestptr == 0 ) 
      buildpage () ;
    } 
    break ;
  case 8 : 
    {
      if ( ( curinput .locfield != -1073741823L ) || ( ( curinput .indexfield 
      != 6 ) && ( curinput .indexfield != 3 ) ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1069 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1070 ;
	  helpline [0 ]= 1071 ;
	} 
	error () ;
	do {
	    gettoken () ;
	} while ( ! ( curinput .locfield == -1073741823L ) ) ;
      } 
      endtokenlist () ;
      endgraf () ;
      unsave () ;
      outputactive = false ;
      insertpenalties = 0 ;
      if ( eqtb [25581 ].hh .v.RH != -1073741823L ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 1072 ) ;
	} 
	printesc ( 428 ) ;
	printint ( 255 ) ;
	{
	  helpptr = 3 ;
	  helpline [2 ]= 1073 ;
	  helpline [1 ]= 1074 ;
	  helpline [0 ]= 1075 ;
	} 
	boxerror ( 255 ) ;
      } 
      if ( curlist .tailfield != curlist .headfield ) 
      {
	mem [pagetail ].hh .v.RH = mem [curlist .headfield ].hh .v.RH ;
	pagetail = curlist .tailfield ;
      } 
      if ( mem [memtop - 2 ].hh .v.RH != -1073741823L ) 
      {
	if ( mem [memtop - 1 ].hh .v.RH == -1073741823L ) 
	nest [0 ].tailfield = pagetail ;
	mem [pagetail ].hh .v.RH = mem [memtop - 1 ].hh .v.RH ;
	mem [memtop - 1 ].hh .v.RH = mem [memtop - 2 ].hh .v.RH ;
	mem [memtop - 2 ].hh .v.RH = -1073741823L ;
	pagetail = memtop - 2 ;
      } 
      popnest () ;
      buildpage () ;
    } 
    break ;
  case 10 : 
    builddiscretionary () ;
    break ;
  case 6 : 
    {
      backinput () ;
      curtok = 536886426L ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 263 ) ;
	print ( 666 ) ;
      } 
      printesc ( 956 ) ;
      print ( 667 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 1197 ;
      } 
      inserror () ;
    } 
    break ;
  case 7 : 
    {
      endgraf () ;
      unsave () ;
      alignpeek () ;
    } 
    break ;
  case 12 : 
    {
      endgraf () ;
      unsave () ;
      saveptr = saveptr - 2 ;
      p = vpackage ( mem [curlist .headfield ].hh .v.RH , savestack [
      saveptr + 1 ].cint , savestack [saveptr + 0 ].cint , 1073741823L ) ;
      mem [p ].hh.b1 = abs ( curlist .dirfield ) ;
      popnest () ;
      if ( ( mem [p ].hh.b1 ) != abs ( curlist .dirfield ) ) 
      p = newdirnode ( p , abs ( curlist .dirfield ) ) ;
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = 31 ;
      mem [curlist .tailfield + 1 ].hh .v.RH = 2 ;
      mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    } 
    break ;
  case 13 : 
    buildchoices () ;
    break ;
  case 9 : 
    {
      unsave () ;
      decr ( saveptr ) ;
      mem [savestack [saveptr + 0 ].cint ].hh .v.RH = 4 ;
      p = finmlist ( -1073741823L ) ;
      mem [savestack [saveptr + 0 ].cint ].hh .v.LH = p ;
      if ( p != -1073741823L ) {
	  
	if ( mem [p ].hh .v.RH == -1073741823L ) {
	    
	  if ( mem [p ].hh.b0 == 18 ) 
	  {
	    if ( mem [p + 3 ].hh .v.RH == 0 ) {
		
	      if ( ( ( mem [p + 2 ].hh .v.RH == 0 ) && ( mem [p + 4 ].hh 
	      .v.LH == -1073741823L ) ) ) 
	      {
		mem [savestack [saveptr + 0 ].cint ].hh = mem [p + 1 ]
		.hh ;
		freenode ( p , 5 ) ;
	      } 
	    } 
	  } 
	  else if ( mem [p ].hh.b0 == 30 ) {
	      
	    if ( savestack [saveptr + 0 ].cint == curlist .tailfield + 1 ) {
		
	      if ( mem [curlist .tailfield ].hh.b0 == 18 ) 
	      {
		q = curlist .headfield ;
		while ( mem [q ].hh .v.RH != curlist .tailfield ) q = mem [
		q ].hh .v.RH ;
		mem [q ].hh .v.RH = p ;
		freenode ( curlist .tailfield , 5 ) ;
		curlist .tailfield = p ;
	      } 
	    } 
	  } 
	} 
      } 
    } 
    break ;
    default: 
    confusion ( 1105 ) ;
    break ;
  } 
} 
void 
maincontrol ( void ) 
{
  /* 60 21 70 80 130 131 133 141 150 90 91 92 95 100 101 110 111 112 120 10 
  */ maincontrol_regmem 
  integer t  ;
  KANJIcode cx  ;
  halfword kp  ;
  halfword gp, gq  ;
  scaled disp  ;
  boolean inskp  ;
  if ( eqtb [25067 ].hh .v.RH != -1073741823L ) 
  begintokenlist ( eqtb [25067 ].hh .v.RH , 12 ) ;
  lab60: getxtoken () ;
  lab21: if ( interrupt != 0 ) {
      
    if ( OKtointerrupt ) 
    {
      backinput () ;
      {
	if ( interrupt != 0 ) 
	pauseforinstructions () ;
      } 
      goto lab60 ;
    } 
  } 
	;
#ifdef TEXMF_DEBUG
  if ( panicking ) 
  checkmem ( false ) ;
#endif /* TEXMF_DEBUG */
  if ( eqtb [28498 ].cint > 0 ) 
  showcurcmdchr () ;
  inskp = false ;
  switch ( abs ( curlist .modefield ) + curcmd ) 
  {case 128 : 
  case 129 : 
    goto lab70 ;
    break ;
  case 133 : 
  case 134 : 
  case 135 : 
  case 136 : 
  case 191 : 
    goto lab130 ;
    break ;
  case 190 : 
    if ( checkecharrange ( curchr ) ) 
    goto lab70 ;
    else goto lab130 ;
    break ;
  case 137 : 
    {
      scancharnum () ;
      curchr = curval ;
      if ( checkecharrange ( curchr ) ) 
      goto lab70 ;
      else goto lab130 ;
    } 
    break ;
  case 171 : 
    {
      scancharnum () ;
      curchr = curval ;
      goto lab130 ;
    } 
    break ;
  case 187 : 
    {
      getxtoken () ;
      if ( ( curcmd == 11 ) || ( curcmd == 12 ) || ( ( curcmd >= 16 ) && ( 
      curcmd <= 19 ) ) || ( curcmd == 73 ) || ( curcmd == 20 ) || ( curcmd == 
      74 ) || ( curcmd == 54 ) ) 
      cancelboundary = true ;
      goto lab21 ;
    } 
    break ;
  case 127 : 
    if ( curlist .auxfield .hh .v.LH == 1000 ) 
    goto lab120 ;
    else appspace () ;
    break ;
  case 186 : 
  case 302 : 
    goto lab120 ;
    break ;
  case 1 : 
  case 117 : 
  case 233 : 
  case 11 : 
  case 243 : 
  case 303 : 
    ;
    break ;
  case 44 : 
  case 160 : 
  case 276 : 
    {
      do {
	  getxtoken () ;
      } while ( ! ( curcmd != 10 ) ) ;
      goto lab21 ;
    } 
    break ;
  case 15 : 
    if ( itsallover () ) 
    return ;
    break ;
  case 27 : 
  case 142 : 
  case 258 : 
  case 77 : 
  case 193 : 
  case 309 : 
  case 43 : 
  case 49 : 
  case 53 : 
  case 169 : 
  case 7 : 
  case 123 : 
  case 239 : 
    reportillegalcase () ;
    break ;
  case 8 : 
  case 124 : 
  case 9 : 
  case 125 : 
  case 22 : 
  case 138 : 
  case 76 : 
  case 192 : 
  case 56 : 
  case 172 : 
  case 16 : 
  case 132 : 
  case 54 : 
  case 170 : 
  case 58 : 
  case 174 : 
  case 72 : 
  case 188 : 
  case 59 : 
  case 175 : 
  case 60 : 
  case 176 : 
  case 62 : 
  case 178 : 
  case 61 : 
  case 177 : 
  case 35 : 
  case 151 : 
  case 57 : 
  case 173 : 
  case 33 : 
  case 149 : 
  case 51 : 
  case 167 : 
  case 242 : 
  case 246 : 
  case 247 : 
  case 264 : 
  case 261 : 
  case 270 : 
  case 273 : 
    insertdollarsign () ;
    break ;
  case 41 : 
  case 156 : 
  case 272 : 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = scanrulespec () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      if ( abs ( curlist .modefield ) == 1 ) 
      curlist .auxfield .cint = -65536000L ;
      else if ( abs ( curlist .modefield ) == 117 ) 
      curlist .auxfield .hh .v.LH = 1000 ;
    } 
    break ;
  case 32 : 
  case 147 : 
  case 263 : 
  case 265 : 
    appendglue () ;
    break ;
  case 34 : 
  case 150 : 
  case 266 : 
  case 267 : 
    appendkern () ;
    break ;
  case 2 : 
  case 118 : 
    newsavelevel ( 1 ) ;
    break ;
  case 67 : 
  case 183 : 
  case 299 : 
    newsavelevel ( 14 ) ;
    break ;
  case 68 : 
  case 184 : 
  case 300 : 
    if ( curgroup == 14 ) 
    unsave () ;
    else offsave () ;
    break ;
  case 3 : 
  case 119 : 
  case 235 : 
    handlerightbrace () ;
    break ;
  case 26 : 
  case 143 : 
  case 259 : 
    {
      t = curchr ;
      scandimen ( false , false , false ) ;
      if ( t == 0 ) 
      scanbox ( curval ) ;
      else scanbox ( - (integer) curval ) ;
    } 
    break ;
  case 36 : 
  case 152 : 
  case 268 : 
    scanbox ( 1073742237L + curchr ) ;
    break ;
  case 25 : 
  case 141 : 
  case 257 : 
    beginbox ( 0 ) ;
    break ;
  case 79 : 
  case 195 : 
  case 311 : 
    {
      if ( curgroup != 6 ) {
	  
	if ( curlist .headfield == curlist .tailfield ) 
	{
	  curlist .dirfield = curchr ;
	  if ( curlist .modefield == 1 ) 
	  pagedir = curchr ;
	} 
	else {
	    
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 263 ) ;
	    print ( 1127 ) ;
	  } 
	  printcmdchr ( curcmd , curchr ) ;
	  print ( 1128 ) ;
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 1129 ;
	    helpline [0 ]= 1130 ;
	  } 
	  error () ;
	} 
      } 
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 263 ) ;
	  print ( 726 ) ;
	} 
	printcmdchr ( curcmd , curchr ) ;
	print ( 1131 ) ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1132 ;
	  helpline [0 ]= 1133 ;
	} 
	error () ;
      } 
    } 
    break ;
  case 48 : 
    newgraf ( curchr > 0 ) ;
    break ;
  case 12 : 
  case 13 : 
  case 21 : 
  case 74 : 
  case 55 : 
  case 75 : 
  case 4 : 
  case 28 : 
  case 40 : 
  case 50 : 
  case 52 : 
  case 31 : 
  case 38 : 
  case 17 : 
  case 18 : 
  case 19 : 
  case 20 : 
  case 70 : 
  case 71 : 
    {
      backinput () ;
      newgraf ( true ) ;
    } 
    break ;
  case 164 : 
  case 280 : 
    indentinhmode () ;
    break ;
  case 14 : 
    {
      normalparagraph () ;
      if ( curlist .modefield > 0 ) 
      buildpage () ;
    } 
    break ;
  case 130 : 
    {
      if ( alignstate < 0 ) 
      offsave () ;
      endgraf () ;
      if ( curlist .modefield == 1 ) 
      buildpage () ;
    } 
    break ;
  case 131 : 
  case 148 : 
  case 157 : 
  case 145 : 
  case 153 : 
    headforvmode () ;
    break ;
  case 42 : 
  case 158 : 
  case 274 : 
  case 159 : 
  case 275 : 
    begininsertoradjust () ;
    break ;
  case 23 : 
  case 139 : 
  case 255 : 
    makemark () ;
    break ;
  case 47 : 
  case 163 : 
  case 279 : 
    appendpenalty () ;
    break ;
  case 30 : 
  case 146 : 
  case 262 : 
    deletelast () ;
    break ;
  case 29 : 
  case 144 : 
  case 260 : 
    unpackage () ;
    break ;
  case 165 : 
    appenditaliccorrection () ;
    break ;
  case 281 : 
    {
      mem [curlist .tailfield ].hh .v.RH = newkern ( 0 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    break ;
  case 168 : 
  case 284 : 
    appenddiscretionary () ;
    break ;
  case 166 : 
    makeaccent () ;
    break ;
  case 6 : 
  case 122 : 
  case 238 : 
  case 5 : 
  case 121 : 
  case 237 : 
    alignerror () ;
    break ;
  case 39 : 
  case 155 : 
  case 271 : 
    noalignerror () ;
    break ;
  case 69 : 
  case 185 : 
  case 301 : 
    omiterror () ;
    break ;
  case 37 : 
  case 154 : 
    initalign () ;
    break ;
  case 269 : 
    if ( privileged () ) {
	
      if ( curgroup == 15 ) 
      initalign () ;
      else offsave () ;
    } 
    break ;
  case 10 : 
  case 126 : 
    doendv () ;
    break ;
  case 73 : 
  case 189 : 
  case 305 : 
    cserror () ;
    break ;
  case 120 : 
    initmath () ;
    break ;
  case 285 : 
    if ( privileged () ) {
	
      if ( curgroup == 15 ) 
      starteqno () ;
      else offsave () ;
    } 
    break ;
  case 234 : 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      backinput () ;
      scanmath ( curlist .tailfield + 1 , curlist .tailfield + 4 ) ;
    } 
    break ;
  case 244 : 
  case 245 : 
  case 306 : 
    if ( checkecharrange ( curchr ) ) {
	
      if ( curchr < 128 ) 
      setmathchar ( eqtb [27950 + curchr ].hh .v.RH ) ;
      else setmathchar ( curchr ) ;
    } 
    else setmathkchar ( curchr ) ;
    break ;
  case 249 : 
  case 250 : 
  case 251 : 
  case 252 : 
    {
      cx = curchr ;
      setmathkchar ( cx ) ;
    } 
    break ;
  case 253 : 
    {
      scancharnum () ;
      curchr = curval ;
      if ( checkecharrange ( curchr ) ) {
	  
	if ( curchr < 128 ) 
	setmathchar ( eqtb [27950 + curchr ].hh .v.RH ) ;
	else setmathchar ( curchr ) ;
      } 
      else setmathkchar ( curchr ) ;
    } 
    break ;
  case 307 : 
    setmathkchar ( curchr ) ;
    break ;
  case 287 : 
    {
      scancharnum () ;
      curchr = curval ;
      setmathkchar ( curchr ) ;
    } 
    break ;
  case 254 : 
    {
      scanfifteenbitint () ;
      setmathchar ( curval ) ;
    } 
    break ;
  case 308 : 
    setmathchar ( curchr ) ;
    break ;
  case 248 : 
    {
      scantwentysevenbitint () ;
      setmathchar ( curval / 4096 ) ;
    } 
    break ;
  case 288 : 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = curchr ;
      scanmath ( curlist .tailfield + 1 , curlist .tailfield + 4 ) ;
    } 
    break ;
  case 289 : 
    mathlimitswitch () ;
    break ;
  case 304 : 
    mathradical () ;
    break ;
  case 282 : 
  case 283 : 
    mathac () ;
    break ;
  case 294 : 
    {
      scanspec ( 12 , false ) ;
      normalparagraph () ;
      inhibitglueflag = false ;
      pushnest () ;
      curlist .modefield = -1 ;
      curlist .auxfield .cint = -65536000L ;
      if ( ( insertsrcspecialeveryvbox ) ) 
      insertsrcspecial () ;
      if ( eqtb [25066 ].hh .v.RH != -1073741823L ) 
      begintokenlist ( eqtb [25066 ].hh .v.RH , 11 ) ;
    } 
    break ;
  case 291 : 
    {
      mem [curlist .tailfield ].hh .v.RH = newstyle ( curchr ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    break ;
  case 293 : 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = newglue ( membot ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b1 = 98 ;
    } 
    break ;
  case 292 : 
    appendchoices () ;
    break ;
  case 241 : 
  case 240 : 
    subsup () ;
    break ;
  case 290 : 
    mathfraction () ;
    break ;
  case 286 : 
    mathleftright () ;
    break ;
  case 236 : 
    if ( curgroup == 15 ) 
    aftermath () ;
    else offsave () ;
    break ;
  case 88 : 
  case 204 : 
  case 320 : 
  case 89 : 
  case 205 : 
  case 321 : 
  case 115 : 
  case 231 : 
  case 347 : 
  case 116 : 
  case 232 : 
  case 348 : 
  case 90 : 
  case 206 : 
  case 322 : 
  case 80 : 
  case 196 : 
  case 312 : 
  case 81 : 
  case 197 : 
  case 313 : 
  case 82 : 
  case 198 : 
  case 314 : 
  case 101 : 
  case 217 : 
  case 333 : 
  case 102 : 
  case 218 : 
  case 334 : 
  case 83 : 
  case 199 : 
  case 315 : 
  case 84 : 
  case 200 : 
  case 316 : 
  case 85 : 
  case 201 : 
  case 317 : 
  case 86 : 
  case 202 : 
  case 318 : 
  case 87 : 
  case 203 : 
  case 319 : 
  case 91 : 
  case 207 : 
  case 323 : 
  case 92 : 
  case 208 : 
  case 324 : 
  case 93 : 
  case 209 : 
  case 325 : 
  case 94 : 
  case 210 : 
  case 326 : 
  case 95 : 
  case 211 : 
  case 327 : 
  case 96 : 
  case 212 : 
  case 328 : 
  case 97 : 
  case 213 : 
  case 329 : 
  case 98 : 
  case 214 : 
  case 330 : 
  case 99 : 
  case 215 : 
  case 331 : 
  case 100 : 
  case 216 : 
  case 332 : 
  case 103 : 
  case 219 : 
  case 335 : 
  case 104 : 
  case 220 : 
  case 336 : 
  case 105 : 
  case 221 : 
  case 337 : 
  case 106 : 
  case 222 : 
  case 338 : 
  case 107 : 
  case 223 : 
  case 339 : 
  case 108 : 
  case 224 : 
  case 340 : 
  case 109 : 
  case 225 : 
  case 341 : 
  case 110 : 
  case 226 : 
  case 342 : 
  case 111 : 
  case 227 : 
  case 343 : 
  case 112 : 
  case 228 : 
  case 344 : 
  case 113 : 
  case 229 : 
  case 345 : 
  case 114 : 
  case 230 : 
  case 346 : 
    prefixedcommand () ;
    break ;
  case 45 : 
  case 161 : 
  case 277 : 
    {
      gettoken () ;
      aftertoken = curtok ;
    } 
    break ;
  case 46 : 
  case 162 : 
  case 278 : 
    {
      gettoken () ;
      saveforafter ( curtok ) ;
    } 
    break ;
  case 66 : 
  case 182 : 
  case 298 : 
    openorclosein () ;
    break ;
  case 64 : 
  case 180 : 
  case 296 : 
    issuemessage () ;
    break ;
  case 63 : 
  case 179 : 
  case 295 : 
    shiftcase () ;
    break ;
  case 24 : 
  case 140 : 
  case 256 : 
    showwhatever () ;
    break ;
  case 78 : 
  case 194 : 
  case 310 : 
    inhibitglueflag = true ;
    break ;
  case 65 : 
  case 181 : 
  case 297 : 
    doextension () ;
    break ;
  } 
  goto lab60 ;
  lab130: if ( ( curlist .tailfield >= himemmin ) ) 
  {
    cx = mem [curlist .tailfield ].hh.b1 ;
    {
      kp = getkinsokupos ( cx , 1 ) ;
      if ( kp != 1000 ) 
      {
	if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	{
	  {
	    mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29317 + 
	    kp ].cint ) ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  mem [curlist .tailfield ].hh.b1 = 2 ;
	} 
      } 
    } 
  } 
  else if ( mem [curlist .tailfield ].hh.b0 == 8 ) 
  {
    cx = mem [curlist .tailfield + 1 ].hh.b1 ;
    {
      kp = getkinsokupos ( cx , 1 ) ;
      if ( kp != 1000 ) 
      {
	if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	{
	  {
	    mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29317 + 
	    kp ].cint ) ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  mem [curlist .tailfield ].hh.b1 = 2 ;
	} 
      } 
    } 
  } 
  if ( curlist .dirfield == 3 ) 
  {
    if ( fontdir [mainf ]== 3 ) 
    disp = 0 ;
    else if ( fontdir [mainf ]== 4 ) 
    disp = eqtb [29059 ].cint - eqtb [29060 ].cint ;
    else disp = eqtb [29059 ].cint ;
    mainf = eqtb [25632 ].hh .v.RH ;
  } 
  else {
      
    if ( fontdir [mainf ]== 4 ) 
    disp = 0 ;
    else if ( fontdir [mainf ]== 3 ) 
    disp = eqtb [29060 ].cint - eqtb [29059 ].cint ;
    else disp = eqtb [29060 ].cint ;
    mainf = eqtb [25631 ].hh .v.RH ;
  } 
  if ( disp != 0 ) 
  {
    if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield ]
    .hh.b0 == 5 ) ) 
    {
      mem [curlist .tailfield + 1 ].cint = 0 ;
    } 
    else {
	
      curlist .pnodefield = curlist .tailfield ;
      {
	mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = 5 ;
      mem [curlist .tailfield + 1 ].cint = 0 ;
      curlist .pdispfield = disp ;
    } 
  } 
  inskp = false ;
  ligaturepresent = false ;
  curl = getjfmpos ( curchr , mainf ) ;
  maini = fontinfo [charbase [mainf ]+ 0 ].qqqq ;
  goto lab133 ;
  lab131: curlist .auxfield .hh .v.LH = 1000 ;
  if ( mainf != 0 ) 
  {
    {
      mainp = avail ;
      if ( mainp == -1073741823L ) 
      mainp = getavail () ;
      else {
	  
	avail = mem [mainp ].hh .v.RH ;
	mem [mainp ].hh .v.RH = -1073741823L ;
	;
#ifdef STAT
	incr ( dynused ) ;
#endif /* STAT */
      } 
    } 
    mem [mainp ].hh.b0 = mainf ;
    mem [mainp ].hh.b1 = curl ;
    mem [curlist .tailfield ].hh .v.RH = mainp ;
    curlist .tailfield = mainp ;
    curlist .lastjchrfield = curlist .tailfield ;
    {
      mainp = avail ;
      if ( mainp == -1073741823L ) 
      mainp = getavail () ;
      else {
	  
	avail = mem [mainp ].hh .v.RH ;
	mem [mainp ].hh .v.RH = -1073741823L ;
	;
#ifdef STAT
	incr ( dynused ) ;
#endif /* STAT */
      } 
    } 
    mem [mainp ].hh .v.LH = curchr + curcmd * 16777216L ;
    mem [curlist .tailfield ].hh .v.RH = mainp ;
    curlist .tailfield = mainp ;
    cx = curchr ;
    {
      kp = getkinsokupos ( cx , 1 ) ;
      if ( kp != 1000 ) 
      {
	if ( eqtb [26916 + kp ].hh.b0 == 1 ) 
	{
	  if ( ! ( curq >= himemmin ) && ( mem [curq ].hh.b0 == 14 ) ) 
	  mem [curq + 1 ].cint = mem [curq + 1 ].cint + eqtb [29317 + kp 
	  ].cint ;
	  else {
	      
	    mainp = mem [curq ].hh .v.RH ;
	    mem [curq ].hh .v.RH = newpenalty ( eqtb [29317 + kp ].cint ) 
	    ;
	    mem [mem [curq ].hh .v.RH ].hh.b1 = 2 ;
	    mem [mem [curq ].hh .v.RH ].hh .v.RH = mainp ;
	  } 
	} 
	else if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	{
	  {
	    mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29317 + 
	    kp ].cint ) ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  mem [curlist .tailfield ].hh.b1 = 2 ;
	} 
      } 
    } 
  } 
  inskp = false ;
  lab150: getnext () ;
  maini = fontinfo [charbase [mainf ]+ curl ].qqqq ;
  switch ( curcmd ) 
  {case 16 : 
  case 17 : 
  case 18 : 
  case 19 : 
    {
      curl = getjfmpos ( curchr , mainf ) ;
      goto lab133 ;
    } 
    break ;
  case 11 : 
  case 12 : 
    {
      inskp = true ;
      curl = 0 ;
      goto lab133 ;
    } 
    break ;
  } 
  xtoken () ;
  switch ( curcmd ) 
  {case 16 : 
  case 17 : 
  case 18 : 
  case 19 : 
    curl = getjfmpos ( curchr , mainf ) ;
    break ;
  case 11 : 
  case 12 : 
    {
      inskp = true ;
      curl = 0 ;
    } 
    break ;
  case 73 : 
    {
      if ( checkecharrange ( curchr ) ) 
      {
	inskp = true ;
	curl = 0 ;
      } 
      else curl = getjfmpos ( curchr , mainf ) ;
    } 
    break ;
  case 20 : 
    {
      scancharnum () ;
      curchr = curval ;
      if ( checkecharrange ( curchr ) ) 
      {
	inskp = true ;
	curl = 0 ;
      } 
      else curl = getjfmpos ( curchr , mainf ) ;
    } 
    break ;
  case 74 : 
    {
      curl = getjfmpos ( curchr , mainf ) ;
    } 
    break ;
  case 54 : 
    {
      scancharnum () ;
      curchr = curval ;
      curl = getjfmpos ( curchr , mainf ) ;
    } 
    break ;
  case 77 : 
    {
      inhibitglueflag = true ;
      goto lab150 ;
    } 
    break ;
    default: 
    {
      inskp = 1073741823L ;
      curl = 0 ;
      curr = 256 ;
      ligstack = -1073741823L ;
    } 
    break ;
  } 
  lab133: if ( inskp == true ) 
  {
    kp = getkinsokupos ( curchr , 1 ) ;
    if ( kp != 1000 ) 
    {
      if ( eqtb [26916 + kp ].hh.b0 == 1 ) {
	  
	if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist 
	.tailfield ].hh.b0 == 14 ) ) 
	mem [curlist .tailfield + 1 ].cint = mem [curlist .tailfield + 1 ]
	.cint + eqtb [29317 + kp ].cint ;
	else {
	    
	  {
	    mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29317 + 
	    kp ].cint ) ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  mem [curlist .tailfield ].hh.b1 = 2 ;
	} 
      } 
    } 
  } 
  if ( mainf != 0 ) 
  {
    curq = curlist .tailfield ;
    if ( inhibitglueflag != true ) 
    {
      if ( ( ( maini .b2 ) % 4 ) == 1 ) 
      {
	maink = ligkernbase [mainf ]+ maini .b3 ;
	do {
	    mainj = fontinfo [maink ].qqqq ;
	  if ( mainj .b1 == curl ) 
	  {
	    if ( mainj .b2 < 128 ) 
	    {
	      gp = fontglue [mainf ];
	      curr = mainj .b3 ;
	      if ( gp != -1073741823L ) 
	      {
		while ( ( ( mem [gp ].hh.b0 != curr ) && ( mem [gp ].hh 
		.v.RH != -1073741823L ) ) ) gp = mem [gp ].hh .v.RH ;
		gq = mem [gp + 1 ].hh .v.LH ;
	      } 
	      else {
		  
		gp = getnode ( 2 ) ;
		fontglue [mainf ]= gp ;
		gq = -1073741823L ;
	      } 
	      if ( gq == -1073741823L ) 
	      {
		mem [gp ].hh.b0 = curr ;
		gq = newspec ( membot ) ;
		mem [gp + 1 ].hh .v.LH = gq ;
		maink = extenbase [mainf ]+ ( curr ) * 3 ;
		mem [gq + 1 ].cint = fontinfo [maink ].cint ;
		mem [gq + 2 ].cint = fontinfo [maink + 1 ].cint ;
		mem [gq + 3 ].cint = fontinfo [maink + 2 ].cint ;
		incr ( mem [gq ].hh .v.RH ) ;
		mem [gp ].hh .v.RH = getnode ( 2 ) ;
		gp = mem [gp ].hh .v.RH ;
		mem [gp + 1 ].hh .v.LH = -1073741823L ;
		mem [gp ].hh .v.RH = -1073741823L ;
	      } 
	      {
		mem [curlist .tailfield ].hh .v.RH = newglue ( gq ) ;
		curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	      } 
	      mem [curlist .tailfield ].hh.b1 = 21 ;
	      goto lab141 ;
	    } 
	    else {
		
	      {
		mem [curlist .tailfield ].hh .v.RH = newkern ( fontinfo [
		kernbase [mainf ]+ 256 * mainj .b2 + mainj .b3 ].cint ) ;
		curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	      } 
	      goto lab141 ;
	    } 
	  } 
	  incr ( maink ) ;
	} while ( ! ( mainj .b0 >= 128 ) ) ;
      } 
    } 
    lab141: inhibitglueflag = false ;
  } 
  else inhibitglueflag = false ;
  if ( inskp == false ) 
  {
    goto lab131 ;
  } 
  else if ( inskp == true ) 
  {
    inskp = false ;
    goto lab70 ;
  } 
  else {
      
    goto lab21 ;
  } 
  lab70: inhibitglueflag = false ;
  if ( ( ( curlist .headfield == curlist .tailfield ) && ( curlist .modefield 
  > 0 ) ) ) 
  {
    if ( ( insertsrcspecialauto ) ) 
    appendsrcspecial () ;
  } 
  mains = eqtb [27694 + curchr ].hh .v.RH ;
  if ( mains == 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else if ( mains < 1000 ) 
  {
    if ( mains > 0 ) 
    curlist .auxfield .hh .v.LH = mains ;
  } 
  else if ( curlist .auxfield .hh .v.LH < 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else curlist .auxfield .hh .v.LH = mains ;
  if ( curlist .dirfield == 3 ) 
  disp = eqtb [29059 ].cint ;
  else disp = eqtb [29060 ].cint ;
  {
    if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield ]
    .hh.b0 == 5 ) ) 
    {
      if ( curlist .pdispfield == disp ) 
      {
	freenode ( curlist .tailfield , 2 ) ;
	curlist .tailfield = curlist .pnodefield ;
	mem [curlist .tailfield ].hh .v.RH = -1073741823L ;
      } 
      else mem [curlist .tailfield + 1 ].cint = disp ;
    } 
    else if ( disp != 0 ) 
    {
      curlist .pnodefield = curlist .tailfield ;
      {
	mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = 5 ;
      mem [curlist .tailfield + 1 ].cint = disp ;
      curlist .pdispfield = disp ;
    } 
  } 
  mainf = eqtb [25582 ].hh .v.RH ;
  bchar = fontbchar [mainf ];
  falsebchar = fontfalsebchar [mainf ];
  if ( curlist .modefield > 0 ) {
      
    if ( eqtb [28513 ].cint != curlist .auxfield .hh .v.RH ) 
    fixlanguage () ;
  } 
  {
    ligstack = avail ;
    if ( ligstack == -1073741823L ) 
    ligstack = getavail () ;
    else {
	
      avail = mem [ligstack ].hh .v.RH ;
      mem [ligstack ].hh .v.RH = -1073741823L ;
	;
#ifdef STAT
      incr ( dynused ) ;
#endif /* STAT */
    } 
  } 
  mem [ligstack ].hh.b0 = mainf ;
  curl = curchr ;
  mem [ligstack ].hh.b1 = curl ;
  curq = curlist .tailfield ;
  if ( cancelboundary ) 
  {
    cancelboundary = false ;
    maink = 0 ;
  } 
  else maink = bcharlabel [mainf ];
  if ( maink == 0 ) 
  goto lab92 ;
  curr = curl ;
  curl = 256 ;
  goto lab111 ;
  lab80: if ( curl < 256 ) 
  {
    if ( mem [curq ].hh .v.RH > -1073741823L ) {
	
      if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
      insdisc = true ;
    } 
    if ( ligaturepresent ) 
    {
      mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
      if ( lfthit ) 
      {
	mem [mainp ].hh.b1 = 2 ;
	lfthit = false ;
      } 
      if ( rthit ) {
	  
	if ( ligstack == -1073741823L ) 
	{
	  incr ( mem [mainp ].hh.b1 ) ;
	  rthit = false ;
	} 
      } 
      mem [curq ].hh .v.RH = mainp ;
      curlist .tailfield = mainp ;
      ligaturepresent = false ;
    } 
    if ( insdisc ) 
    {
      insdisc = false ;
      if ( curlist .modefield > 0 ) 
      {
	mem [curlist .tailfield ].hh .v.RH = newdisc () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
    } 
  } 
  lab90: if ( ligstack == -1073741823L ) 
  {
    if ( disp != 0 ) 
    {
      if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield 
      ].hh.b0 == 5 ) ) 
      {
	mem [curlist .tailfield + 1 ].cint = 0 ;
      } 
      else {
	  
	curlist .pnodefield = curlist .tailfield ;
	{
	  mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b0 = 5 ;
	mem [curlist .tailfield + 1 ].cint = 0 ;
	curlist .pdispfield = disp ;
      } 
    } 
    goto lab21 ;
  } 
  curq = curlist .tailfield ;
  curl = mem [ligstack ].hh.b1 ;
  lab91: if ( ! ( ligstack >= himemmin ) ) 
  goto lab95 ;
  lab92: if ( ( effectivechar ( false , mainf , curchr ) > fontec [mainf ]) 
  || ( effectivechar ( false , mainf , curchr ) < fontbc [mainf ]) ) 
  {
    charwarning ( mainf , curchr ) ;
    {
      mem [ligstack ].hh .v.RH = avail ;
      avail = ligstack ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } 
    goto lab60 ;
  } 
  maini = effectivecharinfo ( mainf , curl ) ;
  if ( ! ( maini .b0 > 0 ) ) 
  {
    charwarning ( mainf , curchr ) ;
    {
      mem [ligstack ].hh .v.RH = avail ;
      avail = ligstack ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } 
    goto lab60 ;
  } 
  mem [curlist .tailfield ].hh .v.RH = ligstack ;
  curlist .tailfield = ligstack ;
  lab100: getnext () ;
  if ( curcmd == 11 ) 
  goto lab101 ;
  if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
  {
    bchar = 256 ;
    curr = bchar ;
    ligstack = -1073741823L ;
    if ( ligaturepresent ) 
    {
      mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
      if ( lfthit ) 
      {
	mem [mainp ].hh.b1 = 2 ;
	lfthit = false ;
      } 
      if ( rthit ) {
	  
	if ( ligstack == -1073741823L ) 
	{
	  incr ( mem [mainp ].hh.b1 ) ;
	  rthit = false ;
	} 
      } 
      mem [curq ].hh .v.RH = mainp ;
      curlist .tailfield = mainp ;
      ligaturepresent = false ;
    } 
    if ( inskp == true ) 
    {
      cx = curl ;
      {
	kp = getkinsokupos ( cx , 1 ) ;
	if ( kp != 1000 ) 
	{
	  if ( eqtb [26916 + kp ].hh.b0 == 1 ) 
	  {
	    if ( ! ( curq >= himemmin ) && ( mem [curq ].hh.b0 == 14 ) ) 
	    mem [curq + 1 ].cint = mem [curq + 1 ].cint + eqtb [29317 + 
	    kp ].cint ;
	    else {
		
	      mainp = mem [curq ].hh .v.RH ;
	      mem [curq ].hh .v.RH = newpenalty ( eqtb [29317 + kp ].cint 
	      ) ;
	      mem [mem [curq ].hh .v.RH ].hh.b1 = 2 ;
	      mem [mem [curq ].hh .v.RH ].hh .v.RH = mainp ;
	    } 
	  } 
	  else if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	  {
	    {
	      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29317 
	      + kp ].cint ) ;
	      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	    } 
	    mem [curlist .tailfield ].hh.b1 = 2 ;
	  } 
	} 
      } 
    } 
    inskp = false ;
    goto lab130 ;
  } 
  if ( curcmd == 12 ) 
  goto lab101 ;
  if ( curcmd == 73 ) 
  {
    if ( checkecharrange ( curchr ) ) 
    goto lab101 ;
    else {
	
      bchar = 256 ;
      curr = bchar ;
      ligstack = -1073741823L ;
      if ( ligaturepresent ) 
      {
	mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	if ( lfthit ) 
	{
	  mem [mainp ].hh.b1 = 2 ;
	  lfthit = false ;
	} 
	if ( rthit ) {
	    
	  if ( ligstack == -1073741823L ) 
	  {
	    incr ( mem [mainp ].hh.b1 ) ;
	    rthit = false ;
	  } 
	} 
	mem [curq ].hh .v.RH = mainp ;
	curlist .tailfield = mainp ;
	ligaturepresent = false ;
      } 
      if ( inskp == true ) 
      {
	cx = curl ;
	{
	  kp = getkinsokupos ( cx , 1 ) ;
	  if ( kp != 1000 ) 
	  {
	    if ( eqtb [26916 + kp ].hh.b0 == 1 ) 
	    {
	      if ( ! ( curq >= himemmin ) && ( mem [curq ].hh.b0 == 14 ) ) 
	      mem [curq + 1 ].cint = mem [curq + 1 ].cint + eqtb [29317 + 
	      kp ].cint ;
	      else {
		  
		mainp = mem [curq ].hh .v.RH ;
		mem [curq ].hh .v.RH = newpenalty ( eqtb [29317 + kp ]
		.cint ) ;
		mem [mem [curq ].hh .v.RH ].hh.b1 = 2 ;
		mem [mem [curq ].hh .v.RH ].hh .v.RH = mainp ;
	      } 
	    } 
	    else if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	    {
	      {
		mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [
		29317 + kp ].cint ) ;
		curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	      } 
	      mem [curlist .tailfield ].hh.b1 = 2 ;
	    } 
	  } 
	} 
      } 
      inskp = false ;
      goto lab130 ;
    } 
  } 
  if ( curcmd == 74 ) 
  {
    bchar = 256 ;
    curr = bchar ;
    ligstack = -1073741823L ;
    if ( ligaturepresent ) 
    {
      mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
      if ( lfthit ) 
      {
	mem [mainp ].hh.b1 = 2 ;
	lfthit = false ;
      } 
      if ( rthit ) {
	  
	if ( ligstack == -1073741823L ) 
	{
	  incr ( mem [mainp ].hh.b1 ) ;
	  rthit = false ;
	} 
      } 
      mem [curq ].hh .v.RH = mainp ;
      curlist .tailfield = mainp ;
      ligaturepresent = false ;
    } 
    if ( inskp == true ) 
    {
      cx = curl ;
      {
	kp = getkinsokupos ( cx , 1 ) ;
	if ( kp != 1000 ) 
	{
	  if ( eqtb [26916 + kp ].hh.b0 == 1 ) 
	  {
	    if ( ! ( curq >= himemmin ) && ( mem [curq ].hh.b0 == 14 ) ) 
	    mem [curq + 1 ].cint = mem [curq + 1 ].cint + eqtb [29317 + 
	    kp ].cint ;
	    else {
		
	      mainp = mem [curq ].hh .v.RH ;
	      mem [curq ].hh .v.RH = newpenalty ( eqtb [29317 + kp ].cint 
	      ) ;
	      mem [mem [curq ].hh .v.RH ].hh.b1 = 2 ;
	      mem [mem [curq ].hh .v.RH ].hh .v.RH = mainp ;
	    } 
	  } 
	  else if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	  {
	    {
	      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29317 
	      + kp ].cint ) ;
	      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	    } 
	    mem [curlist .tailfield ].hh.b1 = 2 ;
	  } 
	} 
      } 
    } 
    inskp = false ;
    goto lab130 ;
  } 
  xtoken () ;
  if ( curcmd == 11 ) 
  goto lab101 ;
  if ( ( curcmd >= 16 ) && ( curcmd <= 19 ) ) 
  {
    bchar = 256 ;
    curr = bchar ;
    ligstack = -1073741823L ;
    if ( ligaturepresent ) 
    {
      mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
      if ( lfthit ) 
      {
	mem [mainp ].hh.b1 = 2 ;
	lfthit = false ;
      } 
      if ( rthit ) {
	  
	if ( ligstack == -1073741823L ) 
	{
	  incr ( mem [mainp ].hh.b1 ) ;
	  rthit = false ;
	} 
      } 
      mem [curq ].hh .v.RH = mainp ;
      curlist .tailfield = mainp ;
      ligaturepresent = false ;
    } 
    if ( inskp == true ) 
    {
      cx = curl ;
      {
	kp = getkinsokupos ( cx , 1 ) ;
	if ( kp != 1000 ) 
	{
	  if ( eqtb [26916 + kp ].hh.b0 == 1 ) 
	  {
	    if ( ! ( curq >= himemmin ) && ( mem [curq ].hh.b0 == 14 ) ) 
	    mem [curq + 1 ].cint = mem [curq + 1 ].cint + eqtb [29317 + 
	    kp ].cint ;
	    else {
		
	      mainp = mem [curq ].hh .v.RH ;
	      mem [curq ].hh .v.RH = newpenalty ( eqtb [29317 + kp ].cint 
	      ) ;
	      mem [mem [curq ].hh .v.RH ].hh.b1 = 2 ;
	      mem [mem [curq ].hh .v.RH ].hh .v.RH = mainp ;
	    } 
	  } 
	  else if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	  {
	    {
	      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29317 
	      + kp ].cint ) ;
	      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	    } 
	    mem [curlist .tailfield ].hh.b1 = 2 ;
	  } 
	} 
      } 
    } 
    inskp = false ;
    goto lab130 ;
  } 
  if ( curcmd == 12 ) 
  goto lab101 ;
  if ( curcmd == 73 ) 
  {
    if ( checkecharrange ( curchr ) ) 
    goto lab101 ;
    else {
	
      bchar = 256 ;
      curr = bchar ;
      ligstack = -1073741823L ;
      if ( ligaturepresent ) 
      {
	mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	if ( lfthit ) 
	{
	  mem [mainp ].hh.b1 = 2 ;
	  lfthit = false ;
	} 
	if ( rthit ) {
	    
	  if ( ligstack == -1073741823L ) 
	  {
	    incr ( mem [mainp ].hh.b1 ) ;
	    rthit = false ;
	  } 
	} 
	mem [curq ].hh .v.RH = mainp ;
	curlist .tailfield = mainp ;
	ligaturepresent = false ;
      } 
      if ( inskp == true ) 
      {
	cx = curl ;
	{
	  kp = getkinsokupos ( cx , 1 ) ;
	  if ( kp != 1000 ) 
	  {
	    if ( eqtb [26916 + kp ].hh.b0 == 1 ) 
	    {
	      if ( ! ( curq >= himemmin ) && ( mem [curq ].hh.b0 == 14 ) ) 
	      mem [curq + 1 ].cint = mem [curq + 1 ].cint + eqtb [29317 + 
	      kp ].cint ;
	      else {
		  
		mainp = mem [curq ].hh .v.RH ;
		mem [curq ].hh .v.RH = newpenalty ( eqtb [29317 + kp ]
		.cint ) ;
		mem [mem [curq ].hh .v.RH ].hh.b1 = 2 ;
		mem [mem [curq ].hh .v.RH ].hh .v.RH = mainp ;
	      } 
	    } 
	    else if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	    {
	      {
		mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [
		29317 + kp ].cint ) ;
		curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	      } 
	      mem [curlist .tailfield ].hh.b1 = 2 ;
	    } 
	  } 
	} 
      } 
      inskp = false ;
      goto lab130 ;
    } 
  } 
  if ( curcmd == 20 ) 
  {
    scancharnum () ;
    curchr = curval ;
    if ( checkecharrange ( curchr ) ) 
    goto lab101 ;
    else {
	
      bchar = 256 ;
      curr = bchar ;
      ligstack = -1073741823L ;
      if ( ligaturepresent ) 
      {
	mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	if ( lfthit ) 
	{
	  mem [mainp ].hh.b1 = 2 ;
	  lfthit = false ;
	} 
	if ( rthit ) {
	    
	  if ( ligstack == -1073741823L ) 
	  {
	    incr ( mem [mainp ].hh.b1 ) ;
	    rthit = false ;
	  } 
	} 
	mem [curq ].hh .v.RH = mainp ;
	curlist .tailfield = mainp ;
	ligaturepresent = false ;
      } 
      if ( inskp == true ) 
      {
	cx = curl ;
	{
	  kp = getkinsokupos ( cx , 1 ) ;
	  if ( kp != 1000 ) 
	  {
	    if ( eqtb [26916 + kp ].hh.b0 == 1 ) 
	    {
	      if ( ! ( curq >= himemmin ) && ( mem [curq ].hh.b0 == 14 ) ) 
	      mem [curq + 1 ].cint = mem [curq + 1 ].cint + eqtb [29317 + 
	      kp ].cint ;
	      else {
		  
		mainp = mem [curq ].hh .v.RH ;
		mem [curq ].hh .v.RH = newpenalty ( eqtb [29317 + kp ]
		.cint ) ;
		mem [mem [curq ].hh .v.RH ].hh.b1 = 2 ;
		mem [mem [curq ].hh .v.RH ].hh .v.RH = mainp ;
	      } 
	    } 
	    else if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	    {
	      {
		mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [
		29317 + kp ].cint ) ;
		curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	      } 
	      mem [curlist .tailfield ].hh.b1 = 2 ;
	    } 
	  } 
	} 
      } 
      inskp = false ;
      goto lab130 ;
    } 
  } 
  if ( curcmd == 54 ) 
  {
    scancharnum () ;
    curchr = curval ;
    {
      bchar = 256 ;
      curr = bchar ;
      ligstack = -1073741823L ;
      if ( ligaturepresent ) 
      {
	mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	if ( lfthit ) 
	{
	  mem [mainp ].hh.b1 = 2 ;
	  lfthit = false ;
	} 
	if ( rthit ) {
	    
	  if ( ligstack == -1073741823L ) 
	  {
	    incr ( mem [mainp ].hh.b1 ) ;
	    rthit = false ;
	  } 
	} 
	mem [curq ].hh .v.RH = mainp ;
	curlist .tailfield = mainp ;
	ligaturepresent = false ;
      } 
      if ( inskp == true ) 
      {
	cx = curl ;
	{
	  kp = getkinsokupos ( cx , 1 ) ;
	  if ( kp != 1000 ) 
	  {
	    if ( eqtb [26916 + kp ].hh.b0 == 1 ) 
	    {
	      if ( ! ( curq >= himemmin ) && ( mem [curq ].hh.b0 == 14 ) ) 
	      mem [curq + 1 ].cint = mem [curq + 1 ].cint + eqtb [29317 + 
	      kp ].cint ;
	      else {
		  
		mainp = mem [curq ].hh .v.RH ;
		mem [curq ].hh .v.RH = newpenalty ( eqtb [29317 + kp ]
		.cint ) ;
		mem [mem [curq ].hh .v.RH ].hh.b1 = 2 ;
		mem [mem [curq ].hh .v.RH ].hh .v.RH = mainp ;
	      } 
	    } 
	    else if ( eqtb [26916 + kp ].hh.b0 == 2 ) 
	    {
	      {
		mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [
		29317 + kp ].cint ) ;
		curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	      } 
	      mem [curlist .tailfield ].hh.b1 = 2 ;
	    } 
	  } 
	} 
      } 
      inskp = false ;
      goto lab130 ;
    } 
  } 
  if ( curcmd == 77 ) 
  {
    inhibitglueflag = true ;
    goto lab100 ;
  } 
  if ( curcmd == 70 ) 
  bchar = 256 ;
  curr = bchar ;
  ligstack = -1073741823L ;
  goto lab110 ;
  lab101: mains = eqtb [27694 + curchr ].hh .v.RH ;
  if ( mains == 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else if ( mains < 1000 ) 
  {
    if ( mains > 0 ) 
    curlist .auxfield .hh .v.LH = mains ;
  } 
  else if ( curlist .auxfield .hh .v.LH < 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else curlist .auxfield .hh .v.LH = mains ;
  inhibitglueflag = false ;
  {
    ligstack = avail ;
    if ( ligstack == -1073741823L ) 
    ligstack = getavail () ;
    else {
	
      avail = mem [ligstack ].hh .v.RH ;
      mem [ligstack ].hh .v.RH = -1073741823L ;
	;
#ifdef STAT
      incr ( dynused ) ;
#endif /* STAT */
    } 
  } 
  mem [ligstack ].hh.b0 = mainf ;
  curr = curchr ;
  mem [ligstack ].hh.b1 = curr ;
  if ( curr == falsebchar ) 
  curr = 256 ;
  lab110: if ( ( ( maini .b2 ) % 4 ) != 1 ) 
  goto lab80 ;
  if ( curr == 256 ) 
  goto lab80 ;
  maink = ligkernbase [mainf ]+ maini .b3 ;
  mainj = fontinfo [maink ].qqqq ;
  if ( mainj .b0 <= 128 ) 
  goto lab112 ;
  maink = ligkernbase [mainf ]+ 256 * mainj .b2 + mainj .b3 + 32768L - 256 * 
  ( 128 ) ;
  lab111: mainj = fontinfo [maink ].qqqq ;
  lab112: if ( mainj .b1 == curr ) {
      
    if ( mainj .b0 <= 128 ) 
    {
      if ( mainj .b2 >= 128 ) 
      {
	if ( curl < 256 ) 
	{
	  if ( mem [curq ].hh .v.RH > -1073741823L ) {
	      
	    if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
	    insdisc = true ;
	  } 
	  if ( ligaturepresent ) 
	  {
	    mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	    if ( lfthit ) 
	    {
	      mem [mainp ].hh.b1 = 2 ;
	      lfthit = false ;
	    } 
	    if ( rthit ) {
		
	      if ( ligstack == -1073741823L ) 
	      {
		incr ( mem [mainp ].hh.b1 ) ;
		rthit = false ;
	      } 
	    } 
	    mem [curq ].hh .v.RH = mainp ;
	    curlist .tailfield = mainp ;
	    ligaturepresent = false ;
	  } 
	  if ( insdisc ) 
	  {
	    insdisc = false ;
	    if ( curlist .modefield > 0 ) 
	    {
	      mem [curlist .tailfield ].hh .v.RH = newdisc () ;
	      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	    } 
	  } 
	} 
	{
	  mem [curlist .tailfield ].hh .v.RH = newkern ( fontinfo [kernbase 
	  [mainf ]+ 256 * mainj .b2 + mainj .b3 ].cint ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	goto lab90 ;
      } 
      if ( curl == 256 ) 
      lfthit = true ;
      else if ( ligstack == -1073741823L ) 
      rthit = true ;
      {
	if ( interrupt != 0 ) 
	pauseforinstructions () ;
      } 
      switch ( mainj .b2 ) 
      {case 1 : 
      case 5 : 
	{
	  curl = mainj .b3 ;
	  maini = fontinfo [charbase [mainf ]+ effectivechar ( true , mainf 
	  , curl ) ].qqqq ;
	  ligaturepresent = true ;
	} 
	break ;
      case 2 : 
      case 6 : 
	{
	  curr = mainj .b3 ;
	  if ( ligstack == -1073741823L ) 
	  {
	    ligstack = newligitem ( curr ) ;
	    bchar = 256 ;
	  } 
	  else if ( ( ligstack >= himemmin ) ) 
	  {
	    mainp = ligstack ;
	    ligstack = newligitem ( curr ) ;
	    mem [ligstack + 1 ].hh .v.RH = mainp ;
	  } 
	  else mem [ligstack ].hh.b1 = curr ;
	} 
	break ;
      case 3 : 
	{
	  curr = mainj .b3 ;
	  mainp = ligstack ;
	  ligstack = newligitem ( curr ) ;
	  mem [ligstack ].hh .v.RH = mainp ;
	} 
	break ;
      case 7 : 
      case 11 : 
	{
	  if ( curl < 256 ) 
	  {
	    if ( mem [curq ].hh .v.RH > -1073741823L ) {
		
	      if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
	      insdisc = true ;
	    } 
	    if ( ligaturepresent ) 
	    {
	      mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	      if ( lfthit ) 
	      {
		mem [mainp ].hh.b1 = 2 ;
		lfthit = false ;
	      } 
	      if ( false ) {
		  
		if ( ligstack == -1073741823L ) 
		{
		  incr ( mem [mainp ].hh.b1 ) ;
		  rthit = false ;
		} 
	      } 
	      mem [curq ].hh .v.RH = mainp ;
	      curlist .tailfield = mainp ;
	      ligaturepresent = false ;
	    } 
	    if ( insdisc ) 
	    {
	      insdisc = false ;
	      if ( curlist .modefield > 0 ) 
	      {
		mem [curlist .tailfield ].hh .v.RH = newdisc () ;
		curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	      } 
	    } 
	  } 
	  curq = curlist .tailfield ;
	  curl = mainj .b3 ;
	  maini = fontinfo [charbase [mainf ]+ effectivechar ( true , mainf 
	  , curl ) ].qqqq ;
	  ligaturepresent = true ;
	} 
	break ;
	default: 
	{
	  curl = mainj .b3 ;
	  ligaturepresent = true ;
	  if ( ligstack == -1073741823L ) 
	  goto lab80 ;
	  else goto lab91 ;
	} 
	break ;
      } 
      if ( mainj .b2 > 4 ) {
	  
	if ( mainj .b2 != 7 ) 
	goto lab80 ;
      } 
      if ( curl < 256 ) 
      goto lab110 ;
      maink = bcharlabel [mainf ];
      goto lab111 ;
    } 
  } 
  if ( mainj .b0 == 0 ) 
  incr ( maink ) ;
  else {
      
    if ( mainj .b0 >= 128 ) 
    goto lab80 ;
    maink = maink + mainj .b0 + 1 ;
  } 
  goto lab111 ;
  lab95: mainp = mem [ligstack + 1 ].hh .v.RH ;
  if ( mainp > -1073741823L ) 
  {
    mem [curlist .tailfield ].hh .v.RH = mainp ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  tempptr = ligstack ;
  ligstack = mem [tempptr ].hh .v.RH ;
  freenode ( tempptr , 2 ) ;
  maini = fontinfo [charbase [mainf ]+ effectivechar ( true , mainf , curl 
  ) ].qqqq ;
  ligaturepresent = true ;
  if ( ligstack == -1073741823L ) {
      
    if ( mainp > -1073741823L ) 
    goto lab100 ;
    else curr = bchar ;
  } 
  else curr = mem [ligstack ].hh.b1 ;
  goto lab110 ;
  lab120: if ( eqtb [24539 ].hh .v.RH == membot ) 
  {
    {
      mainp = fontglue [eqtb [25582 ].hh .v.RH ];
      if ( mainp == -1073741823L ) 
      {
	mainp = newspec ( membot ) ;
	maink = parambase [eqtb [25582 ].hh .v.RH ]+ 2 ;
	mem [mainp + 1 ].cint = fontinfo [maink ].cint ;
	mem [mainp + 2 ].cint = fontinfo [maink + 1 ].cint ;
	mem [mainp + 3 ].cint = fontinfo [maink + 2 ].cint ;
	fontglue [eqtb [25582 ].hh .v.RH ]= mainp ;
      } 
    } 
    tempptr = newglue ( mainp ) ;
  } 
  else tempptr = newparamglue ( 12 ) ;
  if ( ! ( curlist .tailfield >= himemmin ) && ( mem [curlist .tailfield ]
  .hh.b0 == 5 ) ) 
  {
    mem [curlist .pnodefield ].hh .v.RH = tempptr ;
    mem [tempptr ].hh .v.RH = curlist .tailfield ;
    curlist .pnodefield = tempptr ;
  } 
  else {
      
    mem [curlist .tailfield ].hh .v.RH = tempptr ;
    curlist .tailfield = tempptr ;
  } 
  goto lab60 ;
} 
void 
giveerrhelp ( void ) 
{
  giveerrhelp_regmem 
  tokenshow ( eqtb [25069 ].hh .v.RH ) ;
} 
boolean 
openfmtfile ( void ) 
{
  /* 40 10 */ register boolean Result; openfmtfile_regmem 
  integer j  ;
  j = curinput .locfield ;
  if ( buffer [curinput .locfield ]== 38 ) 
  {
    incr ( curinput .locfield ) ;
    j = curinput .locfield ;
    buffer [last ]= 32 ;
    while ( buffer [j ]!= 32 ) incr ( j ) ;
    packbufferedname ( 0 , curinput .locfield , j - 1 ) ;
    if ( wopenin ( fmtfile ) ) 
    goto lab40 ;
    Fputs ( stdout ,  "Sorry, I can't find the format `" ) ;
    fputs ( stringcast ( nameoffile + 1 ) , stdout ) ;
    Fputs ( stdout ,  "'; will try `" ) ;
    fputs ( TEXformatdefault + 1 , stdout ) ;
    fprintf ( stdout , "%s\n",  "'." ) ;
    fflush ( stdout ) ;
  } 
  packbufferedname ( formatdefaultlength - 4 , 1 , 0 ) ;
  if ( ! wopenin ( fmtfile ) ) 
  {
    ;
    Fputs ( stdout ,  "I can't find the format file `" ) ;
    fputs ( TEXformatdefault + 1 , stdout ) ;
    fprintf ( stdout , "%s\n",  "'!" ) ;
    Result = false ;
    return Result ;
  } 
  lab40: curinput .locfield = j ;
  Result = true ;
  return Result ;
} 
void 
closefilesandterminate ( void ) 
{
  closefilesandterminate_regmem 
  integer k  ;
  {register integer for_end; k = 0 ;for_end = 15 ; if ( k <= for_end) do 
    if ( writeopen [k ]) 
    aclose ( writefile [k ]) ;
  while ( k++ < for_end ) ;} 
	;
#ifdef STAT
  if ( eqtb [28493 ].cint > 0 ) {
      
    if ( logopened ) 
    {
      { putc ( ' ' ,  logfile );  putc ( '\n',  logfile ); }
      fprintf ( logfile , "%s%s\n",  "Here is how much of TeX's memory" , " you used:" ) 
      ;
      fprintf ( logfile , "%c%ld%s",  ' ' , (long)strptr - initstrptr , " string" ) ;
      if ( strptr != initstrptr + 1 ) 
      putc ( 's' ,  logfile );
      fprintf ( logfile , "%s%ld\n",  " out of " , (long)maxstrings - initstrptr ) ;
      fprintf ( logfile , "%c%ld%s%ld\n",  ' ' , (long)poolptr - initpoolptr ,       " string characters out of " , (long)poolsize - initpoolptr ) ;
      fprintf ( logfile , "%c%ld%s%ld\n",  ' ' , (long)lomemmax - memmin + memend - himemmin + 2 ,       " words of memory out of " , (long)memend + 1 - memmin ) ;
      fprintf ( logfile , "%c%ld%s%ld%c%ld\n",  ' ' , (long)cscount ,       " multiletter control sequences out of " , (long)15000 , '+' , (long)hashextra ) ;
      fprintf ( logfile , "%c%ld%s%ld%s",  ' ' , (long)fmemptr , " words of font info for " , (long)fontptr -       0 , " font" ) ;
      if ( fontptr != 1 ) 
      putc ( 's' ,  logfile );
      fprintf ( logfile , "%s%ld%s%ld\n",  ", out of " , (long)fontmemsize , " for " , (long)fontmax - 0 ) 
      ;
      fprintf ( logfile , "%c%ld%s",  ' ' , (long)hyphcount , " hyphenation exception" ) ;
      if ( hyphcount != 1 ) 
      putc ( 's' ,  logfile );
      fprintf ( logfile , "%s%ld\n",  " out of " , (long)hyphsize ) ;
      fprintf ( logfile , "%c%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%c\n",  ' ' , (long)maxinstack , "i," , (long)maxneststack , "n," ,       (long)maxparamstack , "p," , (long)maxbufstack + 1 , "b," , (long)maxsavestack + 6 ,       "s stack positions out of " , (long)stacksize , "i," , (long)nestsize , "n," ,       (long)paramsize , "p," , (long)bufsize , "b," , (long)savesize , 's' ) ;
    } 
  } 
#endif /* STAT */
  while ( curs > -1 ) {
      
    if ( curs > 0 ) 
    {
      dvibuf [dviptr ]= 142 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    else {
	
      {
	dvibuf [dviptr ]= 140 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      incr ( totalpages ) ;
    } 
    decr ( curs ) ;
  } 
  if ( totalpages == 0 ) 
  printnl ( 893 ) ;
  else if ( curs != -2 ) 
  {
    {
      dvibuf [dviptr ]= 248 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( lastbop ) ;
    lastbop = dvioffset + dviptr - 5 ;
    dvifour ( 25400000L ) ;
    dvifour ( 473628672L ) ;
    preparemag () ;
    dvifour ( eqtb [28479 ].cint ) ;
    dvifour ( maxv ) ;
    dvifour ( maxh ) ;
    {
      dvibuf [dviptr ]= maxpush / 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= maxpush % 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( totalpages / 256 ) % 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= totalpages % 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    while ( fontptr > 0 ) {
	
      if ( fontused [fontptr ]) 
      dvifontdef ( fontptr ) ;
      decr ( fontptr ) ;
    } 
    {
      dvibuf [dviptr ]= 249 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( lastbop ) ;
    if ( dirused ) 
    {
      dvibuf [dviptr ]= 3 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    else {
	
      dvibuf [dviptr ]= 2 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
	;
#ifdef IPC
    k = 7 - ( ( 3 + dvioffset + dviptr ) % 4 ) ;
#endif /* IPC */
	;
#ifndef IPC
    k = 4 + ( ( dvibufsize - dviptr ) % 4 ) ;
#endif /* not IPC */
    while ( k > 0 ) {
	
      {
	dvibuf [dviptr ]= 223 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      decr ( k ) ;
    } 
    if ( dvilimit == halfbuf ) 
    writedvi ( halfbuf , dvibufsize - 1 ) ;
    if ( dviptr > ( 2147483647L - dvioffset ) ) 
    {
      curs = -2 ;
      fatalerror ( 882 ) ;
    } 
    if ( dviptr > 0 ) 
    writedvi ( 0 , dviptr - 1 ) ;
    printnl ( 894 ) ;
    printfilename ( 0 , outputfilename , 0 ) ;
    print ( 285 ) ;
    printint ( totalpages ) ;
    if ( totalpages != 1 ) 
    print ( 895 ) ;
    else print ( 896 ) ;
    print ( 328 ) ;
    printint ( dvioffset + dviptr ) ;
    print ( 897 ) ;
    bclose ( dvifile ) ;
  } 
  synctexterminate ( logopened ) ;
  if ( logopened ) 
  {
    putc ('\n',  logfile );
    aclose ( logfile ) ;
    selector = selector - 2 ;
    if ( selector == 17 ) 
    {
      printnl ( 1360 ) ;
      printfilename ( 0 , texmflogname , 0 ) ;
      printchar ( 46 ) ;
    } 
  } 
  println () ;
  if ( ( editnamestart != 0 ) && ( interaction > 0 ) ) 
  calledit ( strpool , editnamestart , editnamelength , editline ) ;
} 
#ifdef TEXMF_DEBUG
void 
debughelp ( void ) 
{
  /* 888 10 */ debughelp_regmem 
  integer k, l, m, n  ;
  while ( true ) {
      
    ;
    printnl ( 1369 ) ;
    fflush ( stdout ) ;
    read ( stdin , m ) ;
    if ( m < 0 ) 
    return ;
    else if ( m == 0 ) 
    dumpcore () ;
    else {
	
      read ( stdin , n ) ;
      switch ( m ) 
      {case 1 : 
	printword ( mem [n ]) ;
	break ;
      case 2 : 
	printint ( mem [n ].hh .v.LH ) ;
	break ;
      case 3 : 
	printint ( mem [n ].hh .v.RH ) ;
	break ;
      case 4 : 
	printword ( eqtb [n ]) ;
	break ;
      case 5 : 
	{
	  printscaled ( fontinfo [n ].cint ) ;
	  printchar ( 32 ) ;
	  printint ( fontinfo [n ].qqqq .b0 ) ;
	  printchar ( 58 ) ;
	  printint ( fontinfo [n ].qqqq .b1 ) ;
	  printchar ( 58 ) ;
	  printint ( fontinfo [n ].qqqq .b2 ) ;
	  printchar ( 58 ) ;
	  printint ( fontinfo [n ].qqqq .b3 ) ;
	} 
	break ;
      case 6 : 
	printword ( savestack [n ]) ;
	break ;
      case 7 : 
	showbox ( n ) ;
	break ;
      case 8 : 
	{
	  breadthmax = 10000 ;
	  depththreshold = poolsize - poolptr - 10 ;
	  shownodelist ( n ) ;
	} 
	break ;
      case 9 : 
	showtokenlist ( n , -1073741823L , 1000 ) ;
	break ;
      case 10 : 
	slowprint ( n ) ;
	break ;
      case 11 : 
	checkmem ( n > 0 ) ;
	break ;
      case 12 : 
	searchmem ( n ) ;
	break ;
      case 13 : 
	{
	  read ( stdin , l ) ;
	  printcmdchr ( n , l ) ;
	} 
	break ;
      case 14 : 
	{register integer for_end; k = 0 ;for_end = n ; if ( k <= for_end) 
	do 
	  print ( buffer [k ]) ;
	while ( k++ < for_end ) ;} 
	break ;
      case 15 : 
	{
	  fontinshortdisplay = 0 ;
	  shortdisplay ( n ) ;
	} 
	break ;
      case 16 : 
	panicking = ! panicking ;
	break ;
	default: 
	print ( 63 ) ;
	break ;
      } 
    } 
  } 
} 
#endif /* TEXMF_DEBUG */
strnumber 
getnullstr ( void ) 
{
  register strnumber Result; getnullstr_regmem 
  Result = 344 ;
  return Result ;
} 