#include <iostream>

using namespace std;

struct avl {
   int d;
   struct avl *left;
   struct avl *right;
}*r;

class avl_tree {
   public:
      int height(avl*);
      int difference(avl*);
      avl *right_right_rotate(avl*);
      avl *left_left_rotate(avl*);
      avl *left_right_rotate(avl*);
      avl *right_left_rotate(avl*);
      avl *balance(avl*);
      avl *insert(avl*, int);
      void show(avl*, int);
      void inorder(avl*);
      void preorder(avl*);
      void postorder(avl*);
      avl_tree() {
         r = NULL;
      }
};

int avl_tree::height(avl *t) {
   int h = 0;
   if (t != NULL) {
      int l_height = height(t->left);
      int r_height = height(t->right);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
   }
   return h;
}

int avl_tree::difference(avl *t) {
   int l_height = height(t->left);
   int r_height = height(t->right);
   int b_factor = l_height - r_height;
   return b_factor;
}

avl *avl_tree::right_right_rotate(avl *parent) {
   avl *t;
   t = parent->right;
   parent->right = t->left;
   t->left = parent;
   cout<<"Right-Right rotation";
   return t;
}

avl *avl_tree::left_left_rotate(avl *parent) {
   avl *t;
   t = parent->left;
   parent->left = t->right;
   t->right = parent;
   cout<<"Left-Left rotation";
   return t;
}

avl *avl_tree::left_right_rotate(avl *parent) {
   avl *t;
   t = parent->left;
   parent->left = right_right_rotate(t);
   cout<<"Left-Right rotation";
   return left_left_rotate(parent);
}

avl *avl_tree::right_left_rotate(avl *parent) {
   avl *t;
   t = parent->right;
   parent->right = left_left_rotate(t);
   cout<<"Right-Left rotation";
   return right_right_rotate(parent);
}

avl *avl_tree::balance(avl *t) {
   int bal_factor = difference(t);
   if (bal_factor > 1) {
      if (difference(t->left) > 0)
         t = left_left_rotate(t);
      else
         t = left_right_rotate(t);
   } else if (bal_factor < -1) {
      if (difference(t->right) > 0)
         t = right_left_rotate(t);
      else
         t = right_right_rotate(t);
   }
   return t;
}

avl *avl_tree::insert(avl *r, int v) {
   if (r == NULL) {
      r = new avl;
      r->d = v;
      r->left = NULL;
      r->right = NULL;
      return r;
   } else if (v< r->d) {
      r->left = insert(r->left, v);
      r = balance(r);
   } else if (v >= r->d) {
      r->right = insert(r->right, v);
      r = balance(r);
   } return r;
}

void avl_tree::show(avl *p, int l) {
   int i;
   if (p != NULL) {
      show(p->right, l+ 1);
      cout<<" ";
      if (p == r)
         cout << "Root -> ";
      for (i = 0; i < l&& p != r; i++)
         cout << " ";
         cout << p->d;
         show(p->left, l + 1);
   }
}

void avl_tree::inorder(avl *t) {
   if (t == NULL)
      return;
      inorder(t->left);
      cout << t->d << " ";
      inorder(t->right);
}

void avl_tree::preorder(avl *t) {
   if (t == NULL)
      return;
      cout << t->d << " ";
      preorder(t->left);
      preorder(t->right);
}

void avl_tree::postorder(avl *t) {
   if (t == NULL)
      return;
      postorder(t->left);
      postorder(t->right);
      cout << t->d << " ";
}

int main() {
   int choice, input;
   avl_tree avl;
   while (1) {
      cout << "1.Insert Element into the tree" << endl;
      cout << "2.show Balanced AVL Tree" << endl;
      cout << "3.InOrder traversal" << endl;
      cout << "4.PreOrder traversal" << endl;
      cout << "5.PostOrder traversal" << endl;
      cout << "6.Exit" << endl;
      cout << "Enter your Choice: ";
      cin >> choice;

      switch (choice) {
         case 1:
            cout << "Enter value to be inserted: ";
            cin >> input;
            r = avl.insert(r, input);
         break;
         case 2:
            if (r == NULL) {
               cout << "Tree is Empty" << endl;
               continue;
            }
            cout << "Balanced AVL Tree:" << endl;
            avl.show(r, 1);
            cout<<endl;
         break;
         case 3:
            cout << "Inorder Traversal:" << endl;
            avl.inorder(r);
            cout << endl;
         break;
         case 4:
            cout << "Preorder Traversal:" << endl;
            avl.preorder(r);
            cout << endl;
         break;
         case 5:
            cout << "Postorder Traversal:" << endl;
            avl.postorder(r);
            cout << endl;
         break;
         case 6:
            exit(1);
         break;
         default:
            cout << "Wrong Choice" << endl;
      }
   }
   return 0;
}
