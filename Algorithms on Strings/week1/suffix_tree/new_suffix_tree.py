# python3
import sys
import queue

global_key = 1;

#  NODE OF TREE
class Node(object):
  """docstring for Node"""
  def __init__(self, key, leaf_value, text_pos):
    self.key = key
    self.leaf_value = leaf_value
    self.text_pos = text_pos
    self.child = {}


#  PRINT TREE
def LevelOrderTransversal(root):
  print("TREE: (node_number, is_leaf, text_pos)")

  # if root is null
  if len(root.child) == 0:
    return
  
  # Standard level order transversal code
  q = queue.Queue() # Create queue
  q.put(root) # Enqueue root

  while not q.empty():
    n = q.qsize()

    # if this node has children
    while n > 0:
      # dequeue an item and print it
      p = q.get()
      print("(" + str(p.key) + "," + str(p.leaf_value) + "," + str(p.text_pos) + ") ")

      # Enqueue all children of the dequeued item
      for x in p.child.values():
        q.put(x)
      n -= 1;

    # print("\n")

# MAKETREE
def growtree(root, s, n, start_pos, text_pos):
  global global_key
  
  while n > 1:
    # no child
    if len(root.child) == 0:
      temp = Node(global_key, -1, text_pos)
      root.child[s[0]] = temp
      root = temp
      global_key += 1



    # when child 
    else:
      # symbol match
      if s[0] in root.child:
        root = root.child[s[0]]      
      else:
        temp = Node(global_key, -1, text_pos)
        root.child[s[0]] = temp
        root = temp
        global_key += 1


    text_pos += 1
    s = s[1:]
    n -= 1

  # last case when n = 1 i.e. s = '$'
  temp = Node(global_key, start_pos, text_pos)
  root.child[s[0]] = temp
  global_key += 1


def build_suffix_tree(text):
    
  """
  Build a suffix tree of the string text and return a list
  with all of the labels of its edges (the corresponding 
  substrings of the text) in any order.
  """
  result = []
  # Implement this function yourself
  root = Node(0, -1, -1)

  text_size = len(text)
  for i in range(text_size):
    growtree(root, text[i:],text_size-i, i, i)

  # print("OK")  
  LevelOrderTransversal(root)

  return result


if __name__ == '__main__':
  text = sys.stdin.readline().strip()
  result = build_suffix_tree(text)
  print("\n".join(result))