#include<iostream>
#include<stack>
#include<omp.h>
#include<queue>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
};

Node* insert(Node* root, int data) {
    if (!root) {
        root = new Node{data, NULL, NULL};
        return root;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (!temp->left) {
            temp->left = new Node{data, NULL, NULL};
            return root;
        } else {
            q.push(temp->left);
        }

        if (!temp->right) {
            temp->right = new Node{data, NULL, NULL};
            return root;
        } else {
            q.push(temp->right);
        }
    }

    return root;
}


void dfs(Node* root) {
    if (!root) return;

    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        #pragma omp critical
        {
            cout << current->data << " ";
        }

        #pragma omp critical
        {
            if (current->right) s.push(current->right);
            if (current->left) s.push(current->left);
        }
    }
}

int main() {
    Node* root = NULL;
    int data;
    char choice;

    do {
        cout << "Enter data: ";
        cin >> data;
        root = insert(root, data);

        cout << "Insert more nodes? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    double start = omp_get_wtime();
    cout << "\nDFS Traversal: ";
    dfs(root);
    double end = omp_get_wtime();

    cout << "\nExecution Time: " << (end - start) << " seconds\n";
    return 0;
}