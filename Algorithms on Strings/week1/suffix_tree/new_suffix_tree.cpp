#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// Represent a node of an n-ary tree
struct Node
{
	int key;
	int leaf_value;
	int text_pos;
	int num_child;
	vector<Node *> child;
	vector<char>edge_label; // to store corresponding edge label for child
};

// Utility function to create a new tree node
Node *newNode(int key, int text_pos)
{
	Node *temp = new Node;
	temp->key = key;
	temp->leaf_value = -1;
	temp->text_pos = text_pos;
	temp->num_child = 0;
	return temp;
}

// Prints the n-ary tree level wise
void LevelOrderTransversal(Node * root)
{
	cout << "TREE: (node_number , is_leaf, text_pos)\n";

	if(root == NULL)
	 return;

	// Standard level order traversal code using queue
	queue<Node *> q; // Create queue
	q.push(root); // Enqueue root

	while(!q.empty())
	{
		int n = q.size();

		// If this node has children
		while(n > 0)
		{
			// Dequeue an item from queue and print it
			Node * p = q.front();
			q.pop();
			cout << "(" << p->key << "," << p->leaf_value << "," << p->text_pos <<") ";

			// Enqueue all children of the dequeued item
			for (int i = 0; i < p->child.size(); ++i)
				q.push(p->child[i]);
			n--;
		}
		
		cout << endl; // Print new line between two levels
	}
}

// MAKETREE
void growtree(Node * root, string s, int current_pos, int last_pos, int &global_key, int start_pos){
	if(current_pos > last_pos) return;

//CASE1:
	/* 
	if root has children, check through all children
	if found then recursive call
	*/
	for(int i=0; i<root->num_child; i++){
		// if found then this will not be leaf node because of '$'
		if(root->edge_label[i] == s[current_pos]){
			growtree(root->child[i], s, current_pos++, last_pos, global_key, start_pos);
			return;
		}
	}


//CASE2:
	// if root has no children or not found, add new nodes for rest string 
		int last_child = root->num_child;
		while(current_pos < last_pos+1){
			// create new node with global_key
			Node * temp = newNode(global_key, current_pos);
			global_key++;

			// check if it is leaf node
			if(current_pos == last_pos){
				temp->leaf_value = start_pos;
			}

			// push into root's children
			(root->child).push_back(temp);
			(root->edge_label).push_back(s[current_pos]);
			root->num_child++;

			root = root->child[last_child];
			current_pos++;

			last_child = 0;
		}

		return;

}


// COMPRESS TREE
void compress_path(Node * root, vector<string> &result, string until)
{
	// if one child
	while(root->num_child == 1){
		until += root->edge_label[0];
		root = root->child[0];
	}

	// if more than one child
	result.push_back(until);
	for(int i=0; i<root->num_child; i++)
		compress_path(root->child[i], result, string(1, root->edge_label[i]));
	return;
}


// function to Compute Suffix Tree Edges
vector<string> ComputeSuffixTreeEdges(string& text) {

	// to store edges after tree construction
	vector<string> result;

	// Create Root Node
	Node * root = newNode(0, -1);

	int text_size = text.size();
	int global_key = 1;     // to give key to nodes

	// Make tree
	for(int i=0; i<text_size; i++)
		growtree(root, text, i, text_size-1, global_key, i);

	// PRINT TREE
	// LevelOrderTransversal(root);

	// compress paths
	for(int i=0; i<root->child.size(); i++)
		compress_path(root->child[i], result, string(1, root->edge_label[i]));

	return result;
}


//----------------------------MAIN FUNCTION--------------------------
int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);

  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}	