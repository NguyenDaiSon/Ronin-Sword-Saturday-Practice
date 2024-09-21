class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
    
    def Print(self):
        current = self
        while current:
            print(current.val, end=" ")
            current = current.next
        print("")

    ############################################
    # LC: 83. Remove Duplicates from Sorted List
    ############################################
    def DeleteDuplicates(self):
        current = self
        while current and current.next:
            if current.val == current.next.val:
                current.next = current.next.next
            else:
                current = current.next

if __name__ == '__main__':
    head = ListNode(1, ListNode(1, ListNode(2, ListNode(3, ListNode(3)))))
    head.Print()
    head.DeleteDuplicates()
    head.Print()

