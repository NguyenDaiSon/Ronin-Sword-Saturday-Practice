from typing import List, Optional

class ListNode:
    def __init__(self, val=0):
        self.val = val
        self.next = None

class SinglyLinkedList:
    def __init__(self):
        self.head: Optional[ListNode] = None
    
    def build(self, values: List[int]):
        current = None
        for value in values:
            new_node = ListNode(value)
            if not self.head:
                self.head = new_node
            else:
                current.next = new_node
            current = new_node

    def make_cycle(self, cycle_pos: int):
        circle = None
        tail = None
        current = self.head
        pos = 0

        while current:
            if pos == cycle_pos:
                circle = current
            tail = current
            current = current.next
            pos += 1

        if tail and circle:
            tail.next = circle

    def has_cycle(self) -> bool:
        slow, fast = self.head, self.head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                return True
        return False

if __name__ == '__main__':
    sll = SinglyLinkedList()
    sll.build([3, 2, 0, -4])
    print(f"Has Cycle: {sll.has_cycle()}")
    sll.make_cycle(1)
    print(f"Has Cycle: {sll.has_cycle()}")

