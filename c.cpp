#include "pch.h"
#include <iostream>
#include <fstream>


using namespace std;










class nod
{


private:
	int valoare;
	nod* next;
	friend class lista;

public:
	bool is_egal(nod &n)
	{
		if (this == &n) return true;
		else
		{
			return false;
		}
	}


};

class lista
{
public:
	int nr_elemente;
	nod *start;

	lista()
	{
		nr_elemente = 0;
		start = new nod;
		start->next = new nod;
	}

	lista(lista &l)
	{
		nr_elemente = 0;
		start = new nod;
		start->next = new nod;
		copiere(l);
	}

	~lista()
	{

			nod* current = start;
			nod* next;
			int p = 0;
			while (p < nr_elemente) {
				next = current->next;
				delete current;
				current = next;
				p++;
			}

		cout << "D" << endl;
	}


    void adauga_inceput(int el)
    {
        nod *p=new nod;
        p->valoare=el;
        p->next=start;
        start=p;
        nr_elemente++;
    }

	void adauga_cap(int el)
	{
		nod *poz = start;
		for (int i = 0; i < nr_elemente; i++)
		{
			poz = poz->next;
		}
		poz->next = new nod;
		poz->valoare = el;
		nr_elemente++;
	}



	int el(int p)
	{
		if (p > nr_elemente - 1) return -9999;
		nod *poz = start;
		for (int i = 0; i < p; i++)
		{
			poz = poz->next;
		}
		return poz->valoare;

	}

	void rm(int p)
	{
	    if (p>nr_elemente) return;
		if (p == 0)
		{
			nod *poz = start;
			poz = poz->next;
			start = poz;
			nr_elemente--;
			return;
		}

		nod *poz = start;
		for (int i = 0; i < p - 1; i++)
		{
			poz = poz->next;
		}

		nod *par = poz->next;
		poz->next = par->next;
		delete par;

		nr_elemente--;
	}


	void golire()
	{
		for (int i = 0; i < nr_elemente; i++)
		{
			rm(i);
		}
		start->valoare = 0;

	}


	void copiere(lista &m)
	{
		if (start->is_egal(*m.start)) return;
		golire();
		start->valoare = m.start->valoare;
		int i = 1;
		while (m.nr_elemente > i)
		{
			adauga_cap(m.el(i));
			i++;
		}

	}



	void afisare()
	{
		nod *poz = start;
		for (int i = 0; i <nr_elemente; i++)
		{
			cout << poz->valoare<<" ";
			poz = poz->next;

		}
		cout<<endl;
	}


	void swap(nod *n1 ,nod *n2)
	{
		int aux = n1->valoare;
		n1->valoare = n2->valoare;
		n2->valoare = aux;
	}


	void add(lista&l2)
	{
		nod* curent = start;
		for (int i = 1; i < nr_elemente; i++)
		{
			curent = curent->next;
		}
		int s = 0;
		nod* c2 = l2.start;
		if (nr_elemente == 0)
		{
			s = 1;
			curent->valoare = c2->valoare;
			c2 = c2->next;
		}
		for (int i = s; i < l2.nr_elemente; i++)
		{
			curent->next = new nod;
			curent->next->valoare = c2->valoare;
			curent= curent->next;
			c2 = c2->next;
		}
		curent->next = new nod;
		nr_elemente += l2.nr_elemente;
	}


	void sortare()
	{
		bool unsorted = true;
				nod * cur;
		int p;
		while (unsorted) {
			unsorted = false;
			cur = start;
			p = 1;
			while (p<nr_elemente) {
				nod *next = cur->next;
				if (next->valoare < cur->valoare) {
					swap(cur, next);
						unsorted = true;
				}
				p++;
				cur = cur->next;
			}
		}
	}


	void to_multime()
	{
		sortare();
		bool unsorted = true;
		nod * cur;
		int p;
		while (unsorted) {
			unsorted = false;
			cur = start;
			p = 1;
			while (p < nr_elemente) {
				nod *next = cur->next;
				if (next->valoare == cur->valoare) {
					rm(p);
					unsorted = true;
				}
				p++;
				cur = cur->next;
			}
		}



	}

	void intersectie(lista &m)
	{
		to_multime();
		m.to_multime();
		add(m);
		int i = 0,j=0;
		while (i<nr_elemente)
		{
			j = i + 1; int nr = 0;
			while (j<nr_elemente)
			{
				if (el(i) == el(j)) nr++;
				j++;
			}
			if (nr < 1) rm(i);
			else i++;

		}
	}

	void scadere(lista &m)
	{
		lista copie=*this;
		to_multime();
		m.to_multime();
		add(m);
		int i = 0, j = 0;
		while (i < nr_elemente)
		{
			j = i + 1;
			while (j < nr_elemente)
			{
				if (el(i) == el(j)) {
					rm(j); rm(i); j = i+1;
				}
				else j++;
			}
			i++;
		}
		intersectie(copie);
	}

	lista &operator=(lista &m)
	{
		copiere(m);
		return *this;
	}

	 lista &operator+(lista &m)
	{
		 this->add(m);
		return *this;
	}

	void add_p(int p,int el)
	{
	    if(p>=nr_elemente || p<0) {
        cout<<"nu se poate;"<<endl;   return;
	    }
	    nod *poz = start;
		for (int i = 0; i < p; i++)
		{
			poz = poz->next;
		}
		nod *n=new nod;
		n->valoare=el;
		n->next=poz->next;
		poz->next =n;
		nr_elemente++;
	}

    int p_val(int n)
    {
        if(n<nr_elemente) return 99999;
        nod *poz = start;
		for (int i = 0; i < nr_elemente; i++)
		{
		    if(poz->valoare==n) return i;
			poz = poz->next;
		}
        return -1;

    }



};











int main()
{
    int n;
    lista l;
    int ok=false;
    while(!ok)
    {
        cout<<"variante:"<<endl;
        cout<<"2 adaugarea unui nou elementla finalul listei;"<<endl;
        cout<<"3 adaugarea unui nou element in  interiorul  listei"<<endl;
        cout<<"4 afisarea listei;"<<endl;
        cout<<"5 cautarea unui elementdupa valoare;"<<endl;
        cout<<"6 cautarea unui element dupa pozitie"<<endl;
        cout<<"7 stergerea unui element dupa valoare"<<endl;
        cout<<"8 stergerea unui element dupa pozitie;"<<endl;
        cout<<"9 stergerea intregii liste"<<endl;
        cout<<"1 stop"<<endl;
        cout<<"10 adaugare inceput"<<endl;
        cin>>n;
        switch(n)
        {
            case 1: return 0;break;
            case 2:
                {
                    int e;cout<<"valoare:"<<endl;cin>>e;l.adauga_cap(e);break;
                }
            case 3: int e,p; cout<<"pozitie si valoare"<<endl;cin>>p>>e;l.add_p(p-1,e); break;
            case 4: l.afisare();break;
            case 6: cout<<"pozitie: "<<endl;int li; cin>>li; cout<<l.el(li)<<endl;break;
            case 5: cout<<"valoarea: "<<endl;int v; cin>>v; cout<<l.p_val(v)<<endl;break;
            case 7: cout<<"valoare: "<<endl;int val;cin>>val; l.rm(l.p_val(val));break;
            case 8:  cout<<"pozitie:"<<endl;int poz;cin>>poz; l.rm(poz);break;
            case 9: l.golire();break;
            case 10: cout<<"valoare"<<endl; int valoare;cin>>valoare; l.adauga_inceput(valoare);
        }
    }

}
