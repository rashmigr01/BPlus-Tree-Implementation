#include <bits/stdc++.h>
using namespace std;
int num;
ofstream dotf("output.dot");
struct Node
{
public:
    vector<int> keys;
    vector<Node *> pts;
    bool leaf;
    int si;
    Node()
    {
        this->leaf = false;
        this->keys = vector<int>(num);
        this->pts = vector<Node *>(num + 1);
    }
};

class Bptree : Node
{
public:
    Node *root;

    Bptree()
    {
        this->root = NULL;
    }
    void insertinner(int, Node *, Node *);
    void deletekeyinner(int, Node *, Node *);
    Node *findparent(Node *, Node *);
    void search(int, vector<vector<string> >);
    void insert(int);
    void deletekey(int);
    void display(Node *, vector<vector<string> >);
    void displayinner(Node *pre);
    void printkeys(Node *);
};

void Bptree::search(int x, vector<vector<string> > data)
{

    if (root != NULL)
    {
        Node *pre = root;
        while (pre->leaf == false)
        {
            for (int i = 0; i < pre->si; i++)
            {
                if (x < pre->keys[i])
                {
                    pre = pre->pts[i];
                    break;
                }
                if (i == pre->si - 1)
                {
                    pre = pre->pts[i + 1];
                    break;
                }
            }
        }
        for (int i = 0; i < pre->si; i++)
        {
            if (pre->keys[i] == x)
            {
                cout << "The key is present and the tuple at the key is: \n";
                for (int k = 0; k < data[pre->keys[i]].size(); k++)
                {
                    cout << data[pre->keys[i]][k] << " ";
                }
                cout << "\n";
                return;
            }
        }
        cout << "The key is not present\n";
    }
    else
    {
        cout << "Empty Tree\n";
    }
}

void Bptree::insert(int x)
{

    if (root != NULL)
    {
        Node *pre = root;
        Node *parent;
        while (pre->leaf == false)
        {
            parent = pre;
            for (int i = 0; i < pre->si; i++)
            {
                if (x < pre->keys[i])
                {
                    pre = pre->pts[i];
                    break;
                }
                if (i == pre->si - 1)
                {
                    pre = pre->pts[i + 1];
                    break;
                }
            }
        }
        if (pre->si < num)
        {
            int i = 0;
            while (x > pre->keys[i] && i < pre->si)
                i++;
            for (int j = pre->si; j > i; j--)
            {
                pre->keys[j] = pre->keys[j - 1];
            }
            pre->keys[i] = x;
            pre->si++;
            pre->pts[pre->si] = pre->pts[pre->si - 1];
            pre->pts[pre->si - 1] = NULL;
        }
        else
        {
            Node *newLeaf = new Node;
            int virtualNode[num + 1];
            int i, j;
            for (i = 0; i < num; i++)
            {
                virtualNode[i] = pre->keys[i];
            }
            i = 0;
            while (x > virtualNode[i] && i < num)
                i++;
            for (int j = num + 1; j > i; j--)
            {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = x;
            newLeaf->leaf = true;
            pre->si = (num + 1) / 2;
            newLeaf->si = num + 1 - (num + 1) / 2;
            pre->pts[pre->si] = newLeaf;
            newLeaf->pts[newLeaf->si] = pre->pts[num];
            pre->pts[num] = NULL;
            for (i = 0; i < pre->si; i++)
            {
                pre->keys[i] = virtualNode[i];
            }
            for (i = 0, j = pre->si; i < newLeaf->si; i++, j++)
            {
                newLeaf->keys[i] = virtualNode[j];
            }
            if (pre == root)
            {
                Node *newRoot = new Node;
                newRoot->keys[0] = newLeaf->keys[0];
                newRoot->pts[0] = pre;
                newRoot->pts[1] = newLeaf;
                newRoot->leaf = false;
                newRoot->si = 1;
                root = newRoot;
            }
            else
            {
                insertinner(newLeaf->keys[0], parent, newLeaf);
            }
        }
    }
    else
    {
        root = new Node;
        root->keys[0] = x;
        root->leaf = true;
        root->si = 1;
    }
}

void Bptree::insertinner(int x, Node *pre, Node *child)
{
    if (pre->si < num)
    {
        int i = 0;
        while (x > pre->keys[i] && i < pre->si)
            i++;
        for (int j = pre->si; j > i; j--)
        {
            pre->keys[j] = pre->keys[j - 1];
        }
        for (int j = pre->si + 1; j > i + 1; j--)
        {
            pre->pts[j] = pre->pts[j - 1];
        }
        pre->keys[i] = x;
        pre->si++;
        pre->pts[i + 1] = child;
    }
    else
    {
        Node *newinner = new Node;
        int virtualKey[num + 1];
        Node *virtualPtr[num + 2];
        int i, j;
        for (i = 0; i < num; i++)
        {
            virtualKey[i] = pre->keys[i];
        }
        for (i = 0; i < num + 1; i++)
        {
            virtualPtr[i] = pre->pts[i];
        }
        i = 0;
        while (x > virtualKey[i] && i < num)
        {
            i++;
        }
        for (int j = num + 1; j > i; j--)
        {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = x;
        for (int j = num + 2; j > i + 1; j--)
        {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newinner->leaf = false;
        pre->si = (num + 1) / 2;
        newinner->si = num - (num + 1) / 2;
        for (i = 0, j = pre->si + 1; i < newinner->si; i++, j++)
        {
            newinner->keys[i] = virtualKey[j];
        }
        for (i = 0, j = pre->si + 1; i < newinner->si + 1; i++, j++)
        {
            newinner->pts[i] = virtualPtr[j];
        }
        if (pre == root)
        {
            Node *newRoot = new Node;
            newRoot->keys[0] = pre->keys[pre->si];
            newRoot->pts[0] = pre;
            newRoot->pts[1] = newinner;
            newRoot->leaf = false;
            newRoot->si = 1;
            root = newRoot;
        }
        else
        {
            insertinner(pre->keys[pre->si], findparent(root, pre), newinner);
        }
    }
}

void Bptree::deletekey(int x)
{
    if (root != NULL)
    {
        Node *pre = root;
        Node *parent;
        int lsib, rsib;
        while (pre->leaf == false)
        {
            for (int i = 0; i < pre->si; i++)
            {
                parent = pre;
                lsib = i - 1;
                rsib = i + 1;
                if (x < pre->keys[i])
                {
                    pre = pre->pts[i];
                    break;
                }
                if (i == pre->si - 1)
                {
                    lsib = i;
                    rsib = i + 2;
                    pre = pre->pts[i + 1];
                    break;
                }
            }
        }
        bool found = false;
        int pos;
        for (pos = 0; pos < pre->si; pos++)
        {
            if (pre->keys[pos] == x)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "The key is not present\n";
            return;
        }
        for (int i = pos; i < pre->si; i++)
        {
            pre->keys[i] = pre->keys[i + 1];
        }
        pre->si--;
        if (pre == root)
        {
            for (int i = 0; i < num + 1; i++)
            {
                pre->pts[i] = NULL;
            }
            if (pre->si == 0)
            {
                delete pre;
                root = NULL;
            }
            return;
        }
        pre->pts[pre->si] = pre->pts[pre->si + 1];
        pre->pts[pre->si + 1] = NULL;
        if (pre->si >= (num + 1) / 2)
        {
            return;
        }
        if (lsib >= 0)
        {
            Node *lNode = parent->pts[lsib];
            if (lNode->si >= (num + 1) / 2 + 1)
            {
                for (int i = pre->si; i > 0; i--)
                {
                    pre->keys[i] = pre->keys[i - 1];
                }
                pre->si++;
                pre->pts[pre->si] = pre->pts[pre->si - 1];
                pre->pts[pre->si - 1] = NULL;
                pre->keys[0] = lNode->keys[lNode->si - 1];
                lNode->si--;
                lNode->pts[lNode->si] = pre;
                lNode->pts[lNode->si + 1] = NULL;
                parent->keys[lsib] = pre->keys[0];
                return;
            }
        }
        if (rsib <= parent->si)
        {
            Node *rNode = parent->pts[rsib];
            if (rNode->si >= (num + 1) / 2 + 1)
            {
                pre->si++;
                pre->pts[pre->si] = pre->pts[pre->si - 1];
                pre->pts[pre->si - 1] = NULL;
                pre->keys[pre->si - 1] = rNode->keys[0];
                rNode->si--;
                rNode->pts[rNode->si] = rNode->pts[rNode->si + 1];
                rNode->pts[rNode->si + 1] = NULL;
                for (int i = 0; i < rNode->si; i++)
                {
                    rNode->keys[i] = rNode->keys[i + 1];
                }
                parent->keys[rsib - 1] = rNode->keys[0];
                return;
            }
        }
        if (lsib >= 0)
        {
            Node *lNode = parent->pts[lsib];
            for (int i = lNode->si, j = 0; j < pre->si; i++, j++)
            {
                lNode->keys[i] = pre->keys[j];
            }
            lNode->pts[lNode->si] = NULL;
            lNode->si += pre->si;
            lNode->pts[lNode->si] = pre->pts[pre->si];
            deletekeyinner(parent->keys[lsib], parent, pre);
            delete pre;
        }
        else if (rsib <= parent->si)
        {
            Node *rNode = parent->pts[rsib];
            for (int i = pre->si, j = 0; j < rNode->si; i++, j++)
            {
                pre->keys[i] = rNode->keys[j];
            }
            pre->pts[pre->si] = NULL;
            pre->si += rNode->si;
            pre->pts[pre->si] = rNode->pts[rNode->si];
            deletekeyinner(parent->keys[rsib - 1], parent, rNode);
            rNode->keys.clear();
            rNode->pts.clear();
        }
    }
    else
    {
        cout << "The tree is empty\n";
    }
}
void Bptree::deletekeyinner(int x, Node *pre, Node *child)
{
    if (pre == root)
    {
        if (pre->si == 1)
        {
            if (pre->pts[1] == child)
            {
                child->keys.clear();
                child->pts.clear();
                delete child;
                root = pre->pts[0];
                pre->keys.clear();
                pre->pts.clear();
                delete pre;
                return;
            }
            else if (pre->pts[0] == child)
            {
                child->keys.clear();
                child->pts.clear();
                delete child;
                root = pre->pts[1];
                pre->keys.clear();
                pre->pts.clear();
                delete pre;
                return;
            }
        }
    }
    int pos;
    for (pos = 0; pos < pre->si; pos++)
    {
        if (pre->keys[pos] == x)
        {
            break;
        }
    }
    for (int i = pos; i < pre->si; i++)
    {
        pre->keys[i] = pre->keys[i + 1];
    }
    for (pos = 0; pos < pre->si + 1; pos++)
    {
        if (pre->pts[pos] == child)
        {
            break;
        }
    }
    for (int i = pos; i < pre->si + 1; i++)
    {
        pre->pts[i] = pre->pts[i + 1];
    }
    pre->si--;
    if (pre->si >= (num + 1) / 2 - 1)
    {
        return;
    }
    if (pre == root)
        return;
    Node *parent = findparent(root, pre);
    int lsib, rsib;
    for (pos = 0; pos < parent->si + 1; pos++)
    {
        if (parent->pts[pos] == pre)
        {
            lsib = pos - 1;
            rsib = pos + 1;
            break;
        }
    }
    if (lsib >= 0)
    {
        Node *lNode = parent->pts[lsib];
        if (lNode->si >= (num + 1) / 2)
        {
            for (int i = pre->si; i > 0; i--)
            {
                pre->keys[i] = pre->keys[i - 1];
            }
            pre->keys[0] = parent->keys[lsib];
            parent->keys[lsib] = lNode->keys[lNode->si - 1];
            for (int i = pre->si + 1; i > 0; i--)
            {
                pre->pts[i] = pre->pts[i - 1];
            }
            pre->pts[0] = lNode->pts[lNode->si];
            pre->si++;
            lNode->si--;
            return;
        }
    }
    if (rsib <= parent->si)
    {
        Node *rNode = parent->pts[rsib];
        if (rNode->si >= (num + 1) / 2)
        {
            pre->keys[pre->si] = parent->keys[pos];
            parent->keys[pos] = rNode->keys[0];
            for (int i = 0; i < rNode->si - 1; i++)
            {
                rNode->keys[i] = rNode->keys[i + 1];
            }
            pre->pts[pre->si + 1] = rNode->pts[0];
            for (int i = 0; i < rNode->si; ++i)
            {
                rNode->pts[i] = rNode->pts[i + 1];
            }
            pre->si++;
            rNode->si--;
            return;
        }
    }
    if (lsib >= 0)
    {
        Node *lNode = parent->pts[lsib];
        lNode->keys[lNode->si] = parent->keys[lsib];
        for (int i = lNode->si + 1, j = 0; j < pre->si; j++)
        {
            lNode->keys[i] = pre->keys[j];
        }
        for (int i = lNode->si + 1, j = 0; j < pre->si + 1; j++)
        {
            lNode->pts[i] = pre->pts[j];
            pre->pts[j] = NULL;
        }
        lNode->si += pre->si + 1;
        pre->si = 0;
        deletekeyinner(parent->keys[lsib], parent, pre);
    }
    else if (rsib <= parent->si)
    {
        Node *rNode = parent->pts[rsib];
        pre->keys[pre->si] = parent->keys[rsib - 1];
        for (int i = pre->si + 1, j = 0; j < rNode->si; j++)
        {
            pre->keys[i] = rNode->keys[j];
        }
        for (int i = pre->si + 1, j = 0; j < rNode->si + 1; j++)
        {
            pre->pts[i] = rNode->pts[j];
            rNode->pts[j] = NULL;
        }
        pre->si += rNode->si + 1;
        rNode->si = 0;
        deletekeyinner(parent->keys[rsib - 1], parent, rNode);
    }
}

Node *Bptree::findparent(Node *pre, Node *child)
{
    Node *parent;
    if (pre->leaf || (pre->pts[0])->leaf)
    {
        return NULL;
    }
    for (int i = 0; i < pre->si + 1; i++)
    {
        if (pre->pts[i] == child)
        {
            parent = pre;
            return parent;
        }
        else
        {
            parent = findparent(pre->pts[i], child);
            if (parent != NULL)
            {
                return parent;
            }
        }
    }
    return parent;
}

void Bptree::display(Node *pre, vector<vector<string> > data)
{
    if (pre->leaf != true)
    {
        for (int i = 0; i < pre->si + 1; i++)
        {
            if (pre->pts[i] != NULL)
            {
                printkeys(pre);
                dotf << "--";
                printkeys(pre->pts[i]);
                dotf << "\n";
                display(pre->pts[i], data);
            }
        }
    }
    else
    {
        for (int j = 0; j < pre->si; j++)
        {
            printkeys(pre);
            dotf << "--";
            dotf << "\"";
            dotf << pre->keys[j] << " ";
            for (int i = 0; i < data[pre->keys[j]].size(); i++)
            {
                dotf << data[pre->keys[j]][i] << " ";
            }
            dotf << "\"";
            dotf << "\n";
        }
    }
}

void Bptree::displayinner(Node *pre)
{
    if (pre->leaf != true)
    {
        for (int i = 0; i < pre->si + 1; i++)
        {
            if (pre->pts[i] != NULL)
            {
                printkeys(pre);
                dotf << "--";
                printkeys(pre->pts[i]);
                dotf << "\n";
                displayinner(pre->pts[i]);
            }
        }
    }
}

void Bptree::printkeys(Node *pre)
{
    dotf << "\"";
    for (int j = 0; j < pre->si; j++)
    {
        dotf << pre->keys[j] << " ";
    }
    dotf << "\"";
}
