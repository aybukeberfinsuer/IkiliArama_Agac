#ifndef bst_hpp
#define bst_hpp
#include <iostream>
#include <cmath>
using namespace std;

template <typename Object>
struct Node
{
    Object data;
    Node<Object> *left;
    Node<Object> *right;
    Node(const Object &dt, Node<Object> *lf = NULL, Node<Object> *rg = NULL)
    {
        left = lf;
        right = rg;
        data = dt;
    }
};

template <typename Object>
class BST
{
private:
    Node<Object> *root;
    void SearchAndAdd(Node<Object> *&subNode, const Object &item)
    {
        if (subNode == NULL)
            subNode = new Node<Object>(item);
        else if (item < subNode->data)
            SearchAndAdd(subNode->left, item);
        else if (item > subNode->data)
            SearchAndAdd(subNode->right, item);
        else
            return;
    }
    bool Search(Node<Object> *subNode, const Object &item) //Burada düğümün varlığı kontrol ediliyor.
    {
        if (subNode == NULL)
            return false;
        if (subNode->data == item)
            return true;
        if (item < subNode->data)
            return Search(subNode->left, item);
        else
            return Search(subNode->right, item);
    }

    bool SearchandDelete(Node<Object> *&subNode, const Object &data)
    { 
        if (subNode == NULL) // Burada düğüm bulunmuyorsa false döndürüyoruz yani bir düğümün olmadığını görüyoruz.
            return false;

        if (subNode->data == data) // Silinmek istenen düğüm üzerinde olduğumuz düğüme eşitse direkt düğümü silebiliriz. Bkz. BST::DeleteNode(Node<Object> *&subNode)
            return DeleteNode(subNode);
        else if (data < subNode->data) // Silinmek istenen düğüm üzerinde olduğumuz düğümden daha küçükse sol tarafta arama yapmaya devam edilmelidir.
            return SearchandDelete(subNode->left, data);
        else // Silinmek istenen düğüm üzerinde olduğumuz düğümden daha büyükse sağ tarafta aramaya devam edilmelidir.
            return SearchandDelete(subNode->right, data);
    }

    bool DeleteNode(Node<Object> *&subNode) // Silme işlemini yapacak olan fonksiyon budur. SearchAndDelete adlı fonksiyon silineceğin belirlemesi,doluluk kontrolleri yapılır.
    {
        Node<Object> *delNode = subNode;
        if (subNode->right == NULL)
            subNode = subNode->left;
        /* !!! ÖNEMLİ !!!
        subNode isimli düğümün sadece sol çocuğu varsa biz subNode'un sol çocuğunu subNode'a eşitliyoruz.
        Artık subNode ebeveyni değil sol çocuğunu gösteriyor. Alttaki de aynı mantık.
        Bu işlemi tek çocuğu olduğunda kullanıyoruz.
        */
        else if (subNode->left == NULL)
            subNode = subNode->right;
        else // Bu fonksiyonda biz silinecek düğümün solunun en sağındakini(veya sağın en solundaki kullanılabilir), silineceğin yerine yazarak silme işlemini gerçekleitiriyoruz.
        {
            delNode = subNode->left;
            Node<Object> *parent = subNode;
            // parent arama aşağıya indikçe bir üst düğümü tutacak.
            while (delNode->right != NULL)
            {
                parent = delNode;
                delNode = delNode->right;
            }
            subNode->data = delNode->data;

            if (parent == subNode) subNode->left = delNode->left;
            // delNode'un hiç sağ çocuğu olmadığı durumda bu ifade oluşur.            
            else parent->right = delNode->left;
            // delNode'un solunu kaybetmemek için paretnin sağına eşitliyoruz.
        }
        delete delNode;
        return true;
    }
    int Height(Node<Object> *subNode)
    {
        if (subNode == NULL)
            return -1;
        return 1 + max(Height(subNode->left), Height(subNode->right));
    }

    void inorder(Node<Object> *&subNode)
    {
        if (subNode != NULL)
        {
            inorder(subNode->left);
            cout << subNode->data << " ";
            inorder(subNode->right);
        }
    }
    void preorder(Node<Object> *subNode)
    {
        if (subNode != NULL)
        {
            cout << subNode->data << " ";
            preorder(subNode->left);
            preorder(subNode->right);
        }
    }
    void postorder(Node<Object> *subNode)
    {
        if (subNode != NULL)
        {
            postorder(subNode->left);
            postorder(subNode->right);
            cout << subNode->data << " ";
        }
    }

    void PrintLevel(Node<Object> *subNode, int level)
    {
        if (subNode == NULL)
            return;
        if (level == 0)
            cout << subNode->data << " ";
        else
        {
            PrintLevel(subNode->left, level - 1);
            PrintLevel(subNode->right, level - 1);
        }
    }

public:
    BST() // ilk önce düğüm olmadığı için kök null gösterecek.
    {
        root = NULL;
    }

    bool isEmpty() const
    {
        return root == NULL;
    }

    void Add(const Object &item) // Bu fonksiyon arayıp eklemeye nerden başlayacağımızı belirliyor.
    {
        SearchAndAdd(root, item);
    }

    void Delete(const Object &data)
    {
        if (SearchandDelete(root, data) == false)
        {
            cout << "Bu dugum onceden silinmistir." << endl;
        }
        else cout<<"Istenilen dugum silindi"<<endl;
        
    }
    bool search(const Object &item)
    {
        if(Search(root, item)==0){
            cout<<"Aradiginiz dugum bulunmamaktadir."<<endl;
        }
        else cout<<"Aradiginiz eleman dugum icinde bulunmaktadir"<<endl;
        
    }
    int Height()
    {
        return 1+Height(root);
    }
    void Clear()
    {
        while (!isEmpty())
            DeleteNode(root);
    }
    void inorder()
    {
        inorder(root);
    }
    void preorder()
    {
        preorder(root);
    }
    void postorder()
    {
        postorder(root);
    }
    void levelorder()
    {
        int h = Height();
        for (int level = 0; level <= h; level++)
        {
            PrintLevel(root, level);
        }
    }
    ~BST()
    {
        Clear();
    }
};

#endif