/*1:*/
#line 21 "./luatexdir/font/writeenc.w"



#include "ptexlib.h"

/*:1*//*2:*/
#line 27 "./luatexdir/font/writeenc.w"

struct avl_table*fe_tree= NULL;

/*:2*//*3:*/
#line 31 "./luatexdir/font/writeenc.w"

static int comp_fe_entry(const void*pa,const void*pb,void*p)
{
(void)p;
return strcmp(((const fe_entry*)pa)->name,((const fe_entry*)pb)->name);
}

static fe_entry*new_fe_entry(void)
{
fe_entry*fe;
fe= xtalloc(1,fe_entry);
fe->name= NULL;
fe->fe_objnum= 0;
fe->glyph_names= NULL;
fe->tx_tree= NULL;
return fe;
}

static fe_entry*lookup_fe_entry(char*s)
{
fe_entry fe;
assert(s!=NULL);
fe.name= s;
if(fe_tree==NULL){
fe_tree= avl_create(comp_fe_entry,NULL,&avl_xallocator);
assert(fe_tree!=NULL);
}
return(fe_entry*)avl_find(fe_tree,&fe);
}

static void register_fe_entry(fe_entry*fe)
{
void**aa;
if(fe_tree==NULL){
fe_tree= avl_create(comp_fe_entry,NULL,&avl_xallocator);
assert(fe_tree!=NULL);
}
assert(fe!=NULL);
assert(fe->name!=NULL);
assert(lookup_fe_entry(fe->name)==NULL);
aa= avl_probe(fe_tree,fe);
assert(aa!=NULL);
}

fe_entry*get_fe_entry(char*s)
{
fe_entry*fe;
char**gl;
if((fe= lookup_fe_entry(s))==NULL&&(gl= load_enc_file(s))!=NULL){
fe= new_fe_entry();
fe->name= s;
fe->glyph_names= gl;
register_fe_entry(fe);
}
return fe;
}

/*:3*//*4:*/
#line 88 "./luatexdir/font/writeenc.w"

static void write_enc(PDF pdf,char**glyph_names,struct avl_table*tx_tree,
int fe_objnum)
{
int i_old,*p;
struct avl_traverser t;
assert(glyph_names!=NULL);
assert(tx_tree!=NULL);
assert(fe_objnum!=0);
pdf_begin_obj(pdf,fe_objnum,OBJSTM_ALWAYS);
pdf_begin_dict(pdf);
pdf_dict_add_name(pdf,"Type","Encoding");
pdf_add_name(pdf,"Differences");
pdf_begin_array(pdf);
avl_t_init(&t,tx_tree);
for(i_old= -2,p= (int*)avl_t_first(&t,tx_tree);p!=NULL;
p= (int*)avl_t_next(&t)){
if(*p==i_old+1)
pdf_add_name(pdf,glyph_names[*p]);
else{
pdf_add_int(pdf,*p);
pdf_add_name(pdf,glyph_names[*p]);
}
i_old= *p;
}
pdf_end_array(pdf);
pdf_end_dict(pdf);
pdf_end_obj(pdf);
}

static void write_fontencoding(PDF pdf,fe_entry*fe)
{
assert(fe!=NULL);
write_enc(pdf,fe->glyph_names,fe->tx_tree,fe->fe_objnum);
}

void write_fontencodings(PDF pdf)
{
fe_entry*fe;
struct avl_traverser t;
if(fe_tree==NULL)
return;
avl_t_init(&t,fe_tree);
for(fe= (fe_entry*)avl_t_first(&t,fe_tree);fe!=NULL;
fe= (fe_entry*)avl_t_next(&t))
if(fe->fe_objnum!=0)
write_fontencoding(pdf,fe);
}

/*:4*//*5:*/
#line 138 "./luatexdir/font/writeenc.w"


static void destroy_fe_entry(void*pa,void*pb)
{
fe_entry*p;
int i;
(void)pb;
p= (fe_entry*)pa;
xfree(p->name);
if(p->glyph_names!=NULL)
for(i= 0;i<256;i++)
if(p->glyph_names[i]!=notdef)
xfree(p->glyph_names[i]);
xfree(p->glyph_names);
if(p->tx_tree!=NULL)
avl_destroy(p->tx_tree,NULL);
xfree(p);
}

void enc_free(void)
{
if(fe_tree!=NULL)
avl_destroy(fe_tree,destroy_fe_entry);
fe_tree= NULL;
}/*:5*/