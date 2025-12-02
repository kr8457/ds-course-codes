#include <iostream>
#include "Queue.h"
#include "S_list.h"
using namespace std;

template <typename Type>
class Simple_tree {

private:
    Type element;
    Simple_tree* parent_node;
    S_list<Simple_tree*> children;

public:

    Simple_tree(Type const& obj = Type(), Simple_tree* p = NULL)
        : element(obj), parent_node(p) {}

    Type retrieve() const {
        return element;
    }

    Simple_tree* parent() const {
        return parent_node;
    }

    bool is_root() const {
        return parent_node == NULL;
    }

    int degree() const {
        return children.size();
    }

    bool is_leaf() const {
        return degree() == 0;
    }

    Simple_tree* child(int n) const {
        if (n <= 0 || n > degree())
            return NULL;

        Node<Simple_tree*>* ptr = children.head();
        for (int i = 1; i < n; ++i)
            ptr = ptr->next();

        return ptr->retrieve();
    }

    void insert(Type const& obj) {
        children.push_end(new Simple_tree(obj, this));
    }

    int size() const {
        int s = 1;
        for (Node<Simple_tree*>* ptr = children.head(); ptr != NULL; ptr = ptr->next())
            s += ptr->retrieve()->size();
        return s;
    }

    int height() const {
        int h = 0;
        for (Node<Simple_tree*>* ptr = children.head(); ptr != NULL; ptr = ptr->next())
            h = std::max(h, 1 + ptr->retrieve()->height());
        return h;
    }

    void attach(Simple_tree* tree) {
        if (!tree->is_root())
            tree->detach();

        tree->parent_node = this;
        children.push_end(tree);
    }

    void detach() {
        if (is_root())
            return;

        parent()->children.erase(this);
        parent_node = NULL;
    }

    void depth_first_traversal() const {
        cout << retrieve() << "\t";
        for (Node<Simple_tree*>* ptr = children.head(); ptr != NULL; ptr = ptr->next())
            ptr->retrieve()->depth_first_traversal();
    }

    void breadth_first_traversal() {
        Queue<Simple_tree*> q;
        q.enqueue(this);

        while (!q.empty()) {
            Simple_tree* p = q.dequeue();
            cout << p->retrieve() << "\t";

            for (Node<Simple_tree*>* ptr = p->children.head(); ptr != NULL; ptr = ptr->next())
                q.enqueue(ptr->retrieve());
        }
    }

};

int main() {
   

    Simple_tree<char> root('A');
    root.insert('B');
    root.insert('C');

    root.child(1)->insert('D');
    root.child(1)->insert('E');
    root.child(2)->insert('F');

    cout << "Depth-first traversal: ";
    root.depth_first_traversal();
    cout << endl;

    cout << "Breadth-first traversal: ";
    root.breadth_first_traversal();
    cout << endl;

    return 0;
}
