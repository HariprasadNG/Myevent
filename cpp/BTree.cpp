#include<assert.h>
#include<vector>
#include<iostream>

using namespace std;

#define TS 7

class Btree {
private:
    int values[TS + 1];
    Btree* childs[TS + 2];
    Btree* insertNode(Btree *l, Btree* r, int v);
    Btree* split(int &v);
    unsigned int m_keys;
    Btree* m_parent;
public:
    Btree* search(int v);
    Btree* insert(int v);
    Btree* earase(int v);
    Btree() {
        m_keys = 0;
        m_parent = NULL;
        for (int i=0; i< TS+1; i++) {
            values[i] = 0;
            childs[i] = NULL;
        }
        childs[TS + 2] = NULL;
    }
};


int findFirstLessOrEq(int v, int *a, int l) {
    int s = 0;
    int e = l - 1;
    while (s < e) {
        int m = ((e-s) >> 1) + s;
        if(a[m] == v) return m;
        if(a[m] > v) {
            l = m - 1;
        } else {
            s = m + 1;
        }
    }
    if (a[s] < v) return s;
    return s-1;
}

void insert_at(int i, int v, int *a, int l) {
    for (int j=l-1; j>i; j--) {
        a[j+1] = a[j];
    }
    a[i] = v;
}

Btree* Btree::split(int &v) {
    int mid = TS >> 1;
    assert(m_keys == TS);
    Btree *rt = new Btree();
    v = values[mid];
    rt->m_parent = m_parent; // rt will be the sibling of this node
    for (int i = mid+1; i < TS + 1; i++) {
        rt->values[i-mid-1] = values[i];
        rt->childs[i-mid-1] = childs[i];
        if(rt->childs[i-mid-1])rt->childs[i-mid-1]->m_parent = rt;
        rt->m_keys++;
        m_keys--;
    }
    rt->childs[rt->m_keys] = childs[TS+1];
    //Very iritiating boundry condition bug i fixed
    if(rt->childs[rt->m_keys]) rt->childs[rt->m_keys]->m_parent = rt;
    return rt;
}

Btree* Btree::insertNode(Btree* l, Btree* r, int v) {
    int i = findFirstLessOrEq(v, values, m_keys);
    assert(values[i] != v);
    insert_at(i+1, v, values, m_keys);
    for (int j = m_keys; j >= i+1; j--) {
       childs[j+1] = childs[j];
    }
    childs[i+1] = l;
    childs[i+2] = r;
    if (m_keys == TS) {
        int n;
        Btree *rt = split(n);
        if (!m_parent) {
            Btree *t = new Btree();
            t->values[0] = n;
            t->childs[0] = this;
            t->childs[1] = rt;
            t->m_keys = 1;
            m_parent = t;
            rt->m_parent = t;
            return t;
        }
        return m_parent->insertNode(this, rt, n);
    }
    m_keys++;
    Btree* root = this;
    Btree* prev = NULL;
    while (root) {
       prev = root;
       root = root->m_parent;
    }
    return prev;
}

Btree* Btree::insert(int v) {
    if (m_keys == 0) {
        values[0] = v;
        m_keys++;
        return this;
    }
    
    Btree *next = this;
    Btree *prev = NULL;
    int i = -1;
    while (next) {
        i = findFirstLessOrEq(v, next->values, next->m_keys);
        if ( i > -1 && next->values[i] == v) {
            return this;
        }
        prev = next;
        next = next->childs[i+1];
    };

    insert_at(i+1, v, prev->values, prev->m_keys);
    if (prev->m_keys == TS) {
        int n;
        Btree *rt = prev->split(n);
        if (!prev->m_parent) {
            Btree *t = new Btree();
            t->values[0] = n;
            t->childs[0] = prev;
            t->childs[1] = rt;
            t->m_keys = 1;
            prev->m_parent = t;
            rt->m_parent = t;
            return t;
        }
        return prev->m_parent->insertNode(prev, rt, n);
    }
    prev->m_keys++;
    return this;
}

Btree* Btree::search(int v) {
    if(m_keys == 0) 
    return NULL;
    Btree *c = this;
    Btree *p = NULL;
    int i = findFirstLessOrEq(v, values, m_keys);
    if( (i > -1) && (values[i] == v)) return this;
    if(childs[i+1]) return childs[i+1]->search(v);
    return NULL;
}

int main() {
    Btree* t = new Btree();
    for (int i = 0; i<100; i++) {
        t = t->insert(i);
    }
    return 0;
}
