#include <iostream>
#include <queue>
#include <omp.h>
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

void bfs(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            Node* current;

            #pragma omp critical
            {
                current = q.front();
                q.pop();
                cout << current->data << " ";
            }

            #pragma omp critical
            {
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
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
    cout << "\nBFS Traversal: ";
    bfs(root);
    double end = omp_get_wtime();

    cout << "\nExecution Time: " << (end - start) << " seconds\n";
    return 0;
    

}