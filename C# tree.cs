using System;
using System.Reflection;

namespace Tree
{
    internal class AvlTree <T1, T2> where T2 : IComparable<T2>
    {
        private class Node
        {
            public T1 Data;
            public T2 Key;
            public Node PLeft, PRight;
            public int Height;

            public Node(T1 data, T2 key)
            {
                Data = data;
                Key = key;
                Height = 1;
                PLeft = PRight = null;
            }
        }

        private Node _pRoot;

        private int Height(Node pNode)
        {
            return pNode?.Height ?? 0;
        }

        private int balance_factor(Node pNode)
        {
            return Height(pNode.PRight) - Height(pNode.PLeft);
        }

        private void fix_height(Node pNode)
        {
            int lHeight = pNode.PLeft?.Height ?? 0;
            int rHeight = pNode.PRight?.Height ?? 0;
            pNode.Height = (lHeight > rHeight ? lHeight : rHeight) + 1;
        }

        private Node rotate_right(Node pNode)
        {
            Node temp = pNode.PLeft;
            pNode.PLeft = temp.PRight;
            temp.PRight = pNode;
            fix_height(pNode);
            fix_height(temp);
            return temp;
        }

        private Node rotate_left(Node pNode)
        {
            Node temp = pNode.PRight;
            pNode.PRight = temp.PLeft;
            temp.PLeft = pNode;
            fix_height(pNode);
            fix_height(temp);
            return temp;
        }

        private Node Balance(Node pNode)
        {
            fix_height(pNode);
            if (balance_factor(pNode) == 2)
            {
                if (balance_factor(pNode.PRight) < 0)
                    pNode.PRight = rotate_right(pNode.PRight);
                return rotate_left(pNode);
            }

            if (balance_factor(pNode) == -2)
            {
                if (balance_factor(pNode.PLeft) > 0)
                    pNode.PLeft = rotate_left(pNode.PLeft);
                return rotate_right(pNode);
            }

            return pNode;
        }

        private Node Insert (Node pNode, T1 data, T2 key)
        {
            if (pNode == null) return new Node(data, key);

            var compare = pNode.Key.CompareTo(key);
            if (compare > 0) pNode.PLeft = Insert(pNode.PLeft, data, key);
            else if (compare < 0) pNode.PRight = Insert(pNode.PRight, data, key);
            else throw new AmbiguousMatchException($"key node: \"{key}\" already exists");

            return Balance(pNode);
        }

        public void Insert(T1 data, T2 key)
        {
            _pRoot = Insert(_pRoot, data, key);
        }

        public T1 get_data(T2 key)
        {
            var pNode = _pRoot;
            while (pNode != null)
            {
                if (pNode.Key.CompareTo(key) == 0)
                    return pNode.Data;
                if (pNode.Key.CompareTo(key) < 0)
                {
                    pNode = pNode.PRight;
                    continue;
                }

                if (pNode.Key.CompareTo(key) > 0)
                {
                    pNode = pNode.PLeft;
                    continue;
                }

                break;
            }
            throw new NullReferenceException($"node with key \"{key}\" does not exist");
        }

        private Node remove_min(Node pNode, ref Node pMin)
        {
            if (pNode.PLeft == null)
            {
                pMin = pNode;
                return pNode.PRight;
            }
            pNode.PLeft = remove_min(pNode.PLeft, ref pMin);

            return Balance(pNode);
        }

        private Node Remove(Node pNode, T2 key)
        {
            if (pNode == null)
                throw new NullReferenceException($"node with key \"{key}\" does not exist");

            if (pNode.Key.CompareTo(key) < 0) pNode.PRight = Remove(pNode.PRight, key);
            else if (pNode.Key.CompareTo(key) > 0) pNode.PLeft = Remove(pNode.PLeft, key);
            else if (pNode.Key.CompareTo(key) == 0)
            {
                var pLeft = pNode.PLeft;
                var pRight = pNode.PRight;

                if (pRight == null) return pLeft;
                Node min = null;
                var minRight = remove_min(pRight, ref min);
                min.PRight = minRight;
                min.PLeft = pLeft;
                return Balance(min);
            }

            return Balance(pNode);
        }

        public void Remove(T2 key)
        {
            _pRoot = Remove(_pRoot, key);
        }
    }
}
