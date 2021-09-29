#include<iostream>
using namespace std;

template<typename T>
struct TreeNode{
    T val;
    TreeNode *lson, *rson;
    int height;
    TreeNode() : lson(nullptr), rson(nullptr), height(0) {}
    TreeNode(T x) : val(x), lson(nullptr), rson(nullptr), height(0) {}
};

template<typename T>
class Splay{
private:
    typedef TreeNode<T> node;
protected:
    node * root;
    int _size;
public:
    Splay() : root(nullptr), _size(0) {}
    ~Splay() {clear();}

    int size() {return _size;}

    node* insert(T, node*);
    node* remove(T, node*);
    node* find(T x, node* p);
    void clear(node *);

    node* init(T x){if (_size) clear(); root = new node(x); _size = 1; return root;}
    node* insert(T x){if (_size) return root = insert(x, root); else return init(x);}
    node* remove(T x){return remove(x, root);}
    node *find(T x){return root = find(x, root);}
    void clear() {clear(root); root = nullptr; _size = 0;}

    bool is_leaf(node* p) const {return !(p->lson || p->rson);}
    bool is_root(node* p) const {return p == root;}
    node *find_min(node* p) const {while(p->lson) p=p->lson; return p;}
    node *find_max(node* p) const {while(p->rson) p=p->rson; return p;}

    node* left_zig(node*);
    node* right_zig(node*);
    node* left_zig_zig(node*);
    node* left_zig_zag(node*);
    node* right_zig_zig(node*);
    node* right_zig_zag(node*);

    int L_HEIGHT(node* p) {return p->lson ? p->lson->height : -1;}
    int R_HEIGHT(node* p) {return p->rson ? p->rson->height : -1;}
    int BALANCE(node* p) {return L_HEIGHT(p) - R_HEIGHT(p);}
};

template<typename T>
TreeNode<T>* Splay<T>::insert(T x, node* p){
    if (_size == 0 || p == nullptr){
        p = new node(x);
        _size++;
    }
    else{
        if (x < p->val){
            p->lson = insert(x, p->lson);
        } 
        else if (x > p->val){
            p->rson = insert(x, p->rson);
        }
    }
    return p;
}


template<typename T>
void Splay<T>::clear(node *p){
    if (p){
        clear(p->lson);
        clear(p->rson);
        delete p;
    }
}

template<typename T>
TreeNode<T>* Splay<T>::find(T x, node* p){
    if (p == nullptr) return nullptr;
    node *q;
    if (x < p->val){
        q = p->lson = find(x, p->lson);
        if (x == q->val){
            if (p != root) return p; // p not root, no need to splay
            else return right_zig(p);
            
        }
        else{
            if (x < q->val) return right_zig_zig(p); // zig zig
            else return right_zig_zag(p); // zig zag
        }

    }
    else if (x > p->val){
        q = p->rson = find(x, p->rson);
        if (x == q->val){
            if (p != root) return p; // p not root, no need to splay
            else return left_zig(p);
            
        }
        else{
            if (x > q->val) return left_zig_zig(p); // zig zig
            else return left_zig_zag(p); // zig zag
        }
    }
    else return p;

}

template<typename T> 
TreeNode<T>* Splay<T>::right_zig(node *p){
    node *q = p->lson;
    p->lson = q->rson;
    q->rson = p;

    p->height = max(L_HEIGHT(p), R_HEIGHT(p)) + 1;
    q->height = max(L_HEIGHT(q), R_HEIGHT(q)) + 1;

    return q;
}

template<typename T> 
TreeNode<T>* Splay<T>::left_zig(node *p){
    node *q = p->rson;
    p->rson = q->lson;
    q->lson = p;

    p->height = max(L_HEIGHT(p), R_HEIGHT(p)) + 1;
    q->height = max(L_HEIGHT(q), R_HEIGHT(q)) + 1;

    return q;
}

template<typename T> 
TreeNode<T>* Splay<T>::right_zig_zag(node *p){
    p->lson = left_zig(p->lson);
    return right_zig(p);
}

template<typename T> 
TreeNode<T>* Splay<T>::left_zig_zag(node *p){
    p->rson = right_zig(p->rson);
    return left_zig(p);
}

template<typename T> 
TreeNode<T>* Splay<T>::right_zig_zig(node *p){
    node *q = p->lson;
    node *r = q->lson;
    p->lson = q->rson;
    q->rson = p;
    q->lson = r->rson;
    r->rson = q;

    p->height = max(L_HEIGHT(p), R_HEIGHT(p)) + 1;
    q->height = max(L_HEIGHT(q), R_HEIGHT(q)) + 1;
    r->height = max(L_HEIGHT(r), R_HEIGHT(r)) + 1;

    return r;
}

template<typename T> 
TreeNode<T>* Splay<T>::left_zig_zig(node *p){
    node *q = p->rson;
    node *r = q->rson;
    p->rson = q->lson;
    q->lson = p;
    q->rson = r->lson;
    r->lson = q;

    p->height = max(L_HEIGHT(p), R_HEIGHT(p)) + 1;
    q->height = max(L_HEIGHT(q), R_HEIGHT(q)) + 1;
    r->height = max(L_HEIGHT(r), R_HEIGHT(r)) + 1;

    return r;
}

int main(){
    Splay<int> tree;
    int N = 100;
    for(int i = 1; i <= N; i++){
        tree.insert(i * 3 % 100);
        tree.find(i * 3 % 100);
    }
    printf("Nyaaaaaan~\n");

    // for(int i = 0; i <= N; i++){
    //     tree.remove(i);
    // }
    return 0;
}
