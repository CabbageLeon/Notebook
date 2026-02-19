#include<iostream>
class LinkListNode{
public:
    int val;
    LinkListNode* next;
    LinkListNode(int x):val(x),next(nullptr){};
};

class MyLinkedList {
public:
    LinkListNode* head;
    MyLinkedList() {
        head = nullptr;
    }
    
    int get(int index) {
        LinkListNode* current = nullptr;
        int currentIndex = 0;
        if(this->head == nullptr) return -1; else current = this->head;
        for(int i = 0;i<index;i++)
        {
            if(current->next != nullptr)
            {
                current = current->next;
            }else return -1;
        }
        return current->val;
    }
    
    void addAtHead(int val) {
        if(head == nullptr)
        {
            head = new LinkListNode(val);
        }else
        {
            LinkListNode* temp = head;
            head->val = val;
            head->next = temp;
        }

    }
    
    void addAtTail(int val) {
        LinkListNode* currentNode;
        LinkListNode* newNode = new LinkListNode(val);
        if(head != nullptr)  
        {
            currentNode = head;
        }else 
        {
            head = new LinkListNode(val);
        }
        while(currentNode->next != nullptr)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;

    }
    
    void addAtIndex(int index, int val) {
        LinkListNode* currentNode;
        LinkListNode* newNode = new LinkListNode(val);
        if(index == 0) addAtHead(val);
        else
        {
            if(head!=nullptr) currentNode = head;
                for(int i = 0;i<index-1;i++)
                {
                    if(currentNode->next != nullptr)
                    {
                        currentNode = currentNode->next;
                    }else if (i == index-1)//表示要添加的元素在链表末尾
                    {
                        currentNode->next = newNode;
                    } else return;
                    
                }
                newNode->next = currentNode->next;
                currentNode->next = newNode;
        }
    }
    
    void deleteAtIndex(int index) {
        LinkListNode* currentNode;
        if(head != nullptr) currentNode = head;
        else return;
        if(index == 0)//表示要删除的是头节点
        {
            LinkListNode* temp;
            temp = head;
            head = head->next;
            delete temp;
        }
        for(int i = 0;i<index-1;i++)
        {
            if(currentNode->next != nullptr)
            {
                currentNode = currentNode->next;
            }else return;
        }
        LinkListNode* temp;
        temp = currentNode->next;
        currentNode->next = currentNode->next->next;
        delete temp;
    }
    void LinkListInfo()
    {
        LinkListNode* currentNode;
        if(head != nullptr) currentNode = head;
        else
        {
            printf("nothing in the linklist");
            return;
        }
        while(currentNode != nullptr)
        {
            printf("%d ",currentNode->val);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
int main(int argc, char const *argv[])
{
    MyLinkedList myLinkedList =  MyLinkedList();
    myLinkedList.addAtHead(1);
    myLinkedList.LinkListInfo();
    myLinkedList.addAtTail(3);
    myLinkedList.LinkListInfo();
    myLinkedList.addAtIndex(1, 2);    // 链表变为 1->2->3
    myLinkedList.LinkListInfo();
    myLinkedList.get(1);              // 返回 2
    myLinkedList.deleteAtIndex(1);    // 现在，链表变为 1->3
    myLinkedList.LinkListInfo();
    myLinkedList.get(1);              // 返回 3

    return 0;
}
