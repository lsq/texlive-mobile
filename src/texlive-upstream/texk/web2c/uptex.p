{4:}{9:}{$C-,A+,D-}ifdef('TEXMF_DEBUG'){$C+,D+}
endif('TEXMF_DEBUG'){:9}program TEX;const{11:}hashoffset=514;
trieopsize=35111;negtrieopsize=-35111;mintrieop=0;maxtrieop=65535;
poolname=TEXMFPOOLNAME;enginename=TEXMFENGINENAME;infmembot=0;
supmembot=1;infmainmemory=3000;supmainmemory=256000000;inftriesize=8000;
suptriesize=4194303;infmaxstrings=3000;supmaxstrings=2097151;
infstringsfree=100;supstringsfree=supmaxstrings;infbufsize=500;
supbufsize=30000000;infnestsize=40;supnestsize=4000;infmaxinopen=6;
supmaxinopen=127;infparamsize=60;supparamsize=32767;infsavesize=600;
supsavesize=80000;infstacksize=200;supstacksize=30000;infdvibufsize=800;
supdvibufsize=65536;inffontmemsize=20000;supfontmemsize=147483647;
supfontmax=9000;inffontmax=50;infpoolsize=32000;suppoolsize=40000000;
infpoolfree=1000;suppoolfree=suppoolsize;infstringvacancies=8000;
supstringvacancies=suppoolsize-23000;suphashextra=supmaxstrings;
infhashextra=0;suphyphsize=65535;infhyphsize=610;infexpanddepth=10;
supexpanddepth=10000000;{:11}type{18:}ASCIIcode=0..255;
KANJIcode=0..16777215;{:18}{25:}eightbits=0..255;sixteenbits=0..65535;
alphafile=packed file of ASCIIcode;bytefile=packed file of eightbits;
{:25}{39:}poolpointer=integer;strnumber=0..2097151;
packedASCIIcode=0..255;{:39}{102:}scaled=integer;
nonnegativeinteger=0..2147483647;smallnumber=0..63;
{:102}{110:}{:110}{114:}quarterword=0..65535;
halfword=-1073741823..1073741823;twochoices=1..2;fourchoices=1..4;
#include "texmfmem.h";wordfile=file of memoryword;
{:114}{156:}glueord=0..3;
{:156}{218:}liststaterecord=record modefield:-233..233;
dirfield,adjdirfield:-4..4;pdispfield:scaled;
headfield,tailfield,pnodefield,lastjchrfield:halfword;
pgfield,mlfield:integer;auxfield:memoryword;end;
{:218}{275:}groupcode=0..16;
{:275}{306:}instaterecord=record statefield,indexfield:quarterword;
startfield,locfield,limitfield,namefield:halfword;
synctextagfield:integer;end;{:306}{559:}internalfontnumber=integer;
fontindex=integer;ninebits=0..256;{:559}{605:}dviindex=0..dvibufsize;
{:605}{931:}triepointer=0..4194303;trieopcode=0..65535;
{:931}{936:}hyphpointer=0..65535;{:936}var{13:}bad:integer;
{:13}{20:}xord:array[ASCIIcode]of ASCIIcode;
xchr:array[ASCIIcode]of ASCIIcode;xprn:array[ASCIIcode]of ASCIIcode;
{:20}{26:}nameoffile:^ASCIIcode;namelength:0..maxint;
{:26}{31:}buffer:^ASCIIcode;first:0..bufsize;last:0..bufsize;
maxbufstack:0..bufsize;{:31}{33:}ifdef('INITEX')iniversion:boolean;
dumpoption:boolean;dumpline:boolean;
endif('INITEX')dumpname:constcstring;bounddefault:integer;
boundname:constcstring;membot:integer;mainmemory:integer;
extramembot:integer;memmin:integer;memtop:integer;extramemtop:integer;
memmax:integer;errorline:integer;halferrorline:integer;
maxprintline:integer;maxstrings:integer;stringsfree:integer;
stringvacancies:integer;poolsize:integer;poolfree:integer;
fontmemsize:integer;fontmax:integer;fontk:integer;hyphsize:integer;
triesize:integer;bufsize:integer;stacksize:integer;maxinopen:integer;
paramsize:integer;nestsize:integer;savesize:integer;dvibufsize:integer;
expanddepth:integer;parsefirstlinep:cinttype;
filelineerrorstylep:cinttype;eightbitp:cinttype;haltonerrorp:cinttype;
quotedfilename:boolean;srcspecialsp:boolean;
insertsrcspecialauto:boolean;insertsrcspecialeverypar:boolean;
insertsrcspecialeveryparend:boolean;insertsrcspecialeverycr:boolean;
insertsrcspecialeverymath:boolean;insertsrcspecialeveryhbox:boolean;
insertsrcspecialeveryvbox:boolean;insertsrcspecialeverydisplay:boolean;
{:33}{40:}strpool:^packedASCIIcode;strstart:^poolpointer;
poolptr:poolpointer;strptr:strnumber;initpoolptr:poolpointer;
initstrptr:strnumber;{:40}{51:}ifdef('INITEX')poolfile:alphafile;
endif('INITEX'){:51}{55:}logfile:alphafile;selector:0..21;
dig:array[0..22]of 0..15;tally:integer;termoffset:0..maxprintline;
fileoffset:0..maxprintline;trickbuf:array[0..255]of ASCIIcode;
trickbuf2:array[0..255]of 0..20;kcodepos:0..20;kcp:0..20;
prevchar:ASCIIcode;trickcount:integer;firstcount:integer;
{:55}{74:}interaction:0..3;interactionoption:0..4;
{:74}{77:}deletionsallowed:boolean;setboxallowed:boolean;history:0..3;
errorcount:-1..100;{:77}{80:}helpline:array[0..5]of strnumber;
helpptr:0..6;useerrhelp:boolean;{:80}{97:}interrupt:integer;
OKtointerrupt:boolean;{:97}{105:}aritherror:boolean;texremainder:scaled;
{:105}{116:}tempptr:halfword;{:116}{117:}yzmem:^memoryword;
zmem:^memoryword;lomemmax:halfword;himemmin:halfword;
{:117}{118:}varused,dynused:integer;{:118}{119:}avail:halfword;
memend:halfword;{:119}{125:}rover:halfword;
{:125}{171:}ifdef('TEXMF_DEBUG')freearr:packed array[0..9]of boolean;
wasfree:packed array[0..9]of boolean;
wasmemend,waslomax,washimin:halfword;panicking:boolean;
endif('TEXMF_DEBUG'){:171}{179:}fontinshortdisplay:integer;
{:179}{187:}depththreshold:integer;breadthmax:integer;
{:187}{219:}nest:^liststaterecord;nestptr:0..nestsize;
maxneststack:0..nestsize;curlist:liststaterecord;shownmode:-233..233;
{:219}{252:}oldsetting:0..21;{:252}{259:}zeqtb:^memoryword;
xeqlevel:array[28462..29572]of quarterword;{:259}{262:}hash:^twohalves;
yhash:^twohalves;hashused:halfword;hashextra:halfword;hashtop:halfword;
eqtbtop:halfword;hashhigh:halfword;nonewcontrolsequence:boolean;
cscount:integer;{:262}{277:}savestack:^memoryword;saveptr:0..savesize;
maxsavestack:0..savesize;curlevel:quarterword;curgroup:groupcode;
curboundary:0..savesize;{:277}{292:}magset:integer;
{:292}{303:}curcmd:eightbits;curchr:halfword;curcs:halfword;
curtok:halfword;{:303}{307:}inputstack:^instaterecord;
inputptr:0..stacksize;maxinstack:0..stacksize;curinput:instaterecord;
{:307}{310:}inopen:0..maxinopen;openparens:0..maxinopen;
inputfile:^alphafile;line:integer;linestack:^integer;
sourcefilenamestack:^strnumber;fullsourcefilenamestack:^strnumber;
{:310}{311:}scannerstatus:0..5;warningindex:halfword;defref:halfword;
{:311}{314:}paramstack:^halfword;paramptr:0..paramsize;
maxparamstack:integer;{:314}{315:}alignstate:integer;
{:315}{316:}baseptr:0..stacksize;{:316}{339:}parloc:halfword;
partoken:halfword;{:339}{354:}skipmode:boolean;
{:354}{369:}forceeof:boolean;{:369}{375:}expanddepthcount:integer;
{:375}{393:}curmark:array[0..4]of halfword;
{:393}{398:}longstate:126..129;
{:398}{399:}pstack:array[0..8]of halfword;{:399}{421:}curval:integer;
curvallevel:0..5;{:421}{449:}radix:smallnumber;
{:449}{458:}curorder:glueord;
{:458}{491:}readfile:array[0..15]of alphafile;
readopen:array[0..16]of 0..2;{:491}{500:}condptr:halfword;iflimit:0..4;
curif:smallnumber;ifline:integer;{:500}{504:}skipline:integer;
{:504}{523:}curname:strnumber;curarea:strnumber;curext:strnumber;
{:523}{524:}areadelimiter:poolpointer;extdelimiter:poolpointer;
{:524}{531:}formatdefaultlength:integer;TEXformatdefault:cstring;
{:531}{538:}nameinprogress:boolean;jobname:strnumber;logopened:boolean;
{:538}{543:}dvifile:bytefile;outputfilename:strnumber;
texmflogname:strnumber;{:543}{550:}tfmfile:bytefile;
{:550}{560:}fontinfo:^memoryword;fontdir:^eightbits;fontnumext:^integer;
fmemptr:fontindex;fontptr:internalfontnumber;fontcheck:^fourquarters;
fontsize:^scaled;fontdsize:^scaled;fontparams:^fontindex;
fontname:^strnumber;fontarea:^strnumber;fontbc:^eightbits;
fontec:^eightbits;fontglue:^halfword;fontused:^boolean;
hyphenchar:^integer;skewchar:^integer;bcharlabel:^fontindex;
fontbchar:^ninebits;fontfalsebchar:^ninebits;
{:560}{561:}charbase:^integer;ctypebase:^integer;widthbase:^integer;
heightbase:^integer;depthbase:^integer;italicbase:^integer;
ligkernbase:^integer;kernbase:^integer;extenbase:^integer;
parambase:^integer;{:561}{566:}nullcharacter:fourquarters;
{:566}{603:}totalpages:integer;maxv:scaled;maxh:scaled;maxpush:integer;
lastbop:integer;deadcycles:integer;doingleaders:boolean;c:quarterword;
f:internalfontnumber;dirused:boolean;ruleht,ruledp,rulewd:scaled;
g:halfword;lq,lr:integer;{:603}{606:}dvibuf:^eightbits;halfbuf:integer;
dvilimit:integer;dviptr:integer;dvioffset:integer;dvigone:integer;
{:606}{616:}downptr,rightptr:halfword;{:616}{627:}dvih,dviv:scaled;
curh,curv:scaled;dvif:internalfontnumber;curs:integer;
{:627}{657:}totalstretch,totalshrink:array[glueord]of scaled;
lastbadness:integer;{:657}{658:}adjusttail:halfword;lastdisp:scaled;
curkanjiskip:halfword;curxkanjiskip:halfword;
{:658}{672:}packbeginline:integer;{:672}{695:}emptyfield:twohalves;
nulldelimiter:fourquarters;{:695}{730:}curmlist:halfword;
curstyle:smallnumber;cursize:smallnumber;curmu:scaled;
mlistpenalties:boolean;{:730}{735:}curf:internalfontnumber;
curc:quarterword;curi:fourquarters;{:735}{775:}magicoffset:integer;
{:775}{781:}curalign:halfword;curspan:halfword;curloop:halfword;
alignptr:halfword;curhead,curtail:halfword;{:781}{825:}justbox:halfword;
{:825}{832:}passive:halfword;printednode:halfword;passnumber:halfword;
{:832}{834:}activewidth:array[1..6]of scaled;
curactivewidth:array[1..6]of scaled;background:array[1..6]of scaled;
breakwidth:array[1..6]of scaled;{:834}{836:}noshrinkerroryet:boolean;
{:836}{839:}curp:halfword;chain:boolean;secondpass:boolean;
finalpass:boolean;threshold:integer;
{:839}{844:}minimaldemerits:array[0..3]of integer;
minimumdemerits:integer;bestplace:array[0..3]of halfword;
bestplline:array[0..3]of halfword;{:844}{850:}discwidth:scaled;
{:850}{858:}easyline:halfword;lastspecialline:halfword;
firstwidth:scaled;secondwidth:scaled;firstindent:scaled;
secondindent:scaled;{:858}{883:}bestbet:halfword;fewestdemerits:integer;
bestline:halfword;actuallooseness:integer;linediff:integer;
{:883}{903:}hc:array[0..65]of 0..256;hn:smallnumber;ha,hb:halfword;
hf:internalfontnumber;hu:array[0..63]of 0..256;hyfchar:integer;
curlang,initcurlang:ASCIIcode;lhyf,rhyf,initlhyf,initrhyf:integer;
hyfbchar:halfword;{:903}{911:}hyf:array[0..64]of 0..9;initlist:halfword;
initlig:boolean;initlft:boolean;{:911}{916:}hyphenpassed:smallnumber;
{:916}{918:}curl,curr:halfword;curq:halfword;ligstack:halfword;
ligaturepresent:boolean;lfthit,rthit:boolean;
{:918}{932:}trietrl:^triepointer;trietro:^triepointer;
trietrc:^quarterword;hyfdistance:array[1..trieopsize]of smallnumber;
hyfnum:array[1..trieopsize]of smallnumber;
hyfnext:array[1..trieopsize]of trieopcode;
opstart:array[ASCIIcode]of 0..trieopsize;
{:932}{937:}hyphword:^strnumber;hyphlist:^halfword;
hyphlink:^hyphpointer;hyphcount:integer;hyphnext:integer;
{:937}{954:}ifdef('INITEX')trieophash:array[negtrieopsize..trieopsize]of
0..trieopsize;trieused:array[ASCIIcode]of trieopcode;
trieoplang:array[1..trieopsize]of ASCIIcode;
trieopval:array[1..trieopsize]of trieopcode;trieopptr:0..trieopsize;
endif('INITEX')maxopused:trieopcode;smallop:boolean;
{:954}{958:}ifdef('INITEX')triec:^packedASCIIcode;trieo:^trieopcode;
triel:^triepointer;trier:^triepointer;trieptr:triepointer;
triehash:^triepointer;
endif('INITEX'){:958}{961:}ifdef('INITEX')trietaken:^boolean;
triemin:array[ASCIIcode]of triepointer;triemax:triepointer;
trienotready:boolean;
endif('INITEX'){:961}{982:}bestheightplusdepth:scaled;
{:982}{991:}pagetail:halfword;pagecontents:0..2;pagemaxdepth:scaled;
bestpagebreak:halfword;leastpagecost:integer;bestsize:scaled;
{:991}{993:}pagesofar:array[0..7]of scaled;lastglue:halfword;
lastpenalty:integer;lastkern:scaled;insertpenalties:integer;
{:993}{1000:}outputactive:boolean;
{:1000}{1043:}mainf:internalfontnumber;maini:fourquarters;
mainj:fourquarters;maink:fontindex;mainp:halfword;mains:integer;
bchar:halfword;falsebchar:halfword;cancelboundary:boolean;
insdisc:boolean;{:1043}{1086:}curbox:halfword;
{:1086}{1279:}aftertoken:halfword;{:1279}{1294:}longhelpseen:boolean;
{:1294}{1312:}formatident:strnumber;{:1312}{1318:}fmtfile:wordfile;
{:1318}{1344:}readyalready:integer;
{:1344}{1355:}writefile:array[0..15]of alphafile;
writeopen:array[0..17]of boolean;{:1355}{1358:}writeloc:halfword;
{:1358}{1392:}editnamestart:poolpointer;editnamelength,editline:integer;
ipcon:cinttype;stopatspace:boolean;{:1392}{1394:}savestrptr:strnumber;
savepoolptr:poolpointer;shellenabledp:cinttype;restrictedshell:cinttype;
outputcomment:^char;k,l:0..255;{:1394}{1396:}debugformatfile:boolean;
{:1396}{1404:}mltexp:boolean;{:1404}{1405:}mltexenabledp:boolean;
{:1405}{1410:}accentc,basec,replacec:integer;iac,ibc:fourquarters;
baseslant,accentslant:real;basexheight:scaled;
basewidth,baseheight:scaled;accentwidth,accentheight:scaled;
delta:scaled;{:1410}{1418:}synctexoption:integer;
{:1418}{1422:}synctexoffset:integer;
{:1422}{1463:}inhibitglueflag:boolean;{:1463}{1479:}dvidir:integer;
curdirhv:integer;pagedir:eightbits;{:1479}{1482:}firstchar:halfword;
lastchar:halfword;findfirstchar:boolean;{:1482}procedure initialize;
var{19:}i:integer;{:19}{169:}k:integer;{:169}{938:}z:hyphpointer;
{:938}begin{8:}{21:}xchr[32]:=' ';xchr[33]:='!';xchr[34]:='"';
xchr[35]:='#';xchr[36]:='$';xchr[37]:='%';xchr[38]:='&';xchr[39]:='''';
xchr[40]:='(';xchr[41]:=')';xchr[42]:='*';xchr[43]:='+';xchr[44]:=',';
xchr[45]:='-';xchr[46]:='.';xchr[47]:='/';xchr[48]:='0';xchr[49]:='1';
xchr[50]:='2';xchr[51]:='3';xchr[52]:='4';xchr[53]:='5';xchr[54]:='6';
xchr[55]:='7';xchr[56]:='8';xchr[57]:='9';xchr[58]:=':';xchr[59]:=';';
xchr[60]:='<';xchr[61]:='=';xchr[62]:='>';xchr[63]:='?';xchr[64]:='@';
xchr[65]:='A';xchr[66]:='B';xchr[67]:='C';xchr[68]:='D';xchr[69]:='E';
xchr[70]:='F';xchr[71]:='G';xchr[72]:='H';xchr[73]:='I';xchr[74]:='J';
xchr[75]:='K';xchr[76]:='L';xchr[77]:='M';xchr[78]:='N';xchr[79]:='O';
xchr[80]:='P';xchr[81]:='Q';xchr[82]:='R';xchr[83]:='S';xchr[84]:='T';
xchr[85]:='U';xchr[86]:='V';xchr[87]:='W';xchr[88]:='X';xchr[89]:='Y';
xchr[90]:='Z';xchr[91]:='[';xchr[92]:='\';xchr[93]:=']';xchr[94]:='^';
xchr[95]:='_';xchr[96]:='`';xchr[97]:='a';xchr[98]:='b';xchr[99]:='c';
xchr[100]:='d';xchr[101]:='e';xchr[102]:='f';xchr[103]:='g';
xchr[104]:='h';xchr[105]:='i';xchr[106]:='j';xchr[107]:='k';
xchr[108]:='l';xchr[109]:='m';xchr[110]:='n';xchr[111]:='o';
xchr[112]:='p';xchr[113]:='q';xchr[114]:='r';xchr[115]:='s';
xchr[116]:='t';xchr[117]:='u';xchr[118]:='v';xchr[119]:='w';
xchr[120]:='x';xchr[121]:='y';xchr[122]:='z';xchr[123]:='{';
xchr[124]:='|';xchr[125]:='}';xchr[126]:='~';
{:21}{23:}for i:=0 to 31 do xchr[i]:=i;for i:=127 to 255 do xchr[i]:=i;
{:23}{24:}for i:=0 to 255 do xord[chr(i)]:=127;
for i:=128 to 255 do xord[xchr[i]]:=i;
for i:=0 to 126 do xord[xchr[i]]:=i;
for i:=0 to 255 do xprn[i]:=(eightbitp or((i>=32)and(i<=126)));
if translatefilename then readtcxfile;
{:24}{75:}if interactionoption=4 then interaction:=3 else interaction:=
interactionoption;{:75}{78:}deletionsallowed:=true;setboxallowed:=true;
errorcount:=0;{:78}{81:}helpptr:=0;useerrhelp:=false;
{:81}{98:}interrupt:=0;OKtointerrupt:=true;
{:98}{172:}ifdef('TEXMF_DEBUG')wasmemend:=memmin;waslomax:=memmin;
washimin:=memmax;panicking:=false;
endif('TEXMF_DEBUG'){:172}{221:}nestptr:=0;maxneststack:=0;
curlist.modefield:=1;curlist.headfield:=memtop-1;
curlist.tailfield:=memtop-1;curlist.pnodefield:=curlist.tailfield;
curlist.dirfield:=4;curlist.adjdirfield:=curlist.dirfield;
curlist.pdispfield:=0;curlist.lastjchrfield:=-1073741823;
curlist.auxfield.int:=-65536000;curlist.mlfield:=0;curlist.pgfield:=0;
shownmode:=0;pagecontents:=0;pagetail:=memtop-2;lastglue:=1073741823;
lastpenalty:=0;lastkern:=0;pagesofar[7]:=0;pagemaxdepth:=0;
{:221}{260:}for k:=28462 to 29572 do xeqlevel[k]:=1;
{:260}{263:}nonewcontrolsequence:=true;{:263}{278:}saveptr:=0;
curlevel:=1;curgroup:=0;curboundary:=0;maxsavestack:=0;
{:278}{293:}magset:=0;{:293}{355:}skipmode:=true;
{:355}{376:}expanddepthcount:=0;{:376}{394:}curmark[0]:=-1073741823;
curmark[1]:=-1073741823;curmark[2]:=-1073741823;curmark[3]:=-1073741823;
curmark[4]:=-1073741823;{:394}{450:}curval:=0;curvallevel:=0;radix:=0;
curorder:=0;{:450}{492:}for k:=0 to 16 do readopen[k]:=2;
{:492}{501:}condptr:=-1073741823;iflimit:=0;curif:=0;ifline:=0;
{:501}{562:}{:562}{567:}nullcharacter.b0:=0;nullcharacter.b1:=0;
nullcharacter.b2:=0;nullcharacter.b3:=0;{:567}{604:}totalpages:=0;
maxv:=0;maxh:=0;maxpush:=0;lastbop:=-1;doingleaders:=false;
deadcycles:=0;curs:=-1;dirused:=false;
{:604}{607:}halfbuf:=dvibufsize div 2;dvilimit:=dvibufsize;dviptr:=0;
dvioffset:=0;dvigone:=0;{:607}{617:}downptr:=-1073741823;
rightptr:=-1073741823;{:617}{659:}adjusttail:=-1073741823;
lastbadness:=0;curkanjiskip:=membot;curxkanjiskip:=membot;
{:659}{673:}packbeginline:=0;{:673}{696:}emptyfield.rh:=0;
emptyfield.lh:=-1073741823;nulldelimiter.b0:=0;nulldelimiter.b1:=0;
nulldelimiter.b2:=0;nulldelimiter.b3:=0;
{:696}{782:}alignptr:=-1073741823;curalign:=-1073741823;
curspan:=-1073741823;curloop:=-1073741823;curhead:=-1073741823;
curtail:=-1073741823;
{:782}{939:}for z:=0 to hyphsize do begin hyphword[z]:=0;
hyphlist[z]:=-1073741823;hyphlink[z]:=0;end;hyphcount:=0;hyphnext:=608;
if hyphnext>hyphsize then hyphnext:=607;
{:939}{1001:}outputactive:=false;insertpenalties:=0;
{:1001}{1044:}ligaturepresent:=false;cancelboundary:=false;
lfthit:=false;rthit:=false;insdisc:=false;{:1044}{1280:}aftertoken:=0;
{:1280}{1295:}longhelpseen:=false;{:1295}{1313:}formatident:=0;
{:1313}{1356:}for k:=0 to 17 do writeopen[k]:=false;
{:1356}{1393:}editnamestart:=0;stopatspace:=true;
{:1393}{1397:}ifdef('TEXMF_DEBUG')debugformatfile:=true;
endif('TEXMF_DEBUG');{:1397}{1406:}mltexenabledp:=false;
{:1406}{1464:}inhibitglueflag:=false;{:1464}{1480:}pagedir:=4;
{:1480}ifdef('INITEX')if iniversion then begin{170:}for k:=membot+1 to
membot+19 do mem[k].int:=0;k:=membot;
while k<=membot+19 do begin mem[k].hh.rh:=-1073741822;mem[k].hh.b0:=0;
mem[k].hh.b1:=0;k:=k+4;end;mem[membot+6].int:=65536;
mem[membot+4].hh.b0:=1;mem[membot+10].int:=65536;mem[membot+8].hh.b0:=2;
mem[membot+14].int:=65536;mem[membot+12].hh.b0:=1;
mem[membot+15].int:=65536;mem[membot+12].hh.b1:=1;
mem[membot+18].int:=-65536;mem[membot+16].hh.b0:=1;rover:=membot+20;
mem[rover].hh.rh:=1073741823;mem[rover].hh.lh:=1000;
mem[rover+1].hh.lh:=rover;mem[rover+1].hh.rh:=rover;
lomemmax:=rover+1000;mem[lomemmax].hh.rh:=-1073741823;
mem[lomemmax].hh.lh:=-1073741823;
for k:=memtop-13 to memtop do mem[k]:=mem[lomemmax];
{801:}mem[memtop-10].hh.lh:=536886430;
{:801}{808:}mem[memtop-9].hh.rh:=65536;mem[memtop-9].hh.lh:=-1073741823;
{:808}{831:}mem[memtop-7].hh.b0:=1;mem[memtop-6].hh.lh:=1073741823;
mem[memtop-7].hh.b1:=0;{:831}{992:}mem[memtop].hh.b1:=255;
mem[memtop].hh.b0:=1;mem[memtop].hh.rh:=memtop;
{:992}{999:}mem[memtop-2].hh.b0:=12;mem[memtop-2].hh.b1:=0;{:999};
avail:=-1073741823;memend:=memtop;himemmin:=memtop-13;
varused:=membot+20-membot;dynused:=14;
{:170}{228:}eqtb[24526].hh.b0:=116;eqtb[24526].hh.rh:=-1073741823;
eqtb[24526].hh.b1:=0;for k:=1 to eqtbtop do eqtb[k]:=eqtb[24526];
{:228}{234:}eqtb[24527].hh.rh:=membot;eqtb[24527].hh.b1:=1;
eqtb[24527].hh.b0:=132;for k:=24528 to 25059 do eqtb[k]:=eqtb[24527];
mem[membot].hh.rh:=mem[membot].hh.rh+533;
{:234}{238:}eqtb[25060].hh.rh:=-1073741823;eqtb[25060].hh.b0:=133;
eqtb[25060].hh.b1:=1;for k:=25061 to 25325 do eqtb[k]:=eqtb[24526];
eqtb[25326].hh.rh:=-1073741823;eqtb[25326].hh.b0:=134;
eqtb[25326].hh.b1:=1;for k:=25327 to 25581 do eqtb[k]:=eqtb[25326];
eqtb[25582].hh.rh:=0;eqtb[25582].hh.b0:=135;eqtb[25582].hh.b1:=1;
eqtb[25631].hh.rh:=0;eqtb[25631].hh.b0:=135;eqtb[25631].hh.b1:=1;
eqtb[25632].hh.rh:=0;eqtb[25632].hh.b0:=135;eqtb[25632].hh.b1:=1;
for k:=25583 to 25630 do eqtb[k]:=eqtb[25582];eqtb[25636].hh.rh:=0;
eqtb[25636].hh.b0:=135;eqtb[25636].hh.b1:=1;
for k:=25637 to 28461 do eqtb[k]:=eqtb[25636];eqtb[25633]:=eqtb[25636];
eqtb[25634]:=eqtb[25636];eqtb[25635]:=eqtb[25636];
for k:=0 to 255 do begin eqtb[25636+k].hh.rh:=12;eqtb[27950+k].hh.rh:=k;
eqtb[27694+k].hh.rh:=1000;eqtb[26404+k].hh.rh:=0;eqtb[26660+k].hh.rh:=0;
eqtb[26660+k].hh.b0:=0;eqtb[26916+k].hh.rh:=0;eqtb[26916+k].hh.b0:=0;
end;for k:=0 to 511 do begin eqtb[25892+k].hh.rh:=18;end;
eqtb[25649].hh.rh:=5;eqtb[25668].hh.rh:=10;eqtb[25728].hh.rh:=0;
eqtb[25673].hh.rh:=14;eqtb[25763].hh.rh:=15;eqtb[25636].hh.rh:=9;
for k:=48 to 57 do begin eqtb[27950+k].hh.rh:=k+28672;
eqtb[26404+k].hh.rh:=3;end;eqtb[27172].hh.rh:=toDVI(fromJIS(8507));
eqtb[27173].hh.rh:=toDVI(fromJIS(12396));
eqtb[27174].hh.rh:=toDVI(fromJIS(18035));
eqtb[27175].hh.rh:=toDVI(fromJIS(15152));
eqtb[27176].hh.rh:=toDVI(fromJIS(15181));
eqtb[27177].hh.rh:=toDVI(fromJIS(14430));
eqtb[27178].hh.rh:=toDVI(fromJIS(20283));
eqtb[27179].hh.rh:=toDVI(fromJIS(15415));
eqtb[27180].hh.rh:=toDVI(fromJIS(18476));
eqtb[27181].hh.rh:=toDVI(fromJIS(13925));
for k:=65 to 90 do begin eqtb[25636+k].hh.rh:=11;
eqtb[25636+k+32].hh.rh:=11;eqtb[27950+k].hh.rh:=k+28928;
eqtb[27950+k+32].hh.rh:=k+28960;eqtb[27182+k].hh.rh:=k+32;
eqtb[27182+k+32].hh.rh:=k+32;eqtb[27438+k].hh.rh:=k;
eqtb[27438+k+32].hh.rh:=k;eqtb[26404+k].hh.rh:=3;
eqtb[26404+k+32].hh.rh:=3;eqtb[27694+k].hh.rh:=999;end;
if(isinternalUPTEX)then begin eqtb[25892].hh.rh:=15;
eqtb[25927].hh.rh:=19;for k:=100 to 102 do eqtb[25892+k].hh.rh:=16;
for k:=104 to 105 do eqtb[25892+k].hh.rh:=17;eqtb[25998].hh.rh:=16;
eqtb[25999].hh.rh:=19;for k:=108 to 110 do eqtb[25892+k].hh.rh:=16;
eqtb[26003].hh.rh:=17;eqtb[26006].hh.rh:=16;eqtb[26008].hh.rh:=16;
eqtb[26024].hh.rh:=19;eqtb[26035].hh.rh:=19;eqtb[26036].hh.rh:=19;
eqtb[26041].hh.rh:=16;eqtb[26120].hh.rh:=17;
for k:=253 to 257 do eqtb[25892+k].hh.rh:=16;eqtb[26402].hh.rh:=17;
eqtb[26403].hh.rh:=17;end else begin eqtb[25925].hh.rh:=18;
eqtb[25926].hh.rh:=18;for k:=3 to 6 do eqtb[25924+k].hh.rh:=17;
for k:=7 to 13 do eqtb[25924+k].hh.rh:=18;
for k:=14 to 120 do eqtb[25924+k].hh.rh:=16;
for k:=16 to 94 do eqtb[26052+k].hh.rh:=16;end;
{:238}{246:}for k:=28462 to 28781 do eqtb[k].int:=0;
eqtb[28522].int:=256;eqtb[28523].int:=-1;eqtb[28479].int:=1000;
eqtb[28463].int:=10000;eqtb[28503].int:=1;eqtb[28502].int:=25;
eqtb[28508].int:=92;eqtb[28511].int:=13;
for k:=0 to 255 do eqtb[28782+k].int:=-1;eqtb[28828].int:=0;
{:246}{256:}for k:=29038 to 29572 do eqtb[k].int:=0;
{:256}{264:}hashused:=15514;hashhigh:=0;cscount:=0;
eqtb[15523].hh.b0:=131;hash[15523].rh:=537;
{:264}{563:}{:563}{692:}eqtb[28519].int:=1000;eqtb[28520].int:=700;
eqtb[28521].int:=500;
{:692}{957:}for k:=-trieopsize to trieopsize do trieophash[k]:=0;
for k:=0 to 255 do trieused[k]:=mintrieop;maxopused:=mintrieop;
trieopptr:=0;{:957}{962:}trienotready:=true;
{:962}{1228:}hash[15514].rh:=1265;
{:1228}{1314:}if iniversion then formatident:=1339;
{:1314}{1382:}hash[15522].rh:=1381;eqtb[15522].hh.b1:=1;
eqtb[15522].hh.b0:=128;eqtb[15522].hh.rh:=-1073741823;{:1382}end;
endif('INITEX'){:8}{1423:}synctexoffset:=28525;{:1423}end;
{58:}procedure println;var ii:integer;
begin case selector of 19:begin if nrestmultichr(kcodepos)>0 then for ii
:=0 to nrestmultichr(kcodepos)-1 do begin write(stdout,' ');
write(logfile,' ');end;writeln(stdout);writeln(logfile);termoffset:=0;
fileoffset:=0;end;
18:begin if nrestmultichr(kcodepos)>0 then for ii:=0 to nrestmultichr(
kcodepos)-1 do write(logfile,' ');writeln(logfile);fileoffset:=0;end;
17:begin if nrestmultichr(kcodepos)>0 then for ii:=0 to nrestmultichr(
kcodepos)-1 do write(stdout,' ');writeln(stdout);termoffset:=0;end;
16,20,21:;others:writeln(writefile[selector])end;kcodepos:=0;end;
{:58}{59:}procedure printchar(s:ASCIIcode);label 10;
begin if{250:}s=eqtb[28512].int{:250}then if selector<20 then begin
println;goto 10;end;
if(kcodepos=1)or((kcodepos>=9)and(kcodepos<=10))or((kcodepos>=17)and(
kcodepos<=19))then incr(kcodepos)else if iskanji1(xchr[s])then begin if(
ismultichr(4,1,xchr[s]))then kcodepos:=17 else if(ismultichr(3,1,xchr[s]
))then kcodepos:=9 else kcodepos:=1;
if(selector=19)or(selector=18)then if fileoffset>=maxprintline-
nrestmultichr(kcodepos)then begin writeln(logfile);fileoffset:=0;end;
if(selector=19)or(selector=17)then if termoffset>=maxprintline-
nrestmultichr(kcodepos)then begin writeln(stdout);termoffset:=0;end;
end else kcodepos:=0;case selector of 19:begin write(stdout,xchr[s]);
incr(termoffset);if termoffset=maxprintline then begin writeln(stdout);
termoffset:=0;end;write(logfile,xchr[s]);incr(fileoffset);
if fileoffset=maxprintline then begin writeln(logfile);fileoffset:=0;
end;end;18:begin write(logfile,xchr[s]);incr(fileoffset);
if fileoffset=maxprintline then println;end;
17:begin write(stdout,xchr[s]);incr(termoffset);
if termoffset=maxprintline then println;end;16:;
20:if tally<trickcount then begin trickbuf[tally mod errorline]:=s;
trickbuf2[tally mod errorline]:=kcodepos;end;
21:begin if poolptr<poolsize then begin strpool[poolptr]:=s;
incr(poolptr);end;end;others:write(writefile[selector],xchr[s])end;
incr(tally);10:end;{:59}{60:}procedure print(s:integer);label 10;
var j:poolpointer;nl:integer;
begin if s>=strptr then s:=260 else if s<256 then if s<0 then s:=260
else begin if selector>20 then begin printchar(s);goto 10;end;
if({250:}s=eqtb[28512].int{:250})then if selector<20 then begin println;
goto 10;end;nl:=eqtb[28512].int;eqtb[28512].int:=-1;j:=strstart[s];
while j<strstart[s+1]do begin printchar(strpool[j]);incr(j);end;
eqtb[28512].int:=nl;goto 10;end;j:=strstart[s];
while j<strstart[s+1]do begin printchar(strpool[j]);incr(j);end;10:end;
{:60}{61:}procedure slowprint(s:integer);var j:poolpointer;
begin if(s>=strptr)or(s<256)then print(s)else begin j:=strstart[s];
while j<strstart[s+1]do begin print(strpool[j]);incr(j);end;end;end;
{:61}{63:}procedure printnl(s:strnumber);
begin if((termoffset>0)and(odd(selector)))or((fileoffset>0)and(selector
>=18))then println;print(s);end;
{:63}{64:}procedure printesc(s:strnumber);var c:integer;
begin{249:}c:=eqtb[28508].int{:249};if c>=0 then if c<256 then print(c);
slowprint(s);end;{:64}{65:}procedure printthedigs(k:eightbits);
begin while k>0 do begin decr(k);
if dig[k]<10 then printchar(48+dig[k])else printchar(55+dig[k]);end;end;
{:65}{66:}procedure printint(n:integer);var k:0..23;m:integer;
begin k:=0;if n<0 then begin printchar(45);
if n>-100000000 then n:=-n else begin m:=-1-n;n:=m div 10;
m:=(m mod 10)+1;k:=1;if m<10 then dig[0]:=m else begin dig[0]:=0;
incr(n);end;end;end;repeat dig[k]:=n mod 10;n:=n div 10;incr(k);
until n=0;printthedigs(k);end;{:66}{268:}procedure printcs(p:integer);
begin if p<514 then if p>=257 then if p=513 then begin printesc(539);
printesc(540);printchar(32);end else begin printesc(p-257);
if eqtb[25636+p-257].hh.rh=11 then printchar(32);
end else if p<1 then printesc(541)else print(p-1)else if((p>=24526)and(p
<=29572))or(p>eqtbtop)then printesc(541)else if(hash[p].rh>=strptr)then
printesc(542)else begin printesc(hash[p].rh);printchar(32);end;end;
{:268}{269:}procedure sprintcs(p:halfword);
begin if p<514 then if p<257 then print(p-1)else if p<513 then printesc(
p-257)else begin printesc(539);printesc(540);
end else printesc(hash[p].rh);end;
{:269}{529:}procedure printfilename(n,a,e:integer);
var mustquote:boolean;j:poolpointer;begin mustquote:=false;
if a<>0 then begin j:=strstart[a];
while(not mustquote)and(j<strstart[a+1])do begin mustquote:=strpool[j]=
32;incr(j);end;end;if n<>0 then begin j:=strstart[n];
while(not mustquote)and(j<strstart[n+1])do begin mustquote:=strpool[j]=
32;incr(j);end;end;if e<>0 then begin j:=strstart[e];
while(not mustquote)and(j<strstart[e+1])do begin mustquote:=strpool[j]=
32;incr(j);end;end;if mustquote then printchar(34);
if a<>0 then for j:=strstart[a]to strstart[a+1]-1 do if strpool[j]<>34
then print(strpool[j]);
if n<>0 then for j:=strstart[n]to strstart[n+1]-1 do if strpool[j]<>34
then print(strpool[j]);
if e<>0 then for j:=strstart[e]to strstart[e+1]-1 do if strpool[j]<>34
then print(strpool[j]);if mustquote then printchar(34);end;
{:529}{710:}procedure printsize(s:integer);
begin if s=0 then printesc(431)else if s=16 then printesc(432)else
printesc(433);end;{:710}{1368:}procedure printwritewhatsit(s:strnumber;
p:halfword);begin printesc(s);
if mem[p+1].hh.lh<16 then printint(mem[p+1].hh.lh)else if mem[p+1].hh.lh
=16 then printchar(42)else printchar(45);end;
{:1368}{1395:}procedure printcsnames(hstart:integer;hfinish:integer);
var c,h:integer;
begin writeln(stderr,'fmtdebug:csnames from ',hstart,' to ',hfinish,':')
;for h:=hstart to hfinish do begin if hash[h].rh>0 then begin for c:=
strstart[hash[h].rh]to strstart[hash[h].rh+1]-1 do begin putbyte(strpool
[c],stderr);end;writeln(stderr,'|');end;end;end;
{:1395}{1398:}procedure printfileline;var level:0..maxinopen;
begin level:=inopen;
while(level>0)and(fullsourcefilenamestack[level]=0)do decr(level);
if level=0 then printnl(263)else begin printnl(344);
print(fullsourcefilenamestack[level]);print(58);
if level=inopen then printint(line)else printint(linestack[level+1]);
print(607);end;end;{:1398}{1500:}procedure printdir(dir:eightbits);
begin if dir=4 then printchar(89)else if dir=3 then printchar(84)else if
dir=1 then printchar(68)end;procedure printdirection(d:integer);
begin case abs(d)of 4:print(1121);3:print(1120);1:print(1122);end;
if d<0 then print(1438);print(1439);end;
{:1500}{1506:}procedure printkanji(s:KANJIcode);
begin s:=toBUFF(s mod 16777216);if BYTE1(s)<>0 then printchar(BYTE1(s));
if BYTE2(s)<>0 then printchar(BYTE2(s));
if BYTE3(s)<>0 then printchar(BYTE3(s));printchar(BYTE4(s));end;
function checkkcatcode(ct:integer):integer;
begin if((ct>=16)and(eqtb[25635].hh.rh=0))or(eqtb[25635].hh.rh=2)then
checkkcatcode:=1 else checkkcatcode:=0;end;
function checkecharrange(c:integer):integer;
begin if(c>=0)and(c<256)then checkecharrange:=1 else checkecharrange:=0;
end;{:1506}{79:}procedure normalizeselector;forward;procedure gettoken;
forward;procedure terminput;forward;procedure showcontext;forward;
procedure beginfilereading;forward;procedure openlogfile;forward;
procedure closefilesandterminate;forward;procedure clearforerrorprompt;
forward;procedure giveerrhelp;forward;
ifdef('TEXMF_DEBUG')procedure debughelp;forward;
endif('TEXMF_DEBUG'){:79}{82:}noreturn procedure jumpout;
begin closefilesandterminate;begin fflush(stdout);readyalready:=0;
if(history<>0)and(history<>1)then uexit(1)else uexit(0);end;end;
{:82}{83:}procedure error;label 22,10;var c:ASCIIcode;
s1,s2,s3,s4:integer;begin if history<2 then history:=2;printchar(46);
showcontext;if(haltonerrorp)then begin history:=3;jumpout;end;
if interaction=3 then{84:}while true do begin 22:clearforerrorprompt;
begin;print(265);terminput;end;if last=first then goto 10;
c:=buffer[first];if c>=97 then c:=c-32;
{85:}case c of 48,49,50,51,52,53,54,55,56,57:if deletionsallowed then
{89:}begin s1:=curtok;s2:=curcmd;s3:=curchr;s4:=alignstate;
alignstate:=1000000;OKtointerrupt:=false;
if(last>first+1)and(buffer[first+1]>=48)and(buffer[first+1]<=57)then c:=
c*10+buffer[first+1]-48*11 else c:=c-48;while c>0 do begin gettoken;
decr(c);end;curtok:=s1;curcmd:=s2;curchr:=s3;alignstate:=s4;
OKtointerrupt:=true;begin helpptr:=2;helpline[1]:=278;helpline[0]:=279;
end;showcontext;goto 22;end{:89};ifdef('TEXMF_DEBUG')68:begin debughelp;
goto 22;end;
endif('TEXMF_DEBUG')69:if baseptr>0 then begin editnamestart:=strstart[
inputstack[baseptr].namefield];
editnamelength:=strstart[inputstack[baseptr].namefield+1]-strstart[
inputstack[baseptr].namefield];editline:=line;jumpout;end;
72:{90:}begin if useerrhelp then begin giveerrhelp;useerrhelp:=false;
end else begin if helpptr=0 then begin helpptr:=2;helpline[1]:=280;
helpline[0]:=281;end;repeat decr(helpptr);print(helpline[helpptr]);
println;until helpptr=0;end;begin helpptr:=4;helpline[3]:=282;
helpline[2]:=281;helpline[1]:=283;helpline[0]:=284;end;goto 22;end{:90};
73:{88:}begin beginfilereading;
if last>first+1 then begin curinput.locfield:=first+1;buffer[first]:=32;
end else begin begin;print(277);terminput;end;curinput.locfield:=first;
end;first:=last;curinput.limitfield:=last-1;goto 10;end{:88};
81,82,83:{87:}begin errorcount:=0;interaction:=0+c-81;print(272);
case c of 81:begin printesc(273);decr(selector);end;82:printesc(274);
83:printesc(275);end;print(276);println;fflush(stdout);goto 10;end{:87};
88:begin interaction:=2;jumpout;end;others:end;{86:}begin print(266);
printnl(267);printnl(268);if baseptr>0 then print(269);
if deletionsallowed then printnl(270);printnl(271);end{:86}{:85};
end{:84};incr(errorcount);if errorcount=100 then begin printnl(264);
history:=3;jumpout;end;{91:}if interaction>0 then decr(selector);
if useerrhelp then begin println;giveerrhelp;
end else while helpptr>0 do begin decr(helpptr);
printnl(helpline[helpptr]);end;println;
if interaction>0 then incr(selector);println{:91};10:end;
{:83}{94:}noreturn procedure fatalerror(s:strnumber);
begin normalizeselector;begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(286);
end;begin helpptr:=1;helpline[0]:=s;end;
begin if interaction=3 then interaction:=2;if logopened then error;
ifdef('TEXMF_DEBUG')if interaction>0 then debughelp;
endif('TEXMF_DEBUG')history:=3;jumpout;end;end;
{:94}{95:}noreturn procedure overflow(s:strnumber;n:integer);
begin normalizeselector;begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(287);
end;print(s);printchar(61);printint(n);printchar(93);begin helpptr:=2;
helpline[1]:=288;helpline[0]:=289;end;
begin if interaction=3 then interaction:=2;if logopened then error;
ifdef('TEXMF_DEBUG')if interaction>0 then debughelp;
endif('TEXMF_DEBUG')history:=3;jumpout;end;end;
{:95}{96:}noreturn procedure confusion(s:strnumber);
begin normalizeselector;
if history<2 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(290);
end;print(s);printchar(41);begin helpptr:=1;helpline[0]:=291;end;
end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(292);
end;begin helpptr:=2;helpline[1]:=293;helpline[0]:=294;end;end;
begin if interaction=3 then interaction:=2;if logopened then error;
ifdef('TEXMF_DEBUG')if interaction>0 then debughelp;
endif('TEXMF_DEBUG')history:=3;jumpout;end;end;
{:96}{:4}{32:}{[36:]begin curinput.locfield:=first;
curinput.limitfield:=last-1;overflow(257,bufsize);end[:36]}
{:32}{38:}function initterminal:boolean;label 10;begin topenin;
if last>first then begin curinput.locfield:=first;
while(curinput.locfield<last)and(buffer[curinput.locfield]=' ')do incr(
curinput.locfield);
if curinput.locfield<last then begin initterminal:=true;goto 10;end;end;
while true do begin;write(stdout,'**');fflush(stdout);
if not inputln(stdin,true)then begin writeln(stdout);
writeln(stdout,'! End of file on the terminal... why?');
initterminal:=false;goto 10;end;curinput.locfield:=first;
while(curinput.locfield<last)and(buffer[curinput.locfield]=32)do incr(
curinput.locfield);
if curinput.locfield<last then begin initterminal:=true;goto 10;end;
writeln(stdout,'Please type the name of your input file.');end;10:end;
{:38}{44:}function makestring:strnumber;
begin if strptr=maxstrings then overflow(259,maxstrings-initstrptr);
incr(strptr);strstart[strptr]:=poolptr;makestring:=strptr-1;end;
{:44}{46:}function streqbuf(s:strnumber;k:integer):boolean;label 45;
var j:poolpointer;result:boolean;begin j:=strstart[s];
while j<strstart[s+1]do begin if strpool[j]<>buffer[k]then begin result
:=false;goto 45;end;incr(j);incr(k);end;result:=true;
45:streqbuf:=result;end;
{:46}{47:}function streqstr(s,t:strnumber):boolean;label 45;
var j,k:poolpointer;result:boolean;begin result:=false;
if(strstart[s+1]-strstart[s])<>(strstart[t+1]-strstart[t])then goto 45;
j:=strstart[s];k:=strstart[t];
while j<strstart[s+1]do begin if strpool[j]<>strpool[k]then goto 45;
incr(j);incr(k);end;result:=true;45:streqstr:=result;end;
{:47}{48:}{1402:}function searchstring(search:strnumber):strnumber;
label 40;var result:strnumber;s:strnumber;len:integer;begin result:=0;
len:=(strstart[search+1]-strstart[search]);
if len=0 then begin result:=344;goto 40;end else begin s:=search-1;
while s>255 do begin if(strstart[s+1]-strstart[s])=len then if streqstr(
s,search)then begin result:=s;goto 40;end;decr(s);end;end;
40:searchstring:=result;end;
{:1402}{1403:}function slowmakestring:strnumber;label 10;
var s:strnumber;t:strnumber;begin t:=makestring;s:=searchstring(t);
if s>0 then begin begin decr(strptr);poolptr:=strstart[strptr];end;
slowmakestring:=s;goto 10;end;slowmakestring:=t;10:end;
{:1403}ifdef('INITEX')function getstringsstarted:boolean;label 30,10;
var k,l:KANJIcode;g:strnumber;begin poolptr:=0;strptr:=0;strstart[0]:=0;
{49:}for k:=0 to 255 do begin if({50:}not(ismultiprn(k)or xprn[k]){:50})
then begin begin strpool[poolptr]:=94;incr(poolptr);end;
begin strpool[poolptr]:=94;incr(poolptr);end;
if k<64 then begin strpool[poolptr]:=k+64;incr(poolptr);
end else if k<128 then begin strpool[poolptr]:=k-64;incr(poolptr);
end else begin l:=k div 16;if l<10 then begin strpool[poolptr]:=l+48;
incr(poolptr);end else begin strpool[poolptr]:=l+87;incr(poolptr);end;
l:=k mod 16;if l<10 then begin strpool[poolptr]:=l+48;incr(poolptr);
end else begin strpool[poolptr]:=l+87;incr(poolptr);end;end;
end else begin strpool[poolptr]:=k;incr(poolptr);end;g:=makestring;
end{:49};{52:}g:=loadpoolstrings((poolsize-stringvacancies));
if g=0 then begin;writeln(stdout,'! You have to increase POOLSIZE.');
getstringsstarted:=false;goto 10;end;getstringsstarted:=true;{:52};
10:end;endif('INITEX'){:48}{67:}procedure printtwo(n:integer);
begin n:=abs(n)mod 100;printchar(48+(n div 10));
printchar(48+(n mod 10));end;{:67}{68:}procedure printhex(n:integer);
var k:0..22;begin k:=0;printchar(34);repeat dig[k]:=n mod 16;
n:=n div 16;incr(k);until n=0;printthedigs(k);end;
{:68}{70:}procedure printromanint(n:integer);label 10;
var j,k:poolpointer;u,v:nonnegativeinteger;begin j:=strstart[261];
v:=1000;while true do begin while n>=v do begin printchar(strpool[j]);
n:=n-v;end;if n<=0 then goto 10;k:=j+2;u:=v div(strpool[k-1]-48);
if strpool[k-1]=50 then begin k:=k+2;u:=u div(strpool[k-1]-48);end;
if n+u>=v then begin printchar(strpool[k]);n:=n+u;end else begin j:=j+2;
v:=v div(strpool[j-1]-48);end;end;10:end;
{:70}{71:}procedure printcurrentstring;var j:poolpointer;
begin j:=strstart[strptr];
while j<poolptr do begin printchar(strpool[j]);incr(j);end;end;
{:71}{72:}procedure terminput;var k:0..bufsize;begin fflush(stdout);
if not inputln(stdin,true)then fatalerror(262);termoffset:=0;
decr(selector);
if last<>first then for k:=first to last-1 do print(buffer[k]);println;
incr(selector);end;{:72}{92:}procedure interror(n:integer);
begin print(285);printint(n);printchar(41);error;end;
{:92}{93:}procedure normalizeselector;
begin if logopened then selector:=19 else selector:=17;
if jobname=0 then openlogfile;if interaction=0 then decr(selector);end;
{:93}{99:}procedure pauseforinstructions;
begin if OKtointerrupt then begin interaction:=3;
if(selector=18)or(selector=16)then incr(selector);
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(295);
end;begin helpptr:=3;helpline[2]:=296;helpline[1]:=297;helpline[0]:=298;
end;deletionsallowed:=false;error;deletionsallowed:=true;interrupt:=0;
end;end;{:99}{101:}function half(x:integer):integer;
begin if odd(x)then half:=(x+1)div 2 else half:=x div 2;end;
{:101}{103:}function rounddecimals(k:smallnumber):scaled;var a:integer;
begin a:=0;while k>0 do begin decr(k);a:=(a+dig[k]*131072)div 10;end;
rounddecimals:=(a+1)div 2;end;
{:103}{104:}procedure printscaled(s:scaled);var delta:scaled;
begin if s<0 then begin printchar(45);s:=-s;end;printint(s div 65536);
printchar(46);s:=10*(s mod 65536)+5;delta:=10;
repeat if delta>65536 then s:=s-17232;printchar(48+(s div 65536));
s:=10*(s mod 65536);delta:=delta*10;until s<=delta;end;
{:104}{106:}function multandadd(n:integer;x,y,maxanswer:scaled):scaled;
begin if n<0 then begin x:=-x;n:=-n;end;
if n=0 then multandadd:=y else if((x<=(maxanswer-y)div n)and(-x<=(
maxanswer+y)div n))then multandadd:=n*x+y else begin aritherror:=true;
multandadd:=0;end;end;{:106}{107:}function xovern(x:scaled;
n:integer):scaled;var negative:boolean;begin negative:=false;
if n=0 then begin aritherror:=true;xovern:=0;texremainder:=x;
end else begin if n<0 then begin x:=-x;n:=-n;negative:=true;end;
if x>=0 then begin xovern:=x div n;texremainder:=x mod n;
end else begin xovern:=-((-x)div n);texremainder:=-((-x)mod n);end;end;
if negative then texremainder:=-texremainder;end;
{:107}{108:}function xnoverd(x:scaled;n,d:integer):scaled;
var positive:boolean;t,u,v:nonnegativeinteger;
begin if x>=0 then positive:=true else begin x:=-x;positive:=false;end;
t:=(x mod 32768)*n;u:=(x div 32768)*n+(t div 32768);
v:=(u mod d)*32768+(t mod 32768);
if u div d>=32768 then aritherror:=true else u:=32768*(u div d)+(v div d
);if positive then begin xnoverd:=u;texremainder:=v mod d;
end else begin xnoverd:=-u;texremainder:=-(v mod d);end;end;
{:108}{109:}function badness(t,s:scaled):halfword;var r:integer;
begin if t=0 then badness:=0 else if s<=0 then badness:=10000 else begin
if t<=7230584 then r:=(t*297)div s else if s>=1663497 then r:=t div(s
div 297)else r:=t;
if r>1290 then badness:=10000 else badness:=(r*r*r+131072)div 262144;
end;end;
{:109}{115:}ifdef('TEXMF_DEBUG')procedure printword(w:memoryword);
begin printint(w.int);printchar(32);printscaled(w.int);printchar(32);
printscaled(round(65536*w.gr));println;printint(w.hh.lh);printchar(61);
printint(w.hh.b0);printchar(58);printint(w.hh.b1);printchar(59);
printint(w.hh.rh);printchar(32);printint(w.qqqq.b0);printchar(58);
printint(w.qqqq.b1);printchar(58);printint(w.qqqq.b2);printchar(58);
printint(w.qqqq.b3);end;
endif('TEXMF_DEBUG'){:115}{120:}{298:}procedure showtokenlist(p,q:
integer;l:integer);label 10;var m,c:integer;matchchr:ASCIIcode;
n:ASCIIcode;begin matchchr:=35;n:=48;tally:=0;
while(p<>-1073741823)and(tally<l)do begin if p=q then{326:}begin
firstcount:=tally;kcp:=trickbuf2[(firstcount-1)mod errorline];
if(firstcount>0)and(kcp>0)then firstcount:=firstcount+nrestmultichr(kcp)
;trickcount:=firstcount+1+errorline-halferrorline;
if trickcount<errorline then trickcount:=errorline;end{:326};
{299:}if(p<himemmin)or(p>memend)then begin printesc(313);goto 10;end;
if mem[p].hh.lh>=536870911 then printcs(mem[p].hh.lh-536870911)else
begin if checkkanji(mem[p].hh.lh)then begin m:=mem[p].hh.lh div 16777216
;c:=mem[p].hh.lh mod 16777216;end else begin m:=mem[p].hh.lh div 256;
c:=mem[p].hh.lh mod 256;end;
if(m<16)and(c>256)then printesc(593)else{300:}case m of 16,17,18,19:
printkanji(c);1,2,3,4,7,8,10,11,12:print(c);6:begin print(c);print(c);
end;5:begin print(matchchr);
if c<=9 then printchar(c+48)else begin printchar(33);goto 10;end;end;
13:begin matchchr:=c;print(c);incr(n);printchar(n);if n>57 then goto 10;
end;14:print(594);others:printesc(593)end{:300};end{:299};
p:=mem[p].hh.rh;end;if p<>-1073741823 then printesc(592);10:end;
{:298}{312:}procedure runaway;var p:halfword;
begin if scannerstatus>1 then begin case scannerstatus of 2:begin
printnl(608);p:=defref;end;3:begin printnl(609);p:=memtop-3;end;
4:begin printnl(610);p:=memtop-4;end;5:begin printnl(611);p:=defref;end;
end;printchar(63);println;
showtokenlist(mem[p].hh.rh,-1073741823,errorline-10);end;end;
{:312}{:120}{121:}function getavail:halfword;var p:halfword;
begin p:=avail;
if p<>-1073741823 then avail:=mem[avail].hh.rh else if memend<memmax
then begin incr(memend);p:=memend;end else begin decr(himemmin);
p:=himemmin;if himemmin<=lomemmax then begin runaway;
overflow(299,memmax+1-memmin);end;end;mem[p].hh.rh:=-1073741823;
ifdef('STAT')incr(dynused);endif('STAT')getavail:=p;end;
{:121}{124:}procedure flushlist(p:halfword);var q,r:halfword;
begin if p<>-1073741823 then begin r:=p;repeat q:=r;r:=mem[r].hh.rh;
ifdef('STAT')decr(dynused);endif('STAT')until r=-1073741823;
mem[q].hh.rh:=avail;avail:=p;end;end;
{:124}{126:}function getnode(s:integer):halfword;label 40,10,20;
var p:halfword;q:halfword;r:integer;t:integer;begin 20:p:=rover;
repeat{128:}q:=p+mem[p].hh.lh;
while(mem[q].hh.rh=1073741823)do begin t:=mem[q+1].hh.rh;
if q=rover then rover:=t;mem[t+1].hh.lh:=mem[q+1].hh.lh;
mem[mem[q+1].hh.lh+1].hh.rh:=t;q:=q+mem[q].hh.lh;end;r:=q-s;
if r>p+1 then{129:}begin mem[p].hh.lh:=r-p;rover:=p;goto 40;end{:129};
if r=p then if mem[p+1].hh.rh<>p then{130:}begin rover:=mem[p+1].hh.rh;
t:=mem[p+1].hh.lh;mem[rover+1].hh.lh:=t;mem[t+1].hh.rh:=rover;goto 40;
end{:130};mem[p].hh.lh:=q-p{:128};p:=mem[p+1].hh.rh;until p=rover;
if s=1073741824 then begin getnode:=1073741823;goto 10;end;
if lomemmax+2<himemmin then if lomemmax+2<=membot+1073741823 then{127:}
begin if himemmin-lomemmax>=1998 then t:=lomemmax+1000 else t:=lomemmax
+1+(himemmin-lomemmax)div 2;p:=mem[rover+1].hh.lh;q:=lomemmax;
mem[p+1].hh.rh:=q;mem[rover+1].hh.lh:=q;
if t>membot+1073741823 then t:=membot+1073741823;mem[q+1].hh.rh:=rover;
mem[q+1].hh.lh:=p;mem[q].hh.rh:=1073741823;mem[q].hh.lh:=t-lomemmax;
lomemmax:=t;mem[lomemmax].hh.rh:=-1073741823;
mem[lomemmax].hh.lh:=-1073741823;rover:=q;goto 20;end{:127};
overflow(299,memmax+1-memmin);40:mem[r].hh.rh:=-1073741823;
ifdef('STAT')varused:=varused+s;
endif('STAT'){1427:}if s>=4 then begin mem[r+s-2].int:=curinput.
synctextagfield;mem[r+s-1].int:=line;end;{:1427};getnode:=r;10:end;
{:126}{131:}procedure freenode(p:halfword;s:halfword);var q:halfword;
begin mem[p].hh.lh:=s;mem[p].hh.rh:=1073741823;q:=mem[rover+1].hh.lh;
mem[p+1].hh.lh:=q;mem[p+1].hh.rh:=rover;mem[rover+1].hh.lh:=p;
mem[q+1].hh.rh:=p;ifdef('STAT')varused:=varused-s;endif('STAT')end;
{:131}{132:}ifdef('INITEX')procedure sortavail;var p,q,r:halfword;
oldrover:halfword;begin p:=getnode(1073741824);p:=mem[rover+1].hh.rh;
mem[rover+1].hh.rh:=1073741823;oldrover:=rover;
while p<>oldrover do{133:}if p<rover then begin q:=p;p:=mem[q+1].hh.rh;
mem[q+1].hh.rh:=rover;rover:=q;end else begin q:=rover;
while mem[q+1].hh.rh<p do q:=mem[q+1].hh.rh;r:=mem[p+1].hh.rh;
mem[p+1].hh.rh:=mem[q+1].hh.rh;mem[q+1].hh.rh:=p;p:=r;end{:133};
p:=rover;
while mem[p+1].hh.rh<>1073741823 do begin mem[mem[p+1].hh.rh+1].hh.lh:=p
;p:=mem[p+1].hh.rh;end;mem[p+1].hh.rh:=rover;mem[rover+1].hh.lh:=p;end;
endif('INITEX'){:132}{137:}function newnullbox:halfword;var p:halfword;
begin p:=getnode(10);mem[p].hh.b0:=0;mem[p].hh.b1:=0;mem[p+1].int:=0;
mem[p+2].int:=0;mem[p+3].int:=0;mem[p+4].int:=0;
mem[p+5].hh.rh:=-1073741823;mem[p+5].hh.b0:=0;mem[p+5].hh.b1:=0;
mem[p+6].gr:=0.0;mem[p+7].hh.rh:=membot;mem[p+7].hh.lh:=membot;
incr(mem[membot].hh.rh);incr(mem[membot].hh.rh);newnullbox:=p;end;
{:137}{139:}function newdirnode(b:halfword;dir:eightbits):halfword;
var p:halfword;begin if mem[b].hh.b0>1 then confusion(300);
p:=newnullbox;mem[p].hh.b0:=2;mem[p].hh.b1:=dir;
case(mem[b].hh.b1)of 4:{140:}case dir of 3:begin mem[p+1].int:=mem[b+3].
int+mem[b+2].int;mem[p+2].int:=mem[b+1].int/2;
mem[p+3].int:=mem[b+1].int-mem[p+2].int;end;
1:begin mem[p+1].int:=mem[b+3].int+mem[b+2].int;mem[p+2].int:=0;
mem[p+3].int:=mem[b+1].int;end;others:confusion(302);end{:140};
3:{141:}case dir of 4:begin mem[p+1].int:=mem[b+3].int+mem[b+2].int;
mem[p+2].int:=0;mem[p+3].int:=mem[b+1].int;end;
1:begin mem[p+1].int:=mem[b+1].int;mem[p+2].int:=mem[b+3].int;
mem[p+3].int:=mem[b+2].int;end;others:confusion(303);end{:141};
1:{142:}case dir of 4:begin mem[p+1].int:=mem[b+3].int+mem[b+2].int;
mem[p+2].int:=0;mem[p+3].int:=mem[b+1].int;end;
3:begin mem[p+1].int:=mem[b+1].int;mem[p+2].int:=mem[b+3].int;
mem[p+3].int:=mem[b+2].int;end;others:confusion(304);end{:142};
others:confusion(301);end;mem[b].hh.rh:=-1073741823;mem[p+5].hh.rh:=b;
newdirnode:=p;end;{:139}{144:}function newrule:halfword;var p:halfword;
begin p:=getnode(6);mem[p].hh.b0:=3;mem[p].hh.b1:=0;
mem[p+1].int:=-1073741824;mem[p+2].int:=-1073741824;
mem[p+3].int:=-1073741824;newrule:=p;end;
{:144}{150:}function newligature(f:internalfontnumber;c:quarterword;
q:halfword):halfword;var p:halfword;begin p:=getnode(2);mem[p].hh.b0:=8;
mem[p+1].hh.b0:=f;mem[p+1].hh.b1:=c;mem[p+1].hh.rh:=q;mem[p].hh.b1:=0;
newligature:=p;end;function newligitem(c:quarterword):halfword;
var p:halfword;begin p:=getnode(2);mem[p].hh.b1:=c;
mem[p+1].hh.rh:=-1073741823;newligitem:=p;end;
{:150}{151:}function newdisc:halfword;var p:halfword;
begin p:=getnode(2);mem[p].hh.b0:=9;mem[p].hh.b1:=0;
mem[p+1].hh.lh:=-1073741823;mem[p+1].hh.rh:=-1073741823;newdisc:=p;end;
{:151}{153:}function newmath(w:scaled;s:smallnumber):halfword;
var p:halfword;begin p:=getnode(4);mem[p].hh.b0:=11;mem[p].hh.b1:=s;
mem[p+1].int:=w;newmath:=p;end;
{:153}{157:}function newspec(p:halfword):halfword;var q:halfword;
begin q:=getnode(4);mem[q]:=mem[p];mem[q].hh.rh:=-1073741823;
mem[q+1].int:=mem[p+1].int;mem[q+2].int:=mem[p+2].int;
mem[q+3].int:=mem[p+3].int;newspec:=q;end;
{:157}{158:}function newparamglue(n:smallnumber):halfword;
var p:halfword;q:halfword;begin p:=getnode(4);mem[p].hh.b0:=12;
mem[p].hh.b1:=n+1;mem[p+1].hh.rh:=-1073741823;
q:={230:}eqtb[24527+n].hh.rh{:230};mem[p+1].hh.lh:=q;incr(mem[q].hh.rh);
newparamglue:=p;end;{:158}{159:}function newglue(q:halfword):halfword;
var p:halfword;begin p:=getnode(4);mem[p].hh.b0:=12;mem[p].hh.b1:=0;
mem[p+1].hh.rh:=-1073741823;mem[p+1].hh.lh:=q;incr(mem[q].hh.rh);
newglue:=p;end;
{:159}{160:}function newskipparam(n:smallnumber):halfword;
var p:halfword;begin tempptr:=newspec({230:}eqtb[24527+n].hh.rh{:230});
p:=newglue(tempptr);mem[tempptr].hh.rh:=-1073741823;mem[p].hh.b1:=n+1;
newskipparam:=p;end;{:160}{162:}function newkern(w:scaled):halfword;
var p:halfword;begin p:=getnode(4);mem[p].hh.b0:=13;mem[p].hh.b1:=0;
mem[p+1].int:=w;newkern:=p;end;
{:162}{164:}function newpenalty(m:integer):halfword;var p:halfword;
begin p:=getnode(4);mem[p].hh.b0:=14;mem[p].hh.b1:=0;mem[p+1].int:=m;
newpenalty:=p;end;
{:164}{173:}ifdef('TEXMF_DEBUG')procedure checkmem(printlocs:boolean);
label 31,32;var p,q:halfword;clobbered:boolean;
begin for p:=memmin to lomemmax do freearr[p]:=false;
for p:=himemmin to memend do freearr[p]:=false;{174:}p:=avail;
q:=-1073741823;clobbered:=false;
while p<>-1073741823 do begin if(p>memend)or(p<himemmin)then clobbered:=
true else if freearr[p]then clobbered:=true;
if clobbered then begin printnl(305);printint(q);goto 31;end;
freearr[p]:=true;q:=p;p:=mem[q].hh.rh;end;31:{:174};{175:}p:=rover;
q:=-1073741823;clobbered:=false;
repeat if(p>=lomemmax)or(p<memmin)then clobbered:=true else if(mem[p+1].
hh.rh>=lomemmax)or(mem[p+1].hh.rh<memmin)then clobbered:=true else if
not((mem[p].hh.rh=1073741823))or(mem[p].hh.lh<2)or(p+mem[p].hh.lh>
lomemmax)or(mem[mem[p+1].hh.rh+1].hh.lh<>p)then clobbered:=true;
if clobbered then begin printnl(306);printint(q);goto 32;end;
for q:=p to p+mem[p].hh.lh-1 do begin if freearr[q]then begin printnl(
307);printint(q);goto 32;end;freearr[q]:=true;end;q:=p;
p:=mem[p+1].hh.rh;until p=rover;32:{:175};{176:}p:=memmin;
while p<=lomemmax do begin if(mem[p].hh.rh=1073741823)then begin printnl
(308);printint(p);end;while(p<=lomemmax)and not freearr[p]do incr(p);
while(p<=lomemmax)and freearr[p]do incr(p);end{:176};
if printlocs then{177:}begin printnl(309);
for p:=memmin to lomemmax do if not freearr[p]and((p>waslomax)or wasfree
[p])then begin printchar(32);printint(p);end;
for p:=himemmin to memend do if not freearr[p]and((p<washimin)or(p>
wasmemend)or wasfree[p])then begin printchar(32);printint(p);end;
end{:177};for p:=memmin to lomemmax do wasfree[p]:=freearr[p];
for p:=himemmin to memend do wasfree[p]:=freearr[p];wasmemend:=memend;
waslomax:=lomemmax;washimin:=himemmin;end;
endif('TEXMF_DEBUG'){:173}{178:}ifdef('TEXMF_DEBUG')procedure searchmem(
p:halfword);var q:integer;
begin for q:=memmin to lomemmax do begin if mem[q].hh.rh=p then begin
printnl(310);printint(q);printchar(41);end;
if mem[q].hh.lh=p then begin printnl(311);printint(q);printchar(41);end;
end;
for q:=himemmin to memend do begin if mem[q].hh.rh=p then begin printnl(
310);printint(q);printchar(41);end;
if mem[q].hh.lh=p then begin printnl(311);printint(q);printchar(41);end;
end;
{261:}for q:=1 to 25581 do begin if eqtb[q].hh.rh=p then begin printnl(
536);printint(q);printchar(41);end;end{:261};
{291:}if saveptr>0 then for q:=0 to saveptr-1 do begin if savestack[q].
hh.rh=p then begin printnl(584);printint(q);printchar(41);end;end{:291};
{944:}for q:=0 to hyphsize do begin if hyphlist[q]=p then begin printnl(
997);printint(q);printchar(41);end;end{:944};end;
endif('TEXMF_DEBUG'){:178}{180:}procedure shortdisplay(p:integer);
var n:integer;
begin while p>memmin do begin if(p>=himemmin)then begin if p<=memend
then begin if mem[p].hh.b0<>fontinshortdisplay then begin if(mem[p].hh.
b0>fontmax)then printchar(42)else{273:}printesc(hash[15525+mem[p].hh.b0]
.rh){:273};printchar(32);fontinshortdisplay:=mem[p].hh.b0;end;
if fontdir[mem[p].hh.b0]<>0 then begin p:=mem[p].hh.rh;
printkanji(mem[p].hh.lh);end else print(mem[p].hh.b1);end;
end else{181:}case mem[p].hh.b0 of 0,1,2,4,10,6,7,15:print(312);
3:printchar(124);12:if mem[p+1].hh.lh<>membot then printchar(32);
11:printchar(36);8:shortdisplay(mem[p+1].hh.rh);
9:begin shortdisplay(mem[p+1].hh.lh);shortdisplay(mem[p+1].hh.rh);
n:=mem[p].hh.b1;
while n>0 do begin if mem[p].hh.rh<>-1073741823 then p:=mem[p].hh.rh;
decr(n);end;end;others:end{:181};p:=mem[p].hh.rh;end;end;
{:180}{182:}procedure printfontandchar(p:integer);
begin if p>memend then printesc(313)else begin if(mem[p].hh.b0>fontmax)
then printchar(42)else{273:}printesc(hash[15525+mem[p].hh.b0].rh){:273};
printchar(32);if fontdir[mem[p].hh.b0]<>0 then begin p:=mem[p].hh.rh;
printkanji(mem[p].hh.lh);end else print(mem[p].hh.b1);end;end;
procedure printmark(p:integer);begin printchar(123);
if(p<himemmin)or(p>memend)then printesc(313)else showtokenlist(mem[p].hh
.rh,-1073741823,maxprintline-10);printchar(125);end;
procedure printruledimen(d:scaled);
begin if(d=-1073741824)then printchar(42)else printscaled(d);end;
{:182}{183:}procedure printglue(d:scaled;order:integer;s:strnumber);
begin printscaled(d);
if(order<0)or(order>3)then print(314)else if order>0 then begin print(
315);while order>1 do begin printchar(108);decr(order);end;
end else if s<>0 then print(s);end;
{:183}{184:}procedure printspec(p:integer;s:strnumber);
begin if(p<memmin)or(p>=lomemmax)then printchar(42)else begin
printscaled(mem[p+1].int);if s<>0 then print(s);
if mem[p+2].int<>0 then begin print(316);
printglue(mem[p+2].int,mem[p].hh.b0,s);end;
if mem[p+3].int<>0 then begin print(317);
printglue(mem[p+3].int,mem[p].hh.b1,s);end;end;end;
{:184}{185:}{702:}procedure printfamandchar(p:halfword;t:smallnumber);
var cx:KANJIcode;begin printesc(488);printint(mem[p].hh.b0);
printchar(32);
if t=1 then print(mem[p].hh.b1)else begin cx:=mem[p+3].hh.lh;
printkanji(cx);end;end;procedure printdelimiter(p:halfword);
var a:integer;begin a:=mem[p].qqqq.b0*256+mem[p].qqqq.b1;
a:=a*4096+mem[p].qqqq.b2*256+mem[p].qqqq.b3;
if a<0 then printint(a)else printhex(a);end;
{:702}{703:}procedure showinfo;forward;
procedure printsubsidiarydata(p:halfword;c:ASCIIcode);
begin if(poolptr-strstart[strptr])>=depththreshold then begin if mem[p].
hh.rh<>0 then print(318);end else begin begin strpool[poolptr]:=c;
incr(poolptr);end;tempptr:=p;case mem[p].hh.rh of 1,6:begin println;
printcurrentstring;printfamandchar(p,mem[p].hh.rh);end;2,3:showinfo;
4:if mem[p].hh.lh=-1073741823 then begin println;printcurrentstring;
print(916);end else showinfo;others:end;decr(poolptr);end;end;
{:703}{705:}procedure printstyle(c:integer);
begin case c div 2 of 0:printesc(917);1:printesc(918);2:printesc(919);
3:printesc(920);others:print(921)end;end;
{:705}{231:}procedure printskipparam(n:integer);
begin case n of 0:printesc(392);1:printesc(393);2:printesc(394);
3:printesc(395);4:printesc(396);5:printesc(397);6:printesc(398);
7:printesc(399);8:printesc(400);9:printesc(401);10:printesc(402);
11:printesc(403);12:printesc(404);13:printesc(405);14:printesc(406);
17:printesc(407);18:printesc(408);19:printesc(409);15:printesc(410);
16:printesc(411);20:print(412);others:print(413)end;end;
{:231}{:185}{188:}procedure shownodelist(p:integer);label 10;
var n:integer;g:real;
begin if(poolptr-strstart[strptr])>depththreshold then begin if p>
-1073741823 then print(318);goto 10;end;n:=0;
while p>memmin do begin println;printcurrentstring;
if p>memend then begin print(319);goto 10;end;incr(n);
if n>breadthmax then begin print(320);goto 10;end;
{189:}if(p>=himemmin)then begin printfontandchar(p);
if fontdir[mem[p].hh.b0]<>0 then p:=mem[p].hh.rh end else case mem[p].hh
.b0 of 0,1,2,15:{190:}begin case mem[p].hh.b0 of 0:printesc(104);
1:printesc(118);2:printesc(323);others:printesc(324)end;print(325);
printscaled(mem[p+3].int);printchar(43);printscaled(mem[p+2].int);
print(326);printscaled(mem[p+1].int);
if mem[p].hh.b0=15 then{191:}begin if mem[p].hh.b1<>0 then begin print(
285);printint(mem[p].hh.b1+1);print(329);end;
if mem[p+6].int<>0 then begin print(330);
printglue(mem[p+6].int,mem[p+5].hh.b1,0);end;
if mem[p+4].int<>0 then begin print(331);
printglue(mem[p+4].int,mem[p+5].hh.b0,0);end;
end{:191}else begin{192:}g:=mem[p+6].gr;
if(g<>0.0)and(mem[p+5].hh.b0<>0)then begin print(332);
if mem[p+5].hh.b0=2 then print(333);
if fabs(g)>20000.0 then begin if g>0.0 then printchar(62)else print(334)
;printglue(20000*65536,mem[p+5].hh.b1,0);
end else printglue(round(65536*g),mem[p+5].hh.b1,0);end{:192};
if mem[p+4].int<>0 then begin print(327);printscaled(mem[p+4].int);end;
if(mem[p].hh.b1)<>0 then begin print(328);
printdirection((mem[p].hh.b1));end;end;begin begin strpool[poolptr]:=46;
incr(poolptr);end;shownodelist(mem[p+5].hh.rh);decr(poolptr);end;
end{:190};3:{193:}begin printesc(335);printruledimen(mem[p+3].int);
printchar(43);printruledimen(mem[p+2].int);print(326);
printruledimen(mem[p+1].int);end{:193};4:{194:}begin printesc(336);
printint(mem[p].hh.b1);printdir(mem[p+5].hh.b1);print(337);
printscaled(mem[p+3].int);print(338);printspec(mem[p+4].hh.rh,0);
printchar(44);printscaled(mem[p+2].int);print(339);
printint(mem[p+1].int);begin begin strpool[poolptr]:=46;incr(poolptr);
end;shownodelist(mem[p+4].hh.lh);decr(poolptr);end;end{:194};
10:{1369:}case mem[p].hh.b1 of 0:begin printwritewhatsit(1370,p);
printchar(61);
printfilename(mem[p+1].hh.rh,mem[p+2].hh.lh,mem[p+2].hh.rh);end;
1:begin printwritewhatsit(632,p);printmark(mem[p+1].hh.rh);end;
2:printwritewhatsit(1371,p);3:begin printesc(1372);
printmark(mem[p+1].hh.rh);end;4:begin printesc(1374);
printint(mem[p+1].hh.rh);print(1377);printint(mem[p+1].hh.b0);
printchar(44);printint(mem[p+1].hh.b1);printchar(41);end;
others:print(1378)end{:1369};5:begin printesc(321);
printscaled(mem[p+1].int);end;
12:{195:}if mem[p].hh.b1>=100 then{196:}begin printesc(344);
if mem[p].hh.b1=101 then printchar(99)else if mem[p].hh.b1=102 then
printchar(120);print(345);printspec(mem[p+1].hh.lh,0);
begin begin strpool[poolptr]:=46;incr(poolptr);end;
shownodelist(mem[p+1].hh.rh);decr(poolptr);end;
end{:196}else begin printesc(340);
if mem[p].hh.b1<>0 then begin printchar(40);
if mem[p].hh.b1<98 then printskipparam(mem[p].hh.b1-1)else if mem[p].hh.
b1=98 then printesc(341)else printesc(342);printchar(41);end;
if mem[p].hh.b1<>98 then begin printchar(32);
if mem[p].hh.b1<98 then printspec(mem[p+1].hh.lh,0)else printspec(mem[p
+1].hh.lh,343);end;end{:195};
13:{197:}if mem[p].hh.b1<>99 then begin printesc(346);
if mem[p].hh.b1<>0 then printchar(32);printscaled(mem[p+1].int);
if mem[p].hh.b1=2 then print(347);end else begin printesc(348);
printscaled(mem[p+1].int);print(343);end{:197};
11:{198:}begin printesc(349);
if mem[p].hh.b1=0 then print(350)else print(351);
if mem[p+1].int<>0 then begin print(352);printscaled(mem[p+1].int);end;
end{:198};8:{199:}begin printfontandchar(p+1);print(353);
if mem[p].hh.b1>1 then printchar(124);
fontinshortdisplay:=mem[p+1].hh.b0;shortdisplay(mem[p+1].hh.rh);
if odd(mem[p].hh.b1)then printchar(124);printchar(41);end{:199};
14:{200:}begin printesc(354);printint(mem[p+1].int);
if mem[p].hh.b1=1 then print(355)else if mem[p].hh.b1=2 then print(356);
end{:200};9:{201:}begin printesc(357);
if mem[p].hh.b1>0 then begin print(358);printint(mem[p].hh.b1);end;
begin begin strpool[poolptr]:=46;incr(poolptr);end;
shownodelist(mem[p+1].hh.lh);decr(poolptr);end;
begin strpool[poolptr]:=124;incr(poolptr);end;
shownodelist(mem[p+1].hh.rh);decr(poolptr);end{:201};
6:{202:}begin printesc(359);printmark(mem[p+1].int);end{:202};
7:{203:}begin printesc(360);begin begin strpool[poolptr]:=46;
incr(poolptr);end;shownodelist(mem[p+1].int);decr(poolptr);end;
end{:203};{701:}16:printstyle(mem[p].hh.b1);
17:{706:}begin printesc(563);begin strpool[poolptr]:=68;incr(poolptr);
end;shownodelist(mem[p+1].hh.lh);decr(poolptr);
begin strpool[poolptr]:=84;incr(poolptr);end;
shownodelist(mem[p+1].hh.rh);decr(poolptr);begin strpool[poolptr]:=83;
incr(poolptr);end;shownodelist(mem[p+2].hh.lh);decr(poolptr);
begin strpool[poolptr]:=115;incr(poolptr);end;
shownodelist(mem[p+2].hh.rh);decr(poolptr);end{:706};
18,19,20,21,22,23,24,25,26,29,28,31,30,32,33:{707:}begin case mem[p].hh.
b0 of 18:printesc(922);19:printesc(923);20:printesc(924);
21:printesc(925);22:printesc(926);23:printesc(927);24:printesc(928);
25:printesc(929);29:printesc(930);28:printesc(931);31:printesc(577);
26:begin printesc(571);printdelimiter(p+5);end;30:begin printesc(543);
printfamandchar(p+5,1);end;32:begin printesc(932);printdelimiter(p+1);
end;33:begin printesc(933);printdelimiter(p+1);end;end;
if mem[p].hh.b1<>0 then if mem[p].hh.b1=1 then printesc(934)else
printesc(935);if mem[p].hh.b0<32 then printsubsidiarydata(p+1,46);
printsubsidiarydata(p+2,94);printsubsidiarydata(p+3,95);end{:707};
27:{708:}begin printesc(936);
if mem[p+1].int=1073741824 then print(937)else printscaled(mem[p+1].int)
;
if(mem[p+5].qqqq.b0<>0)or(mem[p+5].qqqq.b1<>0)or(mem[p+5].qqqq.b2<>0)or(
mem[p+5].qqqq.b3<>0)then begin print(938);printdelimiter(p+5);end;
if(mem[p+4].qqqq.b0<>0)or(mem[p+4].qqqq.b1<>0)or(mem[p+4].qqqq.b2<>0)or(
mem[p+4].qqqq.b3<>0)then begin print(939);printdelimiter(p+4);end;
printsubsidiarydata(p+2,92);printsubsidiarydata(p+3,47);end{:708};
{:701}others:print(322)end{:189};p:=mem[p].hh.rh;end;10:end;
{:188}{204:}procedure showbox(p:halfword);
begin{242:}depththreshold:=eqtb[28487].int;
breadthmax:=eqtb[28486].int{:242};if breadthmax<=0 then breadthmax:=5;
if poolptr+depththreshold>=poolsize then depththreshold:=poolsize-
poolptr-1;shownodelist(p);println;end;
{:204}{206:}procedure deletetokenref(p:halfword);
begin if mem[p].hh.lh=-1073741823 then flushlist(p)else decr(mem[p].hh.
lh);end;{:206}{207:}procedure deleteglueref(p:halfword);
begin if mem[p].hh.rh=-1073741823 then freenode(p,4)else decr(mem[p].hh.
rh);end;{:207}{208:}procedure flushnodelist(p:halfword);label 30;
var q:halfword;begin while p<>-1073741823 do begin q:=mem[p].hh.rh;
if(p>=himemmin)then begin mem[p].hh.rh:=avail;avail:=p;
ifdef('STAT')decr(dynused);
endif('STAT')end else begin case mem[p].hh.b0 of 0,1,2,15:begin
flushnodelist(mem[p+5].hh.rh);
begin if mem[mem[p+7].hh.rh].hh.rh=-1073741823 then freenode(mem[p+7].hh
.rh,4)else decr(mem[mem[p+7].hh.rh].hh.rh);end;
begin if mem[mem[p+7].hh.lh].hh.rh=-1073741823 then freenode(mem[p+7].hh
.lh,4)else decr(mem[mem[p+7].hh.lh].hh.rh);end;freenode(p,10);goto 30;
end;3:begin freenode(p,6);goto 30;end;
4:begin flushnodelist(mem[p+4].hh.lh);deleteglueref(mem[p+4].hh.rh);
freenode(p,6);goto 30;end;
10:{1371:}begin case mem[p].hh.b1 of 0:freenode(p,3);
1,3:begin deletetokenref(mem[p+1].hh.rh);freenode(p,2);goto 30;end;
2,4:freenode(p,2);others:confusion(1380)end;goto 30;end{:1371};
12:begin begin if mem[mem[p+1].hh.lh].hh.rh=-1073741823 then freenode(
mem[p+1].hh.lh,4)else decr(mem[mem[p+1].hh.lh].hh.rh);end;
if mem[p+1].hh.rh<>-1073741823 then flushnodelist(mem[p+1].hh.rh);
freenode(p,4);goto 30;end;5:;13,11,14:begin freenode(p,4);goto 30;end;
8:flushnodelist(mem[p+1].hh.rh);6:deletetokenref(mem[p+1].int);
9:begin flushnodelist(mem[p+1].hh.lh);flushnodelist(mem[p+1].hh.rh);end;
7:flushnodelist(mem[p+1].int);{709:}16:begin freenode(p,3);goto 30;end;
17:begin flushnodelist(mem[p+1].hh.lh);flushnodelist(mem[p+1].hh.rh);
flushnodelist(mem[p+2].hh.lh);flushnodelist(mem[p+2].hh.rh);
freenode(p,3);goto 30;end;
18,19,20,21,22,23,24,25,26,29,28,31,30:begin if(mem[p+1].hh.rh>=2)and(
mem[p+1].hh.rh<>6)and(mem[p+1].hh.rh<>7)then flushnodelist(mem[p+1].hh.
lh);
if mem[p+2].hh.rh>=2 and(mem[p+2].hh.rh<>6)and(mem[p+2].hh.rh<>7)then
flushnodelist(mem[p+2].hh.lh);
if mem[p+3].hh.rh>=2 and(mem[p+3].hh.rh<>6)and(mem[p+3].hh.rh<>7)then
flushnodelist(mem[p+3].hh.lh);
if mem[p].hh.b0=26 then freenode(p,6)else if mem[p].hh.b0=30 then
freenode(p,6)else freenode(p,5);goto 30;end;32,33:begin freenode(p,5);
goto 30;end;27:begin flushnodelist(mem[p+2].hh.lh);
flushnodelist(mem[p+3].hh.lh);freenode(p,6);goto 30;end;
{:709}others:confusion(361)end;freenode(p,2);30:end;p:=q;end;end;
{:208}{210:}function copynodelist(p:halfword):halfword;var h:halfword;
q:halfword;r:halfword;words:0..5;begin h:=getavail;q:=h;
while p<>-1073741823 do begin{211:}words:=1;
if(p>=himemmin)then r:=getavail else{212:}case mem[p].hh.b0 of 2,0,1,15:
begin r:=getnode(10);{1445:}mem[r+8].int:=mem[p+8].int;
mem[r+9].int:=mem[p+9].int;{:1445};mem[r+7]:=mem[p+7];
mem[r+6]:=mem[p+6];mem[r+5]:=mem[p+5];incr(mem[mem[r+7].hh.rh].hh.rh);
incr(mem[mem[r+7].hh.lh].hh.rh);
mem[r+5].hh.rh:=copynodelist(mem[p+5].hh.rh);words:=5;end;
3:begin r:=getnode(6);words:=4;{1446:}{:1446};end;4:begin r:=getnode(6);
mem[r+5]:=mem[p+5];mem[r+4]:=mem[p+4];incr(mem[mem[p+4].hh.rh].hh.rh);
mem[r+4].hh.lh:=copynodelist(mem[p+4].hh.lh);words:=4;end;
10:{1370:}case mem[p].hh.b1 of 0:begin r:=getnode(3);words:=3;end;
1,3:begin r:=getnode(2);incr(mem[mem[p+1].hh.rh].hh.lh);words:=2;end;
2,4:begin r:=getnode(2);words:=2;end;others:confusion(1379)end{:1370};
12:begin r:=getnode(4);incr(mem[mem[p+1].hh.lh].hh.rh);
{1447:}mem[r+2].int:=mem[p+2].int;mem[r+3].int:=mem[p+3].int;{:1447};
mem[r+1].hh.lh:=mem[p+1].hh.lh;
mem[r+1].hh.rh:=copynodelist(mem[p+1].hh.rh);end;5:begin r:=getnode(2);
words:=2;end;13,11,14:begin r:=getnode(4);words:=4;end;
8:begin r:=getnode(2);mem[r+1]:=mem[p+1];
mem[r+1].hh.rh:=copynodelist(mem[p+1].hh.rh);end;9:begin r:=getnode(2);
mem[r+1].hh.lh:=copynodelist(mem[p+1].hh.lh);
mem[r+1].hh.rh:=copynodelist(mem[p+1].hh.rh);end;6:begin r:=getnode(2);
incr(mem[mem[p+1].int].hh.lh);words:=2;end;7:begin r:=getnode(2);
mem[r+1].int:=copynodelist(mem[p+1].int);end;
others:confusion(362)end{:212};while words>0 do begin decr(words);
mem[r+words]:=mem[p+words];end{:211};mem[q].hh.rh:=r;q:=r;
p:=mem[p].hh.rh;end;mem[q].hh.rh:=-1073741823;q:=mem[h].hh.rh;
begin mem[h].hh.rh:=avail;avail:=h;ifdef('STAT')decr(dynused);
endif('STAT')end;copynodelist:=q;end;
{:210}{217:}procedure printmode(m:integer);
begin if m>0 then case m div(116)of 0:print(363);1:print(364);
2:print(365);
end else if m=0 then print(366)else case(-m)div(116)of 0:print(367);
1:print(368);2:print(369);end;end;procedure printinmode(m:integer);
begin if m>0 then case m div(116)of 0:print(370);1:print(371);
2:print(372);
end else if m=0 then print(373)else case(-m)div(116)of 0:print(374);
1:print(375);2:print(376);end;end;{:217}{222:}procedure pushnest;
begin if nestptr>maxneststack then begin maxneststack:=nestptr;
if nestptr=nestsize then overflow(377,nestsize);end;
nest[nestptr]:=curlist;incr(nestptr);curlist.headfield:=newnullbox;
curlist.tailfield:=curlist.headfield;
curlist.pnodefield:=curlist.tailfield;curlist.pgfield:=0;
curlist.pdispfield:=0;curlist.lastjchrfield:=-1073741823;
curlist.mlfield:=line;end;{:222}{223:}procedure popnest;
begin begin if mem[mem[curlist.headfield+7].hh.rh].hh.rh=-1073741823
then freenode(mem[curlist.headfield+7].hh.rh,4)else decr(mem[mem[curlist
.headfield+7].hh.rh].hh.rh);end;
begin if mem[mem[curlist.headfield+7].hh.lh].hh.rh=-1073741823 then
freenode(mem[curlist.headfield+7].hh.lh,4)else decr(mem[mem[curlist.
headfield+7].hh.lh].hh.rh);end;freenode(curlist.headfield,10);
decr(nestptr);curlist:=nest[nestptr];end;
{:223}{224:}procedure printtotals;forward;procedure showactivities;
var p:0..nestsize;m:-233..233;a:memoryword;q,r:halfword;t:integer;
begin nest[nestptr]:=curlist;printnl(344);println;
for p:=nestptr downto 0 do begin m:=nest[p].modefield;
a:=nest[p].auxfield;printnl(378);printdirection(nest[p].dirfield);
print(328);printmode(m);print(379);printint(abs(nest[p].mlfield));
if m=117 then if nest[p].pgfield<>8585216 then begin print(380);
printint(nest[p].pgfield mod 65536);print(381);
printint(nest[p].pgfield div 4194304);printchar(44);
printint((nest[p].pgfield div 65536)mod 64);printchar(41);end;
if nest[p].mlfield<0 then print(382);
if p=0 then begin{997:}if memtop-2<>pagetail then begin printnl(1037);
if outputactive then print(1038);showbox(mem[memtop-2].hh.rh);
if pagecontents>0 then begin printnl(1039);printtotals;printnl(1040);
printscaled(pagesofar[0]);r:=mem[memtop].hh.rh;
while r<>memtop do begin println;printesc(336);t:=mem[r].hh.b1;
printint(t);print(1041);
if eqtb[28526+t].int=1000 then t:=mem[r+3].int else t:=xovern(mem[r+3].
int,1000)*eqtb[28526+t].int;printscaled(t);
if mem[r].hh.b0=1 then begin q:=memtop-2;t:=0;repeat q:=mem[q].hh.rh;
if(mem[q].hh.b0=4)and(mem[q].hh.b1=mem[r].hh.b1)then incr(t);
until q=mem[r+1].hh.lh;print(1042);printint(t);print(1043);end;
r:=mem[r].hh.rh;end;end;end{:997};
if mem[memtop-1].hh.rh<>-1073741823 then printnl(383);end;
showbox(mem[nest[p].headfield].hh.rh);
{225:}case abs(m)div(116)of 0:begin printnl(384);
if a.int<=-65536000 then print(385)else printscaled(a.int);
if nest[p].pgfield<>0 then begin print(386);printint(nest[p].pgfield);
if nest[p].pgfield<>1 then print(387)else print(388);end;end;
1:begin printnl(389);printint(a.hh.lh);
if m>0 then if a.hh.rh>0 then begin print(390);printint(a.hh.rh);end;
end;2:if a.int<>-1073741823 then begin print(391);showbox(a.int);end;
end{:225};end;end;{:224}{243:}procedure printparam(n:integer);
begin case n of 0:printesc(444);1:printesc(445);2:printesc(446);
3:printesc(447);4:printesc(448);5:printesc(449);6:printesc(450);
7:printesc(451);8:printesc(452);9:printesc(453);10:printesc(454);
11:printesc(455);12:printesc(456);13:printesc(457);14:printesc(458);
15:printesc(459);16:printesc(460);17:printesc(461);18:printesc(462);
19:printesc(463);20:printesc(464);21:printesc(465);22:printesc(466);
23:printesc(467);24:printesc(468);25:printesc(469);26:printesc(470);
27:printesc(471);28:printesc(472);29:printesc(473);30:printesc(474);
31:printesc(475);32:printesc(476);33:printesc(477);34:printesc(478);
35:printesc(479);36:printesc(480);37:printesc(481);38:printesc(482);
39:printesc(483);40:printesc(484);41:printesc(485);42:printesc(486);
43:printesc(487);44:printesc(488);46:printesc(489);47:printesc(490);
48:printesc(491);49:printesc(492);50:printesc(493);45:printesc(494);
56:printesc(495);57:printesc(496);58:printesc(497);59:printesc(498);
51:printesc(499);52:printesc(500);53:printesc(501);54:printesc(502);
55:printesc(503);60:printesc(504);61:printesc(505);62:printesc(506);
others:print(507)end;end;{:243}{251:}procedure begindiagnostic;
begin oldsetting:=selector;
if(eqtb[28491].int<=0)and(selector=19)then begin decr(selector);
if history=0 then history:=1;end;end;
procedure enddiagnostic(blankline:boolean);begin printnl(344);
if blankline then println;selector:=oldsetting;end;
{:251}{253:}procedure printlengthparam(n:integer);
begin case n of 0:printesc(510);1:printesc(511);2:printesc(512);
3:printesc(513);4:printesc(514);5:printesc(515);6:printesc(516);
7:printesc(517);8:printesc(518);9:printesc(519);10:printesc(520);
11:printesc(521);12:printesc(522);13:printesc(523);14:printesc(524);
15:printesc(525);16:printesc(526);17:printesc(527);18:printesc(528);
19:printesc(529);21:printesc(530);22:printesc(531);20:printesc(532);
others:print(533)end;end;
{:253}{258:}{304:}procedure printcmdchr(cmd:quarterword;
chrcode:halfword);begin case cmd of 1:begin print(595);print(chrcode);
end;2:begin print(596);print(chrcode);end;3:begin print(597);
print(chrcode);end;6:begin print(598);print(chrcode);end;
7:begin print(599);print(chrcode);end;8:begin print(600);print(chrcode);
end;9:print(601);10:begin print(602);print(chrcode);end;
11:begin print(603);print(chrcode);end;12:begin print(604);
print(chrcode);end;16,17,18,19:begin print(605);printkanji(chrcode);end;
{233:}83,84:if chrcode<24548 then printskipparam(chrcode-24527)else if
chrcode<24804 then begin printesc(414);printint(chrcode-24548);
end else begin printesc(415);printint(chrcode-24804);end;
{:233}{237:}80:if chrcode>=25070 then begin printesc(426);
printint(chrcode-25070);end else case chrcode of 25061:printesc(417);
25062:printesc(418);25063:printesc(419);25064:printesc(420);
25065:printesc(421);25066:printesc(422);25067:printesc(423);
25068:printesc(424);others:printesc(425)end;
{:237}{245:}81:if chrcode<28526 then printparam(chrcode-28462)else begin
printesc(508);printint(chrcode-28526);end;
{:245}{255:}82:if chrcode<29061 then printlengthparam(chrcode-29038)else
begin printesc(534);printint(chrcode-29061);end;
{:255}{272:}49:printesc(543);103:printesc(544);44:printesc(545);
45:printesc(546);85:printesc(557);66:printesc(547);46:printesc(569);
20:printesc(548);122:printesc(539);99:printesc(554);100:printesc(555);
101:printesc(556);15:printesc(550);105:printesc(551);72:printesc(540);
67:printesc(552);69:printesc(32);117:printesc(553);36:printesc(558);
40:printesc(559);43:printesc(560);41:printesc(336);48:printesc(47);
54:printesc(549);22:printesc(359);50:printesc(561);21:printesc(562);
59:printesc(563);104:printesc(564);38:printesc(565);70:printesc(566);
118:printesc(567);60:printesc(341);68:printesc(568);71:printesc(571);
109:printesc(572);0:printesc(573);111:printesc(574);91:printesc(570);
95:printesc(427);124:printesc(575);79:printesc(426);42:printesc(360);
37:printesc(576);61:printesc(577);39:printesc(578);
{:272}{341:}13:printesc(635);
{:341}{388:}119:if chrcode=0 then printesc(670)else printesc(671);
{:388}{396:}125:case chrcode of 1:printesc(673);2:printesc(674);
3:printesc(675);4:printesc(676);others:printesc(672)end;
{:396}{423:}102:if chrcode=0 then printesc(508)else if chrcode=1 then
printesc(534)else if chrcode=2 then printesc(414)else printesc(415);
{:423}{428:}90:if chrcode=1 then printesc(710)else printesc(709);
93:if chrcode=0 then printesc(711)else printesc(712);
94:if chrcode=1 then printesc(713)else if chrcode=3 then printesc(714)
else printesc(715);76:case chrcode of 0:printesc(716);1:printesc(717);
2:printesc(718);3:printesc(719);others:printesc(720)end;
{:428}{480:}123:case chrcode of 0:printesc(778);1:printesc(779);
3:printesc(780);4:printesc(781);5:printesc(782);2:printesc(783);
6:printesc(784);7:printesc(785);8:printesc(786);9:printesc(787);
10:printesc(788);others:printesc(789)end;
{:480}{499:}120:case chrcode of 1:printesc(806);2:printesc(807);
3:printesc(808);4:printesc(809);5:printesc(810);6:printesc(811);
7:printesc(812);8:printesc(813);9:printesc(814);10:printesc(815);
11:printesc(816);12:printesc(817);13:printesc(818);14:printesc(819);
15:printesc(820);16:printesc(821);17:printesc(822);18:printesc(823);
19:printesc(824);20:printesc(825);21:printesc(826);22:printesc(827);
23:printesc(828);others:printesc(805)end;
{:499}{503:}121:if chrcode=2 then printesc(829)else if chrcode=4 then
printesc(830)else printesc(831);
{:503}{792:}4:if chrcode=256 then printesc(955)else begin print(959);
print(chrcode);end;
5:if chrcode=257 then printesc(956)else printesc(957);
{:792}{995:}92:case chrcode of 0:printesc(1027);1:printesc(1028);
2:printesc(1029);3:printesc(1030);4:printesc(1031);5:printesc(1032);
6:printesc(1033);others:printesc(1034)end;
{:995}{1065:}14:if chrcode=1 then printesc(1084)else printesc(1083);
{:1065}{1071:}30:case chrcode of 4:printesc(1085);0:printesc(1086);
1:printesc(1087);2:printesc(1088);others:printesc(1089)end;
31:case chrcode of 4:printesc(1090);0:printesc(1091);1:printesc(1092);
2:printesc(1093);others:printesc(1094)end;32:printesc(342);
33:printesc(346);34:printesc(348);
{:1071}{1084:}25:if chrcode=1 then printesc(1112)else printesc(1113);
26:if chrcode=1 then printesc(1114)else printesc(1115);
24:case chrcode of 0:printesc(428);1:printesc(1116);2:printesc(1117);
3:printesc(1022);4:printesc(1118);5:printesc(1024);
others:printesc(1119)end;78:case chrcode of 4:printesc(1121);
3:printesc(1120);1:printesc(1122);end;
35:if chrcode=100 then printesc(1124)else if chrcode=101 then printesc(
1125)else if chrcode=102 then printesc(1126)else printesc(1123);
{:1084}{1101:}47:if chrcode=0 then printesc(1149)else printesc(1148);
{:1101}{1120:}29:if chrcode=12 then printesc(1162)else if chrcode=13
then printesc(1161)else printesc(1160);
27:if chrcode=1 then printesc(1164)else printesc(1163);
28:if chrcode=1 then printesc(1166)else printesc(1165);
{:1120}{1127:}51:if chrcode=1 then printesc(45)else printesc(357);
{:1127}{1155:}52:if chrcode=1 then printesc(1200)else printesc(1199);
{:1155}{1169:}55:case chrcode of 18:printesc(922);19:printesc(923);
20:printesc(924);21:printesc(925);22:printesc(926);23:printesc(927);
24:printesc(928);25:printesc(929);28:printesc(931);
others:printesc(930)end;
56:if chrcode=1 then printesc(934)else if chrcode=2 then printesc(935)
else printesc(1204);{:1169}{1182:}58:printstyle(chrcode);
{:1182}{1191:}57:case chrcode of 1:printesc(1223);2:printesc(1224);
3:printesc(1225);4:printesc(1226);5:printesc(1227);
others:printesc(1222)end;
{:1191}{1201:}53:if chrcode=32 then printesc(932)else printesc(933);
{:1201}{1221:}106:if chrcode=1 then printesc(1246)else if chrcode=2 then
printesc(1247)else printesc(1248);
110:if chrcode=0 then printesc(1249)else if chrcode=1 then printesc(1250
)else if chrcode=2 then printesc(1251)else printesc(1252);
{:1221}{1232:}107:if chrcode<>0 then printesc(1267)else printesc(1266);
{:1232}{1235:}108:case chrcode of 0:printesc(1268);8:printesc(1269);
1:printesc(1270);2:printesc(1271);3:printesc(1272);4:printesc(1273);
5:printesc(1274);7:printesc(1276);others:printesc(1275)end;
73:begin printesc(548);printhex(chrcode);end;74:begin printesc(549);
printhex(chrcode);end;75:begin printesc(562);printhex(chrcode);end;
{:1235}{1243:}96:if chrcode=25636 then printesc(434)else if chrcode=
25892 then printesc(435)else if chrcode=26404 then printesc(436)else if
chrcode=27950 then printesc(443)else if chrcode=27182 then printesc(440)
else if chrcode=27438 then printesc(441)else if chrcode=27694 then
printesc(442)else printesc(509);97:printsize(chrcode-25583);
{:1243}{1264:}112:if chrcode=1 then printesc(1010)else printesc(998);
{:1264}{1268:}86:if chrcode=0 then printesc(1298)else printesc(1299);
{:1268}{1274:}98:begin print(1307);slowprint(fontname[chrcode]);
if fontsize[chrcode]<>fontdsize[chrcode]then begin print(790);
printscaled(fontsize[chrcode]);print(416);end;end;
{:1274}{1276:}113:case chrcode of 0:printesc(273);1:printesc(274);
2:printesc(275);others:printesc(1308)end;
{:1276}{1286:}65:if chrcode=0 then printesc(1310)else printesc(1309);
{:1286}{1291:}63:if chrcode=0 then printesc(1311)else printesc(1312);
{:1291}{1300:}62:if chrcode=27182 then printesc(1318)else printesc(1319)
;{:1300}{1305:}23:case chrcode of 1:printesc(1321);2:printesc(1322);
3:printesc(1323);4:printesc(1324);others:printesc(1320)end;
{:1305}{1308:}116:print(1331);126:print(1332);127:printesc(1333);
128:printesc(1334);129:begin printesc(1246);printesc(1334);end;
130:printesc(1335);{:1308}{1359:}64:case chrcode of 0:printesc(1370);
1:printesc(632);2:printesc(1371);3:printesc(1372);4:printesc(1373);
5:printesc(1374);others:print(1375)end;{:1359}{1455:}89:printesc(439);
{:1455}{1460:}114:begin if(chrcode mod 2)=0 then printesc(1410)else
printesc(1411);if chrcode<2 then print(1412)else print(1413);end;
115:begin if chrcode=0 then printesc(1414)else if chrcode=1 then
printesc(1415)else printesc(1416);print(1417);end;
{:1460}{1467:}77:printesc(1422);88:printesc(1423);
{:1467}{1472:}87:case chrcode of 1:printesc(1426);2:printesc(1427);end;
{:1472}others:print(606)end;end;
{:304}ifdef('STAT')procedure showeqtb(n:halfword);
begin if n<1 then printchar(63)else if(n<24527)or((n>29572)and(n<=
eqtbtop))then{229:}begin sprintcs(n);printchar(61);
printcmdchr(eqtb[n].hh.b0,eqtb[n].hh.rh);
if eqtb[n].hh.b0>=126 then begin printchar(58);
showtokenlist(mem[eqtb[n].hh.rh].hh.rh,-1073741823,32);end;
end{:229}else if n<25060 then{235:}if n<24548 then begin printskipparam(
n-24527);printchar(61);
if n<24544 then printspec(eqtb[n].hh.rh,416)else printspec(eqtb[n].hh.rh
,343);end else if n<24804 then begin printesc(414);printint(n-24548);
printchar(61);printspec(eqtb[n].hh.rh,416);end else begin printesc(415);
printint(n-24804);printchar(61);printspec(eqtb[n].hh.rh,343);
end{:235}else if n<28462 then{239:}if n=25060 then begin printesc(427);
printchar(61);
if eqtb[25060].hh.rh=-1073741823 then printchar(48)else printint(mem[
eqtb[25060].hh.rh].hh.lh);
end else if n<25070 then begin printcmdchr(80,n);printchar(61);
if eqtb[n].hh.rh<>-1073741823 then showtokenlist(mem[eqtb[n].hh.rh].hh.
rh,-1073741823,32);end else if n<25326 then begin printesc(426);
printint(n-25070);printchar(61);
if eqtb[n].hh.rh<>-1073741823 then showtokenlist(mem[eqtb[n].hh.rh].hh.
rh,-1073741823,32);end else if n<25582 then begin printesc(428);
printint(n-25326);printchar(61);
if eqtb[n].hh.rh=-1073741823 then print(429)else begin depththreshold:=0
;breadthmax:=1;shownodelist(eqtb[n].hh.rh);end;
end else if n<25636 then{240:}begin if n=25582 then print(430)else if n<
25599 then begin printesc(431);printint(n-25583);
end else if n<25615 then begin printesc(432);printint(n-25599);
end else begin printesc(433);printint(n-25615);end;printchar(61);
printesc(hash[15525+eqtb[n].hh.rh].rh);
end{:240}else{241:}if n<27950 then begin if n<25892 then begin printesc(
434);printint(n-25636);end else if n<26404 then begin printesc(435);
printint(n-25892);end else if n<26660 then begin printesc(436);
printint(n-26404);end else if n<26916 then begin print(437);
printint(n-26660);end else if n<27172 then begin print(438);
printint(n-26916);end else if n<27182 then begin printesc(439);
printint(n-27172);end else if n<27438 then begin printesc(440);
printint(n-27182);end else if n<27694 then begin printesc(441);
printint(n-27438);end else begin printesc(442);printint(n-27694);end;
printchar(61);printint(eqtb[n].hh.rh);end else begin printesc(443);
printint(n-27950);printchar(61);printint(eqtb[n].hh.rh);
end{:241}{:239}else if n<29038 then{248:}begin if n<28526 then
printparam(n-28462)else if n<28782 then begin printesc(508);
printint(n-28526);end else begin printesc(509);printint(n-28782);end;
printchar(61);printint(eqtb[n].int);
end{:248}else if n<29317 then{257:}begin if n<29061 then
printlengthparam(n-29038)else begin printesc(534);printint(n-29061);end;
printchar(61);printscaled(eqtb[n].int);print(416);
end{:257}else if n<=29572 then print(535)else printchar(63);end;
endif('STAT'){:258}{265:}function idlookup(j,l:integer):halfword;
label 40;var h:integer;d:integer;p:halfword;k:halfword;
begin{267:}h:=buffer[j];for k:=j+1 to j+l-1 do begin h:=h+h+buffer[k];
while h>=8501 do h:=h-8501;end{:267};p:=h+514;
while true do begin if hash[p].rh>0 then if(strstart[hash[p].rh+1]-
strstart[hash[p].rh])=l then if streqbuf(hash[p].rh,j)then goto 40;
if hash[p].lh=0 then begin if nonewcontrolsequence then p:=24526 else
{266:}begin if hash[p].rh>0 then begin if hashhigh<hashextra then begin
incr(hashhigh);hash[p].lh:=hashhigh+29572;p:=hashhigh+29572;
end else begin repeat if(hashused=514)then overflow(538,15000+hashextra)
;decr(hashused);until hash[hashused].rh=0;hash[p].lh:=hashused;
p:=hashused;end;end;
begin if poolptr+l>poolsize then overflow(258,poolsize-initpoolptr);end;
d:=(poolptr-strstart[strptr]);
while poolptr>strstart[strptr]do begin decr(poolptr);
strpool[poolptr+l]:=strpool[poolptr];end;
for k:=j to j+l-1 do begin strpool[poolptr]:=buffer[k];incr(poolptr);
end;hash[p].rh:=makestring;poolptr:=poolptr+d;
ifdef('STAT')incr(cscount);endif('STAT')end{:266};goto 40;end;
p:=hash[p].lh;end;40:idlookup:=p;end;
{:265}{270:}ifdef('INITEX')procedure primitive(s:strnumber;
c:quarterword;o:halfword);var k:poolpointer;j:smallnumber;l:smallnumber;
begin if s<256 then curval:=s+257 else begin k:=strstart[s];
l:=strstart[s+1]-k;for j:=0 to l-1 do buffer[j]:=strpool[k+j];
curval:=idlookup(0,l);begin decr(strptr);poolptr:=strstart[strptr];end;
hash[curval].rh:=s;end;eqtb[curval].hh.b1:=1;eqtb[curval].hh.b0:=c;
eqtb[curval].hh.rh:=o;end;
endif('INITEX'){:270}{280:}procedure newsavelevel(c:groupcode);
begin if saveptr>maxsavestack then begin maxsavestack:=saveptr;
if maxsavestack>savesize-6 then overflow(579,savesize);end;
savestack[saveptr].hh.b0:=3;savestack[saveptr].hh.b1:=curgroup;
savestack[saveptr].hh.rh:=curboundary;
if curlevel=65535 then overflow(580,65535);curboundary:=saveptr;
incr(curlevel);incr(saveptr);curgroup:=c;end;
{:280}{281:}procedure eqdestroy(w:memoryword);var q:halfword;
begin case w.hh.b0 of 126,127,128,129:deletetokenref(w.hh.rh);
132:deleteglueref(w.hh.rh);133:begin q:=w.hh.rh;
if q<>-1073741823 then freenode(q,mem[q].hh.lh+mem[q].hh.lh+1);end;
134:flushnodelist(w.hh.rh);others:end;end;
{:281}{282:}procedure eqsave(p:halfword;l:quarterword);
begin if saveptr>maxsavestack then begin maxsavestack:=saveptr;
if maxsavestack>savesize-6 then overflow(579,savesize);end;
if l=0 then savestack[saveptr].hh.b0:=1 else begin savestack[saveptr]:=
eqtb[p];incr(saveptr);savestack[saveptr].hh.b0:=0;end;
savestack[saveptr].hh.b1:=l;savestack[saveptr].hh.rh:=p;incr(saveptr);
end;{:282}{283:}procedure eqdefine(p:halfword;t:quarterword;e:halfword);
begin if eqtb[p].hh.b1=curlevel then eqdestroy(eqtb[p])else if curlevel>
1 then eqsave(p,eqtb[p].hh.b1);eqtb[p].hh.b1:=curlevel;eqtb[p].hh.b0:=t;
eqtb[p].hh.rh:=e;end;{:283}{284:}procedure eqworddefine(p:halfword;
w:integer);
begin if xeqlevel[p]<>curlevel then begin eqsave(p,xeqlevel[p]);
xeqlevel[p]:=curlevel;end;eqtb[p].int:=w;end;
{:284}{285:}procedure geqdefine(p:halfword;t:quarterword;e:halfword);
begin eqdestroy(eqtb[p]);eqtb[p].hh.b1:=1;eqtb[p].hh.b0:=t;
eqtb[p].hh.rh:=e;end;procedure geqworddefine(p:halfword;w:integer);
begin eqtb[p].int:=w;xeqlevel[p]:=1;end;
{:285}{286:}procedure saveforafter(t:halfword);
begin if curlevel>1 then begin if saveptr>maxsavestack then begin
maxsavestack:=saveptr;
if maxsavestack>savesize-6 then overflow(579,savesize);end;
savestack[saveptr].hh.b0:=2;savestack[saveptr].hh.b1:=0;
savestack[saveptr].hh.rh:=t;incr(saveptr);end;end;
{:286}{287:}{290:}ifdef('STAT')procedure restoretrace(p:halfword;
s:strnumber);begin begindiagnostic;printchar(123);print(s);
printchar(32);showeqtb(p);printchar(125);enddiagnostic(false);end;
endif('STAT'){:290}procedure backinput;forward;procedure unsave;
label 30;var p:halfword;l:quarterword;t:halfword;
begin if curlevel>1 then begin decr(curlevel);
{288:}while true do begin decr(saveptr);
if savestack[saveptr].hh.b0=3 then goto 30;p:=savestack[saveptr].hh.rh;
if savestack[saveptr].hh.b0=2 then{332:}begin t:=curtok;curtok:=p;
backinput;curtok:=t;
end{:332}else begin if savestack[saveptr].hh.b0=0 then begin l:=
savestack[saveptr].hh.b1;decr(saveptr);
end else savestack[saveptr]:=eqtb[24526];
{289:}if(p<28462)or(p>29572)then if eqtb[p].hh.b1=1 then begin eqdestroy
(savestack[saveptr]);
ifdef('STAT')if eqtb[28499].int>0 then restoretrace(p,582);
endif('STAT')end else begin eqdestroy(eqtb[p]);
eqtb[p]:=savestack[saveptr];
ifdef('STAT')if eqtb[28499].int>0 then restoretrace(p,583);
endif('STAT')end else if xeqlevel[p]<>1 then begin eqtb[p]:=savestack[
saveptr];xeqlevel[p]:=l;
ifdef('STAT')if eqtb[28499].int>0 then restoretrace(p,583);
endif('STAT')end else begin ifdef('STAT')if eqtb[28499].int>0 then
restoretrace(p,582);endif('STAT')end{:289};end;end;
30:curgroup:=savestack[saveptr].hh.b1;
curboundary:=savestack[saveptr].hh.rh{:288};end else confusion(581);end;
{:287}{294:}procedure preparemag;
begin if(magset>0)and(eqtb[28479].int<>magset)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(585);
end;printint(eqtb[28479].int);print(586);printnl(587);begin helpptr:=2;
helpline[1]:=588;helpline[0]:=589;end;interror(magset);
geqworddefine(28479,magset);end;
if(eqtb[28479].int<=0)or(eqtb[28479].int>32768)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(590);
end;begin helpptr:=1;helpline[0]:=591;end;interror(eqtb[28479].int);
geqworddefine(28479,1000);end;magset:=eqtb[28479].int;end;
{:294}{301:}procedure tokenshow(p:halfword);
begin if p<>-1073741823 then showtokenlist(mem[p].hh.rh,-1073741823,
10000000);end;{:301}{302:}procedure printmeaning;
begin printcmdchr(curcmd,curchr);
if curcmd>=126 then begin printchar(58);println;tokenshow(curchr);
end else if curcmd=125 then begin printchar(58);println;
tokenshow(curmark[curchr]);end;end;{:302}{305:}procedure showcurcmdchr;
begin begindiagnostic;printnl(123);
if curlist.modefield<>shownmode then begin printmode(curlist.modefield);
print(607);shownmode:=curlist.modefield;end;printcmdchr(curcmd,curchr);
printchar(125);enddiagnostic(false);end;
{:305}{317:}procedure showcontext;label 30,31;var oldsetting:0..21;
s:halfword;nn:integer;bottomline:boolean;{321:}i:0..bufsize;
j:0..bufsize;l:0..halferrorline;m:integer;n:0..errorline;p:integer;
q:integer;{:321}begin baseptr:=inputptr;inputstack[baseptr]:=curinput;
nn:=-1;bottomline:=false;
while true do begin curinput:=inputstack[baseptr];
if(curinput.statefield<>0)then if(curinput.namefield>17)or(baseptr=0)
then bottomline:=true;
if(baseptr=inputptr)or bottomline or(nn<eqtb[28517].int)then{318:}begin
if(baseptr=inputptr)or(curinput.statefield<>0)or(curinput.indexfield<>3)
or(curinput.locfield<>-1073741823)then begin tally:=0;
oldsetting:=selector;
if curinput.statefield<>0 then begin{319:}if curinput.namefield<=17 then
if(curinput.namefield=0)then if baseptr=0 then printnl(612)else printnl(
613)else begin printnl(614);
if curinput.namefield=17 then printchar(42)else printint(curinput.
namefield-1);printchar(62);end else begin printnl(615);printint(line);
end;printchar(32){:319};{324:}begin l:=tally;tally:=0;selector:=20;
kcodepos:=0;trickcount:=1000000;end;
if buffer[curinput.limitfield]=eqtb[28511].int then j:=curinput.
limitfield else j:=curinput.limitfield+1;
if j>0 then for i:=curinput.startfield to j-1 do begin if i=curinput.
locfield then begin firstcount:=tally;
kcp:=trickbuf2[(firstcount-1)mod errorline];
if(firstcount>0)and(kcp>0)then firstcount:=firstcount+nrestmultichr(kcp)
;trickcount:=firstcount+1+errorline-halferrorline;
if trickcount<errorline then trickcount:=errorline;end;print(buffer[i]);
end{:324};
end else begin{320:}case curinput.indexfield of 0:printnl(616);
1,2:printnl(617);
3:if curinput.locfield=-1073741823 then printnl(618)else printnl(619);
4:printnl(620);5:begin println;printcs(curinput.namefield);end;
6:printnl(621);7:printnl(622);8:printnl(623);9:printnl(624);
10:printnl(625);11:printnl(626);12:printnl(627);13:printnl(628);
14:printnl(629);15:printnl(630);others:printnl(63)end{:320};
{325:}begin l:=tally;tally:=0;selector:=20;kcodepos:=0;
trickcount:=1000000;end;
if curinput.indexfield<5 then begin if(curinput.indexfield=3)and(
curinput.locfield<>-1073741823)then begin if(mem[curinput.startfield].hh
.rh=-1073741823)and(checkkanji(mem[curinput.startfield].hh.lh))then
begin curinput:=inputstack[baseptr-1];s:=getavail;
mem[s].hh.lh:=(mem[curinput.locfield].hh.lh mod 256);
curinput:=inputstack[baseptr];mem[curinput.startfield].hh.rh:=s;
showtokenlist(curinput.startfield,curinput.locfield,100000);
begin mem[s].hh.rh:=avail;avail:=s;ifdef('STAT')decr(dynused);
endif('STAT')end;mem[curinput.startfield].hh.rh:=-1073741823;goto 31;
end;end;showtokenlist(curinput.startfield,curinput.locfield,100000);
end else showtokenlist(mem[curinput.startfield].hh.rh,curinput.locfield,
100000);31:{:325};end;selector:=oldsetting;
{323:}if trickcount=1000000 then begin firstcount:=tally;
kcp:=trickbuf2[(firstcount-1)mod errorline];
if(firstcount>0)and(kcp>0)then firstcount:=firstcount+nrestmultichr(kcp)
;trickcount:=firstcount+1+errorline-halferrorline;
if trickcount<errorline then trickcount:=errorline;end;
if tally<trickcount then m:=tally-firstcount else m:=trickcount-
firstcount;if l+firstcount<=halferrorline then begin p:=0;
n:=l+firstcount;end else begin print(276);
p:=l+firstcount-halferrorline+3;n:=halferrorline;end;
kcp:=trickbuf2[p mod errorline];
if(kcp mod 8)>1 then begin p:=p+nrestmultichr(kcp)+1;
n:=n-nrestmultichr(kcp)-1;end;
for q:=p to firstcount-1 do printchar(trickbuf[q mod errorline]);
println;for q:=1 to n do printchar(32);
if m+n<=errorline then p:=firstcount+m else p:=firstcount+(errorline-n-3
);kcp:=trickbuf2[(p-1)mod errorline];
if((kcp mod 8)>0)and(nrestmultichr(kcp)>0)then p:=p-(kcp mod 8);
for q:=firstcount to p-1 do printchar(trickbuf[q mod errorline]);
if m+n>errorline then print(276){:323};incr(nn);end;
end{:318}else if nn=eqtb[28517].int then begin printnl(276);incr(nn);
end;if bottomline then goto 30;decr(baseptr);end;
30:curinput:=inputstack[inputptr];end;
{:317}{329:}procedure begintokenlist(p:halfword;t:quarterword);
begin begin if inputptr>maxinstack then begin maxinstack:=inputptr;
if inputptr=stacksize then overflow(631,stacksize);end;
inputstack[inputptr]:=curinput;incr(inputptr);end;
curinput.statefield:=0;curinput.startfield:=p;curinput.indexfield:=t;
if t>=5 then begin incr(mem[p].hh.lh);
if t=5 then curinput.limitfield:=paramptr else begin curinput.locfield:=
mem[p].hh.rh;if eqtb[28492].int>1 then begin begindiagnostic;
printnl(344);case t of 14:printesc(359);15:printesc(632);
others:printcmdchr(80,t+25055)end;print(594);tokenshow(p);
enddiagnostic(false);end;end;end else curinput.locfield:=p;end;
{:329}{330:}procedure endtokenlist;
begin if curinput.indexfield>=3 then begin if curinput.indexfield<=4
then flushlist(curinput.startfield)else begin deletetokenref(curinput.
startfield);
if curinput.indexfield=5 then while paramptr>curinput.limitfield do
begin decr(paramptr);flushlist(paramstack[paramptr]);end;end;
end else if curinput.indexfield=1 then if alignstate>500000 then
alignstate:=0 else fatalerror(633);begin decr(inputptr);
curinput:=inputstack[inputptr];end;
begin if interrupt<>0 then pauseforinstructions;end;end;
{:330}{331:}procedure backinput;var p:halfword;
begin while(curinput.statefield=0)and(curinput.locfield=-1073741823)and(
curinput.indexfield<>2)do endtokenlist;p:=getavail;mem[p].hh.lh:=curtok;
if curtok<768 then if curtok<512 then decr(alignstate)else incr(
alignstate);
begin if inputptr>maxinstack then begin maxinstack:=inputptr;
if inputptr=stacksize then overflow(631,stacksize);end;
inputstack[inputptr]:=curinput;incr(inputptr);end;
curinput.statefield:=0;curinput.startfield:=p;curinput.indexfield:=3;
curinput.locfield:=p;end;{:331}{333:}procedure backerror;
begin OKtointerrupt:=false;backinput;OKtointerrupt:=true;error;end;
procedure inserror;begin OKtointerrupt:=false;backinput;
curinput.indexfield:=4;OKtointerrupt:=true;error;end;
{:333}{334:}procedure beginfilereading;
begin if inopen=maxinopen then overflow(634,maxinopen);
if first=bufsize then overflow(257,bufsize);incr(inopen);
begin if inputptr>maxinstack then begin maxinstack:=inputptr;
if inputptr=stacksize then overflow(631,stacksize);end;
inputstack[inputptr]:=curinput;incr(inputptr);end;
curinput.indexfield:=inopen;sourcefilenamestack[curinput.indexfield]:=0;
fullsourcefilenamestack[curinput.indexfield]:=0;
linestack[curinput.indexfield]:=line;curinput.startfield:=first;
curinput.statefield:=1;curinput.namefield:=0;
{1430:}curinput.synctextagfield:=0;{:1430};end;
{:334}{335:}procedure endfilereading;begin first:=curinput.startfield;
line:=linestack[curinput.indexfield];
if curinput.namefield>17 then aclose(inputfile[curinput.indexfield]);
begin decr(inputptr);curinput:=inputstack[inputptr];end;decr(inopen);
end;{:335}{336:}procedure clearforerrorprompt;
begin while(curinput.statefield<>0)and(curinput.namefield=0)and(inputptr
>0)and(curinput.locfield>curinput.limitfield)do endfilereading;println;;
end;{:336}{342:}procedure checkoutervalidity;var p:halfword;q:halfword;
begin if scannerstatus<>0 then begin deletionsallowed:=false;
{343:}if curcs<>0 then begin if(curinput.statefield=0)or(curinput.
namefield<1)or(curinput.namefield>17)then begin p:=getavail;
mem[p].hh.lh:=536870911+curcs;begintokenlist(p,3);end;curcmd:=10;
curchr:=32;end{:343};if scannerstatus>1 then{344:}begin runaway;
if curcs=0 then begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(642);
end else begin curcs:=0;begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(643);
end;end;{345:}p:=getavail;case scannerstatus of 2:begin print(649);
mem[p].hh.lh:=637;end;3:begin print(650);mem[p].hh.lh:=partoken;
longstate:=128;end;4:begin print(651);mem[p].hh.lh:=637;q:=p;
p:=getavail;mem[p].hh.rh:=q;mem[p].hh.lh:=536886426;
alignstate:=-1000000;end;5:begin print(652);mem[p].hh.lh:=637;end;end;
begintokenlist(p,4){:345};print(644);sprintcs(warningindex);
begin helpptr:=4;helpline[3]:=645;helpline[2]:=646;helpline[1]:=647;
helpline[0]:=648;end;error;
end{:344}else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(636);
end;printcmdchr(120,curif);print(637);printint(skipline);
begin helpptr:=3;helpline[2]:=638;helpline[1]:=639;helpline[0]:=640;end;
if curcs<>0 then curcs:=0 else helpline[2]:=641;curtok:=536886429;
inserror;end;deletionsallowed:=true;end;end;
{:342}{346:}procedure firmuptheline;forward;
{:346}{347:}procedure getnext;label 20,25,21,26,40,10;var k:0..bufsize;
t:halfword;cat:0..19;l:0..bufsize;c,cc:ASCIIcode;d:2..3;
begin 20:curcs:=0;
if curinput.statefield<>0 then{349:}begin 25:if curinput.locfield<=
curinput.limitfield then begin curchr:=fromBUFF(ustringcast(buffer),
curinput.limitfield,curinput.locfield);
curcmd:=eqtb[25892+kcatcodekey(curchr)].hh.rh;
if(multistrlen(ustringcast(buffer),curinput.limitfield,curinput.locfield
)>1)and checkkcatcode(curcmd)then begin if(curcmd=15)then curcmd:=18;
curinput.locfield:=curinput.locfield+multistrlen(ustringcast(buffer),
curinput.limitfield,curinput.locfield)end else begin curchr:=buffer[
curinput.locfield];incr(curinput.locfield);
21:curcmd:=eqtb[25636+curchr].hh.rh;end;
{350:}case curinput.statefield+curcmd of{351:}10,30,50,70,51,71{:351}:
goto 25;
1,21,41,61:{362:}begin if curinput.locfield>curinput.limitfield then
curcs:=513 else begin k:=curinput.locfield;
curchr:=fromBUFF(ustringcast(buffer),curinput.limitfield,k);
cat:=eqtb[25892+kcatcodekey(curchr)].hh.rh;
if(multistrlen(ustringcast(buffer),curinput.limitfield,k)>1)and
checkkcatcode(cat)then begin if(cat=15)then cat:=18;
k:=k+multistrlen(ustringcast(buffer),curinput.limitfield,k)end else
begin curchr:=buffer[k];cat:=eqtb[25636+curchr].hh.rh;incr(k);end;
26:if(cat=11)or(cat=16)or(cat=17)or(cat=19)then curinput.statefield:=41
else if cat=10 then curinput.statefield:=41 else curinput.statefield:=1;
if cat=18 then begin curcs:=idlookup(curinput.locfield,k-curinput.
locfield);curinput.locfield:=k;goto 40;
end else if((cat=11)or(cat=16)or(cat=17)or(cat=19))and(k<=curinput.
limitfield)then{364:}begin repeat curchr:=fromBUFF(ustringcast(buffer),
curinput.limitfield,k);cat:=eqtb[25892+kcatcodekey(curchr)].hh.rh;
if(multistrlen(ustringcast(buffer),curinput.limitfield,k)>1)and
checkkcatcode(cat)then begin if(cat=15)then cat:=18;
k:=k+multistrlen(ustringcast(buffer),curinput.limitfield,k)end else
begin curchr:=buffer[k];cat:=eqtb[25636+curchr].hh.rh;incr(k);end;
while(buffer[k]=curchr)and(cat=7)and(k<curinput.limitfield)do begin c:=
buffer[k+1];if c<128 then begin d:=2;
if(((c>=48)and(c<=57))or((c>=97)and(c<=102)))then if k+2<=curinput.
limitfield then begin cc:=buffer[k+2];
if(((cc>=48)and(cc<=57))or((cc>=97)and(cc<=102)))then incr(d);end;
if d>2 then begin if c<=57 then curchr:=c-48 else curchr:=c-87;
if cc<=57 then curchr:=16*curchr+cc-48 else curchr:=16*curchr+cc-87;
end else if c<64 then curchr:=c+64 else curchr:=c-64;
cat:=eqtb[25636+curchr].hh.rh;
if(cat=11)or(cat=7)then begin buffer[k-1]:=curchr;
curinput.limitfield:=curinput.limitfield-d;first:=first-d;l:=k;
while l<=curinput.limitfield do begin buffer[l]:=buffer[l+d];incr(l);
end;end;end;end;
until not((cat=11)or(cat=16)or(cat=17)or(cat=19))or(k>curinput.
limitfield);if not((cat=11)or(cat=16)or(cat=17)or(cat=19))then decr(k);
if cat=18 then k:=k-multilenbuffchar(curchr)+1;
if k>curinput.locfield+1 then begin curcs:=idlookup(curinput.locfield,k-
curinput.locfield);curinput.locfield:=k;goto 40;end;
end{:364}else{363:}begin if buffer[k]=curchr then if cat=7 then if k<
curinput.limitfield then begin c:=buffer[k+1];if c<128 then begin d:=2;
if(((c>=48)and(c<=57))or((c>=97)and(c<=102)))then if k+2<=curinput.
limitfield then begin cc:=buffer[k+2];
if(((cc>=48)and(cc<=57))or((cc>=97)and(cc<=102)))then incr(d);end;
if d>2 then begin if c<=57 then curchr:=c-48 else curchr:=c-87;
if cc<=57 then curchr:=16*curchr+cc-48 else curchr:=16*curchr+cc-87;
buffer[k-1]:=curchr;
end else if c<64 then buffer[k-1]:=c+64 else buffer[k-1]:=c-64;
curinput.limitfield:=curinput.limitfield-d;first:=first-d;l:=k;
curchr:=buffer[k-1];cat:=eqtb[25636+curchr].hh.rh;
while l<=curinput.limitfield do begin buffer[l]:=buffer[l+d];incr(l);
end;goto 26;end;end;end{:363};curcs:=257+buffer[curinput.locfield];
incr(curinput.locfield);end;40:curcmd:=eqtb[curcs].hh.b0;
curchr:=eqtb[curcs].hh.rh;if curcmd>=128 then checkoutervalidity;
end{:362};14,34,54,74:{361:}begin curcs:=curchr+1;
curcmd:=eqtb[curcs].hh.b0;curchr:=eqtb[curcs].hh.rh;
curinput.statefield:=1;if curcmd>=128 then checkoutervalidity;end{:361};
8,28,48,68:{360:}begin if curchr=buffer[curinput.locfield]then if
curinput.locfield<curinput.limitfield then begin c:=buffer[curinput.
locfield+1];if c<128 then begin curinput.locfield:=curinput.locfield+2;
if(((c>=48)and(c<=57))or((c>=97)and(c<=102)))then if curinput.locfield<=
curinput.limitfield then begin cc:=buffer[curinput.locfield];
if(((cc>=48)and(cc<=57))or((cc>=97)and(cc<=102)))then begin incr(
curinput.locfield);if c<=57 then curchr:=c-48 else curchr:=c-87;
if cc<=57 then curchr:=16*curchr+cc-48 else curchr:=16*curchr+cc-87;
goto 21;end;end;if c<64 then curchr:=c+64 else curchr:=c-64;goto 21;end;
end;curinput.statefield:=1;end{:360};
16,36,56,76:{352:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(653);
end;begin helpptr:=2;helpline[1]:=654;helpline[0]:=655;end;
deletionsallowed:=false;error;deletionsallowed:=true;goto 20;end{:352};
{353:}31,11:{357:}begin curinput.statefield:=41;curchr:=32;end{:357};
6:{356:}begin curinput.locfield:=curinput.limitfield+1;curcmd:=10;
curchr:=32;end{:356};
26:if skipmode then{358:}begin curinput.locfield:=curinput.limitfield+1;
goto 25;
end{:358}else{356:}begin curinput.locfield:=curinput.limitfield+1;
curcmd:=10;curchr:=32;end{:356};
46,15,35,55,75:{358:}begin curinput.locfield:=curinput.limitfield+1;
goto 25;end{:358};
66:{359:}begin curinput.locfield:=curinput.limitfield+1;curcs:=parloc;
curcmd:=eqtb[curcs].hh.b0;curchr:=eqtb[curcs].hh.rh;
if curcmd>=128 then checkoutervalidity;end{:359};2,22:incr(alignstate);
42,62:begin curinput.statefield:=1;incr(alignstate);end;
3,23:decr(alignstate);43,63:begin curinput.statefield:=1;
decr(alignstate);end;
44,45,47,49,52,53,64,65,67,69,72,73,24,25,27,29,32,33:curinput.
statefield:=1;57,58,59,77,78,79,17,18,19:curinput.statefield:=21;
60,80,40:curinput.statefield:=1;{:353}others:end{:350};
end else begin curinput.statefield:=61;
{368:}if curinput.namefield>17 then{370:}begin incr(line);
first:=curinput.startfield;
if not forceeof then begin if inputln(inputfile[curinput.indexfield],
true)then firmuptheline else forceeof:=true;end;
if forceeof then begin printchar(41);decr(openparens);fflush(stdout);
forceeof:=false;endfilereading;checkoutervalidity;goto 20;end;
if(eqtb[28511].int<0)or(eqtb[28511].int>255)then decr(curinput.
limitfield)else buffer[curinput.limitfield]:=eqtb[28511].int;
first:=curinput.limitfield+1;curinput.locfield:=curinput.startfield;
end{:370}else begin if not(curinput.namefield=0)then begin curcmd:=0;
curchr:=0;goto 10;end;if inputptr>0 then begin endfilereading;goto 20;
end;if selector<18 then openlogfile;
if interaction>1 then begin if(eqtb[28511].int<0)or(eqtb[28511].int>255)
then incr(curinput.limitfield);
if curinput.limitfield=curinput.startfield then printnl(656);println;
first:=curinput.startfield;begin;print(42);terminput;end;
curinput.limitfield:=last;
if(eqtb[28511].int<0)or(eqtb[28511].int>255)then decr(curinput.
limitfield)else buffer[curinput.limitfield]:=eqtb[28511].int;
first:=curinput.limitfield+1;curinput.locfield:=curinput.startfield;
end else fatalerror(657);end{:368};
begin if interrupt<>0 then pauseforinstructions;end;goto 25;end;
end{:349}else{365:}if curinput.locfield<>-1073741823 then begin t:=mem[
curinput.locfield].hh.lh;
curinput.locfield:=mem[curinput.locfield].hh.rh;
if t>=536870911 then begin curcs:=t-536870911;curcmd:=eqtb[curcs].hh.b0;
curchr:=eqtb[curcs].hh.rh;
if curcmd>=128 then if curcmd=131 then{366:}begin curcs:=mem[curinput.
locfield].hh.lh-536870911;curinput.locfield:=-1073741823;
curcmd:=eqtb[curcs].hh.b0;curchr:=eqtb[curcs].hh.rh;
if curcmd>115 then begin curcmd:=0;curchr:=257;end;
end{:366}else checkoutervalidity;
end else if checkkanji(t)then begin curcmd:=t div 16777216;
curchr:=t mod 16777216;end else begin curcmd:=t div 256;
curchr:=t mod 256;case curcmd of 1:incr(alignstate);2:decr(alignstate);
5:{367:}begin begintokenlist(paramstack[curinput.limitfield+curchr-1],0)
;goto 20;end{:367};others:end;end;end else begin endtokenlist;goto 20;
end{:365};
{348:}if curcmd<=5 then if curcmd>=4 then if alignstate=0 then{800:}
begin if(scannerstatus=4)or(curalign=-1073741823)then fatalerror(633);
curcmd:=mem[curalign+5].hh.lh;mem[curalign+5].hh.lh:=curchr;
if curcmd=68 then begintokenlist(memtop-10,2)else begintokenlist(mem[
curalign+2].int,2);alignstate:=1000000;goto 20;end{:800}{:348};10:end;
{:347}{371:}procedure firmuptheline;var k:0..bufsize;
begin curinput.limitfield:=last;
if eqtb[28490].int>0 then if interaction>1 then begin;println;
if curinput.startfield<curinput.limitfield then for k:=curinput.
startfield to curinput.limitfield-1 do print(buffer[k]);
first:=curinput.limitfield;begin;print(658);terminput;end;
if last>first then begin for k:=first to last-1 do buffer[k+curinput.
startfield-first]:=buffer[k];
curinput.limitfield:=curinput.startfield+last-first;end;end;end;
{:371}{373:}procedure gettoken;begin nonewcontrolsequence:=false;
getnext;nonewcontrolsequence:=true;
if curcs=0 then if(curcmd>=16)and(curcmd<=19)then curtok:=(curcmd
*16777216)+curchr else curtok:=(curcmd*256)+curchr else curtok:=
536870911+curcs;end;{:373}{377:}{400:}procedure macrocall;
label 10,22,30,31,40;var r:halfword;p:halfword;q:halfword;s:halfword;
t:halfword;u,v:halfword;rbraceptr:halfword;n:smallnumber;
unbalance:halfword;m:halfword;refcount:halfword;
savescannerstatus:smallnumber;savewarningindex:halfword;
matchchr:ASCIIcode;begin savescannerstatus:=scannerstatus;
savewarningindex:=warningindex;warningindex:=curcs;refcount:=curchr;
r:=mem[refcount].hh.rh;n:=0;
if eqtb[28492].int>0 then{412:}begin begindiagnostic;println;
printcs(warningindex);tokenshow(refcount);enddiagnostic(false);
end{:412};if mem[r].hh.lh<>3584 then{402:}begin scannerstatus:=3;
unbalance:=0;longstate:=eqtb[curcs].hh.b0;
if longstate>=128 then longstate:=longstate-2;
repeat mem[memtop-3].hh.rh:=-1073741823;
if(mem[r].hh.lh>3583)or(mem[r].hh.lh<3328)then s:=-1073741823 else begin
matchchr:=mem[r].hh.lh-3328;s:=mem[r].hh.rh;r:=s;p:=memtop-3;m:=0;end;
{403:}22:gettoken;
if curtok=mem[r].hh.lh then{405:}begin r:=mem[r].hh.rh;
if(mem[r].hh.lh>=3328)and(mem[r].hh.lh<=3584)then begin if curtok<512
then decr(alignstate);goto 40;end else goto 22;end{:405};
{408:}if s<>r then if s=-1073741823 then{409:}begin begin if interaction
=3 then;if filelineerrorstylep then printfileline else printnl(263);
print(691);end;sprintcs(warningindex);print(692);begin helpptr:=4;
helpline[3]:=693;helpline[2]:=694;helpline[1]:=695;helpline[0]:=696;end;
error;goto 10;end{:409}else begin t:=s;repeat begin q:=getavail;
mem[p].hh.rh:=q;mem[q].hh.lh:=mem[t].hh.lh;p:=q;end;incr(m);
u:=mem[t].hh.rh;v:=s;
while true do begin if u=r then if curtok<>mem[v].hh.lh then goto 30
else begin r:=mem[v].hh.rh;goto 22;end;
if mem[u].hh.lh<>mem[v].hh.lh then goto 30;u:=mem[u].hh.rh;
v:=mem[v].hh.rh;end;30:t:=mem[t].hh.rh;until t=r;r:=s;end{:408};
if curtok=partoken then if longstate<>127 then{407:}begin if longstate=
126 then begin runaway;begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(686);
end;sprintcs(warningindex);print(687);begin helpptr:=3;helpline[2]:=688;
helpline[1]:=689;helpline[0]:=690;end;backerror;end;
pstack[n]:=mem[memtop-3].hh.rh;alignstate:=alignstate-unbalance;
for m:=0 to n do flushlist(pstack[m]);goto 10;end{:407};
if curtok<768 then if curtok<512 then{410:}begin unbalance:=1;
while true do begin begin begin q:=avail;
if q=-1073741823 then q:=getavail else begin avail:=mem[q].hh.rh;
mem[q].hh.rh:=-1073741823;ifdef('STAT')incr(dynused);endif('STAT')end;
end;mem[p].hh.rh:=q;mem[q].hh.lh:=curtok;p:=q;end;gettoken;
if curtok=partoken then if longstate<>127 then{407:}begin if longstate=
126 then begin runaway;begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(686);
end;sprintcs(warningindex);print(687);begin helpptr:=3;helpline[2]:=688;
helpline[1]:=689;helpline[0]:=690;end;backerror;end;
pstack[n]:=mem[memtop-3].hh.rh;alignstate:=alignstate-unbalance;
for m:=0 to n do flushlist(pstack[m]);goto 10;end{:407};
if curtok<768 then if curtok<512 then incr(unbalance)else begin decr(
unbalance);if unbalance=0 then goto 31;end;end;31:rbraceptr:=p;
begin q:=getavail;mem[p].hh.rh:=q;mem[q].hh.lh:=curtok;p:=q;end;
end{:410}else{406:}begin backinput;begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(678);
end;sprintcs(warningindex);print(679);begin helpptr:=6;helpline[5]:=680;
helpline[4]:=681;helpline[3]:=682;helpline[2]:=683;helpline[1]:=684;
helpline[0]:=685;end;incr(alignstate);longstate:=126;curtok:=partoken;
inserror;goto 22;
end{:406}else{404:}begin if curtok=2592 then if mem[r].hh.lh<=3584 then
if mem[r].hh.lh>=3328 then goto 22;begin q:=getavail;mem[p].hh.rh:=q;
mem[q].hh.lh:=curtok;p:=q;end;end{:404};incr(m);
if mem[r].hh.lh>3584 then goto 22;if mem[r].hh.lh<3328 then goto 22;
40:if s<>-1073741823 then{411:}begin if(m=1)and(mem[p].hh.lh<768)and(p<>
memtop-3)then begin mem[rbraceptr].hh.rh:=-1073741823;
begin mem[p].hh.rh:=avail;avail:=p;ifdef('STAT')decr(dynused);
endif('STAT')end;p:=mem[memtop-3].hh.rh;pstack[n]:=mem[p].hh.rh;
begin mem[p].hh.rh:=avail;avail:=p;ifdef('STAT')decr(dynused);
endif('STAT')end;end else pstack[n]:=mem[memtop-3].hh.rh;incr(n);
if eqtb[28492].int>0 then begin begindiagnostic;printnl(matchchr);
printint(n);print(697);showtokenlist(pstack[n-1],-1073741823,1000);
enddiagnostic(false);end;end{:411}{:403};until mem[r].hh.lh=3584;
end{:402};
{401:}while(curinput.statefield=0)and(curinput.locfield=-1073741823)and(
curinput.indexfield<>2)do endtokenlist;begintokenlist(refcount,5);
curinput.namefield:=warningindex;curinput.locfield:=mem[r].hh.rh;
if n>0 then begin if paramptr+n>maxparamstack then begin maxparamstack:=
paramptr+n;if maxparamstack>paramsize then overflow(677,paramsize);end;
for m:=0 to n-1 do paramstack[paramptr+m]:=pstack[m];
paramptr:=paramptr+n;end{:401};10:scannerstatus:=savescannerstatus;
warningindex:=savewarningindex;end;{:400}{390:}procedure insertrelax;
begin curtok:=536870911+curcs;backinput;curtok:=536886432;backinput;
curinput.indexfield:=4;end;{:390}procedure passtext;forward;
procedure startinput;forward;procedure conditional;forward;
procedure getxtoken;forward;procedure convtoks;forward;
procedure insthetoks;forward;procedure expand;var t:halfword;
p,q,r:halfword;j:0..bufsize;cvbackup:integer;
cvlbackup,radixbackup,cobackup:smallnumber;backupbackup:halfword;
savescannerstatus:smallnumber;begin incr(expanddepthcount);
if expanddepthcount>=expanddepth then overflow(659,expanddepth);
cvbackup:=curval;cvlbackup:=curvallevel;radixbackup:=radix;
cobackup:=curorder;backupbackup:=mem[memtop-13].hh.rh;
if curcmd<126 then{378:}begin if eqtb[28498].int>1 then showcurcmdchr;
case curcmd of 125:{397:}begin if curmark[curchr]<>-1073741823 then
begintokenlist(curmark[curchr],14);end{:397};117:{379:}begin gettoken;
t:=curtok;gettoken;if curcmd>115 then expand else backinput;curtok:=t;
backinput;end{:379};118:{380:}begin savescannerstatus:=scannerstatus;
scannerstatus:=0;gettoken;scannerstatus:=savescannerstatus;t:=curtok;
backinput;if t>=536870911 then begin p:=getavail;
mem[p].hh.lh:=536886434;mem[p].hh.rh:=curinput.locfield;
curinput.startfield:=p;curinput.locfield:=p;end;end{:380};
122:{383:}begin r:=getavail;p:=r;repeat getxtoken;
if curcs=0 then begin q:=getavail;mem[p].hh.rh:=q;mem[q].hh.lh:=curtok;
p:=q;end;until curcs<>0;
if curcmd<>72 then{384:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(666);
end;printesc(540);print(667);begin helpptr:=2;helpline[1]:=668;
helpline[0]:=669;end;backerror;end{:384};{385:}j:=first;p:=mem[r].hh.rh;
while p<>-1073741823 do begin if j>=maxbufstack then begin maxbufstack:=
j+1;if maxbufstack=bufsize then overflow(257,bufsize);end;
if checkkanji(mem[p].hh.lh)then begin t:=toBUFF(mem[p].hh.lh mod
16777216);if BYTE1(t)<>0 then begin buffer[j]:=BYTE1(t);incr(j);end;
if BYTE2(t)<>0 then begin buffer[j]:=BYTE2(t);incr(j);end;
if BYTE3(t)<>0 then begin buffer[j]:=BYTE3(t);incr(j);end;
buffer[j]:=BYTE4(t);incr(j);p:=mem[p].hh.rh;
end else begin buffer[j]:=mem[p].hh.lh mod 256;incr(j);p:=mem[p].hh.rh;
end;end;if j>first+1 then begin nonewcontrolsequence:=false;
curcs:=idlookup(first,j-first);nonewcontrolsequence:=true;
end else if j=first then curcs:=513 else curcs:=257+buffer[first]{:385};
flushlist(r);if eqtb[curcs].hh.b0=116 then begin eqdefine(curcs,0,256);
end;curtok:=curcs+536870911;backinput;end{:383};123:convtoks;
124:insthetoks;120:conditional;
121:{521:}if curchr>iflimit then if iflimit=1 then insertrelax else
begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(832);
end;printcmdchr(121,curchr);begin helpptr:=1;helpline[0]:=833;end;error;
end else begin while curchr<>2 do passtext;{507:}begin p:=condptr;
ifline:=mem[p+1].int;curif:=mem[p].hh.b1;iflimit:=mem[p].hh.b0;
condptr:=mem[p].hh.rh;freenode(p,2);end{:507};end{:521};
119:{389:}if curchr>0 then forceeof:=true else if nameinprogress then
insertrelax else startinput{:389};
others:{381:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(660);
end;begin helpptr:=5;helpline[4]:=661;helpline[3]:=662;helpline[2]:=663;
helpline[1]:=664;helpline[0]:=665;end;error;end{:381}end;
end{:378}else if curcmd<130 then macrocall else{386:}begin curtok:=
536886431;backinput;end{:386};curval:=cvbackup;curvallevel:=cvlbackup;
radix:=radixbackup;curorder:=cobackup;
mem[memtop-13].hh.rh:=backupbackup;decr(expanddepthcount);end;
{:377}{391:}procedure getxtoken;label 20,30;begin 20:getnext;
if curcmd<=115 then goto 30;
if curcmd>=126 then if curcmd<130 then macrocall else begin curcs:=15520
;curcmd:=9;goto 30;end else expand;goto 20;
30:if curcs=0 then if(curcmd>=16)and(curcmd<=19)then curtok:=(curcmd
*16777216)+curchr else curtok:=(curcmd*256)+curchr else curtok:=
536870911+curcs;end;{:391}{392:}procedure xtoken;
begin while curcmd>115 do begin expand;getnext;end;
if curcs=0 then if(curcmd>=16)and(curcmd<=19)then curtok:=(curcmd
*16777216)+curchr else curtok:=(curcmd*256)+curchr else curtok:=
536870911+curcs;end;{:392}{414:}procedure scanleftbrace;
begin{415:}repeat getxtoken;until(curcmd<>10)and(curcmd<>0){:415};
if curcmd<>1 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(698);
end;begin helpptr:=4;helpline[3]:=699;helpline[2]:=700;helpline[1]:=701;
helpline[0]:=702;end;backerror;curtok:=379;curcmd:=1;curchr:=123;
incr(alignstate);end;end;{:414}{416:}procedure scanoptionalequals;
begin{417:}repeat getxtoken;until curcmd<>10{:417};
if curtok<>3133 then backinput;end;
{:416}{418:}function scankeyword(s:strnumber):boolean;label 10;
var p:halfword;q:halfword;k:poolpointer;begin p:=memtop-13;
mem[p].hh.rh:=-1073741823;k:=strstart[s];
while k<strstart[s+1]do begin getxtoken;
if(curcs=0)and((curchr=strpool[k])or(curchr=strpool[k]-32))then begin
begin q:=getavail;mem[p].hh.rh:=q;mem[q].hh.lh:=curtok;p:=q;end;incr(k);
end else if(curcmd<>10)or(p<>memtop-13)then begin backinput;
if p<>memtop-13 then begintokenlist(mem[memtop-13].hh.rh,3);
scankeyword:=false;goto 10;end;end;flushlist(mem[memtop-13].hh.rh);
scankeyword:=true;10:end;{:418}{419:}procedure muerror;
begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(703);
end;begin helpptr:=1;helpline[0]:=704;end;error;end;
{:419}{420:}procedure scanint;forward;{444:}procedure scaneightbitint;
begin scanint;
if(curval<0)or(curval>255)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(728);
end;begin helpptr:=2;helpline[1]:=729;helpline[0]:=730;end;
interror(curval);curval:=0;end;end;{:444}{445:}procedure scancharnum;
begin scanint;
if not ischarascii(curval)and not ischarkanji(curval)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(731);
end;begin helpptr:=2;helpline[1]:=732;helpline[0]:=730;end;
interror(curval);curval:=0;end;end;{:445}{446:}procedure scanfourbitint;
begin scanint;
if(curval<0)or(curval>15)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(733);
end;begin helpptr:=2;helpline[1]:=734;helpline[0]:=730;end;
interror(curval);curval:=0;end;end;
{:446}{447:}procedure scanfifteenbitint;begin scanint;
if(curval<0)or(curval>32767)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(735);
end;begin helpptr:=2;helpline[1]:=736;helpline[0]:=730;end;
interror(curval);curval:=0;end;end;
{:447}{448:}procedure scantwentysevenbitint;begin scanint;
if(curval<0)or(curval>134217727)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(737);
end;begin helpptr:=2;helpline[1]:=738;helpline[0]:=730;end;
interror(curval);curval:=0;end;end;
{:448}{1399:}procedure scanfourbitintor18;begin scanint;
if(curval<0)or((curval>15)and(curval<>18))then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(733);
end;begin helpptr:=2;helpline[1]:=734;helpline[0]:=730;end;
interror(curval);curval:=0;end;end;{:1399}{588:}procedure scanfontident;
var f:internalfontnumber;m:halfword;begin{417:}repeat getxtoken;
until curcmd<>10{:417};
if curcmd=100 then f:=eqtb[25631].hh.rh else if curcmd=101 then f:=eqtb[
25632].hh.rh else if curcmd=99 then f:=eqtb[25582].hh.rh else if curcmd=
98 then f:=curchr else if curcmd=97 then begin m:=curchr;scanfourbitint;
f:=eqtb[m+curval].hh.rh;end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(872);
end;begin helpptr:=2;helpline[1]:=873;helpline[0]:=874;end;backerror;
f:=0;end;curval:=f;end;
{:588}{589:}procedure findfontdimen(writing:boolean);
var f:internalfontnumber;n:integer;begin scanint;n:=curval;
scanfontident;f:=curval;
if n<=0 then curval:=fmemptr else begin if writing and(n<=4)and(n>=2)and
(fontglue[f]<>-1073741823)then begin deleteglueref(fontglue[f]);
fontglue[f]:=-1073741823;end;
if n>fontparams[f]then if f<fontptr then curval:=fmemptr else{591:}begin
repeat if fmemptr=fontmemsize then overflow(879,fontmemsize);
fontinfo[fmemptr].int:=0;incr(fmemptr);incr(fontparams[f]);
until n=fontparams[f];curval:=fmemptr-1;
end{:591}else curval:=n+parambase[f];end;
{590:}if curval=fmemptr then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(857);
end;printesc(hash[15525+f].rh);print(875);printint(fontparams[f]);
print(876);begin helpptr:=2;helpline[1]:=877;helpline[0]:=878;end;error;
end{:590};end;{:589}{1449:}function getjfmpos(kcode:KANJIcode;
f:internalfontnumber):eightbits;var jc:KANJIcode;sp,mp,ep:halfword;
begin if f=0 then begin getjfmpos:=fontinfo[ctypebase[0]+0].hh.lhfield;
goto 10;end;jc:=toDVI(kcode);sp:=1;ep:=fontnumext[f]-1;
if(ep>=1)and(fontinfo[ctypebase[f]+sp].hh.rh<=jc)and(jc<=fontinfo[
ctypebase[f]+ep].hh.rh)then begin while(sp<=ep)do begin mp:=sp+((ep-sp)
div 2);
if jc<fontinfo[ctypebase[f]+mp].hh.rh then ep:=mp-1 else if jc>fontinfo[
ctypebase[f]+mp].hh.rh then sp:=mp+1 else begin getjfmpos:=fontinfo[
ctypebase[f]+mp].hh.lhfield;goto 10;end;end;end;
getjfmpos:=fontinfo[ctypebase[f]+0].hh.lhfield;end;
{:1449}{:420}{424:}{1458:}procedure printkansuji(n:integer);var k:0..23;
cx:KANJIcode;begin k:=0;if n<0 then goto 10;repeat dig[k]:=n mod 10;
n:=n div 10;incr(k);until n=0;begin while k>0 do begin decr(k);
cx:=eqtb[27172+dig[k]].hh.rh;printkanji(fromDVI(cx));end;end;end;
{:1458}{1468:}function getinhibitpos(c:KANJIcode;
n:smallnumber):halfword;label 30,31;var p,s:halfword;
begin s:=calcpos(c);p:=s;
if n=0 then begin repeat if(eqtb[26660+p].hh.rh=0)or(eqtb[26660+p].hh.rh
=c)then goto 30;incr(p);if p>255 then p:=0;until s=p;p:=1000;
end else begin repeat if eqtb[26660+p].hh.rh=0 then goto 31;
if eqtb[26660+p].hh.rh=c then goto 30;incr(p);if p>255 then p:=0;
until s=p;31:p:=1000;end;30:getinhibitpos:=p;end;
{:1468}{1473:}function getkinsokupos(c:KANJIcode;
n:smallnumber):halfword;label 30,31;var p,s:halfword;
begin s:=calcpos(c);p:=s;ifdef('TEXMF_DEBUG')println;print(1428);
printint(c);print(1429);printint(s);if p+26916<0 then begin print(1430);
println;end;
endif('TEXMF_DEBUG')if n=0 then begin repeat if(eqtb[26916+p].hh.b0=0)or
(eqtb[26916+p].hh.rh=c)then goto 30;incr(p);if p>255 then p:=0;
until s=p;p:=1000;
end else begin repeat if eqtb[26916+p].hh.b0=0 then goto 31;
if eqtb[26916+p].hh.rh=c then goto 30;incr(p);if p>255 then p:=0;
until s=p;31:p:=1000;end;30:getkinsokupos:=p;end;
{:1473}procedure scansomethinginternal(level:smallnumber;
negative:boolean);var m:halfword;tx:halfword;qx:halfword;p:0..nestsize;
q,r:halfword;begin m:=curchr;case curcmd of 87:{1475:}begin scanint;
q:=getkinsokupos(curval,1);curvallevel:=0;curval:=0;
if(q<>1000)and(m=eqtb[26916+q].hh.b0)then begin curval:=eqtb[29317+q].
int;curvallevel:=0;end;end{:1475};88:{1470:}begin scanint;
q:=getinhibitpos(curval,1);curvallevel:=0;curval:=3;
if q<>1000 then curval:=eqtb[26660+q].hh.b0;end{:1470};
96:{425:}begin scancharnum;
if m=27950 then begin curval:=eqtb[27950+curval].hh.rh;curvallevel:=0;
end else if m=25892 then begin curval:=eqtb[m+kcatcodekey(curval)].hh.rh
;curvallevel:=0;
end else if m<27950 then begin if not ischarascii(curval)then begin
curval:=eqtb[m+Hi(curval)].hh.rh;curvallevel:=0;
end else begin curval:=eqtb[m+curval].hh.rh;curvallevel:=0;
end end else begin if not ischarascii(curval)then begin curval:=eqtb[m+
Hi(curval)].int;curvallevel:=0;
end else begin curval:=eqtb[m+curval].int;curvallevel:=0;end end;
end{:425};
79,80,97,98,99,100,101:{426:}if level<>5 then begin begin if interaction
=3 then;if filelineerrorstylep then printfileline else printnl(263);
print(705);end;begin helpptr:=3;helpline[2]:=706;helpline[1]:=707;
helpline[0]:=708;end;backerror;begin curval:=0;curvallevel:=1;end;
end else if curcmd<=80 then begin if curcmd<80 then begin
scaneightbitint;m:=25070+curval;end;begin curval:=eqtb[m].hh.rh;
curvallevel:=5;end;end else begin backinput;scanfontident;
begin curval:=15525+curval;curvallevel:=4;end;end{:426};
81:begin curval:=eqtb[m].int;curvallevel:=0;end;
82:begin curval:=eqtb[m].int;curvallevel:=1;end;
83:begin curval:=eqtb[m].hh.rh;curvallevel:=2;end;
84:begin curval:=eqtb[m].hh.rh;curvallevel:=3;end;
90:{429:}if abs(curlist.modefield)<>m then begin begin if interaction=3
then;if filelineerrorstylep then printfileline else printnl(263);
print(721);end;printcmdchr(90,m);begin helpptr:=4;helpline[3]:=722;
helpline[2]:=723;helpline[1]:=724;helpline[0]:=725;end;error;
if level<>5 then begin curval:=0;curvallevel:=1;
end else begin curval:=0;curvallevel:=0;end;
end else if m=1 then begin curval:=curlist.auxfield.int;curvallevel:=1;
end else begin curval:=curlist.auxfield.hh.lh;curvallevel:=0;end{:429};
91:{433:}if curlist.modefield=0 then begin curval:=0;curvallevel:=0;
end else begin nest[nestptr]:=curlist;p:=nestptr;
while abs(nest[p].modefield)<>1 do decr(p);
begin curval:=nest[p].pgfield;curvallevel:=0;end;end{:433};
93:{430:}begin if m=0 then curval:=deadcycles else curval:=
insertpenalties;curvallevel:=0;end{:430};
92:{432:}begin if(pagecontents=0)and(not outputactive)then if m=0 then
curval:=1073741823 else curval:=0 else curval:=pagesofar[m];
curvallevel:=1;end{:432};
95:{434:}begin if eqtb[25060].hh.rh=-1073741823 then curval:=0 else
curval:=mem[eqtb[25060].hh.rh].hh.lh;curvallevel:=0;end{:434};
94:{431:}begin scaneightbitint;q:=eqtb[25326+curval].hh.rh;
if q=-1073741823 then curval:=0 else begin qx:=q;
while(q<>-1073741823)and((mem[q].hh.b1)<>abs(curlist.dirfield))do q:=mem
[q].hh.rh;if q=-1073741823 then begin r:=mem[qx].hh.rh;
mem[qx].hh.rh:=-1073741823;q:=newdirnode(qx,abs(curlist.dirfield));
mem[qx].hh.rh:=r;curval:=mem[q+m].int;deleteglueref(mem[q+7].hh.rh);
deleteglueref(mem[q+7].hh.lh);freenode(q,10);
end else curval:=mem[q+m].int;end;curvallevel:=1;end{:431};
74,73,75:begin curval:=curchr;curvallevel:=0;end;
85:{436:}begin findfontdimen(false);fontinfo[fmemptr].int:=0;
begin curval:=fontinfo[curval].int;curvallevel:=1;end;end{:436};
86:{437:}begin scanfontident;
if m=0 then begin curval:=hyphenchar[curval];curvallevel:=0;
end else begin curval:=skewchar[curval];curvallevel:=0;end;end{:437};
102:{438:}begin scaneightbitint;
case m of 0:curval:=eqtb[28526+curval].int;
1:curval:=eqtb[29061+curval].int;2:curval:=eqtb[24548+curval].hh.rh;
3:curval:=eqtb[24804+curval].hh.rh;end;curvallevel:=m;end{:438};
76:{435:}if curchr>2 then begin if curchr=3 then curval:=line else
curval:=lastbadness;curvallevel:=0;
end else begin if curchr=2 then curval:=membot else curval:=0;
tx:=curlist.tailfield;
if not(tx>=himemmin)then if mem[tx].hh.b0=5 then begin tx:=curlist.
pnodefield;
if not(tx>=himemmin)then if mem[tx].hh.b0=5 then begin tx:=curlist.
headfield;q:=mem[curlist.headfield].hh.rh;
while q<>curlist.pnodefield do begin if(q>=himemmin)then tx:=q else if
mem[q].hh.b0<>5 then tx:=q;end;q:=mem[q].hh.rh;end;end;
curvallevel:=curchr;
if not(tx>=himemmin)and(tx<>curlist.headfield)and(curlist.modefield<>0)
then case curchr of 0:if mem[tx].hh.b0=14 then curval:=mem[tx+1].int;
1:if mem[tx].hh.b0=13 then curval:=mem[tx+1].int;
2:if mem[tx].hh.b0=12 then begin curval:=mem[tx+1].hh.lh;
if mem[tx].hh.b1=99 then curvallevel:=3;end;
end else if(curlist.modefield=1)and(tx=curlist.headfield)then case
curchr of 0:curval:=lastpenalty;1:curval:=lastkern;
2:if lastglue<>1073741823 then curval:=lastglue;end;end{:435};
others:{439:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(726);
end;printcmdchr(curcmd,curchr);print(727);printesc(575);
begin helpptr:=1;helpline[0]:=725;end;error;
if level<>5 then begin curval:=0;curvallevel:=1;
end else begin curval:=0;curvallevel:=0;end;end{:439}end;
while curvallevel>level do{440:}begin if curvallevel=2 then curval:=mem[
curval+1].int else if curvallevel=3 then muerror;decr(curvallevel);
end{:440};
{441:}if negative then if curvallevel>=2 then begin curval:=newspec(
curval);{442:}begin mem[curval+1].int:=-mem[curval+1].int;
mem[curval+2].int:=-mem[curval+2].int;
mem[curval+3].int:=-mem[curval+3].int;end{:442};
end else curval:=-curval else if(curvallevel>=2)and(curvallevel<=3)then
incr(mem[curval].hh.rh){:441};end;{:424}{451:}procedure scanint;
label 30;var negative:boolean;m:integer;d:smallnumber;vacuous:boolean;
OKsofar:boolean;begin radix:=0;OKsofar:=true;{452:}negative:=false;
repeat{417:}repeat getxtoken;until curcmd<>10{:417};
if curtok=3117 then begin negative:=not negative;curtok:=3115;end;
until curtok<>3115{:452};if curtok=3168 then{453:}begin gettoken;
if curtok<536870911 then if(curcmd>=16)and(curcmd<=19)then begin
skipmode:=false;curval:=curchr;end else begin curval:=curchr;
if curcmd<=2 then if curcmd=2 then incr(alignstate)else decr(alignstate)
;
end else if curtok<536871168 then curval:=curtok-536870912 else curval:=
curtok-536871168;
if(curval>255)and((curcmd<16)or(curcmd>19))then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(739);
end;begin helpptr:=2;helpline[1]:=740;helpline[0]:=741;end;curval:=48;
backerror;end else{454:}begin getxtoken;if curcmd<>10 then backinput;
end{:454};skipmode:=true;
end{:453}else if(curcmd>=73)and(curcmd<=102)then scansomethinginternal(0
,false)else{455:}begin radix:=10;m:=214748364;
if curtok=3111 then begin radix:=8;m:=268435456;getxtoken;
end else if curtok=3106 then begin radix:=16;m:=134217728;getxtoken;end;
vacuous:=true;curval:=0;
{456:}while true do begin if(curtok<3120+radix)and(curtok>=3120)and(
curtok<=3129)then d:=curtok-3120 else if radix=16 then if(curtok<=2886)
and(curtok>=2881)then d:=curtok-2871 else if(curtok<=3142)and(curtok>=
3137)then d:=curtok-3127 else goto 30 else goto 30;vacuous:=false;
if(curval>=m)and((curval>m)or(d>7)or(radix<>10))then begin if OKsofar
then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(742);
end;begin helpptr:=2;helpline[1]:=743;helpline[0]:=744;end;error;
curval:=2147483647;OKsofar:=false;end;end else curval:=curval*radix+d;
getxtoken;end;30:{:456};
if vacuous then{457:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(705);
end;begin helpptr:=3;helpline[2]:=706;helpline[1]:=707;helpline[0]:=708;
end;backerror;end{:457}else if curcmd<>10 then backinput;end{:455};
if negative then curval:=-curval;end;
{:451}{459:}procedure scandimen(mu,inf,shortcut:boolean);
label 30,31,32,40,45,88,89;var negative:boolean;f:integer;
{461:}num,denom:1..65536;k,kk:smallnumber;p,q:halfword;v:scaled;
savecurval:integer;{:461}{1450:}t:eightbits;{:1450}begin f:=0;
aritherror:=false;curorder:=0;negative:=false;
if not shortcut then begin{452:}negative:=false;
repeat{417:}repeat getxtoken;until curcmd<>10{:417};
if curtok=3117 then begin negative:=not negative;curtok:=3115;end;
until curtok<>3115{:452};
if(curcmd>=73)and(curcmd<=102)then{460:}if mu then begin
scansomethinginternal(3,false);
{462:}if curvallevel>=2 then begin v:=mem[curval+1].int;
deleteglueref(curval);curval:=v;end{:462};if curvallevel=3 then goto 89;
if curvallevel<>0 then muerror;
end else begin scansomethinginternal(1,false);
if curvallevel=1 then goto 89;end{:460}else begin backinput;
if curtok=3116 then curtok:=3118;
if curtok<>3118 then scanint else begin radix:=10;curval:=0;end;
if curtok=3116 then curtok:=3118;
if(radix=10)and(curtok=3118)then{463:}begin k:=0;p:=-1073741823;
gettoken;while true do begin getxtoken;
if(curtok>3129)or(curtok<3120)then goto 31;
if k<17 then begin q:=getavail;mem[q].hh.rh:=p;
mem[q].hh.lh:=curtok-3120;p:=q;incr(k);end;end;
31:for kk:=k downto 1 do begin dig[kk-1]:=mem[p].hh.lh;q:=p;
p:=mem[p].hh.rh;begin mem[q].hh.rh:=avail;avail:=q;
ifdef('STAT')decr(dynused);endif('STAT')end;end;f:=rounddecimals(k);
if curcmd<>10 then backinput;end{:463};end;end;
if curval<0 then begin negative:=not negative;curval:=-curval;end;
{464:}if inf then{465:}if scankeyword(315)then begin curorder:=1;
while scankeyword(108)do begin if curorder=3 then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(746);
end;print(747);begin helpptr:=1;helpline[0]:=748;end;error;
end else incr(curorder);end;goto 88;end{:465};{466:}savecurval:=curval;
{417:}repeat getxtoken;until curcmd<>10{:417};
if(curcmd<73)or(curcmd>102)then backinput else begin if mu then begin
scansomethinginternal(3,false);
{462:}if curvallevel>=2 then begin v:=mem[curval+1].int;
deleteglueref(curval);curval:=v;end{:462};
if curvallevel<>3 then muerror;end else scansomethinginternal(1,false);
v:=curval;goto 40;end;if mu then goto 45;
if scankeyword(749)then v:=({569:}fontinfo[6+parambase[eqtb[25582].hh.rh
]].int{:569})else if scankeyword(750)then v:=({570:}fontinfo[5+parambase
[eqtb[25582].hh.rh]].int{:570})else if scankeyword(751)then{1451:}if
curlist.dirfield=3 then v:=fontinfo[widthbase[eqtb[25632].hh.rh]+
fontinfo[charbase[eqtb[25632].hh.rh]+0].qqqq.b0].int else v:=fontinfo[
widthbase[eqtb[25631].hh.rh]+fontinfo[charbase[eqtb[25631].hh.rh]+0].
qqqq.b0].int{:1451}else if scankeyword(752)then{1452:}if curlist.
dirfield=3 then begin t:=fontinfo[charbase[eqtb[25632].hh.rh]+0].qqqq.b1
;v:=fontinfo[heightbase[eqtb[25632].hh.rh]+(t)div 16].int+fontinfo[
depthbase[eqtb[25632].hh.rh]+(t)mod 16].int;
end else begin t:=fontinfo[charbase[eqtb[25631].hh.rh]+0].qqqq.b1;
v:=fontinfo[heightbase[eqtb[25631].hh.rh]+(t)div 16].int+fontinfo[
depthbase[eqtb[25631].hh.rh]+(t)mod 16].int;end{:1452}else goto 45;
{454:}begin getxtoken;if curcmd<>10 then backinput;end{:454};
40:curval:=multandadd(savecurval,v,xnoverd(v,f,65536),1073741823);
goto 89;45:{:466};
if mu then{467:}if scankeyword(343)then goto 88 else begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(746);
end;print(753);begin helpptr:=4;helpline[3]:=754;helpline[2]:=755;
helpline[1]:=756;helpline[0]:=757;end;error;goto 88;end{:467};
if scankeyword(745)then{468:}begin preparemag;
if eqtb[28479].int<>1000 then begin curval:=xnoverd(curval,1000,eqtb[
28479].int);f:=(1000*f+65536*texremainder)div eqtb[28479].int;
curval:=curval+(f div 65536);f:=f mod 65536;end;end{:468};
if scankeyword(416)then goto 88;
{469:}if scankeyword(758)then begin num:=7227;denom:=100;
end else if scankeyword(759)then begin num:=12;denom:=1;
end else if scankeyword(760)then begin num:=7227;denom:=254;
end else if scankeyword(761)then begin num:=7227;denom:=2540;
end else if scankeyword(762)then begin num:=7227;denom:=7200;
end else if scankeyword(763)then begin num:=1238;denom:=1157;
end else if scankeyword(764)then begin num:=14856;denom:=1157;
end else if scankeyword(72)then begin num:=7227;denom:=10160;
end else if scankeyword(81)then begin num:=7227;denom:=10160;
end else if scankeyword(765)then goto 30 else{470:}begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(746);
end;print(766);begin helpptr:=6;helpline[5]:=767;helpline[4]:=768;
helpline[3]:=769;helpline[2]:=755;helpline[1]:=756;helpline[0]:=757;end;
error;goto 32;end{:470};curval:=xnoverd(curval,num,denom);
f:=(num*f+65536*texremainder)div denom;curval:=curval+(f div 65536);
f:=f mod 65536;32:{:469};
88:if curval>=16384 then aritherror:=true else curval:=curval*65536+f;
30:{:464};{454:}begin getxtoken;if curcmd<>10 then backinput;end{:454};
89:if aritherror or(abs(curval)>=1073741824)then{471:}begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(770);
end;begin helpptr:=2;helpline[1]:=771;helpline[0]:=772;end;error;
curval:=1073741823;aritherror:=false;end{:471};
if negative then curval:=-curval;end;
{:459}{472:}procedure scanglue(level:smallnumber);label 10;
var negative:boolean;q:halfword;mu:boolean;begin mu:=(level=3);
{452:}negative:=false;repeat{417:}repeat getxtoken;
until curcmd<>10{:417};if curtok=3117 then begin negative:=not negative;
curtok:=3115;end;until curtok<>3115{:452};
if(curcmd>=73)and(curcmd<=102)then begin scansomethinginternal(level,
negative);
if curvallevel>=2 then begin if curvallevel<>level then muerror;goto 10;
end;if curvallevel=0 then scandimen(mu,false,true)else if level=3 then
muerror;end else begin backinput;scandimen(mu,false,false);
if negative then curval:=-curval;end;{473:}q:=newspec(membot);
mem[q+1].int:=curval;
if scankeyword(773)then begin scandimen(mu,true,false);
mem[q+2].int:=curval;mem[q].hh.b0:=curorder;end;
if scankeyword(774)then begin scandimen(mu,true,false);
mem[q+3].int:=curval;mem[q].hh.b1:=curorder;end;curval:=q{:473};10:end;
{:472}{474:}function scanrulespec:halfword;label 21;var q:halfword;
begin q:=newrule;
if curcmd=39 then mem[q+1].int:=26214 else begin mem[q+3].int:=26214;
mem[q+2].int:=0;end;
21:if scankeyword(775)then begin scandimen(false,false,false);
mem[q+1].int:=curval;goto 21;end;
if scankeyword(776)then begin scandimen(false,false,false);
mem[q+3].int:=curval;goto 21;end;
if scankeyword(777)then begin scandimen(false,false,false);
mem[q+2].int:=curval;goto 21;end;scanrulespec:=q;end;
{:474}{475:}function strtoks(b:poolpointer):halfword;var p:halfword;
q:halfword;t:halfword;k:poolpointer;cc:0..19;
begin begin if poolptr+1>poolsize then overflow(258,poolsize-initpoolptr
);end;p:=memtop-3;mem[p].hh.rh:=-1073741823;k:=b;
while k<poolptr do begin t:=fromBUFF(ustringcast(strpool),poolptr,k);
cc:=eqtb[25892+kcatcodekey(t)].hh.rh;
if(multistrlen(ustringcast(strpool),poolptr,k)>1)and checkkcatcode(cc)
then begin if(cc=15)then cc:=18;t:=t+cc*16777216;
k:=k+multistrlen(ustringcast(strpool),poolptr,k)-1;
end else begin t:=strpool[k];if t=32 then t:=2592 else t:=3072+t;end;
begin begin q:=avail;
if q=-1073741823 then q:=getavail else begin avail:=mem[q].hh.rh;
mem[q].hh.rh:=-1073741823;ifdef('STAT')incr(dynused);endif('STAT')end;
end;mem[p].hh.rh:=q;mem[q].hh.lh:=t;p:=q;end;incr(k);end;poolptr:=b;
strtoks:=p;end;{:475}{476:}function thetoks:halfword;
var oldsetting:0..21;p,q,r:halfword;b:poolpointer;begin getxtoken;
scansomethinginternal(5,false);
if curvallevel>=4 then{477:}begin p:=memtop-3;mem[p].hh.rh:=-1073741823;
if curvallevel=4 then begin q:=getavail;mem[p].hh.rh:=q;
mem[q].hh.lh:=536870911+curval;p:=q;
end else if curval<>-1073741823 then begin r:=mem[curval].hh.rh;
while r<>-1073741823 do begin begin begin q:=avail;
if q=-1073741823 then q:=getavail else begin avail:=mem[q].hh.rh;
mem[q].hh.rh:=-1073741823;ifdef('STAT')incr(dynused);endif('STAT')end;
end;mem[p].hh.rh:=q;mem[q].hh.lh:=mem[r].hh.lh;p:=q;end;r:=mem[r].hh.rh;
end;end;thetoks:=p;end{:477}else begin oldsetting:=selector;
selector:=21;b:=poolptr;case curvallevel of 0:printint(curval);
1:begin printscaled(curval);print(416);end;
2:begin printspec(curval,416);deleteglueref(curval);end;
3:begin printspec(curval,343);deleteglueref(curval);end;end;
selector:=oldsetting;thetoks:=strtoks(b);end;end;
{:476}{478:}procedure insthetoks;begin mem[memtop-12].hh.rh:=thetoks;
begintokenlist(mem[memtop-3].hh.rh,4);end;
{:478}{481:}procedure convtoks;var oldsetting:0..21;cx:KANJIcode;
c:0..11;savescannerstatus:smallnumber;b:poolpointer;begin c:=curchr;
{482:}cx:=0;case c of 0,1,2,6,7,8,9,10:scanint;
3,4:begin savescannerstatus:=scannerstatus;scannerstatus:=0;gettoken;
if(curcmd>=16)and(curcmd<=19)then cx:=curtok;
scannerstatus:=savescannerstatus;end;5:scanfontident;
11:if jobname=0 then openlogfile;end{:482};oldsetting:=selector;
selector:=21;b:=poolptr;{483:}case c of 0:printint(curval);
1:printromanint(curval);8:printint(fromJIS(curval));
6:printint(fromEUC(curval));7:printint(fromSJIS(curval));
9:printint(fromKUTEN(curval));10:printint(fromUCS(curval));
2:printkansuji(curval);
3:if curcs<>0 then sprintcs(curcs)else if cx=0 then printchar(curchr)
else printkanji(cx);4:printmeaning;5:begin print(fontname[curval]);
if fontsize[curval]<>fontdsize[curval]then begin print(790);
printscaled(fontsize[curval]);print(416);end;end;11:print(jobname);
end{:483};selector:=oldsetting;mem[memtop-12].hh.rh:=strtoks(b);
begintokenlist(mem[memtop-3].hh.rh,4);end;
{:481}{484:}function scantoks(macrodef,xpand:boolean):halfword;
label 40,30,31,32;var t:halfword;s:halfword;p:halfword;q:halfword;
unbalance:halfword;hashbrace:halfword;
begin if macrodef then scannerstatus:=2 else scannerstatus:=5;
warningindex:=curcs;defref:=getavail;mem[defref].hh.lh:=-1073741823;
p:=defref;hashbrace:=0;t:=3120;
if macrodef then{485:}begin while true do begin gettoken;
if curtok<768 then goto 31;if curcmd=6 then{487:}begin s:=3328+curchr;
gettoken;if curcmd=1 then begin hashbrace:=curtok;begin q:=getavail;
mem[p].hh.rh:=q;mem[q].hh.lh:=curtok;p:=q;end;begin q:=getavail;
mem[p].hh.rh:=q;mem[q].hh.lh:=3584;p:=q;end;goto 30;end;
if t=3129 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(793);
end;begin helpptr:=1;helpline[0]:=794;end;error;end else begin incr(t);
if curtok<>t then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(795);
end;begin helpptr:=2;helpline[1]:=796;helpline[0]:=797;end;backerror;
end;curtok:=s;end;end{:487};begin q:=getavail;mem[p].hh.rh:=q;
mem[q].hh.lh:=curtok;p:=q;end;end;31:begin q:=getavail;mem[p].hh.rh:=q;
mem[q].hh.lh:=3584;p:=q;end;
if curcmd=2 then{486:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(698);
end;incr(alignstate);begin helpptr:=2;helpline[1]:=791;helpline[0]:=792;
end;error;goto 40;end{:486};30:end{:485}else scanleftbrace;
{488:}unbalance:=1;
while true do begin if xpand then{489:}begin while true do begin getnext
;if curcmd<=115 then goto 32;
if curcmd<>124 then expand else begin q:=thetoks;
if mem[memtop-3].hh.rh<>-1073741823 then begin mem[p].hh.rh:=mem[memtop
-3].hh.rh;p:=q;end;end;end;32:xtoken end{:489}else gettoken;
if curtok<768 then if curcmd<2 then incr(unbalance)else begin decr(
unbalance);if unbalance=0 then goto 40;
end else if curcmd=6 then if macrodef then{490:}begin s:=curtok;
if xpand then getxtoken else gettoken;
if curcmd<>6 then if(curtok<=3120)or(curtok>t)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(798);
end;sprintcs(warningindex);begin helpptr:=3;helpline[2]:=799;
helpline[1]:=800;helpline[0]:=801;end;backerror;curtok:=s;
end else curtok:=1232+curchr;end{:490};begin q:=getavail;
mem[p].hh.rh:=q;mem[q].hh.lh:=curtok;p:=q;end;end{:488};
40:scannerstatus:=0;if hashbrace<>0 then begin q:=getavail;
mem[p].hh.rh:=q;mem[q].hh.lh:=hashbrace;p:=q;end;scantoks:=p;end;
{:484}{493:}procedure readtoks(n:integer;r:halfword);label 30;
var p:halfword;q:halfword;s:integer;m:smallnumber;
begin scannerstatus:=2;warningindex:=r;defref:=getavail;
mem[defref].hh.lh:=-1073741823;p:=defref;begin q:=getavail;
mem[p].hh.rh:=q;mem[q].hh.lh:=3584;p:=q;end;
if(n<0)or(n>15)then m:=16 else m:=n;s:=alignstate;alignstate:=1000000;
repeat{494:}beginfilereading;curinput.namefield:=m+1;
if readopen[m]=2 then{495:}if interaction>1 then if n<0 then begin;
print(344);terminput;end else begin;println;sprintcs(r);begin;print(61);
terminput;end;n:=-1;
end else fatalerror(802){:495}else if readopen[m]=1 then{496:}if inputln
(readfile[m],false)then readopen[m]:=0 else begin aclose(readfile[m]);
readopen[m]:=2;
end{:496}else{497:}begin if not inputln(readfile[m],true)then begin
aclose(readfile[m]);readopen[m]:=2;
if alignstate<>1000000 then begin runaway;begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(803);
end;printesc(572);begin helpptr:=1;helpline[0]:=804;end;
alignstate:=1000000;error;end;end;end{:497};curinput.limitfield:=last;
if(eqtb[28511].int<0)or(eqtb[28511].int>255)then decr(curinput.
limitfield)else buffer[curinput.limitfield]:=eqtb[28511].int;
first:=curinput.limitfield+1;curinput.locfield:=curinput.startfield;
curinput.statefield:=61;while true do begin gettoken;
if curtok=0 then goto 30;
if alignstate<1000000 then begin repeat gettoken;until curtok=0;
alignstate:=1000000;goto 30;end;begin q:=getavail;mem[p].hh.rh:=q;
mem[q].hh.lh:=curtok;p:=q;end;end;30:endfilereading{:494};
until alignstate=1000000;curval:=defref;scannerstatus:=0;alignstate:=s;
end;{:493}{505:}procedure passtext;label 30;var l:integer;
savescannerstatus:smallnumber;begin savescannerstatus:=scannerstatus;
scannerstatus:=1;l:=0;skipline:=line;while true do begin getnext;
if curcmd=121 then begin if l=0 then goto 30;if curchr=2 then decr(l);
end else if curcmd=120 then incr(l);end;
30:scannerstatus:=savescannerstatus;end;
{:505}{508:}procedure changeiflimit(l:smallnumber;p:halfword);label 10;
var q:halfword;begin if p=condptr then iflimit:=l else begin q:=condptr;
while true do begin if q=-1073741823 then confusion(805);
if mem[q].hh.rh=p then begin mem[q].hh.b0:=l;goto 10;end;
q:=mem[q].hh.rh;end;end;10:end;{:508}{509:}procedure conditional;
label 10,50;var b:boolean;r:60..62;m,n:integer;p,q:halfword;
savescannerstatus:smallnumber;savecondptr:halfword;thisif:smallnumber;
begin{506:}begin p:=getnode(2);mem[p].hh.rh:=condptr;
mem[p].hh.b0:=iflimit;mem[p].hh.b1:=curif;mem[p+1].int:=ifline;
condptr:=p;curif:=curchr;iflimit:=1;ifline:=line;end{:506};
savecondptr:=condptr;thisif:=curchr;
{512:}case thisif of 0,1:{517:}begin begin getxtoken;
if curcmd=0 then if curchr=257 then begin curcmd:=13;
curchr:=curtok-536870912;end;end;
if(curcmd>=16)and(curcmd<=19)then begin m:=curcmd;n:=curchr;
end else if(curcmd>13)or(curchr>255)then begin m:=0;n:=256;
end else begin m:=curcmd;n:=curchr;end;begin getxtoken;
if curcmd=0 then if curchr=257 then begin curcmd:=13;
curchr:=curtok-536870912;end;end;
if(curcmd>=16)and(curcmd<=19)then begin curcmd:=curcmd;
end else if(curcmd>13)or(curchr>255)then begin curcmd:=0;curchr:=256;
end;if thisif=0 then b:=(n=curchr)else b:=(m=curcmd);end{:517};
2,3:{514:}begin if thisif=2 then scanint else scandimen(false,false,
false);n:=curval;{417:}repeat getxtoken;until curcmd<>10{:417};
if(curtok>=3132)and(curtok<=3134)then r:=curtok-3072 else begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(836);
end;printcmdchr(120,thisif);begin helpptr:=1;helpline[0]:=837;end;
backerror;r:=61;end;
if thisif=2 then scanint else scandimen(false,false,false);
case r of 60:b:=(n<curval);61:b:=(n=curval);62:b:=(n>curval);end;
end{:514};4:{515:}begin scanint;b:=odd(curval);end{:515};
5:b:=(abs(curlist.modefield)=1);6:b:=(abs(curlist.modefield)=117);
7:b:=(abs(curlist.modefield)=233);8:b:=(curlist.modefield<0);
17:b:=(abs(curlist.dirfield)=3);18:b:=(abs(curlist.dirfield)=4);
19:b:=(abs(curlist.dirfield)=1);20:b:=(curlist.dirfield<0);
9,10,11,21,22,23:{516:}begin scaneightbitint;
p:=eqtb[25326+curval].hh.rh;
if thisif=9 then b:=(p=-1073741823)else if p=-1073741823 then b:=false
else begin if mem[p].hh.b0=2 then p:=mem[p+5].hh.rh;
if thisif=10 then b:=(mem[p].hh.b0=0)else if thisif=11 then b:=(mem[p].
hh.b0=1)else if thisif=21 then b:=((mem[p].hh.b1)=3)else if thisif=22
then b:=((mem[p].hh.b1)=4)else b:=((mem[p].hh.b1)=1);end end{:516};
12:{518:}begin savescannerstatus:=scannerstatus;scannerstatus:=0;
getnext;n:=curcs;p:=curcmd;q:=curchr;getnext;
if curcmd<>p then b:=false else if curcmd<126 then b:=(curchr=q)else
{519:}begin p:=mem[curchr].hh.rh;q:=mem[eqtb[n].hh.rh].hh.rh;
if p=q then b:=true else begin while(p<>-1073741823)and(q<>-1073741823)
do if mem[p].hh.lh<>mem[q].hh.lh then p:=-1073741823 else begin p:=mem[p
].hh.rh;q:=mem[q].hh.rh;end;b:=((p=-1073741823)and(q=-1073741823));end;
end{:519};scannerstatus:=savescannerstatus;end{:518};
13:begin scanfourbitintor18;
if curval=18 then b:=not shellenabledp else b:=(readopen[curval]=2);end;
14:b:=true;15:b:=false;16:{520:}begin scanint;n:=curval;
if eqtb[28498].int>1 then begin begindiagnostic;print(838);printint(n);
printchar(125);enddiagnostic(false);end;while n<>0 do begin passtext;
if condptr=savecondptr then if curchr=4 then decr(n)else goto 50 else if
curchr=2 then{507:}begin p:=condptr;ifline:=mem[p+1].int;
curif:=mem[p].hh.b1;iflimit:=mem[p].hh.b0;condptr:=mem[p].hh.rh;
freenode(p,2);end{:507};end;changeiflimit(4,savecondptr);goto 10;
end{:520};end{:512};
if eqtb[28498].int>1 then{513:}begin begindiagnostic;
if b then print(834)else print(835);enddiagnostic(false);end{:513};
if b then begin changeiflimit(3,savecondptr);goto 10;end;
{511:}while true do begin passtext;
if condptr=savecondptr then begin if curchr<>4 then goto 50;
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(832);
end;printesc(830);begin helpptr:=1;helpline[0]:=833;end;error;
end else if curchr=2 then{507:}begin p:=condptr;ifline:=mem[p+1].int;
curif:=mem[p].hh.b1;iflimit:=mem[p].hh.b0;condptr:=mem[p].hh.rh;
freenode(p,2);end{:507};end{:511};
50:if curchr=2 then{507:}begin p:=condptr;ifline:=mem[p+1].int;
curif:=mem[p].hh.b1;iflimit:=mem[p].hh.b0;condptr:=mem[p].hh.rh;
freenode(p,2);end{:507}else iflimit:=2;10:end;
{:509}{526:}procedure beginname;begin areadelimiter:=0;extdelimiter:=0;
quotedfilename:=false;prevchar:=0;end;
{:526}{527:}function morename(c:ASCIIcode):boolean;
begin if(c=32)and stopatspace and(not quotedfilename)then morename:=
false else if c=34 then begin quotedfilename:=not quotedfilename;
morename:=true;
end else begin begin if poolptr+1>poolsize then overflow(258,poolsize-
initpoolptr);end;begin strpool[poolptr]:=c;incr(poolptr);end;
if(ISDIRSEP(c)and(notkanjicharseq(prevchar,c)))then begin areadelimiter
:=(poolptr-strstart[strptr]);extdelimiter:=0;
end else if c=46 then extdelimiter:=(poolptr-strstart[strptr]);
morename:=true;end;prevchar:=c;end;{:527}{528:}procedure endname;
var tempstr:strnumber;j,s,t:poolpointer;mustquote:boolean;
begin if strptr+3>maxstrings then overflow(259,maxstrings-initstrptr);
begin if poolptr+6>poolsize then overflow(258,poolsize-initpoolptr);end;
if areadelimiter<>0 then begin mustquote:=false;s:=strstart[strptr];
t:=strstart[strptr]+areadelimiter;j:=s;
while(not mustquote)and(j<t)do begin mustquote:=strpool[j]=32;incr(j);
end;if mustquote then begin for j:=poolptr-1 downto t do strpool[j+2]:=
strpool[j];strpool[t+1]:=34;
for j:=t-1 downto s do strpool[j+1]:=strpool[j];strpool[s]:=34;
if extdelimiter<>0 then extdelimiter:=extdelimiter+2;
areadelimiter:=areadelimiter+2;poolptr:=poolptr+2;end;end;
s:=strstart[strptr]+areadelimiter;
if extdelimiter=0 then t:=poolptr else t:=strstart[strptr]+extdelimiter
-1;mustquote:=false;j:=s;
while(not mustquote)and(j<t)do begin mustquote:=strpool[j]=32;incr(j);
end;if mustquote then begin for j:=poolptr-1 downto t do strpool[j+2]:=
strpool[j];strpool[t+1]:=34;
for j:=t-1 downto s do strpool[j+1]:=strpool[j];strpool[s]:=34;
if extdelimiter<>0 then extdelimiter:=extdelimiter+2;poolptr:=poolptr+2;
end;if extdelimiter<>0 then begin s:=strstart[strptr]+extdelimiter-1;
t:=poolptr;mustquote:=false;j:=s;
while(not mustquote)and(j<t)do begin mustquote:=strpool[j]=32;incr(j);
end;if mustquote then begin strpool[t+1]:=34;
for j:=t-1 downto s do strpool[j+1]:=strpool[j];strpool[s]:=34;
poolptr:=poolptr+2;end;end;
if areadelimiter=0 then curarea:=344 else begin curarea:=strptr;
strstart[strptr+1]:=strstart[strptr]+areadelimiter;incr(strptr);
tempstr:=searchstring(curarea);if tempstr>0 then begin curarea:=tempstr;
decr(strptr);
for j:=strstart[strptr+1]to poolptr-1 do begin strpool[j-areadelimiter]
:=strpool[j];end;poolptr:=poolptr-areadelimiter;end;end;
if extdelimiter=0 then begin curext:=344;curname:=slowmakestring;
end else begin curname:=strptr;
strstart[strptr+1]:=strstart[strptr]+extdelimiter-areadelimiter-1;
incr(strptr);curext:=makestring;decr(strptr);
tempstr:=searchstring(curname);if tempstr>0 then begin curname:=tempstr;
decr(strptr);
for j:=strstart[strptr+1]to poolptr-1 do begin strpool[j-extdelimiter+
areadelimiter+1]:=strpool[j];end;
poolptr:=poolptr-extdelimiter+areadelimiter+1;end;
curext:=slowmakestring;end;end;
{:528}{530:}procedure packfilename(n,a,e:strnumber);var k:integer;
c:ASCIIcode;j:poolpointer;begin k:=0;
if nameoffile then libcfree(nameoffile);
nameoffile:=xmallocarray(ASCIIcode,(strstart[a+1]-strstart[a])+(strstart
[n+1]-strstart[n])+(strstart[e+1]-strstart[e])+1);
for j:=strstart[a]to strstart[a+1]-1 do begin c:=strpool[j];
if not(c=34)then begin incr(k);if k<=maxint then nameoffile[k]:=xchr[c];
end end;for j:=strstart[n]to strstart[n+1]-1 do begin c:=strpool[j];
if not(c=34)then begin incr(k);if k<=maxint then nameoffile[k]:=xchr[c];
end end;for j:=strstart[e]to strstart[e+1]-1 do begin c:=strpool[j];
if not(c=34)then begin incr(k);if k<=maxint then nameoffile[k]:=xchr[c];
end end;if k<=maxint then namelength:=k else namelength:=maxint;
nameoffile[namelength+1]:=0;end;
{:530}{534:}procedure packbufferedname(n:smallnumber;a,b:integer);
var k:integer;c:ASCIIcode;j:integer;
begin if n+b-a+5>maxint then b:=a+maxint-n-5;k:=0;
if nameoffile then libcfree(nameoffile);
nameoffile:=xmallocarray(ASCIIcode,n+(b-a+1)+5);
for j:=1 to n do begin c:=xord[ucharcast(TEXformatdefault[j])];
if not(c=34)then begin incr(k);if k<=maxint then nameoffile[k]:=xchr[c];
end end;for j:=a to b do begin c:=buffer[j];
if not(c=34)then begin incr(k);if k<=maxint then nameoffile[k]:=xchr[c];
end end;
for j:=formatdefaultlength-3 to formatdefaultlength do begin c:=xord[
ucharcast(TEXformatdefault[j])];if not(c=34)then begin incr(k);
if k<=maxint then nameoffile[k]:=xchr[c];end end;
if k<=maxint then namelength:=k else namelength:=maxint;
nameoffile[namelength+1]:=0;end;
{:534}{536:}function makenamestring:strnumber;var k:1..maxint;
saveareadelimiter,saveextdelimiter:poolpointer;
savenameinprogress,savestopatspace:boolean;
begin if(poolptr+namelength>poolsize)or(strptr=maxstrings)or((poolptr-
strstart[strptr])>0)then makenamestring:=63 else begin for k:=1 to
namelength do begin strpool[poolptr]:=xord[nameoffile[k]];incr(poolptr);
end;makenamestring:=makestring;saveareadelimiter:=areadelimiter;
saveextdelimiter:=extdelimiter;savenameinprogress:=nameinprogress;
savestopatspace:=stopatspace;nameinprogress:=true;beginname;
stopatspace:=false;k:=1;
while(k<=namelength)and(morename(nameoffile[k]))do incr(k);
stopatspace:=savestopatspace;endname;nameinprogress:=savenameinprogress;
areadelimiter:=saveareadelimiter;extdelimiter:=saveextdelimiter;end;end;
function amakenamestring(var f:alphafile):strnumber;
begin amakenamestring:=makenamestring;end;
function bmakenamestring(var f:bytefile):strnumber;
begin bmakenamestring:=makenamestring;end;
function wmakenamestring(var f:wordfile):strnumber;
begin wmakenamestring:=makenamestring;end;
{:536}{537:}procedure scanfilename;label 30;begin nameinprogress:=true;
beginname;{417:}repeat getxtoken;until curcmd<>10{:417};skipmode:=false;
while true do begin if(curcmd>=16)and(curcmd<=19)then begin begin if
poolptr+4>poolsize then overflow(258,poolsize-initpoolptr);end;
curchr:=toBUFF(curchr);
if BYTE1(curchr)<>0 then begin strpool[poolptr]:=BYTE1(curchr);
incr(poolptr);end;
if BYTE2(curchr)<>0 then begin strpool[poolptr]:=BYTE2(curchr);
incr(poolptr);end;
if BYTE3(curchr)<>0 then begin strpool[poolptr]:=BYTE3(curchr);
incr(poolptr);end;begin strpool[poolptr]:=BYTE4(curchr);incr(poolptr);
end;end else if(curcmd>12)or(curchr>255)then begin backinput;goto 30;
end else if((curchr=32)and(curinput.statefield<>0)and(curinput.locfield>
curinput.limitfield))or not morename(curchr)then goto 30;getxtoken;end;
30:endname;nameinprogress:=false;skipmode:=true;end;
{:537}{540:}procedure packjobname(s:strnumber);begin curarea:=344;
curext:=s;curname:=jobname;packfilename(curname,curarea,curext);end;
{:540}{541:}procedure promptfilename(s,e:strnumber);label 30;
var k:0..bufsize;savedcurname:strnumber;savedcurext:strnumber;
savedcurarea:strnumber;begin if interaction=2 then;
if s=840 then begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(841);
end else begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(842);
end;printfilename(curname,curarea,curext);print(843);
if(e=844)or(e=344)then showcontext;println;
printcstring(promptfilenamehelpmsg);if(e<>344)then begin print(845);
print(e);print(39);end;print(41);println;printnl(846);print(s);
if interaction<2 then fatalerror(847);savedcurname:=curname;
savedcurext:=curext;savedcurarea:=curarea;;begin;print(607);terminput;
end;{542:}begin beginname;k:=first;
while(buffer[k]=32)and(k<last)do incr(k);
while true do begin if k=last then goto 30;
if not morename(buffer[k])then goto 30;incr(k);end;30:endname;end{:542};
if((strstart[curname+1]-strstart[curname])=0)and(curext=344)and(curarea=
344)then begin curname:=savedcurname;curext:=savedcurext;
curarea:=savedcurarea;end else if curext=344 then curext:=e;
packfilename(curname,curarea,curext);end;
{:541}{545:}procedure openlogfile;var oldsetting:0..21;k:0..bufsize;
l:0..bufsize;months:constcstring;begin oldsetting:=selector;
if jobname=0 then jobname:=getjobname(850);packjobname(851);
recorderchangefilename(stringcast(nameoffile+1));packjobname(852);
while not aopenout(logfile)do{546:}begin selector:=17;
promptfilename(854,852);end{:546};
texmflogname:=amakenamestring(logfile);selector:=18;logopened:=true;
{547:}begin if srcspecialsp or filelineerrorstylep or parsefirstlinep
then write(logfile,'This is upTeX, Version 3.14159265','-p3.7.1',
'-u1.21')else write(logfile,'This is upTeX, Version 3.14159265',
'-p3.7.1','-u1.21');write(logfile,' (');
write(logfile,conststringcast(getencstring));write(logfile,')');
write(logfile,versionstring);slowprint(formatident);print(855);
printint(eqtb[28483].int);printchar(32);
months:=' JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC';
for k:=3*eqtb[28484].int-2 to 3*eqtb[28484].int do write(logfile,months[
k]);printchar(32);printint(eqtb[28485].int);printchar(32);
printtwo(eqtb[28482].int div 60);printchar(58);
printtwo(eqtb[28482].int mod 60);
if shellenabledp then begin writeln(logfile);write(logfile,' ');
if restrictedshell then begin write(logfile,'restricted ');end;
write(logfile,'\write18 enabled.')end;
if srcspecialsp then begin writeln(logfile);
write(logfile,' Source specials enabled.')end;
if filelineerrorstylep then begin writeln(logfile);
write(logfile,' file:line:error style messages enabled.')end;
if parsefirstlinep then begin writeln(logfile);
write(logfile,' %&-line parsing enabled.');end;
if translatefilename then begin writeln(logfile);write(logfile,' (');
fputs(translatefilename,logfile);write(logfile,')');end;end{:547};
if mltexenabledp then begin writeln(logfile);
write(logfile,'MLTeX v2.2 enabled');end;inputstack[inputptr]:=curinput;
printnl(853);l:=inputstack[0].limitfield;
if buffer[l]=eqtb[28511].int then decr(l);
for k:=1 to l do print(buffer[k]);println;selector:=oldsetting+2;end;
{:545}{548:}procedure startinput;label 30;var tempstr:strnumber;
begin scanfilename;packfilename(curname,curarea,curext);
while true do begin beginfilereading;texinputtype:=1;
if kpseinnameok(stringcast(nameoffile+1))and aopenin(inputfile[curinput.
indexfield],kpsetexformat)then goto 30;endfilereading;
promptfilename(840,344);end;
30:curinput.namefield:=amakenamestring(inputfile[curinput.indexfield]);
sourcefilenamestack[inopen]:=curinput.namefield;
fullsourcefilenamestack[inopen]:=makefullnamestring;
if curinput.namefield=strptr-1 then begin tempstr:=searchstring(curinput
.namefield);if tempstr>0 then begin curinput.namefield:=tempstr;
begin decr(strptr);poolptr:=strstart[strptr];end;end;end;
if jobname=0 then begin jobname:=getjobname(curname);openlogfile;end;
if termoffset+(strstart[fullsourcefilenamestack[inopen]+1]-strstart[
fullsourcefilenamestack[inopen]])>maxprintline-2 then println else if(
termoffset>0)or(fileoffset>0)then printchar(32);printchar(40);
incr(openparens);slowprint(fullsourcefilenamestack[inopen]);
fflush(stdout);curinput.statefield:=61;{1429:}synctexstartinput;{:1429};
{549:}begin line:=1;
if inputln(inputfile[curinput.indexfield],false)then;firmuptheline;
if(eqtb[28511].int<0)or(eqtb[28511].int>255)then decr(curinput.
limitfield)else buffer[curinput.limitfield]:=eqtb[28511].int;
first:=curinput.limitfield+1;curinput.locfield:=curinput.startfield;
end{:549};end;{:548}{571:}{1407:}function effectivechar(errp:boolean;
f:internalfontnumber;c:quarterword):integer;label 40;var basec:integer;
result:integer;begin result:=c;if not mltexenabledp then goto 40;
if fontec[f]>=c then if fontbc[f]<=c then if(fontinfo[charbase[f]+c].
qqqq.b0>0)then goto 40;
if c>=eqtb[28522].int then if c<=eqtb[28523].int then if(eqtb[28206+c].
hh.rh>0)then begin basec:=(eqtb[28206+c].hh.rh mod 256);result:=basec;
if not errp then goto 40;
if fontec[f]>=basec then if fontbc[f]<=basec then if(fontinfo[charbase[f
]+basec].qqqq.b0>0)then goto 40;end;if errp then begin begindiagnostic;
printnl(880);print(1396);print(c);print(881);slowprint(fontname[f]);
printchar(33);enddiagnostic(false);result:=fontbc[f];end;
40:effectivechar:=result;end;
{:1407}{1408:}function effectivecharinfo(f:internalfontnumber;
c:quarterword):fourquarters;label 10;var ci:fourquarters;basec:integer;
begin if not mltexenabledp then begin effectivecharinfo:=fontinfo[
charbase[f]+c].qqqq;goto 10;end;
if fontec[f]>=c then if fontbc[f]<=c then begin ci:=fontinfo[charbase[f]
+c].qqqq;if(ci.b0>0)then begin effectivecharinfo:=ci;goto 10;end;end;
if c>=eqtb[28522].int then if c<=eqtb[28523].int then if(eqtb[28206+c].
hh.rh>0)then begin basec:=(eqtb[28206+c].hh.rh mod 256);
if fontec[f]>=basec then if fontbc[f]<=basec then begin ci:=fontinfo[
charbase[f]+basec].qqqq;if(ci.b0>0)then begin effectivecharinfo:=ci;
goto 10;end;end;end;effectivecharinfo:=nullcharacter;10:end;
{:1408}function readfontinfo(u:halfword;nom,aire:strnumber;
s:scaled):internalfontnumber;label 30,11,45;var k:fontindex;
jfmflag:0..3;nt:halfword;cx:KANJIcode;nametoolong:boolean;
fileopened:boolean;lf,lh,bc,ec,nw,nh,nd,ni,nl,nk,ne,np:halfword;
f:internalfontnumber;g:internalfontnumber;a,b,c,d:eightbits;
qw:fourquarters;sw:scaled;bchlabel:integer;bchar:0..256;z:scaled;
alpha:integer;beta:1..16;begin g:=0;{573:}{574:}fileopened:=false;
nametoolong:=((strstart[nom+1]-strstart[nom])>255)or((strstart[aire+1]-
strstart[aire])>255);if nametoolong then goto 11;
packfilename(nom,aire,344);if not bopenin(tfmfile)then goto 11;
fileopened:=true{:574};{576:}begin begin lf:=tfmtemp;
if lf>127 then goto 11;tfmtemp:=getc(tfmfile);lf:=lf*256+tfmtemp;end;
tfmtemp:=getc(tfmfile);begin lh:=tfmtemp;if lh>127 then goto 11;
tfmtemp:=getc(tfmfile);lh:=lh*256+tfmtemp;end;
if lf=11 then begin jfmflag:=4;nt:=lh;tfmtemp:=getc(tfmfile);
begin lf:=tfmtemp;if lf>127 then goto 11;tfmtemp:=getc(tfmfile);
lf:=lf*256+tfmtemp;end;tfmtemp:=getc(tfmfile);begin lh:=tfmtemp;
if lh>127 then goto 11;tfmtemp:=getc(tfmfile);lh:=lh*256+tfmtemp;end;
end else if lf=9 then begin jfmflag:=3;nt:=lh;tfmtemp:=getc(tfmfile);
begin lf:=tfmtemp;if lf>127 then goto 11;tfmtemp:=getc(tfmfile);
lf:=lf*256+tfmtemp;end;tfmtemp:=getc(tfmfile);begin lh:=tfmtemp;
if lh>127 then goto 11;tfmtemp:=getc(tfmfile);lh:=lh*256+tfmtemp;end;
end else begin jfmflag:=0;nt:=0;end;tfmtemp:=getc(tfmfile);
begin bc:=tfmtemp;if bc>127 then goto 11;tfmtemp:=getc(tfmfile);
bc:=bc*256+tfmtemp;end;tfmtemp:=getc(tfmfile);begin ec:=tfmtemp;
if ec>127 then goto 11;tfmtemp:=getc(tfmfile);ec:=ec*256+tfmtemp;end;
if(bc>ec+1)or(ec>255)then goto 11;if bc>255 then begin bc:=1;ec:=0;end;
tfmtemp:=getc(tfmfile);begin nw:=tfmtemp;if nw>127 then goto 11;
tfmtemp:=getc(tfmfile);nw:=nw*256+tfmtemp;end;tfmtemp:=getc(tfmfile);
begin nh:=tfmtemp;if nh>127 then goto 11;tfmtemp:=getc(tfmfile);
nh:=nh*256+tfmtemp;end;tfmtemp:=getc(tfmfile);begin nd:=tfmtemp;
if nd>127 then goto 11;tfmtemp:=getc(tfmfile);nd:=nd*256+tfmtemp;end;
tfmtemp:=getc(tfmfile);begin ni:=tfmtemp;if ni>127 then goto 11;
tfmtemp:=getc(tfmfile);ni:=ni*256+tfmtemp;end;tfmtemp:=getc(tfmfile);
begin nl:=tfmtemp;if nl>127 then goto 11;tfmtemp:=getc(tfmfile);
nl:=nl*256+tfmtemp;end;tfmtemp:=getc(tfmfile);begin nk:=tfmtemp;
if nk>127 then goto 11;tfmtemp:=getc(tfmfile);nk:=nk*256+tfmtemp;end;
tfmtemp:=getc(tfmfile);begin ne:=tfmtemp;if ne>127 then goto 11;
tfmtemp:=getc(tfmfile);ne:=ne*256+tfmtemp;end;tfmtemp:=getc(tfmfile);
begin np:=tfmtemp;if np>127 then goto 11;tfmtemp:=getc(tfmfile);
np:=np*256+tfmtemp;end;
if jfmflag<>0 then begin if lf<>7+lh+nt+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+
np then goto 11;
end else begin if lf<>6+lh+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+np then goto
11;end;if(nw=0)or(nh=0)or(nd=0)or(ni=0)then goto 11;end{:576};
{577:}if jfmflag<>0 then lf:=lf-7-lh else lf:=lf-6-lh;
if np<7 then lf:=lf+7-np;
if(fontptr=fontmax)or(fmemptr+lf>fontmemsize)then{578:}begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(857);
end;sprintcs(u);printchar(61);printfilename(nom,aire,344);
if s>=0 then begin print(790);printscaled(s);print(416);
end else if s<>-1000 then begin print(858);printint(-s);end;print(867);
begin helpptr:=4;helpline[3]:=868;helpline[2]:=869;helpline[1]:=870;
helpline[0]:=871;end;error;goto 30;end{:578};f:=fontptr+1;
fontdir[f]:=jfmflag;fontnumext[f]:=nt;ctypebase[f]:=fmemptr;
charbase[f]:=ctypebase[f]+nt-bc;widthbase[f]:=charbase[f]+ec+1;
heightbase[f]:=widthbase[f]+nw;depthbase[f]:=heightbase[f]+nh;
italicbase[f]:=depthbase[f]+nd;ligkernbase[f]:=italicbase[f]+ni;
kernbase[f]:=ligkernbase[f]+nl-256*(128);
extenbase[f]:=kernbase[f]+256*(128)+nk;parambase[f]:=extenbase[f]+ne;
{:577};{579:}begin if lh<2 then goto 11;begin tfmtemp:=getc(tfmfile);
a:=tfmtemp;qw.b0:=a;tfmtemp:=getc(tfmfile);b:=tfmtemp;qw.b1:=b;
tfmtemp:=getc(tfmfile);c:=tfmtemp;qw.b2:=c;tfmtemp:=getc(tfmfile);
d:=tfmtemp;qw.b3:=d;fontcheck[f]:=qw;end;tfmtemp:=getc(tfmfile);
begin z:=tfmtemp;if z>127 then goto 11;tfmtemp:=getc(tfmfile);
z:=z*256+tfmtemp;end;tfmtemp:=getc(tfmfile);z:=z*256+tfmtemp;
tfmtemp:=getc(tfmfile);z:=(z*16)+(tfmtemp div 16);
if z<65536 then goto 11;while lh>2 do begin tfmtemp:=getc(tfmfile);
tfmtemp:=getc(tfmfile);tfmtemp:=getc(tfmfile);tfmtemp:=getc(tfmfile);
decr(lh);end;fontdsize[f]:=z;
if s<>-1000 then if s>=0 then z:=s else z:=xnoverd(z,-s,1000);
fontsize[f]:=z;end{:579};
{580:}if jfmflag<>0 then for k:=ctypebase[f]to ctypebase[f]+nt-1 do
begin tfmtemp:=getc(tfmfile);begin cx:=tfmtemp;if cx>255 then goto 11;
tfmtemp:=getc(tfmfile);cx:=cx*256+tfmtemp;end;fontinfo[k].hh.rh:=cx;
tfmtemp:=getc(tfmfile);begin cx:=tfmtemp;if cx>127 then goto 11;
tfmtemp:=getc(tfmfile);cx:=cx*256+tfmtemp;end;
fontinfo[k].hh.lhfield:=cx;end;
for k:=charbase[f]+bc to widthbase[f]-1 do begin begin tfmtemp:=getc(
tfmfile);a:=tfmtemp;qw.b0:=a;tfmtemp:=getc(tfmfile);b:=tfmtemp;qw.b1:=b;
tfmtemp:=getc(tfmfile);c:=tfmtemp;qw.b2:=c;tfmtemp:=getc(tfmfile);
d:=tfmtemp;qw.b3:=d;fontinfo[k].qqqq:=qw;end;
if(a>=nw)or(b div 16>=nh)or(b mod 16>=nd)or(c div 4>=ni)then goto 11;
case c mod 4 of 1:if d>=nl then goto 11;3:if d>=ne then goto 11;
2:{581:}begin begin if(d<bc)or(d>ec)then goto 11 end;
while d<k-charbase[f]do begin qw:=fontinfo[charbase[f]+d].qqqq;
if((qw.b2)mod 4)<>2 then goto 45;d:=qw.b3;end;
if d=k-charbase[f]then goto 11;45:end{:581};others:end;end{:580};
{582:}begin{583:}begin alpha:=16;while z>=8388608 do begin z:=z div 2;
alpha:=alpha+alpha;end;beta:=256 div alpha;alpha:=alpha*z;end{:583};
for k:=widthbase[f]to ligkernbase[f]-1 do begin tfmtemp:=getc(tfmfile);
a:=tfmtemp;tfmtemp:=getc(tfmfile);b:=tfmtemp;tfmtemp:=getc(tfmfile);
c:=tfmtemp;tfmtemp:=getc(tfmfile);d:=tfmtemp;
sw:=(((((d*z)div 256)+(c*z))div 256)+(b*z))div beta;
if a=0 then fontinfo[k].int:=sw else if a=255 then fontinfo[k].int:=sw-
alpha else goto 11;end;if fontinfo[widthbase[f]].int<>0 then goto 11;
if fontinfo[heightbase[f]].int<>0 then goto 11;
if fontinfo[depthbase[f]].int<>0 then goto 11;
if fontinfo[italicbase[f]].int<>0 then goto 11;end{:582};
{584:}bchlabel:=32767;bchar:=256;
if nl>0 then begin for k:=ligkernbase[f]to kernbase[f]+256*(128)-1 do
begin begin tfmtemp:=getc(tfmfile);a:=tfmtemp;qw.b0:=a;
tfmtemp:=getc(tfmfile);b:=tfmtemp;qw.b1:=b;tfmtemp:=getc(tfmfile);
c:=tfmtemp;qw.b2:=c;tfmtemp:=getc(tfmfile);d:=tfmtemp;qw.b3:=d;
fontinfo[k].qqqq:=qw;end;
if a>128 then begin if 256*c+d>=nl then goto 11;
if a=255 then if k=ligkernbase[f]then bchar:=b;
end else begin if b<>bchar then begin begin if(b<bc)or(b>ec)then goto 11
end;qw:=fontinfo[charbase[f]+b].qqqq;if not(qw.b0>0)then goto 11;end;
if c<128 then begin if jfmflag<>0 then begin if d>=ne then goto 11;
end else begin begin if(d<bc)or(d>ec)then goto 11 end;
qw:=fontinfo[charbase[f]+d].qqqq;if not(qw.b0>0)then goto 11;end;
end else if 256*(c-128)+d>=nk then goto 11;
if a<128 then if k-ligkernbase[f]+a+1>=nl then goto 11;end;end;
if a=255 then bchlabel:=256*c+d;end;
for k:=kernbase[f]+256*(128)to extenbase[f]-1 do begin tfmtemp:=getc(
tfmfile);a:=tfmtemp;tfmtemp:=getc(tfmfile);b:=tfmtemp;
tfmtemp:=getc(tfmfile);c:=tfmtemp;tfmtemp:=getc(tfmfile);d:=tfmtemp;
sw:=(((((d*z)div 256)+(c*z))div 256)+(b*z))div beta;
if a=0 then fontinfo[k].int:=sw else if a=255 then fontinfo[k].int:=sw-
alpha else goto 11;end;{:584};
{585:}if jfmflag<>0 then for k:=extenbase[f]to parambase[f]-1 do begin
tfmtemp:=getc(tfmfile);a:=tfmtemp;tfmtemp:=getc(tfmfile);b:=tfmtemp;
tfmtemp:=getc(tfmfile);c:=tfmtemp;tfmtemp:=getc(tfmfile);d:=tfmtemp;
sw:=(((((d*z)div 256)+(c*z))div 256)+(b*z))div beta;
if a=0 then fontinfo[k].int:=sw else if a=255 then fontinfo[k].int:=sw-
alpha else goto 11;
end else for k:=extenbase[f]to parambase[f]-1 do begin begin tfmtemp:=
getc(tfmfile);a:=tfmtemp;qw.b0:=a;tfmtemp:=getc(tfmfile);b:=tfmtemp;
qw.b1:=b;tfmtemp:=getc(tfmfile);c:=tfmtemp;qw.b2:=c;
tfmtemp:=getc(tfmfile);d:=tfmtemp;qw.b3:=d;fontinfo[k].qqqq:=qw;end;
if a<>0 then begin begin if(a<bc)or(a>ec)then goto 11 end;
qw:=fontinfo[charbase[f]+a].qqqq;if not(qw.b0>0)then goto 11;end;
if b<>0 then begin begin if(b<bc)or(b>ec)then goto 11 end;
qw:=fontinfo[charbase[f]+b].qqqq;if not(qw.b0>0)then goto 11;end;
if c<>0 then begin begin if(c<bc)or(c>ec)then goto 11 end;
qw:=fontinfo[charbase[f]+c].qqqq;if not(qw.b0>0)then goto 11;end;
begin begin if(d<bc)or(d>ec)then goto 11 end;
qw:=fontinfo[charbase[f]+d].qqqq;if not(qw.b0>0)then goto 11;end;
end{:585};
{586:}begin for k:=1 to np do if k=1 then begin tfmtemp:=getc(tfmfile);
sw:=tfmtemp;if sw>127 then sw:=sw-256;tfmtemp:=getc(tfmfile);
sw:=sw*256+tfmtemp;tfmtemp:=getc(tfmfile);sw:=sw*256+tfmtemp;
tfmtemp:=getc(tfmfile);
fontinfo[parambase[f]].int:=(sw*16)+(tfmtemp div 16);
end else begin tfmtemp:=getc(tfmfile);a:=tfmtemp;tfmtemp:=getc(tfmfile);
b:=tfmtemp;tfmtemp:=getc(tfmfile);c:=tfmtemp;tfmtemp:=getc(tfmfile);
d:=tfmtemp;sw:=(((((d*z)div 256)+(c*z))div 256)+(b*z))div beta;
if a=0 then fontinfo[parambase[f]+k-1].int:=sw else if a=255 then
fontinfo[parambase[f]+k-1].int:=sw-alpha else goto 11;end;
if feof(tfmfile)then goto 11;
for k:=np+1 to 7 do fontinfo[parambase[f]+k-1].int:=0;end{:586};
{587:}if np>=7 then fontparams[f]:=np else fontparams[f]:=7;
hyphenchar[f]:=eqtb[28509].int;skewchar[f]:=eqtb[28510].int;
if bchlabel<nl then bcharlabel[f]:=bchlabel+ligkernbase[f]else
bcharlabel[f]:=0;fontbchar[f]:=bchar;fontfalsebchar[f]:=bchar;
if bchar<=ec then if bchar>=bc then begin qw:=fontinfo[charbase[f]+bchar
].qqqq;if(qw.b0>0)then fontfalsebchar[f]:=256;end;fontname[f]:=nom;
fontarea[f]:=aire;fontbc[f]:=bc;fontec[f]:=ec;fontglue[f]:=-1073741823;
ctypebase[f]:=ctypebase[f];charbase[f]:=charbase[f];
widthbase[f]:=widthbase[f];ligkernbase[f]:=ligkernbase[f];
kernbase[f]:=kernbase[f];extenbase[f]:=extenbase[f];decr(parambase[f]);
fmemptr:=fmemptr+lf;fontptr:=f;g:=f;goto 30{:587}{:573};
11:{572:}begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(857);
end;sprintcs(u);printchar(61);printfilename(nom,aire,344);
if s>=0 then begin print(790);printscaled(s);print(416);
end else if s<>-1000 then begin print(858);printint(-s);end;
if fileopened then print(859)else if nametoolong then print(860)else
print(861);begin helpptr:=5;helpline[4]:=862;helpline[3]:=863;
helpline[2]:=864;helpline[1]:=865;helpline[0]:=866;end;error{:572};
30:if fileopened then bclose(tfmfile);readfontinfo:=g;end;
{:571}{592:}procedure charwarning(f:internalfontnumber;c:eightbits);
var l:0..255;begin if eqtb[28497].int>0 then begin begindiagnostic;
printnl(880);if(c<32)or(c>126)then begin printchar(94);printchar(94);
if c<64 then printchar(c+64)else if c<128 then printchar(c-64)else begin
l:=c div 16;if l<10 then printchar(l+48)else printchar(l+87);
l:=c mod 16;if l<10 then printchar(l+48)else printchar(l+87);
end end else print(c);print(881);slowprint(fontname[f]);printchar(33);
enddiagnostic(false);end;end;
{:592}{593:}function newcharacter(f:internalfontnumber;
c:eightbits):halfword;label 10;var p:halfword;ec:quarterword;
begin ec:=effectivechar(false,f,c);
if fontbc[f]<=ec then if fontec[f]>=ec then if(fontinfo[charbase[f]+ec].
qqqq.b0>0)then begin p:=getavail;mem[p].hh.b0:=f;mem[p].hh.b1:=c;
newcharacter:=p;goto 10;end;charwarning(f,c);newcharacter:=-1073741823;
10:end;{:593}{609:}procedure dviswap;
begin if dviptr>(2147483647-dvioffset)then begin curs:=-2;
fatalerror(882);end;
if dvilimit=dvibufsize then begin writedvi(0,halfbuf-1);
dvilimit:=halfbuf;dvioffset:=dvioffset+dvibufsize;dviptr:=0;
end else begin writedvi(halfbuf,dvibufsize-1);dvilimit:=dvibufsize;end;
dvigone:=dvigone+halfbuf;end;{:609}{611:}procedure dvifour(x:integer);
begin if x>=0 then begin dvibuf[dviptr]:=x div 16777216;incr(dviptr);
if dviptr=dvilimit then dviswap;end else begin x:=x+1073741824;
x:=x+1073741824;begin dvibuf[dviptr]:=(x div 16777216)+128;incr(dviptr);
if dviptr=dvilimit then dviswap;end;end;x:=x mod 16777216;
begin dvibuf[dviptr]:=x div 65536;incr(dviptr);
if dviptr=dvilimit then dviswap;end;x:=x mod 65536;
begin dvibuf[dviptr]:=x div 256;incr(dviptr);
if dviptr=dvilimit then dviswap;end;begin dvibuf[dviptr]:=x mod 256;
incr(dviptr);if dviptr=dvilimit then dviswap;end;end;
{:611}{612:}procedure dvipop(l:integer);
begin if(l=dvioffset+dviptr)and(dviptr>0)then decr(dviptr)else begin
dvibuf[dviptr]:=142;incr(dviptr);if dviptr=dvilimit then dviswap;end;
end;{:612}{613:}procedure dvifontdef(f:internalfontnumber);
var k:poolpointer;begin if f<=256 then begin begin dvibuf[dviptr]:=243;
incr(dviptr);if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=f-1;incr(dviptr);if dviptr=dvilimit then dviswap;
end;end else begin begin dvibuf[dviptr]:=244;incr(dviptr);
if dviptr=dvilimit then dviswap;end;begin dvibuf[dviptr]:=(f-1)div 256;
incr(dviptr);if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=(f-1)mod 256;incr(dviptr);
if dviptr=dvilimit then dviswap;end;end;
begin dvibuf[dviptr]:=fontcheck[f].b0;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=fontcheck[f].b1;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=fontcheck[f].b2;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=fontcheck[f].b3;incr(dviptr);
if dviptr=dvilimit then dviswap;end;dvifour(fontsize[f]);
dvifour(fontdsize[f]);
begin dvibuf[dviptr]:=(strstart[fontarea[f]+1]-strstart[fontarea[f]]);
incr(dviptr);if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=(strstart[fontname[f]+1]-strstart[fontname[f]]);
incr(dviptr);if dviptr=dvilimit then dviswap;end;
{614:}for k:=strstart[fontarea[f]]to strstart[fontarea[f]+1]-1 do begin
dvibuf[dviptr]:=strpool[k];incr(dviptr);if dviptr=dvilimit then dviswap;
end;
for k:=strstart[fontname[f]]to strstart[fontname[f]+1]-1 do begin dvibuf
[dviptr]:=strpool[k];incr(dviptr);if dviptr=dvilimit then dviswap;
end{:614};end;{:613}{618:}procedure movement(w:scaled;o:eightbits);
label 10,40,45,2,1;var mstate:smallnumber;p,q:halfword;k:integer;
begin q:=getnode(3);mem[q+1].int:=w;mem[q+2].int:=dvioffset+dviptr;
if o=157 then begin mem[q].hh.rh:=downptr;downptr:=q;
end else begin mem[q].hh.rh:=rightptr;rightptr:=q;end;
{622:}p:=mem[q].hh.rh;mstate:=0;
while p<>-1073741823 do begin if mem[p+1].int=w then{623:}case mstate+
mem[p].hh.lh of 3,4,15,16:if mem[p+2].int<dvigone then goto 45 else
{624:}begin k:=mem[p+2].int-dvioffset;if k<0 then k:=k+dvibufsize;
dvibuf[k]:=dvibuf[k]+5;mem[p].hh.lh:=1;goto 40;end{:624};
5,9,11:if mem[p+2].int<dvigone then goto 45 else{625:}begin k:=mem[p+2].
int-dvioffset;if k<0 then k:=k+dvibufsize;dvibuf[k]:=dvibuf[k]+10;
mem[p].hh.lh:=2;goto 40;end{:625};1,2,8,13:goto 40;
others:end{:623}else case mstate+mem[p].hh.lh of 1:mstate:=6;
2:mstate:=12;8,13:goto 45;others:end;p:=mem[p].hh.rh;end;45:{:622};
{621:}mem[q].hh.lh:=3;
if abs(w)>=8388608 then begin begin dvibuf[dviptr]:=o+3;incr(dviptr);
if dviptr=dvilimit then dviswap;end;dvifour(w);goto 10;end;
if abs(w)>=32768 then begin begin dvibuf[dviptr]:=o+2;incr(dviptr);
if dviptr=dvilimit then dviswap;end;if w<0 then w:=w+16777216;
begin dvibuf[dviptr]:=w div 65536;incr(dviptr);
if dviptr=dvilimit then dviswap;end;w:=w mod 65536;goto 2;end;
if abs(w)>=128 then begin begin dvibuf[dviptr]:=o+1;incr(dviptr);
if dviptr=dvilimit then dviswap;end;if w<0 then w:=w+65536;goto 2;end;
begin dvibuf[dviptr]:=o;incr(dviptr);if dviptr=dvilimit then dviswap;
end;if w<0 then w:=w+256;goto 1;2:begin dvibuf[dviptr]:=w div 256;
incr(dviptr);if dviptr=dvilimit then dviswap;end;
1:begin dvibuf[dviptr]:=w mod 256;incr(dviptr);
if dviptr=dvilimit then dviswap;end;goto 10{:621};
40:{620:}mem[q].hh.lh:=mem[p].hh.lh;
if mem[q].hh.lh=1 then begin begin dvibuf[dviptr]:=o+4;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
while mem[q].hh.rh<>p do begin q:=mem[q].hh.rh;
case mem[q].hh.lh of 3:mem[q].hh.lh:=5;4:mem[q].hh.lh:=6;others:end;end;
end else begin begin dvibuf[dviptr]:=o+9;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
while mem[q].hh.rh<>p do begin q:=mem[q].hh.rh;
case mem[q].hh.lh of 3:mem[q].hh.lh:=4;5:mem[q].hh.lh:=6;others:end;end;
end{:620};10:end;{:618}{626:}procedure prunemovements(l:integer);
label 30,10;var p:halfword;
begin while downptr<>-1073741823 do begin if mem[downptr+2].int<l then
goto 30;p:=downptr;downptr:=mem[p].hh.rh;freenode(p,3);end;
30:while rightptr<>-1073741823 do begin if mem[rightptr+2].int<l then
goto 10;p:=rightptr;rightptr:=mem[p].hh.rh;freenode(p,3);end;10:end;
{:626}{629:}procedure vlistout;forward;
{:629}{630:}{1381:}procedure specialout(p:halfword);
var oldsetting:0..21;k:poolpointer;
begin if curh<>dvih then begin movement(curh-dvih,143);dvih:=curh;end;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
oldsetting:=selector;selector:=21;
showtokenlist(mem[mem[p+1].hh.rh].hh.rh,-1073741823,poolsize-poolptr);
selector:=oldsetting;
begin if poolptr+1>poolsize then overflow(258,poolsize-initpoolptr);end;
if(poolptr-strstart[strptr])<256 then begin begin dvibuf[dviptr]:=239;
incr(dviptr);if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=(poolptr-strstart[strptr]);incr(dviptr);
if dviptr=dvilimit then dviswap;end;
end else begin begin dvibuf[dviptr]:=242;incr(dviptr);
if dviptr=dvilimit then dviswap;end;dvifour((poolptr-strstart[strptr]));
end;
for k:=strstart[strptr]to poolptr-1 do begin dvibuf[dviptr]:=strpool[k];
incr(dviptr);if dviptr=dvilimit then dviswap;end;
poolptr:=strstart[strptr];end;
{:1381}{1383:}procedure writeout(p:halfword);var oldsetting:0..21;
oldmode:integer;j:smallnumber;q,r:halfword;d:integer;clobbered:boolean;
runsystemret:integer;begin{1384:}q:=getavail;mem[q].hh.lh:=637;
r:=getavail;mem[q].hh.rh:=r;mem[r].hh.lh:=536886433;begintokenlist(q,4);
begintokenlist(mem[p+1].hh.rh,15);q:=getavail;mem[q].hh.lh:=379;
begintokenlist(q,4);oldmode:=curlist.modefield;curlist.modefield:=0;
curcs:=writeloc;q:=scantoks(false,true);gettoken;
if curtok<>536886433 then{1385:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1390);
end;begin helpptr:=2;helpline[1]:=1391;helpline[0]:=1071;end;error;
repeat gettoken;until curtok=536886433;end{:1385};
curlist.modefield:=oldmode;endtokenlist{:1384};oldsetting:=selector;
j:=mem[p+1].hh.lh;
if j=18 then selector:=21 else if writeopen[j]then selector:=j else
begin if(j=17)and(selector=19)then selector:=18;printnl(344);end;
tokenshow(defref);println;flushlist(defref);
if j=18 then begin if(eqtb[28491].int<=0)then selector:=18 else selector
:=19;if not logopened then selector:=17;printnl(1382);
for d:=0 to(poolptr-strstart[strptr])-1 do begin print(strpool[strstart[
strptr]+d]);end;print(1383);
if shellenabledp then begin begin if poolptr+1>poolsize then overflow(
258,poolsize-initpoolptr);end;begin strpool[poolptr]:=0;incr(poolptr);
end;clobbered:=false;
for d:=0 to(poolptr-strstart[strptr])-1 do begin strpool[strstart[strptr
]+d]:=xchr[strpool[strstart[strptr]+d]];
if(strpool[strstart[strptr]+d]=0)and(d<(poolptr-strstart[strptr])-1)then
clobbered:=true;end;
if clobbered then print(1384)else begin runsystemret:=runsystem(
conststringcast(addressof(strpool[strstart[strptr]])));
if runsystemret=-1 then print(1385)else if runsystemret=0 then print(
1386)else if runsystemret=1 then print(1387)else if runsystemret=2 then
print(1388)end;end else begin print(1389);end;printchar(46);
printnl(344);println;poolptr:=strstart[strptr];end;selector:=oldsetting;
end;{:1383}{1386:}procedure outwhat(p:halfword);var j:smallnumber;
oldsetting:0..21;
begin case mem[p].hh.b1 of 0,1,2:{1387:}if not doingleaders then begin j
:=mem[p+1].hh.lh;
if mem[p].hh.b1=1 then writeout(p)else begin if writeopen[j]then aclose(
writefile[j]);
if mem[p].hh.b1=2 then writeopen[j]:=false else if j<16 then begin
curname:=mem[p+1].hh.rh;curarea:=mem[p+2].hh.lh;curext:=mem[p+2].hh.rh;
if curext=344 then curext:=844;packfilename(curname,curarea,curext);
while not kpseoutnameok(stringcast(nameoffile+1))or not aopenout(
writefile[j])do promptfilename(1393,844);writeopen[j]:=true;
if logopened then begin oldsetting:=selector;
if(eqtb[28491].int<=0)then selector:=18 else selector:=19;printnl(1394);
printint(j);print(1395);printfilename(curname,curarea,curext);
print(843);printnl(344);println;selector:=oldsetting;end;end;end;
end{:1387};3:specialout(p);4:;others:confusion(1392)end;end;
{:1386}{1481:}procedure synchdir;var tmp:scaled;
begin case curdirhv of 4:if dvidir<>curdirhv then begin if curh<>dvih
then begin movement(curh-dvih,143);dvih:=curh;end;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
begin dvibuf[dviptr]:=255;incr(dviptr);if dviptr=dvilimit then dviswap;
end;begin dvibuf[dviptr]:=0;incr(dviptr);
if dviptr=dvilimit then dviswap;end;dirused:=true;
case dvidir of 3:begin tmp:=curh;curh:=-curv;curv:=tmp end;
1:begin tmp:=curh;curh:=curv;curv:=-tmp end;end;dvih:=curh;dviv:=curv;
dvidir:=curdirhv;end;
3:if dvidir<>curdirhv then begin if curh<>dvih then begin movement(curh-
dvih,143);dvih:=curh;end;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
begin dvibuf[dviptr]:=255;incr(dviptr);if dviptr=dvilimit then dviswap;
end;begin dvibuf[dviptr]:=1;incr(dviptr);
if dviptr=dvilimit then dviswap;end;dirused:=true;
case dvidir of 4:begin tmp:=curh;curh:=curv;curv:=-tmp end;
1:begin curv:=-curv;curh:=-curh;end;end;dvih:=curh;dviv:=curv;
dvidir:=curdirhv;end;
1:if dvidir<>curdirhv then begin if curh<>dvih then begin movement(curh-
dvih,143);dvih:=curh;end;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
begin dvibuf[dviptr]:=255;incr(dviptr);if dviptr=dvilimit then dviswap;
end;begin dvibuf[dviptr]:=3;incr(dviptr);
if dviptr=dvilimit then dviswap;end;dirused:=true;
case dvidir of 4:begin tmp:=curh;curh:=-curv;curv:=tmp end;
3:begin curv:=-curv;curh:=-curh;end;end;dvih:=curh;dviv:=curv;
dvidir:=curdirhv;end;others:confusion(1436);end end;
{:1481}{1483:}function checkbox(boxp:halfword):boolean;label 30;
var p:halfword;flag:boolean;begin flag:=false;p:=boxp;
while p<>-1073741823 do begin if(p>=himemmin)then repeat if
findfirstchar then begin firstchar:=p;findfirstchar:=false end;
lastchar:=p;flag:=true;if fontdir[mem[p].hh.b0]<>0 then p:=mem[p].hh.rh;
p:=mem[p].hh.rh;if p=-1073741823 then goto 30;until not(p>=himemmin);
case mem[p].hh.b0 of 0:begin flag:=true;
if mem[p+4].int=0 then begin if checkbox(mem[p+5].hh.rh)then flag:=true;
end else if findfirstchar then findfirstchar:=false else lastchar:=
-1073741823;end;8:if checkbox(mem[p+1].hh.rh)then flag:=true;
4,5,6,7,10,14:;
11:if(mem[p].hh.b1=0)or(mem[p].hh.b1=1)then begin if findfirstchar then
begin findfirstchar:=false;firstchar:=p;end;lastchar:=p;flag:=true;
end else;13:if mem[p].hh.b1=2 then begin p:=mem[p].hh.rh;
if(p>=himemmin)then if fontdir[mem[p].hh.b0]<>0 then p:=mem[p].hh.rh;
p:=mem[mem[p].hh.rh].hh.rh;
if findfirstchar then begin findfirstchar:=false;firstchar:=p;end;
lastchar:=p;flag:=true;if fontdir[mem[p].hh.b0]<>0 then p:=mem[p].hh.rh;
end else begin flag:=true;
if findfirstchar then findfirstchar:=false else lastchar:=-1073741823;
end;others:begin flag:=true;
if findfirstchar then findfirstchar:=false else lastchar:=-1073741823;
end;end;p:=mem[p].hh.rh;end;30:checkbox:=flag;end;
{:1483}{1484:}procedure adjusthlist(p:halfword;pf:boolean);label 10;
var q,s,t,u,v,x,z:halfword;i,k:halfword;a:halfword;insertskip:0..2;
cx:KANJIcode;ax:ASCIIcode;doins:boolean;
begin if mem[p].hh.rh=-1073741823 then goto 10;
if eqtb[25633].hh.rh>0 then begin deleteglueref(mem[p+7].hh.rh);
mem[p+7].hh.rh:=eqtb[24542].hh.rh;incr(mem[eqtb[24542].hh.rh].hh.rh);
end;if eqtb[25634].hh.rh>0 then begin deleteglueref(mem[p+7].hh.lh);
mem[p+7].hh.lh:=eqtb[24543].hh.rh;incr(mem[eqtb[24543].hh.rh].hh.rh);
end;u:=mem[p+7].hh.rh;incr(mem[u].hh.rh);s:=mem[p+7].hh.lh;
incr(mem[s].hh.rh);
if not(mem[p].hh.rh>=himemmin)and(mem[mem[p].hh.rh].hh.b0=12)and(mem[mem
[p].hh.rh].hh.b1=21)then begin v:=mem[p].hh.rh;
mem[p].hh.rh:=mem[v].hh.rh;
begin if mem[mem[v+1].hh.lh].hh.rh=-1073741823 then freenode(mem[v+1].hh
.lh,4)else decr(mem[mem[v+1].hh.lh].hh.rh);end;freenode(v,2);end;i:=0;
insertskip:=0;p:=mem[p].hh.rh;v:=p;q:=p;
while p<>-1073741823 do begin if(p>=himemmin)then begin repeat{1485:}if
fontdir[mem[p].hh.b0]<>0 then begin cx:=mem[mem[p].hh.rh].hh.lh mod
16777216;if insertskip=1 then{1492:}begin begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=1)then
doins:=false else doins:=true else doins:=true;end;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;end{:1492};
p:=mem[p].hh.rh;insertskip:=2;end else begin ax:=mem[p].hh.b1;
if insertskip=2 then{1493:}begin if(eqtb[26404+ax].hh.rh mod 2)=1 then
begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=2)then
doins:=false else doins:=true else doins:=true;end else doins:=false;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;end{:1493};
if eqtb[26404+ax].hh.rh>=2 then insertskip:=1 else insertskip:=0;
end{:1485};q:=p;p:=mem[p].hh.rh;incr(i);
if(i>5)and pf then begin if(v>=himemmin)then if fontdir[mem[v].hh.b0]<>0
then v:=mem[v].hh.rh;v:=mem[v].hh.rh;end;until not(p>=himemmin);
end else begin case mem[p].hh.b0 of 0:{1486:}begin findfirstchar:=true;
firstchar:=-1073741823;lastchar:=-1073741823;
if mem[p+4].int=0 then begin if checkbox(mem[p+5].hh.rh)then begin if
firstchar<>-1073741823 then{1487:}if mem[firstchar].hh.b0=11 then begin
ax:=48;
if insertskip=2 then{1493:}begin if(eqtb[26404+ax].hh.rh mod 2)=1 then
begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=2)then
doins:=false else doins:=true else doins:=true;end else doins:=false;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;end{:1493};
end else if fontdir[mem[firstchar].hh.b0]<>0 then begin cx:=mem[mem[
firstchar].hh.rh].hh.lh mod 16777216;
if insertskip=1 then{1492:}begin begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=1)then
doins:=false else doins:=true else doins:=true;end;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;
end{:1492}else if insertskip=2 then{1494:}begin z:=newglue(u);
mem[z].hh.b1:=16;mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;
end{:1494};end else begin ax:=mem[firstchar].hh.b1;
if insertskip=2 then{1493:}begin if(eqtb[26404+ax].hh.rh mod 2)=1 then
begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=2)then
doins:=false else doins:=true else doins:=true;end else doins:=false;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;end{:1493};end;
{:1487};
if lastchar<>-1073741823 then begin{1488:}if mem[lastchar].hh.b0=11 then
begin ax:=48;
if eqtb[26404+ax].hh.rh>=2 then insertskip:=1 else insertskip:=0;
end else if fontdir[mem[lastchar].hh.b0]<>0 then begin insertskip:=2;
cx:=mem[mem[lastchar].hh.rh].hh.lh;
if(mem[p].hh.rh>=himemmin)and(fontdir[mem[mem[p].hh.rh].hh.b0]<>0)then
begin{1495:}begin z:=newglue(u);mem[z].hh.b1:=16;
mem[z].hh.rh:=mem[p].hh.rh;mem[p].hh.rh:=z;p:=mem[z].hh.rh;q:=z;
end{:1495};p:=mem[p].hh.rh;end;end else begin ax:=mem[lastchar].hh.b1;
if eqtb[26404+ax].hh.rh>=2 then insertskip:=1 else insertskip:=0;end;
{:1488};end else insertskip:=0;end else insertskip:=0;
end else insertskip:=0;end{:1486};8:{1490:}begin t:=mem[p+1].hh.rh;
if(t>=himemmin)then begin ax:=mem[t].hh.b1;
if insertskip=2 then{1493:}begin if(eqtb[26404+ax].hh.rh mod 2)=1 then
begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=2)then
doins:=false else doins:=true else doins:=true;end else doins:=false;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;end{:1493};
while mem[t].hh.rh<>-1073741823 do t:=mem[t].hh.rh;
if(t>=himemmin)then begin ax:=mem[t].hh.b1;
if eqtb[26404+ax].hh.rh>=2 then insertskip:=1 else insertskip:=0;end;
end;end{:1490};
14,5:{1491:}begin if(mem[p].hh.rh>=himemmin)then begin q:=p;
p:=mem[p].hh.rh;
if fontdir[mem[p].hh.b0]<>0 then begin cx:=mem[mem[p].hh.rh].hh.lh mod
16777216;if insertskip=1 then{1492:}begin begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=1)then
doins:=false else doins:=true else doins:=true;end;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;
end{:1492}else if insertskip=2 then{1494:}begin z:=newglue(u);
mem[z].hh.b1:=16;mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;
end{:1494};p:=mem[p].hh.rh;insertskip:=2;
end else begin ax:=mem[p].hh.b1;
if insertskip=2 then{1493:}begin if(eqtb[26404+ax].hh.rh mod 2)=1 then
begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=2)then
doins:=false else doins:=true else doins:=true;end else doins:=false;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;end{:1493};
if eqtb[26404+ax].hh.rh>=2 then insertskip:=1 else insertskip:=0;end;
end end{:1491};
13:if mem[p].hh.b1=1 then insertskip:=0 else if mem[p].hh.b1=2 then
begin if q=p then begin t:=mem[p].hh.rh;
if(t>=himemmin)then if fontdir[mem[t].hh.b0]<>0 then t:=mem[t].hh.rh;
p:=mem[mem[t].hh.rh].hh.rh;
if fontdir[mem[p].hh.b0]<>0 then begin p:=mem[p].hh.rh;insertskip:=2;
end else insertskip:=1;end else begin a:=p;t:=mem[p].hh.rh;
if(t>=himemmin)then if fontdir[mem[t].hh.b0]<>0 then t:=mem[t].hh.rh;
t:=mem[mem[t].hh.rh].hh.rh;mem[q].hh.rh:=t;p:=t;
{1485:}if fontdir[mem[p].hh.b0]<>0 then begin cx:=mem[mem[p].hh.rh].hh.
lh mod 16777216;
if insertskip=1 then{1492:}begin begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=1)then
doins:=false else doins:=true else doins:=true;end;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;end{:1492};
p:=mem[p].hh.rh;insertskip:=2;end else begin ax:=mem[p].hh.b1;
if insertskip=2 then{1493:}begin if(eqtb[26404+ax].hh.rh mod 2)=1 then
begin x:=getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=2)then
doins:=false else doins:=true else doins:=true;end else doins:=false;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;end{:1493};
if eqtb[26404+ax].hh.rh>=2 then insertskip:=1 else insertskip:=0;
end{:1485};incr(i);
if(i>5)and pf then begin if(v>=himemmin)then if fontdir[mem[v].hh.b0]<>0
then v:=mem[v].hh.rh;v:=mem[v].hh.rh;end;
if mem[q].hh.rh<>t then mem[mem[q].hh.rh].hh.rh:=a else mem[q].hh.rh:=a;
end;end;
11:{1489:}begin if(mem[p].hh.b1=0)and(insertskip=2)then begin ax:=48;
{1493:}begin if(eqtb[26404+ax].hh.rh mod 2)=1 then begin x:=
getinhibitpos(cx,1);
if x<>1000 then if(eqtb[26660+x].hh.b0=0)or(eqtb[26660+x].hh.b0=2)then
doins:=false else doins:=true else doins:=true;end else doins:=false;
if doins then begin z:=newglue(s);mem[z].hh.b1:=17;
mem[z].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=z;q:=z;end;end{:1493};
insertskip:=0;end else if mem[p].hh.b1=1 then begin ax:=48;
if eqtb[26404+ax].hh.rh>=2 then insertskip:=1 else insertskip:=0;
end else insertskip:=0;end{:1489};6,7,4,10:;others:insertskip:=0;end;
q:=p;p:=mem[p].hh.rh;end;end;
if not(q>=himemmin)and(mem[q].hh.b0=12)and(mem[q].hh.b1=21)then begin
begin if mem[mem[q+1].hh.lh].hh.rh=-1073741823 then freenode(mem[q+1].hh
.lh,4)else decr(mem[mem[q+1].hh.lh].hh.rh);end;mem[q+1].hh.lh:=membot;
incr(mem[membot].hh.rh);end;deleteglueref(u);deleteglueref(s);
if(v<>-1073741823)and pf and(i>5)then{1496:}begin q:=v;p:=mem[v].hh.rh;
if(v>=himemmin)and(fontdir[mem[v].hh.b0]<>0)then begin q:=p;
p:=mem[p].hh.rh;end;t:=q;s:=-1073741823;
{1497:}while(p<>-1073741823)do begin if(p>=himemmin)then begin if
fontdir[mem[p].hh.b0]<>0 then begin cx:=mem[mem[p].hh.rh].hh.lh mod
16777216;i:=mem[mem[p].hh.rh].hh.lh div 16777216;k:=0;
if(i=16)or(i=17)or(i=19)then begin t:=q;s:=p;end;p:=mem[p].hh.rh;q:=p;
end else begin k:=k+1;if k>1 then begin q:=p;s:=-1073741823;end;end;
end else begin case mem[p].hh.b0 of 14,6,7,10,12,13,11,5:;
others:begin q:=p;s:=-1073741823;end;end;end;p:=mem[p].hh.rh;end{:1497};
if s<>-1073741823 then begin s:=mem[t].hh.rh;
if not(s>=himemmin)and(mem[s].hh.b0=14)then mem[s+1].int:=mem[s+1].int+
eqtb[28518].int else if eqtb[28518].int<>0 then begin s:=newpenalty(eqtb
[28518].int);mem[s].hh.b1:=1;mem[s].hh.rh:=mem[t].hh.rh;mem[t].hh.rh:=s;
t:=mem[s].hh.rh;
while(not(t>=himemmin))do begin if(mem[t].hh.b0=12)or(mem[t].hh.b0=13)
then goto 10;t:=mem[t].hh.rh;end;z:=newglue(u);mem[z].hh.b1:=16;
mem[z].hh.rh:=mem[s].hh.rh;mem[s].hh.rh:=z;end;end;end;{:1496};10:end;
{:1484}{1498:}procedure dirout;var thisbox:halfword;
begin thisbox:=tempptr;tempptr:=mem[thisbox+5].hh.rh;
if(mem[tempptr].hh.b0<>0)and(mem[tempptr].hh.b0<>1)then confusion(1437);
case(mem[thisbox].hh.b1)of 4:case(mem[tempptr].hh.b1)of 3:begin curv:=
curv-mem[thisbox+3].int;curh:=curh+mem[tempptr+2].int end;
1:begin curv:=curv+mem[thisbox+2].int;curh:=curh+mem[tempptr+3].int end;
end;3:case(mem[tempptr].hh.b1)of 4:begin curv:=curv+mem[thisbox+2].int;
curh:=curh+mem[tempptr+3].int end;
1:begin curv:=curv+mem[thisbox+2].int-mem[tempptr+3].int;
curh:=curh+mem[tempptr+1].int end;end;
1:case(mem[tempptr].hh.b1)of 4:begin curv:=curv-mem[thisbox+3].int;
curh:=curh+mem[tempptr+2].int end;
3:begin curv:=curv+mem[thisbox+2].int-mem[tempptr+3].int;
curh:=curh+mem[tempptr+1].int end;end;end;
curdirhv:=(mem[tempptr].hh.b1);
if mem[tempptr].hh.b0=1 then vlistout else hlistout;end;
{:1498}procedure hlistout;label 21,13,14,15,22,40;var baseline:scaled;
disp:scaled;savedir:eightbits;jc:KANJIcode;kspptr:halfword;
leftedge:scaled;saveh,savev:scaled;thisbox:halfword;gorder:glueord;
gsign:0..2;p:halfword;saveloc:integer;leaderbox:halfword;
leaderwd:scaled;lx:scaled;outerdoingleaders:boolean;edge:scaled;
gluetemp:real;curglue:real;curg:scaled;begin curg:=0;curglue:=0.0;
thisbox:=tempptr;gorder:=mem[thisbox+5].hh.b1;
gsign:=mem[thisbox+5].hh.b0;p:=mem[thisbox+5].hh.rh;
kspptr:=mem[thisbox+7].hh.rh;incr(curs);
if curs>0 then begin dvibuf[dviptr]:=141;incr(dviptr);
if dviptr=dvilimit then dviswap;end;if curs>maxpush then maxpush:=curs;
saveloc:=dvioffset+dviptr;synchdir;baseline:=curv;leftedge:=curh;
disp:=0;{1437:}synctexhlist(thisbox);{:1437};
while p<>-1073741823 do{631:}21:if(p>=himemmin)then begin if curh<>dvih
then begin movement(curh-dvih,143);dvih:=curh;end;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
chain:=false;repeat f:=mem[p].hh.b0;c:=mem[p].hh.b1;
if f<>dvif then{632:}begin if not fontused[f]then begin dvifontdef(f);
fontused[f]:=true;end;if f<=64 then begin dvibuf[dviptr]:=f+170;
incr(dviptr);if dviptr=dvilimit then dviswap;
end else if f<=256 then begin begin dvibuf[dviptr]:=235;incr(dviptr);
if dviptr=dvilimit then dviswap;end;begin dvibuf[dviptr]:=f-1;
incr(dviptr);if dviptr=dvilimit then dviswap;end;
end else begin begin dvibuf[dviptr]:=236;incr(dviptr);
if dviptr=dvilimit then dviswap;end;begin dvibuf[dviptr]:=(f-1)div 256;
incr(dviptr);if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=(f-1)mod 256;incr(dviptr);
if dviptr=dvilimit then dviswap;end;end;dvif:=f;end{:632};
if fontdir[f]=0 then begin chain:=false;
if fontec[f]>=c then if fontbc[f]<=c then if(fontinfo[charbase[f]+c].
qqqq.b0>0)then begin if c>=128 then begin dvibuf[dviptr]:=128;
incr(dviptr);if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=c;incr(dviptr);if dviptr=dvilimit then dviswap;
end;
curh:=curh+fontinfo[widthbase[f]+fontinfo[charbase[f]+c].qqqq.b0].int;
goto 22;end;
if mltexenabledp then{1409:}begin{1411:}if c>=eqtb[28522].int then if c
<=eqtb[28523].int then if(eqtb[28206+c].hh.rh>0)then begin basec:=(eqtb[
28206+c].hh.rh mod 256);accentc:=(eqtb[28206+c].hh.rh div 256);
if(fontec[f]>=basec)then if(fontbc[f]<=basec)then if(fontec[f]>=accentc)
then if(fontbc[f]<=accentc)then begin iac:=fontinfo[charbase[f]+
effectivechar(true,f,accentc)].qqqq;
ibc:=fontinfo[charbase[f]+effectivechar(true,f,basec)].qqqq;
if(ibc.b0>0)then if(iac.b0>0)then goto 40;end;begindiagnostic;
printnl(1397);print(c);print(1278);print(accentc);print(32);
print(basec);print(881);slowprint(fontname[f]);printchar(33);
enddiagnostic(false);goto 22;end;begindiagnostic;printnl(880);
print(1396);print(c);print(881);slowprint(fontname[f]);printchar(33);
enddiagnostic(false);goto 22{:1411};
40:{1412:}if eqtb[28497].int>99 then begin begindiagnostic;
printnl(1398);print(c);print(1278);print(accentc);print(32);
print(basec);print(881);slowprint(fontname[f]);printchar(46);
enddiagnostic(false);end{:1412};
{1413:}basexheight:=fontinfo[5+parambase[f]].int;
baseslant:=fontinfo[1+parambase[f]].int/65536.0;accentslant:=baseslant;
basewidth:=fontinfo[widthbase[f]+ibc.b0].int;
baseheight:=fontinfo[heightbase[f]+(ibc.b1)div 16].int;
accentwidth:=fontinfo[widthbase[f]+iac.b0].int;
accentheight:=fontinfo[heightbase[f]+(iac.b1)div 16].int;
delta:=round((basewidth-accentwidth)/2.0+baseheight*baseslant-
basexheight*accentslant);dvih:=curh;curh:=curh+delta;
if curh<>dvih then begin movement(curh-dvih,143);dvih:=curh;end;
if((baseheight<>basexheight)and(accentheight>0))then begin curv:=
baseline+(basexheight-baseheight);
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
if accentc>=128 then begin dvibuf[dviptr]:=128;incr(dviptr);
if dviptr=dvilimit then dviswap;end;begin dvibuf[dviptr]:=accentc;
incr(dviptr);if dviptr=dvilimit then dviswap;end;curv:=baseline;
end else begin if curv<>dviv then begin movement(curv-dviv,157);
dviv:=curv;end;if accentc>=128 then begin dvibuf[dviptr]:=128;
incr(dviptr);if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=accentc;incr(dviptr);
if dviptr=dvilimit then dviswap;end;end;curh:=curh+accentwidth;
dvih:=curh;curh:=curh+(-accentwidth-delta);
if curh<>dvih then begin movement(curh-dvih,143);dvih:=curh;end;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
if basec>=128 then begin dvibuf[dviptr]:=128;incr(dviptr);
if dviptr=dvilimit then dviswap;end;begin dvibuf[dviptr]:=basec;
incr(dviptr);if dviptr=dvilimit then dviswap;end;curh:=curh+basewidth;
dvih:=curh{:1413};end{:1409};
22:end else begin if chain=false then chain:=true else begin curh:=curh+
mem[kspptr+1].int;
if gsign<>0 then begin if gsign=1 then begin if mem[kspptr].hh.b0=gorder
then curh:=curh+round(mem[thisbox+6].gr*mem[kspptr+2].int);
end else begin if mem[kspptr].hh.b1=gorder then curh:=curh-round(mem[
thisbox+6].gr*mem[kspptr+3].int);end;end;
if curh<>dvih then begin movement(curh-dvih,143);dvih:=curh;end;end;
p:=mem[p].hh.rh;jc:=toDVI(mem[p].hh.lh mod 16777216);
if(jc<65536)then begin begin dvibuf[dviptr]:=129;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
end else begin begin dvibuf[dviptr]:=130;incr(dviptr);
if dviptr=dvilimit then dviswap;end;begin dvibuf[dviptr]:=BYTE2(jc);
incr(dviptr);if dviptr=dvilimit then dviswap;end;end;
begin dvibuf[dviptr]:=BYTE3(jc);incr(dviptr);
if dviptr=dvilimit then dviswap;end;begin dvibuf[dviptr]:=BYTE4(jc);
incr(dviptr);if dviptr=dvilimit then dviswap;end;
curh:=curh+fontinfo[widthbase[f]+fontinfo[charbase[f]+c].qqqq.b0].int;
end;dvih:=curh;p:=mem[p].hh.rh;until not(p>=himemmin);
{1440:}synctexcurrent;{:1440};chain:=false;
end else{633:}begin case mem[p].hh.b0 of 0,1,2:{634:}if mem[p+5].hh.rh=
-1073741823 then begin if mem[p].hh.b0<>2 then{1439:}if mem[p].hh.b0=1
then begin synctexvoidvlist(p,thisbox);
end else begin synctexvoidhlist(p,thisbox);end;{:1439};
curh:=curh+mem[p+1].int;end else begin saveh:=dvih;savev:=dviv;
savedir:=dvidir;curv:=baseline+disp+mem[p+4].int;tempptr:=p;edge:=curh;
case mem[p].hh.b0 of 0:hlistout;1:vlistout;2:dirout;end;dvih:=saveh;
dviv:=savev;dvidir:=savedir;curh:=edge+mem[p+1].int;curv:=baseline+disp;
curdirhv:=savedir;end{:634};3:begin ruleht:=mem[p+3].int;
ruledp:=mem[p+2].int;rulewd:=mem[p+1].int;goto 14;end;
10:{1380:}outwhat(p){:1380};5:begin disp:=mem[p+1].int;
curv:=baseline+disp;end;12:{636:}begin g:=mem[p+1].hh.lh;
rulewd:=mem[g+1].int-curg;
if gsign<>0 then begin if gsign=1 then begin if mem[g].hh.b0=gorder then
begin curglue:=curglue+mem[g+2].int;gluetemp:=mem[thisbox+6].gr*curglue;
if gluetemp>1000000000.0 then gluetemp:=1000000000.0 else if gluetemp<
-1000000000.0 then gluetemp:=-1000000000.0;curg:=round(gluetemp);end;
end else if mem[g].hh.b1=gorder then begin curglue:=curglue-mem[g+3].int
;gluetemp:=mem[thisbox+6].gr*curglue;
if gluetemp>1000000000.0 then gluetemp:=1000000000.0 else if gluetemp<
-1000000000.0 then gluetemp:=-1000000000.0;curg:=round(gluetemp);end;
end;rulewd:=rulewd+curg;
if mem[p].hh.b1>=100 then{637:}begin leaderbox:=mem[p+1].hh.rh;
if mem[leaderbox].hh.b0=3 then begin ruleht:=mem[leaderbox+3].int;
ruledp:=mem[leaderbox+2].int;goto 14;end;leaderwd:=mem[leaderbox+1].int;
if(leaderwd>0)and(rulewd>0)then begin rulewd:=rulewd+10;
edge:=curh+rulewd;lx:=0;
{638:}if mem[p].hh.b1=100 then begin saveh:=curh;
curh:=leftedge+leaderwd*((curh-leftedge)div leaderwd);
if curh<saveh then curh:=curh+leaderwd;
end else begin lq:=rulewd div leaderwd;lr:=rulewd mod leaderwd;
if mem[p].hh.b1=101 then curh:=curh+(lr div 2)else begin lx:=lr div(lq+1
);curh:=curh+((lr-(lq-1)*lx)div 2);end;end{:638};
while curh+leaderwd<=edge do{639:}begin curv:=baseline+disp+mem[
leaderbox+4].int;if curv<>dviv then begin movement(curv-dviv,157);
dviv:=curv;end;savev:=dviv;
if curh<>dvih then begin movement(curh-dvih,143);dvih:=curh;end;
saveh:=dvih;savedir:=dvidir;tempptr:=leaderbox;
outerdoingleaders:=doingleaders;doingleaders:=true;
case mem[leaderbox].hh.b0 of 0:hlistout;1:vlistout;2:dirout;end;
doingleaders:=outerdoingleaders;dviv:=savev;dvih:=saveh;dvidir:=savedir;
curv:=baseline;curh:=saveh+leaderwd+lx;curdirhv:=savedir;end{:639};
curh:=edge-10;goto 15;end;end{:637};goto 13;end{:636};
13:begin{1442:}synctexkern(p,thisbox);{:1442};curh:=curh+mem[p+1].int;
end;11:begin{1443:}synctexmath(p,thisbox);{:1443};
curh:=curh+mem[p+1].int;end;8:{663:}begin mem[memtop-12]:=mem[p+1];
mem[memtop-12].hh.rh:=mem[p].hh.rh;p:=memtop-12;goto 21;end{:663};
others:end;goto 15;
14:{635:}if(ruleht=-1073741824)then ruleht:=mem[thisbox+3].int+disp;
if(ruledp=-1073741824)then ruledp:=mem[thisbox+2].int-disp;
ruleht:=ruleht+ruledp;
if(ruleht>0)and(rulewd>0)then begin if curh<>dvih then begin movement(
curh-dvih,143);dvih:=curh;end;curv:=baseline+ruledp;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
begin dvibuf[dviptr]:=132;incr(dviptr);if dviptr=dvilimit then dviswap;
end;dvifour(ruleht);dvifour(rulewd);curv:=baseline;dvih:=dvih+rulewd;
end{:635};13:begin curh:=curh+rulewd;
{1441:}synctexhorizontalruleorglue(p,thisbox);{:1441};end;
15:p:=mem[p].hh.rh;end{:633}{:631};{1438:}synctextsilh(thisbox);{:1438};
prunemovements(saveloc);if curs>0 then dvipop(saveloc);decr(curs);end;
{:630}{640:}procedure vlistout;label 13,14,15;var leftedge:scaled;
topedge:scaled;saveh,savev:scaled;thisbox:halfword;gorder:glueord;
gsign:0..2;p:halfword;saveloc:integer;leaderbox:halfword;
leaderht:scaled;lx:scaled;outerdoingleaders:boolean;edge:scaled;
gluetemp:real;curglue:real;curg:scaled;savedir:integer;begin curg:=0;
curglue:=0.0;thisbox:=tempptr;gorder:=mem[thisbox+5].hh.b1;
gsign:=mem[thisbox+5].hh.b0;p:=mem[thisbox+5].hh.rh;incr(curs);
if curs>0 then begin dvibuf[dviptr]:=141;incr(dviptr);
if dviptr=dvilimit then dviswap;end;if curs>maxpush then maxpush:=curs;
saveloc:=dvioffset+dviptr;synchdir;leftedge:=curh;
{1435:}synctexvlist(thisbox);{:1435};curv:=curv-mem[thisbox+3].int;
topedge:=curv;
while p<>-1073741823 do{641:}begin if(p>=himemmin)then confusion(884)
else{642:}begin case mem[p].hh.b0 of 0,1,2:{643:}if mem[p+5].hh.rh=
-1073741823 then begin curv:=curv+mem[p+3].int;
if mem[p].hh.b0<>2 then{1439:}if mem[p].hh.b0=1 then begin
synctexvoidvlist(p,thisbox);end else begin synctexvoidhlist(p,thisbox);
end;{:1439};curv:=curv+mem[p+2].int;
end else begin curv:=curv+mem[p+3].int;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
saveh:=dvih;savev:=dviv;savedir:=dvidir;curh:=leftedge+mem[p+4].int;
tempptr:=p;case mem[p].hh.b0 of 0:hlistout;1:vlistout;2:dirout;end;
dvih:=saveh;dviv:=savev;dvidir:=savedir;curv:=savev+mem[p+2].int;
curh:=leftedge;curdirhv:=savedir;end{:643};3:begin ruleht:=mem[p+3].int;
ruledp:=mem[p+2].int;rulewd:=mem[p+1].int;goto 14;end;
10:{1379:}outwhat(p){:1379};12:{645:}begin g:=mem[p+1].hh.lh;
ruleht:=mem[g+1].int-curg;
if gsign<>0 then begin if gsign=1 then begin if mem[g].hh.b0=gorder then
begin curglue:=curglue+mem[g+2].int;gluetemp:=mem[thisbox+6].gr*curglue;
if gluetemp>1000000000.0 then gluetemp:=1000000000.0 else if gluetemp<
-1000000000.0 then gluetemp:=-1000000000.0;curg:=round(gluetemp);end;
end else if mem[g].hh.b1=gorder then begin curglue:=curglue-mem[g+3].int
;gluetemp:=mem[thisbox+6].gr*curglue;
if gluetemp>1000000000.0 then gluetemp:=1000000000.0 else if gluetemp<
-1000000000.0 then gluetemp:=-1000000000.0;curg:=round(gluetemp);end;
end;ruleht:=ruleht+curg;
if mem[p].hh.b1>=100 then{646:}begin leaderbox:=mem[p+1].hh.rh;
if mem[leaderbox].hh.b0=3 then begin rulewd:=mem[leaderbox+1].int;
ruledp:=0;goto 14;end;
leaderht:=mem[leaderbox+3].int+mem[leaderbox+2].int;
if(leaderht>0)and(ruleht>0)then begin ruleht:=ruleht+10;
edge:=curv+ruleht;lx:=0;
{647:}if mem[p].hh.b1=100 then begin savev:=curv;
curv:=topedge+leaderht*((curv-topedge)div leaderht);
if curv<savev then curv:=curv+leaderht;
end else begin lq:=ruleht div leaderht;lr:=ruleht mod leaderht;
if mem[p].hh.b1=101 then curv:=curv+(lr div 2)else begin lx:=lr div(lq+1
);curv:=curv+((lr-(lq-1)*lx)div 2);end;end{:647};
while curv+leaderht<=edge do{648:}begin curh:=leftedge+mem[leaderbox+4].
int;if curh<>dvih then begin movement(curh-dvih,143);dvih:=curh;end;
saveh:=dvih;curv:=curv+mem[leaderbox+3].int;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
savev:=dviv;savedir:=dvidir;tempptr:=leaderbox;
outerdoingleaders:=doingleaders;doingleaders:=true;
case mem[leaderbox].hh.b0 of 0:hlistout;1:vlistout;2:dirout;end;
doingleaders:=outerdoingleaders;dviv:=savev;dvih:=saveh;dvidir:=savedir;
curh:=leftedge;curv:=savev-mem[leaderbox+3].int+leaderht+lx;
curdirhv:=savedir;end{:648};curv:=edge-10;goto 15;end;end{:646};goto 13;
end{:645};13:curv:=curv+mem[p+1].int;others:end;goto 15;
14:{644:}if(rulewd=-1073741824)then rulewd:=mem[thisbox+1].int;
ruleht:=ruleht+ruledp;curv:=curv+ruleht;
if(ruleht>0)and(rulewd>0)then begin if curh<>dvih then begin movement(
curh-dvih,143);dvih:=curh;end;
if curv<>dviv then begin movement(curv-dviv,157);dviv:=curv;end;
begin dvibuf[dviptr]:=137;incr(dviptr);if dviptr=dvilimit then dviswap;
end;dvifour(ruleht);dvifour(rulewd);end;goto 15{:644};
13:curv:=curv+ruleht;end{:642};15:p:=mem[p].hh.rh;end{:641};
{1436:}synctextsilv(thisbox);{:1436};prunemovements(saveloc);
if curs>0 then dvipop(saveloc);decr(curs);end;
{:640}{649:}procedure shipout(p:halfword);label 30;var pageloc:integer;
delnode:halfword;j,k:0..9;s:poolpointer;oldsetting:0..21;
begin{1433:}synctexsheet(eqtb[28479].int);{:1433};
begin if eqtb[28496].int>0 then begin printnl(344);println;print(885);
end;if termoffset>maxprintline-9 then println else if(termoffset>0)or(
fileoffset>0)then printchar(32);printchar(91);j:=9;
while(eqtb[28526+j].int=0)and(j>0)do decr(j);
for k:=0 to j do begin printint(eqtb[28526+k].int);
if k<j then printchar(46);end;fflush(stdout);
if eqtb[28496].int>0 then begin printchar(93);begindiagnostic;
showbox(p);enddiagnostic(true);end;
if mem[p].hh.b0=2 then begin delnode:=p;p:=mem[p+5].hh.rh;
deleteglueref(mem[delnode+7].hh.rh);deleteglueref(mem[delnode+7].hh.lh);
freenode(delnode,10);end;flushnodelist(mem[p].hh.rh);
mem[p].hh.rh:=-1073741823;if(mem[p].hh.b1)<>4 then p:=newdirnode(p,4);
{651:}{652:}if(mem[p+3].int>1073741823)or(mem[p+2].int>1073741823)or(mem
[p+3].int+mem[p+2].int+eqtb[29057].int>1073741823)or(mem[p+1].int+eqtb[
29056].int>1073741823)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(889);
end;begin helpptr:=2;helpline[1]:=890;helpline[0]:=891;end;error;
if eqtb[28496].int<=0 then begin begindiagnostic;printnl(892);
showbox(p);enddiagnostic(true);end;goto 30;end;
if mem[p+3].int+mem[p+2].int+eqtb[29057].int>maxv then maxv:=mem[p+3].
int+mem[p+2].int+eqtb[29057].int;
if mem[p+1].int+eqtb[29056].int>maxh then maxh:=mem[p+1].int+eqtb[29056]
.int{:652};{628:}dvih:=0;dviv:=0;curh:=eqtb[29056].int;dvif:=0;
dvidir:=4;curdirhv:=dvidir;
if outputfilename=0 then begin if jobname=0 then openlogfile;
packjobname(848);while not bopenout(dvifile)do promptfilename(849,848);
outputfilename:=bmakenamestring(dvifile);end;
if totalpages=0 then begin begin dvibuf[dviptr]:=247;incr(dviptr);
if dviptr=dvilimit then dviswap;end;begin dvibuf[dviptr]:=2;
incr(dviptr);if dviptr=dvilimit then dviswap;end;dvifour(25400000);
dvifour(473628672);preparemag;dvifour(eqtb[28479].int);
if outputcomment then begin l:=strlen(outputcomment);
begin dvibuf[dviptr]:=l;incr(dviptr);if dviptr=dvilimit then dviswap;
end;for s:=0 to l-1 do begin dvibuf[dviptr]:=outputcomment[s];
incr(dviptr);if dviptr=dvilimit then dviswap;end;
end else begin oldsetting:=selector;selector:=21;print(883);
printint(eqtb[28485].int);printchar(46);printtwo(eqtb[28484].int);
printchar(46);printtwo(eqtb[28483].int);printchar(58);
printtwo(eqtb[28482].int div 60);printtwo(eqtb[28482].int mod 60);
selector:=oldsetting;begin dvibuf[dviptr]:=(poolptr-strstart[strptr]);
incr(dviptr);if dviptr=dvilimit then dviswap;end;
for s:=strstart[strptr]to poolptr-1 do begin dvibuf[dviptr]:=strpool[s];
incr(dviptr);if dviptr=dvilimit then dviswap;end;
poolptr:=strstart[strptr];end;end{:628};pageloc:=dvioffset+dviptr;
begin dvibuf[dviptr]:=139;incr(dviptr);if dviptr=dvilimit then dviswap;
end;for k:=0 to 9 do dvifour(eqtb[28526+k].int);dvifour(lastbop);
lastbop:=pageloc;curv:=mem[p+3].int+eqtb[29057].int;tempptr:=p;
case mem[p].hh.b0 of 0:hlistout;1:vlistout;2:dirout;end;
begin dvibuf[dviptr]:=140;incr(dviptr);if dviptr=dvilimit then dviswap;
end;incr(totalpages);curs:=-1;
ifdef('IPC')if ipcon>0 then begin if dvilimit=halfbuf then begin
writedvi(halfbuf,dvibufsize-1);flushdvi;dvigone:=dvigone+halfbuf;end;
if dviptr>(2147483647-dvioffset)then begin curs:=-2;fatalerror(882);end;
if dviptr>0 then begin writedvi(0,dviptr-1);flushdvi;
dvioffset:=dvioffset+dviptr;dvigone:=dvigone+dviptr;end;dviptr:=0;
dvilimit:=dvibufsize;ipcpage(dvigone);end;endif('IPC');30:{:651};
if eqtb[28496].int<=0 then printchar(93);deadcycles:=0;fflush(stdout);
{650:}ifdef('STAT')if eqtb[28493].int>1 then begin printnl(886);
printint(varused);printchar(38);printint(dynused);printchar(59);end;
endif('STAT')flushnodelist(p);
ifdef('STAT')if eqtb[28493].int>1 then begin print(887);
printint(varused);printchar(38);printint(dynused);print(888);
printint(himemmin-lomemmax-1);println;end;endif('STAT'){:650};end;
{1434:}synctexteehs;{:1434};end;
{:649}{656:}procedure scanspec(c:groupcode;threecodes:boolean);label 40;
var s:integer;speccode:0..1;
begin if threecodes then s:=savestack[saveptr+0].int;
if scankeyword(898)then speccode:=0 else if scankeyword(899)then
speccode:=1 else begin speccode:=1;curval:=0;goto 40;end;
scandimen(false,false,false);
40:if threecodes then begin savestack[saveptr+0].int:=s;incr(saveptr);
end;savestack[saveptr+0].int:=speccode;savestack[saveptr+1].int:=curval;
saveptr:=saveptr+2;newsavelevel(c);scanleftbrace;end;
{:656}{660:}function hpack(p:halfword;w:scaled;m:smallnumber):halfword;
label 21,50,10;var r:halfword;k:halfword;disp:scaled;q:halfword;
h,d,x:scaled;s:scaled;g:halfword;o:glueord;f:internalfontnumber;
i:fourquarters;hd:eightbits;begin lastbadness:=0;r:=getnode(10);
mem[r].hh.b0:=0;mem[r].hh.b1:=0;mem[r+4].int:=0;
mem[r+7].hh.rh:=curkanjiskip;mem[r+7].hh.lh:=curxkanjiskip;
incr(mem[curkanjiskip].hh.rh);incr(mem[curxkanjiskip].hh.rh);
k:=curkanjiskip;q:=r+5;mem[q].hh.rh:=p;h:=0;{661:}d:=0;x:=0;
totalstretch[0]:=0;totalshrink[0]:=0;totalstretch[1]:=0;
totalshrink[1]:=0;totalstretch[2]:=0;totalshrink[2]:=0;
totalstretch[3]:=0;totalshrink[3]:=0{:661};disp:=0;
while p<>-1073741823 do{662:}begin 21:chain:=false;
while(p>=himemmin)do{665:}begin f:=mem[p].hh.b0;
i:=fontinfo[charbase[f]+effectivechar(true,f,mem[p].hh.b1)].qqqq;
hd:=i.b1;x:=x+fontinfo[widthbase[f]+i.b0].int;
s:=fontinfo[heightbase[f]+(hd)div 16].int-disp;if s>h then h:=s;
s:=fontinfo[depthbase[f]+(hd)mod 16].int+disp;if s>d then d:=s;
if fontdir[f]<>0 then begin p:=mem[p].hh.rh;
if chain then begin x:=x+mem[k+1].int;o:=mem[k].hh.b0;
totalstretch[o]:=totalstretch[o]+mem[k+2].int;o:=mem[k].hh.b1;
totalshrink[o]:=totalshrink[o]+mem[k+3].int;end else chain:=true;
end else chain:=false;p:=mem[p].hh.rh;end{:665};
if p<>-1073741823 then begin case mem[p].hh.b0 of 0,1,2,3,15:{664:}begin
x:=x+mem[p+1].int;
if mem[p].hh.b0>=3 then s:=disp else s:=mem[p+4].int+disp;
if mem[p+3].int-s>h then h:=mem[p+3].int-s;
if mem[p+2].int+s>d then d:=mem[p+2].int+s;end{:664};
4,6,7:if adjusttail<>-1073741823 then{666:}begin while mem[q].hh.rh<>p
do q:=mem[q].hh.rh;
if mem[p].hh.b0=7 then begin mem[adjusttail].hh.rh:=mem[p+1].int;
while mem[adjusttail].hh.rh<>-1073741823 do adjusttail:=mem[adjusttail].
hh.rh;p:=mem[p].hh.rh;freenode(mem[q].hh.rh,2);
end else begin mem[adjusttail].hh.rh:=p;adjusttail:=p;p:=mem[p].hh.rh;
end;mem[q].hh.rh:=p;p:=q;end{:666};10:{1373:}{:1373};
5:disp:=mem[p+1].int;12:{667:}begin g:=mem[p+1].hh.lh;x:=x+mem[g+1].int;
o:=mem[g].hh.b0;totalstretch[o]:=totalstretch[o]+mem[g+2].int;
o:=mem[g].hh.b1;totalshrink[o]:=totalshrink[o]+mem[g+3].int;
if mem[p].hh.b1>=100 then begin g:=mem[p+1].hh.rh;
if mem[g+3].int>h then h:=mem[g+3].int;
if mem[g+2].int>d then d:=mem[g+2].int;end;end{:667};
13,11:x:=x+mem[p+1].int;8:{663:}begin mem[memtop-12]:=mem[p+1];
mem[memtop-12].hh.rh:=mem[p].hh.rh;p:=memtop-12;goto 21;end{:663};
others:end;p:=mem[p].hh.rh;end;end{:662};
if adjusttail<>-1073741823 then mem[adjusttail].hh.rh:=-1073741823;
mem[r+3].int:=h;mem[r+2].int:=d;{668:}if m=1 then w:=x+w;
mem[r+1].int:=w;x:=w-x;if x=0 then begin mem[r+5].hh.b0:=0;
mem[r+5].hh.b1:=0;mem[r+6].gr:=0.0;goto 10;
end else if x>0 then{669:}begin{670:}if totalstretch[3]<>0 then o:=3
else if totalstretch[2]<>0 then o:=2 else if totalstretch[1]<>0 then o:=
1 else o:=0{:670};mem[r+5].hh.b1:=o;mem[r+5].hh.b0:=1;
if totalstretch[o]<>0 then mem[r+6].gr:=x/totalstretch[o]else begin mem[
r+5].hh.b0:=0;mem[r+6].gr:=0.0;end;
if o=0 then if mem[r+5].hh.rh<>-1073741823 then{671:}begin lastbadness:=
badness(x,totalstretch[0]);
if lastbadness>eqtb[28488].int then begin println;
if lastbadness>100 then printnl(900)else printnl(901);print(902);
printint(lastbadness);goto 50;end;end{:671};goto 10;
end{:669}else{675:}begin{676:}if totalshrink[3]<>0 then o:=3 else if
totalshrink[2]<>0 then o:=2 else if totalshrink[1]<>0 then o:=1 else o:=
0{:676};mem[r+5].hh.b1:=o;mem[r+5].hh.b0:=2;
if totalshrink[o]<>0 then mem[r+6].gr:=(-x)/totalshrink[o]else begin mem
[r+5].hh.b0:=0;mem[r+6].gr:=0.0;end;
if(totalshrink[o]<-x)and(o=0)and(mem[r+5].hh.rh<>-1073741823)then begin
lastbadness:=1000000;mem[r+6].gr:=1.0;
{677:}if(-x-totalshrink[0]>eqtb[29046].int)or(eqtb[28488].int<100)then
begin if(eqtb[29054].int>0)and(-x-totalshrink[0]>eqtb[29046].int)then
begin while mem[q].hh.rh<>-1073741823 do q:=mem[q].hh.rh;
mem[q].hh.rh:=newrule;mem[mem[q].hh.rh+1].int:=eqtb[29054].int;end;
println;printnl(908);printscaled(-x-totalshrink[0]);print(909);goto 50;
end{:677};
end else if o=0 then if mem[r+5].hh.rh<>-1073741823 then{678:}begin
lastbadness:=badness(-x,totalshrink[0]);
if lastbadness>eqtb[28488].int then begin println;printnl(910);
printint(lastbadness);goto 50;end;end{:678};goto 10;end{:675}{:668};
50:{674:}if outputactive then print(903)else begin if packbeginline<>0
then begin if packbeginline>0 then print(904)else print(905);
printint(abs(packbeginline));print(906);end else print(907);
printint(line);end;println;fontinshortdisplay:=0;
shortdisplay(mem[r+5].hh.rh);println;begindiagnostic;showbox(r);
enddiagnostic(true){:674};10:lastdisp:=disp;hpack:=r;end;
{:660}{679:}function vpackage(p:halfword;h:scaled;m:smallnumber;
l:scaled):halfword;label 50,10;var r:halfword;w,d,x:scaled;s:scaled;
g:halfword;o:glueord;begin lastbadness:=0;r:=getnode(10);
mem[r].hh.b0:=1;mem[r].hh.b1:=0;mem[r+4].int:=0;mem[r+7].hh.rh:=membot;
mem[r+7].hh.lh:=membot;incr(mem[membot].hh.rh);incr(mem[membot].hh.rh);
mem[r+5].hh.rh:=p;w:=0;{661:}d:=0;x:=0;totalstretch[0]:=0;
totalshrink[0]:=0;totalstretch[1]:=0;totalshrink[1]:=0;
totalstretch[2]:=0;totalshrink[2]:=0;totalstretch[3]:=0;
totalshrink[3]:=0{:661};
while p<>-1073741823 do{680:}begin if(p>=himemmin)then confusion(911)
else case mem[p].hh.b0 of 0,1,2,3,15:{681:}begin x:=x+d+mem[p+3].int;
d:=mem[p+2].int;if mem[p].hh.b0>=3 then s:=0 else s:=mem[p+4].int;
if mem[p+1].int+s>w then w:=mem[p+1].int+s;end{:681};10:{1372:}{:1372};
12:{682:}begin x:=x+d;d:=0;g:=mem[p+1].hh.lh;x:=x+mem[g+1].int;
o:=mem[g].hh.b0;totalstretch[o]:=totalstretch[o]+mem[g+2].int;
o:=mem[g].hh.b1;totalshrink[o]:=totalshrink[o]+mem[g+3].int;
if mem[p].hh.b1>=100 then begin g:=mem[p+1].hh.rh;
if mem[g+1].int>w then w:=mem[g+1].int;end;end{:682};
13:begin x:=x+d+mem[p+1].int;d:=0;end;others:end;p:=mem[p].hh.rh;
end{:680};mem[r+1].int:=w;if d>l then begin x:=x+d-l;mem[r+2].int:=l;
end else mem[r+2].int:=d;{683:}if m=1 then h:=x+h;mem[r+3].int:=h;
x:=h-x;if x=0 then begin mem[r+5].hh.b0:=0;mem[r+5].hh.b1:=0;
mem[r+6].gr:=0.0;goto 10;
end else if x>0 then{684:}begin{670:}if totalstretch[3]<>0 then o:=3
else if totalstretch[2]<>0 then o:=2 else if totalstretch[1]<>0 then o:=
1 else o:=0{:670};mem[r+5].hh.b1:=o;mem[r+5].hh.b0:=1;
if totalstretch[o]<>0 then mem[r+6].gr:=x/totalstretch[o]else begin mem[
r+5].hh.b0:=0;mem[r+6].gr:=0.0;end;
if o=0 then if mem[r+5].hh.rh<>-1073741823 then{685:}begin lastbadness:=
badness(x,totalstretch[0]);
if lastbadness>eqtb[28489].int then begin println;
if lastbadness>100 then printnl(900)else printnl(901);print(912);
printint(lastbadness);goto 50;end;end{:685};goto 10;
end{:684}else{687:}begin{676:}if totalshrink[3]<>0 then o:=3 else if
totalshrink[2]<>0 then o:=2 else if totalshrink[1]<>0 then o:=1 else o:=
0{:676};mem[r+5].hh.b1:=o;mem[r+5].hh.b0:=2;
if totalshrink[o]<>0 then mem[r+6].gr:=(-x)/totalshrink[o]else begin mem
[r+5].hh.b0:=0;mem[r+6].gr:=0.0;end;
if(totalshrink[o]<-x)and(o=0)and(mem[r+5].hh.rh<>-1073741823)then begin
lastbadness:=1000000;mem[r+6].gr:=1.0;
{688:}if(-x-totalshrink[0]>eqtb[29047].int)or(eqtb[28489].int<100)then
begin println;printnl(913);printscaled(-x-totalshrink[0]);print(914);
goto 50;end{:688};
end else if o=0 then if mem[r+5].hh.rh<>-1073741823 then{689:}begin
lastbadness:=badness(-x,totalshrink[0]);
if lastbadness>eqtb[28489].int then begin println;printnl(915);
printint(lastbadness);goto 50;end;end{:689};goto 10;end{:687}{:683};
50:{686:}if outputactive then print(903)else begin if packbeginline<>0
then begin print(905);printint(abs(packbeginline));print(906);
end else print(907);printint(line);println;end;begindiagnostic;
showbox(r);enddiagnostic(true){:686};10:vpackage:=r;end;
{:679}{690:}procedure appendtovlist(b:halfword);var d:scaled;p:halfword;
begin if curlist.auxfield.int>-65536000 then begin d:=mem[eqtb[24528].hh
.rh+1].int-curlist.auxfield.int-mem[b+3].int;
if d<eqtb[29040].int then p:=newparamglue(0)else begin p:=newskipparam(1
);mem[tempptr+1].int:=d;end;mem[curlist.tailfield].hh.rh:=p;
curlist.tailfield:=p;end;mem[curlist.tailfield].hh.rh:=b;
curlist.tailfield:=b;curlist.auxfield.int:=mem[b+2].int;end;
{:690}{697:}function newnoad:halfword;var p:halfword;
begin p:=getnode(5);mem[p].hh.b0:=18;mem[p].hh.b1:=0;
mem[p+1].hh:=emptyfield;mem[p+3].hh:=emptyfield;mem[p+2].hh:=emptyfield;
mem[p+4].hh:=emptyfield;newnoad:=p;end;
{:697}{699:}function newstyle(s:smallnumber):halfword;var p:halfword;
begin p:=getnode(3);mem[p].hh.b0:=16;mem[p].hh.b1:=s;mem[p+1].int:=0;
mem[p+2].int:=0;newstyle:=p;end;{:699}{700:}function newchoice:halfword;
var p:halfword;begin p:=getnode(3);mem[p].hh.b0:=17;mem[p].hh.b1:=0;
mem[p+1].hh.lh:=-1073741823;mem[p+1].hh.rh:=-1073741823;
mem[p+2].hh.lh:=-1073741823;mem[p+2].hh.rh:=-1073741823;newchoice:=p;
end;{:700}{704:}procedure showinfo;
begin shownodelist(mem[tempptr].hh.lh);end;
{:704}{715:}function fractionrule(t:scaled):halfword;var p:halfword;
begin p:=newrule;mem[p+3].int:=t;mem[p+2].int:=0;fractionrule:=p;end;
{:715}{716:}function overbar(b:halfword;k,t:scaled):halfword;
var p,q:halfword;begin p:=newkern(k);mem[p].hh.rh:=b;q:=fractionrule(t);
mem[q].hh.rh:=p;p:=newkern(t);mem[p].hh.rh:=q;
overbar:=vpackage(p,0,1,1073741823);end;
{:716}{717:}{720:}function charbox(f:internalfontnumber;
c:quarterword):halfword;var q:fourquarters;hd:eightbits;b,p:halfword;
begin q:=fontinfo[charbase[f]+effectivechar(true,f,c)].qqqq;hd:=q.b1;
b:=newnullbox;
mem[b+1].int:=fontinfo[widthbase[f]+q.b0].int+fontinfo[italicbase[f]+(q.
b2)div 4].int;mem[b+3].int:=fontinfo[heightbase[f]+(hd)div 16].int;
mem[b+2].int:=fontinfo[depthbase[f]+(hd)mod 16].int;p:=getavail;
mem[p].hh.b1:=c;mem[p].hh.b0:=f;mem[b+5].hh.rh:=p;charbox:=b;end;
{:720}{722:}procedure stackintobox(b:halfword;f:internalfontnumber;
c:quarterword);var p:halfword;begin p:=charbox(f,c);
mem[p].hh.rh:=mem[b+5].hh.rh;mem[b+5].hh.rh:=p;
mem[b+3].int:=mem[p+3].int;end;
{:722}{723:}function heightplusdepth(f:internalfontnumber;
c:quarterword):scaled;var q:fourquarters;hd:eightbits;
begin q:=fontinfo[charbase[f]+effectivechar(true,f,c)].qqqq;hd:=q.b1;
heightplusdepth:=fontinfo[heightbase[f]+(hd)div 16].int+fontinfo[
depthbase[f]+(hd)mod 16].int;end;{:723}function vardelimiter(d:halfword;
s:smallnumber;v:scaled):halfword;label 40,22;var b:halfword;
f,g:internalfontnumber;c,x,y:quarterword;m,n:integer;u:scaled;w:scaled;
q:fourquarters;hd:eightbits;r:fourquarters;z:smallnumber;
largeattempt:boolean;begin f:=0;w:=0;largeattempt:=false;
z:=mem[d].qqqq.b0;x:=mem[d].qqqq.b1;
while true do begin{718:}if(z<>0)or(x<>0)then begin z:=z+s+16;
repeat z:=z-16;g:=eqtb[25583+z].hh.rh;if g<>0 then{719:}begin y:=x;
if(y>=fontbc[g])and(y<=fontec[g])then begin 22:q:=fontinfo[charbase[g]+y
].qqqq;if(q.b0>0)then begin if((q.b2)mod 4)=3 then begin f:=g;c:=y;
goto 40;end;hd:=q.b1;
u:=fontinfo[heightbase[g]+(hd)div 16].int+fontinfo[depthbase[g]+(hd)mod
16].int;if u>w then begin f:=g;c:=y;w:=u;if u>=v then goto 40;end;
if((q.b2)mod 4)=2 then begin y:=q.b3;goto 22;end;end;end;end{:719};
until z<16;end{:718};if largeattempt then goto 40;largeattempt:=true;
z:=mem[d].qqqq.b2;x:=mem[d].qqqq.b3;end;
40:if f<>0 then{721:}if((q.b2)mod 4)=3 then{724:}begin b:=newnullbox;
mem[b].hh.b0:=1;r:=fontinfo[extenbase[f]+q.b3].qqqq;{725:}c:=r.b3;
u:=heightplusdepth(f,c);w:=0;
q:=fontinfo[charbase[f]+effectivechar(true,f,c)].qqqq;
mem[b+1].int:=fontinfo[widthbase[f]+q.b0].int+fontinfo[italicbase[f]+(q.
b2)div 4].int;c:=r.b2;if c<>0 then w:=w+heightplusdepth(f,c);c:=r.b1;
if c<>0 then w:=w+heightplusdepth(f,c);c:=r.b0;
if c<>0 then w:=w+heightplusdepth(f,c);n:=0;
if u>0 then while w<v do begin w:=w+u;incr(n);if r.b1<>0 then w:=w+u;
end{:725};c:=r.b2;if c<>0 then stackintobox(b,f,c);c:=r.b3;
for m:=1 to n do stackintobox(b,f,c);c:=r.b1;
if c<>0 then begin stackintobox(b,f,c);c:=r.b3;
for m:=1 to n do stackintobox(b,f,c);end;c:=r.b0;
if c<>0 then stackintobox(b,f,c);mem[b+2].int:=w-mem[b+3].int;
end{:724}else b:=charbox(f,c){:721}else begin b:=newnullbox;
mem[b+1].int:=eqtb[29049].int;end;
mem[b+4].int:=half(mem[b+3].int-mem[b+2].int)-fontinfo[22+parambase[eqtb
[25585+s].hh.rh]].int;vardelimiter:=b;end;
{:717}{726:}function rebox(b:halfword;w:scaled):halfword;var p:halfword;
f:internalfontnumber;v:scaled;
begin if(mem[b+1].int<>w)and(mem[b+5].hh.rh<>-1073741823)then begin if
mem[b].hh.b0<>0 then b:=hpack(b,0,1);p:=mem[b+5].hh.rh;
if(p>=himemmin)then if fontdir[mem[p].hh.b0]<>0 then begin if mem[mem[p]
.hh.rh].hh.rh=-1073741823 then begin f:=mem[p].hh.b0;
v:=fontinfo[widthbase[f]+fontinfo[charbase[f]+mem[p].hh.b1].qqqq.b0].int
;
if v<>mem[b+1].int then mem[mem[p].hh.rh].hh.rh:=newkern(mem[b+1].int-v)
;end end else if mem[p].hh.rh=-1073741823 then begin f:=mem[p].hh.b0;
v:=fontinfo[widthbase[f]+fontinfo[charbase[f]+mem[p].hh.b1].qqqq.b0].int
;if v<>mem[b+1].int then mem[p].hh.rh:=newkern(mem[b+1].int-v);end;
deleteglueref(mem[b+7].hh.rh);deleteglueref(mem[b+7].hh.lh);
freenode(b,10);b:=newglue(membot+12);mem[b].hh.rh:=p;
while mem[p].hh.rh<>-1073741823 do p:=mem[p].hh.rh;
mem[p].hh.rh:=newglue(membot+12);rebox:=hpack(b,w,0);
end else begin mem[b+1].int:=w;rebox:=b;end;end;
{:726}{727:}function mathglue(g:halfword;m:scaled):halfword;
var p:halfword;n:integer;f:scaled;begin n:=xovern(m,65536);
f:=texremainder;if f<0 then begin decr(n);f:=f+65536;end;p:=getnode(4);
mem[p+1].int:=multandadd(n,mem[g+1].int,xnoverd(mem[g+1].int,f,65536),
1073741823);mem[p].hh.b0:=mem[g].hh.b0;
if mem[p].hh.b0=0 then mem[p+2].int:=multandadd(n,mem[g+2].int,xnoverd(
mem[g+2].int,f,65536),1073741823)else mem[p+2].int:=mem[g+2].int;
mem[p].hh.b1:=mem[g].hh.b1;
if mem[p].hh.b1=0 then mem[p+3].int:=multandadd(n,mem[g+3].int,xnoverd(
mem[g+3].int,f,65536),1073741823)else mem[p+3].int:=mem[g+3].int;
mathglue:=p;end;{:727}{728:}procedure mathkern(p:halfword;m:scaled);
var n:integer;f:scaled;
begin if mem[p].hh.b1=99 then begin n:=xovern(m,65536);f:=texremainder;
if f<0 then begin decr(n);f:=f+65536;end;
mem[p+1].int:=multandadd(n,mem[p+1].int,xnoverd(mem[p+1].int,f,65536),
1073741823);mem[p].hh.b1:=1;end;end;{:728}{729:}procedure flushmath;
begin flushnodelist(mem[curlist.headfield].hh.rh);
flushnodelist(curlist.auxfield.int);
mem[curlist.headfield].hh.rh:=-1073741823;
curlist.tailfield:=curlist.headfield;curlist.auxfield.int:=-1073741823;
end;{:729}{731:}procedure mlisttohlist;forward;
function shiftsubexpbox(q:halfword):halfword;var d:halfword;
begin if curlist.dirfield=3 then d:=eqtb[29059].int else d:=eqtb[29060].
int;
if curstyle<4 then d:=xnoverd(d,eqtb[28519].int,1000)else if curstyle<6
then d:=xnoverd(d,eqtb[28520].int,1000)else d:=xnoverd(d,eqtb[28521].int
,1000);mem[mem[q].hh.lh+4].int:=mem[mem[q].hh.lh+4].int-d;
mem[q].hh.rh:=2;shiftsubexpbox:=mem[q].hh.lh;end;
function cleanbox(p:halfword;s:smallnumber;jc:halfword):halfword;
label 40;var q:halfword;savestyle:smallnumber;x:halfword;r:halfword;
begin case mem[p].hh.rh of 1:begin curmlist:=newnoad;
mem[curmlist+1]:=mem[p];end;6:begin curmlist:=newnoad;
mem[curmlist+1]:=mem[p];mem[curmlist+4].hh.lh:=jc;end;
2:begin q:=mem[p].hh.lh;goto 40;end;3:begin q:=shiftsubexpbox(p);
goto 40;end;4:curmlist:=mem[p].hh.lh;others:begin q:=newnullbox;goto 40;
end end;savestyle:=curstyle;curstyle:=s;mlistpenalties:=false;
mlisttohlist;q:=mem[memtop-3].hh.rh;curstyle:=savestyle;
{714:}begin if curstyle<4 then cursize:=0 else cursize:=16*((curstyle-2)
div 2);
curmu:=xovern(fontinfo[6+parambase[eqtb[25585+cursize].hh.rh]].int,18);
end{:714};
40:if(q>=himemmin)or(q=-1073741823)then x:=hpack(q,0,1)else if(mem[q].hh
.rh=-1073741823)and(mem[q].hh.b0<=2)and(mem[q+4].int=0)then x:=q else x
:=hpack(q,0,1);{732:}q:=mem[x+5].hh.rh;
if(q>=himemmin)then begin if fontdir[mem[q].hh.b0]<>0 then q:=mem[q].hh.
rh;r:=mem[q].hh.rh;
if r<>-1073741823 then if mem[r].hh.rh=-1073741823 then if not(r>=
himemmin)then if mem[r].hh.b0=13 then begin freenode(r,4);
mem[q].hh.rh:=-1073741823;end;end{:732};cleanbox:=x;end;
{:731}{733:}procedure fetch(a:halfword);begin curc:=mem[a].hh.b1;
curf:=eqtb[25583+mem[a].hh.b0+cursize].hh.rh;
if curf=0 then{734:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(344);
end;printsize(cursize);printchar(32);printint(mem[a].hh.b0);print(940);
print(curc);printchar(41);begin helpptr:=4;helpline[3]:=941;
helpline[2]:=942;helpline[1]:=943;helpline[0]:=944;end;error;
curi:=nullcharacter;mem[a].hh.rh:=0;
end{:734}else begin if fontdir[curf]<>0 then curc:=getjfmpos(mem[a+3].hh
.lh,curf);
if(curc>=fontbc[curf])and(curc<=fontec[curf])then curi:=fontinfo[
charbase[curf]+curc].qqqq else curi:=nullcharacter;
if not((curi.b0>0))then begin charwarning(curf,curc);mem[a].hh.rh:=0;
end;end;end;{:733}{737:}{745:}procedure makeover(q:halfword);
begin mem[q+1].hh.lh:=overbar(cleanbox(q+1,2*(curstyle div 2)+1,mem[q+4]
.hh.lh),3*fontinfo[8+parambase[eqtb[25586+cursize].hh.rh]].int,fontinfo[
8+parambase[eqtb[25586+cursize].hh.rh]].int);mem[q+1].hh.rh:=2;end;
{:745}{746:}procedure makeunder(q:halfword);var p,x,y:halfword;
delta:scaled;begin x:=cleanbox(q+1,curstyle,mem[q+4].hh.lh);
p:=newkern(3*fontinfo[8+parambase[eqtb[25586+cursize].hh.rh]].int);
mem[x].hh.rh:=p;
mem[p].hh.rh:=fractionrule(fontinfo[8+parambase[eqtb[25586+cursize].hh.
rh]].int);y:=vpackage(x,0,1,1073741823);
delta:=mem[y+3].int+mem[y+2].int+fontinfo[8+parambase[eqtb[25586+cursize
].hh.rh]].int;mem[y+3].int:=mem[x+3].int;
mem[y+2].int:=delta-mem[y+3].int;mem[q+1].hh.lh:=y;mem[q+1].hh.rh:=2;
end;{:746}{747:}procedure makevcenter(q:halfword);var v:halfword;
delta:scaled;begin v:=mem[q+1].hh.lh;
if mem[v].hh.b0=2 then begin if mem[mem[v+5].hh.rh].hh.b0<>1 then
confusion(946)end else begin if mem[v].hh.b0<>1 then confusion(577)end;
delta:=mem[v+3].int+mem[v+2].int;
mem[v+3].int:=fontinfo[22+parambase[eqtb[25585+cursize].hh.rh]].int+half
(delta);mem[v+2].int:=delta-mem[v+3].int;end;
{:747}{748:}procedure makeradical(q:halfword);var x,y:halfword;
delta,clr:scaled;
begin x:=cleanbox(q+1,2*(curstyle div 2)+1,mem[q+4].hh.lh);
if curstyle<2 then clr:=fontinfo[8+parambase[eqtb[25586+cursize].hh.rh]]
.int+(abs(fontinfo[5+parambase[eqtb[25585+cursize].hh.rh]].int)div 4)
else begin clr:=fontinfo[8+parambase[eqtb[25586+cursize].hh.rh]].int;
clr:=clr+(abs(clr)div 4);end;
y:=vardelimiter(q+5,cursize,mem[x+3].int+mem[x+2].int+clr+fontinfo[8+
parambase[eqtb[25586+cursize].hh.rh]].int);
delta:=mem[y+2].int-(mem[x+3].int+mem[x+2].int+clr);
if delta>0 then clr:=clr+half(delta);mem[y+4].int:=-(mem[x+3].int+clr);
mem[y].hh.rh:=overbar(x,clr,mem[y+3].int);mem[q+1].hh.lh:=hpack(y,0,1);
mem[q+1].hh.rh:=2;end;{:748}{749:}procedure makemathaccent(q:halfword);
label 30,31;var p,x,y:halfword;a:integer;c:quarterword;
f:internalfontnumber;i:fourquarters;s:scaled;h:scaled;delta:scaled;
w:scaled;begin fetch(q+5);if(curi.b0>0)then begin i:=curi;c:=curc;
f:=curf;{752:}s:=0;if mem[q+1].hh.rh=1 then begin fetch(q+1);
if((curi.b2)mod 4)=1 then begin a:=ligkernbase[curf]+curi.b3;
curi:=fontinfo[a].qqqq;
if curi.b0>128 then begin a:=ligkernbase[curf]+256*curi.b2+curi.b3
+32768-256*(128);curi:=fontinfo[a].qqqq;end;
while true do begin if curi.b1=skewchar[curf]then begin if curi.b2>=128
then if curi.b0<=128 then s:=fontinfo[kernbase[curf]+256*curi.b2+curi.b3
].int;goto 31;end;if curi.b0>=128 then goto 31;a:=a+curi.b0+1;
curi:=fontinfo[a].qqqq;end;end;end;31:{:752};
x:=cleanbox(q+1,2*(curstyle div 2)+1,mem[q+4].hh.lh);w:=mem[x+1].int;
h:=mem[x+3].int;
{751:}while true do begin if((i.b2)mod 4)<>2 then goto 30;y:=i.b3;
i:=fontinfo[charbase[f]+y].qqqq;if not(i.b0>0)then goto 30;
if fontinfo[widthbase[f]+i.b0].int>w then goto 30;c:=y;end;30:{:751};
if h<fontinfo[5+parambase[f]].int then delta:=h else delta:=fontinfo[5+
parambase[f]].int;
if(mem[q+2].hh.rh<>0)or(mem[q+3].hh.rh<>0)then if mem[q+1].hh.rh=1 then
{753:}begin flushnodelist(x);x:=newnoad;mem[x+1]:=mem[q+1];
mem[x+2]:=mem[q+2];mem[x+3]:=mem[q+3];mem[q+2].hh:=emptyfield;
mem[q+3].hh:=emptyfield;mem[q+1].hh.rh:=4;mem[q+1].hh.lh:=x;
x:=cleanbox(q+1,curstyle,mem[q+4].hh.lh);delta:=delta+mem[x+3].int-h;
h:=mem[x+3].int;end{:753};y:=charbox(f,c);
mem[y+4].int:=s+half(w-mem[y+1].int);mem[y+1].int:=0;p:=newkern(-delta);
mem[p].hh.rh:=x;mem[y].hh.rh:=p;y:=vpackage(y,0,1,1073741823);
mem[y+1].int:=mem[x+1].int;
if mem[y+3].int<h then{750:}begin p:=newkern(h-mem[y+3].int);
mem[p].hh.rh:=mem[y+5].hh.rh;mem[y+5].hh.rh:=p;mem[y+3].int:=h;
end{:750};mem[q+1].hh.lh:=y;mem[q+1].hh.rh:=2;end;end;
{:749}{754:}procedure makefraction(q:halfword);var p,v,x,y,z:halfword;
delta,delta1,delta2,shiftup,shiftdown,clr:scaled;
begin if mem[q+1].int=1073741824 then mem[q+1].int:=fontinfo[8+parambase
[eqtb[25586+cursize].hh.rh]].int;
{755:}x:=cleanbox(q+2,curstyle+2-2*(curstyle div 6),mem[q+4].hh.lh);
z:=cleanbox(q+3,2*(curstyle div 2)+3-2*(curstyle div 6),mem[q+4].hh.lh);
if mem[x+1].int<mem[z+1].int then x:=rebox(x,mem[z+1].int)else z:=rebox(
z,mem[x+1].int);
if curstyle<2 then begin shiftup:=fontinfo[8+parambase[eqtb[25585+
cursize].hh.rh]].int;
shiftdown:=fontinfo[11+parambase[eqtb[25585+cursize].hh.rh]].int;
end else begin shiftdown:=fontinfo[12+parambase[eqtb[25585+cursize].hh.
rh]].int;
if mem[q+1].int<>0 then shiftup:=fontinfo[9+parambase[eqtb[25585+cursize
].hh.rh]].int else shiftup:=fontinfo[10+parambase[eqtb[25585+cursize].hh
.rh]].int;end{:755};
if mem[q+1].int=0 then{756:}begin if curstyle<2 then clr:=7*fontinfo[8+
parambase[eqtb[25586+cursize].hh.rh]].int else clr:=3*fontinfo[8+
parambase[eqtb[25586+cursize].hh.rh]].int;
delta:=half(clr-((shiftup-mem[x+2].int)-(mem[z+3].int-shiftdown)));
if delta>0 then begin shiftup:=shiftup+delta;shiftdown:=shiftdown+delta;
end;
end{:756}else{757:}begin if curstyle<2 then clr:=3*mem[q+1].int else clr
:=mem[q+1].int;delta:=half(mem[q+1].int);
delta1:=clr-((shiftup-mem[x+2].int)-(fontinfo[22+parambase[eqtb[25585+
cursize].hh.rh]].int+delta));
delta2:=clr-((fontinfo[22+parambase[eqtb[25585+cursize].hh.rh]].int-
delta)-(mem[z+3].int-shiftdown));
if delta1>0 then shiftup:=shiftup+delta1;
if delta2>0 then shiftdown:=shiftdown+delta2;end{:757};
{758:}v:=newnullbox;mem[v].hh.b0:=1;mem[v+3].int:=shiftup+mem[x+3].int;
mem[v+2].int:=mem[z+2].int+shiftdown;mem[v+1].int:=mem[x+1].int;
if mem[q+1].int=0 then begin p:=newkern((shiftup-mem[x+2].int)-(mem[z+3]
.int-shiftdown));mem[p].hh.rh:=z;
end else begin y:=fractionrule(mem[q+1].int);
p:=newkern((fontinfo[22+parambase[eqtb[25585+cursize].hh.rh]].int-delta)
-(mem[z+3].int-shiftdown));mem[y].hh.rh:=p;mem[p].hh.rh:=z;
p:=newkern((shiftup-mem[x+2].int)-(fontinfo[22+parambase[eqtb[25585+
cursize].hh.rh]].int+delta));mem[p].hh.rh:=y;end;mem[x].hh.rh:=p;
mem[v+5].hh.rh:=x{:758};
{759:}if curstyle<2 then delta:=fontinfo[20+parambase[eqtb[25585+cursize
].hh.rh]].int else delta:=fontinfo[21+parambase[eqtb[25585+cursize].hh.
rh]].int;x:=vardelimiter(q+5,cursize,delta);mem[x].hh.rh:=v;
z:=vardelimiter(q+4,cursize,delta);mem[v].hh.rh:=z;
mem[q+1].int:=hpack(x,0,1){:759};end;
{:754}{760:}function makeop(q:halfword):scaled;var delta:scaled;
p,v,x,y,z:halfword;c:quarterword;i:fourquarters;
shiftup,shiftdown:scaled;
begin if(mem[q].hh.b1=0)and(curstyle<2)then mem[q].hh.b1:=1;
if mem[q+1].hh.rh=1 then begin fetch(q+1);
if(curstyle<2)and(((curi.b2)mod 4)=2)then begin c:=curi.b3;
i:=fontinfo[charbase[curf]+c].qqqq;if(i.b0>0)then begin curc:=c;curi:=i;
mem[q+1].hh.b1:=c;end;end;
delta:=fontinfo[italicbase[curf]+(curi.b2)div 4].int;
x:=cleanbox(q+1,curstyle,mem[q+4].hh.lh);
if(mem[q+3].hh.rh<>0)and(mem[q].hh.b1<>1)then mem[x+1].int:=mem[x+1].int
-delta;
mem[x+4].int:=half(mem[x+3].int-mem[x+2].int)-fontinfo[22+parambase[eqtb
[25585+cursize].hh.rh]].int;mem[q+1].hh.rh:=2;mem[q+1].hh.lh:=x;
end else delta:=0;
if mem[q].hh.b1=1 then{761:}begin x:=cleanbox(q+2,2*(curstyle div 4)+4+(
curstyle mod 2),mem[q+4].hh.lh);
y:=cleanbox(q+1,curstyle,mem[q+4].hh.lh);
z:=cleanbox(q+3,2*(curstyle div 4)+5,mem[q+4].hh.lh);v:=newnullbox;
mem[v].hh.b0:=1;mem[v+1].int:=mem[y+1].int;
if mem[x+1].int>mem[v+1].int then mem[v+1].int:=mem[x+1].int;
if mem[z+1].int>mem[v+1].int then mem[v+1].int:=mem[z+1].int;
x:=rebox(x,mem[v+1].int);y:=rebox(y,mem[v+1].int);
z:=rebox(z,mem[v+1].int);mem[x+4].int:=half(delta);
mem[z+4].int:=-mem[x+4].int;mem[v+3].int:=mem[y+3].int;
mem[v+2].int:=mem[y+2].int;
{762:}if mem[q+2].hh.rh=0 then begin deleteglueref(mem[x+7].hh.rh);
deleteglueref(mem[x+7].hh.lh);freenode(x,10);mem[v+5].hh.rh:=y;
end else begin shiftup:=fontinfo[11+parambase[eqtb[25586+cursize].hh.rh]
].int-mem[x+2].int;
if shiftup<fontinfo[9+parambase[eqtb[25586+cursize].hh.rh]].int then
shiftup:=fontinfo[9+parambase[eqtb[25586+cursize].hh.rh]].int;
p:=newkern(shiftup);mem[p].hh.rh:=y;mem[x].hh.rh:=p;
p:=newkern(fontinfo[13+parambase[eqtb[25586+cursize].hh.rh]].int);
mem[p].hh.rh:=x;mem[v+5].hh.rh:=p;
mem[v+3].int:=mem[v+3].int+fontinfo[13+parambase[eqtb[25586+cursize].hh.
rh]].int+mem[x+3].int+mem[x+2].int+shiftup;end;
if mem[q+3].hh.rh=0 then begin deleteglueref(mem[z+7].hh.rh);
deleteglueref(mem[z+7].hh.lh);
freenode(z,10)end else begin shiftdown:=fontinfo[12+parambase[eqtb[
25586+cursize].hh.rh]].int-mem[z+3].int;
if shiftdown<fontinfo[10+parambase[eqtb[25586+cursize].hh.rh]].int then
shiftdown:=fontinfo[10+parambase[eqtb[25586+cursize].hh.rh]].int;
p:=newkern(shiftdown);mem[y].hh.rh:=p;mem[p].hh.rh:=z;
p:=newkern(fontinfo[13+parambase[eqtb[25586+cursize].hh.rh]].int);
mem[z].hh.rh:=p;
mem[v+2].int:=mem[v+2].int+fontinfo[13+parambase[eqtb[25586+cursize].hh.
rh]].int+mem[z+3].int+mem[z+2].int+shiftdown;end{:762};mem[q+1].int:=v;
end{:761};makeop:=delta;end;{:760}{763:}procedure makeord(q:halfword);
label 20,10;var a:integer;gp,gq,p,r:halfword;rr:halfword;
begin 20:if(mem[q+3].hh.rh=0)and(mem[q+2].hh.rh=0)and((mem[q+1].hh.rh=1)
or(mem[q+1].hh.rh=6))then begin p:=mem[q].hh.rh;
if p<>-1073741823 then if(mem[p].hh.b0>=18)and(mem[p].hh.b0<=24)then if
mem[p+1].hh.b0=mem[q+1].hh.b0 then if mem[p+1].hh.rh=1 then begin mem[q
+1].hh.rh:=5;fetch(q+1);
if((curi.b2)mod 4)=1 then begin a:=ligkernbase[curf]+curi.b3;
curc:=mem[p+1].hh.b1;curi:=fontinfo[a].qqqq;
if curi.b0>128 then begin a:=ligkernbase[curf]+256*curi.b2+curi.b3
+32768-256*(128);curi:=fontinfo[a].qqqq;end;
while true do begin{764:}if curi.b1=curc then if curi.b0<=128 then if
curi.b2>=128 then begin p:=newkern(fontinfo[kernbase[curf]+256*curi.b2+
curi.b3].int);mem[p].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=p;goto 10;
end else begin begin if interrupt<>0 then pauseforinstructions;end;
case curi.b2 of 1,5:mem[q+1].hh.b1:=curi.b3;2,6:mem[p+1].hh.b1:=curi.b3;
3,7,11:begin r:=newnoad;mem[r+1].hh.b1:=curi.b3;
mem[r+1].hh.b0:=mem[q+1].hh.b0;mem[q].hh.rh:=r;mem[r].hh.rh:=p;
if curi.b2<11 then mem[r+1].hh.rh:=1 else mem[r+1].hh.rh:=5;end;
others:begin mem[q].hh.rh:=mem[p].hh.rh;mem[q+1].hh.b1:=curi.b3;
mem[q+3]:=mem[p+3];mem[q+2]:=mem[p+2];freenode(p,5);end end;
if curi.b2>3 then goto 10;mem[q+1].hh.rh:=1;goto 20;end{:764};
if curi.b0>=128 then goto 10;a:=a+curi.b0+1;curi:=fontinfo[a].qqqq;end;
end;end else if mem[p+1].hh.rh=6 then begin mem[q+1].hh.rh:=7;
fetch(p+1);a:=curc;fetch(q+1);if((curi.b2)mod 4)=1 then begin curc:=a;
a:=ligkernbase[curf]+curi.b3;repeat curi:=fontinfo[a].qqqq;
if curi.b1=curc then if curi.b2<128 then begin gp:=fontglue[curf];
rr:=curi.b3;
if gp<>-1073741823 then begin while((mem[gp].hh.b0<>rr)and(mem[gp].hh.rh
<>-1073741823))do begin gp:=mem[gp].hh.rh;end;gq:=mem[gp+1].hh.lh;
end else begin gp:=getnode(2);fontglue[curf]:=gp;gq:=-1073741823;end;
if gq=-1073741823 then begin mem[gp].hh.b0:=rr;gq:=newspec(membot);
mem[gp+1].hh.lh:=gq;a:=extenbase[curf]+(rr)*3;
mem[gq+1].int:=fontinfo[a].int;mem[gq+2].int:=fontinfo[a+1].int;
mem[gq+3].int:=fontinfo[a+2].int;incr(mem[gq].hh.rh);
mem[gp].hh.rh:=getnode(2);gp:=mem[gp].hh.rh;
mem[gp+1].hh.lh:=-1073741823;mem[gp].hh.rh:=-1073741823;end;
p:=newglue(gq);mem[p].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=p;goto 10;
end else begin p:=newkern(fontinfo[kernbase[curf]+256*curi.b2+curi.b3].
int);mem[p].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=p;goto 10;end;incr(a);
until curi.b0>=128;end;end;end;10:end;
{:763}{767:}procedure makescripts(q:halfword;delta:scaled);
var p,x,y,z:halfword;shiftup,shiftdown,clr:scaled;t:smallnumber;
begin p:=mem[q+1].int;if(p>=himemmin)then begin shiftup:=0;shiftdown:=0;
end else begin z:=hpack(p,0,1);if curstyle<4 then t:=16 else t:=32;
shiftup:=mem[z+3].int-fontinfo[18+parambase[eqtb[25585+t].hh.rh]].int;
shiftdown:=mem[z+2].int+fontinfo[19+parambase[eqtb[25585+t].hh.rh]].int;
deleteglueref(mem[z+7].hh.rh);deleteglueref(mem[z+7].hh.lh);
freenode(z,10);end;
if mem[q+2].hh.rh=0 then{768:}begin x:=cleanbox(q+3,2*(curstyle div 4)+5
,mem[q+4].hh.lh);mem[x+1].int:=mem[x+1].int+eqtb[29050].int;
if shiftdown<fontinfo[16+parambase[eqtb[25585+cursize].hh.rh]].int then
shiftdown:=fontinfo[16+parambase[eqtb[25585+cursize].hh.rh]].int;
clr:=mem[x+3].int-(abs(fontinfo[5+parambase[eqtb[25585+cursize].hh.rh]].
int*4)div 5);if shiftdown<clr then shiftdown:=clr;
mem[x+4].int:=shiftdown;
end{:768}else begin{769:}begin x:=cleanbox(q+2,2*(curstyle div 4)+4+(
curstyle mod 2),mem[q+4].hh.lh);
mem[x+1].int:=mem[x+1].int+eqtb[29050].int;
if odd(curstyle)then clr:=fontinfo[15+parambase[eqtb[25585+cursize].hh.
rh]].int else if curstyle<2 then clr:=fontinfo[13+parambase[eqtb[25585+
cursize].hh.rh]].int else clr:=fontinfo[14+parambase[eqtb[25585+cursize]
.hh.rh]].int;if shiftup<clr then shiftup:=clr;
clr:=mem[x+2].int+(abs(fontinfo[5+parambase[eqtb[25585+cursize].hh.rh]].
int)div 4);if shiftup<clr then shiftup:=clr;end{:769};
if mem[q+3].hh.rh=0 then mem[x+4].int:=-shiftup else{770:}begin y:=
cleanbox(q+3,2*(curstyle div 4)+5,mem[q+4].hh.lh);
mem[y+1].int:=mem[y+1].int+eqtb[29050].int;
if shiftdown<fontinfo[17+parambase[eqtb[25585+cursize].hh.rh]].int then
shiftdown:=fontinfo[17+parambase[eqtb[25585+cursize].hh.rh]].int;
clr:=4*fontinfo[8+parambase[eqtb[25586+cursize].hh.rh]].int-((shiftup-
mem[x+2].int)-(mem[y+3].int-shiftdown));
if clr>0 then begin shiftdown:=shiftdown+clr;
clr:=(abs(fontinfo[5+parambase[eqtb[25585+cursize].hh.rh]].int*4)div 5)-
(shiftup-mem[x+2].int);if clr>0 then begin shiftup:=shiftup+clr;
shiftdown:=shiftdown-clr;end;end;mem[x+4].int:=delta;
p:=newkern((shiftup-mem[x+2].int)-(mem[y+3].int-shiftdown));
mem[x].hh.rh:=p;mem[p].hh.rh:=y;x:=vpackage(x,0,1,1073741823);
mem[x+4].int:=shiftdown;end{:770};end;
if mem[q+1].int=-1073741823 then mem[q+1].int:=x else begin p:=mem[q+1].
int;while mem[p].hh.rh<>-1073741823 do p:=mem[p].hh.rh;mem[p].hh.rh:=x;
end;end;{:767}{773:}function makeleftright(q:halfword;style:smallnumber;
maxd,maxh:scaled):smallnumber;var delta,delta1,delta2:scaled;
begin if style<4 then cursize:=0 else cursize:=16*((style-2)div 2);
delta2:=maxd+fontinfo[22+parambase[eqtb[25585+cursize].hh.rh]].int;
delta1:=maxh+maxd-delta2;if delta2>delta1 then delta1:=delta2;
delta:=(delta1 div 500)*eqtb[28480].int;
delta2:=delta1+delta1-eqtb[29048].int;
if delta<delta2 then delta:=delta2;
mem[q+1].int:=vardelimiter(q+1,cursize,delta);
makeleftright:=mem[q].hh.b0-(10);end;{:773}procedure mlisttohlist;
label 21,82,80,81,83,30;var mlist:halfword;penalties:boolean;
style:smallnumber;u:halfword;savestyle:smallnumber;q:halfword;
r:halfword;rtype:smallnumber;t:smallnumber;p,x,y,z:halfword;pen:integer;
s:smallnumber;maxh,maxd:scaled;delta:scaled;begin mlist:=curmlist;
penalties:=mlistpenalties;style:=curstyle;q:=mlist;r:=-1073741823;
rtype:=19;maxh:=0;maxd:=0;
{714:}begin if curstyle<4 then cursize:=0 else cursize:=16*((curstyle-2)
div 2);
curmu:=xovern(fontinfo[6+parambase[eqtb[25585+cursize].hh.rh]].int,18);
end{:714};while q<>-1073741823 do{738:}begin{739:}21:delta:=0;
case mem[q].hh.b0 of 20:case rtype of 20,19,21,22,24,32:begin mem[q].hh.
b0:=18;goto 21;end;others:end;
21,23,24,33:begin{740:}if rtype=20 then mem[r].hh.b0:=18{:740};
if mem[q].hh.b0=33 then goto 80;end;{744:}32:goto 80;
27:begin makefraction(q);goto 82;end;19:begin delta:=makeop(q);
if mem[q].hh.b1=1 then goto 82;end;18:makeord(q);22,25:;
26:makeradical(q);29:makeover(q);28:makeunder(q);30:makemathaccent(q);
31:makevcenter(q);{:744}{741:}16:begin curstyle:=mem[q].hh.b1;
{714:}begin if curstyle<4 then cursize:=0 else cursize:=16*((curstyle-2)
div 2);
curmu:=xovern(fontinfo[6+parambase[eqtb[25585+cursize].hh.rh]].int,18);
end{:714};goto 81;end;
17:{742:}begin case curstyle div 2 of 0:begin p:=mem[q+1].hh.lh;
mem[q+1].hh.lh:=-1073741823;end;1:begin p:=mem[q+1].hh.rh;
mem[q+1].hh.rh:=-1073741823;end;2:begin p:=mem[q+2].hh.lh;
mem[q+2].hh.lh:=-1073741823;end;3:begin p:=mem[q+2].hh.rh;
mem[q+2].hh.rh:=-1073741823;end;end;flushnodelist(mem[q+1].hh.lh);
flushnodelist(mem[q+1].hh.rh);flushnodelist(mem[q+2].hh.lh);
flushnodelist(mem[q+2].hh.rh);mem[q].hh.b0:=16;mem[q].hh.b1:=curstyle;
mem[q+1].int:=0;mem[q+2].int:=0;
if p<>-1073741823 then begin z:=mem[q].hh.rh;mem[q].hh.rh:=p;
while mem[p].hh.rh<>-1073741823 do p:=mem[p].hh.rh;mem[p].hh.rh:=z;end;
goto 81;end{:742};4,6,7,10,14,9:goto 81;
3:begin if mem[q+3].int>maxh then maxh:=mem[q+3].int;
if mem[q+2].int>maxd then maxd:=mem[q+2].int;goto 81;end;
12:begin{743:}if mem[q].hh.b1=99 then begin x:=mem[q+1].hh.lh;
y:=mathglue(x,curmu);deleteglueref(x);mem[q+1].hh.lh:=y;mem[q].hh.b1:=0;
end else if(cursize<>0)and(mem[q].hh.b1=98)then begin p:=mem[q].hh.rh;
if p<>-1073741823 then if(mem[p].hh.b0=12)or(mem[p].hh.b0=13)then begin
mem[q].hh.rh:=mem[p].hh.rh;mem[p].hh.rh:=-1073741823;flushnodelist(p);
end;end{:743};goto 81;end;13:begin mathkern(q,curmu);goto 81;end;
5:goto 81;{:741}others:confusion(945)end;
{765:}case mem[q+1].hh.rh of 1,5,6,7:{766:}begin fetch(q+1);
if(curi.b0>0)then begin delta:=fontinfo[italicbase[curf]+(curi.b2)div 4]
.int;p:=newcharacter(curf,curc);u:=p;
if fontdir[curf]<>0 then begin mem[u].hh.rh:=getavail;u:=mem[u].hh.rh;
mem[u].hh.lh:=mem[q+4].hh.lh;end;
if((mem[q+1].hh.rh=5)or(mem[q+1].hh.rh=7))and(fontinfo[2+parambase[curf]
].int<>0)then delta:=0;
if(mem[q+3].hh.rh=0)and(delta<>0)then begin mem[u].hh.rh:=newkern(delta)
;delta:=0;end;end else p:=-1073741823;end{:766};0:p:=-1073741823;
2:p:=mem[q+1].hh.lh;3:p:=shiftsubexpbox(q+1);
4:begin curmlist:=mem[q+1].hh.lh;savestyle:=curstyle;
mlistpenalties:=false;mlisttohlist;curstyle:=savestyle;
{714:}begin if curstyle<4 then cursize:=0 else cursize:=16*((curstyle-2)
div 2);
curmu:=xovern(fontinfo[6+parambase[eqtb[25585+cursize].hh.rh]].int,18);
end{:714};p:=hpack(mem[memtop-3].hh.rh,0,1);end;
others:confusion(947)end;mem[q+1].int:=p;
if(mem[q+3].hh.rh=0)and(mem[q+2].hh.rh=0)then goto 82;
makescripts(q,delta){:765}{:739};82:z:=hpack(mem[q+1].int,0,1);
if mem[z+3].int>maxh then maxh:=mem[z+3].int;
if mem[z+2].int>maxd then maxd:=mem[z+2].int;
deleteglueref(mem[z+7].hh.rh);deleteglueref(mem[z+7].hh.lh);
freenode(z,10);80:r:=q;rtype:=mem[r].hh.b0;81:q:=mem[q].hh.rh;end{:738};
{740:}if rtype=20 then mem[r].hh.b0:=18{:740};{771:}p:=memtop-3;
mem[p].hh.rh:=-1073741823;q:=mlist;rtype:=0;curstyle:=style;
{714:}begin if curstyle<4 then cursize:=0 else cursize:=16*((curstyle-2)
div 2);
curmu:=xovern(fontinfo[6+parambase[eqtb[25585+cursize].hh.rh]].int,18);
end{:714};while q<>-1073741823 do begin{772:}t:=18;s:=5;pen:=10000;
case mem[q].hh.b0 of 19,22,23,24,25:t:=mem[q].hh.b0;20:begin t:=20;
pen:=eqtb[28471].int;end;21:begin t:=21;pen:=eqtb[28472].int;end;
18,31,29,28:;26:s:=6;30:s:=6;27:begin t:=25;s:=6;end;
32,33:t:=makeleftright(q,style,maxd,maxh);
16:{774:}begin curstyle:=mem[q].hh.b1;s:=3;
{714:}begin if curstyle<4 then cursize:=0 else cursize:=16*((curstyle-2)
div 2);
curmu:=xovern(fontinfo[6+parambase[eqtb[25585+cursize].hh.rh]].int,18);
end{:714};goto 83;end{:774};10,14,3,9,7,4,6,12,13:begin mem[p].hh.rh:=q;
p:=q;q:=mem[q].hh.rh;mem[p].hh.rh:=-1073741823;goto 30;end;
5:begin mem[p].hh.rh:=q;p:=q;q:=mem[q].hh.rh;mem[p].hh.rh:=-1073741823;
goto 30;end;others:confusion(948)end{:772};
{777:}if rtype>0 then begin case strpool[rtype*8+t+magicoffset]of 48:x:=
0;49:if curstyle<4 then x:=17 else x:=0;50:x:=17;
51:if curstyle<4 then x:=18 else x:=0;
52:if curstyle<4 then x:=19 else x:=0;others:confusion(950)end;
if x<>0 then begin y:=mathglue(eqtb[24527+x].hh.rh,curmu);z:=newglue(y);
mem[y].hh.rh:=-1073741823;mem[p].hh.rh:=z;p:=z;mem[z].hh.b1:=x+1;end;
end{:777};
{778:}if mem[q+1].int<>-1073741823 then begin mem[p].hh.rh:=mem[q+1].int
;repeat p:=mem[p].hh.rh;until mem[p].hh.rh=-1073741823;end;
if penalties then if mem[q].hh.rh<>-1073741823 then if pen<10000 then
begin rtype:=mem[mem[q].hh.rh].hh.b0;
if rtype<>14 then if rtype<>21 then begin z:=newpenalty(pen);
mem[p].hh.rh:=z;p:=z;end;end{:778};rtype:=t;83:r:=q;q:=mem[q].hh.rh;
freenode(r,s);30:end{:771};p:=newnullbox;
mem[p].hh.rh:=mem[memtop-3].hh.rh;adjusthlist(p,false);
mem[memtop-3].hh.rh:=mem[p].hh.rh;deleteglueref(mem[p+7].hh.rh);
deleteglueref(mem[p+7].hh.lh);freenode(p,10);end;
{:737}{783:}procedure pushalignment;var p:halfword;begin p:=getnode(5);
mem[p].hh.rh:=alignptr;mem[p].hh.lh:=curalign;
mem[p+1].hh.lh:=mem[memtop-8].hh.rh;mem[p+1].hh.rh:=curspan;
mem[p+2].int:=curloop;mem[p+3].int:=alignstate;mem[p+4].hh.lh:=curhead;
mem[p+4].hh.rh:=curtail;alignptr:=p;curhead:=getavail;end;
procedure popalignment;var p:halfword;
begin begin mem[curhead].hh.rh:=avail;avail:=curhead;
ifdef('STAT')decr(dynused);endif('STAT')end;p:=alignptr;
curtail:=mem[p+4].hh.rh;curhead:=mem[p+4].hh.lh;
alignstate:=mem[p+3].int;curloop:=mem[p+2].int;curspan:=mem[p+1].hh.rh;
mem[memtop-8].hh.rh:=mem[p+1].hh.lh;curalign:=mem[p].hh.lh;
alignptr:=mem[p].hh.rh;freenode(p,5);end;
{:783}{785:}{793:}procedure getpreambletoken;label 20;begin 20:gettoken;
while(curchr=256)and(curcmd=4)do begin gettoken;
if curcmd>115 then begin expand;gettoken;end;end;
if curcmd=9 then fatalerror(633);
if(curcmd=83)and(curchr=24538)then begin scanoptionalequals;scanglue(2);
if eqtb[28505].int>0 then geqdefine(24538,132,curval)else eqdefine(24538
,132,curval);goto 20;end;end;{:793}procedure alignpeek;forward;
procedure normalparagraph;forward;procedure initalign;label 30,31,32,22;
var savecsptr:halfword;p:halfword;begin savecsptr:=curcs;pushalignment;
alignstate:=-1000000;
{787:}if(curlist.modefield=233)and((curlist.tailfield<>curlist.headfield
)or(curlist.auxfield.int<>-1073741823))then begin begin if interaction=3
then;if filelineerrorstylep then printfileline else printnl(263);
print(721);end;printesc(558);print(951);begin helpptr:=3;
helpline[2]:=952;helpline[1]:=953;helpline[0]:=954;end;error;flushmath;
end{:787};pushnest;
{786:}if curlist.modefield=233 then begin curlist.modefield:=-1;
curlist.auxfield.int:=nest[nestptr-2].auxfield.int;
end else if curlist.modefield>0 then curlist.modefield:=-curlist.
modefield{:786};scanspec(6,false);
{788:}mem[memtop-8].hh.rh:=-1073741823;curalign:=memtop-8;
curloop:=-1073741823;scannerstatus:=4;warningindex:=savecsptr;
alignstate:=-1000000;
while true do begin{789:}mem[curalign].hh.rh:=newparamglue(11);
curalign:=mem[curalign].hh.rh{:789};if curcmd=5 then goto 30;
{790:}{794:}p:=memtop-4;mem[p].hh.rh:=-1073741823;
while true do begin getpreambletoken;if curcmd=6 then goto 31;
if(curcmd<=5)and(curcmd>=4)and(alignstate=-1000000)then if(p=memtop-4)
and(curloop=-1073741823)and(curcmd=4)then curloop:=curalign else begin
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(960);
end;begin helpptr:=3;helpline[2]:=961;helpline[1]:=962;helpline[0]:=963;
end;backerror;goto 31;
end else if(curcmd<>10)or(p<>memtop-4)then begin mem[p].hh.rh:=getavail;
p:=mem[p].hh.rh;mem[p].hh.lh:=curtok;end;end;31:{:794};
mem[curalign].hh.rh:=newnullbox;curalign:=mem[curalign].hh.rh;
mem[curalign].hh.lh:=memtop-9;mem[curalign+1].int:=-1073741824;
mem[curalign+3].int:=mem[memtop-4].hh.rh;{795:}p:=memtop-4;
mem[p].hh.rh:=-1073741823;while true do begin 22:getpreambletoken;
if(curcmd<=5)and(curcmd>=4)and(alignstate=-1000000)then goto 32;
if curcmd=6 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(964);
end;begin helpptr:=3;helpline[2]:=961;helpline[1]:=962;helpline[0]:=965;
end;error;goto 22;end;mem[p].hh.rh:=getavail;p:=mem[p].hh.rh;
mem[p].hh.lh:=curtok;end;32:mem[p].hh.rh:=getavail;p:=mem[p].hh.rh;
mem[p].hh.lh:=536886430{:795};
mem[curalign+2].int:=mem[memtop-4].hh.rh{:790};end;
30:scannerstatus:=0{:788};newsavelevel(6);
if eqtb[25068].hh.rh<>-1073741823 then begintokenlist(eqtb[25068].hh.rh,
13);alignpeek;end;{:785}{797:}{798:}procedure initspan(p:halfword);
begin pushnest;
if curlist.modefield=-117 then curlist.auxfield.hh.lh:=1000 else begin
curlist.auxfield.int:=-65536000;normalparagraph;end;curspan:=p;end;
{:798}procedure initrow;begin pushnest;
curlist.modefield:=(-118)-curlist.modefield;
if curlist.modefield=-117 then curlist.auxfield.hh.lh:=0 else curlist.
auxfield.int:=0;
begin mem[curlist.tailfield].hh.rh:=newglue(mem[mem[memtop-8].hh.rh+1].
hh.lh);curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=12;
curalign:=mem[mem[memtop-8].hh.rh].hh.rh;curtail:=curhead;
initspan(curalign);end;{:797}{799:}procedure initcol;
begin mem[curalign+5].hh.lh:=curcmd;
if curcmd=68 then alignstate:=0 else begin backinput;
begintokenlist(mem[curalign+3].int,1);end;end;
{:799}{802:}function fincol:boolean;label 10;var p:halfword;
q,r:halfword;s:halfword;u:halfword;w:scaled;o:glueord;n:halfword;
begin if curalign=-1073741823 then confusion(966);
q:=mem[curalign].hh.rh;if q=-1073741823 then confusion(966);
if alignstate<500000 then fatalerror(633);p:=mem[q].hh.rh;
{803:}if(p=-1073741823)and(mem[curalign+5].hh.lh<257)then if curloop<>
-1073741823 then{804:}begin mem[q].hh.rh:=newnullbox;p:=mem[q].hh.rh;
mem[p].hh.lh:=memtop-9;mem[p+1].int:=-1073741824;
curloop:=mem[curloop].hh.rh;{805:}q:=memtop-4;r:=mem[curloop+3].int;
while r<>-1073741823 do begin mem[q].hh.rh:=getavail;q:=mem[q].hh.rh;
mem[q].hh.lh:=mem[r].hh.lh;r:=mem[r].hh.rh;end;
mem[q].hh.rh:=-1073741823;mem[p+3].int:=mem[memtop-4].hh.rh;q:=memtop-4;
r:=mem[curloop+2].int;
while r<>-1073741823 do begin mem[q].hh.rh:=getavail;q:=mem[q].hh.rh;
mem[q].hh.lh:=mem[r].hh.lh;r:=mem[r].hh.rh;end;
mem[q].hh.rh:=-1073741823;mem[p+2].int:=mem[memtop-4].hh.rh{:805};
curloop:=mem[curloop].hh.rh;mem[p].hh.rh:=newglue(mem[curloop+1].hh.lh);
end{:804}else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(967);
end;printesc(956);begin helpptr:=3;helpline[2]:=968;helpline[1]:=969;
helpline[0]:=970;end;mem[curalign+5].hh.lh:=257;error;end{:803};
if mem[curalign+5].hh.lh<>256 then begin unsave;newsavelevel(6);
{807:}begin if curlist.modefield=-117 then begin adjusttail:=curtail;
adjusthlist(curlist.headfield,false);deleteglueref(curkanjiskip);
deleteglueref(curxkanjiskip);
curkanjiskip:=mem[curlist.headfield+7].hh.rh;
curxkanjiskip:=mem[curlist.headfield+7].hh.lh;
incr(mem[curkanjiskip].hh.rh);incr(mem[curxkanjiskip].hh.rh);
u:=hpack(mem[curlist.headfield].hh.rh,0,1);w:=mem[u+1].int;
curtail:=adjusttail;adjusttail:=-1073741823;
end else begin u:=vpackage(mem[curlist.headfield].hh.rh,0,1,0);
w:=mem[u+3].int;end;n:=0;
if curspan<>curalign then{809:}begin q:=curspan;repeat incr(n);
q:=mem[mem[q].hh.rh].hh.rh;until q=curalign;
if n>65535 then confusion(971);q:=curspan;
while mem[mem[q].hh.lh].hh.rh<n do q:=mem[q].hh.lh;
if mem[mem[q].hh.lh].hh.rh>n then begin s:=getnode(2);
mem[s].hh.lh:=mem[q].hh.lh;mem[s].hh.rh:=n;mem[q].hh.lh:=s;
mem[s+1].int:=w;
end else if mem[mem[q].hh.lh+1].int<w then mem[mem[q].hh.lh+1].int:=w;
end{:809}else if w>mem[curalign+1].int then mem[curalign+1].int:=w;
mem[u].hh.b0:=15;mem[u].hh.b1:=n;
{670:}if totalstretch[3]<>0 then o:=3 else if totalstretch[2]<>0 then o
:=2 else if totalstretch[1]<>0 then o:=1 else o:=0{:670};
mem[u+5].hh.b1:=o;mem[u+6].int:=totalstretch[o];
{676:}if totalshrink[3]<>0 then o:=3 else if totalshrink[2]<>0 then o:=2
else if totalshrink[1]<>0 then o:=1 else o:=0{:676};mem[u+5].hh.b0:=o;
mem[u+4].int:=totalshrink[o];popnest;mem[curlist.tailfield].hh.rh:=u;
curlist.tailfield:=u;end{:807};
{806:}begin mem[curlist.tailfield].hh.rh:=newglue(mem[mem[curalign].hh.
rh+1].hh.lh);curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=12{:806};
if mem[curalign+5].hh.lh>=257 then begin fincol:=true;goto 10;end;
initspan(p);end;alignstate:=1000000;{417:}repeat getxtoken;
until curcmd<>10{:417};curalign:=p;initcol;fincol:=false;10:end;
{:802}{810:}procedure finrow;var p:halfword;
begin if curlist.modefield=-117 then begin adjusthlist(curlist.headfield
,false);deleteglueref(curkanjiskip);deleteglueref(curxkanjiskip);
curkanjiskip:=mem[curlist.headfield+7].hh.rh;
curxkanjiskip:=mem[curlist.headfield+7].hh.lh;
incr(mem[curkanjiskip].hh.rh);incr(mem[curxkanjiskip].hh.rh);
p:=hpack(mem[curlist.headfield].hh.rh,0,1);popnest;appendtovlist(p);
if curhead<>curtail then begin mem[curlist.tailfield].hh.rh:=mem[curhead
].hh.rh;curlist.tailfield:=curtail;end;
end else begin p:=vpackage(mem[curlist.headfield].hh.rh,0,1,1073741823);
popnest;mem[curlist.tailfield].hh.rh:=p;curlist.tailfield:=p;
curlist.auxfield.hh.lh:=1000;end;mem[p].hh.b0:=15;mem[p+6].int:=0;
if eqtb[25068].hh.rh<>-1073741823 then begintokenlist(eqtb[25068].hh.rh,
13);alignpeek;end;{:810}{811:}procedure doassignments;forward;
procedure resumeafterdisplay;forward;procedure buildpage;forward;
procedure finalign;var p,q,r,s,u,v,z:halfword;t,w:scaled;o:scaled;
n:halfword;rulesave:scaled;auxsave:memoryword;
begin if curgroup<>6 then confusion(972);unsave;
if curgroup<>6 then confusion(973);unsave;
if nest[nestptr-1].modefield=233 then o:=eqtb[29053].int else o:=0;
{812:}q:=mem[mem[memtop-8].hh.rh].hh.rh;repeat flushlist(mem[q+3].int);
flushlist(mem[q+2].int);p:=mem[mem[q].hh.rh].hh.rh;
if mem[q+1].int=-1073741824 then{813:}begin mem[q+1].int:=0;
r:=mem[q].hh.rh;s:=mem[r+1].hh.lh;
if s<>membot then begin incr(mem[membot].hh.rh);deleteglueref(s);
mem[r+1].hh.lh:=membot;end;end{:813};
if mem[q].hh.lh<>memtop-9 then{814:}begin t:=mem[q+1].int+mem[mem[mem[q]
.hh.rh+1].hh.lh+1].int;r:=mem[q].hh.lh;s:=memtop-9;mem[s].hh.lh:=p;n:=1;
repeat mem[r+1].int:=mem[r+1].int-t;u:=mem[r].hh.lh;
while mem[r].hh.rh>n do begin s:=mem[s].hh.lh;
n:=mem[mem[s].hh.lh].hh.rh+1;end;
if mem[r].hh.rh<n then begin mem[r].hh.lh:=mem[s].hh.lh;mem[s].hh.lh:=r;
decr(mem[r].hh.rh);s:=r;
end else begin if mem[r+1].int>mem[mem[s].hh.lh+1].int then mem[mem[s].
hh.lh+1].int:=mem[r+1].int;freenode(r,2);end;r:=u;until r=memtop-9;
end{:814};mem[q].hh.b0:=15;mem[q].hh.b1:=0;mem[q+3].int:=0;
mem[q+2].int:=0;mem[q+5].hh.b1:=0;mem[q+5].hh.b0:=0;mem[q+6].int:=0;
mem[q+4].int:=0;q:=p;until q=-1073741823{:812};{815:}saveptr:=saveptr-2;
packbeginline:=-curlist.mlfield;
if curlist.modefield=-1 then begin rulesave:=eqtb[29054].int;
eqtb[29054].int:=0;z:=newnullbox;mem[z].hh.rh:=mem[memtop-8].hh.rh;
adjusthlist(z,false);deleteglueref(curkanjiskip);
deleteglueref(curxkanjiskip);curkanjiskip:=mem[z+7].hh.rh;
curxkanjiskip:=mem[z+7].hh.lh;incr(mem[curkanjiskip].hh.rh);
incr(mem[curxkanjiskip].hh.rh);
p:=hpack(mem[memtop-8].hh.rh,savestack[saveptr+1].int,savestack[saveptr
+0].int);eqtb[29054].int:=rulesave;deleteglueref(mem[z+7].hh.rh);
deleteglueref(mem[z+7].hh.lh);freenode(z,10);
end else begin q:=mem[mem[memtop-8].hh.rh].hh.rh;
repeat mem[q+3].int:=mem[q+1].int;mem[q+1].int:=0;
q:=mem[mem[q].hh.rh].hh.rh;until q=-1073741823;
p:=vpackage(mem[memtop-8].hh.rh,savestack[saveptr+1].int,savestack[
saveptr+0].int,1073741823);q:=mem[mem[memtop-8].hh.rh].hh.rh;
repeat mem[q+1].int:=mem[q+3].int;mem[q+3].int:=0;
q:=mem[mem[q].hh.rh].hh.rh;until q=-1073741823;end;
packbeginline:=0{:815};{816:}q:=mem[curlist.headfield].hh.rh;
s:=curlist.headfield;
while q<>-1073741823 do begin if not(q>=himemmin)then if mem[q].hh.b0=15
then{818:}begin if curlist.modefield=-1 then begin mem[q].hh.b0:=0;
mem[q+1].int:=mem[p+1].int;end else begin mem[q].hh.b0:=1;
mem[q+3].int:=mem[p+3].int;end;mem[q].hh.b1:=abs(curlist.dirfield);
mem[q+5].hh.b1:=mem[p+5].hh.b1;mem[q+5].hh.b0:=mem[p+5].hh.b0;
mem[q+6].gr:=mem[p+6].gr;mem[q+4].int:=o;r:=mem[mem[q+5].hh.rh].hh.rh;
s:=mem[mem[p+5].hh.rh].hh.rh;repeat{819:}n:=mem[r].hh.b1;
t:=mem[s+1].int;w:=t;u:=memtop-4;while n>0 do begin decr(n);
{820:}s:=mem[s].hh.rh;v:=mem[s+1].hh.lh;mem[u].hh.rh:=newglue(v);
u:=mem[u].hh.rh;mem[u].hh.b1:=12;t:=t+mem[v+1].int;
if mem[p+5].hh.b0=1 then begin if mem[v].hh.b0=mem[p+5].hh.b1 then t:=t+
round(mem[p+6].gr*mem[v+2].int);
end else if mem[p+5].hh.b0=2 then begin if mem[v].hh.b1=mem[p+5].hh.b1
then t:=t-round(mem[p+6].gr*mem[v+3].int);end;s:=mem[s].hh.rh;
mem[u].hh.rh:=newnullbox;u:=mem[u].hh.rh;t:=t+mem[s+1].int;
if curlist.modefield=-1 then mem[u+1].int:=mem[s+1].int else begin mem[u
].hh.b0:=1;mem[u+3].int:=mem[s+1].int;end;
mem[u].hh.b1:=abs(curlist.dirfield){:820};end;
if curlist.modefield=-1 then{821:}begin mem[r+3].int:=mem[q+3].int;
mem[r+2].int:=mem[q+2].int;
if t=mem[r+1].int then begin mem[r+5].hh.b0:=0;mem[r+5].hh.b1:=0;
mem[r+6].gr:=0.0;
end else if t>mem[r+1].int then begin mem[r+5].hh.b0:=1;
if mem[r+6].int=0 then mem[r+6].gr:=0.0 else mem[r+6].gr:=(t-mem[r+1].
int)/mem[r+6].int;end else begin mem[r+5].hh.b1:=mem[r+5].hh.b0;
mem[r+5].hh.b0:=2;
if mem[r+4].int=0 then mem[r+6].gr:=0.0 else if(mem[r+5].hh.b1=0)and(mem
[r+1].int-t>mem[r+4].int)then mem[r+6].gr:=1.0 else mem[r+6].gr:=(mem[r
+1].int-t)/mem[r+4].int;end;mem[r+1].int:=w;mem[r].hh.b0:=0;
mem[r].hh.b1:=abs(curlist.dirfield);
end{:821}else{822:}begin mem[r+1].int:=mem[q+1].int;
if t=mem[r+3].int then begin mem[r+5].hh.b0:=0;mem[r+5].hh.b1:=0;
mem[r+6].gr:=0.0;
end else if t>mem[r+3].int then begin mem[r+5].hh.b0:=1;
if mem[r+6].int=0 then mem[r+6].gr:=0.0 else mem[r+6].gr:=(t-mem[r+3].
int)/mem[r+6].int;end else begin mem[r+5].hh.b1:=mem[r+5].hh.b0;
mem[r+5].hh.b0:=2;
if mem[r+4].int=0 then mem[r+6].gr:=0.0 else if(mem[r+5].hh.b1=0)and(mem
[r+3].int-t>mem[r+4].int)then mem[r+6].gr:=1.0 else mem[r+6].gr:=(mem[r
+3].int-t)/mem[r+4].int;end;mem[r+3].int:=w;mem[r].hh.b0:=1;
mem[r].hh.b1:=abs(curlist.dirfield);end{:822};mem[r+4].int:=0;
if u<>memtop-4 then begin mem[u].hh.rh:=mem[r].hh.rh;
mem[r].hh.rh:=mem[memtop-4].hh.rh;r:=u;end{:819};
r:=mem[mem[r].hh.rh].hh.rh;s:=mem[mem[s].hh.rh].hh.rh;
until r=-1073741823;
end{:818}else if mem[q].hh.b0=3 then{817:}begin if(mem[q+1].int=
-1073741824)then mem[q+1].int:=mem[p+1].int;
if(mem[q+3].int=-1073741824)then mem[q+3].int:=mem[p+3].int;
if(mem[q+2].int=-1073741824)then mem[q+2].int:=mem[p+2].int;
if o<>0 then begin r:=mem[q].hh.rh;mem[q].hh.rh:=-1073741823;
q:=hpack(q,0,1);mem[q+4].int:=o;mem[q].hh.rh:=r;mem[s].hh.rh:=q;end;
end{:817};s:=q;q:=mem[q].hh.rh;end{:816};flushnodelist(p);popalignment;
{823:}auxsave:=curlist.auxfield;p:=mem[curlist.headfield].hh.rh;
q:=curlist.tailfield;popnest;
if curlist.modefield=233 then{1218:}begin doassignments;
if curcmd<>3 then{1219:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1245);
end;begin helpptr:=2;helpline[1]:=952;helpline[0]:=953;end;backerror;
end{:1219}else{1209:}begin getxtoken;
if curcmd<>3 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1241);
end;begin helpptr:=2;helpline[1]:=1242;helpline[0]:=1243;end;backerror;
end;end{:1209};popnest;
begin mem[curlist.tailfield].hh.rh:=newpenalty(eqtb[28473].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
begin mem[curlist.tailfield].hh.rh:=newparamglue(3);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.rh:=p;
if p<>-1073741823 then curlist.tailfield:=q;
begin mem[curlist.tailfield].hh.rh:=newpenalty(eqtb[28474].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
begin mem[curlist.tailfield].hh.rh:=newparamglue(4);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
curlist.auxfield.int:=auxsave.int;resumeafterdisplay;
end{:1218}else begin curlist.auxfield:=auxsave;
mem[curlist.tailfield].hh.rh:=p;
if p<>-1073741823 then curlist.tailfield:=q;
if curlist.modefield=1 then buildpage;end{:823};end;
{796:}procedure alignpeek;label 20;begin 20:alignstate:=1000000;
{417:}repeat getxtoken;until curcmd<>10{:417};
if curcmd=38 then begin scanleftbrace;newsavelevel(7);
if curlist.modefield=-1 then normalparagraph;
end else if curcmd=2 then finalign else if(curcmd=5)and(curchr=258)then
goto 20 else begin initrow;initcol;end;end;
{:796}{:811}{826:}{837:}function finiteshrink(p:halfword):halfword;
var q:halfword;
begin if noshrinkerroryet then begin noshrinkerroryet:=false;
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(974);
end;begin helpptr:=5;helpline[4]:=975;helpline[3]:=976;helpline[2]:=977;
helpline[1]:=978;helpline[0]:=979;end;error;end;q:=newspec(p);
mem[q].hh.b1:=0;deleteglueref(p);finiteshrink:=q;end;
{:837}{840:}procedure trybreak(pi:integer;breaktype:smallnumber);
label 10,30,31,22,60;var r:halfword;prevr:halfword;oldl:halfword;
nobreakyet:boolean;{841:}prevprevr:halfword;s:halfword;q:halfword;
v:halfword;t:integer;f:internalfontnumber;l:halfword;
noderstaysactive:boolean;linewidth:scaled;fitclass:0..3;b:halfword;
d:integer;artificialdemerits:boolean;savelink:halfword;shortfall:scaled;
{:841}begin{842:}if abs(pi)>=10000 then if pi>0 then goto 10 else pi:=
-10000{:842};nobreakyet:=true;prevr:=memtop-7;oldl:=0;
curactivewidth[1]:=activewidth[1];curactivewidth[2]:=activewidth[2];
curactivewidth[3]:=activewidth[3];curactivewidth[4]:=activewidth[4];
curactivewidth[5]:=activewidth[5];curactivewidth[6]:=activewidth[6];
while true do begin 22:r:=mem[prevr].hh.rh;
{843:}if mem[r].hh.b0=2 then begin curactivewidth[1]:=curactivewidth[1]+
mem[r+1].int;curactivewidth[2]:=curactivewidth[2]+mem[r+2].int;
curactivewidth[3]:=curactivewidth[3]+mem[r+3].int;
curactivewidth[4]:=curactivewidth[4]+mem[r+4].int;
curactivewidth[5]:=curactivewidth[5]+mem[r+5].int;
curactivewidth[6]:=curactivewidth[6]+mem[r+6].int;prevprevr:=prevr;
prevr:=r;goto 22;end{:843};{846:}begin l:=mem[r+1].hh.lh;
if l>oldl then begin if(minimumdemerits<1073741823)and((oldl<>easyline)
or(r=memtop-7))then{847:}begin if nobreakyet then{848:}begin nobreakyet
:=false;breakwidth[1]:=background[1];breakwidth[2]:=background[2];
breakwidth[3]:=background[3];breakwidth[4]:=background[4];
breakwidth[5]:=background[5];breakwidth[6]:=background[6];s:=curp;
if breaktype>0 then if curp<>-1073741823 then{851:}begin t:=mem[curp].hh
.b1;v:=curp;s:=mem[curp+1].hh.rh;while t>0 do begin decr(t);
v:=mem[v].hh.rh;{852:}if(v>=himemmin)then begin f:=mem[v].hh.b0;
breakwidth[1]:=breakwidth[1]-fontinfo[widthbase[f]+fontinfo[charbase[f]+
mem[v].hh.b1].qqqq.b0].int;if fontdir[f]<>0 then v:=mem[v].hh.rh;
end else case mem[v].hh.b0 of 8:begin f:=mem[v+1].hh.b0;
breakwidth[1]:=breakwidth[1]-fontinfo[widthbase[f]+fontinfo[charbase[f]+
mem[v+1].hh.b1].qqqq.b0].int;end;
0,1,2,3,13:breakwidth[1]:=breakwidth[1]-mem[v+1].int;5:;
others:confusion(980)end{:852};end;
while s<>-1073741823 do begin{853:}if(s>=himemmin)then begin f:=mem[s].
hh.b0;
breakwidth[1]:=breakwidth[1]+fontinfo[widthbase[f]+fontinfo[charbase[f]+
mem[s].hh.b1].qqqq.b0].int;if fontdir[f]<>0 then s:=mem[s].hh.rh;
end else case mem[s].hh.b0 of 8:begin f:=mem[s+1].hh.b0;
breakwidth[1]:=breakwidth[1]+fontinfo[widthbase[f]+fontinfo[charbase[f]+
mem[s+1].hh.b1].qqqq.b0].int;end;
0,1,2,3,13:breakwidth[1]:=breakwidth[1]+mem[s+1].int;5:;
others:confusion(981)end{:853};s:=mem[s].hh.rh;end;
breakwidth[1]:=breakwidth[1]+discwidth;
if mem[curp+1].hh.rh=-1073741823 then s:=mem[v].hh.rh;end{:851};
while s<>-1073741823 do begin if(s>=himemmin)then begin if chain then
begin breakwidth[1]:=breakwidth[1]-mem[curkanjiskip+1].int;
breakwidth[2+mem[curkanjiskip].hh.b0]:=breakwidth[2+mem[curkanjiskip].hh
.b0]-mem[curkanjiskip+2].int;
breakwidth[6]:=breakwidth[6]-mem[curkanjiskip+3].int;end;goto 30 end;
case mem[s].hh.b0 of 12:{849:}begin v:=mem[s+1].hh.lh;
breakwidth[1]:=breakwidth[1]-mem[v+1].int;
breakwidth[2+mem[v].hh.b0]:=breakwidth[2+mem[v].hh.b0]-mem[v+2].int;
breakwidth[6]:=breakwidth[6]-mem[v+3].int;end{:849};14:;
11:breakwidth[1]:=breakwidth[1]-mem[s+1].int;
13:if(mem[s].hh.b1<>1)and(mem[s].hh.b1<>3)then goto 30 else breakwidth[1
]:=breakwidth[1]-mem[s+1].int;others:goto 30 end;s:=mem[s].hh.rh;end;
30:end{:848};
{854:}if mem[prevr].hh.b0=2 then begin mem[prevr+1].int:=mem[prevr+1].
int-curactivewidth[1]+breakwidth[1];
mem[prevr+2].int:=mem[prevr+2].int-curactivewidth[2]+breakwidth[2];
mem[prevr+3].int:=mem[prevr+3].int-curactivewidth[3]+breakwidth[3];
mem[prevr+4].int:=mem[prevr+4].int-curactivewidth[4]+breakwidth[4];
mem[prevr+5].int:=mem[prevr+5].int-curactivewidth[5]+breakwidth[5];
mem[prevr+6].int:=mem[prevr+6].int-curactivewidth[6]+breakwidth[6];
end else if prevr=memtop-7 then begin activewidth[1]:=breakwidth[1];
activewidth[2]:=breakwidth[2];activewidth[3]:=breakwidth[3];
activewidth[4]:=breakwidth[4];activewidth[5]:=breakwidth[5];
activewidth[6]:=breakwidth[6];end else begin q:=getnode(7);
mem[q].hh.rh:=r;mem[q].hh.b0:=2;mem[q].hh.b1:=0;
mem[q+1].int:=breakwidth[1]-curactivewidth[1];
mem[q+2].int:=breakwidth[2]-curactivewidth[2];
mem[q+3].int:=breakwidth[3]-curactivewidth[3];
mem[q+4].int:=breakwidth[4]-curactivewidth[4];
mem[q+5].int:=breakwidth[5]-curactivewidth[5];
mem[q+6].int:=breakwidth[6]-curactivewidth[6];mem[prevr].hh.rh:=q;
prevprevr:=prevr;prevr:=q;end{:854};
if abs(eqtb[28478].int)>=1073741823-minimumdemerits then minimumdemerits
:=1073741822 else minimumdemerits:=minimumdemerits+abs(eqtb[28478].int);
for fitclass:=0 to 3 do begin if minimaldemerits[fitclass]<=
minimumdemerits then{856:}begin q:=getnode(2);mem[q].hh.rh:=passive;
passive:=q;mem[q+1].hh.rh:=curp;ifdef('STAT')incr(passnumber);
mem[q].hh.lh:=passnumber;
endif('STAT')mem[q+1].hh.lh:=bestplace[fitclass];q:=getnode(3);
mem[q+1].hh.rh:=passive;mem[q+1].hh.lh:=bestplline[fitclass]+1;
mem[q].hh.b1:=fitclass;mem[q].hh.b0:=breaktype;
mem[q+2].int:=minimaldemerits[fitclass];mem[q].hh.rh:=r;
mem[prevr].hh.rh:=q;prevr:=q;
ifdef('STAT')if eqtb[28494].int>0 then{857:}begin printnl(982);
printint(mem[passive].hh.lh);print(983);printint(mem[q+1].hh.lh-1);
printchar(46);printint(fitclass);if breaktype=1 then printchar(45);
print(984);printint(mem[q+2].int);print(985);
if mem[passive+1].hh.lh=-1073741823 then printchar(48)else printint(mem[
mem[passive+1].hh.lh].hh.lh);end{:857};endif('STAT')end{:856};
minimaldemerits[fitclass]:=1073741823;end;minimumdemerits:=1073741823;
{855:}if r<>memtop-7 then begin q:=getnode(7);mem[q].hh.rh:=r;
mem[q].hh.b0:=2;mem[q].hh.b1:=0;
mem[q+1].int:=curactivewidth[1]-breakwidth[1];
mem[q+2].int:=curactivewidth[2]-breakwidth[2];
mem[q+3].int:=curactivewidth[3]-breakwidth[3];
mem[q+4].int:=curactivewidth[4]-breakwidth[4];
mem[q+5].int:=curactivewidth[5]-breakwidth[5];
mem[q+6].int:=curactivewidth[6]-breakwidth[6];mem[prevr].hh.rh:=q;
prevprevr:=prevr;prevr:=q;end{:855};end{:847};
if r=memtop-7 then goto 10;
{861:}if l>easyline then begin linewidth:=secondwidth;oldl:=1073741822;
end else begin oldl:=l;
if l>lastspecialline then linewidth:=secondwidth else if eqtb[25060].hh.
rh=-1073741823 then linewidth:=firstwidth else linewidth:=mem[eqtb[25060
].hh.rh+2*l].int;end{:861};end;end{:846};
{862:}begin artificialdemerits:=false;
shortfall:=linewidth-curactivewidth[1];
if shortfall>0 then{863:}if(curactivewidth[3]<>0)or(curactivewidth[4]<>0
)or(curactivewidth[5]<>0)then begin b:=0;fitclass:=2;
end else begin if shortfall>7230584 then if curactivewidth[2]<1663497
then begin b:=10000;fitclass:=0;goto 31;end;
b:=badness(shortfall,curactivewidth[2]);
if b>12 then if b>99 then fitclass:=0 else fitclass:=1 else fitclass:=2;
31:end{:863}else{864:}begin if-shortfall>curactivewidth[6]then b:=10001
else b:=badness(-shortfall,curactivewidth[6]);
if b>12 then fitclass:=3 else fitclass:=2;end{:864};
if(b>10000)or(pi=-10000)then{865:}begin if finalpass and(minimumdemerits
=1073741823)and(mem[r].hh.rh=memtop-7)and(prevr=memtop-7)then
artificialdemerits:=true else if b>threshold then goto 60;
noderstaysactive:=false;end{:865}else begin prevr:=r;
if b>threshold then goto 22;noderstaysactive:=true;end;
{866:}if artificialdemerits then d:=0 else{870:}begin d:=eqtb[28464].int
+b;if abs(d)>=10000 then d:=100000000 else d:=d*d;
if pi<>0 then if pi>0 then d:=d+pi*pi else if pi>-10000 then d:=d-pi*pi;
if(breaktype=1)and(mem[r].hh.b0=1)then if curp<>-1073741823 then d:=d+
eqtb[28476].int else d:=d+eqtb[28477].int;
if abs(fitclass-mem[r].hh.b1)>1 then d:=d+eqtb[28478].int;end{:870};
ifdef('STAT')if eqtb[28494].int>0 then{867:}begin if printednode<>curp
then{868:}begin printnl(344);
if curp=-1073741823 then shortdisplay(mem[printednode].hh.rh)else begin
savelink:=mem[curp].hh.rh;mem[curp].hh.rh:=-1073741823;printnl(344);
shortdisplay(mem[printednode].hh.rh);mem[curp].hh.rh:=savelink;end;
printednode:=curp;end{:868};printnl(64);
if curp=-1073741823 then printesc(635)else if(mem[curp].hh.b0<>12)and(
not(curp>=himemmin))then begin if mem[curp].hh.b0=14 then printesc(569)
else if mem[curp].hh.b0=9 then printesc(357)else if mem[curp].hh.b0=13
then printesc(346)else printesc(349);end;print(986);
if mem[r+1].hh.rh=-1073741823 then printchar(48)else printint(mem[mem[r
+1].hh.rh].hh.lh);print(987);
if b>10000 then printchar(42)else printint(b);print(988);printint(pi);
print(989);if artificialdemerits then printchar(42)else printint(d);
end{:867};endif('STAT')d:=d+mem[r+2].int;
if d<=minimaldemerits[fitclass]then begin minimaldemerits[fitclass]:=d;
bestplace[fitclass]:=mem[r+1].hh.rh;bestplline[fitclass]:=l;
if d<minimumdemerits then minimumdemerits:=d;end{:866};
if noderstaysactive then goto 22;
60:{871:}mem[prevr].hh.rh:=mem[r].hh.rh;freenode(r,3);
if prevr=memtop-7 then{872:}begin r:=mem[memtop-7].hh.rh;
if mem[r].hh.b0=2 then begin activewidth[1]:=activewidth[1]+mem[r+1].int
;activewidth[2]:=activewidth[2]+mem[r+2].int;
activewidth[3]:=activewidth[3]+mem[r+3].int;
activewidth[4]:=activewidth[4]+mem[r+4].int;
activewidth[5]:=activewidth[5]+mem[r+5].int;
activewidth[6]:=activewidth[6]+mem[r+6].int;
curactivewidth[1]:=activewidth[1];curactivewidth[2]:=activewidth[2];
curactivewidth[3]:=activewidth[3];curactivewidth[4]:=activewidth[4];
curactivewidth[5]:=activewidth[5];curactivewidth[6]:=activewidth[6];
mem[memtop-7].hh.rh:=mem[r].hh.rh;freenode(r,7);end;
end{:872}else if mem[prevr].hh.b0=2 then begin r:=mem[prevr].hh.rh;
if r=memtop-7 then begin curactivewidth[1]:=curactivewidth[1]-mem[prevr
+1].int;curactivewidth[2]:=curactivewidth[2]-mem[prevr+2].int;
curactivewidth[3]:=curactivewidth[3]-mem[prevr+3].int;
curactivewidth[4]:=curactivewidth[4]-mem[prevr+4].int;
curactivewidth[5]:=curactivewidth[5]-mem[prevr+5].int;
curactivewidth[6]:=curactivewidth[6]-mem[prevr+6].int;
mem[prevprevr].hh.rh:=memtop-7;freenode(prevr,7);prevr:=prevprevr;
end else if mem[r].hh.b0=2 then begin curactivewidth[1]:=curactivewidth[
1]+mem[r+1].int;curactivewidth[2]:=curactivewidth[2]+mem[r+2].int;
curactivewidth[3]:=curactivewidth[3]+mem[r+3].int;
curactivewidth[4]:=curactivewidth[4]+mem[r+4].int;
curactivewidth[5]:=curactivewidth[5]+mem[r+5].int;
curactivewidth[6]:=curactivewidth[6]+mem[r+6].int;
mem[prevr+1].int:=mem[prevr+1].int+mem[r+1].int;
mem[prevr+2].int:=mem[prevr+2].int+mem[r+2].int;
mem[prevr+3].int:=mem[prevr+3].int+mem[r+3].int;
mem[prevr+4].int:=mem[prevr+4].int+mem[r+4].int;
mem[prevr+5].int:=mem[prevr+5].int+mem[r+5].int;
mem[prevr+6].int:=mem[prevr+6].int+mem[r+6].int;
mem[prevr].hh.rh:=mem[r].hh.rh;freenode(r,7);end;end{:871};end{:862};
end;
10:ifdef('STAT'){869:}if curp=printednode then if curp<>-1073741823 then
if mem[curp].hh.b0=9 then begin t:=mem[curp].hh.b1;
while t>0 do begin decr(t);printednode:=mem[printednode].hh.rh;end;
end{:869}endif('STAT')end;
{:840}{888:}procedure postlinebreak(finalwidowpenalty:integer);
label 30,31;var q,r,s:halfword;discbreak:boolean;postdiscbreak:boolean;
curwidth:scaled;curindent:scaled;t:quarterword;pen:integer;
curline:halfword;begin{889:}q:=mem[bestbet+1].hh.rh;curp:=-1073741823;
repeat r:=q;q:=mem[q+1].hh.lh;mem[r+1].hh.lh:=curp;curp:=r;
until q=-1073741823{:889};curline:=curlist.pgfield+1;lastdisp:=0;
repeat{891:}{892:}q:=mem[curp+1].hh.rh;discbreak:=false;
postdiscbreak:=false;
if q<>-1073741823 then begin if not(q>=himemmin)then if mem[q].hh.b0=12
then begin deleteglueref(mem[q+1].hh.lh);
mem[q+1].hh.lh:=eqtb[24535].hh.rh;mem[q].hh.b1:=9;
incr(mem[eqtb[24535].hh.rh].hh.rh);goto 30;
end else begin if mem[q].hh.b0=9 then{893:}begin t:=mem[q].hh.b1;
{894:}if t=0 then r:=mem[q].hh.rh else begin r:=q;
while t>1 do begin r:=mem[r].hh.rh;decr(t);end;s:=mem[r].hh.rh;
r:=mem[s].hh.rh;mem[s].hh.rh:=-1073741823;flushnodelist(mem[q].hh.rh);
mem[q].hh.b1:=0;end{:894};
if mem[q+1].hh.rh<>-1073741823 then{895:}begin s:=mem[q+1].hh.rh;
while mem[s].hh.rh<>-1073741823 do s:=mem[s].hh.rh;mem[s].hh.rh:=r;
r:=mem[q+1].hh.rh;mem[q+1].hh.rh:=-1073741823;postdiscbreak:=true;
end{:895};
if mem[q+1].hh.lh<>-1073741823 then{896:}begin s:=mem[q+1].hh.lh;
mem[q].hh.rh:=s;while mem[s].hh.rh<>-1073741823 do s:=mem[s].hh.rh;
mem[q+1].hh.lh:=-1073741823;q:=s;end{:896};mem[q].hh.rh:=r;
discbreak:=true;
end{:893}else if(mem[q].hh.b0=11)or(mem[q].hh.b0=13)then mem[q+1].int:=0
;end end else begin q:=memtop-3;
while mem[q].hh.rh<>-1073741823 do q:=mem[q].hh.rh;end;
{897:}r:=newparamglue(8);mem[r].hh.rh:=mem[q].hh.rh;mem[q].hh.rh:=r;
q:=r{:897};30:{:892};{898:}r:=mem[q].hh.rh;mem[q].hh.rh:=-1073741823;
q:=mem[memtop-3].hh.rh;mem[memtop-3].hh.rh:=r;
if lastdisp<>0 then begin r:=getnode(2);mem[r].hh.b0:=5;
mem[r+1].int:=lastdisp;mem[r].hh.rh:=q;q:=r;end;
if eqtb[24534].hh.rh<>membot then begin r:=newparamglue(7);
mem[r].hh.rh:=q;q:=r;end{:898};
{900:}if curline>lastspecialline then begin curwidth:=secondwidth;
curindent:=secondindent;
end else if eqtb[25060].hh.rh=-1073741823 then begin curwidth:=
firstwidth;curindent:=firstindent;
end else begin curwidth:=mem[eqtb[25060].hh.rh+2*curline].int;
curindent:=mem[eqtb[25060].hh.rh+2*curline-1].int;end;
adjusttail:=memtop-5;justbox:=hpack(q,curwidth,0);
mem[justbox+4].int:=curindent{:900};{899:}appendtovlist(justbox);
if memtop-5<>adjusttail then begin mem[curlist.tailfield].hh.rh:=mem[
memtop-5].hh.rh;curlist.tailfield:=adjusttail;end;
adjusttail:=-1073741823{:899};
{901:}if curline+1<>bestline then begin pen:=eqtb[28475].int;
if curline=curlist.pgfield+1 then pen:=pen+eqtb[28467].int;
if curline+2=bestline then pen:=pen+finalwidowpenalty;
if discbreak then pen:=pen+eqtb[28470].int;
if pen<>0 then begin r:=newpenalty(pen);mem[curlist.tailfield].hh.rh:=r;
curlist.tailfield:=r;end;end{:901}{:891};incr(curline);
curp:=mem[curp+1].hh.lh;
if curp<>-1073741823 then if not postdiscbreak then{890:}begin r:=memtop
-3;while true do begin q:=mem[r].hh.rh;
if q=mem[curp+1].hh.rh then goto 31;if(q>=himemmin)then goto 31;
if(mem[q].hh.b0<11)then goto 31;
if mem[q].hh.b0=13 then if(mem[q].hh.b1<>1)and(mem[q].hh.b1<>3)then goto
31;r:=q;end;31:if r<>memtop-3 then begin mem[r].hh.rh:=-1073741823;
flushnodelist(mem[memtop-3].hh.rh);mem[memtop-3].hh.rh:=q;end;end{:890};
until curp=-1073741823;
if(curline<>bestline)or(mem[memtop-3].hh.rh<>-1073741823)then confusion(
996);curlist.pgfield:=bestline-1;end;
{:888}{906:}{917:}function reconstitute(j,n:smallnumber;
bchar,hchar:halfword):smallnumber;label 22,30;var p:halfword;t:halfword;
q:fourquarters;currh:halfword;testchar:halfword;w:scaled;k:fontindex;
begin hyphenpassed:=0;t:=memtop-4;w:=0;mem[memtop-4].hh.rh:=-1073741823;
{919:}curl:=hu[j];curq:=t;if j=0 then begin ligaturepresent:=initlig;
p:=initlist;if ligaturepresent then lfthit:=initlft;
while p>-1073741823 do begin begin mem[t].hh.rh:=getavail;
t:=mem[t].hh.rh;mem[t].hh.b0:=hf;mem[t].hh.b1:=mem[p].hh.b1;end;
p:=mem[p].hh.rh;end;
end else if curl<256 then begin mem[t].hh.rh:=getavail;t:=mem[t].hh.rh;
mem[t].hh.b0:=hf;mem[t].hh.b1:=curl;end;ligstack:=-1073741823;
begin if j<n then curr:=hu[j+1]else curr:=bchar;
if odd(hyf[j])then currh:=hchar else currh:=256;end{:919};
22:{920:}if curl=256 then begin k:=bcharlabel[hf];
if k=0 then goto 30 else q:=fontinfo[k].qqqq;
end else begin q:=fontinfo[charbase[hf]+effectivechar(true,hf,curl)].
qqqq;if((q.b2)mod 4)<>1 then goto 30;k:=ligkernbase[hf]+q.b3;
q:=fontinfo[k].qqqq;
if q.b0>128 then begin k:=ligkernbase[hf]+256*q.b2+q.b3+32768-256*(128);
q:=fontinfo[k].qqqq;end;end;
if currh<256 then testchar:=currh else testchar:=curr;
while true do begin if q.b1=testchar then if q.b0<=128 then if currh<256
then begin hyphenpassed:=j;hchar:=256;currh:=256;goto 22;
end else begin if hchar<256 then if odd(hyf[j])then begin hyphenpassed:=
j;hchar:=256;end;
if q.b2<128 then{922:}begin if curl=256 then lfthit:=true;
if j=n then if ligstack=-1073741823 then rthit:=true;
begin if interrupt<>0 then pauseforinstructions;end;
case q.b2 of 1,5:begin curl:=q.b3;ligaturepresent:=true;end;
2,6:begin curr:=q.b3;
if ligstack>-1073741823 then mem[ligstack].hh.b1:=curr else begin
ligstack:=newligitem(curr);
if j=n then bchar:=256 else begin p:=getavail;mem[ligstack+1].hh.rh:=p;
mem[p].hh.b1:=hu[j+1];mem[p].hh.b0:=hf;end;end;end;3:begin curr:=q.b3;
p:=ligstack;ligstack:=newligitem(curr);mem[ligstack].hh.rh:=p;end;
7,11:begin if ligaturepresent then begin p:=newligature(hf,curl,mem[curq
].hh.rh);if lfthit then begin mem[p].hh.b1:=2;lfthit:=false;end;
if false then if ligstack=-1073741823 then begin incr(mem[p].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=p;t:=p;ligaturepresent:=false;end;
curq:=t;curl:=q.b3;ligaturepresent:=true;end;others:begin curl:=q.b3;
ligaturepresent:=true;
if ligstack>-1073741823 then begin if mem[ligstack+1].hh.rh>-1073741823
then begin mem[t].hh.rh:=mem[ligstack+1].hh.rh;t:=mem[t].hh.rh;incr(j);
end;p:=ligstack;ligstack:=mem[p].hh.rh;freenode(p,2);
if ligstack=-1073741823 then begin if j<n then curr:=hu[j+1]else curr:=
bchar;if odd(hyf[j])then currh:=hchar else currh:=256;
end else curr:=mem[ligstack].hh.b1;
end else if j=n then goto 30 else begin begin mem[t].hh.rh:=getavail;
t:=mem[t].hh.rh;mem[t].hh.b0:=hf;mem[t].hh.b1:=curr;end;incr(j);
begin if j<n then curr:=hu[j+1]else curr:=bchar;
if odd(hyf[j])then currh:=hchar else currh:=256;end;end;end end;
if q.b2>4 then if q.b2<>7 then goto 30;goto 22;end{:922};
w:=fontinfo[kernbase[hf]+256*q.b2+q.b3].int;goto 30;end;
if q.b0>=128 then if currh=256 then goto 30 else begin currh:=256;
goto 22;end;k:=k+q.b0+1;q:=fontinfo[k].qqqq;end;30:{:920};
{921:}if ligaturepresent then begin p:=newligature(hf,curl,mem[curq].hh.
rh);if lfthit then begin mem[p].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[p].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=p;t:=p;ligaturepresent:=false;end;
if w<>0 then begin mem[t].hh.rh:=newkern(w);t:=mem[t].hh.rh;w:=0;
mem[t+2].int:=0;end;if ligstack>-1073741823 then begin curq:=t;
curl:=mem[ligstack].hh.b1;ligaturepresent:=true;
begin if mem[ligstack+1].hh.rh>-1073741823 then begin mem[t].hh.rh:=mem[
ligstack+1].hh.rh;t:=mem[t].hh.rh;incr(j);end;p:=ligstack;
ligstack:=mem[p].hh.rh;freenode(p,2);
if ligstack=-1073741823 then begin if j<n then curr:=hu[j+1]else curr:=
bchar;if odd(hyf[j])then currh:=hchar else currh:=256;
end else curr:=mem[ligstack].hh.b1;end;goto 22;end{:921};
reconstitute:=j;end;{:917}procedure hyphenate;
label 50,30,40,41,42,45,10;var{912:}i,j,l:0..65;q,r,s:halfword;
bchar:halfword;{:912}{923:}majortail,minortail:halfword;c:ASCIIcode;
cloc:0..63;rcount:integer;hyfnode:halfword;{:923}{933:}z:triepointer;
v:integer;{:933}{940:}h:hyphpointer;k:strnumber;u:poolpointer;
{:940}begin{934:}for j:=0 to hn do hyf[j]:=0;{941:}h:=hc[1];incr(hn);
hc[hn]:=curlang;for j:=2 to hn do h:=(h+h+hc[j])mod 607;
while true do begin{942:}k:=hyphword[h];if k=0 then goto 45;
if(strstart[k+1]-strstart[k])=hn then begin j:=1;u:=strstart[k];
repeat if strpool[u]<>hc[j]then goto 30;incr(j);incr(u);until j>hn;
{943:}s:=hyphlist[h];while s<>-1073741823 do begin hyf[mem[s].hh.lh]:=1;
s:=mem[s].hh.rh;end{:943};decr(hn);goto 40;end;30:{:942};h:=hyphlink[h];
if h=0 then goto 45;decr(h);end;45:decr(hn){:941};
if trietrc[curlang+1]<>curlang then goto 10;hc[0]:=0;hc[hn+1]:=0;
hc[hn+2]:=256;
for j:=0 to hn-rhyf+1 do begin z:=trietrl[curlang+1]+hc[j];l:=j;
while hc[l]=trietrc[z]do begin if trietro[z]<>mintrieop then{935:}begin
v:=trietro[z];repeat v:=v+opstart[curlang];i:=l-hyfdistance[v];
if hyfnum[v]>hyf[i]then hyf[i]:=hyfnum[v];v:=hyfnext[v];
until v=mintrieop;end{:935};incr(l);z:=trietrl[z]+hc[l];end;end;
40:for j:=0 to lhyf-1 do hyf[j]:=0;
for j:=0 to rhyf-1 do hyf[hn-j]:=0{:934};
{913:}for j:=lhyf to hn-rhyf do if odd(hyf[j])then goto 41;goto 10;
41:{:913};{914:}q:=mem[hb].hh.rh;mem[hb].hh.rh:=-1073741823;
r:=mem[ha].hh.rh;mem[ha].hh.rh:=-1073741823;bchar:=hyfbchar;
if(ha>=himemmin)then if mem[ha].hh.b0<>hf then goto 42 else begin
initlist:=ha;initlig:=false;hu[0]:=mem[ha].hh.b1;
end else if mem[ha].hh.b0=8 then if mem[ha+1].hh.b0<>hf then goto 42
else begin initlist:=mem[ha+1].hh.rh;initlig:=true;
initlft:=(mem[ha].hh.b1>1);hu[0]:=mem[ha+1].hh.b1;
if initlist=-1073741823 then if initlft then begin hu[0]:=256;
initlig:=false;end;freenode(ha,2);
end else begin if not(r>=himemmin)then if mem[r].hh.b0=8 then if mem[r].
hh.b1>1 then goto 42;j:=1;s:=ha;initlist:=-1073741823;goto 50;end;
s:=curp;while mem[s].hh.rh<>ha do s:=mem[s].hh.rh;j:=0;goto 50;42:s:=ha;
j:=0;hu[0]:=256;initlig:=false;initlist:=-1073741823;
50:flushnodelist(r);{924:}repeat l:=j;
j:=reconstitute(j,hn,bchar,hyfchar)+1;
if hyphenpassed=0 then begin mem[s].hh.rh:=mem[memtop-4].hh.rh;
while mem[s].hh.rh>-1073741823 do s:=mem[s].hh.rh;
if odd(hyf[j-1])then begin l:=j;hyphenpassed:=j-1;
mem[memtop-4].hh.rh:=-1073741823;end;end;
if hyphenpassed>0 then{925:}repeat r:=getnode(2);
mem[r].hh.rh:=mem[memtop-4].hh.rh;mem[r].hh.b0:=9;majortail:=r;
rcount:=0;
while mem[majortail].hh.rh>-1073741823 do begin majortail:=mem[majortail
].hh.rh;incr(rcount);end;i:=hyphenpassed;hyf[i]:=0;
{926:}minortail:=-1073741823;mem[r+1].hh.lh:=-1073741823;
hyfnode:=newcharacter(hf,hyfchar);
if hyfnode<>-1073741823 then begin incr(i);c:=hu[i];hu[i]:=hyfchar;
begin mem[hyfnode].hh.rh:=avail;avail:=hyfnode;
ifdef('STAT')decr(dynused);endif('STAT')end;end;
while l<=i do begin l:=reconstitute(l,i,fontbchar[hf],256)+1;
if mem[memtop-4].hh.rh>-1073741823 then begin if minortail=-1073741823
then mem[r+1].hh.lh:=mem[memtop-4].hh.rh else mem[minortail].hh.rh:=mem[
memtop-4].hh.rh;minortail:=mem[memtop-4].hh.rh;
while mem[minortail].hh.rh>-1073741823 do minortail:=mem[minortail].hh.
rh;end;end;if hyfnode<>-1073741823 then begin hu[i]:=c;l:=i;decr(i);
end{:926};{927:}minortail:=-1073741823;mem[r+1].hh.rh:=-1073741823;
cloc:=0;if bcharlabel[hf]<>0 then begin decr(l);c:=hu[l];cloc:=l;
hu[l]:=256;end;
while l<j do begin repeat l:=reconstitute(l,hn,bchar,256)+1;
if cloc>0 then begin hu[cloc]:=c;cloc:=0;end;
if mem[memtop-4].hh.rh>-1073741823 then begin if minortail=-1073741823
then mem[r+1].hh.rh:=mem[memtop-4].hh.rh else mem[minortail].hh.rh:=mem[
memtop-4].hh.rh;minortail:=mem[memtop-4].hh.rh;
while mem[minortail].hh.rh>-1073741823 do minortail:=mem[minortail].hh.
rh;end;until l>=j;
while l>j do{928:}begin j:=reconstitute(j,hn,bchar,256)+1;
mem[majortail].hh.rh:=mem[memtop-4].hh.rh;
while mem[majortail].hh.rh>-1073741823 do begin majortail:=mem[majortail
].hh.rh;incr(rcount);end;end{:928};end{:927};
{929:}if rcount>127 then begin mem[s].hh.rh:=mem[r].hh.rh;
mem[r].hh.rh:=-1073741823;flushnodelist(r);
end else begin mem[s].hh.rh:=r;mem[r].hh.b1:=rcount;end;
s:=majortail{:929};hyphenpassed:=j-1;mem[memtop-4].hh.rh:=-1073741823;
until not odd(hyf[j-1]){:925};until j>hn;mem[s].hh.rh:=q{:924};
flushlist(initlist){:914};10:end;
{:906}{953:}ifdef('INITEX'){955:}function newtrieop(d,n:smallnumber;
v:trieopcode):trieopcode;label 10;var h:negtrieopsize..trieopsize;
u:trieopcode;l:0..trieopsize;
begin h:=abs(n+313*d+361*v+1009*curlang)mod(trieopsize-negtrieopsize)+
negtrieopsize;while true do begin l:=trieophash[h];
if l=0 then begin if trieopptr=trieopsize then overflow(1006,trieopsize)
;u:=trieused[curlang];
if u=maxtrieop then overflow(1007,maxtrieop-mintrieop);incr(trieopptr);
incr(u);trieused[curlang]:=u;if u>maxopused then maxopused:=u;
hyfdistance[trieopptr]:=d;hyfnum[trieopptr]:=n;hyfnext[trieopptr]:=v;
trieoplang[trieopptr]:=curlang;trieophash[h]:=trieopptr;
trieopval[trieopptr]:=u;newtrieop:=u;goto 10;end;
if(hyfdistance[l]=d)and(hyfnum[l]=n)and(hyfnext[l]=v)and(trieoplang[l]=
curlang)then begin newtrieop:=trieopval[l];goto 10;end;
if h>-trieopsize then decr(h)else h:=trieopsize;end;10:end;
{:955}{959:}function trienode(p:triepointer):triepointer;label 10;
var h:triepointer;q:triepointer;
begin h:=abs(triec[p]+1009*trieo[p]+2718*triel[p]+3142*trier[p])mod
triesize;while true do begin q:=triehash[h];
if q=0 then begin triehash[h]:=p;trienode:=p;goto 10;end;
if(triec[q]=triec[p])and(trieo[q]=trieo[p])and(triel[q]=triel[p])and(
trier[q]=trier[p])then begin trienode:=q;goto 10;end;
if h>0 then decr(h)else h:=triesize;end;10:end;
{:959}{960:}function compresstrie(p:triepointer):triepointer;
begin if p=0 then compresstrie:=0 else begin triel[p]:=compresstrie(
triel[p]);trier[p]:=compresstrie(trier[p]);compresstrie:=trienode(p);
end;end;{:960}{964:}procedure firstfit(p:triepointer);label 45,40;
var h:triepointer;z:triepointer;q:triepointer;c:ASCIIcode;
l,r:triepointer;ll:1..256;begin c:=triec[p];z:=triemin[c];
while true do begin h:=z-c;
{965:}if triemax<h+256 then begin if triesize<=h+256 then overflow(1008,
triesize);repeat incr(triemax);trietaken[triemax]:=false;
trietrl[triemax]:=triemax+1;trietro[triemax]:=triemax-1;
until triemax=h+256;end{:965};if trietaken[h]then goto 45;
{966:}q:=trier[p];
while q>0 do begin if trietrl[h+triec[q]]=0 then goto 45;q:=trier[q];
end;goto 40{:966};45:z:=trietrl[z];end;40:{967:}trietaken[h]:=true;
triehash[p]:=h;q:=p;repeat z:=h+triec[q];l:=trietro[z];r:=trietrl[z];
trietro[r]:=l;trietrl[l]:=r;trietrl[z]:=0;
if l<256 then begin if z<256 then ll:=z else ll:=256;
repeat triemin[l]:=r;incr(l);until l=ll;end;q:=trier[q];until q=0{:967};
end;{:964}{968:}procedure triepack(p:triepointer);var q:triepointer;
begin repeat q:=triel[p];
if(q>0)and(triehash[q]=0)then begin firstfit(q);triepack(q);end;
p:=trier[p];until p=0;end;{:968}{970:}procedure triefix(p:triepointer);
var q:triepointer;c:ASCIIcode;z:triepointer;begin z:=triehash[p];
repeat q:=triel[p];c:=triec[p];trietrl[z+c]:=triehash[q];
trietrc[z+c]:=c;trietro[z+c]:=trieo[p];if q>0 then triefix(q);
p:=trier[p];until p=0;end;{:970}{971:}procedure newpatterns;label 30,31;
var k,l:0..64;digitsensed:boolean;v:trieopcode;p,q:triepointer;
firstchild:boolean;c:ASCIIcode;
begin if trienotready then begin if eqtb[28513].int<=0 then curlang:=0
else if eqtb[28513].int>255 then curlang:=0 else curlang:=eqtb[28513].
int;scanleftbrace;{972:}k:=0;hyf[0]:=0;digitsensed:=false;
while true do begin getxtoken;
case curcmd of 11,12:{973:}if digitsensed or(curchr<48)or(curchr>57)then
begin if curchr=46 then curchr:=0 else begin curchr:=eqtb[27182+curchr].
hh.rh;if curchr=0 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1014);
end;begin helpptr:=1;helpline[0]:=1013;end;error;end;end;
if k<63 then begin incr(k);hc[k]:=curchr;hyf[k]:=0;digitsensed:=false;
end;end else if k<63 then begin hyf[k]:=curchr-48;digitsensed:=true;
end{:973};
10,2:begin if k>0 then{974:}begin{976:}if hc[1]=0 then hyf[0]:=0;
if hc[k]=0 then hyf[k]:=0;l:=k;v:=mintrieop;
while true do begin if hyf[l]<>0 then v:=newtrieop(k-l,hyf[l],v);
if l>0 then decr(l)else goto 31;end;31:{:976};q:=0;hc[0]:=curlang;
while l<=k do begin c:=hc[l];incr(l);p:=triel[q];firstchild:=true;
while(p>0)and(c>triec[p])do begin q:=p;p:=trier[q];firstchild:=false;
end;
if(p=0)or(c<triec[p])then{975:}begin if trieptr=triesize then overflow(
1008,triesize);incr(trieptr);trier[trieptr]:=p;p:=trieptr;triel[p]:=0;
if firstchild then triel[q]:=p else trier[q]:=p;triec[p]:=c;
trieo[p]:=mintrieop;end{:975};q:=p;end;
if trieo[q]<>mintrieop then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1015);
end;begin helpptr:=1;helpline[0]:=1013;end;error;end;trieo[q]:=v;
end{:974};if curcmd=2 then goto 30;k:=0;hyf[0]:=0;digitsensed:=false;
end;others:begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1012);
end;printesc(1010);begin helpptr:=1;helpline[0]:=1013;end;error;end end;
end;30:{:972};end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1009);
end;printesc(1010);begin helpptr:=1;helpline[0]:=1011;end;error;
mem[memtop-12].hh.rh:=scantoks(false,false);flushlist(defref);end;end;
{:971}{977:}procedure inittrie;var p:triepointer;j,k,t:integer;
r,s:triepointer;begin{963:}{956:}opstart[0]:=-mintrieop;
for j:=1 to 255 do opstart[j]:=opstart[j-1]+trieused[j-1];
for j:=1 to trieopptr do trieophash[j]:=opstart[trieoplang[j]]+trieopval
[j];
for j:=1 to trieopptr do while trieophash[j]>j do begin k:=trieophash[j]
;t:=hyfdistance[k];hyfdistance[k]:=hyfdistance[j];hyfdistance[j]:=t;
t:=hyfnum[k];hyfnum[k]:=hyfnum[j];hyfnum[j]:=t;t:=hyfnext[k];
hyfnext[k]:=hyfnext[j];hyfnext[j]:=t;trieophash[j]:=trieophash[k];
trieophash[k]:=k;end{:956};for p:=0 to triesize do triehash[p]:=0;
triel[0]:=compresstrie(triel[0]);for p:=0 to trieptr do triehash[p]:=0;
for p:=0 to 255 do triemin[p]:=p+1;trietrl[0]:=1;triemax:=0{:963};
if triel[0]<>0 then begin firstfit(triel[0]);triepack(triel[0]);end;
{969:}if triel[0]=0 then begin for r:=0 to 256 do begin trietrl[r]:=0;
trietro[r]:=mintrieop;trietrc[r]:=0;end;triemax:=256;
end else begin triefix(triel[0]);r:=0;repeat s:=trietrl[r];
begin trietrl[r]:=0;trietro[r]:=mintrieop;trietrc[r]:=0;end;r:=s;
until r>triemax;end;trietrc[0]:=63;{:969};trienotready:=false;end;
{:977}endif('INITEX'){:953}procedure linebreak(finalwidowpenalty:integer
);label 30,31,32,33,34,35,22;var{873:}autobreaking:boolean;
prevp:halfword;q,r,s,prevs:halfword;f,postf:internalfontnumber;
postp:halfword;cc:ASCIIcode;firstuse:boolean;{:873}{904:}j:smallnumber;
c:0..255;{:904}begin packbeginline:=curlist.mlfield;
{827:}firstuse:=true;chain:=false;deleteglueref(curkanjiskip);
deleteglueref(curxkanjiskip);
curkanjiskip:=mem[curlist.headfield+7].hh.rh;
curxkanjiskip:=mem[curlist.headfield+7].hh.lh;
incr(mem[curkanjiskip].hh.rh);incr(mem[curxkanjiskip].hh.rh);
mem[memtop-3].hh.rh:=mem[curlist.headfield].hh.rh;
if not(curlist.tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)
then begin freenode(curlist.tailfield,2);
curlist.tailfield:=curlist.pnodefield;
mem[curlist.tailfield].hh.rh:=-1073741823 end;
if(curlist.tailfield>=himemmin)then begin mem[curlist.tailfield].hh.rh:=
newpenalty(10000);curlist.tailfield:=mem[curlist.tailfield].hh.rh;
end else if mem[curlist.tailfield].hh.b0<>12 then begin mem[curlist.
tailfield].hh.rh:=newpenalty(10000);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;
end else begin mem[curlist.tailfield].hh.b0:=14;
deleteglueref(mem[curlist.tailfield+1].hh.lh);
flushnodelist(mem[curlist.tailfield+1].hh.rh);
mem[curlist.tailfield+1].int:=10000;end;
mem[curlist.tailfield].hh.rh:=newparamglue(14);
initcurlang:=curlist.pgfield mod 65536;
initlhyf:=curlist.pgfield div 4194304;
initrhyf:=(curlist.pgfield div 65536)mod 64;popnest;
{:827}{838:}noshrinkerroryet:=true;
if(mem[eqtb[24534].hh.rh].hh.b1<>0)and(mem[eqtb[24534].hh.rh+3].int<>0)
then begin eqtb[24534].hh.rh:=finiteshrink(eqtb[24534].hh.rh);end;
if(mem[eqtb[24535].hh.rh].hh.b1<>0)and(mem[eqtb[24535].hh.rh+3].int<>0)
then begin eqtb[24535].hh.rh:=finiteshrink(eqtb[24535].hh.rh);end;
q:=eqtb[24534].hh.rh;r:=eqtb[24535].hh.rh;
background[1]:=mem[q+1].int+mem[r+1].int;background[2]:=0;
background[3]:=0;background[4]:=0;background[5]:=0;
background[2+mem[q].hh.b0]:=mem[q+2].int;
background[2+mem[r].hh.b0]:=background[2+mem[r].hh.b0]+mem[r+2].int;
background[6]:=mem[q+3].int+mem[r+3].int;
{:838}{845:}minimumdemerits:=1073741823;minimaldemerits[3]:=1073741823;
minimaldemerits[2]:=1073741823;minimaldemerits[1]:=1073741823;
minimaldemerits[0]:=1073741823;
{:845}{859:}if eqtb[25060].hh.rh=-1073741823 then if eqtb[29055].int=0
then begin lastspecialline:=0;secondwidth:=eqtb[29041].int;
secondindent:=0;
end else{860:}begin lastspecialline:=abs(eqtb[28503].int);
if eqtb[28503].int<0 then begin firstwidth:=eqtb[29041].int-abs(eqtb[
29055].int);
if eqtb[29055].int>=0 then firstindent:=eqtb[29055].int else firstindent
:=0;secondwidth:=eqtb[29041].int;secondindent:=0;
end else begin firstwidth:=eqtb[29041].int;firstindent:=0;
secondwidth:=eqtb[29041].int-abs(eqtb[29055].int);
if eqtb[29055].int>=0 then secondindent:=eqtb[29055].int else
secondindent:=0;end;
end{:860}else begin lastspecialline:=mem[eqtb[25060].hh.rh].hh.lh-1;
secondwidth:=mem[eqtb[25060].hh.rh+2*(lastspecialline+1)].int;
secondindent:=mem[eqtb[25060].hh.rh+2*lastspecialline+1].int;end;
if eqtb[28481].int=0 then easyline:=lastspecialline else easyline:=
1073741823{:859};{874:}threshold:=eqtb[28462].int;
if threshold>=0 then begin ifdef('STAT')if eqtb[28494].int>0 then begin
begindiagnostic;printnl(990);end;endif('STAT')secondpass:=false;
finalpass:=false;end else begin threshold:=eqtb[28463].int;
secondpass:=true;finalpass:=(eqtb[29058].int<=0);
ifdef('STAT')if eqtb[28494].int>0 then begindiagnostic;endif('STAT')end;
while true do begin if threshold>10000 then threshold:=10000;
if secondpass then{902:}begin ifdef('INITEX')if trienotready then
inittrie;endif('INITEX')curlang:=initcurlang;lhyf:=initlhyf;
rhyf:=initrhyf;end{:902};{875:}q:=getnode(3);mem[q].hh.b0:=0;
mem[q].hh.b1:=2;mem[q].hh.rh:=memtop-7;mem[q+1].hh.rh:=-1073741823;
mem[q+1].hh.lh:=curlist.pgfield+1;mem[q+2].int:=0;
mem[memtop-7].hh.rh:=q;activewidth[1]:=background[1];
activewidth[2]:=background[2];activewidth[3]:=background[3];
activewidth[4]:=background[4];activewidth[5]:=background[5];
activewidth[6]:=background[6];passive:=-1073741823;
printednode:=memtop-3;passnumber:=0;fontinshortdisplay:=0{:875};
curp:=mem[memtop-3].hh.rh;autobreaking:=true;prevp:=curp;
while(curp<>-1073741823)and(mem[memtop-7].hh.rh<>memtop-7)do{877:}begin
if(curp>=himemmin)then{878:}begin chain:=false;
if(curp>=himemmin)then if fontdir[mem[curp].hh.b0]<>0 then begin case
mem[prevp].hh.b0 of 0,1,2,3,8,9,11:begin curp:=prevp;trybreak(0,0);
curp:=mem[curp].hh.rh;end;others:;end;end;prevp:=curp;postp:=curp;
postf:=mem[postp].hh.b0;repeat f:=postf;cc:=mem[curp].hh.b1;
activewidth[1]:=activewidth[1]+fontinfo[widthbase[f]+fontinfo[charbase[f
]+cc].qqqq.b0].int;postp:=mem[curp].hh.rh;
if fontdir[f]<>0 then begin prevp:=curp;curp:=postp;
postp:=mem[postp].hh.rh;
if(postp>=himemmin)then begin postf:=mem[postp].hh.b0;
if fontdir[postf]<>0 then chain:=true else chain:=false;trybreak(0,0);
end else begin chain:=false;
case mem[postp].hh.b0 of 0,1,2,3,8,9,11:trybreak(0,0);others:;end;end;
if chain then begin if firstuse then begin if(mem[curkanjiskip].hh.b1<>0
)and(mem[curkanjiskip+3].int<>0)then begin curkanjiskip:=finiteshrink(
curkanjiskip);end;firstuse:=false;end;
activewidth[1]:=activewidth[1]+mem[curkanjiskip+1].int;
activewidth[2+mem[curkanjiskip].hh.b0]:=activewidth[2+mem[curkanjiskip].
hh.b0]+mem[curkanjiskip+2].int;
activewidth[6]:=activewidth[6]+mem[curkanjiskip+3].int;end;prevp:=curp;
end else if(postp>=himemmin)then begin postf:=mem[postp].hh.b0;
chain:=false;if fontdir[postf]<>0 then trybreak(0,0);end;curp:=postp;
until not(curp>=himemmin);chain:=false;end{:878};
case mem[curp].hh.b0 of 0,1,2,3:activewidth[1]:=activewidth[1]+mem[curp
+1].int;
10:{1375:}if mem[curp].hh.b1=4 then begin curlang:=mem[curp+1].hh.rh;
lhyf:=mem[curp+1].hh.b0;rhyf:=mem[curp+1].hh.b1;end{:1375};
12:begin{879:}if autobreaking then begin if(prevp>=himemmin)then
trybreak(0,0)else if(mem[prevp].hh.b0<11)then trybreak(0,0)else if mem[
prevp].hh.b0=13 then if(mem[prevp].hh.b1<>1)and(mem[prevp].hh.b1<>3)then
trybreak(0,0);end;
if(mem[mem[curp+1].hh.lh].hh.b1<>0)and(mem[mem[curp+1].hh.lh+3].int<>0)
then begin mem[curp+1].hh.lh:=finiteshrink(mem[curp+1].hh.lh);end;
q:=mem[curp+1].hh.lh;activewidth[1]:=activewidth[1]+mem[q+1].int;
activewidth[2+mem[q].hh.b0]:=activewidth[2+mem[q].hh.b0]+mem[q+2].int;
activewidth[6]:=activewidth[6]+mem[q+3].int{:879};
if secondpass and autobreaking then{905:}begin prevs:=curp;
s:=mem[prevs].hh.rh;
if s<>-1073741823 then begin{907:}while true do begin if(s>=himemmin)
then begin hf:=mem[s].hh.b0;if fontdir[hf]<>0 then begin prevs:=s;
s:=mem[prevs].hh.rh;c:=mem[s].hh.lh;goto 22;end else c:=mem[s].hh.b1;
end else if mem[s].hh.b0=5 then goto 22 else if(mem[s].hh.b0=14)and(not
mem[s].hh.b1=0)then goto 22 else if mem[s].hh.b0=8 then if mem[s+1].hh.
rh=-1073741823 then goto 22 else begin q:=mem[s+1].hh.rh;
c:=mem[q].hh.b1;hf:=mem[q].hh.b0;
end else if(mem[s].hh.b0=13)and(mem[s].hh.b1=0)then goto 22 else if mem[
s].hh.b0=10 then begin{1376:}if mem[s].hh.b1=4 then begin curlang:=mem[s
+1].hh.rh;lhyf:=mem[s+1].hh.b0;rhyf:=mem[s+1].hh.b1;end{:1376};goto 22;
end else goto 31;
if eqtb[27182+c].hh.rh<>0 then if(eqtb[27182+c].hh.rh=c)or(eqtb[28500].
int>0)then goto 32 else goto 31;22:prevs:=s;s:=mem[prevs].hh.rh;end;
32:hyfchar:=hyphenchar[hf];if hyfchar<0 then goto 31;
if hyfchar>255 then goto 31;ha:=prevs{:907};
if lhyf+rhyf>63 then goto 31;{908:}hn:=0;
while true do begin if(s>=himemmin)then begin if mem[s].hh.b0<>hf then
goto 33;hyfbchar:=mem[s].hh.b1;c:=hyfbchar;
if eqtb[27182+c].hh.rh=0 then goto 33;if hn=63 then goto 33;hb:=s;
incr(hn);hu[hn]:=c;hc[hn]:=eqtb[27182+c].hh.rh;hyfbchar:=256;
end else if mem[s].hh.b0=8 then{909:}begin if mem[s+1].hh.b0<>hf then
goto 33;j:=hn;q:=mem[s+1].hh.rh;
if q>-1073741823 then hyfbchar:=mem[q].hh.b1;
while q>-1073741823 do begin c:=mem[q].hh.b1;
if eqtb[27182+c].hh.rh=0 then goto 33;if j=63 then goto 33;incr(j);
hu[j]:=c;hc[j]:=eqtb[27182+c].hh.rh;q:=mem[q].hh.rh;end;hb:=s;hn:=j;
if odd(mem[s].hh.b1)then hyfbchar:=fontbchar[hf]else hyfbchar:=256;
end{:909}else if(mem[s].hh.b0=13)and(mem[s].hh.b1=0)then begin hb:=s;
hyfbchar:=fontbchar[hf];end else goto 33;s:=mem[s].hh.rh;end;33:{:908};
{910:}if hn<lhyf+rhyf then goto 31;
while true do begin if not((s>=himemmin))then case mem[s].hh.b0 of 8:;
13:if mem[s].hh.b1<>0 then goto 34;5:;10,12,14,4,7,6:goto 34;
others:goto 31 end;s:=mem[s].hh.rh;end;34:{:910};hyphenate;end;
31:end{:905};end;
13:if(mem[curp].hh.b1=1)or(mem[curp].hh.b1=3)then begin if not(mem[curp]
.hh.rh>=himemmin)and autobreaking then if mem[mem[curp].hh.rh].hh.b0=12
then trybreak(0,0);activewidth[1]:=activewidth[1]+mem[curp+1].int;
end else activewidth[1]:=activewidth[1]+mem[curp+1].int;
8:begin f:=mem[curp+1].hh.b0;
activewidth[1]:=activewidth[1]+fontinfo[widthbase[f]+fontinfo[charbase[f
]+effectivechar(true,f,mem[curp+1].hh.b1)].qqqq.b0].int;end;
9:{880:}begin s:=mem[curp+1].hh.lh;discwidth:=0;
if s=-1073741823 then trybreak(eqtb[28466].int,1)else begin repeat{881:}
if(s>=himemmin)then begin f:=mem[s].hh.b0;
discwidth:=discwidth+fontinfo[widthbase[f]+fontinfo[charbase[f]+mem[s].
hh.b1].qqqq.b0].int;
if fontdir[f]<>0 then s:=mem[s].hh.rh end else case mem[s].hh.b0 of 8:
begin f:=mem[s+1].hh.b0;
discwidth:=discwidth+fontinfo[widthbase[f]+fontinfo[charbase[f]+mem[s+1]
.hh.b1].qqqq.b0].int;end;0,1,2,3,13:discwidth:=discwidth+mem[s+1].int;
5:;others:confusion(994)end{:881};s:=mem[s].hh.rh;until s=-1073741823;
activewidth[1]:=activewidth[1]+discwidth;trybreak(eqtb[28465].int,1);
activewidth[1]:=activewidth[1]-discwidth;end;r:=mem[curp].hh.b1;
s:=mem[curp].hh.rh;
while r>0 do begin{882:}if(s>=himemmin)then begin f:=mem[s].hh.b0;
activewidth[1]:=activewidth[1]+fontinfo[widthbase[f]+fontinfo[charbase[f
]+mem[s].hh.b1].qqqq.b0].int;
if fontdir[f]<>0 then s:=mem[s].hh.rh end else case mem[s].hh.b0 of 8:
begin f:=mem[s+1].hh.b0;
activewidth[1]:=activewidth[1]+fontinfo[widthbase[f]+fontinfo[charbase[f
]+mem[s+1].hh.b1].qqqq.b0].int;end;
0,1,2,3,13:activewidth[1]:=activewidth[1]+mem[s+1].int;5:;
others:confusion(995)end{:882};decr(r);s:=mem[s].hh.rh;end;prevp:=curp;
curp:=s;goto 35;end{:880};11:begin autobreaking:=(mem[curp].hh.b1=1);
begin if not(mem[curp].hh.rh>=himemmin)and autobreaking then if mem[mem[
curp].hh.rh].hh.b0=12 then trybreak(0,0);
activewidth[1]:=activewidth[1]+mem[curp+1].int;end;end;
14:trybreak(mem[curp+1].int,0);5,6,4,7:;others:confusion(993)end;
prevp:=curp;curp:=mem[curp].hh.rh;35:end{:877};
if curp=-1073741823 then{884:}begin trybreak(-10000,1);
if mem[memtop-7].hh.rh<>memtop-7 then begin{885:}r:=mem[memtop-7].hh.rh;
fewestdemerits:=1073741823;
repeat if mem[r].hh.b0<>2 then if mem[r+2].int<fewestdemerits then begin
fewestdemerits:=mem[r+2].int;bestbet:=r;end;r:=mem[r].hh.rh;
until r=memtop-7;bestline:=mem[bestbet+1].hh.lh{:885};
if eqtb[28481].int=0 then goto 30;{886:}begin r:=mem[memtop-7].hh.rh;
actuallooseness:=0;
repeat if mem[r].hh.b0<>2 then begin linediff:=mem[r+1].hh.lh-bestline;
if((linediff<actuallooseness)and(eqtb[28481].int<=linediff))or((linediff
>actuallooseness)and(eqtb[28481].int>=linediff))then begin bestbet:=r;
actuallooseness:=linediff;fewestdemerits:=mem[r+2].int;
end else if(linediff=actuallooseness)and(mem[r+2].int<fewestdemerits)
then begin bestbet:=r;fewestdemerits:=mem[r+2].int;end;end;
r:=mem[r].hh.rh;until r=memtop-7;bestline:=mem[bestbet+1].hh.lh;
end{:886};if(actuallooseness=eqtb[28481].int)or finalpass then goto 30;
end;end{:884};{876:}q:=mem[memtop-7].hh.rh;
while q<>memtop-7 do begin curp:=mem[q].hh.rh;
if mem[q].hh.b0=2 then freenode(q,7)else freenode(q,3);q:=curp;end;
q:=passive;while q<>-1073741823 do begin curp:=mem[q].hh.rh;
freenode(q,2);q:=curp;end{:876};
if not secondpass then begin ifdef('STAT')if eqtb[28494].int>0 then
printnl(991);endif('STAT')threshold:=eqtb[28463].int;secondpass:=true;
finalpass:=(eqtb[29058].int<=0);
end else begin ifdef('STAT')if eqtb[28494].int>0 then printnl(992);
endif('STAT')background[2]:=background[2]+eqtb[29058].int;
finalpass:=true;end;end;
30:ifdef('STAT')if eqtb[28494].int>0 then begin enddiagnostic(true);
normalizeselector;end;endif('STAT'){:874};
{887:}postlinebreak(finalwidowpenalty){:887};
{876:}q:=mem[memtop-7].hh.rh;
while q<>memtop-7 do begin curp:=mem[q].hh.rh;
if mem[q].hh.b0=2 then freenode(q,7)else freenode(q,3);q:=curp;end;
q:=passive;while q<>-1073741823 do begin curp:=mem[q].hh.rh;
freenode(q,2);q:=curp;end{:876};packbeginline:=0;end;
{:826}{945:}procedure newhyphexceptions;label 21,10,40,45;var n:0..64;
j:0..64;h:hyphpointer;k:strnumber;p:halfword;q:halfword;s:strnumber;
u,v:poolpointer;begin scanleftbrace;
if eqtb[28513].int<=0 then curlang:=0 else if eqtb[28513].int>255 then
curlang:=0 else curlang:=eqtb[28513].int;{946:}n:=0;p:=-1073741823;
while true do begin getxtoken;
21:case curcmd of 11,12,73,74:{948:}if curchr=45 then{949:}begin if n<63
then begin q:=getavail;mem[q].hh.rh:=p;mem[q].hh.lh:=n;p:=q;end;
end{:949}else begin if eqtb[27182+curchr].hh.rh=0 then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1002);
end;begin helpptr:=2;helpline[1]:=1003;helpline[0]:=1004;end;error;
end else if n<63 then begin incr(n);hc[n]:=eqtb[27182+curchr].hh.rh;end;
end{:948};20,54:begin scancharnum;curchr:=curval;curcmd:=73;goto 21;end;
10,2:begin if n>1 then{950:}begin incr(n);hc[n]:=curlang;
begin if poolptr+n>poolsize then overflow(258,poolsize-initpoolptr);end;
h:=0;for j:=1 to n do begin h:=(h+h+hc[j])mod 607;
begin strpool[poolptr]:=hc[j];incr(poolptr);end;end;s:=makestring;
{951:}if hyphnext<=607 then while(hyphnext>0)and(hyphword[hyphnext-1]>0)
do decr(hyphnext);
if(hyphcount=hyphsize)or(hyphnext=0)then overflow(1005,hyphsize);
incr(hyphcount);while hyphword[h]<>0 do begin{952:}k:=hyphword[h];
if(strstart[k+1]-strstart[k])<>(strstart[s+1]-strstart[s])then goto 45;
u:=strstart[k];v:=strstart[s];
repeat if strpool[u]<>strpool[v]then goto 45;incr(u);incr(v);
until u=strstart[k+1];begin decr(strptr);poolptr:=strstart[strptr];end;
s:=hyphword[h];decr(hyphcount);goto 40;45:{:952};
if hyphlink[h]=0 then begin hyphlink[h]:=hyphnext;
if hyphnext>=hyphsize then hyphnext:=607;
if hyphnext>607 then incr(hyphnext);end;h:=hyphlink[h]-1;end;
40:hyphword[h]:=s;hyphlist[h]:=p{:951};end{:950};
if curcmd=2 then goto 10;n:=0;p:=-1073741823;end;
others:{947:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(721);
end;printesc(998);print(999);begin helpptr:=2;helpline[1]:=1000;
helpline[0]:=1001;end;error;end{:947}end;end{:946};10:end;
{:945}{979:}function prunepagetop(p:halfword):halfword;
var prevp:halfword;q:halfword;begin prevp:=memtop-3;
mem[memtop-3].hh.rh:=p;
while p<>-1073741823 do case mem[p].hh.b0 of 2,0,1,3:{980:}begin q:=
newskipparam(10);mem[prevp].hh.rh:=q;mem[q].hh.rh:=p;
if mem[tempptr+1].int>mem[p+3].int then mem[tempptr+1].int:=mem[tempptr
+1].int-mem[p+3].int else mem[tempptr+1].int:=0;p:=-1073741823;
end{:980};10,6,4:begin prevp:=p;p:=mem[prevp].hh.rh;end;
12,13,14:begin q:=p;p:=mem[q].hh.rh;mem[q].hh.rh:=-1073741823;
mem[prevp].hh.rh:=p;flushnodelist(q);end;others:confusion(1016)end;
prunepagetop:=mem[memtop-3].hh.rh;end;
{:979}{981:}function vertbreak(p:halfword;h,d:scaled):halfword;
label 30,45,90;var prevp:halfword;q,r:halfword;pi:integer;b:integer;
leastcost:integer;bestplace:halfword;prevdp:scaled;t:smallnumber;
begin prevp:=p;leastcost:=1073741823;activewidth[1]:=0;
activewidth[2]:=0;activewidth[3]:=0;activewidth[4]:=0;activewidth[5]:=0;
activewidth[6]:=0;prevdp:=0;
while true do begin{983:}if p=-1073741823 then pi:=-10000 else{984:}case
mem[p].hh.b0 of 2,0,1,3:begin activewidth[1]:=activewidth[1]+prevdp+mem[
p+3].int;prevdp:=mem[p+2].int;goto 45;end;10:{1378:}goto 45{:1378};
12:if(mem[prevp].hh.b0<11)then pi:=0 else goto 90;
13:begin if mem[p].hh.rh=-1073741823 then t:=14 else t:=mem[mem[p].hh.rh
].hh.b0;if t=12 then pi:=0 else goto 90;end;14:pi:=mem[p+1].int;
6,4:goto 45;others:confusion(1017)end{:984};
{985:}if pi<10000 then begin{986:}if activewidth[1]<h then if(
activewidth[3]<>0)or(activewidth[4]<>0)or(activewidth[5]<>0)then b:=0
else b:=badness(h-activewidth[1],activewidth[2])else if activewidth[1]-h
>activewidth[6]then b:=1073741823 else b:=badness(activewidth[1]-h,
activewidth[6]){:986};
if b<1073741823 then if pi<=-10000 then b:=pi else if b<10000 then b:=b+
pi else b:=100000;if b<=leastcost then begin bestplace:=p;leastcost:=b;
bestheightplusdepth:=activewidth[1]+prevdp;end;
if(b=1073741823)or(pi<=-10000)then goto 30;end{:985};
if(mem[p].hh.b0<12)or(mem[p].hh.b0>13)then goto 45;
90:{987:}if mem[p].hh.b0=13 then q:=p else begin q:=mem[p+1].hh.lh;
activewidth[2+mem[q].hh.b0]:=activewidth[2+mem[q].hh.b0]+mem[q+2].int;
activewidth[6]:=activewidth[6]+mem[q+3].int;
if(mem[q].hh.b1<>0)and(mem[q+3].int<>0)then begin begin if interaction=3
then;if filelineerrorstylep then printfileline else printnl(263);
print(1018);end;begin helpptr:=4;helpline[3]:=1019;helpline[2]:=1020;
helpline[1]:=1021;helpline[0]:=979;end;error;r:=newspec(q);
mem[r].hh.b1:=0;deleteglueref(q);mem[p+1].hh.lh:=r;q:=r;end;end;
activewidth[1]:=activewidth[1]+prevdp+mem[q+1].int;prevdp:=0{:987};
45:if prevdp>d then begin activewidth[1]:=activewidth[1]+prevdp-d;
prevdp:=d;end;{:983};prevp:=p;p:=mem[prevp].hh.rh;end;
30:vertbreak:=bestplace;end;{:981}{988:}function vsplit(n:eightbits;
h:scaled):halfword;label 10,30;var v:halfword;w:halfword;p:halfword;
q:halfword;begin v:=eqtb[25326+n].hh.rh;
if curmark[3]<>-1073741823 then begin deletetokenref(curmark[3]);
curmark[3]:=-1073741823;deletetokenref(curmark[4]);
curmark[4]:=-1073741823;end;
{989:}if v=-1073741823 then begin vsplit:=-1073741823;goto 10;end;
if mem[v].hh.b0=2 then begin w:=v;v:=mem[v+5].hh.rh;
deleteglueref(mem[w+7].hh.rh);deleteglueref(mem[w+7].hh.lh);
freenode(w,10);end;
if mem[v].hh.b0<>1 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(344);
end;printesc(1022);print(1023);printesc(1024);begin helpptr:=2;
helpline[1]:=1025;helpline[0]:=1026;end;error;vsplit:=-1073741823;
goto 10;end;flushnodelist(mem[v].hh.rh);mem[v].hh.rh:=-1073741823{:989};
q:=vertbreak(mem[v+5].hh.rh,h,eqtb[29044].int);{990:}p:=mem[v+5].hh.rh;
if p=q then mem[v+5].hh.rh:=-1073741823 else while true do begin if mem[
p].hh.b0=6 then if curmark[3]=-1073741823 then begin curmark[3]:=mem[p+1
].int;curmark[4]:=curmark[3];
mem[curmark[3]].hh.lh:=mem[curmark[3]].hh.lh+2;
end else begin deletetokenref(curmark[4]);curmark[4]:=mem[p+1].int;
incr(mem[curmark[4]].hh.lh);end;
if mem[p].hh.rh=q then begin mem[p].hh.rh:=-1073741823;goto 30;end;
p:=mem[p].hh.rh;end;30:{:990};q:=prunepagetop(q);p:=mem[v+5].hh.rh;
if q=-1073741823 then eqtb[25326+n].hh.rh:=-1073741823 else begin eqtb[
25326+n].hh.rh:=vpackage(q,0,1,1073741823);
mem[eqtb[25326+n].hh.rh].hh.b1:=(mem[v].hh.b1);end;
q:=vpackage(p,h,0,eqtb[29044].int);mem[q].hh.b1:=(mem[v].hh.b1);
deleteglueref(mem[v+7].hh.rh);deleteglueref(mem[v+7].hh.lh);
freenode(v,10);vsplit:=q;10:end;{:988}{996:}procedure printtotals;
begin printscaled(pagesofar[1]);
if pagesofar[2]<>0 then begin print(316);printscaled(pagesofar[2]);
print(344);end;if pagesofar[3]<>0 then begin print(316);
printscaled(pagesofar[3]);print(315);end;
if pagesofar[4]<>0 then begin print(316);printscaled(pagesofar[4]);
print(1035);end;if pagesofar[5]<>0 then begin print(316);
printscaled(pagesofar[5]);print(1036);end;
if pagesofar[6]<>0 then begin print(317);printscaled(pagesofar[6]);end;
end;{:996}{998:}procedure freezepagespecs(s:smallnumber);
begin pagecontents:=s;pagesofar[0]:=eqtb[29042].int;
pagemaxdepth:=eqtb[29043].int;pagesofar[7]:=0;pagesofar[1]:=0;
pagesofar[2]:=0;pagesofar[3]:=0;pagesofar[4]:=0;pagesofar[5]:=0;
pagesofar[6]:=0;leastpagecost:=1073741823;
ifdef('STAT')if eqtb[28495].int>0 then begin begindiagnostic;
printnl(1044);printscaled(pagesofar[0]);print(1045);
printscaled(pagemaxdepth);enddiagnostic(false);end;endif('STAT')end;
{:998}{1003:}procedure boxerror(n:eightbits);begin error;
begindiagnostic;printnl(892);showbox(eqtb[25326+n].hh.rh);
enddiagnostic(true);flushnodelist(eqtb[25326+n].hh.rh);
eqtb[25326+n].hh.rh:=-1073741823;end;
{:1003}{1004:}procedure ensurevbox(n:eightbits);var p:halfword;
begin p:=eqtb[25326+n].hh.rh;
if p<>-1073741823 then if mem[p].hh.b0=2 then begin p:=mem[p+5].hh.rh;
deleteglueref(mem[eqtb[25326+n].hh.rh+7].hh.rh);
deleteglueref(mem[eqtb[25326+n].hh.rh+7].hh.lh);
freenode(eqtb[25326+n].hh.rh,10);eqtb[25326+n].hh.rh:=p end;
if p<>-1073741823 then if mem[p].hh.b0<>1 then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1046);
end;begin helpptr:=3;helpline[2]:=1047;helpline[1]:=1048;
helpline[0]:=1049;end;boxerror(n);end;end;
{:1004}{1005:}{1023:}procedure fireup(c:halfword);label 10;
var p,q,r,s:halfword;prevp:halfword;n:0..255;wait:boolean;
savevbadness:integer;savevfuzz:scaled;savesplittopskip:halfword;
begin{1024:}if mem[bestpagebreak].hh.b0=14 then begin geqworddefine(
28501,mem[bestpagebreak+1].int);mem[bestpagebreak+1].int:=10000;
end else geqworddefine(28501,10000){:1024};
if curmark[2]<>-1073741823 then begin if curmark[0]<>-1073741823 then
deletetokenref(curmark[0]);curmark[0]:=curmark[2];
incr(mem[curmark[0]].hh.lh);deletetokenref(curmark[1]);
curmark[1]:=-1073741823;end;
{1025:}if c=bestpagebreak then bestpagebreak:=-1073741823;
{1026:}if eqtb[25581].hh.rh<>-1073741823 then begin begin if interaction
=3 then;if filelineerrorstylep then printfileline else printnl(263);
print(344);end;printesc(428);print(1062);begin helpptr:=2;
helpline[1]:=1063;helpline[0]:=1049;end;boxerror(255);end{:1026};
insertpenalties:=0;savesplittopskip:=eqtb[24537].hh.rh;
if eqtb[28516].int<=0 then{1029:}begin r:=mem[memtop].hh.rh;
while r<>memtop do begin if mem[r+2].hh.lh<>-1073741823 then begin n:=
mem[r].hh.b1;ensurevbox(n);
if eqtb[25326+n].hh.rh=-1073741823 then eqtb[25326+n].hh.rh:=newnullbox;
p:=eqtb[25326+n].hh.rh+5;
while mem[p].hh.rh<>-1073741823 do p:=mem[p].hh.rh;mem[r+2].hh.rh:=p;
end;r:=mem[r].hh.rh;end;end{:1029};q:=memtop-4;
mem[q].hh.rh:=-1073741823;prevp:=memtop-2;p:=mem[prevp].hh.rh;
while p<>bestpagebreak do begin if mem[p].hh.b0=4 then begin if eqtb[
28516].int<=0 then{1031:}begin r:=mem[memtop].hh.rh;
while mem[r].hh.b1<>mem[p].hh.b1 do r:=mem[r].hh.rh;
if mem[r+2].hh.lh=-1073741823 then wait:=true else begin wait:=false;
n:=mem[p].hh.b1;
case(mem[eqtb[25326+n].hh.rh].hh.b1)of 4,3,1:if mem[p+5].hh.b1<>(mem[
eqtb[25326+n].hh.rh].hh.b1)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1055);
end;begin helpptr:=3;helpline[2]:=1047;helpline[1]:=1056;
helpline[0]:=1049;end;boxerror(n);eqtb[25326+n].hh.rh:=newnullbox;
mem[r+2].hh.rh:=eqtb[25326+n].hh.rh+5;end;
others:mem[eqtb[25326+n].hh.rh].hh.b1:=mem[p+5].hh.b1;end;
s:=mem[r+2].hh.rh;mem[s].hh.rh:=mem[p+4].hh.lh;
if mem[r+2].hh.lh=p then{1032:}begin if mem[r].hh.b0=1 then if(mem[r+1].
hh.lh=p)and(mem[r+1].hh.rh<>-1073741823)then begin while mem[s].hh.rh<>
mem[r+1].hh.rh do s:=mem[s].hh.rh;mem[s].hh.rh:=-1073741823;
eqtb[24537].hh.rh:=mem[p+4].hh.rh;
mem[p+4].hh.lh:=prunepagetop(mem[r+1].hh.rh);
if mem[p+4].hh.lh<>-1073741823 then begin tempptr:=vpackage(mem[p+4].hh.
lh,0,1,1073741823);mem[p+3].int:=mem[tempptr+3].int+mem[tempptr+2].int;
deleteglueref(mem[tempptr+7].hh.rh);deleteglueref(mem[tempptr+7].hh.lh);
freenode(tempptr,10);wait:=true;end;end;mem[r+2].hh.lh:=-1073741823;
n:=mem[r].hh.b1;tempptr:=mem[eqtb[25326+n].hh.rh+5].hh.rh;
deleteglueref(mem[eqtb[25326+n].hh.rh+7].hh.rh);
deleteglueref(mem[eqtb[25326+n].hh.rh+7].hh.lh);
flushnodelist(mem[eqtb[25326+n].hh.rh].hh.rh);
freenode(eqtb[25326+n].hh.rh,10);
eqtb[25326+n].hh.rh:=vpackage(tempptr,0,1,1073741823);
mem[eqtb[25326+n].hh.rh].hh.b1:=mem[p+5].hh.b1;
end{:1032}else begin while mem[s].hh.rh<>-1073741823 do s:=mem[s].hh.rh;
mem[r+2].hh.rh:=s;end;end;{1033:}mem[prevp].hh.rh:=mem[p].hh.rh;
mem[p].hh.rh:=-1073741823;if wait then begin mem[q].hh.rh:=p;q:=p;
incr(insertpenalties);end else begin deleteglueref(mem[p+4].hh.rh);
freenode(p,6);end;p:=prevp{:1033};end{:1031};
end else if mem[p].hh.b0=6 then{1027:}begin if curmark[1]=-1073741823
then begin curmark[1]:=mem[p+1].int;incr(mem[curmark[1]].hh.lh);end;
if curmark[2]<>-1073741823 then deletetokenref(curmark[2]);
curmark[2]:=mem[p+1].int;incr(mem[curmark[2]].hh.lh);end{:1027};
prevp:=p;p:=mem[prevp].hh.rh;end;eqtb[24537].hh.rh:=savesplittopskip;
{1028:}if p<>-1073741823 then begin if mem[memtop-1].hh.rh=-1073741823
then if nestptr=0 then curlist.tailfield:=pagetail else nest[0].
tailfield:=pagetail;mem[pagetail].hh.rh:=mem[memtop-1].hh.rh;
mem[memtop-1].hh.rh:=p;mem[prevp].hh.rh:=-1073741823;end;
savevbadness:=eqtb[28489].int;eqtb[28489].int:=10000;
savevfuzz:=eqtb[29047].int;eqtb[29047].int:=1073741823;
eqtb[25581].hh.rh:=vpackage(mem[memtop-2].hh.rh,bestsize,0,pagemaxdepth)
;mem[eqtb[25581].hh.rh].hh.b1:=pagedir;eqtb[28489].int:=savevbadness;
eqtb[29047].int:=savevfuzz;
if lastglue<>1073741823 then deleteglueref(lastglue);
{1002:}pagecontents:=0;pagetail:=memtop-2;
mem[memtop-2].hh.rh:=-1073741823;lastglue:=1073741823;lastpenalty:=0;
lastkern:=0;pagesofar[7]:=0;pagemaxdepth:=0{:1002};
if q<>memtop-4 then begin mem[memtop-2].hh.rh:=mem[memtop-4].hh.rh;
pagetail:=q;end{:1028};{1030:}r:=mem[memtop].hh.rh;
while r<>memtop do begin q:=mem[r].hh.rh;freenode(r,4);r:=q;end;
mem[memtop].hh.rh:=memtop{:1030}{:1025};
if(curmark[0]<>-1073741823)and(curmark[1]=-1073741823)then begin curmark
[1]:=curmark[0];incr(mem[curmark[0]].hh.lh);end;
if eqtb[25061].hh.rh<>-1073741823 then if deadcycles>=eqtb[28502].int
then{1035:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1064);
end;printint(deadcycles);print(1065);begin helpptr:=3;helpline[2]:=1066;
helpline[1]:=1067;helpline[0]:=1068;end;error;
end{:1035}else{1036:}begin outputactive:=true;incr(deadcycles);pushnest;
curlist.modefield:=-1;curlist.auxfield.int:=-65536000;
curlist.mlfield:=-line;begintokenlist(eqtb[25061].hh.rh,6);
newsavelevel(8);normalparagraph;scanleftbrace;goto 10;end{:1036};
{1034:}begin if mem[memtop-2].hh.rh<>-1073741823 then begin if mem[
memtop-1].hh.rh=-1073741823 then if nestptr=0 then curlist.tailfield:=
pagetail else nest[0].tailfield:=pagetail else mem[pagetail].hh.rh:=mem[
memtop-1].hh.rh;mem[memtop-1].hh.rh:=mem[memtop-2].hh.rh;
mem[memtop-2].hh.rh:=-1073741823;pagetail:=memtop-2;end;
shipout(eqtb[25581].hh.rh);eqtb[25581].hh.rh:=-1073741823;end{:1034};
10:end;{:1023}procedure buildpage;label 10,30,31,22,80,90;
var p:halfword;q,r:halfword;b,c:integer;pi:integer;n:0..255;
delta,h,w:scaled;
begin if(mem[memtop-1].hh.rh=-1073741823)or outputactive then goto 10;
repeat 22:p:=mem[memtop-1].hh.rh;
{1007:}if lastglue<>1073741823 then deleteglueref(lastglue);
lastpenalty:=0;lastkern:=0;
if mem[p].hh.b0=12 then begin lastglue:=mem[p+1].hh.lh;
incr(mem[lastglue].hh.rh);end else begin lastglue:=1073741823;
if mem[p].hh.b0=14 then lastpenalty:=mem[p+1].int else if mem[p].hh.b0=
13 then lastkern:=mem[p+1].int;end{:1007};
{1008:}{1011:}case mem[p].hh.b0 of 0,1,2,3:if pagecontents<2 then{1012:}
begin if pagecontents=0 then freezepagespecs(2)else pagecontents:=2;
q:=newskipparam(9);
if mem[tempptr+1].int>mem[p+3].int then mem[tempptr+1].int:=mem[tempptr
+1].int-mem[p+3].int else mem[tempptr+1].int:=0;mem[q].hh.rh:=p;
mem[memtop-1].hh.rh:=q;goto 22;
end{:1012}else{1013:}begin pagesofar[1]:=pagesofar[1]+pagesofar[7]+mem[p
+3].int;pagesofar[7]:=mem[p+2].int;goto 80;end{:1013};
10:{1377:}goto 80{:1377};
12:if pagecontents<2 then goto 31 else if(mem[pagetail].hh.b0<11)then pi
:=0 else goto 90;
13:if pagecontents<2 then goto 31 else if mem[p].hh.rh=-1073741823 then
goto 10 else if mem[mem[p].hh.rh].hh.b0=12 then pi:=0 else goto 90;
14:if pagecontents<2 then goto 31 else pi:=mem[p+1].int;6:goto 80;
4:{1019:}begin if pagecontents=0 then freezepagespecs(1);
n:=mem[p].hh.b1;r:=memtop;
while n>=mem[mem[r].hh.rh].hh.b1 do r:=mem[r].hh.rh;n:=n;
if mem[r].hh.b1<>n then{1020:}begin q:=getnode(4);
mem[q].hh.rh:=mem[r].hh.rh;mem[r].hh.rh:=q;r:=q;mem[r].hh.b1:=n;
mem[r].hh.b0:=0;ensurevbox(n);
if eqtb[25326+n].hh.rh=-1073741823 then mem[r+3].int:=0 else begin if
mem[p+5].hh.b1<>(mem[eqtb[25326+n].hh.rh].hh.b1)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1055);
end;begin helpptr:=3;helpline[2]:=1047;helpline[1]:=1056;
helpline[0]:=1049;end;
boxerror(n)end else mem[r+3].int:=mem[eqtb[25326+n].hh.rh+3].int+mem[
eqtb[25326+n].hh.rh+2].int;end;mem[r+2].hh.lh:=-1073741823;
q:=eqtb[24548+n].hh.rh;
if eqtb[28526+n].int=1000 then h:=mem[r+3].int else h:=xovern(mem[r+3].
int,1000)*eqtb[28526+n].int;pagesofar[0]:=pagesofar[0]-h-mem[q+1].int;
pagesofar[2+mem[q].hh.b0]:=pagesofar[2+mem[q].hh.b0]+mem[q+2].int;
pagesofar[6]:=pagesofar[6]+mem[q+3].int;
if(mem[q].hh.b1<>0)and(mem[q+3].int<>0)then begin begin if interaction=3
then;if filelineerrorstylep then printfileline else printnl(263);
print(1057);end;printesc(414);printint(n);begin helpptr:=3;
helpline[2]:=1058;helpline[1]:=1059;helpline[0]:=979;end;error;end;
end{:1020};
if mem[r].hh.b0=1 then insertpenalties:=insertpenalties+mem[p+1].int
else begin mem[r+2].hh.rh:=p;
delta:=pagesofar[0]-pagesofar[1]-pagesofar[7]+pagesofar[6];
if eqtb[28526+n].int=1000 then h:=mem[p+3].int else h:=xovern(mem[p+3].
int,1000)*eqtb[28526+n].int;
if((h<=0)or(h<=delta))and(mem[p+3].int+mem[r+3].int<=eqtb[29061+n].int)
then begin pagesofar[0]:=pagesofar[0]-h;
mem[r+3].int:=mem[r+3].int+mem[p+3].int;
end else{1021:}begin if eqtb[28526+n].int<=0 then w:=1073741823 else
begin w:=pagesofar[0]-pagesofar[1]-pagesofar[7];
if eqtb[28526+n].int<>1000 then w:=xovern(w,eqtb[28526+n].int)*1000;end;
if w>eqtb[29061+n].int-mem[r+3].int then w:=eqtb[29061+n].int-mem[r+3].
int;q:=vertbreak(mem[p+4].hh.lh,w,mem[p+2].int);
mem[r+3].int:=mem[r+3].int+bestheightplusdepth;
ifdef('STAT')if eqtb[28495].int>0 then{1022:}begin begindiagnostic;
printnl(1060);printint(n);print(1061);printscaled(w);printchar(44);
printscaled(bestheightplusdepth);print(988);
if q=-1073741823 then printint(-10000)else if mem[q].hh.b0=14 then
printint(mem[q+1].int)else printchar(48);enddiagnostic(false);
end{:1022};
endif('STAT')if eqtb[28526+n].int<>1000 then bestheightplusdepth:=xovern
(bestheightplusdepth,1000)*eqtb[28526+n].int;
pagesofar[0]:=pagesofar[0]-bestheightplusdepth;mem[r].hh.b0:=1;
mem[r+1].hh.rh:=q;mem[r+1].hh.lh:=p;
if q=-1073741823 then insertpenalties:=insertpenalties-10000 else if mem
[q].hh.b0=14 then insertpenalties:=insertpenalties+mem[q+1].int;
end{:1021};end;goto 80;end{:1019};others:confusion(1050)end{:1011};
{1016:}if pi<10000 then begin{1018:}if pagesofar[1]<pagesofar[0]then if(
pagesofar[3]<>0)or(pagesofar[4]<>0)or(pagesofar[5]<>0)then b:=0 else b:=
badness(pagesofar[0]-pagesofar[1],pagesofar[2])else if pagesofar[1]-
pagesofar[0]>pagesofar[6]then b:=1073741823 else b:=badness(pagesofar[1]
-pagesofar[0],pagesofar[6]){:1018};
if b<1073741823 then if pi<=-10000 then c:=pi else if b<10000 then c:=b+
pi+insertpenalties else c:=100000 else c:=b;
if insertpenalties>=10000 then c:=1073741823;
ifdef('STAT')if eqtb[28495].int>0 then{1017:}begin begindiagnostic;
printnl(37);print(984);printtotals;print(1053);
printscaled(pagesofar[0]);print(987);
if b=1073741823 then printchar(42)else printint(b);print(988);
printint(pi);print(1054);
if c=1073741823 then printchar(42)else printint(c);
if c<=leastpagecost then printchar(35);enddiagnostic(false);end{:1017};
endif('STAT')if c<=leastpagecost then begin bestpagebreak:=p;
bestsize:=pagesofar[0];leastpagecost:=c;r:=mem[memtop].hh.rh;
while r<>memtop do begin mem[r+2].hh.lh:=mem[r+2].hh.rh;r:=mem[r].hh.rh;
end;end;if(c=1073741823)or(pi<=-10000)then begin fireup(p);
if outputactive then goto 10;goto 30;end;end{:1016};
if(mem[p].hh.b0<12)or(mem[p].hh.b0>13)then goto 80;
90:{1015:}if mem[p].hh.b0=13 then q:=p else begin q:=mem[p+1].hh.lh;
pagesofar[2+mem[q].hh.b0]:=pagesofar[2+mem[q].hh.b0]+mem[q+2].int;
pagesofar[6]:=pagesofar[6]+mem[q+3].int;
if(mem[q].hh.b1<>0)and(mem[q+3].int<>0)then begin begin if interaction=3
then;if filelineerrorstylep then printfileline else printnl(263);
print(1051);end;begin helpptr:=4;helpline[3]:=1052;helpline[2]:=1020;
helpline[1]:=1021;helpline[0]:=979;end;error;r:=newspec(q);
mem[r].hh.b1:=0;deleteglueref(q);mem[p+1].hh.lh:=r;q:=r;end;end;
pagesofar[1]:=pagesofar[1]+pagesofar[7]+mem[q+1].int;
pagesofar[7]:=0{:1015};
80:{1014:}if pagesofar[7]>pagemaxdepth then begin pagesofar[1]:=
pagesofar[1]+pagesofar[7]-pagemaxdepth;pagesofar[7]:=pagemaxdepth;end;
{:1014};{1009:}mem[pagetail].hh.rh:=p;pagetail:=p;
mem[memtop-1].hh.rh:=mem[p].hh.rh;mem[p].hh.rh:=-1073741823;
goto 30{:1009};31:{1010:}mem[memtop-1].hh.rh:=mem[p].hh.rh;
mem[p].hh.rh:=-1073741823;flushnodelist(p){:1010};30:{:1008};
until mem[memtop-1].hh.rh=-1073741823;
{1006:}if nestptr=0 then curlist.tailfield:=memtop-1 else nest[0].
tailfield:=memtop-1{:1006};10:end;
{:1005}{1041:}{1055:}procedure appspace;var q:halfword;
begin if(curlist.auxfield.hh.lh>=2000)and(eqtb[24540].hh.rh<>membot)then
q:=newparamglue(13)else begin if eqtb[24539].hh.rh<>membot then mainp:=
eqtb[24539].hh.rh else{1054:}begin mainp:=fontglue[eqtb[25582].hh.rh];
if mainp=-1073741823 then begin mainp:=newspec(membot);
maink:=parambase[eqtb[25582].hh.rh]+2;
mem[mainp+1].int:=fontinfo[maink].int;
mem[mainp+2].int:=fontinfo[maink+1].int;
mem[mainp+3].int:=fontinfo[maink+2].int;
fontglue[eqtb[25582].hh.rh]:=mainp;end;end{:1054};mainp:=newspec(mainp);
{1056:}if curlist.auxfield.hh.lh>=2000 then mem[mainp+1].int:=mem[mainp
+1].int+fontinfo[7+parambase[eqtb[25582].hh.rh]].int;
mem[mainp+2].int:=xnoverd(mem[mainp+2].int,curlist.auxfield.hh.lh,1000);
mem[mainp+3].int:=xnoverd(mem[mainp+3].int,1000,curlist.auxfield.hh.lh)
{:1056};q:=newglue(mainp);mem[mainp].hh.rh:=-1073741823;end;
if not(curlist.tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)
then begin mem[curlist.pnodefield].hh.rh:=q;
mem[q].hh.rh:=curlist.tailfield;curlist.pnodefield:=q;
end else begin mem[curlist.tailfield].hh.rh:=q;curlist.tailfield:=q;
end end;{:1055}{1059:}procedure insertdollarsign;begin backinput;
curtok:=804;begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1076);
end;begin helpptr:=2;helpline[1]:=1077;helpline[0]:=1078;end;inserror;
end;{:1059}{1061:}procedure youcant;begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(726);
end;printcmdchr(curcmd,curchr);printinmode(curlist.modefield);end;
{:1061}{1062:}procedure reportillegalcase;begin youcant;
begin helpptr:=4;helpline[3]:=1079;helpline[2]:=1080;helpline[1]:=1081;
helpline[0]:=1082;end;error;end;
{:1062}{1063:}function privileged:boolean;
begin if curlist.modefield>0 then privileged:=true else begin
reportillegalcase;privileged:=false;end;end;
{:1063}{1066:}function itsallover:boolean;label 10;
begin if privileged then begin if(memtop-2=pagetail)and(curlist.
headfield=curlist.tailfield)and(deadcycles=0)then begin itsallover:=true
;goto 10;end;backinput;begin mem[curlist.tailfield].hh.rh:=newnullbox;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield+1].int:=eqtb[29041].int;
begin mem[curlist.tailfield].hh.rh:=newglue(membot+8);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
begin mem[curlist.tailfield].hh.rh:=newpenalty(-1073741824);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;buildpage;end;
itsallover:=false;10:end;{:1066}{1072:}procedure appendglue;
var s:smallnumber;begin s:=curchr;case s of 0:curval:=membot+4;
1:curval:=membot+8;2:curval:=membot+12;3:curval:=membot+16;
4:scanglue(2);5:scanglue(3);end;
begin mem[curlist.tailfield].hh.rh:=newglue(curval);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
inhibitglueflag:=false;if s>=4 then begin decr(mem[curval].hh.rh);
if s>4 then mem[curlist.tailfield].hh.b1:=99;end;end;
{:1072}{1073:}procedure appendkern;var s:quarterword;begin s:=curchr;
scandimen(s=99,false,false);inhibitglueflag:=false;
if not(curlist.tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)
then begin begin mem[curlist.pnodefield].hh.rh:=newkern(curval);
mem[mem[curlist.pnodefield].hh.rh].hh.rh:=curlist.tailfield;
curlist.pnodefield:=mem[curlist.pnodefield].hh.rh;end;
mem[curlist.pnodefield].hh.b1:=s;
end else begin begin mem[curlist.tailfield].hh.rh:=newkern(curval);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=s;end;end;{:1073}{1076:}procedure offsave;
var p:halfword;
begin if curgroup=0 then{1078:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(832);
end;printcmdchr(curcmd,curchr);begin helpptr:=1;helpline[0]:=1101;end;
error;end{:1078}else begin backinput;p:=getavail;mem[memtop-3].hh.rh:=p;
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(666);
end;{1077:}case curgroup of 14:begin mem[p].hh.lh:=536886427;
printesc(552);end;15:begin mem[p].hh.lh:=804;printchar(36);end;
16:begin mem[p].hh.lh:=536886428;mem[p].hh.rh:=getavail;p:=mem[p].hh.rh;
mem[p].hh.lh:=3118;printesc(1100);end;others:begin mem[p].hh.lh:=637;
printchar(125);end end{:1077};print(667);
begintokenlist(mem[memtop-3].hh.rh,4);begin helpptr:=5;
helpline[4]:=1095;helpline[3]:=1096;helpline[2]:=1097;helpline[1]:=1098;
helpline[0]:=1099;end;error;end;end;
{:1076}{1081:}procedure extrarightbrace;
begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1106);
end;case curgroup of 14:printesc(552);15:printchar(36);16:printesc(933);
end;begin helpptr:=5;helpline[4]:=1107;helpline[3]:=1108;
helpline[2]:=1109;helpline[1]:=1110;helpline[0]:=1111;end;error;
incr(alignstate);end;{:1081}{1082:}procedure normalparagraph;
begin if eqtb[28481].int<>0 then eqworddefine(28481,0);
if eqtb[29055].int<>0 then eqworddefine(29055,0);
if eqtb[28503].int<>1 then eqworddefine(28503,1);
if eqtb[25060].hh.rh<>-1073741823 then eqdefine(25060,133,-1073741823);
end;{:1082}{1087:}procedure boxend(boxcontext:integer);var p:halfword;
q:halfword;
begin if boxcontext<1073741824 then{1088:}begin if curbox<>-1073741823
then begin p:=mem[curbox].hh.rh;mem[curbox].hh.rh:=-1073741823;
while p<>-1073741823 do begin q:=p;p:=mem[p].hh.rh;
if(mem[q].hh.b1)=abs(curlist.dirfield)then begin mem[q+5].hh.rh:=curbox;
curbox:=q;mem[curbox].hh.rh:=-1073741823;
end else begin deleteglueref(mem[q+7].hh.rh);
deleteglueref(mem[q+7].hh.lh);freenode(q,10);end;end;
if(mem[curbox].hh.b1)<>abs(curlist.dirfield)then curbox:=newdirnode(
curbox,abs(curlist.dirfield));mem[curbox+4].int:=boxcontext;
if abs(curlist.modefield)=1 then begin appendtovlist(curbox);
if adjusttail<>-1073741823 then begin if memtop-5<>adjusttail then begin
mem[curlist.tailfield].hh.rh:=mem[memtop-5].hh.rh;
curlist.tailfield:=adjusttail;end;adjusttail:=-1073741823;end;
if curlist.modefield>0 then buildpage;
end else begin if abs(curlist.modefield)=117 then curlist.auxfield.hh.lh
:=1000 else begin p:=newnoad;mem[p+1].hh.rh:=3;mem[p+1].hh.lh:=curbox;
curbox:=p;end;mem[curlist.tailfield].hh.rh:=curbox;
curlist.tailfield:=curbox;end;end;
end{:1088}else if boxcontext<1073742336 then{1089:}if boxcontext<
1073742080 then eqdefine(-1073716498+boxcontext,134,curbox)else
geqdefine(-1073716754+boxcontext,134,curbox){:1089}else if curbox<>
-1073741823 then if boxcontext>1073742336 then{1090:}begin{415:}repeat
getxtoken;until(curcmd<>10)and(curcmd<>0){:415};
if((curcmd=30)and(abs(curlist.modefield)<>1))or((curcmd=31)and(abs(
curlist.modefield)=1))then begin appendglue;
mem[curlist.tailfield].hh.b1:=boxcontext-(1073742237);
if mem[curbox].hh.b0<=2 then begin p:=mem[curbox].hh.rh;
mem[curbox].hh.rh:=-1073741823;while p<>-1073741823 do begin q:=p;
p:=mem[p].hh.rh;
if(mem[q].hh.b1)=abs(curlist.dirfield)then begin mem[q+5].hh.rh:=curbox;
curbox:=q;mem[curbox].hh.rh:=-1073741823;
end else begin deleteglueref(mem[q+7].hh.rh);
deleteglueref(mem[q+7].hh.lh);freenode(q,10);end;end;
if(mem[curbox].hh.b1)<>abs(curlist.dirfield)then curbox:=newdirnode(
curbox,abs(curlist.dirfield));end;
mem[curlist.tailfield+1].hh.rh:=curbox;
end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1134);
end;begin helpptr:=3;helpline[2]:=1135;helpline[1]:=1136;
helpline[0]:=1137;end;backerror;flushnodelist(curbox);end;
end{:1090}else shipout(curbox);end;
{:1087}{1091:}procedure beginbox(boxcontext:integer);label 10,30;
var p,q:halfword;r:halfword;fd:boolean;disp,pdisp:scaled;adir:eightbits;
tx:halfword;m:quarterword;k:halfword;n:eightbits;
begin case curchr of 0:begin scaneightbitint;
curbox:=eqtb[25326+curval].hh.rh;eqtb[25326+curval].hh.rh:=-1073741823;
end;1:begin scaneightbitint;
curbox:=copynodelist(eqtb[25326+curval].hh.rh);end;
2:{1092:}begin curbox:=-1073741823;
if abs(curlist.modefield)=233 then begin youcant;begin helpptr:=1;
helpline[0]:=1138;end;error;
end else if(curlist.modefield=1)and(curlist.headfield=curlist.tailfield)
then begin youcant;begin helpptr:=2;helpline[1]:=1139;helpline[0]:=1140;
end;error;end else begin tx:=curlist.tailfield;
if not(tx>=himemmin)then if mem[tx].hh.b0=5 then begin tx:=curlist.
pnodefield;if not(tx>=himemmin)then if mem[tx].hh.b0=5 then goto 30;end;
if not(tx>=himemmin)and(curlist.headfield<>tx)then if(mem[tx].hh.b0=0)or
(mem[tx].hh.b0=1)or(mem[tx].hh.b0=2)then{1093:}begin q:=curlist.
headfield;p:=-1073741823;disp:=0;pdisp:=0;repeat r:=p;p:=q;fd:=false;
if not(q>=himemmin)then if mem[q].hh.b0=9 then begin for m:=1 to mem[q].
hh.b1 do p:=mem[p].hh.rh;if p=tx then goto 30;
end else if mem[q].hh.b0=5 then begin pdisp:=disp;disp:=mem[q+1].int;
fd:=true;end;q:=mem[p].hh.rh;until q=tx;q:=mem[tx].hh.rh;
mem[p].hh.rh:=q;mem[tx].hh.rh:=-1073741823;
if q=-1073741823 then curlist.tailfield:=p else if fd then begin curlist
.pnodefield:=r;curlist.pdispfield:=pdisp;mem[p].hh.rh:=-1073741823;
curlist.tailfield:=p;mem[p+1].int:=mem[q+1].int;freenode(q,2);
end else curlist.pnodefield:=p;curbox:=tx;mem[curbox+4].int:=0;
if mem[curbox].hh.b0=2 then begin mem[mem[curbox+5].hh.rh].hh.rh:=curbox
;curbox:=mem[curbox+5].hh.rh;
mem[mem[curbox].hh.rh+5].hh.rh:=-1073741823;
end else if(mem[curbox].hh.b1)=0 then mem[curbox].hh.b1:=abs(curlist.
dirfield);end{:1093};30:end;end{:1092};3:{1094:}begin scaneightbitint;
n:=curval;if not scankeyword(898)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1141);
end;begin helpptr:=2;helpline[1]:=1142;helpline[0]:=1143;end;error;end;
scandimen(false,false,false);curbox:=vsplit(n,curval);end{:1094};
others:{1095:}begin k:=curchr-4;savestack[saveptr+0].int:=boxcontext;
adir:=curlist.adjdirfield;
if k=117 then if(boxcontext<1073741824)and(abs(curlist.modefield)=1)then
begin adir:=abs(curlist.dirfield);scanspec(3,true);
end else scanspec(2,true)else begin if k=1 then scanspec(4,true)else
begin scanspec(5,true);k:=1;end;normalparagraph;end;pushnest;
curlist.modefield:=-k;curlist.adjdirfield:=adir;
if k=1 then begin curlist.auxfield.int:=-65536000;
if eqtb[25066].hh.rh<>-1073741823 then begintokenlist(eqtb[25066].hh.rh,
11);end else begin curlist.auxfield.hh.lh:=1000;
if eqtb[25065].hh.rh<>-1073741823 then begintokenlist(eqtb[25065].hh.rh,
10);end;goto 10;end{:1095}end;boxend(boxcontext);10:end;
{:1091}{1096:}procedure scanbox(boxcontext:integer);
begin{415:}repeat getxtoken;until(curcmd<>10)and(curcmd<>0){:415};
if curcmd=24 then beginbox(boxcontext)else if(boxcontext>=1073742337)and
((curcmd=40)or(curcmd=39))then begin curbox:=scanrulespec;
boxend(boxcontext);end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1144);
end;begin helpptr:=3;helpline[2]:=1145;helpline[1]:=1146;
helpline[0]:=1147;end;backerror;end;end;
{:1096}{1098:}procedure package(c:smallnumber);var h:scaled;p:halfword;
d:scaled;begin d:=eqtb[29045].int;deleteglueref(curkanjiskip);
deleteglueref(curxkanjiskip);
if eqtb[25633].hh.rh>0 then curkanjiskip:=eqtb[24542].hh.rh else
curkanjiskip:=membot;
if eqtb[25634].hh.rh>0 then curxkanjiskip:=eqtb[24543].hh.rh else
curxkanjiskip:=membot;incr(mem[curkanjiskip].hh.rh);
incr(mem[curxkanjiskip].hh.rh);unsave;saveptr:=saveptr-3;
if curlist.modefield=-117 then begin curbox:=hpack(mem[curlist.headfield
].hh.rh,savestack[saveptr+2].int,savestack[saveptr+1].int);
mem[curbox].hh.b1:=abs(curlist.dirfield);popnest;
end else begin curbox:=vpackage(mem[curlist.headfield].hh.rh,savestack[
saveptr+2].int,savestack[saveptr+1].int,d);
mem[curbox].hh.b1:=abs(curlist.dirfield);popnest;
if c=4 then{1099:}begin h:=0;p:=mem[curbox+5].hh.rh;
if p<>-1073741823 then if mem[p].hh.b0<=3 then h:=mem[p+3].int;
mem[curbox+2].int:=mem[curbox+2].int-h+mem[curbox+3].int;
mem[curbox+3].int:=h;end{:1099};end;boxend(savestack[saveptr+0].int);
end;{:1098}{1103:}function normmin(h:integer):smallnumber;
begin if h<=0 then normmin:=1 else if h>=63 then normmin:=63 else
normmin:=h;end;procedure newgraf(indented:boolean);
begin curlist.pgfield:=0;
if(curlist.modefield=1)or(curlist.headfield<>curlist.tailfield)then
begin mem[curlist.tailfield].hh.rh:=newparamglue(2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
inhibitglueflag:=false;pushnest;
curlist.adjdirfield:=abs(curlist.dirfield);curlist.modefield:=117;
curlist.auxfield.hh.lh:=1000;
if eqtb[28513].int<=0 then curlang:=0 else if eqtb[28513].int>255 then
curlang:=0 else curlang:=eqtb[28513].int;
curlist.auxfield.hh.rh:=curlang;
curlist.pgfield:=(normmin(eqtb[28514].int)*64+normmin(eqtb[28515].int))
*65536+curlang;if indented then begin curlist.tailfield:=newnullbox;
mem[curlist.headfield].hh.rh:=curlist.tailfield;
mem[curlist.tailfield+1].int:=eqtb[29038].int;
if(insertsrcspecialeverypar)then insertsrcspecial;end;
if eqtb[25062].hh.rh<>-1073741823 then begintokenlist(eqtb[25062].hh.rh,
7);if nestptr=1 then buildpage;end;
{:1103}{1105:}procedure indentinhmode;var p,q:halfword;
begin if curchr>0 then begin p:=newnullbox;
mem[p+1].int:=eqtb[29038].int;
if abs(curlist.modefield)=117 then curlist.auxfield.hh.lh:=1000 else
begin q:=newnoad;mem[q+1].hh.rh:=2;mem[q+1].hh.lh:=p;p:=q;end;
begin mem[curlist.tailfield].hh.rh:=p;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;end;end;
{:1105}{1107:}procedure headforvmode;
begin if curlist.modefield<0 then if curcmd<>40 then offsave else begin
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(726);
end;printesc(559);print(1150);begin helpptr:=2;helpline[1]:=1151;
helpline[0]:=1152;end;error;end else begin backinput;curtok:=partoken;
backinput;curinput.indexfield:=4;end;end;
{:1107}{1108:}procedure endgraf;
begin if curlist.modefield=117 then begin if curlist.headfield=curlist.
tailfield then popnest else begin adjusthlist(curlist.headfield,true);
linebreak(eqtb[28468].int)end;normalparagraph;errorcount:=0;end;end;
{:1108}{1111:}procedure begininsertoradjust;
begin if curcmd=42 then curval:=255 else begin scaneightbitint;
if curval=255 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1153);
end;printesc(336);printint(255);begin helpptr:=1;helpline[0]:=1154;end;
error;curval:=0;end;end;savestack[saveptr+0].int:=curval;incr(saveptr);
newsavelevel(11);scanleftbrace;normalparagraph;pushnest;
curlist.modefield:=-1;curlist.dirfield:=curlist.adjdirfield;
curlist.auxfield.int:=-65536000;end;{:1111}{1113:}procedure makemark;
var p:halfword;begin p:=scantoks(false,true);p:=getnode(2);
mem[p].hh.b0:=6;mem[p].hh.b1:=0;mem[p+1].int:=defref;
if not(curlist.tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)
then begin mem[curlist.pnodefield].hh.rh:=p;
mem[mem[curlist.pnodefield].hh.rh].hh.rh:=curlist.tailfield;
curlist.pnodefield:=mem[curlist.pnodefield].hh.rh;
end else begin mem[curlist.tailfield].hh.rh:=p;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;end;
{:1113}{1115:}procedure appendpenalty;begin scanint;
if not(curlist.tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)
then begin mem[curlist.pnodefield].hh.rh:=newpenalty(curval);
mem[mem[curlist.pnodefield].hh.rh].hh.rh:=curlist.tailfield;
curlist.pnodefield:=mem[curlist.pnodefield].hh.rh;
end else begin mem[curlist.tailfield].hh.rh:=newpenalty(curval);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
if curlist.modefield=1 then buildpage;end;
{:1115}{1117:}procedure deletelast;label 10;var p,q:halfword;r:halfword;
fd:boolean;disp,pdisp:scaled;tx:halfword;m:quarterword;
begin if(curlist.modefield=1)and(curlist.tailfield=curlist.headfield)
then{1118:}begin if(curchr<>12)or(lastglue<>1073741823)then begin
youcant;begin helpptr:=2;helpline[1]:=1139;helpline[0]:=1157;end;
if curchr=13 then helpline[0]:=(1158)else if curchr<>12 then helpline[0]
:=(1159);error;end;end{:1118}else begin tx:=curlist.tailfield;
if not(tx>=himemmin)then if mem[tx].hh.b0=5 then begin tx:=curlist.
pnodefield;if not(tx>=himemmin)then if mem[tx].hh.b0=5 then goto 10;end;
if not(tx>=himemmin)then if mem[tx].hh.b0=curchr then begin q:=curlist.
headfield;p:=-1073741823;disp:=0;pdisp:=0;repeat r:=p;p:=q;fd:=false;
if not(q>=himemmin)then if mem[q].hh.b0=9 then begin for m:=1 to mem[q].
hh.b1 do p:=mem[p].hh.rh;if p=tx then goto 10;
end else if mem[q].hh.b0=5 then begin pdisp:=disp;disp:=mem[q+1].int;
fd:=true;end;q:=mem[p].hh.rh;until q=tx;q:=mem[tx].hh.rh;
mem[p].hh.rh:=q;mem[tx].hh.rh:=-1073741823;
if q=-1073741823 then curlist.tailfield:=p else if fd then begin curlist
.pnodefield:=r;curlist.pdispfield:=pdisp;mem[p].hh.rh:=-1073741823;
curlist.tailfield:=p;mem[p+1].int:=mem[q+1].int;freenode(q,2);
end else curlist.pnodefield:=p;flushnodelist(tx);end;end;10:end;
{:1117}{1122:}procedure unpackage;label 10;var p:halfword;c:0..1;
disp:scaled;begin c:=curchr;scaneightbitint;p:=eqtb[25326+curval].hh.rh;
if p=-1073741823 then goto 10;if mem[p].hh.b0=2 then p:=mem[p+5].hh.rh;
if(abs(curlist.modefield)=233)or((abs(curlist.modefield)=1)and(mem[p].hh
.b0<>1))or((abs(curlist.modefield)=117)and(mem[p].hh.b0<>0))then begin
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1167);
end;begin helpptr:=3;helpline[2]:=1168;helpline[1]:=1169;
helpline[0]:=1170;end;error;goto 10;end;
case(mem[p].hh.b1)of 4,3,1:if abs(curlist.dirfield)<>(mem[p].hh.b1)then
begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1171);
end;begin helpptr:=2;helpline[1]:=1168;helpline[0]:=1172;end;error;
goto 10;end;end;disp:=0;
if c=1 then mem[curlist.tailfield].hh.rh:=copynodelist(mem[p+5].hh.rh)
else begin if mem[eqtb[25326+curval].hh.rh].hh.b0=2 then begin
deleteglueref(mem[eqtb[25326+curval].hh.rh+7].hh.rh);
deleteglueref(mem[eqtb[25326+curval].hh.rh+7].hh.lh);
freenode(eqtb[25326+curval].hh.rh,10);end;flushnodelist(mem[p].hh.rh);
mem[curlist.tailfield].hh.rh:=mem[p+5].hh.rh;
eqtb[25326+curval].hh.rh:=-1073741823;deleteglueref(mem[p+7].hh.rh);
deleteglueref(mem[p+7].hh.lh);freenode(p,10);end;
while mem[curlist.tailfield].hh.rh<>-1073741823 do begin p:=curlist.
tailfield;curlist.tailfield:=mem[curlist.tailfield].hh.rh;
if not(curlist.tailfield>=himemmin)then case mem[curlist.tailfield].hh.
b0 of 12:if(mem[curlist.tailfield].hh.b1=16)or(mem[curlist.tailfield].hh
.b1=17)then begin mem[p].hh.rh:=mem[curlist.tailfield].hh.rh;
deleteglueref(mem[curlist.tailfield+1].hh.lh);
freenode(curlist.tailfield,2);curlist.tailfield:=p;end;
14:if mem[curlist.tailfield].hh.b1=1 then begin mem[p].hh.rh:=mem[
curlist.tailfield].hh.rh;freenode(curlist.tailfield,2);
curlist.tailfield:=p;end;5:begin curlist.pdispfield:=disp;
disp:=mem[curlist.tailfield+1].int;curlist.pnodefield:=p;end;end;end;
10:end;{:1122}{1125:}procedure appenditaliccorrection;label 10;
var p:halfword;f:internalfontnumber;d:halfword;
begin if curlist.tailfield<>curlist.headfield then begin if not(curlist.
tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)then begin d:=
curlist.tailfield;curlist.tailfield:=curlist.pnodefield;
end else d:=-1073741823;
if(curlist.lastjchrfield<>-1073741823)and(mem[curlist.lastjchrfield].hh.
rh=curlist.tailfield)and((curlist.tailfield>=himemmin))then p:=curlist.
lastjchrfield else if(curlist.tailfield>=himemmin)then p:=curlist.
tailfield else if mem[curlist.tailfield].hh.b0=8 then p:=curlist.
tailfield+1 else goto 10;f:=mem[p].hh.b0;
begin mem[curlist.tailfield].hh.rh:=newkern(fontinfo[italicbase[f]+(
fontinfo[charbase[f]+effectivechar(true,f,mem[p].hh.b1)].qqqq.b2)div 4].
int);curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=3;
if d<>-1073741823 then begin curlist.pnodefield:=curlist.tailfield;
begin mem[curlist.tailfield].hh.rh:=d;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;end;end;10:end;
{:1125}{1129:}procedure appenddiscretionary;var c:integer;
begin begin mem[curlist.tailfield].hh.rh:=newdisc;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
if curchr=1 then begin c:=hyphenchar[eqtb[25582].hh.rh];
if c>=0 then if c<256 then mem[curlist.tailfield+1].hh.lh:=newcharacter(
eqtb[25582].hh.rh,c);end else begin incr(saveptr);
savestack[saveptr-1].int:=0;newsavelevel(10);scanleftbrace;pushnest;
curlist.modefield:=-117;curlist.auxfield.hh.lh:=1000;end;end;
{:1129}{1131:}procedure builddiscretionary;label 30,10;var p,q:halfword;
n:integer;begin unsave;{1133:}q:=curlist.headfield;p:=mem[q].hh.rh;n:=0;
while p<>-1073741823 do begin if not(p>=himemmin)then if(mem[p].hh.b0>3)
and(mem[p].hh.b0<>13)and(mem[p].hh.b0<>8)and(mem[p].hh.b0<>5)then if(mem
[p].hh.b0=14)and(mem[p].hh.b1<>0)then begin mem[q].hh.rh:=mem[p].hh.rh;
freenode(p,2);p:=q;end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1179);
end;begin helpptr:=1;helpline[0]:=1180;end;error;begindiagnostic;
printnl(1181);showbox(p);enddiagnostic(true);flushnodelist(p);
mem[q].hh.rh:=-1073741823;goto 30;end;q:=p;p:=mem[q].hh.rh;incr(n);end;
30:{:1133};p:=mem[curlist.headfield].hh.rh;popnest;
case savestack[saveptr-1].int of 0:mem[curlist.tailfield+1].hh.lh:=p;
1:mem[curlist.tailfield+1].hh.rh:=p;
2:{1132:}begin if(n>0)and(abs(curlist.modefield)=233)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1173);
end;printesc(357);begin helpptr:=2;helpline[1]:=1174;helpline[0]:=1175;
end;flushnodelist(p);n:=0;error;
end else mem[curlist.tailfield].hh.rh:=p;
if n<=65535 then mem[curlist.tailfield].hh.b1:=n else begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1176);
end;begin helpptr:=2;helpline[1]:=1177;helpline[0]:=1178;end;error;end;
if n>0 then curlist.tailfield:=q;decr(saveptr);
curlist.pnodefield:=curlist.tailfield;
begin mem[curlist.tailfield].hh.rh:=getnode(2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=5;mem[curlist.tailfield+1].int:=0;
curlist.pdispfield:=0;goto 10;end{:1132};end;
incr(savestack[saveptr-1].int);newsavelevel(10);scanleftbrace;pushnest;
curlist.modefield:=-117;curlist.auxfield.hh.lh:=1000;10:end;
{:1131}{1135:}procedure makeaccent;var s,t:real;disp:scaled;
cx:KANJIcode;p,q,r:halfword;f:internalfontnumber;a,h,x,w,delta:scaled;
i:fourquarters;begin scancharnum;
if checkecharrange(curval)=0 then begin cx:=curval;
if curlist.dirfield=3 then f:=eqtb[25632].hh.rh else f:=eqtb[25631].hh.
rh;p:=newcharacter(f,getjfmpos(cx,f));
if p<>-1073741823 then begin mem[p].hh.rh:=getavail;
mem[mem[p].hh.rh].hh.lh:=cx+eqtb[25892+kcatcodekey(cx)].hh.rh*16777216;
end;end else begin f:=eqtb[25582].hh.rh;p:=newcharacter(f,curval);end;
if p<>-1073741823 then begin x:=fontinfo[5+parambase[f]].int;
s:=fontinfo[1+parambase[f]].int/65536.0;
a:=fontinfo[widthbase[f]+fontinfo[charbase[f]+effectivechar(true,f,mem[p
].hh.b1)].qqqq.b0].int;doassignments;{1136:}q:=-1073741823;
f:=eqtb[25582].hh.rh;cx:=0;
if(curcmd=11)or(curcmd=12)then q:=newcharacter(f,curchr)else if(curcmd>=
16)and(curcmd<=19)then begin if curlist.dirfield=3 then f:=eqtb[25632].
hh.rh else f:=eqtb[25631].hh.rh;cx:=curchr;
end else if curcmd=73 then if checkecharrange(curchr)then q:=
newcharacter(f,curchr)else begin if curlist.dirfield=3 then f:=eqtb[
25632].hh.rh else f:=eqtb[25631].hh.rh;
cx:=curchr end else if curcmd=20 then begin scancharnum;
if checkecharrange(curval)then q:=newcharacter(f,curval)else begin if
curlist.dirfield=3 then f:=eqtb[25632].hh.rh else f:=eqtb[25631].hh.rh;
cx:=curval end end else if curcmd=74 then begin if curlist.dirfield=3
then f:=eqtb[25632].hh.rh else f:=eqtb[25631].hh.rh;
cx:=curchr end else if curcmd=54 then begin scancharnum;
if curlist.dirfield=3 then f:=eqtb[25632].hh.rh else f:=eqtb[25631].hh.
rh;cx:=curval end else backinput;
if curlist.dirfield=3 then begin if fontdir[f]=3 then disp:=0 else if
fontdir[f]=4 then disp:=eqtb[29059].int-eqtb[29060].int else disp:=eqtb[
29059].int end else begin if fontdir[f]=4 then disp:=0 else if fontdir[f
]=3 then disp:=eqtb[29060].int-eqtb[29059].int else disp:=eqtb[29060].
int end;{1503:}begin if not(curlist.tailfield>=himemmin)and(mem[curlist.
tailfield].hh.b0=5)then begin if curlist.pdispfield=disp then begin
freenode(curlist.tailfield,2);curlist.tailfield:=curlist.pnodefield;
mem[curlist.tailfield].hh.rh:=-1073741823;
end else mem[curlist.tailfield+1].int:=disp;
end else if disp<>0 then begin curlist.pnodefield:=curlist.tailfield;
begin mem[curlist.tailfield].hh.rh:=getnode(2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=5;mem[curlist.tailfield+1].int:=disp;
curlist.pdispfield:=disp;end;end;{:1503};
if cx<>0 then begin q:=newcharacter(f,getjfmpos(cx,f));
mem[q].hh.rh:=getavail;
mem[mem[q].hh.rh].hh.lh:=cx+eqtb[25892+kcatcodekey(cx)].hh.rh*16777216;
curlist.lastjchrfield:=q;end;{:1136};
if q<>-1073741823 then{1137:}begin t:=fontinfo[1+parambase[f]].int
/65536.0;
i:=fontinfo[charbase[f]+effectivechar(true,f,mem[q].hh.b1)].qqqq;
w:=fontinfo[widthbase[f]+i.b0].int;
h:=fontinfo[heightbase[f]+(i.b1)div 16].int;
if h<>x then begin deleteglueref(curkanjiskip);
deleteglueref(curxkanjiskip);curkanjiskip:=membot;curxkanjiskip:=membot;
incr(mem[curkanjiskip].hh.rh);incr(mem[curxkanjiskip].hh.rh);
p:=hpack(p,0,1);mem[p+4].int:=x-h;end;delta:=round((w-a)/2.0+h*t-x*s);
r:=newkern(delta);mem[r].hh.b1:=2;mem[curlist.tailfield].hh.rh:=r;
mem[r].hh.rh:=p;curlist.tailfield:=newkern(-a-delta);
mem[curlist.tailfield].hh.b1:=2;
if h=x then begin if fontdir[mem[p].hh.b0]<>0 then mem[mem[p].hh.rh].hh.
rh:=curlist.tailfield else mem[p].hh.rh:=curlist.tailfield;
end else mem[p].hh.rh:=curlist.tailfield;p:=q;end{:1137};
mem[curlist.tailfield].hh.rh:=p;
if mem[p].hh.rh<>-1073741823 then curlist.tailfield:=mem[p].hh.rh else
curlist.tailfield:=p;
{1504:}if disp<>0 then begin if not(curlist.tailfield>=himemmin)and(mem[
curlist.tailfield].hh.b0=5)then begin mem[curlist.tailfield+1].int:=0;
end else begin curlist.pnodefield:=curlist.tailfield;
begin mem[curlist.tailfield].hh.rh:=getnode(2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=5;mem[curlist.tailfield+1].int:=0;
curlist.pdispfield:=disp;end;end;{:1504};curlist.auxfield.hh.lh:=1000;
end;end;{:1135}{1139:}procedure alignerror;
begin if abs(alignstate)>2 then{1140:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1186);
end;printcmdchr(curcmd,curchr);
if curtok=1062 then begin begin helpptr:=6;helpline[5]:=1187;
helpline[4]:=1188;helpline[3]:=1189;helpline[2]:=1190;helpline[1]:=1191;
helpline[0]:=1192;end;end else begin begin helpptr:=5;helpline[4]:=1187;
helpline[3]:=1193;helpline[2]:=1190;helpline[1]:=1191;helpline[0]:=1192;
end;end;error;end{:1140}else begin backinput;
if alignstate<0 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(698);
end;incr(alignstate);curtok:=379;
end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1182);
end;decr(alignstate);curtok:=637;end;begin helpptr:=3;helpline[2]:=1183;
helpline[1]:=1184;helpline[0]:=1185;end;inserror;end;end;
{:1139}{1141:}procedure noalignerror;begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1186);
end;printesc(565);begin helpptr:=2;helpline[1]:=1194;helpline[0]:=1195;
end;error;end;procedure omiterror;begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1186);
end;printesc(568);begin helpptr:=2;helpline[1]:=1196;helpline[0]:=1195;
end;error;end;{:1141}{1143:}procedure doendv;begin baseptr:=inputptr;
inputstack[baseptr]:=curinput;
while(inputstack[baseptr].indexfield<>2)and(inputstack[baseptr].locfield
=-1073741823)and(inputstack[baseptr].statefield=0)do decr(baseptr);
if(inputstack[baseptr].indexfield<>2)or(inputstack[baseptr].locfield<>
-1073741823)or(inputstack[baseptr].statefield<>0)then fatalerror(633);
if curgroup=6 then begin endgraf;if fincol then finrow;end else offsave;
end;{:1143}{1147:}procedure cserror;begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(832);
end;printesc(540);begin helpptr:=1;helpline[0]:=1198;end;error;end;
{:1147}{1148:}procedure pushmath(c:groupcode);begin pushnest;
curlist.modefield:=-233;curlist.auxfield.int:=-1073741823;
newsavelevel(c);end;{:1148}{1150:}procedure initmath;label 21,40,45,30;
var w:scaled;l:scaled;s:scaled;p:halfword;q:halfword;
f:internalfontnumber;n:integer;v:scaled;d:scaled;begin gettoken;
if(curcmd=3)and(curlist.modefield>0)then{1157:}begin if curlist.
headfield=curlist.tailfield then begin popnest;w:=-1073741823;
end else begin adjusthlist(curlist.headfield,true);
linebreak(eqtb[28469].int);
{1158:}v:=mem[justbox+4].int+2*fontinfo[6+parambase[eqtb[25582].hh.rh]].
int;w:=-1073741823;p:=mem[justbox+5].hh.rh;
while p<>-1073741823 do begin{1159:}21:if(p>=himemmin)then begin f:=mem[
p].hh.b0;
d:=fontinfo[widthbase[f]+fontinfo[charbase[f]+mem[p].hh.b1].qqqq.b0].int
;if fontdir[f]<>0 then p:=mem[p].hh.rh;goto 40;end;
case mem[p].hh.b0 of 0,1,2,3:begin d:=mem[p+1].int;goto 40;end;
8:{663:}begin mem[memtop-12]:=mem[p+1];
mem[memtop-12].hh.rh:=mem[p].hh.rh;p:=memtop-12;goto 21;end{:663};
13,11:d:=mem[p+1].int;12:{1160:}begin q:=mem[p+1].hh.lh;d:=mem[q+1].int;
if mem[justbox+5].hh.b0=1 then begin if(mem[justbox+5].hh.b1=mem[q].hh.
b0)and(mem[q+2].int<>0)then v:=1073741823;
end else if mem[justbox+5].hh.b0=2 then begin if(mem[justbox+5].hh.b1=
mem[q].hh.b1)and(mem[q+3].int<>0)then v:=1073741823;end;
if mem[p].hh.b1>=100 then goto 40;end{:1160};10:{1374:}d:=0{:1374};
others:d:=0 end{:1159};if v<1073741823 then v:=v+d;goto 45;
40:if v<1073741823 then begin v:=v+d;w:=v;end else begin w:=1073741823;
goto 30;end;45:p:=mem[p].hh.rh;end;30:{:1158};end;
{1161:}if eqtb[25060].hh.rh=-1073741823 then if(eqtb[29055].int<>0)and((
(eqtb[28503].int>=0)and(curlist.pgfield+2>eqtb[28503].int))or(curlist.
pgfield+1<-eqtb[28503].int))then begin l:=eqtb[29041].int-abs(eqtb[29055
].int);if eqtb[29055].int>0 then s:=eqtb[29055].int else s:=0;
end else begin l:=eqtb[29041].int;s:=0;
end else begin n:=mem[eqtb[25060].hh.rh].hh.lh;
if curlist.pgfield+2>=n then p:=eqtb[25060].hh.rh+2*n else p:=eqtb[25060
].hh.rh+2*(curlist.pgfield+2);s:=mem[p-1].int;l:=mem[p].int;end{:1161};
pushmath(15);curlist.modefield:=233;eqworddefine(28506,-1);
eqworddefine(29051,w);eqworddefine(29052,l);eqworddefine(29053,s);
if eqtb[25064].hh.rh<>-1073741823 then begintokenlist(eqtb[25064].hh.rh,
9);if nestptr=1 then buildpage;end{:1157}else begin backinput;
{1151:}begin pushmath(15);eqworddefine(28506,-1);
if(insertsrcspecialeverymath)then insertsrcspecial;
if eqtb[25063].hh.rh<>-1073741823 then begintokenlist(eqtb[25063].hh.rh,
8);end{:1151};end;curlist.dirfield:=-abs(curlist.dirfield);end;
{:1150}{1154:}procedure starteqno;
begin savestack[saveptr+0].int:=curchr;incr(saveptr);
{1151:}begin pushmath(15);eqworddefine(28506,-1);
if(insertsrcspecialeverymath)then insertsrcspecial;
if eqtb[25063].hh.rh<>-1073741823 then begintokenlist(eqtb[25063].hh.rh,
8);end{:1151};end;{:1154}{1163:}procedure scanmath(p,q:halfword);
label 20,21,10;var c:integer;cx:KANJIcode;begin cx:=0;
20:{415:}repeat getxtoken;until(curcmd<>10)and(curcmd<>0){:415};
21:case curcmd of 11,12,73:if(curchr>=0)and(curchr<=256)then begin c:=
eqtb[27950+curchr].hh.rh;
if c=32768 then begin{1164:}begin curcs:=curchr+1;
curcmd:=eqtb[curcs].hh.b0;curchr:=eqtb[curcs].hh.rh;xtoken;backinput;
end{:1164};goto 20;end;end else cx:=curchr;74:cx:=curchr;
16,17,18,19:cx:=curchr;20:begin scancharnum;curchr:=curval;curcmd:=73;
goto 21;end;21:begin scanfifteenbitint;c:=curval;end;75:c:=curchr;
15:begin scantwentysevenbitint;c:=curval div 4096;end;
others:{1165:}begin backinput;scanleftbrace;savestack[saveptr+0].int:=p;
incr(saveptr);pushmath(9);goto 10;end{:1165}end;
if cx=0 then begin mem[p].hh.rh:=1;mem[p].hh.b1:=c mod 256;
if(c>=28672)and(((eqtb[28506].int>=0)and(eqtb[28506].int<16)))then mem[p
].hh.b0:=eqtb[28506].int else mem[p].hh.b0:=(c div 256)mod 16;
if fontdir[eqtb[25583+mem[p].hh.b0+cursize].hh.rh]<>0 then begin begin
if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1201);
end;begin helpptr:=1;helpline[0]:=1202;end;error;
end end else begin if q=-1073741823 then begin mem[p].hh.rh:=4;
mem[p].hh.lh:=newnoad;p:=mem[p].hh.lh+1;q:=p+3;end;mem[p].hh.rh:=6;
mem[p].hh.b0:=eqtb[28507].int;mem[p].hh.b1:=0;
mem[p+3].hh.lh:=cx+eqtb[25892+kcatcodekey(cx)].hh.rh*16777216;
if fontdir[eqtb[25583+mem[p].hh.b0+cursize].hh.rh]=0 then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1203);
end;begin helpptr:=1;helpline[0]:=1202;end;error;end end;10:end;
{:1163}{1167:}procedure setmathchar(c:integer);var p:halfword;
begin if c>=32768 then{1164:}begin curcs:=curchr+1;
curcmd:=eqtb[curcs].hh.b0;curchr:=eqtb[curcs].hh.rh;xtoken;backinput;
end{:1164}else begin p:=newnoad;mem[p+1].hh.rh:=1;
mem[p+1].hh.b1:=c mod 256;mem[p+1].hh.b0:=(c div 256)mod 16;
if c>=28672 then begin if((eqtb[28506].int>=0)and(eqtb[28506].int<16))
then mem[p+1].hh.b0:=eqtb[28506].int;mem[p].hh.b0:=18;
end else mem[p].hh.b0:=18+(c div 4096);mem[curlist.tailfield].hh.rh:=p;
curlist.tailfield:=p;
if fontdir[eqtb[25583+mem[p+1].hh.b0+cursize].hh.rh]<>0 then begin begin
if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1201);
end;begin helpptr:=1;helpline[0]:=1202;end;error;end;
inhibitglueflag:=false;end;end;{:1167}{1171:}procedure mathlimitswitch;
label 10;
begin if curlist.headfield<>curlist.tailfield then if mem[curlist.
tailfield].hh.b0=19 then begin mem[curlist.tailfield].hh.b1:=curchr;
goto 10;end;begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1205);
end;begin helpptr:=1;helpline[0]:=1206;end;error;10:end;
{:1171}{1172:}procedure scandelimiter(p:halfword;r:boolean);
begin if r then scantwentysevenbitint else begin{415:}repeat getxtoken;
until(curcmd<>10)and(curcmd<>0){:415};
case curcmd of 11,12:curval:=eqtb[28782+curchr].int;
15:scantwentysevenbitint;others:curval:=-1 end;end;
if curval<0 then{1173:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1207);
end;begin helpptr:=6;helpline[5]:=1208;helpline[4]:=1209;
helpline[3]:=1210;helpline[2]:=1211;helpline[1]:=1212;helpline[0]:=1213;
end;backerror;curval:=0;end{:1173};
mem[p].qqqq.b0:=(curval div 1048576)mod 16;
mem[p].qqqq.b1:=(curval div 4096)mod 256;
mem[p].qqqq.b2:=(curval div 256)mod 16;mem[p].qqqq.b3:=curval mod 256;
end;{:1172}{1175:}procedure mathradical;
begin begin mem[curlist.tailfield].hh.rh:=getnode(6);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=26;mem[curlist.tailfield].hh.b1:=0;
mem[curlist.tailfield+1].hh:=emptyfield;
mem[curlist.tailfield+3].hh:=emptyfield;
mem[curlist.tailfield+2].hh:=emptyfield;
scandelimiter(curlist.tailfield+5,true);
scanmath(curlist.tailfield+1,curlist.tailfield+4);end;
{:1175}{1177:}procedure mathac;
begin if curcmd=49 then{1178:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1214);
end;printesc(561);print(1215);begin helpptr:=2;helpline[1]:=1216;
helpline[0]:=1217;end;error;end{:1178};
begin mem[curlist.tailfield].hh.rh:=getnode(6);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=30;mem[curlist.tailfield].hh.b1:=0;
mem[curlist.tailfield+1].hh:=emptyfield;
mem[curlist.tailfield+3].hh:=emptyfield;
mem[curlist.tailfield+2].hh:=emptyfield;
mem[curlist.tailfield+5].hh.rh:=1;scanfifteenbitint;
mem[curlist.tailfield+5].hh.b1:=curval mod 256;
if(curval>=28672)and((eqtb[28506].int>=0)and(eqtb[28506].int<16))then
mem[curlist.tailfield+5].hh.b0:=eqtb[28506].int else mem[curlist.
tailfield+5].hh.b0:=(curval div 256)mod 16;
scanmath(curlist.tailfield+1,curlist.tailfield+4);end;
{:1177}{1184:}procedure appendchoices;
begin begin mem[curlist.tailfield].hh.rh:=newchoice;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;incr(saveptr);
savestack[saveptr-1].int:=0;pushmath(13);scanleftbrace;end;
{:1184}{1186:}{1196:}function finmlist(p:halfword):halfword;
var q:halfword;
begin if curlist.auxfield.int<>-1073741823 then{1197:}begin mem[curlist.
auxfield.int+3].hh.rh:=4;
mem[curlist.auxfield.int+3].hh.lh:=mem[curlist.headfield].hh.rh;
if p=-1073741823 then q:=curlist.auxfield.int else begin q:=mem[curlist.
auxfield.int+2].hh.lh;if mem[q].hh.b0<>32 then confusion(933);
mem[curlist.auxfield.int+2].hh.lh:=mem[q].hh.rh;
mem[q].hh.rh:=curlist.auxfield.int;mem[curlist.auxfield.int].hh.rh:=p;
end;end{:1197}else begin mem[curlist.tailfield].hh.rh:=p;
q:=mem[curlist.headfield].hh.rh;end;popnest;finmlist:=q;end;
{:1196}procedure buildchoices;label 10;var p:halfword;begin unsave;
p:=finmlist(-1073741823);
case savestack[saveptr-1].int of 0:mem[curlist.tailfield+1].hh.lh:=p;
1:mem[curlist.tailfield+1].hh.rh:=p;2:mem[curlist.tailfield+2].hh.lh:=p;
3:begin mem[curlist.tailfield+2].hh.rh:=p;decr(saveptr);goto 10;end;end;
incr(savestack[saveptr-1].int);pushmath(13);scanleftbrace;10:end;
{:1186}{1188:}procedure subsup;var t:smallnumber;p:halfword;begin t:=0;
p:=-1073741823;inhibitglueflag:=false;
if curlist.tailfield<>curlist.headfield then if(mem[curlist.tailfield].
hh.b0>=18)and(mem[curlist.tailfield].hh.b0<32)then begin p:=curlist.
tailfield+2+curcmd-7;t:=mem[p].hh.rh;end;
if(p=-1073741823)or(t<>0)then{1189:}begin begin mem[curlist.tailfield].
hh.rh:=newnoad;curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
p:=curlist.tailfield+2+curcmd-7;
if t<>0 then begin if curcmd=7 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1218);
end;begin helpptr:=1;helpline[0]:=1219;end;
end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1220);
end;begin helpptr:=1;helpline[0]:=1221;end;end;error;end;end{:1189};
scanmath(p,-1073741823);end;{:1188}{1193:}procedure mathfraction;
var c:smallnumber;begin c:=curchr;inhibitglueflag:=false;
if curlist.auxfield.int<>-1073741823 then{1195:}begin if c>=3 then begin
scandelimiter(memtop-12,false);scandelimiter(memtop-12,false);end;
if c mod 3=0 then scandimen(false,false,false);
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1228);
end;begin helpptr:=3;helpline[2]:=1229;helpline[1]:=1230;
helpline[0]:=1231;end;error;
end{:1195}else begin curlist.auxfield.int:=getnode(6);
mem[curlist.auxfield.int].hh.b0:=27;mem[curlist.auxfield.int].hh.b1:=0;
mem[curlist.auxfield.int+2].hh.rh:=4;
mem[curlist.auxfield.int+2].hh.lh:=mem[curlist.headfield].hh.rh;
mem[curlist.auxfield.int+3].hh:=emptyfield;
mem[curlist.auxfield.int+5].qqqq:=nulldelimiter;
mem[curlist.auxfield.int+4].qqqq:=nulldelimiter;
mem[curlist.headfield].hh.rh:=-1073741823;
curlist.tailfield:=curlist.headfield;
{1194:}if c>=3 then begin scandelimiter(curlist.auxfield.int+5,false);
scandelimiter(curlist.auxfield.int+4,false);end;
case c mod 3 of 0:begin scandimen(false,false,false);
mem[curlist.auxfield.int+1].int:=curval;end;
1:mem[curlist.auxfield.int+1].int:=1073741824;
2:mem[curlist.auxfield.int+1].int:=0;end{:1194};end;end;
{:1193}{1203:}procedure mathleftright;var t:smallnumber;p:halfword;
begin t:=curchr;inhibitglueflag:=false;
if(t=33)and(curgroup<>16)then{1204:}begin if curgroup=15 then begin
scandelimiter(memtop-12,false);begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(832);
end;printesc(933);begin helpptr:=1;helpline[0]:=1232;end;error;
end else offsave;end{:1204}else begin p:=newnoad;mem[p].hh.b0:=t;
scandelimiter(p+1,false);if t=32 then begin pushmath(16);
mem[curlist.headfield].hh.rh:=p;curlist.tailfield:=p;
end else begin p:=finmlist(p);unsave;
begin mem[curlist.tailfield].hh.rh:=newnoad;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=25;mem[curlist.tailfield+1].hh.rh:=4;
mem[curlist.tailfield+1].hh.lh:=p;end;end;end;
{:1203}{1206:}procedure aftermath;var l:boolean;disp:scaled;
danger:boolean;m:integer;p:halfword;a:halfword;{1210:}b:halfword;
w:scaled;z:scaled;e:scaled;q:scaled;d:scaled;s:scaled;g1,g2:smallnumber;
r:halfword;t:halfword;{:1210}begin danger:=false;
{1207:}if(fontparams[eqtb[25585].hh.rh]<22)or(fontparams[eqtb[25601].hh.
rh]<22)or(fontparams[eqtb[25617].hh.rh]<22)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1233);
end;begin helpptr:=3;helpline[2]:=1234;helpline[1]:=1235;
helpline[0]:=1236;end;error;flushmath;danger:=true;
end else if(fontparams[eqtb[25586].hh.rh]<13)or(fontparams[eqtb[25602].
hh.rh]<13)or(fontparams[eqtb[25618].hh.rh]<13)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1237);
end;begin helpptr:=3;helpline[2]:=1238;helpline[1]:=1239;
helpline[0]:=1240;end;error;flushmath;danger:=true;end{:1207};
deleteglueref(curkanjiskip);deleteglueref(curxkanjiskip);
if eqtb[25633].hh.rh>0 then curkanjiskip:=eqtb[24542].hh.rh else
curkanjiskip:=membot;
if eqtb[25634].hh.rh>0 then curxkanjiskip:=eqtb[24543].hh.rh else
curxkanjiskip:=membot;incr(mem[curkanjiskip].hh.rh);
incr(mem[curxkanjiskip].hh.rh);m:=curlist.modefield;l:=false;
p:=finmlist(-1073741823);
if curlist.modefield=-m then begin{1209:}begin getxtoken;
if curcmd<>3 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1241);
end;begin helpptr:=2;helpline[1]:=1242;helpline[0]:=1243;end;backerror;
end;end{:1209};curmlist:=p;curstyle:=2;mlistpenalties:=false;
mlisttohlist;a:=hpack(mem[memtop-3].hh.rh,0,1);unsave;decr(saveptr);
if savestack[saveptr+0].int=1 then l:=true;danger:=false;
{1207:}if(fontparams[eqtb[25585].hh.rh]<22)or(fontparams[eqtb[25601].hh.
rh]<22)or(fontparams[eqtb[25617].hh.rh]<22)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1233);
end;begin helpptr:=3;helpline[2]:=1234;helpline[1]:=1235;
helpline[0]:=1236;end;error;flushmath;danger:=true;
end else if(fontparams[eqtb[25586].hh.rh]<13)or(fontparams[eqtb[25602].
hh.rh]<13)or(fontparams[eqtb[25618].hh.rh]<13)then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1237);
end;begin helpptr:=3;helpline[2]:=1238;helpline[1]:=1239;
helpline[0]:=1240;end;error;flushmath;danger:=true;end{:1207};
m:=curlist.modefield;p:=finmlist(-1073741823);end else a:=-1073741823;
if m<0 then{1208:}begin if curlist.dirfield=3 then disp:=eqtb[29059].int
else disp:=eqtb[29060].int;
{1503:}begin if not(curlist.tailfield>=himemmin)and(mem[curlist.
tailfield].hh.b0=5)then begin if curlist.pdispfield=disp then begin
freenode(curlist.tailfield,2);curlist.tailfield:=curlist.pnodefield;
mem[curlist.tailfield].hh.rh:=-1073741823;
end else mem[curlist.tailfield+1].int:=disp;
end else if disp<>0 then begin curlist.pnodefield:=curlist.tailfield;
begin mem[curlist.tailfield].hh.rh:=getnode(2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=5;mem[curlist.tailfield+1].int:=disp;
curlist.pdispfield:=disp;end;end;{:1503};
begin mem[curlist.tailfield].hh.rh:=newmath(eqtb[29039].int,0);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;curmlist:=p;
curstyle:=2;mlistpenalties:=(curlist.modefield>0);mlisttohlist;
mem[curlist.tailfield].hh.rh:=mem[memtop-3].hh.rh;
while mem[curlist.tailfield].hh.rh<>-1073741823 do curlist.tailfield:=
mem[curlist.tailfield].hh.rh;
begin mem[curlist.tailfield].hh.rh:=newmath(eqtb[29039].int,1);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
{1504:}if disp<>0 then begin if not(curlist.tailfield>=himemmin)and(mem[
curlist.tailfield].hh.b0=5)then begin mem[curlist.tailfield+1].int:=0;
end else begin curlist.pnodefield:=curlist.tailfield;
begin mem[curlist.tailfield].hh.rh:=getnode(2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=5;mem[curlist.tailfield+1].int:=0;
curlist.pdispfield:=disp;end;end;{:1504};curlist.auxfield.hh.lh:=1000;
unsave;end{:1208}else begin if a=-1073741823 then{1209:}begin getxtoken;
if curcmd<>3 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1241);
end;begin helpptr:=2;helpline[1]:=1242;helpline[0]:=1243;end;backerror;
end;end{:1209};{1211:}curmlist:=p;curstyle:=0;mlistpenalties:=false;
mlisttohlist;p:=mem[memtop-3].hh.rh;adjusttail:=memtop-5;
b:=hpack(p,0,1);p:=mem[b+5].hh.rh;t:=adjusttail;adjusttail:=-1073741823;
w:=mem[b+1].int;z:=eqtb[29052].int;s:=eqtb[29053].int;
if(a=-1073741823)or danger then begin e:=0;q:=0;
end else begin e:=mem[a+1].int;
q:=e+fontinfo[6+parambase[eqtb[25585].hh.rh]].int;end;
if w+q>z then{1213:}begin if(e<>0)and((w-totalshrink[0]+q<=z)or(
totalshrink[1]<>0)or(totalshrink[2]<>0)or(totalshrink[3]<>0))then begin
deleteglueref(mem[b+7].hh.rh);deleteglueref(mem[b+7].hh.lh);
freenode(b,10);b:=hpack(p,z-q,0);end else begin e:=0;
if w>z then begin deleteglueref(mem[b+7].hh.rh);
deleteglueref(mem[b+7].hh.lh);freenode(b,10);b:=hpack(p,z,0);end;end;
w:=mem[b+1].int;end{:1213};{1214:}d:=half(z-w);
if(e>0)and(d<2*e)then begin d:=half(z-w-e);
if p<>-1073741823 then if not(p>=himemmin)then if mem[p].hh.b0=12 then d
:=0;end{:1214};
{1215:}begin mem[curlist.tailfield].hh.rh:=newpenalty(eqtb[28473].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
if(d+s<=eqtb[29051].int)or l then begin g1:=3;g2:=4;
end else begin g1:=5;g2:=6;end;if l and(e=0)then begin mem[a+4].int:=s;
appendtovlist(a);begin mem[curlist.tailfield].hh.rh:=newpenalty(10000);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
end else begin mem[curlist.tailfield].hh.rh:=newparamglue(g1);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end{:1215};
{1216:}if e<>0 then begin r:=newkern(z-w-e-d);
if l then begin mem[a].hh.rh:=r;mem[r].hh.rh:=b;b:=a;d:=0;
end else begin mem[b].hh.rh:=r;mem[r].hh.rh:=a;end;b:=hpack(b,0,1);end;
mem[b+4].int:=s+d;appendtovlist(b){:1216};
{1217:}if(a<>-1073741823)and(e=0)and not l then begin begin mem[curlist.
tailfield].hh.rh:=newpenalty(10000);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[a+4].int:=s+z-mem[a+1].int;appendtovlist(a);g2:=0;end;
if t<>memtop-5 then begin mem[curlist.tailfield].hh.rh:=mem[memtop-5].hh
.rh;curlist.tailfield:=t;end;
begin mem[curlist.tailfield].hh.rh:=newpenalty(eqtb[28474].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
if g2>0 then begin mem[curlist.tailfield].hh.rh:=newparamglue(g2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end{:1217};
resumeafterdisplay{:1211};end;end;
{:1206}{1212:}procedure resumeafterdisplay;
begin if curgroup<>15 then confusion(1244);unsave;
curlist.pgfield:=curlist.pgfield+3;pushnest;
curlist.adjdirfield:=abs(curlist.dirfield);curlist.modefield:=117;
curlist.auxfield.hh.lh:=1000;
if eqtb[28513].int<=0 then curlang:=0 else if eqtb[28513].int>255 then
curlang:=0 else curlang:=eqtb[28513].int;
curlist.auxfield.hh.rh:=curlang;
curlist.pgfield:=(normmin(eqtb[28514].int)*64+normmin(eqtb[28515].int))
*65536+curlang;{454:}begin getxtoken;if curcmd<>10 then backinput;
end{:454};if nestptr=1 then buildpage;end;
{:1212}{1223:}{1227:}procedure getrtoken;label 20;
begin 20:repeat gettoken;until curtok<>2592;
if(curcs=0)or(curcs>eqtbtop)or((curcs>15514)and(curcs<=29572))then begin
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1259);
end;begin helpptr:=5;helpline[4]:=1260;helpline[3]:=1261;
helpline[2]:=1262;helpline[1]:=1263;helpline[0]:=1264;end;
if curcs=0 then backinput;curtok:=536886425;inserror;goto 20;end;end;
{:1227}{1241:}procedure trapzeroglue;
begin if(mem[curval+1].int=0)and(mem[curval+2].int=0)and(mem[curval+3].
int=0)then begin incr(mem[membot].hh.rh);deleteglueref(curval);
curval:=membot;end;end;
{:1241}{1249:}procedure doregistercommand(a:smallnumber);label 40,10;
var l,q,r,s:halfword;p:0..3;begin q:=curcmd;
{1250:}begin if q<>102 then begin getxtoken;
if(curcmd>=81)and(curcmd<=84)then begin l:=curchr;p:=curcmd-81;goto 40;
end;if curcmd<>102 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(726);
end;printcmdchr(curcmd,curchr);print(727);printcmdchr(q,0);
begin helpptr:=1;helpline[0]:=1291;end;error;goto 10;end;end;p:=curchr;
scaneightbitint;case p of 0:l:=curval+28526;1:l:=curval+29061;
2:l:=curval+24548;3:l:=curval+24804;end;end;40:{:1250};
if q=102 then scanoptionalequals else if scankeyword(1287)then;
aritherror:=false;
if q<104 then{1251:}if p<2 then begin if p=0 then scanint else scandimen
(false,false,false);if q=103 then curval:=curval+eqtb[l].int;
end else begin scanglue(p);if q=103 then{1252:}begin q:=newspec(curval);
r:=eqtb[l].hh.rh;deleteglueref(curval);
mem[q+1].int:=mem[q+1].int+mem[r+1].int;
if mem[q+2].int=0 then mem[q].hh.b0:=0;
if mem[q].hh.b0=mem[r].hh.b0 then mem[q+2].int:=mem[q+2].int+mem[r+2].
int else if(mem[q].hh.b0<mem[r].hh.b0)and(mem[r+2].int<>0)then begin mem
[q+2].int:=mem[r+2].int;mem[q].hh.b0:=mem[r].hh.b0;end;
if mem[q+3].int=0 then mem[q].hh.b1:=0;
if mem[q].hh.b1=mem[r].hh.b1 then mem[q+3].int:=mem[q+3].int+mem[r+3].
int else if(mem[q].hh.b1<mem[r].hh.b1)and(mem[r+3].int<>0)then begin mem
[q+3].int:=mem[r+3].int;mem[q].hh.b1:=mem[r].hh.b1;end;curval:=q;
end{:1252};end{:1251}else{1253:}begin scanint;
if p<2 then if q=104 then if p=0 then curval:=multandadd(eqtb[l].int,
curval,0,2147483647)else curval:=multandadd(eqtb[l].int,curval,0,
1073741823)else curval:=xovern(eqtb[l].int,curval)else begin s:=eqtb[l].
hh.rh;r:=newspec(s);
if q=104 then begin mem[r+1].int:=multandadd(mem[s+1].int,curval,0,
1073741823);mem[r+2].int:=multandadd(mem[s+2].int,curval,0,1073741823);
mem[r+3].int:=multandadd(mem[s+3].int,curval,0,1073741823);
end else begin mem[r+1].int:=xovern(mem[s+1].int,curval);
mem[r+2].int:=xovern(mem[s+2].int,curval);
mem[r+3].int:=xovern(mem[s+3].int,curval);end;curval:=r;end;end{:1253};
if aritherror then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1288);
end;begin helpptr:=2;helpline[1]:=1289;helpline[0]:=1290;end;
if p>=2 then deleteglueref(curval);error;goto 10;end;
if p<2 then if(a>=4)then geqworddefine(l,curval)else eqworddefine(l,
curval)else begin trapzeroglue;
if(a>=4)then geqdefine(l,132,curval)else eqdefine(l,132,curval);end;
10:end;{:1249}{1256:}procedure alteraux;var c:halfword;
begin if curchr<>abs(curlist.modefield)then reportillegalcase else begin
c:=curchr;scanoptionalequals;
if c=1 then begin scandimen(false,false,false);
curlist.auxfield.int:=curval;end else begin scanint;
if(curval<=0)or(curval>32767)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1294);
end;begin helpptr:=1;helpline[0]:=1295;end;interror(curval);
end else curlist.auxfield.hh.lh:=curval;end;end;end;
{:1256}{1257:}procedure alterprevgraf;var p:0..nestsize;
begin nest[nestptr]:=curlist;p:=nestptr;
while abs(nest[p].modefield)<>1 do decr(p);scanoptionalequals;scanint;
if curval<0 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1012);
end;printesc(570);begin helpptr:=1;helpline[0]:=1296;end;
interror(curval);end else begin nest[p].pgfield:=curval;
curlist:=nest[nestptr];end;end;{:1257}{1258:}procedure alterpagesofar;
var c:0..7;begin c:=curchr;scanoptionalequals;
scandimen(false,false,false);pagesofar[c]:=curval;end;
{:1258}{1259:}procedure alterinteger;var c:0..1;begin c:=curchr;
scanoptionalequals;scanint;
if c=0 then deadcycles:=curval else insertpenalties:=curval;end;
{:1259}{1260:}procedure alterboxdimen;var c:smallnumber;p,q:halfword;
b:eightbits;begin c:=curchr;scaneightbitint;b:=curval;
scanoptionalequals;scandimen(false,false,false);
if eqtb[25326+b].hh.rh<>-1073741823 then begin q:=eqtb[25326+b].hh.rh;
p:=mem[q].hh.rh;
while p<>-1073741823 do begin if abs(curlist.dirfield)=(mem[p].hh.b1)
then q:=p;p:=mem[p].hh.rh;end;
if(mem[q].hh.b1)<>abs(curlist.dirfield)then begin p:=mem[eqtb[25326+b].
hh.rh].hh.rh;mem[eqtb[25326+b].hh.rh].hh.rh:=-1073741823;
q:=newdirnode(q,abs(curlist.dirfield));mem[q+5].hh.rh:=-1073741823;
mem[q].hh.rh:=p;mem[eqtb[25326+b].hh.rh].hh.rh:=q;end;
mem[q+c].int:=curval;end;end;
{:1260}{1270:}procedure newfont(a:smallnumber);label 50;var u:halfword;
s:scaled;f:internalfontnumber;t:strnumber;oldsetting:0..21;
begin if jobname=0 then openlogfile;getrtoken;u:=curcs;
if u>=514 then t:=hash[u].rh else if u>=257 then if u=513 then t:=1300
else t:=u-257 else begin oldsetting:=selector;selector:=21;print(1300);
print(u-1);selector:=oldsetting;
begin if poolptr+1>poolsize then overflow(258,poolsize-initpoolptr);end;
t:=makestring;end;if(a>=4)then geqdefine(u,98,0)else eqdefine(u,98,0);
scanoptionalequals;scanfilename;{1271:}nameinprogress:=true;
if scankeyword(1301)then{1272:}begin scandimen(false,false,false);
s:=curval;
if(s<=0)or(s>=134217728)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1303);
end;printscaled(s);print(1304);begin helpptr:=2;helpline[1]:=1305;
helpline[0]:=1306;end;error;s:=10*65536;end;
end{:1272}else if scankeyword(1302)then begin scanint;s:=-curval;
if(curval<=0)or(curval>32768)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(590);
end;begin helpptr:=1;helpline[0]:=591;end;interror(curval);s:=-1000;end;
end else s:=-1000;nameinprogress:=false{:1271};
{1273:}for f:=1 to fontptr do if streqstr(fontname[f],curname)and
streqstr(fontarea[f],curarea)then begin if s>0 then begin if s=fontsize[
f]then goto 50;
end else if fontsize[f]=xnoverd(fontdsize[f],-s,1000)then goto 50;
end{:1273};f:=readfontinfo(u,curname,curarea,s);50:eqtb[u].hh.rh:=f;
eqtb[15525+f]:=eqtb[u];hash[15525+f].rh:=t;end;
{:1270}{1278:}procedure newinteraction;begin println;
interaction:=curchr;
if interaction=0 then kpsemaketexdiscarderrors:=1 else
kpsemaketexdiscarderrors:=0;
{76:}if interaction=0 then selector:=16 else selector:=17{:76};
if logopened then selector:=selector+2;end;
{:1278}procedure prefixedcommand;label 30,10;var a:smallnumber;
m:integer;f:internalfontnumber;j:halfword;k:fontindex;p,q:halfword;
n:integer;e:boolean;begin a:=0;
while curcmd=106 do begin if not odd(a div curchr)then a:=a+curchr;
{415:}repeat getxtoken;until(curcmd<>10)and(curcmd<>0){:415};
if curcmd<=78 then{1224:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1254);
end;printcmdchr(curcmd,curchr);printchar(39);begin helpptr:=1;
helpline[0]:=1255;end;backerror;goto 10;end{:1224};end;
{1225:}if(curcmd<>110)and(a mod 4<>0)then begin begin if interaction=3
then;if filelineerrorstylep then printfileline else printnl(263);
print(726);end;printesc(1246);print(1256);printesc(1247);print(1257);
printcmdchr(curcmd,curchr);printchar(39);begin helpptr:=1;
helpline[0]:=1258;end;error;end{:1225};
{1226:}if eqtb[28505].int<>0 then if eqtb[28505].int<0 then begin if(a>=
4)then a:=a-4;end else begin if not(a>=4)then a:=a+4;end{:1226};
case curcmd of{1229:}98:begin if fontdir[curchr]=4 then if(a>=4)then
geqdefine(25631,135,curchr)else eqdefine(25631,135,curchr)else if
fontdir[curchr]=3 then if(a>=4)then geqdefine(25632,135,curchr)else
eqdefine(25632,135,curchr)else if(a>=4)then geqdefine(25582,135,curchr)
else eqdefine(25582,135,curchr)end;
{:1229}{1230:}110:begin if odd(curchr)and not(a>=4)and(eqtb[28505].int>=
0)then a:=a+4;e:=(curchr>=2);getrtoken;p:=curcs;q:=scantoks(true,e);
if(a>=4)then geqdefine(p,126+(a mod 4),defref)else eqdefine(p,126+(a mod
4),defref);end;{:1230}{1233:}107:begin n:=curchr;getrtoken;p:=curcs;
if n=0 then begin repeat gettoken;until curcmd<>10;
if curtok=3133 then begin gettoken;if curcmd=10 then gettoken;end;
end else begin gettoken;q:=curtok;gettoken;backinput;curtok:=q;
backinput;end;if curcmd>=126 then incr(mem[curchr].hh.lh);
if(a>=4)then geqdefine(p,curcmd,curchr)else eqdefine(p,curcmd,curchr);
end;{:1233}{1236:}108:if curchr=7 then begin scancharnum;
p:=28206+curval;scanoptionalequals;scancharnum;n:=curval;scancharnum;
if(eqtb[28524].int>0)then begin begindiagnostic;printnl(1277);
print(p-28206);print(1278);print(n);printchar(32);print(curval);
enddiagnostic(false);end;n:=n*256+curval;
if(a>=4)then geqdefine(p,135,n)else eqdefine(p,135,n);
if(p-28206)<eqtb[28522].int then if(a>=4)then geqworddefine(28522,p
-28206)else eqworddefine(28522,p-28206);
if(p-28206)>eqtb[28523].int then if(a>=4)then geqworddefine(28523,p
-28206)else eqworddefine(28523,p-28206);end else begin n:=curchr;
getrtoken;p:=curcs;
if(a>=4)then geqdefine(p,0,256)else eqdefine(p,0,256);
scanoptionalequals;case n of 0:begin scancharnum;
if(a>=4)then geqdefine(p,73,curval)else eqdefine(p,73,curval);end;
8:begin scancharnum;
if(a>=4)then geqdefine(p,74,curval)else eqdefine(p,74,curval);end;
1:begin scanfifteenbitint;
if(a>=4)then geqdefine(p,75,curval)else eqdefine(p,75,curval);end;
others:begin scaneightbitint;
case n of 2:if(a>=4)then geqdefine(p,81,28526+curval)else eqdefine(p,81,
28526+curval);
3:if(a>=4)then geqdefine(p,82,29061+curval)else eqdefine(p,82,29061+
curval);
4:if(a>=4)then geqdefine(p,83,24548+curval)else eqdefine(p,83,24548+
curval);
5:if(a>=4)then geqdefine(p,84,24804+curval)else eqdefine(p,84,24804+
curval);
6:if(a>=4)then geqdefine(p,80,25070+curval)else eqdefine(p,80,25070+
curval);end;end end;end;{:1236}{1237:}109:begin scanint;n:=curval;
if not scankeyword(898)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1141);
end;begin helpptr:=2;helpline[1]:=1279;helpline[0]:=1280;end;error;end;
getrtoken;p:=curcs;readtoks(n,p);
if(a>=4)then geqdefine(p,126,curval)else eqdefine(p,126,curval);end;
{:1237}{1238:}79,80:begin q:=curcs;
if curcmd=79 then begin scaneightbitint;p:=25070+curval;
end else p:=curchr;scanoptionalequals;{415:}repeat getxtoken;
until(curcmd<>10)and(curcmd<>0){:415};
if curcmd<>1 then{1239:}begin if curcmd=79 then begin scaneightbitint;
curcmd:=80;curchr:=25070+curval;end;
if curcmd=80 then begin q:=eqtb[curchr].hh.rh;
if q=-1073741823 then if(a>=4)then geqdefine(p,116,-1073741823)else
eqdefine(p,116,-1073741823)else begin incr(mem[q].hh.lh);
if(a>=4)then geqdefine(p,126,q)else eqdefine(p,126,q);end;goto 30;end;
end{:1239};backinput;curcs:=q;q:=scantoks(false,false);
if mem[defref].hh.rh=-1073741823 then begin if(a>=4)then geqdefine(p,116
,-1073741823)else eqdefine(p,116,-1073741823);
begin mem[defref].hh.rh:=avail;avail:=defref;ifdef('STAT')decr(dynused);
endif('STAT')end;
end else begin if p=25061 then begin mem[q].hh.rh:=getavail;
q:=mem[q].hh.rh;mem[q].hh.lh:=637;q:=getavail;mem[q].hh.lh:=379;
mem[q].hh.rh:=mem[defref].hh.rh;mem[defref].hh.rh:=q;end;
if(a>=4)then geqdefine(p,126,defref)else eqdefine(p,126,defref);end;end;
{:1238}{1240:}81:begin p:=curchr;scanoptionalequals;scanint;
if p=28506 then begin if fontdir[eqtb[25583+curval].hh.rh]<>0 then if(a
>=4)then geqworddefine(28507,curval)else eqworddefine(28507,curval)else
if(a>=4)then geqworddefine(p,curval)else eqworddefine(p,curval);
end else if(a>=4)then geqworddefine(p,curval)else eqworddefine(p,curval)
;end;82:begin p:=curchr;scanoptionalequals;scandimen(false,false,false);
if(a>=4)then geqworddefine(p,curval)else eqworddefine(p,curval);end;
83,84:begin p:=curchr;n:=curcmd;scanoptionalequals;
if n=84 then scanglue(3)else scanglue(2);trapzeroglue;
if(a>=4)then geqdefine(p,132,curval)else eqdefine(p,132,curval);end;
{:1240}{1244:}96:begin{1245:}if curchr=25892 then m:=15 else m:=0{:1245}
;{1246:}if curchr=25636 then n:=15 else if curchr=25892 then n:=19 else
if curchr=27950 then n:=32768 else if curchr=27694 then n:=32767 else if
curchr=28782 then n:=16777215 else n:=255{:1246};p:=curchr;scancharnum;
if p=25892 then p:=p+kcatcodekey(curval)else if not ischarascii(curval)
then p:=p+Hi(curval)else p:=p+curval;scanoptionalequals;scanint;
if((curval<m)and(p<28782))or(curval>n)then begin begin if interaction=3
then;if filelineerrorstylep then printfileline else printnl(263);
print(1281);end;printint(curval);if p<28782 then begin print(1282);
printint(m);print(1283);end else print(1284);printint(n);
if m=0 then begin begin helpptr:=1;helpline[0]:=1285;end;error;
end else begin begin helpptr:=1;helpline[0]:=1286;end;error;end;
curval:=m;end;
if p<27950 then if(a>=4)then geqdefine(p,135,curval)else eqdefine(p,135,
curval)else if p<28782 then if(a>=4)then geqdefine(p,135,curval)else
eqdefine(p,135,curval)else if(a>=4)then geqworddefine(p,curval)else
eqworddefine(p,curval);end;{:1244}{1247:}97:begin p:=curchr;
scanfourbitint;p:=p+curval;scanoptionalequals;scanfontident;
if(a>=4)then geqdefine(p,135,curval)else eqdefine(p,135,curval);end;
{:1247}{1248:}102,103,104,105:doregistercommand(a);
{:1248}{1254:}111:begin scaneightbitint;
if(a>=4)then n:=256+curval else n:=curval;scanoptionalequals;
if setboxallowed then scanbox(1073741824+n)else begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(721);
end;printesc(574);begin helpptr:=2;helpline[1]:=1292;helpline[0]:=1293;
end;error;end;end;{:1254}{1255:}90:alteraux;91:alterprevgraf;
92:alterpagesofar;93:alterinteger;94:alterboxdimen;
{:1255}{1261:}95:begin scanoptionalequals;scanint;n:=curval;
if n<=0 then p:=-1073741823 else begin p:=getnode(2*n+1);
mem[p].hh.lh:=n;for j:=1 to n do begin scandimen(false,false,false);
mem[p+2*j-1].int:=curval;scandimen(false,false,false);
mem[p+2*j].int:=curval;end;end;
if(a>=4)then geqdefine(25060,133,p)else eqdefine(25060,133,p);end;
{:1261}{1265:}112:if curchr=1 then begin ifdef('INITEX')if iniversion
then begin newpatterns;goto 30;end;
endif('INITEX')begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1297);
end;helpptr:=0;error;repeat gettoken;until curcmd=2;goto 10;
end else begin newhyphexceptions;goto 30;end;
{:1265}{1266:}85:begin findfontdimen(true);k:=curval;scanoptionalequals;
scandimen(false,false,false);fontinfo[k].int:=curval;end;
86:begin n:=curchr;scanfontident;f:=curval;scanoptionalequals;scanint;
if n=0 then hyphenchar[f]:=curval else skewchar[f]:=curval;end;
{:1266}{1269:}101,100,99:newfont(a);{:1269}{1277:}113:newinteraction;
{:1277}{1456:}89:begin p:=curchr;scanint;n:=curval;scanoptionalequals;
scanint;
if not ischarkanji(curval)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1400);
end;printhex(curval);printchar(41);begin helpptr:=1;helpline[0]:=1401;
end;error;goto 10;
end else if(n<0)or(n>9)then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1402);
end;printint(n);printchar(41);begin helpptr:=1;helpline[0]:=1401;end;
error;goto 10;
end else if(a>=4)then geqdefine(27172+n,n,toDVI(curval))else eqdefine(
27172+n,n,toDVI(curval));end;
{:1456}{1461:}114:begin if curchr<2 then p:=25633 else begin p:=25634;
curchr:=(curchr mod 2);end;
if(a>=4)then geqdefine(p,135,curchr)else eqdefine(p,135,curchr);end;
115:if(a>=4)then geqdefine(25635,135,curchr)else eqdefine(25635,135,
curchr);{:1461}{1469:}88:begin p:=curchr;scanint;n:=curval;
scanoptionalequals;scanint;
if ischarkanji(n)then begin j:=getinhibitpos(n,0);
if j=1000 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1424);
end;begin helpptr:=1;helpline[0]:=1401;end;error;goto 10;end;
if(a>=4)then geqdefine(26660+j,curval,n)else eqdefine(26660+j,curval,n);
end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1425);
end;printhex(n);printchar(41);begin helpptr:=1;helpline[0]:=1401;end;
error;goto 10;end;end;{:1469}{1474:}87:begin p:=curchr;scanint;
n:=curval;scanoptionalequals;scanint;
if ischarascii(n)or ischarkanji(n)then begin j:=getkinsokupos(n,0);
if j=1000 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1431);
end;begin helpptr:=1;helpline[0]:=1401;end;error;goto 10;end;
if(p=1)or(p=2)then begin if(a>=4)then geqdefine(26916+j,p,n)else
eqdefine(26916+j,p,n);
if(a>=4)then geqworddefine(29317+j,curval)else eqworddefine(29317+j,
curval);end else confusion(535);
end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1432);
end;
if p=1 then print(1433)else if p=2 then print(1434)else printchar(63);
print(1435);printhex(n);printchar(41);begin helpptr:=1;
helpline[0]:=1401;end;error;goto 10;end;end;
{:1474}others:confusion(1253)end;
30:{1282:}if aftertoken<>0 then begin curtok:=aftertoken;backinput;
aftertoken:=0;end{:1282};10:end;{:1223}{1283:}procedure doassignments;
label 10;begin while true do begin{415:}repeat getxtoken;
until(curcmd<>10)and(curcmd<>0){:415};if curcmd<=78 then goto 10;
setboxallowed:=false;prefixedcommand;setboxallowed:=true;end;10:end;
{:1283}{1288:}procedure openorclosein;var c:0..1;n:0..15;
begin c:=curchr;scanfourbitint;n:=curval;
if readopen[n]<>2 then begin aclose(readfile[n]);readopen[n]:=2;end;
if c<>0 then begin scanoptionalequals;scanfilename;
packfilename(curname,curarea,curext);texinputtype:=0;
if kpseinnameok(stringcast(nameoffile+1))and aopenin(readfile[n],
kpsetexformat)then readopen[n]:=1;end;end;
{:1288}{1292:}procedure issuemessage;var oldsetting:0..21;c:0..1;
s:strnumber;begin c:=curchr;mem[memtop-12].hh.rh:=scantoks(false,true);
oldsetting:=selector;selector:=21;tokenshow(defref);
selector:=oldsetting;flushlist(defref);
begin if poolptr+1>poolsize then overflow(258,poolsize-initpoolptr);end;
s:=makestring;
if c=0 then{1293:}begin if termoffset+(strstart[s+1]-strstart[s])>
maxprintline-2 then println else if(termoffset>0)or(fileoffset>0)then
printchar(32);slowprint(s);fflush(stdout);
end{:1293}else{1296:}begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(344);
end;slowprint(s);
if eqtb[25069].hh.rh<>-1073741823 then useerrhelp:=true else if
longhelpseen then begin helpptr:=1;helpline[0]:=1313;
end else begin if interaction<3 then longhelpseen:=true;
begin helpptr:=4;helpline[3]:=1314;helpline[2]:=1315;helpline[1]:=1316;
helpline[0]:=1317;end;end;error;useerrhelp:=false;end{:1296};
begin decr(strptr);poolptr:=strstart[strptr];end;end;
{:1292}{1301:}procedure shiftcase;var b:halfword;p:halfword;t:halfword;
c:eightbits;begin b:=curchr;p:=scantoks(false,false);
p:=mem[defref].hh.rh;
while p<>-1073741823 do begin{1302:}t:=mem[p].hh.lh;
if(t<536871168)and(not checkkanji(t))then begin c:=t mod 256;
if eqtb[b+c].hh.rh<>0 then mem[p].hh.lh:=t-c+eqtb[b+c].hh.rh;end{:1302};
p:=mem[p].hh.rh;end;begintokenlist(mem[defref].hh.rh,3);
begin mem[defref].hh.rh:=avail;avail:=defref;ifdef('STAT')decr(dynused);
endif('STAT')end;end;{:1301}{1306:}procedure showwhatever;label 50;
var p:halfword;begin case curchr of 3:begin begindiagnostic;
showactivities;end;1:{1309:}begin scaneightbitint;begindiagnostic;
printnl(1336);printint(curval);printchar(61);
if eqtb[25326+curval].hh.rh=-1073741823 then print(429)else showbox(eqtb
[25326+curval].hh.rh);end{:1309};0:{1307:}begin gettoken;
if interaction=3 then;printnl(1330);
if curcs<>0 then begin sprintcs(curcs);printchar(61);end;printmeaning;
goto 50;end{:1307};4:{1462:}begin printnl(1330);
if eqtb[25633].hh.rh>0 then print(1418)else print(1419);printnl(1330);
if eqtb[25634].hh.rh>0 then print(1420)else print(1421);goto 50;
end{:1462};others:{1310:}begin p:=thetoks;if interaction=3 then;
printnl(1330);tokenshow(memtop-3);flushlist(mem[memtop-3].hh.rh);
goto 50;end{:1310}end;{1311:}enddiagnostic(true);
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1337);
end;if selector=19 then if eqtb[28491].int<=0 then begin selector:=17;
print(1338);selector:=19;end{:1311};
50:if interaction<3 then begin helpptr:=0;decr(errorcount);
end else if eqtb[28491].int>0 then begin begin helpptr:=3;
helpline[2]:=1325;helpline[1]:=1326;helpline[0]:=1327;end;
end else begin begin helpptr:=5;helpline[4]:=1325;helpline[3]:=1326;
helpline[2]:=1327;helpline[1]:=1328;helpline[0]:=1329;end;end;error;end;
{:1306}{1315:}ifdef('INITEX')procedure storefmtfile;label 41,42,31,32;
var j,k,l:integer;p,q:halfword;x:integer;formatengine:^ASCIIcode;
begin{1317:}if saveptr<>0 then begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1340);
end;begin helpptr:=1;helpline[0]:=1341;end;
begin if interaction=3 then interaction:=2;if logopened then error;
ifdef('TEXMF_DEBUG')if interaction>0 then debughelp;
endif('TEXMF_DEBUG')history:=3;jumpout;end;end{:1317};
{1341:}selector:=21;print(1357);print(jobname);printchar(32);
printint(eqtb[28485].int);printchar(46);printint(eqtb[28484].int);
printchar(46);printint(eqtb[28483].int);printchar(41);
if interaction=0 then selector:=18 else selector:=19;
begin if poolptr+1>poolsize then overflow(258,poolsize-initpoolptr);end;
formatident:=makestring;packjobname(839);
while not wopenout(fmtfile)do promptfilename(1358,839);printnl(1359);
slowprint(wmakenamestring(fmtfile));begin decr(strptr);
poolptr:=strstart[strptr];end;printnl(344);
slowprint(formatident){:1341};{1320:}dumpint(1462916184);
x:=strlen(enginename);formatengine:=xmallocarray(ASCIIcode,x+4);
strcpy(stringcast(formatengine),enginename);
for k:=x to x+3 do formatengine[k]:=0;x:=x+4-(x mod 4);dumpint(x);
dumpthings(formatengine[0],x);libcfree(formatengine);dumpkanji(fmtfile);
dumpint(499324729);{1400:}dumpthings(xord[0],256);
dumpthings(xchr[0],256);dumpthings(xprn[0],256);{:1400};
dumpint(1073741823);dumpint(hashhigh);dumpint(membot);dumpint(memtop);
dumpint(29572);dumpint(8501);dumpint(607){:1320};
{1414:}dumpint(1296847960);if mltexp then dumpint(1)else dumpint(0);
{:1414};{1322:}dumpint(poolptr);dumpint(strptr);
dumpthings(strstart[0],strptr+1);dumpthings(strpool[0],poolptr);println;
printint(strptr);print(1342);printint(poolptr){:1322};{1324:}sortavail;
varused:=0;dumpint(lomemmax);dumpint(rover);p:=membot;q:=rover;x:=0;
repeat dumpthings(mem[p],q+2-p);x:=x+q+2-p;varused:=varused+q-p;
p:=q+mem[q].hh.lh;q:=mem[q+1].hh.rh;until q=rover;
varused:=varused+lomemmax-p;dynused:=memend+1-himemmin;
dumpthings(mem[p],lomemmax+1-p);x:=x+lomemmax+1-p;dumpint(himemmin);
dumpint(avail);dumpthings(mem[himemmin],memend+1-himemmin);
x:=x+memend+1-himemmin;p:=avail;
while p<>-1073741823 do begin decr(dynused);p:=mem[p].hh.rh;end;
dumpint(varused);dumpint(dynused);println;printint(x);print(1343);
printint(varused);printchar(38);printint(dynused){:1324};
{1326:}{1328:}k:=1;repeat j:=k;
while j<28461 do begin if(eqtb[j].hh.rh=eqtb[j+1].hh.rh)and(eqtb[j].hh.
b0=eqtb[j+1].hh.b0)and(eqtb[j].hh.b1=eqtb[j+1].hh.b1)then goto 41;
incr(j);end;l:=28462;goto 31;41:incr(j);l:=j;
while j<28461 do begin if(eqtb[j].hh.rh<>eqtb[j+1].hh.rh)or(eqtb[j].hh.
b0<>eqtb[j+1].hh.b0)or(eqtb[j].hh.b1<>eqtb[j+1].hh.b1)then goto 31;
incr(j);end;31:dumpint(l-k);dumpthings(eqtb[k],l-k);k:=j+1;dumpint(k-l);
until k=28462{:1328};{1329:}repeat j:=k;
while j<29572 do begin if eqtb[j].int=eqtb[j+1].int then goto 42;
incr(j);end;l:=29573;goto 32;42:incr(j);l:=j;
while j<29572 do begin if eqtb[j].int<>eqtb[j+1].int then goto 32;
incr(j);end;32:dumpint(l-k);dumpthings(eqtb[k],l-k);k:=j+1;dumpint(k-l);
until k>29572;if hashhigh>0 then dumpthings(eqtb[29573],hashhigh);
{:1329};dumpint(parloc);dumpint(writeloc);{1331:}dumpint(hashused);
cscount:=15513-hashused+hashhigh;
for p:=514 to hashused do if hash[p].rh<>0 then begin dumpint(p);
dumphh(hash[p]);incr(cscount);end;
dumpthings(hash[hashused+1],24525-hashused);
if hashhigh>0 then dumpthings(hash[29573],hashhigh);dumpint(cscount);
println;printint(cscount);print(1344){:1331}{:1326};
{1333:}dumpint(fmemptr);dumpthings(fontinfo[0],fmemptr);
dumpint(fontptr);{1335:}begin dumpthings(fontdir[0],fontptr+1);
dumpthings(fontnumext[0],fontptr+1);dumpthings(fontcheck[0],fontptr+1);
dumpthings(fontsize[0],fontptr+1);dumpthings(fontdsize[0],fontptr+1);
dumpthings(fontparams[0],fontptr+1);dumpthings(hyphenchar[0],fontptr+1);
dumpthings(skewchar[0],fontptr+1);dumpthings(fontname[0],fontptr+1);
dumpthings(fontarea[0],fontptr+1);dumpthings(fontbc[0],fontptr+1);
dumpthings(fontec[0],fontptr+1);dumpthings(ctypebase[0],fontptr+1);
dumpthings(charbase[0],fontptr+1);dumpthings(widthbase[0],fontptr+1);
dumpthings(heightbase[0],fontptr+1);dumpthings(depthbase[0],fontptr+1);
dumpthings(italicbase[0],fontptr+1);
dumpthings(ligkernbase[0],fontptr+1);dumpthings(kernbase[0],fontptr+1);
dumpthings(extenbase[0],fontptr+1);dumpthings(parambase[0],fontptr+1);
dumpthings(fontglue[0],fontptr+1);dumpthings(bcharlabel[0],fontptr+1);
dumpthings(fontbchar[0],fontptr+1);
dumpthings(fontfalsebchar[0],fontptr+1);
for k:=0 to fontptr do begin printnl(1348);printesc(hash[15525+k].rh);
printchar(61);printfilename(fontname[k],fontarea[k],344);
if fontsize[k]<>fontdsize[k]then begin print(790);
printscaled(fontsize[k]);print(416);end;end;end{:1335};println;
printint(fmemptr-7);print(1345);printint(fontptr-0);
if fontptr<>1 then print(1346)else print(1347){:1333};
{1337:}dumpint(hyphcount);if hyphnext<=607 then hyphnext:=hyphsize;
dumpint(hyphnext);
for k:=0 to hyphsize do if hyphword[k]<>0 then begin dumpint(k+65536*
hyphlink[k]);dumpint(hyphword[k]);dumpint(hyphlist[k]);end;println;
printint(hyphcount);if hyphcount<>1 then print(1349)else print(1350);
if trienotready then inittrie;dumpint(triemax);
dumpthings(trietrl[0],triemax+1);dumpthings(trietro[0],triemax+1);
dumpthings(trietrc[0],triemax+1);dumpint(trieopptr);
dumpthings(hyfdistance[1],trieopptr);dumpthings(hyfnum[1],trieopptr);
dumpthings(hyfnext[1],trieopptr);printnl(1351);printint(triemax);
print(1352);printint(trieopptr);
if trieopptr<>1 then print(1353)else print(1354);print(1355);
printint(trieopsize);
for k:=255 downto 0 do if trieused[k]>0 then begin printnl(855);
printint(trieused[k]);print(1356);printint(k);dumpint(k);
dumpint(trieused[k]);end{:1337};{1339:}dumpint(interaction);
dumpint(formatident);dumpint(69069);eqtb[28493].int:=0{:1339};
{1342:}wclose(fmtfile){:1342};end;
endif('INITEX'){:1315}{1361:}{1362:}procedure newwhatsit(s:smallnumber;
w:smallnumber);var p:halfword;begin p:=getnode(w);mem[p].hh.b0:=10;
mem[p].hh.b1:=s;mem[curlist.tailfield].hh.rh:=p;curlist.tailfield:=p;
end;{:1362}{1363:}procedure newwritewhatsit(w:smallnumber);
begin newwhatsit(curchr,w);
if w<>2 then scanfourbitint else begin scanint;
if curval<0 then curval:=17 else if(curval>15)and(curval<>18)then curval
:=16;end;mem[curlist.tailfield+1].hh.lh:=curval;end;
{:1363}procedure doextension;var k:integer;p:halfword;
begin case curchr of 0:{1364:}begin newwritewhatsit(3);
scanoptionalequals;scanfilename;mem[curlist.tailfield+1].hh.rh:=curname;
mem[curlist.tailfield+2].hh.lh:=curarea;
mem[curlist.tailfield+2].hh.rh:=curext;end{:1364};
1:{1365:}begin k:=curcs;newwritewhatsit(2);curcs:=k;
p:=scantoks(false,false);mem[curlist.tailfield+1].hh.rh:=defref;
end{:1365};2:{1366:}begin newwritewhatsit(2);
mem[curlist.tailfield+1].hh.rh:=-1073741823;end{:1366};
3:{1367:}begin newwhatsit(3,2);
mem[curlist.tailfield+1].hh.lh:=-1073741823;p:=scantoks(false,true);
mem[curlist.tailfield+1].hh.rh:=defref;end{:1367};
4:{1388:}begin getxtoken;
if(curcmd=64)and(curchr<=2)then begin p:=curlist.tailfield;doextension;
outwhat(curlist.tailfield);flushnodelist(curlist.tailfield);
curlist.tailfield:=p;mem[p].hh.rh:=-1073741823;end else backinput;
end{:1388};
5:{1390:}if abs(curlist.modefield)<>117 then reportillegalcase else
begin newwhatsit(4,2);scanint;
if curval<=0 then curlist.auxfield.hh.rh:=0 else if curval>255 then
curlist.auxfield.hh.rh:=0 else curlist.auxfield.hh.rh:=curval;
mem[curlist.tailfield+1].hh.rh:=curlist.auxfield.hh.rh;
mem[curlist.tailfield+1].hh.b0:=normmin(eqtb[28514].int);
mem[curlist.tailfield+1].hh.b1:=normmin(eqtb[28515].int);end{:1390};
others:confusion(1376)end;end;{:1361}{1389:}procedure fixlanguage;
var l:ASCIIcode;
begin if eqtb[28513].int<=0 then l:=0 else if eqtb[28513].int>255 then l
:=0 else l:=eqtb[28513].int;
if l<>curlist.auxfield.hh.rh then begin newwhatsit(4,2);
mem[curlist.tailfield+1].hh.rh:=l;curlist.auxfield.hh.rh:=l;
mem[curlist.tailfield+1].hh.b0:=normmin(eqtb[28514].int);
mem[curlist.tailfield+1].hh.b1:=normmin(eqtb[28515].int);end;end;
{:1389}{1501:}procedure setmathkchar(c:integer);var p:halfword;
begin p:=newnoad;mem[p+1].hh.rh:=6;inhibitglueflag:=false;
mem[p+1].hh.b1:=0;mem[p+4].hh.lh:=c;mem[p+1].hh.b0:=eqtb[28507].int;
if fontdir[eqtb[25583+mem[p+1].hh.b0+cursize].hh.rh]=0 then begin begin
if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1203);
end;begin helpptr:=1;helpline[0]:=1202;end;error;end;mem[p].hh.b0:=18;
mem[curlist.tailfield].hh.rh:=p;curlist.tailfield:=p;end;
{:1501}{1508:}procedure insertsrcspecial;var toklist,p,q:halfword;
begin if(sourcefilenamestack[inopen]>0 and isnewsource(
sourcefilenamestack[inopen],line))then begin toklist:=getavail;
p:=toklist;mem[p].hh.lh:=536886435;mem[p].hh.rh:=getavail;
p:=mem[p].hh.rh;mem[p].hh.lh:=379;
q:=strtoks(makesrcspecial(sourcefilenamestack[inopen],line));
mem[p].hh.rh:=mem[memtop-3].hh.rh;p:=q;mem[p].hh.rh:=getavail;
p:=mem[p].hh.rh;mem[p].hh.lh:=637;begintokenlist(toklist,4);
remembersourceinfo(sourcefilenamestack[inopen],line);end;end;
procedure appendsrcspecial;var q:halfword;
begin if(sourcefilenamestack[inopen]>0 and isnewsource(
sourcefilenamestack[inopen],line))then begin newwhatsit(3,2);
mem[curlist.tailfield+1].hh.lh:=0;defref:=getavail;
mem[defref].hh.lh:=-1073741823;
q:=strtoks(makesrcspecial(sourcefilenamestack[inopen],line));
mem[defref].hh.rh:=mem[memtop-3].hh.rh;
mem[curlist.tailfield+1].hh.rh:=defref;
remembersourceinfo(sourcefilenamestack[inopen],line);end;end;
{:1508}{1080:}procedure handlerightbrace;var p,q:halfword;r:halfword;
d:scaled;f:integer;begin case curgroup of 1:unsave;
0:begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1102);
end;begin helpptr:=2;helpline[1]:=1103;helpline[0]:=1104;end;error;end;
14,15,16:extrarightbrace;
{1097:}2:begin adjusthlist(curlist.headfield,false);package(0);end;
3:begin adjusthlist(curlist.headfield,false);adjusttail:=memtop-5;
package(0);end;4:begin endgraf;package(0);end;5:begin endgraf;
package(4);end;{:1097}{1112:}11:begin endgraf;q:=eqtb[24537].hh.rh;
incr(mem[q].hh.rh);d:=eqtb[29044].int;f:=eqtb[28504].int;unsave;
decr(saveptr);p:=vpackage(mem[curlist.headfield].hh.rh,0,1,1073741823);
mem[p].hh.b1:=abs(curlist.dirfield);popnest;
if savestack[saveptr+0].int<255 then begin r:=getnode(6);
mem[r].hh.b0:=4;mem[r].hh.b1:=savestack[saveptr+0].int;
mem[r+3].int:=mem[p+3].int+mem[p+2].int;mem[r+4].hh.lh:=mem[p+5].hh.rh;
mem[r+4].hh.rh:=q;mem[r+2].int:=d;mem[r+1].int:=f;
mem[r+5].hh.b1:=(mem[p].hh.b1);
if not(curlist.tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)
then begin mem[curlist.pnodefield].hh.rh:=r;
mem[mem[curlist.pnodefield].hh.rh].hh.rh:=curlist.tailfield;
curlist.pnodefield:=mem[curlist.pnodefield].hh.rh;
end else begin mem[curlist.tailfield].hh.rh:=r;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
end else begin if(mem[p].hh.b1)<>curlist.adjdirfield then begin begin if
interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1155);
end;begin helpptr:=1;helpline[0]:=1156;end;error;
flushnodelist(mem[p+5].hh.rh);end else begin r:=getnode(2);
mem[r].hh.b0:=7;mem[r+1].int:=mem[p+5].hh.rh;deleteglueref(q);
if not(curlist.tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)
then begin mem[curlist.pnodefield].hh.rh:=r;
mem[mem[curlist.pnodefield].hh.rh].hh.rh:=curlist.tailfield;
curlist.pnodefield:=mem[curlist.pnodefield].hh.rh;
end else begin mem[curlist.tailfield].hh.rh:=r;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;end;end;
deleteglueref(mem[p+7].hh.rh);deleteglueref(mem[p+7].hh.lh);
freenode(p,10);if nestptr=0 then buildpage;end;
8:{1037:}begin if(curinput.locfield<>-1073741823)or((curinput.indexfield
<>6)and(curinput.indexfield<>3))then{1038:}begin begin if interaction=3
then;if filelineerrorstylep then printfileline else printnl(263);
print(1069);end;begin helpptr:=2;helpline[1]:=1070;helpline[0]:=1071;
end;error;repeat gettoken;until curinput.locfield=-1073741823;
end{:1038};endtokenlist;endgraf;unsave;outputactive:=false;
insertpenalties:=0;
{1039:}if eqtb[25581].hh.rh<>-1073741823 then begin begin if interaction
=3 then;if filelineerrorstylep then printfileline else printnl(263);
print(1072);end;printesc(428);printint(255);begin helpptr:=3;
helpline[2]:=1073;helpline[1]:=1074;helpline[0]:=1075;end;boxerror(255);
end{:1039};
if curlist.tailfield<>curlist.headfield then begin mem[pagetail].hh.rh:=
mem[curlist.headfield].hh.rh;pagetail:=curlist.tailfield;end;
if mem[memtop-2].hh.rh<>-1073741823 then begin if mem[memtop-1].hh.rh=
-1073741823 then nest[0].tailfield:=pagetail;
mem[pagetail].hh.rh:=mem[memtop-1].hh.rh;
mem[memtop-1].hh.rh:=mem[memtop-2].hh.rh;
mem[memtop-2].hh.rh:=-1073741823;pagetail:=memtop-2;end;popnest;
buildpage;end{:1037};{:1112}{1130:}10:builddiscretionary;
{:1130}{1144:}6:begin backinput;curtok:=536886426;
begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(666);
end;printesc(956);print(667);begin helpptr:=1;helpline[0]:=1197;end;
inserror;end;{:1144}{1145:}7:begin endgraf;unsave;alignpeek;end;
{:1145}{1180:}12:begin endgraf;unsave;saveptr:=saveptr-2;
p:=vpackage(mem[curlist.headfield].hh.rh,savestack[saveptr+1].int,
savestack[saveptr+0].int,1073741823);
mem[p].hh.b1:=abs(curlist.dirfield);popnest;
if(mem[p].hh.b1)<>abs(curlist.dirfield)then p:=newdirnode(p,abs(curlist.
dirfield));begin mem[curlist.tailfield].hh.rh:=newnoad;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=31;mem[curlist.tailfield+1].hh.rh:=2;
mem[curlist.tailfield+1].hh.lh:=p;end;{:1180}{1185:}13:buildchoices;
{:1185}{1198:}9:begin unsave;decr(saveptr);
mem[savestack[saveptr+0].int].hh.rh:=4;p:=finmlist(-1073741823);
mem[savestack[saveptr+0].int].hh.lh:=p;
if p<>-1073741823 then if mem[p].hh.rh=-1073741823 then if mem[p].hh.b0=
18 then begin if mem[p+3].hh.rh=0 then if((mem[p+2].hh.rh=0)and(mem[p+4]
.hh.lh=-1073741823))then begin mem[savestack[saveptr+0].int].hh:=mem[p+1
].hh;freenode(p,5);end;
end else if mem[p].hh.b0=30 then if savestack[saveptr+0].int=curlist.
tailfield+1 then if mem[curlist.tailfield].hh.b0=18 then{1199:}begin q:=
curlist.headfield;
while mem[q].hh.rh<>curlist.tailfield do q:=mem[q].hh.rh;
mem[q].hh.rh:=p;freenode(curlist.tailfield,5);curlist.tailfield:=p;
end{:1199};end;{:1198}others:confusion(1105)end;end;
{:1080}procedure maincontrol;
label 60,21,70,80,130,131,133,141,150,90,91,92,95,100,101,110,111,112,
120,10;var t:integer;cx:KANJIcode;kp:halfword;gp,gq:halfword;
disp:scaled;inskp:boolean;
begin if eqtb[25067].hh.rh<>-1073741823 then begintokenlist(eqtb[25067].
hh.rh,12);60:getxtoken;
21:{1042:}if interrupt<>0 then if OKtointerrupt then begin backinput;
begin if interrupt<>0 then pauseforinstructions;end;goto 60;end;
ifdef('TEXMF_DEBUG')if panicking then checkmem(false);
endif('TEXMF_DEBUG')if eqtb[28498].int>0 then showcurcmdchr{:1042};
inskp:=false;case abs(curlist.modefield)+curcmd of 128,129:goto 70;
133,134,135,136,191:goto 130;
190:if checkecharrange(curchr)then goto 70 else goto 130;
137:begin scancharnum;curchr:=curval;
if checkecharrange(curchr)then goto 70 else goto 130;end;
171:begin scancharnum;curchr:=curval;goto 130;end;187:begin getxtoken;
if(curcmd=11)or(curcmd=12)or((curcmd>=16)and(curcmd<=19))or(curcmd=73)or
(curcmd=20)or(curcmd=74)or(curcmd=54)then cancelboundary:=true;goto 21;
end;127:if curlist.auxfield.hh.lh=1000 then goto 120 else appspace;
186,302:goto 120;{1057:}1,117,233,11,243,303:;
44,160,276:begin{417:}repeat getxtoken;until curcmd<>10{:417};goto 21;
end;15:if itsallover then goto 10;
{1060:}27,142,258,77,193,309,{:1060}{1110:}43,{:1110}{1123:}49,{:1123}
{1156:}53,169,{:1156}7,123,239:reportillegalcase;
{1058:}8,124,9,125,22,138,76,192,56,172,16,132,54,170,58,174,72,188,59,
175,60,176,62,178,61,177,35,151,57,173,33,149,51,167,242,246,247,264,261
,270,273{:1058}:insertdollarsign;
{1068:}41,156,272:begin begin mem[curlist.tailfield].hh.rh:=scanrulespec
;curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
if abs(curlist.modefield)=1 then curlist.auxfield.int:=-65536000 else if
abs(curlist.modefield)=117 then curlist.auxfield.hh.lh:=1000;end;
{:1068}{1069:}32,147,263,265:appendglue;34,150,266,267:appendkern;
{:1069}{1075:}2,118:newsavelevel(1);67,183,299:newsavelevel(14);
68,184,300:if curgroup=14 then unsave else offsave;
{:1075}{1079:}3,119,235:handlerightbrace;
{:1079}{1085:}26,143,259:begin t:=curchr;scandimen(false,false,false);
if t=0 then scanbox(curval)else scanbox(-curval);end;
36,152,268:scanbox(1073742237+curchr);25,141,257:beginbox(0);
79,195,311:begin if curgroup<>6 then if curlist.headfield=curlist.
tailfield then begin curlist.dirfield:=curchr;
if curlist.modefield=1 then pagedir:=curchr;
end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(1127);
end;printcmdchr(curcmd,curchr);print(1128);begin helpptr:=2;
helpline[1]:=1129;helpline[0]:=1130;end;error;
end else begin begin if interaction=3 then;
if filelineerrorstylep then printfileline else printnl(263);print(726);
end;printcmdchr(curcmd,curchr);print(1131);begin helpptr:=2;
helpline[1]:=1132;helpline[0]:=1133;end;error;end end;
{:1085}{1102:}48:newgraf(curchr>0);
12,13,21,74,55,75,4,28,40,50,52,31,38,17,18,19,20,70,71:begin backinput;
newgraf(true);end;{:1102}{1104:}164,280:indentinhmode;
{:1104}{1106:}14:begin normalparagraph;
if curlist.modefield>0 then buildpage;end;
130:begin if alignstate<0 then offsave;endgraf;
if curlist.modefield=1 then buildpage;end;
131,148,157,145,153:headforvmode;
{:1106}{1109:}42,158,274,159,275:begininsertoradjust;
23,139,255:makemark;{:1109}{1114:}47,163,279:appendpenalty;
{:1114}{1116:}30,146,262:deletelast;{:1116}{1121:}29,144,260:unpackage;
{:1121}{1124:}165:appenditaliccorrection;
281:begin mem[curlist.tailfield].hh.rh:=newkern(0);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
{:1124}{1128:}168,284:appenddiscretionary;{:1128}{1134:}166:makeaccent;
{:1134}{1138:}6,122,238,5,121,237:alignerror;39,155,271:noalignerror;
69,185,301:omiterror;{:1138}{1142:}37,154:initalign;
269:if privileged then if curgroup=15 then initalign else offsave;
10,126:doendv;{:1142}{1146:}73,189,305:cserror;
{:1146}{1149:}120:initmath;
{:1149}{1152:}285:if privileged then if curgroup=15 then starteqno else
offsave;
{:1152}{1162:}234:begin begin mem[curlist.tailfield].hh.rh:=newnoad;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;backinput;
scanmath(curlist.tailfield+1,curlist.tailfield+4);end;
{:1162}{1166:}244,245,306:if checkecharrange(curchr)then if curchr<128
then setmathchar(eqtb[27950+curchr].hh.rh)else setmathchar(curchr)else
setmathkchar(curchr);249,250,251,252:begin cx:=curchr;setmathkchar(cx);
end;253:begin scancharnum;curchr:=curval;
if checkecharrange(curchr)then if curchr<128 then setmathchar(eqtb[
27950+curchr].hh.rh)else setmathchar(curchr)else setmathkchar(curchr);
end;307:setmathkchar(curchr);287:begin scancharnum;curchr:=curval;
setmathkchar(curchr);end;254:begin scanfifteenbitint;
setmathchar(curval);end;308:setmathchar(curchr);
248:begin scantwentysevenbitint;setmathchar(curval div 4096);end;
{:1166}{1170:}288:begin begin mem[curlist.tailfield].hh.rh:=newnoad;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=curchr;
scanmath(curlist.tailfield+1,curlist.tailfield+4);end;
289:mathlimitswitch;{:1170}{1174:}304:mathradical;
{:1174}{1176:}282,283:mathac;{:1176}{1179:}294:begin scanspec(12,false);
normalparagraph;inhibitglueflag:=false;pushnest;curlist.modefield:=-1;
curlist.auxfield.int:=-65536000;
if(insertsrcspecialeveryvbox)then insertsrcspecial;
if eqtb[25066].hh.rh<>-1073741823 then begintokenlist(eqtb[25066].hh.rh,
11);end;
{:1179}{1183:}291:begin mem[curlist.tailfield].hh.rh:=newstyle(curchr);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
293:begin begin mem[curlist.tailfield].hh.rh:=newglue(membot);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=98;end;292:appendchoices;
{:1183}{1187:}241,240:subsup;{:1187}{1192:}290:mathfraction;
{:1192}{1202:}286:mathleftright;
{:1202}{1205:}236:if curgroup=15 then aftermath else offsave;
{:1205}{1222:}88,204,320,89,205,321,115,231,347,116,232,348,90,206,322,
80,196,312,81,197,313,82,198,314,101,217,333,102,218,334,83,199,315,84,
200,316,85,201,317,86,202,318,87,203,319,91,207,323,92,208,324,93,209,
325,94,210,326,95,211,327,96,212,328,97,213,329,98,214,330,99,215,331,
100,216,332,103,219,335,104,220,336,105,221,337,106,222,338,107,223,339,
108,224,340,109,225,341,110,226,342,111,227,343,112,228,344,113,229,345,
114,230,346:prefixedcommand;{:1222}{1281:}45,161,277:begin gettoken;
aftertoken:=curtok;end;{:1281}{1284:}46,162,278:begin gettoken;
saveforafter(curtok);end;{:1284}{1287:}66,182,298:openorclosein;
{:1287}{1289:}64,180,296:issuemessage;
{:1289}{1298:}63,179,295:shiftcase;
{:1298}{1303:}24,140,256:showwhatever;
{:1303}{1465:}78,194,310:inhibitglueflag:=true;
{:1465}{1360:}65,181,297:doextension;{:1360}{:1057}end;goto 60;
130:{1502:}if(curlist.tailfield>=himemmin)then begin cx:=mem[curlist.
tailfield].hh.b1;{1478:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=2 then begin begin mem[
curlist.tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1478};
end else if mem[curlist.tailfield].hh.b0=8 then begin cx:=mem[curlist.
tailfield+1].hh.b1;{1478:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=2 then begin begin mem[
curlist.tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1478};end;
if curlist.dirfield=3 then begin if fontdir[mainf]=3 then disp:=0 else
if fontdir[mainf]=4 then disp:=eqtb[29059].int-eqtb[29060].int else disp
:=eqtb[29059].int;mainf:=eqtb[25632].hh.rh;
end else begin if fontdir[mainf]=4 then disp:=0 else if fontdir[mainf]=3
then disp:=eqtb[29060].int-eqtb[29059].int else disp:=eqtb[29060].int;
mainf:=eqtb[25631].hh.rh;end;
{1504:}if disp<>0 then begin if not(curlist.tailfield>=himemmin)and(mem[
curlist.tailfield].hh.b0=5)then begin mem[curlist.tailfield+1].int:=0;
end else begin curlist.pnodefield:=curlist.tailfield;
begin mem[curlist.tailfield].hh.rh:=getnode(2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=5;mem[curlist.tailfield+1].int:=0;
curlist.pdispfield:=disp;end;end;{:1504};inskp:=false;
ligaturepresent:=false;curl:=getjfmpos(curchr,mainf);
maini:=fontinfo[charbase[mainf]+0].qqqq;goto 133;
131:curlist.auxfield.hh.lh:=1000;
if mainf<>0 then begin begin mainp:=avail;
if mainp=-1073741823 then mainp:=getavail else begin avail:=mem[mainp].
hh.rh;mem[mainp].hh.rh:=-1073741823;ifdef('STAT')incr(dynused);
endif('STAT')end;end;mem[mainp].hh.b0:=mainf;mem[mainp].hh.b1:=curl;
mem[curlist.tailfield].hh.rh:=mainp;curlist.tailfield:=mainp;
curlist.lastjchrfield:=curlist.tailfield;begin mainp:=avail;
if mainp=-1073741823 then mainp:=getavail else begin avail:=mem[mainp].
hh.rh;mem[mainp].hh.rh:=-1073741823;ifdef('STAT')incr(dynused);
endif('STAT')end;end;mem[mainp].hh.lh:=curchr+curcmd*16777216;
mem[curlist.tailfield].hh.rh:=mainp;curlist.tailfield:=mainp;cx:=curchr;
{1476:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=1 then begin if not(curq
>=himemmin)and(mem[curq].hh.b0=14)then mem[curq+1].int:=mem[curq+1].int+
eqtb[29317+kp].int else begin mainp:=mem[curq].hh.rh;
mem[curq].hh.rh:=newpenalty(eqtb[29317+kp].int);
mem[mem[curq].hh.rh].hh.b1:=2;mem[mem[curq].hh.rh].hh.rh:=mainp;end;
end else if eqtb[26916+kp].hh.b0=2 then begin begin mem[curlist.
tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1476};end;inskp:=false;
150:getnext;maini:=fontinfo[charbase[mainf]+curl].qqqq;
case curcmd of 16,17,18,19:begin curl:=getjfmpos(curchr,mainf);goto 133;
end;11,12:begin inskp:=true;curl:=0;goto 133;end;end;xtoken;
case curcmd of 16,17,18,19:curl:=getjfmpos(curchr,mainf);
11,12:begin inskp:=true;curl:=0;end;
73:begin if checkecharrange(curchr)then begin inskp:=true;curl:=0;
end else curl:=getjfmpos(curchr,mainf);end;20:begin scancharnum;
curchr:=curval;if checkecharrange(curchr)then begin inskp:=true;curl:=0;
end else curl:=getjfmpos(curchr,mainf);end;
74:begin curl:=getjfmpos(curchr,mainf);end;54:begin scancharnum;
curchr:=curval;curl:=getjfmpos(curchr,mainf);end;
77:begin inhibitglueflag:=true;goto 150;end;
others:begin inskp:=1073741823;curl:=0;curr:=256;ligstack:=-1073741823;
end;end;133:if inskp=true then{1477:}begin kp:=getkinsokupos(curchr,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=1 then if not(curlist.
tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=14)then mem[curlist
.tailfield+1].int:=mem[curlist.tailfield+1].int+eqtb[29317+kp].int else
begin begin mem[curlist.tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int)
;curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1477};
if mainf<>0 then begin{1505:}curq:=curlist.tailfield;
if inhibitglueflag<>true then begin if((maini.b2)mod 4)=1 then begin
maink:=ligkernbase[mainf]+maini.b3;repeat mainj:=fontinfo[maink].qqqq;
if mainj.b1=curl then begin if mainj.b2<128 then begin gp:=fontglue[
mainf];curr:=mainj.b3;
if gp<>-1073741823 then begin while((mem[gp].hh.b0<>curr)and(mem[gp].hh.
rh<>-1073741823))do gp:=mem[gp].hh.rh;gq:=mem[gp+1].hh.lh;
end else begin gp:=getnode(2);fontglue[mainf]:=gp;gq:=-1073741823;end;
if gq=-1073741823 then begin mem[gp].hh.b0:=curr;gq:=newspec(membot);
mem[gp+1].hh.lh:=gq;maink:=extenbase[mainf]+(curr)*3;
mem[gq+1].int:=fontinfo[maink].int;mem[gq+2].int:=fontinfo[maink+1].int;
mem[gq+3].int:=fontinfo[maink+2].int;incr(mem[gq].hh.rh);
mem[gp].hh.rh:=getnode(2);gp:=mem[gp].hh.rh;
mem[gp+1].hh.lh:=-1073741823;mem[gp].hh.rh:=-1073741823;end;
begin mem[curlist.tailfield].hh.rh:=newglue(gq);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=21;goto 141;
end else begin begin mem[curlist.tailfield].hh.rh:=newkern(fontinfo[
kernbase[mainf]+256*mainj.b2+mainj.b3].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;goto 141;end;end;
incr(maink);until mainj.b0>=128;end;end;141:inhibitglueflag:=false;
{:1505};end else inhibitglueflag:=false;
if inskp=false then begin goto 131;
end else if inskp=true then begin inskp:=false;goto 70;
end else begin goto 21;end;{:1502};70:inhibitglueflag:=false;
{1045:}if((curlist.headfield=curlist.tailfield)and(curlist.modefield>0))
then begin if(insertsrcspecialauto)then appendsrcspecial;end;
mains:=eqtb[27694+curchr].hh.rh;
if mains=1000 then curlist.auxfield.hh.lh:=1000 else if mains<1000 then
begin if mains>0 then curlist.auxfield.hh.lh:=mains;
end else if curlist.auxfield.hh.lh<1000 then curlist.auxfield.hh.lh:=
1000 else curlist.auxfield.hh.lh:=mains;
if curlist.dirfield=3 then disp:=eqtb[29059].int else disp:=eqtb[29060].
int;{1503:}begin if not(curlist.tailfield>=himemmin)and(mem[curlist.
tailfield].hh.b0=5)then begin if curlist.pdispfield=disp then begin
freenode(curlist.tailfield,2);curlist.tailfield:=curlist.pnodefield;
mem[curlist.tailfield].hh.rh:=-1073741823;
end else mem[curlist.tailfield+1].int:=disp;
end else if disp<>0 then begin curlist.pnodefield:=curlist.tailfield;
begin mem[curlist.tailfield].hh.rh:=getnode(2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=5;mem[curlist.tailfield+1].int:=disp;
curlist.pdispfield:=disp;end;end;{:1503};mainf:=eqtb[25582].hh.rh;
bchar:=fontbchar[mainf];falsebchar:=fontfalsebchar[mainf];
if curlist.modefield>0 then if eqtb[28513].int<>curlist.auxfield.hh.rh
then fixlanguage;begin ligstack:=avail;
if ligstack=-1073741823 then ligstack:=getavail else begin avail:=mem[
ligstack].hh.rh;mem[ligstack].hh.rh:=-1073741823;
ifdef('STAT')incr(dynused);endif('STAT')end;end;
mem[ligstack].hh.b0:=mainf;curl:=curchr;mem[ligstack].hh.b1:=curl;
curq:=curlist.tailfield;
if cancelboundary then begin cancelboundary:=false;maink:=0;
end else maink:=bcharlabel[mainf];if maink=0 then goto 92;curr:=curl;
curl:=256;goto 111;
80:{1046:}if curl<256 then begin if mem[curq].hh.rh>-1073741823 then if
mem[curlist.tailfield].hh.b1=hyphenchar[mainf]then insdisc:=true;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if insdisc then begin insdisc:=false;
if curlist.modefield>0 then begin mem[curlist.tailfield].hh.rh:=newdisc;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;end;end{:1046};
90:{1047:}if ligstack=-1073741823 then begin{1504:}if disp<>0 then begin
if not(curlist.tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)
then begin mem[curlist.tailfield+1].int:=0;
end else begin curlist.pnodefield:=curlist.tailfield;
begin mem[curlist.tailfield].hh.rh:=getnode(2);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b0:=5;mem[curlist.tailfield+1].int:=0;
curlist.pdispfield:=disp;end;end;{:1504};goto 21;end;
curq:=curlist.tailfield;curl:=mem[ligstack].hh.b1;
91:if not(ligstack>=himemmin)then goto 95;
92:if(effectivechar(false,mainf,curchr)>fontec[mainf])or(effectivechar(
false,mainf,curchr)<fontbc[mainf])then begin charwarning(mainf,curchr);
begin mem[ligstack].hh.rh:=avail;avail:=ligstack;
ifdef('STAT')decr(dynused);endif('STAT')end;goto 60;end;
maini:=effectivecharinfo(mainf,curl);
if not(maini.b0>0)then begin charwarning(mainf,curchr);
begin mem[ligstack].hh.rh:=avail;avail:=ligstack;
ifdef('STAT')decr(dynused);endif('STAT')end;goto 60;end;
mem[curlist.tailfield].hh.rh:=ligstack;
curlist.tailfield:=ligstack{:1047};100:{1049:}getnext;
if curcmd=11 then goto 101;
if(curcmd>=16)and(curcmd<=19)then{1050:}begin bchar:=256;curr:=bchar;
ligstack:=-1073741823;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if inskp=true then begin cx:=curl;
{1476:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=1 then begin if not(curq
>=himemmin)and(mem[curq].hh.b0=14)then mem[curq+1].int:=mem[curq+1].int+
eqtb[29317+kp].int else begin mainp:=mem[curq].hh.rh;
mem[curq].hh.rh:=newpenalty(eqtb[29317+kp].int);
mem[mem[curq].hh.rh].hh.b1:=2;mem[mem[curq].hh.rh].hh.rh:=mainp;end;
end else if eqtb[26916+kp].hh.b0=2 then begin begin mem[curlist.
tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1476};end;inskp:=false;
goto 130;end{:1050};if curcmd=12 then goto 101;
if curcmd=73 then begin if checkecharrange(curchr)then goto 101 else
{1050:}begin bchar:=256;curr:=bchar;ligstack:=-1073741823;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if inskp=true then begin cx:=curl;
{1476:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=1 then begin if not(curq
>=himemmin)and(mem[curq].hh.b0=14)then mem[curq+1].int:=mem[curq+1].int+
eqtb[29317+kp].int else begin mainp:=mem[curq].hh.rh;
mem[curq].hh.rh:=newpenalty(eqtb[29317+kp].int);
mem[mem[curq].hh.rh].hh.b1:=2;mem[mem[curq].hh.rh].hh.rh:=mainp;end;
end else if eqtb[26916+kp].hh.b0=2 then begin begin mem[curlist.
tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1476};end;inskp:=false;
goto 130;end{:1050};end;if curcmd=74 then{1050:}begin bchar:=256;
curr:=bchar;ligstack:=-1073741823;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if inskp=true then begin cx:=curl;
{1476:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=1 then begin if not(curq
>=himemmin)and(mem[curq].hh.b0=14)then mem[curq+1].int:=mem[curq+1].int+
eqtb[29317+kp].int else begin mainp:=mem[curq].hh.rh;
mem[curq].hh.rh:=newpenalty(eqtb[29317+kp].int);
mem[mem[curq].hh.rh].hh.b1:=2;mem[mem[curq].hh.rh].hh.rh:=mainp;end;
end else if eqtb[26916+kp].hh.b0=2 then begin begin mem[curlist.
tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1476};end;inskp:=false;
goto 130;end{:1050};xtoken;if curcmd=11 then goto 101;
if(curcmd>=16)and(curcmd<=19)then{1050:}begin bchar:=256;curr:=bchar;
ligstack:=-1073741823;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if inskp=true then begin cx:=curl;
{1476:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=1 then begin if not(curq
>=himemmin)and(mem[curq].hh.b0=14)then mem[curq+1].int:=mem[curq+1].int+
eqtb[29317+kp].int else begin mainp:=mem[curq].hh.rh;
mem[curq].hh.rh:=newpenalty(eqtb[29317+kp].int);
mem[mem[curq].hh.rh].hh.b1:=2;mem[mem[curq].hh.rh].hh.rh:=mainp;end;
end else if eqtb[26916+kp].hh.b0=2 then begin begin mem[curlist.
tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1476};end;inskp:=false;
goto 130;end{:1050};if curcmd=12 then goto 101;
if curcmd=73 then begin if checkecharrange(curchr)then goto 101 else
{1050:}begin bchar:=256;curr:=bchar;ligstack:=-1073741823;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if inskp=true then begin cx:=curl;
{1476:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=1 then begin if not(curq
>=himemmin)and(mem[curq].hh.b0=14)then mem[curq+1].int:=mem[curq+1].int+
eqtb[29317+kp].int else begin mainp:=mem[curq].hh.rh;
mem[curq].hh.rh:=newpenalty(eqtb[29317+kp].int);
mem[mem[curq].hh.rh].hh.b1:=2;mem[mem[curq].hh.rh].hh.rh:=mainp;end;
end else if eqtb[26916+kp].hh.b0=2 then begin begin mem[curlist.
tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1476};end;inskp:=false;
goto 130;end{:1050};end;if curcmd=20 then begin scancharnum;
curchr:=curval;
if checkecharrange(curchr)then goto 101 else{1050:}begin bchar:=256;
curr:=bchar;ligstack:=-1073741823;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if inskp=true then begin cx:=curl;
{1476:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=1 then begin if not(curq
>=himemmin)and(mem[curq].hh.b0=14)then mem[curq+1].int:=mem[curq+1].int+
eqtb[29317+kp].int else begin mainp:=mem[curq].hh.rh;
mem[curq].hh.rh:=newpenalty(eqtb[29317+kp].int);
mem[mem[curq].hh.rh].hh.b1:=2;mem[mem[curq].hh.rh].hh.rh:=mainp;end;
end else if eqtb[26916+kp].hh.b0=2 then begin begin mem[curlist.
tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1476};end;inskp:=false;
goto 130;end{:1050};end;if curcmd=54 then begin scancharnum;
curchr:=curval;{1050:}begin bchar:=256;curr:=bchar;
ligstack:=-1073741823;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if inskp=true then begin cx:=curl;
{1476:}begin kp:=getkinsokupos(cx,1);
if kp<>1000 then begin if eqtb[26916+kp].hh.b0=1 then begin if not(curq
>=himemmin)and(mem[curq].hh.b0=14)then mem[curq+1].int:=mem[curq+1].int+
eqtb[29317+kp].int else begin mainp:=mem[curq].hh.rh;
mem[curq].hh.rh:=newpenalty(eqtb[29317+kp].int);
mem[mem[curq].hh.rh].hh.b1:=2;mem[mem[curq].hh.rh].hh.rh:=mainp;end;
end else if eqtb[26916+kp].hh.b0=2 then begin begin mem[curlist.
tailfield].hh.rh:=newpenalty(eqtb[29317+kp].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;
mem[curlist.tailfield].hh.b1:=2;end;end;end;{:1476};end;inskp:=false;
goto 130;end{:1050};end;if curcmd=77 then begin inhibitglueflag:=true;
goto 100;end;if curcmd=70 then bchar:=256;curr:=bchar;
ligstack:=-1073741823;goto 110;101:mains:=eqtb[27694+curchr].hh.rh;
if mains=1000 then curlist.auxfield.hh.lh:=1000 else if mains<1000 then
begin if mains>0 then curlist.auxfield.hh.lh:=mains;
end else if curlist.auxfield.hh.lh<1000 then curlist.auxfield.hh.lh:=
1000 else curlist.auxfield.hh.lh:=mains;inhibitglueflag:=false;
begin ligstack:=avail;
if ligstack=-1073741823 then ligstack:=getavail else begin avail:=mem[
ligstack].hh.rh;mem[ligstack].hh.rh:=-1073741823;
ifdef('STAT')incr(dynused);endif('STAT')end;end;
mem[ligstack].hh.b0:=mainf;curr:=curchr;mem[ligstack].hh.b1:=curr;
if curr=falsebchar then curr:=256{:1049};
110:{1051:}if((maini.b2)mod 4)<>1 then goto 80;if curr=256 then goto 80;
maink:=ligkernbase[mainf]+maini.b3;mainj:=fontinfo[maink].qqqq;
if mainj.b0<=128 then goto 112;
maink:=ligkernbase[mainf]+256*mainj.b2+mainj.b3+32768-256*(128);
111:mainj:=fontinfo[maink].qqqq;
112:if mainj.b1=curr then if mainj.b0<=128 then{1052:}begin if mainj.b2
>=128 then begin if curl<256 then begin if mem[curq].hh.rh>-1073741823
then if mem[curlist.tailfield].hh.b1=hyphenchar[mainf]then insdisc:=true
;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if rthit then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if insdisc then begin insdisc:=false;
if curlist.modefield>0 then begin mem[curlist.tailfield].hh.rh:=newdisc;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;end;end;
begin mem[curlist.tailfield].hh.rh:=newkern(fontinfo[kernbase[mainf]+256
*mainj.b2+mainj.b3].int);
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;goto 90;end;
if curl=256 then lfthit:=true else if ligstack=-1073741823 then rthit:=
true;begin if interrupt<>0 then pauseforinstructions;end;
case mainj.b2 of 1,5:begin curl:=mainj.b3;
maini:=fontinfo[charbase[mainf]+effectivechar(true,mainf,curl)].qqqq;
ligaturepresent:=true;end;2,6:begin curr:=mainj.b3;
if ligstack=-1073741823 then begin ligstack:=newligitem(curr);
bchar:=256;end else if(ligstack>=himemmin)then begin mainp:=ligstack;
ligstack:=newligitem(curr);mem[ligstack+1].hh.rh:=mainp;
end else mem[ligstack].hh.b1:=curr;end;3:begin curr:=mainj.b3;
mainp:=ligstack;ligstack:=newligitem(curr);mem[ligstack].hh.rh:=mainp;
end;
7,11:begin if curl<256 then begin if mem[curq].hh.rh>-1073741823 then if
mem[curlist.tailfield].hh.b1=hyphenchar[mainf]then insdisc:=true;
if ligaturepresent then begin mainp:=newligature(mainf,curl,mem[curq].hh
.rh);if lfthit then begin mem[mainp].hh.b1:=2;lfthit:=false;end;
if false then if ligstack=-1073741823 then begin incr(mem[mainp].hh.b1);
rthit:=false;end;mem[curq].hh.rh:=mainp;curlist.tailfield:=mainp;
ligaturepresent:=false;end;if insdisc then begin insdisc:=false;
if curlist.modefield>0 then begin mem[curlist.tailfield].hh.rh:=newdisc;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;end;end;
curq:=curlist.tailfield;curl:=mainj.b3;
maini:=fontinfo[charbase[mainf]+effectivechar(true,mainf,curl)].qqqq;
ligaturepresent:=true;end;others:begin curl:=mainj.b3;
ligaturepresent:=true;if ligstack=-1073741823 then goto 80 else goto 91;
end end;if mainj.b2>4 then if mainj.b2<>7 then goto 80;
if curl<256 then goto 110;maink:=bcharlabel[mainf];goto 111;end{:1052};
if mainj.b0=0 then incr(maink)else begin if mainj.b0>=128 then goto 80;
maink:=maink+mainj.b0+1;end;goto 111{:1051};
95:{1048:}mainp:=mem[ligstack+1].hh.rh;
if mainp>-1073741823 then begin mem[curlist.tailfield].hh.rh:=mainp;
curlist.tailfield:=mem[curlist.tailfield].hh.rh;end;tempptr:=ligstack;
ligstack:=mem[tempptr].hh.rh;freenode(tempptr,2);
maini:=fontinfo[charbase[mainf]+effectivechar(true,mainf,curl)].qqqq;
ligaturepresent:=true;
if ligstack=-1073741823 then if mainp>-1073741823 then goto 100 else
curr:=bchar else curr:=mem[ligstack].hh.b1;goto 110{:1048}{:1045};
120:{1053:}if eqtb[24539].hh.rh=membot then begin{1054:}begin mainp:=
fontglue[eqtb[25582].hh.rh];
if mainp=-1073741823 then begin mainp:=newspec(membot);
maink:=parambase[eqtb[25582].hh.rh]+2;
mem[mainp+1].int:=fontinfo[maink].int;
mem[mainp+2].int:=fontinfo[maink+1].int;
mem[mainp+3].int:=fontinfo[maink+2].int;
fontglue[eqtb[25582].hh.rh]:=mainp;end;end{:1054};
tempptr:=newglue(mainp);end else tempptr:=newparamglue(12);
if not(curlist.tailfield>=himemmin)and(mem[curlist.tailfield].hh.b0=5)
then begin mem[curlist.pnodefield].hh.rh:=tempptr;
mem[tempptr].hh.rh:=curlist.tailfield;curlist.pnodefield:=tempptr;
end else begin mem[curlist.tailfield].hh.rh:=tempptr;
curlist.tailfield:=tempptr;end;goto 60{:1053};10:end;
{:1041}{1297:}procedure giveerrhelp;begin tokenshow(eqtb[25069].hh.rh);
end;{:1297}{1316:}{535:}function openfmtfile:boolean;label 40,10;
var j:0..bufsize;begin j:=curinput.locfield;
if buffer[curinput.locfield]=38 then begin incr(curinput.locfield);
j:=curinput.locfield;buffer[last]:=32;while buffer[j]<>32 do incr(j);
packbufferedname(0,curinput.locfield,j-1);
if wopenin(fmtfile)then goto 40;;
write(stdout,'Sorry, I can''t find the format `');
fputs(stringcast(nameoffile+1),stdout);write(stdout,'''; will try `');
fputs(TEXformatdefault+1,stdout);writeln(stdout,'''.');fflush(stdout);
end;packbufferedname(formatdefaultlength-4,1,0);
if not wopenin(fmtfile)then begin;
write(stdout,'I can''t find the format file `');
fputs(TEXformatdefault+1,stdout);writeln(stdout,'''!');
openfmtfile:=false;goto 10;end;40:curinput.locfield:=j;
openfmtfile:=true;10:end;{:535}function loadfmtfile:boolean;
label 6666,10;var j,k:integer;p,q:halfword;x:integer;
formatengine:^ASCIIcode;dummyxord:ASCIIcode;dummyxchr:ASCIIcode;
dummyxprn:ASCIIcode;
begin{1321:}ifdef('INITEX')if iniversion then begin libcfree(fontinfo);
libcfree(strpool);libcfree(strstart);libcfree(yhash);libcfree(zeqtb);
libcfree(yzmem);end;endif('INITEX')undumpint(x);
if debugformatfile then begin write(stderr,'fmtdebug:',
'format magic number');writeln(stderr,' = ',x);end;;
if x<>1462916184 then goto 6666;undumpint(x);
if debugformatfile then begin write(stderr,'fmtdebug:',
'engine name size');writeln(stderr,' = ',x);end;;
if(x<0)or(x>256)then goto 6666;formatengine:=xmallocarray(ASCIIcode,x);
undumpthings(formatengine[0],x);formatengine[x-1]:=0;
if strcmp(enginename,stringcast(formatengine))then begin;
writeln(stdout,'---! ',stringcast(nameoffile+1),' was written by ',
formatengine);libcfree(formatengine);goto 6666;end;
libcfree(formatengine);undumpkanji(fmtfile);undumpint(x);
if debugformatfile then begin write(stderr,'fmtdebug:',
'string pool checksum');writeln(stderr,' = ',x);end;;
if x<>499324729 then begin;
writeln(stdout,'---! ',stringcast(nameoffile+1),' doesn''t match ',
poolname);goto 6666;end;
{1401:}if translatefilename then begin for k:=0 to 255 do undumpthings(
dummyxord,1);for k:=0 to 255 do undumpthings(dummyxchr,1);
for k:=0 to 255 do undumpthings(dummyxprn,1);
end else begin undumpthings(xord[0],256);undumpthings(xchr[0],256);
undumpthings(xprn[0],256);
if eightbitp then for k:=0 to 255 do xprn[k]:=1;end;{:1401};
undumpint(x);if x<>1073741823 then goto 6666;undumpint(hashhigh);
if(hashhigh<0)or(hashhigh>suphashextra)then goto 6666;
if hashextra<hashhigh then hashextra:=hashhigh;eqtbtop:=29572+hashextra;
if hashextra=0 then hashtop:=24526 else hashtop:=eqtbtop;
yhash:=xmallocarray(twohalves,1+hashtop-hashoffset);
hash:=yhash-hashoffset;hash[514].lh:=0;hash[514].rh:=0;
for x:=515 to hashtop do hash[x]:=hash[514];
zeqtb:=xmallocarray(memoryword,eqtbtop+1);eqtb:=zeqtb;
eqtb[24526].hh.b0:=116;eqtb[24526].hh.rh:=-1073741823;
eqtb[24526].hh.b1:=0;for x:=29573 to eqtbtop do eqtb[x]:=eqtb[24526];
undumpint(x);
if debugformatfile then begin write(stderr,'fmtdebug:','mem_bot');
writeln(stderr,' = ',x);end;;if x<>membot then goto 6666;
undumpint(memtop);
if debugformatfile then begin write(stderr,'fmtdebug:','mem_top');
writeln(stderr,' = ',memtop);end;;if membot+1100>memtop then goto 6666;
curlist.headfield:=memtop-1;curlist.tailfield:=memtop-1;
pagetail:=memtop-2;memmin:=membot-extramembot;
memmax:=memtop+extramemtop;
yzmem:=xmallocarray(memoryword,memmax-memmin+1);zmem:=yzmem-memmin;
mem:=zmem;undumpint(x);if x<>29572 then goto 6666;undumpint(x);
if x<>8501 then goto 6666;undumpint(x);if x<>607 then goto 6666{:1321};
{1415:}undumpint(x);if x<>1296847960 then goto 6666;undumpint(x);
if x=1 then mltexenabledp:=true else if x<>0 then goto 6666;{:1415};
{1323:}begin undumpint(x);if x<0 then goto 6666;
if x>suppoolsize-poolfree then begin;
writeln(stdout,'---! Must increase the ','string pool size');goto 6666;
end else if debugformatfile then begin write(stderr,'fmtdebug:',
'string pool size');writeln(stderr,' = ',x);end;;poolptr:=x;end;
if poolsize<poolptr+poolfree then poolsize:=poolptr+poolfree;
begin undumpint(x);if x<0 then goto 6666;
if x>supmaxstrings-stringsfree then begin;
writeln(stdout,'---! Must increase the ','sup strings');goto 6666;
end else if debugformatfile then begin write(stderr,'fmtdebug:',
'sup strings');writeln(stderr,' = ',x);end;;strptr:=x;end;
if maxstrings<strptr+stringsfree then maxstrings:=strptr+stringsfree;
strstart:=xmallocarray(poolpointer,maxstrings);
undumpcheckedthings(0,poolptr,strstart[0],strptr+1);
strpool:=xmallocarray(packedASCIIcode,poolsize);
undumpthings(strpool[0],poolptr);initstrptr:=strptr;
initpoolptr:=poolptr{:1323};{1325:}begin undumpint(x);
if(x<membot+1019)or(x>memtop-14)then goto 6666 else lomemmax:=x;end;
begin undumpint(x);
if(x<membot+20)or(x>lomemmax)then goto 6666 else rover:=x;end;p:=membot;
q:=rover;repeat undumpthings(mem[p],q+2-p);p:=q+mem[q].hh.lh;
if(p>lomemmax)or((q>=mem[q+1].hh.rh)and(mem[q+1].hh.rh<>rover))then goto
6666;q:=mem[q+1].hh.rh;until q=rover;undumpthings(mem[p],lomemmax+1-p);
if memmin<membot-2 then begin p:=mem[rover+1].hh.lh;q:=memmin+1;
mem[memmin].hh.rh:=-1073741823;mem[memmin].hh.lh:=-1073741823;
mem[p+1].hh.rh:=q;mem[rover+1].hh.lh:=q;mem[q+1].hh.rh:=rover;
mem[q+1].hh.lh:=p;mem[q].hh.rh:=1073741823;mem[q].hh.lh:=membot-q;end;
begin undumpint(x);
if(x<lomemmax+1)or(x>memtop-13)then goto 6666 else himemmin:=x;end;
begin undumpint(x);
if(x<-1073741823)or(x>memtop)then goto 6666 else avail:=x;end;
memend:=memtop;undumpthings(mem[himemmin],memend+1-himemmin);
undumpint(varused);undumpint(dynused){:1325};{1327:}{1330:}k:=1;
repeat undumpint(x);if(x<1)or(k+x>29573)then goto 6666;
undumpthings(eqtb[k],x);k:=k+x;undumpint(x);
if(x<0)or(k+x>29573)then goto 6666;
for j:=k to k+x-1 do eqtb[j]:=eqtb[k-1];k:=k+x;until k>29572;
if hashhigh>0 then undumpthings(eqtb[29573],hashhigh);{:1330};
begin undumpint(x);if(x<514)or(x>hashtop)then goto 6666 else parloc:=x;
end;partoken:=536870911+parloc;begin undumpint(x);
if(x<514)or(x>hashtop)then goto 6666 else writeloc:=x;end;
{1332:}begin undumpint(x);
if(x<514)or(x>15514)then goto 6666 else hashused:=x;end;p:=513;
repeat begin undumpint(x);
if(x<p+1)or(x>hashused)then goto 6666 else p:=x;end;undumphh(hash[p]);
until p=hashused;undumpthings(hash[hashused+1],24525-hashused);
if debugformatfile then begin printcsnames(514,24525);end;
if hashhigh>0 then begin undumpthings(hash[29573],hashhigh);
if debugformatfile then begin printcsnames(29573,hashhigh-(29573));end;
end;undumpint(cscount){:1332}{:1327};{1334:}begin undumpint(x);
if x<7 then goto 6666;if x>supfontmemsize then begin;
writeln(stdout,'---! Must increase the ','font mem size');goto 6666;
end else if debugformatfile then begin write(stderr,'fmtdebug:',
'font mem size');writeln(stderr,' = ',x);end;;fmemptr:=x;end;
if fmemptr>fontmemsize then fontmemsize:=fmemptr;
fontinfo:=xmallocarray(memoryword,fontmemsize);
undumpthings(fontinfo[0],fmemptr);begin undumpint(x);
if x<0 then goto 6666;if x>9000 then begin;
writeln(stdout,'---! Must increase the ','font max');goto 6666;
end else if debugformatfile then begin write(stderr,'fmtdebug:',
'font max');writeln(stderr,' = ',x);end;;fontptr:=x;end;
{1336:}begin fontdir:=xmallocarray(eightbits,fontmax);
fontnumext:=xmallocarray(integer,fontmax);
fontcheck:=xmallocarray(fourquarters,fontmax);
fontsize:=xmallocarray(scaled,fontmax);
fontdsize:=xmallocarray(scaled,fontmax);
fontparams:=xmallocarray(fontindex,fontmax);
fontname:=xmallocarray(strnumber,fontmax);
fontarea:=xmallocarray(strnumber,fontmax);
fontbc:=xmallocarray(eightbits,fontmax);
fontec:=xmallocarray(eightbits,fontmax);
fontglue:=xmallocarray(halfword,fontmax);
hyphenchar:=xmallocarray(integer,fontmax);
skewchar:=xmallocarray(integer,fontmax);
bcharlabel:=xmallocarray(fontindex,fontmax);
fontbchar:=xmallocarray(ninebits,fontmax);
fontfalsebchar:=xmallocarray(ninebits,fontmax);
ctypebase:=xmallocarray(integer,fontmax);
charbase:=xmallocarray(integer,fontmax);
widthbase:=xmallocarray(integer,fontmax);
heightbase:=xmallocarray(integer,fontmax);
depthbase:=xmallocarray(integer,fontmax);
italicbase:=xmallocarray(integer,fontmax);
ligkernbase:=xmallocarray(integer,fontmax);
kernbase:=xmallocarray(integer,fontmax);
extenbase:=xmallocarray(integer,fontmax);
parambase:=xmallocarray(integer,fontmax);
undumpthings(fontdir[0],fontptr+1);
undumpthings(fontnumext[0],fontptr+1);
undumpthings(fontcheck[0],fontptr+1);
undumpthings(fontsize[0],fontptr+1);
undumpthings(fontdsize[0],fontptr+1);
undumpcheckedthings(-1073741823,1073741823,fontparams[0],fontptr+1);
undumpthings(hyphenchar[0],fontptr+1);
undumpthings(skewchar[0],fontptr+1);
undumpuppercheckthings(strptr,fontname[0],fontptr+1);
undumpuppercheckthings(strptr,fontarea[0],fontptr+1);
undumpthings(fontbc[0],fontptr+1);undumpthings(fontec[0],fontptr+1);
undumpthings(ctypebase[0],fontptr+1);
undumpthings(charbase[0],fontptr+1);
undumpthings(widthbase[0],fontptr+1);
undumpthings(heightbase[0],fontptr+1);
undumpthings(depthbase[0],fontptr+1);
undumpthings(italicbase[0],fontptr+1);
undumpthings(ligkernbase[0],fontptr+1);
undumpthings(kernbase[0],fontptr+1);
undumpthings(extenbase[0],fontptr+1);
undumpthings(parambase[0],fontptr+1);
undumpcheckedthings(-1073741823,lomemmax,fontglue[0],fontptr+1);
undumpcheckedthings(0,fmemptr-1,bcharlabel[0],fontptr+1);
undumpcheckedthings(0,256,fontbchar[0],fontptr+1);
undumpcheckedthings(0,256,fontfalsebchar[0],fontptr+1);end{:1336};
{:1334};{1338:}begin undumpint(x);if x<0 then goto 6666;
if x>hyphsize then begin;
writeln(stdout,'---! Must increase the ','hyph_size');goto 6666;
end else if debugformatfile then begin write(stderr,'fmtdebug:',
'hyph_size');writeln(stderr,' = ',x);end;;hyphcount:=x;end;
begin undumpint(x);if x<607 then goto 6666;if x>hyphsize then begin;
writeln(stdout,'---! Must increase the ','hyph_size');goto 6666;
end else if debugformatfile then begin write(stderr,'fmtdebug:',
'hyph_size');writeln(stderr,' = ',x);end;;hyphnext:=x;end;j:=0;
for k:=1 to hyphcount do begin undumpint(j);if j<0 then goto 6666;
if j>65535 then begin hyphnext:=j div 65536;j:=j-hyphnext*65536;
end else hyphnext:=0;if(j>=hyphsize)or(hyphnext>hyphsize)then goto 6666;
hyphlink[j]:=hyphnext;begin undumpint(x);
if(x<0)or(x>strptr)then goto 6666 else hyphword[j]:=x;end;
begin undumpint(x);
if(x<-1073741823)or(x>1073741823)then goto 6666 else hyphlist[j]:=x;end;
end;incr(j);if j<607 then j:=607;hyphnext:=j;
if hyphnext>=hyphsize then hyphnext:=607 else if hyphnext>=607 then incr
(hyphnext);begin undumpint(x);if x<0 then goto 6666;
if x>triesize then begin;
writeln(stdout,'---! Must increase the ','trie size');goto 6666;
end else if debugformatfile then begin write(stderr,'fmtdebug:',
'trie size');writeln(stderr,' = ',x);end;;j:=x;end;
ifdef('INITEX')triemax:=j;
endif('INITEX')if not trietrl then trietrl:=xmallocarray(triepointer,j+1
);undumpthings(trietrl[0],j+1);
if not trietro then trietro:=xmallocarray(triepointer,j+1);
undumpthings(trietro[0],j+1);
if not trietrc then trietrc:=xmallocarray(quarterword,j+1);
undumpthings(trietrc[0],j+1);begin undumpint(x);if x<0 then goto 6666;
if x>trieopsize then begin;
writeln(stdout,'---! Must increase the ','trie op size');goto 6666;
end else if debugformatfile then begin write(stderr,'fmtdebug:',
'trie op size');writeln(stderr,' = ',x);end;;j:=x;end;
ifdef('INITEX')trieopptr:=j;
endif('INITEX')undumpthings(hyfdistance[1],j);undumpthings(hyfnum[1],j);
undumpuppercheckthings(maxtrieop,hyfnext[1],j);
ifdef('INITEX')for k:=0 to 255 do trieused[k]:=0;endif('INITEX')k:=256;
while j>0 do begin begin undumpint(x);
if(x<0)or(x>k-1)then goto 6666 else k:=x;end;begin undumpint(x);
if(x<1)or(x>j)then goto 6666 else x:=x;end;
ifdef('INITEX')trieused[k]:=x;endif('INITEX')j:=j-x;opstart[k]:=j;end;
ifdef('INITEX')trienotready:=false endif('INITEX'){:1338};
{1340:}begin undumpint(x);
if(x<0)or(x>3)then goto 6666 else interaction:=x;end;
if interactionoption<>4 then interaction:=interactionoption;
begin undumpint(x);
if(x<0)or(x>strptr)then goto 6666 else formatident:=x;end;undumpint(x);
if x<>69069 then goto 6666{:1340};loadfmtfile:=true;goto 10;6666:;
writeln(stdout,'(Fatal format file error; I''m stymied)');
loadfmtfile:=false;10:end;
{:1316}{1343:}{1346:}procedure closefilesandterminate;var k:integer;
begin{1391:}for k:=0 to 15 do if writeopen[k]then aclose(writefile[k])
{:1391};
ifdef('STAT')if eqtb[28493].int>0 then{1347:}if logopened then begin
writeln(logfile,' ');
writeln(logfile,'Here is how much of TeX''s memory',' you used:');
write(logfile,' ',strptr-initstrptr:1,' string');
if strptr<>initstrptr+1 then write(logfile,'s');
writeln(logfile,' out of ',maxstrings-initstrptr:1);
writeln(logfile,' ',poolptr-initpoolptr:1,' string characters out of ',
poolsize-initpoolptr:1);
writeln(logfile,' ',lomemmax-memmin+memend-himemmin+2:1,
' words of memory out of ',memend+1-memmin:1);
writeln(logfile,' ',cscount:1,' multiletter control sequences out of ',
15000:1,'+',hashextra:1);
write(logfile,' ',fmemptr:1,' words of font info for ',fontptr-0:1,
' font');if fontptr<>1 then write(logfile,'s');
writeln(logfile,', out of ',fontmemsize:1,' for ',fontmax-0:1);
write(logfile,' ',hyphcount:1,' hyphenation exception');
if hyphcount<>1 then write(logfile,'s');
writeln(logfile,' out of ',hyphsize:1);
writeln(logfile,' ',maxinstack:1,'i,',maxneststack:1,'n,',maxparamstack:
1,'p,',maxbufstack+1:1,'b,',maxsavestack+6:1,'s stack positions out of '
,stacksize:1,'i,',nestsize:1,'n,',paramsize:1,'p,',bufsize:1,'b,',
savesize:1,'s');end{:1347};endif('STAT');
{653:}while curs>-1 do begin if curs>0 then begin dvibuf[dviptr]:=142;
incr(dviptr);if dviptr=dvilimit then dviswap;
end else begin begin dvibuf[dviptr]:=140;incr(dviptr);
if dviptr=dvilimit then dviswap;end;incr(totalpages);end;decr(curs);end;
if totalpages=0 then printnl(893)else if curs<>-2 then begin begin
dvibuf[dviptr]:=248;incr(dviptr);if dviptr=dvilimit then dviswap;end;
dvifour(lastbop);lastbop:=dvioffset+dviptr-5;dvifour(25400000);
dvifour(473628672);preparemag;dvifour(eqtb[28479].int);dvifour(maxv);
dvifour(maxh);begin dvibuf[dviptr]:=maxpush div 256;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=maxpush mod 256;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=(totalpages div 256)mod 256;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
begin dvibuf[dviptr]:=totalpages mod 256;incr(dviptr);
if dviptr=dvilimit then dviswap;end;
{654:}while fontptr>0 do begin if fontused[fontptr]then dvifontdef(
fontptr);decr(fontptr);end{:654};begin dvibuf[dviptr]:=249;incr(dviptr);
if dviptr=dvilimit then dviswap;end;dvifour(lastbop);
if dirused then begin dvibuf[dviptr]:=3;incr(dviptr);
if dviptr=dvilimit then dviswap;end else begin dvibuf[dviptr]:=2;
incr(dviptr);if dviptr=dvilimit then dviswap;end;
ifdef('IPC')k:=7-((3+dvioffset+dviptr)mod 4);
endif('IPC')ifndef('IPC')k:=4+((dvibufsize-dviptr)mod 4);
endifn('IPC')while k>0 do begin begin dvibuf[dviptr]:=223;incr(dviptr);
if dviptr=dvilimit then dviswap;end;decr(k);end;
{610:}if dvilimit=halfbuf then writedvi(halfbuf,dvibufsize-1);
if dviptr>(2147483647-dvioffset)then begin curs:=-2;fatalerror(882);end;
if dviptr>0 then writedvi(0,dviptr-1){:610};printnl(894);
printfilename(0,outputfilename,0);print(285);printint(totalpages);
if totalpages<>1 then print(895)else print(896);print(328);
printint(dvioffset+dviptr);print(897);bclose(dvifile);end{:653};
{1431:}synctexterminate(logopened);{:1431};
if logopened then begin writeln(logfile);aclose(logfile);
selector:=selector-2;if selector=17 then begin printnl(1360);
printfilename(0,texmflogname,0);printchar(46);end;end;println;
if(editnamestart<>0)and(interaction>0)then calledit(strpool,
editnamestart,editnamelength,editline);end;
{:1346}{1348:}procedure finalcleanup;label 10;var c:smallnumber;
begin c:=curchr;if jobname=0 then openlogfile;
while inputptr>0 do if curinput.statefield=0 then endtokenlist else
endfilereading;while openparens>0 do begin print(1361);decr(openparens);
end;if curlevel>1 then begin printnl(40);printesc(1362);print(1363);
printint(curlevel-1);printchar(41);end;
while condptr<>-1073741823 do begin printnl(40);printesc(1362);
print(1364);printcmdchr(120,curif);if ifline<>0 then begin print(1365);
printint(ifline);end;print(1366);ifline:=mem[condptr+1].int;
curif:=mem[condptr].hh.b1;tempptr:=condptr;condptr:=mem[condptr].hh.rh;
freenode(tempptr,2);end;
if history<>0 then if((history=1)or(interaction<3))then if selector=19
then begin selector:=17;printnl(1367);selector:=19;end;
if c=1 then begin ifdef('INITEX')if iniversion then begin for c:=0 to 4
do if curmark[c]<>-1073741823 then deletetokenref(curmark[c]);
if lastglue<>1073741823 then deleteglueref(lastglue);storefmtfile;
goto 10;end;endif('INITEX')printnl(1368);goto 10;end;10:end;
{:1348}{1349:}ifdef('INITEX')procedure initprim;
begin nonewcontrolsequence:=false;{232:}primitive(392,83,24527);
primitive(393,83,24528);primitive(394,83,24529);primitive(395,83,24530);
primitive(396,83,24531);primitive(397,83,24532);primitive(398,83,24533);
primitive(399,83,24534);primitive(400,83,24535);primitive(401,83,24536);
primitive(402,83,24537);primitive(403,83,24538);primitive(404,83,24539);
primitive(405,83,24540);primitive(406,83,24541);primitive(407,84,24544);
primitive(408,84,24545);primitive(409,84,24546);primitive(410,83,24542);
primitive(411,83,24543);{:232}{236:}primitive(417,80,25061);
primitive(418,80,25062);primitive(419,80,25063);primitive(420,80,25064);
primitive(421,80,25065);primitive(422,80,25066);primitive(423,80,25067);
primitive(424,80,25068);primitive(425,80,25069);
{:236}{244:}primitive(444,81,28462);primitive(445,81,28463);
primitive(446,81,28464);primitive(447,81,28465);primitive(448,81,28466);
primitive(449,81,28467);primitive(450,81,28468);primitive(451,81,28469);
primitive(452,81,28470);primitive(453,81,28471);primitive(454,81,28472);
primitive(455,81,28473);primitive(456,81,28474);primitive(457,81,28475);
primitive(458,81,28476);primitive(459,81,28477);primitive(460,81,28478);
primitive(461,81,28479);primitive(462,81,28480);primitive(463,81,28481);
primitive(464,81,28482);primitive(465,81,28483);primitive(466,81,28484);
primitive(467,81,28485);primitive(468,81,28486);primitive(469,81,28487);
primitive(470,81,28488);primitive(471,81,28489);primitive(472,81,28490);
primitive(473,81,28491);primitive(474,81,28492);primitive(475,81,28493);
primitive(476,81,28494);primitive(477,81,28495);primitive(478,81,28496);
primitive(479,81,28497);primitive(480,81,28498);primitive(481,81,28499);
primitive(482,81,28500);primitive(483,81,28501);primitive(484,81,28502);
primitive(485,81,28503);primitive(486,81,28504);primitive(487,81,28505);
primitive(488,81,28506);primitive(489,81,28508);primitive(490,81,28509);
primitive(491,81,28510);primitive(492,81,28511);primitive(493,81,28512);
primitive(494,81,28507);primitive(495,81,28518);primitive(496,81,28519);
primitive(497,81,28520);primitive(498,81,28521);primitive(499,81,28513);
primitive(500,81,28514);primitive(501,81,28515);primitive(502,81,28516);
primitive(503,81,28517);if mltexp then begin mltexenabledp:=true;
if false then primitive(504,81,28522);primitive(505,81,28523);
primitive(506,81,28524);end;{:244}{254:}primitive(510,82,29038);
primitive(511,82,29039);primitive(512,82,29040);primitive(513,82,29041);
primitive(514,82,29042);primitive(515,82,29043);primitive(516,82,29044);
primitive(517,82,29045);primitive(518,82,29046);primitive(519,82,29047);
primitive(520,82,29048);primitive(521,82,29049);primitive(522,82,29050);
primitive(523,82,29051);primitive(524,82,29052);primitive(525,82,29053);
primitive(526,82,29054);primitive(527,82,29055);primitive(528,82,29056);
primitive(529,82,29057);primitive(530,82,29059);primitive(531,82,29060);
primitive(532,82,29058);{:254}{271:}primitive(32,69,0);
primitive(47,48,0);primitive(543,49,0);primitive(544,103,0);
primitive(545,44,0);primitive(546,45,0);primitive(547,66,0);
primitive(548,20,0);primitive(549,54,0);primitive(539,122,0);
primitive(550,15,0);primitive(551,105,0);primitive(540,72,0);
primitive(552,67,0);hash[15516].rh:=552;eqtb[15516]:=eqtb[curval];
primitive(553,117,0);primitive(554,99,0);primitive(555,100,0);
primitive(556,101,0);primitive(557,85,0);primitive(558,36,0);
primitive(559,40,0);primitive(560,43,0);primitive(336,41,0);
primitive(359,22,0);primitive(561,50,0);primitive(562,21,0);
primitive(563,59,0);primitive(564,104,0);primitive(565,38,0);
primitive(566,70,0);primitive(567,118,0);primitive(341,60,0);
primitive(568,68,0);primitive(427,95,0);primitive(569,46,0);
primitive(570,91,0);primitive(571,71,0);primitive(572,109,0);
primitive(573,0,256);hash[15521].rh:=573;eqtb[15521]:=eqtb[curval];
primitive(574,111,0);primitive(575,124,0);primitive(426,79,0);
primitive(360,42,0);primitive(576,37,0);primitive(577,61,0);
primitive(578,39,0);{:271}{340:}primitive(635,13,256);parloc:=curval;
partoken:=536870911+parloc;{:340}{387:}primitive(670,119,0);
primitive(671,119,1);{:387}{395:}primitive(672,125,0);
primitive(673,125,1);primitive(674,125,2);primitive(675,125,3);
primitive(676,125,4);{:395}{422:}primitive(508,102,0);
primitive(534,102,1);primitive(414,102,2);primitive(415,102,3);
{:422}{427:}primitive(709,90,117);primitive(710,90,1);
primitive(711,93,0);primitive(712,93,1);primitive(713,94,1);
primitive(714,94,3);primitive(715,94,2);primitive(716,76,0);
primitive(717,76,1);primitive(718,76,2);primitive(719,76,3);
primitive(720,76,4);{:427}{479:}primitive(778,123,0);
primitive(779,123,1);primitive(780,123,3);primitive(781,123,4);
primitive(782,123,5);primitive(783,123,2);primitive(784,123,6);
primitive(785,123,7);primitive(786,123,8);primitive(787,123,9);
primitive(788,123,10);primitive(789,123,11);
{:479}{498:}primitive(805,120,0);primitive(806,120,1);
primitive(807,120,2);primitive(808,120,3);primitive(809,120,4);
primitive(810,120,5);primitive(811,120,6);primitive(812,120,7);
primitive(813,120,8);primitive(814,120,9);primitive(815,120,10);
primitive(816,120,11);primitive(817,120,12);primitive(818,120,13);
primitive(819,120,14);primitive(820,120,15);primitive(821,120,16);
primitive(822,120,17);primitive(823,120,18);primitive(824,120,19);
primitive(825,120,20);primitive(826,120,21);primitive(827,120,22);
primitive(828,120,23);{:498}{502:}primitive(829,121,2);
hash[15518].rh:=829;eqtb[15518]:=eqtb[curval];primitive(830,121,4);
primitive(831,121,3);{:502}{564:}primitive(856,98,0);
hash[15525].rh:=856;eqtb[15525]:=eqtb[curval];
{:564}{791:}primitive(955,4,256);primitive(956,5,257);
hash[15515].rh:=956;eqtb[15515]:=eqtb[curval];primitive(957,5,258);
hash[15519].rh:=958;hash[15520].rh:=958;eqtb[15520].hh.b0:=9;
eqtb[15520].hh.rh:=memtop-11;eqtb[15520].hh.b1:=1;
eqtb[15519]:=eqtb[15520];eqtb[15519].hh.b0:=130;
{:791}{994:}primitive(1027,92,0);primitive(1028,92,1);
primitive(1029,92,2);primitive(1030,92,3);primitive(1031,92,4);
primitive(1032,92,5);primitive(1033,92,6);primitive(1034,92,7);
{:994}{1064:}primitive(1083,14,0);primitive(1084,14,1);
{:1064}{1070:}primitive(1085,30,4);primitive(1086,30,0);
primitive(1087,30,1);primitive(1088,30,2);primitive(1089,30,3);
primitive(1090,31,4);primitive(1091,31,0);primitive(1092,31,1);
primitive(1093,31,2);primitive(1094,31,3);primitive(342,32,5);
primitive(346,33,1);primitive(348,34,99);
{:1070}{1083:}primitive(1112,25,1);primitive(1113,25,0);
primitive(1114,26,1);primitive(1115,26,0);primitive(428,24,0);
primitive(1116,24,1);primitive(1117,24,2);primitive(1022,24,3);
primitive(1118,24,4);primitive(1024,24,5);primitive(1119,24,121);
primitive(1120,78,3);primitive(1121,78,4);primitive(1122,78,1);
primitive(1123,35,99);primitive(1124,35,100);primitive(1125,35,101);
primitive(1126,35,102);{:1083}{1100:}primitive(1148,47,1);
primitive(1149,47,0);{:1100}{1119:}primitive(1160,29,14);
primitive(1161,29,13);primitive(1162,29,12);primitive(1163,27,0);
primitive(1164,27,1);primitive(1165,28,0);primitive(1166,28,1);
{:1119}{1126:}primitive(45,51,1);primitive(357,51,0);
{:1126}{1153:}primitive(1199,52,0);primitive(1200,52,1);
{:1153}{1168:}primitive(922,55,18);primitive(923,55,19);
primitive(924,55,20);primitive(925,55,21);primitive(926,55,22);
primitive(927,55,23);primitive(928,55,24);primitive(929,55,25);
primitive(931,55,28);primitive(930,55,29);primitive(1204,56,0);
primitive(934,56,1);primitive(935,56,2);
{:1168}{1181:}primitive(917,58,0);primitive(918,58,2);
primitive(919,58,4);primitive(920,58,6);
{:1181}{1190:}primitive(1222,57,0);primitive(1223,57,1);
primitive(1224,57,2);primitive(1225,57,3);primitive(1226,57,4);
primitive(1227,57,5);{:1190}{1200:}primitive(932,53,32);
primitive(933,53,33);hash[15517].rh:=933;eqtb[15517]:=eqtb[curval];
{:1200}{1220:}primitive(1246,106,1);primitive(1247,106,2);
primitive(1248,106,4);primitive(1249,110,0);primitive(1250,110,1);
primitive(1251,110,2);primitive(1252,110,3);
{:1220}{1231:}primitive(1266,107,0);primitive(1267,107,1);
{:1231}{1234:}primitive(1268,108,0);primitive(1269,108,8);
primitive(1270,108,1);primitive(1271,108,2);primitive(1272,108,3);
primitive(1273,108,4);primitive(1274,108,5);primitive(1275,108,6);
if mltexp then begin primitive(1276,108,7);end;
{:1234}{1242:}primitive(434,96,25636);primitive(435,96,25892);
primitive(436,96,26404);primitive(443,96,27950);primitive(440,96,27182);
primitive(441,96,27438);primitive(442,96,27694);primitive(509,96,28782);
primitive(431,97,25583);primitive(432,97,25599);primitive(433,97,25615);
{:1242}{1263:}primitive(998,112,0);primitive(1010,112,1);
{:1263}{1267:}primitive(1298,86,0);primitive(1299,86,1);
{:1267}{1275:}primitive(273,113,0);primitive(274,113,1);
primitive(275,113,2);primitive(1308,113,3);
{:1275}{1285:}primitive(1309,65,1);primitive(1310,65,0);
{:1285}{1290:}primitive(1311,63,0);primitive(1312,63,1);
{:1290}{1299:}primitive(1318,62,27182);primitive(1319,62,27438);
{:1299}{1304:}primitive(1320,23,0);primitive(1321,23,1);
primitive(1322,23,2);primitive(1323,23,3);primitive(1324,23,4);
{:1304}{1357:}primitive(1370,64,0);primitive(632,64,1);writeloc:=curval;
primitive(1371,64,2);primitive(1372,64,3);hash[15524].rh:=1372;
eqtb[15524]:=eqtb[curval];primitive(1373,64,4);primitive(1374,64,5);
{:1357}{1420:}primitive(1399,81,28525);
{:1420}{1454:}primitive(439,89,0);{:1454}{1459:}primitive(1403,114,1);
primitive(1404,114,0);primitive(1405,114,3);primitive(1406,114,2);
primitive(1407,115,0);primitive(1408,115,1);primitive(1409,115,2);
{:1459}{1466:}primitive(1422,77,0);primitive(1423,88,26660);
{:1466}{1471:}primitive(1426,87,1);primitive(1427,87,2);{:1471};
nonewcontrolsequence:=true;end;
endif('INITEX'){:1349}{1351:}ifdef('TEXMF_DEBUG')procedure debughelp;
label 888,10;var k,l,m,n:integer;begin while true do begin;
printnl(1369);fflush(stdout);read(stdin,m);
if m<0 then goto 10 else if m=0 then dumpcore else begin read(stdin,n);
case m of{1352:}1:printword(mem[n]);2:printint(mem[n].hh.lh);
3:printint(mem[n].hh.rh);4:printword(eqtb[n]);
5:begin printscaled(fontinfo[n].int);printchar(32);
printint(fontinfo[n].qqqq.b0);printchar(58);
printint(fontinfo[n].qqqq.b1);printchar(58);
printint(fontinfo[n].qqqq.b2);printchar(58);
printint(fontinfo[n].qqqq.b3);end;6:printword(savestack[n]);
7:showbox(n);8:begin breadthmax:=10000;
depththreshold:=poolsize-poolptr-10;shownodelist(n);end;
9:showtokenlist(n,-1073741823,1000);10:slowprint(n);11:checkmem(n>0);
12:searchmem(n);13:begin read(stdin,l);printcmdchr(n,l);end;
14:for k:=0 to n do print(buffer[k]);15:begin fontinshortdisplay:=0;
shortdisplay(n);end;16:panicking:=not panicking;
{:1352}others:print(63)end;end;end;10:end;
endif('TEXMF_DEBUG'){:1351}{:1343}{1345:}procedure mainbody;
begin bounddefault:=0;boundname:='mem_bot';
setupboundvariable(addressof(membot),boundname,bounddefault);
bounddefault:=250000;boundname:='main_memory';
setupboundvariable(addressof(mainmemory),boundname,bounddefault);
bounddefault:=0;boundname:='extra_mem_top';
setupboundvariable(addressof(extramemtop),boundname,bounddefault);
bounddefault:=0;boundname:='extra_mem_bot';
setupboundvariable(addressof(extramembot),boundname,bounddefault);
bounddefault:=200000;boundname:='pool_size';
setupboundvariable(addressof(poolsize),boundname,bounddefault);
bounddefault:=75000;boundname:='string_vacancies';
setupboundvariable(addressof(stringvacancies),boundname,bounddefault);
bounddefault:=5000;boundname:='pool_free';
setupboundvariable(addressof(poolfree),boundname,bounddefault);
bounddefault:=15000;boundname:='max_strings';
setupboundvariable(addressof(maxstrings),boundname,bounddefault);
bounddefault:=100;boundname:='strings_free';
setupboundvariable(addressof(stringsfree),boundname,bounddefault);
bounddefault:=100000;boundname:='font_mem_size';
setupboundvariable(addressof(fontmemsize),boundname,bounddefault);
bounddefault:=500;boundname:='font_max';
setupboundvariable(addressof(fontmax),boundname,bounddefault);
bounddefault:=20000;boundname:='trie_size';
setupboundvariable(addressof(triesize),boundname,bounddefault);
bounddefault:=659;boundname:='hyph_size';
setupboundvariable(addressof(hyphsize),boundname,bounddefault);
bounddefault:=3000;boundname:='buf_size';
setupboundvariable(addressof(bufsize),boundname,bounddefault);
bounddefault:=50;boundname:='nest_size';
setupboundvariable(addressof(nestsize),boundname,bounddefault);
bounddefault:=15;boundname:='max_in_open';
setupboundvariable(addressof(maxinopen),boundname,bounddefault);
bounddefault:=60;boundname:='param_size';
setupboundvariable(addressof(paramsize),boundname,bounddefault);
bounddefault:=4000;boundname:='save_size';
setupboundvariable(addressof(savesize),boundname,bounddefault);
bounddefault:=300;boundname:='stack_size';
setupboundvariable(addressof(stacksize),boundname,bounddefault);
bounddefault:=16384;boundname:='dvi_buf_size';
setupboundvariable(addressof(dvibufsize),boundname,bounddefault);
bounddefault:=79;boundname:='error_line';
setupboundvariable(addressof(errorline),boundname,bounddefault);
bounddefault:=50;boundname:='half_error_line';
setupboundvariable(addressof(halferrorline),boundname,bounddefault);
bounddefault:=79;boundname:='max_print_line';
setupboundvariable(addressof(maxprintline),boundname,bounddefault);
bounddefault:=0;boundname:='hash_extra';
setupboundvariable(addressof(hashextra),boundname,bounddefault);
bounddefault:=10000;boundname:='expand_depth';
setupboundvariable(addressof(expanddepth),boundname,bounddefault);
begin if membot<infmembot then membot:=infmembot else if membot>
supmembot then membot:=supmembot end;
begin if mainmemory<infmainmemory then mainmemory:=infmainmemory else if
mainmemory>supmainmemory then mainmemory:=supmainmemory end;
ifdef('INITEX')if iniversion then begin extramemtop:=0;extramembot:=0;
end;endif('INITEX')if extramembot>supmainmemory then extramembot:=
supmainmemory;
if extramemtop>supmainmemory then extramemtop:=supmainmemory;
memtop:=membot+mainmemory-1;memmin:=membot;memmax:=memtop;
begin if triesize<inftriesize then triesize:=inftriesize else if
triesize>suptriesize then triesize:=suptriesize end;
begin if hyphsize<infhyphsize then hyphsize:=infhyphsize else if
hyphsize>suphyphsize then hyphsize:=suphyphsize end;
begin if bufsize<infbufsize then bufsize:=infbufsize else if bufsize>
supbufsize then bufsize:=supbufsize end;
begin if nestsize<infnestsize then nestsize:=infnestsize else if
nestsize>supnestsize then nestsize:=supnestsize end;
begin if maxinopen<infmaxinopen then maxinopen:=infmaxinopen else if
maxinopen>supmaxinopen then maxinopen:=supmaxinopen end;
begin if paramsize<infparamsize then paramsize:=infparamsize else if
paramsize>supparamsize then paramsize:=supparamsize end;
begin if savesize<infsavesize then savesize:=infsavesize else if
savesize>supsavesize then savesize:=supsavesize end;
begin if stacksize<infstacksize then stacksize:=infstacksize else if
stacksize>supstacksize then stacksize:=supstacksize end;
begin if dvibufsize<infdvibufsize then dvibufsize:=infdvibufsize else if
dvibufsize>supdvibufsize then dvibufsize:=supdvibufsize end;
begin if poolsize<infpoolsize then poolsize:=infpoolsize else if
poolsize>suppoolsize then poolsize:=suppoolsize end;
begin if stringvacancies<infstringvacancies then stringvacancies:=
infstringvacancies else if stringvacancies>supstringvacancies then
stringvacancies:=supstringvacancies end;
begin if poolfree<infpoolfree then poolfree:=infpoolfree else if
poolfree>suppoolfree then poolfree:=suppoolfree end;
begin if maxstrings<infmaxstrings then maxstrings:=infmaxstrings else if
maxstrings>supmaxstrings then maxstrings:=supmaxstrings end;
begin if stringsfree<infstringsfree then stringsfree:=infstringsfree
else if stringsfree>supstringsfree then stringsfree:=supstringsfree end;
begin if fontmemsize<inffontmemsize then fontmemsize:=inffontmemsize
else if fontmemsize>supfontmemsize then fontmemsize:=supfontmemsize end;
begin if fontmax<inffontmax then fontmax:=inffontmax else if fontmax>
supfontmax then fontmax:=supfontmax end;
begin if hashextra<infhashextra then hashextra:=infhashextra else if
hashextra>suphashextra then hashextra:=suphashextra end;
if errorline>255 then errorline:=255;
buffer:=xmallocarray(ASCIIcode,bufsize);
nest:=xmallocarray(liststaterecord,nestsize);
savestack:=xmallocarray(memoryword,savesize);
inputstack:=xmallocarray(instaterecord,stacksize);
inputfile:=xmallocarray(alphafile,maxinopen);
linestack:=xmallocarray(integer,maxinopen);
sourcefilenamestack:=xmallocarray(strnumber,maxinopen);
fullsourcefilenamestack:=xmallocarray(strnumber,maxinopen);
paramstack:=xmallocarray(halfword,paramsize);
dvibuf:=xmallocarray(eightbits,dvibufsize);
hyphword:=xmallocarray(strnumber,hyphsize);
hyphlist:=xmallocarray(halfword,hyphsize);
hyphlink:=xmallocarray(hyphpointer,hyphsize);
ifdef('INITEX')if iniversion then begin yzmem:=xmallocarray(memoryword,
memtop-membot+1);zmem:=yzmem-membot;eqtbtop:=29572+hashextra;
if hashextra=0 then hashtop:=24526 else hashtop:=eqtbtop;
yhash:=xmallocarray(twohalves,1+hashtop-hashoffset);
hash:=yhash-hashoffset;hash[514].lh:=0;hash[514].rh:=0;
for hashused:=515 to hashtop do hash[hashused]:=hash[514];
zeqtb:=xmallocarray(memoryword,eqtbtop);eqtb:=zeqtb;
strstart:=xmallocarray(poolpointer,maxstrings);
strpool:=xmallocarray(packedASCIIcode,poolsize);
fontinfo:=xmallocarray(memoryword,fontmemsize);end;
endif('INITEX')history:=3;;if readyalready=314159 then goto 1;
{14:}bad:=0;
if(halferrorline<30)or(halferrorline>errorline-15)then bad:=1;
if maxprintline<60 then bad:=2;if dvibufsize mod 8<>0 then bad:=3;
if membot+1100>memtop then bad:=4;if 8501>15000 then bad:=5;
if maxinopen>=128 then bad:=6;if memtop<267 then bad:=7;
{:14}{112:}ifdef('INITEX')if(memmin<>membot)or(memmax<>memtop)then bad:=
10;endif('INITEX')if(memmin>membot)or(memmax<memtop)then bad:=10;
if(0>0)or(65535<127)then bad:=11;
if(-1073741823>0)or(1073741823<32767)then bad:=12;
if(0<-1073741823)or(65535>1073741823)then bad:=13;
if(membot-supmainmemory<-1073741823)or(memtop+supmainmemory>=1073741823)
or(0<>0)then bad:=14;
if(9000<-1073741823)or(9000>1073741823)then bad:=15;
if fontmax>9000 then bad:=16;
if(savesize>1073741823)or(maxstrings>1073741823)then bad:=17;
if bufsize>1073741823 then bad:=18;if 65535<255 then bad:=19;
{:112}{296:}if 536900483+hashextra>1073741823 then bad:=21;
if(hashoffset<0)or(hashoffset>514)then bad:=42;
{:296}{533:}if formatdefaultlength>maxint then bad:=31;
{:533}{1262:}if 2*1073741823<memtop-memmin then bad:=41;
{:1262}if bad>0 then begin writeln(stdout,
'Ouch---my internal constants have been clobbered!','---case ',bad:1);
goto 9999;end;initialize;
ifdef('INITEX')if iniversion then begin if not getstringsstarted then
goto 9999;initprim;initstrptr:=strptr;initpoolptr:=poolptr;
dateandtime(eqtb[28482].int,eqtb[28483].int,eqtb[28484].int,eqtb[28485].
int);end;endif('INITEX')readyalready:=314159;1:{56:}selector:=17;
tally:=0;termoffset:=0;fileoffset:=0;kcodepos:=0;
{:56}{62:}if srcspecialsp or filelineerrorstylep or parsefirstlinep then
write(stdout,'This is upTeX, Version 3.14159265','-p3.7.1','-u1.21')else
write(stdout,'This is upTeX, Version 3.14159265','-p3.7.1','-u1.21');
write(stdout,' (');write(stdout,conststringcast(getencstring));
write(stdout,')');write(stdout,versionstring);
if formatident=0 then writeln(stdout,' (preloaded format=',dumpname,')')
else begin slowprint(formatident);println;end;
if shellenabledp then begin write(stdout,' ');
if restrictedshell then begin write(stdout,'restricted ');end;
writeln(stdout,'\write18 enabled.');end;
if srcspecialsp then begin writeln(stdout,' Source specials enabled.')
end;if translatefilename then begin write(stdout,' (');
fputs(translatefilename,stdout);writeln(stdout,')');end;fflush(stdout);
{:62}{539:}jobname:=0;nameinprogress:=false;logopened:=false;
{:539}{544:}outputfilename:=0;{:544};
{1350:}begin{337:}begin inputptr:=0;maxinstack:=0;
sourcefilenamestack[0]:=0;fullsourcefilenamestack[0]:=0;inopen:=0;
openparens:=0;maxbufstack:=0;paramptr:=0;maxparamstack:=0;
first:=bufsize;repeat buffer[first]:=0;decr(first);until first=0;
scannerstatus:=0;warningindex:=-1073741823;first:=1;
curinput.statefield:=61;curinput.startfield:=1;curinput.indexfield:=0;
line:=0;curinput.namefield:=0;forceeof:=false;alignstate:=1000000;
if not initterminal then goto 9999;curinput.limitfield:=last;
first:=last+1;end{:337};
if(formatident=0)or(buffer[curinput.locfield]=38)or dumpline then begin
if formatident<>0 then initialize;if not openfmtfile then goto 9999;
if not loadfmtfile then begin wclose(fmtfile);goto 9999;end;
wclose(fmtfile);eqtb:=zeqtb;
while(curinput.locfield<curinput.limitfield)and(buffer[curinput.locfield
]=32)do incr(curinput.locfield);end;
if(eqtb[28511].int<0)or(eqtb[28511].int>255)then decr(curinput.
limitfield)else buffer[curinput.limitfield]:=eqtb[28511].int;
if mltexenabledp then begin writeln(stdout,'MLTeX v2.2 enabled');end;
dateandtime(eqtb[28482].int,eqtb[28483].int,eqtb[28484].int,eqtb[28485].
int);ifdef('INITEX')if trienotready then begin trietrl:=xmallocarray(
triepointer,triesize);trietro:=xmallocarray(triepointer,triesize);
trietrc:=xmallocarray(quarterword,triesize);
triec:=xmallocarray(packedASCIIcode,triesize);
trieo:=xmallocarray(trieopcode,triesize);
triel:=xmallocarray(triepointer,triesize);
trier:=xmallocarray(triepointer,triesize);
triehash:=xmallocarray(triepointer,triesize);
trietaken:=xmallocarray(boolean,triesize);triel[0]:=0;triec[0]:=0;
trieptr:=0;fontdir:=xmallocarray(eightbits,fontmax);
fontnumext:=xmallocarray(integer,fontmax);
fontcheck:=xmallocarray(fourquarters,fontmax);
fontsize:=xmallocarray(scaled,fontmax);
fontdsize:=xmallocarray(scaled,fontmax);
fontparams:=xmallocarray(fontindex,fontmax);
fontname:=xmallocarray(strnumber,fontmax);
fontarea:=xmallocarray(strnumber,fontmax);
fontbc:=xmallocarray(eightbits,fontmax);
fontec:=xmallocarray(eightbits,fontmax);
fontglue:=xmallocarray(halfword,fontmax);
hyphenchar:=xmallocarray(integer,fontmax);
skewchar:=xmallocarray(integer,fontmax);
bcharlabel:=xmallocarray(fontindex,fontmax);
fontbchar:=xmallocarray(ninebits,fontmax);
fontfalsebchar:=xmallocarray(ninebits,fontmax);
ctypebase:=xmallocarray(integer,fontmax);
charbase:=xmallocarray(integer,fontmax);
widthbase:=xmallocarray(integer,fontmax);
heightbase:=xmallocarray(integer,fontmax);
depthbase:=xmallocarray(integer,fontmax);
italicbase:=xmallocarray(integer,fontmax);
ligkernbase:=xmallocarray(integer,fontmax);
kernbase:=xmallocarray(integer,fontmax);
extenbase:=xmallocarray(integer,fontmax);
parambase:=xmallocarray(integer,fontmax);fontptr:=0;fmemptr:=7;
fontdir[0]:=0;fontnumext[0]:=0;fontname[0]:=856;fontarea[0]:=344;
hyphenchar[0]:=45;skewchar[0]:=-1;bcharlabel[0]:=0;fontbchar[0]:=256;
fontfalsebchar[0]:=256;fontbc[0]:=1;fontec[0]:=0;fontsize[0]:=0;
fontdsize[0]:=0;ctypebase[0]:=0;charbase[0]:=0;widthbase[0]:=0;
heightbase[0]:=0;depthbase[0]:=0;italicbase[0]:=0;ligkernbase[0]:=0;
kernbase[0]:=0;extenbase[0]:=0;fontglue[0]:=-1073741823;
fontparams[0]:=7;parambase[0]:=-1;
for fontk:=0 to 6 do fontinfo[fontk].int:=0;end;
endif('INITEX')fontused:=xmallocarray(boolean,fontmax);
for fontk:=0 to fontmax do fontused[fontk]:=false;
{776:}magicoffset:=strstart[949]-9*18{:776};
{76:}if interaction=0 then selector:=16 else selector:=17{:76};
if(curinput.locfield<curinput.limitfield)and(eqtb[25636+buffer[curinput.
locfield]].hh.rh<>0)then startinput;end{:1350};history:=0;
{1424:}synctexinitcommand;{:1424}maincontrol;finalcleanup;
closefilesandterminate;9999:begin fflush(stdout);readyalready:=0;
if(history<>0)and(history<>1)then uexit(1)else uexit(0);end;end;
{:1345}{1509:}function getnullstr:strnumber;begin getnullstr:=344;end;
{:1509}