void reverse() {
    if (head_Node == nullptr) return;

    Node* curr = head_Node;
    Node* temp = nullptr;

    // Swap next and prev for every node
    while (curr != nullptr) {
        temp = curr->prev();           // store prev
        curr->setprev(curr->next());   // swap prev and next
        curr->setnext(temp);

        curr = curr->prev();           // move forward (since we swapped)
    }

    // Swap head and tail
    temp = head_Node;
    head_Node = tail_Node;
    tail_Node = temp;
}
2