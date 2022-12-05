#include "bst.hpp"
int main()
{
    BST<int> *tree = new BST<int>();
    for (int i = 0; i < 7; i++)
    {
        tree->Add(11 * i);
    }
    cout << "Asagide dugumun sirasiyla inorder, postorder, preorder ve level order dolasimlari verilmistir." << endl;
    tree->inorder();
    cout << endl;

    tree->postorder();
    cout << endl;

    tree->preorder();
    cout << endl;

    tree->levelorder();
    cout << endl;

    cout << "Agacinizin yuksekligi: " << tree->Height();  
    cout<<endl;
    tree->Delete(33);  
    cout << "Agacinizin yeni yuksekligi: " << tree->Height();  


    /*Dilerseniz hpp kodunu inceleyerek başka işlemler de yapabilirsiniz.*/
    return 0;
}