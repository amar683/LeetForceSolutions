#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
#include<string>
using namespace std;
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};
struct Compare{
    bool operator()(Node* l, Node* r){
        return l->freq > r->freq;
    }
};

void generateCodes(Node* root, const string& prefix, unordered_map<char, string>& codes) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {  // Leaf node
        codes[root->ch] = prefix;
    }

    generateCodes(root->left, prefix + "0", codes);
    generateCodes(root->right, prefix + "1", codes);
}
Node* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (auto pair : frequencies) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        minHeap.push(merged);
    }

    return minHeap.top();
}
string huffmanEncode(string data, unordered_map<char, string>&codes){
    unordered_map<char,int>frequencies;
    for(char ch:data){
        frequencies[ch]++;
    }
    Node *root = buildHuffmanTree(frequencies);
    generateCodes(root,"",codes);
    
    string encodedData;
    for(char ch:data){
        encodedData += codes[ch];
    }
    return encodedData;
}
string huffmanDecode(const string& encodedData, Node* root) {
    string decodedData;
    Node* current = root;
    for (char bit : encodedData) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {  // Leaf node
            decodedData += current->ch;
            current = root;
        }
    }
    return decodedData;
}
int main(){
    string data = "hello huffman";
    unordered_map<char, string> codes;
    string encoded_data = huffmanEncode(data,codes);
    Node* root = buildHuffmanTree({{'h', 1}, {'e', 1}, {'l', 3}, {'o', 1}, {' ', 1}, {'u', 1}, {'f', 2}, {'m', 1}, {'n', 1}});
    string decodedData = huffmanDecode(encoded_data, root);

    cout << "Original data: " << data << endl;
    cout << "Encoded data: " << encoded_data << endl;
    cout << "Decoded data: " << decodedData << endl;
    cout << "Huffman Codes:\n";
    for (auto pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}