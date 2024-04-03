class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def is_sorted_linked_list(linked_list):
    current = linked_list
    while current and current.next:
        if current.val >= current.next.val:
            return False
        current = current.next
    return True

def can_rearrange_linked_list(linked_lists):
    result = []
    for linked_list in linked_lists:
        current = linked_list
        while current.next.val > current.val and current.next.next:
            current = current.next
        result.append(not current.next.next)
    return result

def main():
    input_str = input("请输入链表数组（格式为[{1,2,3},{2,3,1},{3,2,1}]）：")
    linked_lists = eval(input_str)
    result = can_rearrange_linked_list(linked_lists)
    print(result)

if __name__ == "__main__":
    main()
