from typing import List, Optional

class ListNode:
    def __init__(self, val):
        self.val = val
        self.next = None

    def __repr__(self):
        return f'ListNode(val={self.val})'

class SinglyLinkedList:
    def __init__(self, values: List[int]):
        self.head: Optional[ListNode] = None
        
        current = None
        for value in values:
            new_node = ListNode(value)
            if not self.head:
                self.head = new_node
            else:
                current.next = new_node
            current = new_node

    def Print(self):
        current = self.head
        while current:
            print(current.val,  end=" ")
            current = current.next
        print()

    def MakeIntersectionWithList(self, other: Optional[ListNode], atOtherPos: int):
        tail = None
        current = self.head
        while current:
            tail = current
            current = current.next

        pos = 0
        other_current = other.head
        while other_current:
            if pos == atOtherPos:
                print(f"Creating IntersectionNode: {other_current}")
                if not self.head:
                    tail = other_current
                    self.head = tail
                else:
                    tail.next = other_current
                return
            other_current = other_current.next
            pos += 1

    def GetIntersectionNode(self, other: 'SinglyLinkedList') -> Optional[ListNode]:
        def nextNodeFn(nodeX: ListNode, headY: ListNode) -> Optional[ListNode]:
            return nodeX.next if nodeX else headY

        current = self.head
        other_current = other.head
        while current != other_current:
            current = nextNodeFn(current, other.head)
            other_current = nextNodeFn(other_current, self.head)

        return current

if __name__ == '__main__':
    listA = SinglyLinkedList([4, 1])
    listA.Print()

    listB = SinglyLinkedList([5,6,1,8,4,5])
    listB.Print()

    print(f"IntersectionNode: {listA.GetIntersectionNode(listB)}")

    listA.MakeIntersectionWithList(listB, 3)
    print(f"IntersectionNode: {listA.GetIntersectionNode(listB)}")
    print(f"IntersectionNode: {listB.GetIntersectionNode(listA)}")

