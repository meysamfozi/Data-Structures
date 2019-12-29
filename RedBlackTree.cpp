#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <cstring>
using namespace std;

class str
{
public:
    char data;
    str *next;
    str *getname(str *p)
    {
        char u='0';
        p=new str();
        str *q=p;
		cin.ignore();
		while((u=cin.get())!='\n')
		{
		    q->data=u;
			q->next=new str();
			q=q->next;
		}
        return p;
    }
    str *copy(str *q)
    {
        str *k=new str;
        if(q==0) return 0;
        k->data=q->data;
        k->next=copy(q->next);
        return k;
    }
    void printname(str *p)
    {
        str *q=p;
        while(q!=0)
        {
            cout<<q->data;
            q=q->next;
        }
        return;
    }
    int compare(str *p,str *q)
    {
        str *l1=p;
        str *l2=q;
        while((l1!=0)&&(l2!=0))
        {
            if(l1->data>l2->data)
                return 1;
            if(l1->data<l2->data)
                return -1;
            l1=l1->next;
            l2=l2->next;
        }
        if(l1!=0) return 1;
        if(l2!=0) return -1;
        return 0;
    }
};
class name
{
public:
    str *p;
    name *next;
    name *aloc()
    {
        name *k=new name;
        k->next=0;
        return k;
    }
    void printname(name *q)
    {
        name *s=q;
        str stri;
        while(s!=0)
        {
            stri.printname(s->p);
            s=s->next;
        }
    }
    name *insert(name *q, str *u)
    {
        str stri;
        name *k=aloc();
        k->p=u;
        k->next=q;
        q=k;
        return q;
    }
    name *delet(name *q, str *u)
    {
        str stri;
        name *y=q;
        if(stri.compare(u,y->p)==0)
        {
            q=q->next;
            return q;
        }
        while((y!=0)&&(y->next!=0)&&(stri.compare(u,y->next->p)!=0))
        {
            y=y->next;
        }
        if(y!=0)
        {
            name *t=y->next;
            if(t!=0)
                y->next=t->next;
            if(t==0)
                y->next=0;
            if(t!=0) t=0;
            delete(t);
        }
        return q;
    }
};
class red_black_tree1
{
public:
    red_black_tree1 *rc;
    red_black_tree1 *lc;
    name *actoremovi ;
    str *movtitle;
    int yearmovi ;
    int durationmovi;
    red_black_tree1()
    {
        lc=0;
        rc=0;
    }
    red_black_tree1 *aloc(str *moviname, name *actor, int year, int duration, red_black_tree1 *i, red_black_tree1 *j)
    {
        red_black_tree1 *s=new red_black_tree1 ;
        s->movtitle=moviname;
        s->actoremovi=actor;
        s->yearmovi=year;
        s->durationmovi=duration;
        s->lc=i;
        s->rc=j;
        return s;
    }
    red_black_tree1 *search(red_black_tree1 *s, str *movi)
    {
        str stri;
        if(s==0)
            return 0;
        if(stri.compare(s->movtitle, movi)==0)
            return s;
        if(stri.compare(s->movtitle, movi)==1)
            return search(s->lc, movi);
        return search(s->rc, movi);
    }
    void inorder(red_black_tree1 *q)
    {
        str stri;
        name  nameactor;
        if(q!=0)
        {
            inorder(q->lc);
            stri.printname(q->movtitle);
            cout<<"  ";
            inorder(q->rc);
        }
    }
    int max(int a, int b)
    {
        if(a>b) return a;
        return b;
    }
    int hight(red_black_tree1 *s)
    {
        int m;
        if(s==0) return -1;
        m=max(hight(s->lc),hight(s->rc));
        return m+1;
    }
    red_black_tree1 *Rotate(red_black_tree1 *s,red_black_tree1 *Root,red_black_tree1 *pivot)
    {
        red_black_tree1 *p=parent1(s,Root);
        if(Root->rc==pivot)
        {
            Root->rc=pivot->lc;
            pivot->lc=Root;
            if(p!=0)
            {
                if(Root==p->lc)
                {
                    p->lc=pivot;
                    return s;
                }
                else
                {
                    p->rc=pivot;
                    return s;
                }
            }
            if(p==0)
            {
                s=pivot;
                return s;
            }
        }
        else
        {
            Root->lc=pivot->rc;
            pivot->rc=Root;
            if(p!=0)
            {
                if(Root==p->lc)
                {
                    p->lc=pivot;
                    return s;
                }
                else
                {
                    p->rc=pivot;
                    return s;
                }
            }
            if(p==0)
            {
                s=pivot;
                return s;
            }
        }
    }
    red_black_tree1 *parent1(red_black_tree1 *s,red_black_tree1 *p)
    {
        str stri;
        if(s==0) return 0;
        if(stri.compare(p->movtitle,s->movtitle)==0)
        return 0;
        if(s->rc!=0)
        {
            if(stri.compare(p->movtitle,s->rc->movtitle)==0)
            return s;
        }
        if(s->lc!=0)
        {
            if(stri.compare(p->movtitle,s->lc->movtitle)==0)
            return s;
        }
        if(stri.compare(p->movtitle,s->movtitle)==1)
            return parent1(s->rc,p);
        return parent1(s->lc,p);
    }
    red_black_tree1 *chang(red_black_tree1 *s,red_black_tree1 *p)
    {
        while(p!=0)
        {
            if((hight(p->lc)>hight(p->rc))&&((hight(p->lc)-hight(p->rc))>1))
            {
                if((hight(p->lc->lc)-hight(p->lc->rc))>0)
                {
                    s=Rotate(s,p,p->lc);
                    return s;
                }
                if((hight(p->lc->lc)-hight(p->lc->rc))<0)
                {
                    s=Rotate(s,p->lc,p->lc->rc);
                    s=Rotate(s,p,p->lc);
                    return s;
                }
            }
            if((hight(p->rc)>hight(p->lc))&&((hight(p->rc)-hight(p->lc))>1))
            {
                if((hight(p->rc->rc)-hight(p->rc->lc))>0)
                {
                    s=Rotate(s,p,p->rc);
                    return s;
                }
                if((hight(p->rc->rc)-hight(p->rc->lc))<0)
                {
                    s=Rotate(s,p->rc,p->rc->lc);
                    s=Rotate(s,p,p->rc);
                    return s;
                }
            }
            p=parent1(s,p);
        }
        return s;
    }
    red_black_tree1 *chang1(red_black_tree1 *s,red_black_tree1 *p)
    {
        while(p!=0)
        {
            if((hight(p->lc)>hight(p->rc))&&((hight(p->lc)-hight(p->rc))>1))
            {
                if((hight(p->lc->lc)-hight(p->lc->rc))>0)
                {
                s=Rotate(s,p,p->lc);
                }
                if((hight(p->lc->lc)-hight(p->lc->rc))<0)
                {
                    s=Rotate(s,p->lc,p->lc->rc);
                   s=Rotate(s,p,p->lc);
                }
            }
            if((hight(p->rc)>hight(p->lc))&&((hight(p->rc)-hight(p->lc))>1))
            {
                if((hight(p->rc->rc)-hight(p->rc->lc))>0)
                {
                    s=Rotate(s,p,p->rc);
                }
                if((hight(p->rc->rc)-hight(p->rc->lc))<0)
                {
                    s=Rotate(s,p->rc,p->rc->lc);
                    s=Rotate(s,p,p->rc);
                }
            }
            p=parent1(s,p);
        }
        return s;
    }
    red_black_tree1 *insertion1(red_black_tree1 *s,red_black_tree1 *p)
    {
        str stri;
        if(s==0)
        {
            s=aloc(p->movtitle,p->actoremovi,p->yearmovi,p->durationmovi,0,0);
            return s;
        }
        if(stri.compare(s->movtitle,p->movtitle)==1)
            s->lc=insertion1(s->lc,p);
        if(stri.compare(s->movtitle,p->movtitle)==-1)
            s->rc=insertion1(s->rc,p);
        return s;
    }
    str *parent(red_black_tree1 *p,str *n)
    {
        str stri;
        if(p==0) return 0;
        if(stri.compare(p->movtitle,n)==0)
            return 0;
        if(p->lc!=0)
        {
            if(stri.compare(p->lc->movtitle,n)==0)
            return p->movtitle;
        }
        if(p->rc!=0)
        {
            if(stri.compare(p->rc->movtitle,n)==0)
            return p->movtitle;
        }
        if(stri.compare(p->movtitle,n)==-1)
            return parent(p->rc,n);
        if(stri.compare(p->movtitle,n)==1)
            return parent (p->lc,n);
    }
    red_black_tree1 *node(red_black_tree1 *p,str * x)
    {
        str  stri;
        if(p==0) return 0;
        if(stri.compare(p->movtitle,x)==0)
            return p;
        if(stri.compare(p->movtitle,x)==1)
            return node(p->lc,x);
        return node(p->rc,x);
    }
    red_black_tree1 *delet(red_black_tree1 *p, red_black_tree1 *x)
    {
        str stri;
        if(p==0) return 0;
        if(stri.compare(p->movtitle,x->movtitle)==0)
        {
            if((p->lc==0)&&(p->rc==0))
            {
                p=0;
                return 0;
            }
            if((p->lc==0)&&(p->rc!=0))
            {
                p=p->rc;
                return p;
            }
            if((p->rc==0)&&( p->lc!=0))
            {
                p=p->lc;
                return p;
            }
            red_black_tree1  *l=p->rc;
            while(l->lc!=0)
                l=l->lc;
            str *k=l->movtitle;
            delet(p,l);
            p->movtitle=stri.copy(k);
            return p;
        }
        red_black_tree1  *k=parent1(p,x);
        if((x->lc==0)&&(x->rc==0))
        {
            if((k->lc!=0)&&(stri.compare(k->lc->movtitle,x->movtitle)==0))
            {
                k->lc=0;
                delete(x);
                return p;
            }
            k->rc=0;
            delete(x);
            return p;
        }
        if((x->lc!=0)&&(x->rc==0))
        {
            if((k->lc!=0)&&(stri.compare(k->lc->movtitle,x->movtitle)==0))
            {
                k->lc=x->lc;
                delete(x);
                return p;
            }
            k->rc=x->lc;
            delete(x);
            return p;
        }
        if((x->lc==0)&&(x->rc!=0))
        {
            if((k->lc!=0)&&(stri.compare(k->lc->movtitle,x->movtitle)==0))
            {
                k->lc=x->rc;
                delete(x);
                return p;
            }
            k->rc=x->rc;
            delete(x);
            return p;
        }
        red_black_tree1 *y=x->rc;
        while(y->lc!=0)
            y=y->lc;
        str *s=y->movtitle;
        delet(p,y);
        x->movtitle=stri.copy(s);
        return p;
    }
};
class red_black_tree2
{
public:
    red_black_tree2 *rc;
    red_black_tree2 *lc;
    str *actoremovi;
    name *moviname;
    red_black_tree2()
    {
        lc=0;
        rc=0;
    }
    red_black_tree2 *aloc(str *actorename , name *movinam, red_black_tree2 *l, red_black_tree2 *r)
    {
        red_black_tree2 *k=new red_black_tree2;
        k->lc=l;
        k->rc=r;
        k->actoremovi=actorename;
        k->moviname=movinam;
        return k;
    }
    int max(int a,int b)
    {
        if(a>b)
            return a;
        return b;
    }
    int hight(red_black_tree2 *s)
    {
        int m;
        if(s==0)return -1;
        m=max(hight(s->lc),hight(s->rc));
        return m+1;
    }
    red_black_tree2 *Rotate(red_black_tree2 *s ,red_black_tree2 *Root, red_black_tree2 *pivot)
    {
        red_black_tree2 *p=parent1(s,Root);
        if(Root->rc==pivot)
        {
            Root->rc=pivot->lc;
            pivot->lc=Root;
            if(p!=0)
            {
                if(Root==p->lc)
                {
                    p->lc=pivot;
                    return s;
                }
                else
                {
                    p->rc=pivot;
                    return s;
                }
            }
            if(p==0)
            {
                s=pivot;
                return s;
            }
        }
        else
        {
            Root->lc=pivot->rc;
            pivot->rc=Root;
            if(p!=0)
            {
                if(Root==p->lc)
                {
                    p->lc=pivot;
                    return s;
                }
                else
                {
                    p->rc=pivot;
                    return s;
                }
            }
            if(p==0)
            {
                s=pivot;
                return s;
            }
        }
    }
    red_black_tree2 *parent1(red_black_tree2 *s,red_black_tree2 *p)
    {
        str stri;
        if(s==0) return 0;
        if(stri.compare(p->actoremovi,s->actoremovi)==0)
            return 0;
        if(s->rc!=0)
        {
            if(stri.compare(p->actoremovi,s->rc->actoremovi)==0)
                return s;
        }
        if(s->lc!=0)
        {
            if(stri.compare(p->actoremovi,s->lc->actoremovi)==0)
                return s;
        }
        if(stri.compare(p->actoremovi,s->actoremovi)==1)
            return parent1(s->rc,p);
        return parent1(s->lc,p);
    }
    red_black_tree2 *chang(red_black_tree2 *s,red_black_tree2 *p)
    {
        while(p!=0)
        {
            if((hight(p->lc)>hight(p->rc))&&((hight(p->lc)-hight(p->rc))>1))
            {
                if((hight(p->lc->lc)-hight(p->lc->rc))>0)
                {
                    s=Rotate(s,p,p->lc);
                    return s;
                }
                if((hight(p->lc->lc)-hight(p->lc->rc))<0)
                {
                    s=Rotate(s,p->lc,p->lc->rc);
                    s=Rotate(s,p,p->lc);
                    return s;
                }
            }
            if((hight(p->rc)>hight(p->lc))&&((hight(p->rc)-hight(p->lc))>1))
            {
                if((hight(p->rc->rc)-hight(p->rc->lc))>0)
                {
                    s=Rotate(s,p,p->rc);
                    return s;
                }
                if((hight(p->rc->rc)-hight(p->rc->lc))<0)
                {
                    s=Rotate(s,p->rc,p->rc->lc);
                    s=Rotate(s,p,p->rc);
                    return s;
                }
            }
            p=parent1(s,p);
        }
        return s;
    }
    red_black_tree2 *chang1(red_black_tree2 *s,red_black_tree2 *p)
    {
        while(p!=0)
        {
            if((hight(p->lc)>hight(p->rc))&&((hight(p->lc)-hight(p->rc))>1))
            {
                if((hight(p->lc->lc)-hight(p->lc->rc))>0)
                {
                    s=Rotate(s,p,p->lc);
                }
                if((hight(p->lc->lc)-hight(p->lc->rc))<0)
                {
                    s=Rotate(s,p->lc,p->lc->rc);
                    s=Rotate(s,p,p->lc);
                }
            }
            if((hight(p->rc)>hight(p->lc))&&((hight(p->rc)-hight(p->lc))>1))
            {
                if((hight(p->rc->rc)-hight(p->rc->lc))>0)
                {
                    s=Rotate(s,p,p->rc);
                }
                if((hight(p->rc->rc)-hight(p->rc->lc))<0)
                {
                    s=Rotate(s,p->rc,p->rc->lc);
                    s=Rotate(s,p,p->rc);
                }
            }
            p=parent1(s,p);
        }
        return s;
    }
    red_black_tree2 *insertion2(red_black_tree2 *s,red_black_tree2 *p)
    {
        str stri;
        name actores;
        if(s==0)
        {
            s=aloc(p->actoremovi,p->moviname,0,0);
            return s;
        }
        if(stri.compare(s->actoremovi,p->actoremovi)==1)
            s->lc=insertion2(s->lc,p);
        if(stri.compare(s->actoremovi,p->actoremovi)==-1)
            s->rc=insertion2(s->rc,p);
        return s;
    }
    red_black_tree2 *delet1(red_black_tree2 *p,red_black_tree2 *x)
    {
        str stri;
        if(p==0) return 0;
        if(stri.compare(p->actoremovi,x->actoremovi)==0)
        {
            if((p->lc==0)&&(p->rc==0))
            {
                p=0;
                return 0;
            }
            if((p->lc==0)&&(p->rc!=0))
            {
                p=p->rc;
                return p;
            }
            if((p->rc==0)&&( p->lc!=0))
            {
                p=p->lc;
                return p;
            }
            red_black_tree2 *l=p->rc;
            while(l->lc!=0)
                l=l->lc;
            str *k=l->actoremovi;
            delet1(p,l);
            p->actoremovi=stri.copy(k);
            return p;
        }
        red_black_tree2 *k=parent1(p,x);
        if((x->lc==0)&&(x->rc==0))
        {
            if((k->lc!=0)&&(stri.compare(k->lc->actoremovi,x->actoremovi)==0))
            {
                k->lc=0;
                delete(x);
                return p;
            }
            k->rc=0;
            delete(x);
            return p;
        }
        if((x->lc!=0)&&(x->rc==0))
        {
            if((k->lc!=0)&&(stri.compare(k->lc->actoremovi,x->actoremovi)==0))
            {
                k->lc=x->lc;
                delete(x);
                return p;
            }
            k->rc=x->lc;
            delete(x);
            return p;
        }
        if((x->lc==0)&&(x->rc!=0))
        {
            if((k->lc!=0)&&(stri.compare(k->lc->actoremovi,x->actoremovi)==0))
            {
                k->lc=x->rc;
                delete(x);
                return p;
            }
            k->rc=x->rc;
            delete(x);
            return p;
        }
        red_black_tree2 *y=x->rc;
        while(y->lc!=0)
            y=y->lc;
        str *s=y->actoremovi;
        delet1(p,y);
        x->actoremovi=stri.copy(s);
        return p;
    }
    red_black_tree2 *search(red_black_tree2*s, str *movi)
    {
        str stri;
        if(s==0) return 0;
        if(stri.compare(s->actoremovi,movi)==0)
            return s;
        if(stri.compare(s->actoremovi,movi)==1)
            return search(s->lc,movi);
        return search(s->rc,movi);
    }
    void inorder(red_black_tree2 *q)
    {
        str stri;
        name  nameactor;
        if(q!=0)
        {
            inorder(q->lc);
            stri.printname(q->actoremovi);
            cout<<"  ";
            inorder(q->rc);
        }
    }
};
class red_black_tree3
{
public:
    red_black_tree3 *rc;
    red_black_tree3 *lc;
    name *moviname;
    int yearmovi;
    red_black_tree3()
    {
        lc=0;
        rc=0;
    }
    red_black_tree3 *aloc(int year ,name *movinam, red_black_tree3 *l, red_black_tree3 *r)
    {
        red_black_tree3 *k=new red_black_tree3;
        k->lc=l;
        k->rc=r;
        k->yearmovi=year;
        k->moviname=movinam;
        return k;
    }
    int max(int a,int b)
    {
        if(a>b)
            return a;
        return b;
    }
    int hight(red_black_tree3 *s)
    {
        int m;
        if(s==0) return -1;
        m=max(hight(s->lc),hight(s->rc));
        return m+1;
    }
    red_black_tree3 * Rotate(red_black_tree3 *s, red_black_tree3 *Root, red_black_tree3 *pivot)
    {
        red_black_tree3 *p=parent1(s,Root);
        if(Root->rc==pivot)
        {
            Root->rc=pivot->lc;
            pivot->lc=Root;
            if(p!=0)
            {
                if(Root==p->lc)
                {
                    p->lc=pivot;
                    return s;
                }
                else
                {
                    p->rc=pivot;
                    return s;
                }
            }
            if(p==0)
            {
                s=pivot;
                return s;
            }
        }
        else
        {
            Root->lc=pivot->rc;
            pivot->rc=Root;
            if(p!=0)
            {
                if(Root==p->lc)
                {
                    p->lc=pivot;
                    return s;
                }
                else
                {
                    p->rc=pivot;
                    return s;
                }
            }
            if(p==0)
            {
                s=pivot;
                return s;
            }
        }
    }
    red_black_tree3 *chang(red_black_tree3 *s,red_black_tree3 *p)
    {
        while(p!=0)
        {
            if((hight(p->lc)>hight(p->rc))&&((hight(p->lc)-hight(p->rc))>1))
            {
                if((hight(p->lc->lc)-hight(p->lc->rc))>0)
                {
                    s=Rotate(s,p,p->lc);
                    return s;
                }
                if((hight(p->lc->lc)-hight(p->lc->rc))<0)
                {
                    s=Rotate(s,p->lc,p->lc->rc);
                    s=Rotate(s,p,p->lc);
                    return s;
                }
            }
            if((hight(p->rc)>hight(p->lc))&&((hight(p->rc)-hight(p->lc))>1))
            {
                if((hight(p->rc->rc)-hight(p->rc->lc))>0)
                {
                    s=Rotate(s,p,p->rc);
                    return s;
                }
                if((hight(p->rc->rc)-hight(p->rc->lc))<0)
                {
                    s=Rotate(s,p->rc,p->rc->lc);
                    s=Rotate(s,p,p->rc);
                    return s;
                }
            }
            p=parent1(s,p);
        }
        return s;
    }
    red_black_tree3 *chang1(red_black_tree3 *s, red_black_tree3 *p)
    {
        while(p!=0)
        {
            if((hight(p->lc)>hight(p->rc))&&((hight(p->lc)-hight(p->rc))>1))
            {
                if((hight(p->lc->lc)-hight(p->lc->rc))>0)
                {
                    s=Rotate(s,p,p->lc);
                }
                if((hight(p->lc->lc)-hight(p->lc->rc))<0)
                {
                    s=Rotate(s,p->lc,p->lc->rc);
                    s=Rotate(s,p,p->lc);
                }
            }
            if((hight(p->rc)>hight(p->lc))&&((hight(p->rc)-hight(p->lc))>1))
            {
                if((hight(p->rc->rc)-hight(p->rc->lc))>0)
                {
                    s=Rotate(s,p,p->rc);
                }
                if((hight(p->rc->rc)-hight(p->rc->lc))<0)
                {
                    s=Rotate(s,p->rc,p->rc->lc);
                    s=Rotate(s,p,p->rc);
                }
            }
            p=parent1(s,p);
        }
        return s;
    }
    red_black_tree3 *parent1(red_black_tree3 *s, red_black_tree3 *p)
    {
        str stri;
        if(s==0) return 0;
        if(p->yearmovi==s->yearmovi)
            return 0;
        if(s->rc!=0)
        {
            if(p->yearmovi ==s->rc-> yearmovi)
                return s;
        }
        if(s->lc!=0)
        {
            if(p->yearmovi==s->lc->yearmovi)
                return s;
        }
        if(p->yearmovi>s->yearmovi)
            return parent1(s->rc,p);
        return parent1(s->lc,p);
    }
    red_black_tree3 *insertion3(red_black_tree3 *s, red_black_tree3 *p)
    {
        str stri;
        name   actores;
        if(s==0)
        {
            s=aloc(p->yearmovi,p->moviname,0,0);
            return s;
        }
        if(s->yearmovi>p->yearmovi)
            s->lc=insertion3(s->lc,p);
        if(s->yearmovi<p->yearmovi)
            s->rc=insertion3(s->rc,p);
        return s;
    }
    red_black_tree3 *search( red_black_tree3*s,int  movi)
    {
        str stri;
        if(s==0) return 0;
        if(s->yearmovi==movi)
            return s;
        if(s->yearmovi>movi)
            return search(s->lc,movi);
        return search(s->rc,movi);
    }
    red_black_tree3 *delet2(red_black_tree3 *p, red_black_tree3 *x)
    {
        str stri;
        if(p==0) return 0;
        if(p->yearmovi==x->yearmovi)
        {
            if((p->lc==0)&&(p->rc==0))
            {
                p=0;
                return 0;
            }
            if((p->lc==0)&&(p->rc!=0))
            {
                p=p->rc;
                return p;
            }
            if((p->rc==0)&&( p->lc!=0))
            {
                p=p->lc;
                return p;
            }
            red_black_tree3 *l=p->rc;
            while(l->lc!=0)
                l=l->lc;
            int k=l->yearmovi;
            delet2(p,l);
            p->yearmovi=k;
            return p;
        }
        red_black_tree3  *k=parent1(p,x);
        if((x->lc==0)&&(x->rc==0))
        {
            if((k->lc!=0)&&(k->lc->yearmovi==x->yearmovi))
            {
                k->lc=0;
                delete(x);
                return p;
            }
            k->rc=0;
            delete(x);
            return p;
        }
        if((x->lc!=0)&&(x->rc==0))
        {
            if((k->lc!=0)&&(k->lc->yearmovi==x->yearmovi))
            {
                k->lc=x->lc;
                delete(x);
                return p;
            }
            k->rc=x->lc;
            delete(x);
            return p;
        }
        if((x->lc==0)&&(x->rc!=0))
        {
            if((k->lc!=0)&&(k->lc->yearmovi==x->yearmovi))
            {
                k->lc=x->rc;
                delete(x);
                return p;
            }
            k->rc=x->rc;
            delete(x);
            return p;
        }
        red_black_tree3 *y=x->rc;
        while(y->lc!=0)
            y=y->lc;
        int s=y->yearmovi;
        delet2(p,y);
        x->yearmovi=s;
    }
};
int main()
{
    int z;
    int p;
    red_black_tree2 mytree2;
    red_black_tree3 mytree3;
    red_black_tree1 mytree1;
    int m=0;
	int n=0;
	name myname;
	name *meysam=0;//=myname.aloc();
    str mystring ;
    str *f1=new str;
    str *f2=new str;
    red_black_tree2 *k=new red_black_tree2;
    k=0;
    red_black_tree3 *s=new red_black_tree3;
    s=0;
    red_black_tree1 *q=new red_black_tree1;
    q=0;

    char* Input=new char[12];
    while(strcmp(Input,"exit"))
    {
        delete[] Input;
        Input=new char[12];
        cin>>Input;
        if(!strcmp(Input,"addmovie"))
        {
            str *F1=new str;
            F1=mystring.getname(F1);
            red_black_tree1 *u=new red_black_tree1;
            u->actoremovi=0;
            u->movtitle=F1;
            //	cout<<"enter number";
            cin>>m;
            u->yearmovi=m;
            cin.ignore();
            cin>>n;
            u->durationmovi=n;
            cin>>p;
            for(int i=1;i<=p;i++)
            {
                F1=mystring.getname(F1);
                u->actoremovi=myname.insert(u->actoremovi,F1);
                red_black_tree2 *j=mytree2.search(k,F1);
                if(j==0)
                {
                    red_black_tree2 *h=new red_black_tree2;
                    h->actoremovi=F1;
                    h->moviname=0;
                    h->moviname=myname.insert(h->moviname,u->movtitle);
                    k=mytree2.insertion2(k,h);
                    k=mytree2.chang(k,h);
                }
                else
                {
                    j->moviname=myname.insert(j->moviname,u->movtitle);
                }
            }
            red_black_tree3 *l=mytree3.search(s,u->yearmovi);
            if(l==0)
            {
                red_black_tree3 *x=new red_black_tree3;
                x->yearmovi=u->yearmovi;
                x->moviname=0;
                x->moviname=myname.insert(x->moviname,u->movtitle);
                s=mytree3.insertion3(s,x);
                s=mytree3.chang(s,x);
            }
            else
            {
                l->moviname=myname.insert(l->moviname,u->movtitle);
            }
            q=mytree1.insertion1(q,u);
            q=mytree1.chang(q,u);
        }
        else if(!strcmp(Input,"deletemovie"))
        {
            str	*F2=mystring.getname(F2);
            red_black_tree1 *a=mytree1.search(q,F2);
            red_black_tree1 *t=mytree1.parent1(q,a);
            q=mytree1.delet(q,a);
            q=mytree1.chang1(q,t);
        }
        else if(!strcmp(Input,"addactor"))
        {
            str *F7=mystring.getname(F7);
            str *F8=mystring.getname(F8);
            red_black_tree2*v=mytree2.search(k,F8);
            red_black_tree1*b=mytree1.search(q,F7);
            b->actoremovi=myname.insert(b->actoremovi,F8);
            if(v==0)
            {
                red_black_tree2*o=new red_black_tree2;
                o->moviname=0;
                o->actoremovi=F8;
                k=mytree2.insertion2(k,o);
                k=mytree2.chang(k,o);
                o->moviname=myname.insert(o->moviname,F8);
            }
            else
            {
                v->moviname=myname.insert(v->moviname,F7);
            }
        }
        else if(!strcmp(Input,"deleteactor"))
        {
            str *F3=mystring.getname(F3);
            red_black_tree1 *r=mytree1.search(q,F3);
            str *F4=mystring.getname(F4);
            red_black_tree2 *g=mytree2.search(k,F4);
            if(r!=0)
                r->actoremovi=myname.delet(r->actoremovi,F4);
            if(g!=0)
                g->moviname=myname.delet(g->moviname,F3);
        }
        else if(!strcmp(Input,"findmovie"))
        {
            str *F5=mystring.getname(F5);
            red_black_tree1 *y1=mytree1.search(q,F5);
            if(y1==0)
                cout<<"\nnot found\n";
            else
            {
                cout<<"\n";
                mystring.printname(y1->movtitle);
                cout<<"\n";
                cout<<y1->yearmovi;
                cout<<"\n";
                cout<<y1->durationmovi;
                cout<<"\n";
                myname.printname(y1->actoremovi);
                cout<<"\n";
            }
        }
        else if(!strcmp(Input,"findactor"))
        {
            str *F6=mystring.getname(F6);
            red_black_tree2 *y2=mytree2.search(k,F6);
            if(y2==0)
                cout<<" not found\n";
            else
            {
                myname.printname(y2->moviname);
            }
        }
        else if(!strcmp(Input,"findyear"))
        {
            int i;
            cin>>i;
            red_black_tree3 *y3=mytree3.search(s,i);
            if(y3==0)
                cout<<"\n notfind\n";
            else
            {
                cout<<"\n";
                myname.printname(y3->moviname);
                cout<<"\n";
            }
        }
        else if(!strcmp(Input,"findyears"))
        {
            int c; int d;
            cin>>c;
            cin>>d;
            red_black_tree3 *ut;
            for(int i=c;i<=d;i++)
            {
                ut=mytree3.search(s,i);
                if(ut!=0)
                    myname.printname(ut->moviname);
            }
        }
        else if(!strcmp(Input,"listmovies"))
        {
            mytree1.inorder(q);
        }
    }
}
