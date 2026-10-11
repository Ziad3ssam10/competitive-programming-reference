struct Node{
    ll val = 0;
    Node* l = nullptr, *r = nullptr;
    Node(int val) : val(val) {}
};

ll merge(Node* a, Node* b){
    return (a == nullptr ? 0 : a->val) + (b == nullptr ? 0 : b->val);
}

ll query(int l, int r, Node* node, int s, int e){
    if(node == nullptr) return 0;
    if(s >= l && e <= r) return node->val;
    if(e < l || s > r) return 0;
    int mid = (s+e)/2;
    return query(l, r, node->l, s, mid) + query(l, r, node->r, mid+1, e);
}

Node* update(int idx, int val, Node* node, int s, int e){
    if(s == e) return new Node(val);
    Node* curNode = new Node(0);
    curNode->l = (node == nullptr ? nullptr : node->l);
    curNode->r = (node == nullptr ? nullptr : node->r);

    int mid = (s+e)/2;
    if(idx <= mid) curNode->l = update(idx, val, curNode->l, s, mid);
    else curNode->r = update(idx, val, curNode->r, mid+1, e);
    curNode->val = merge(curNode->l, curNode->r);
    return curNode;
}