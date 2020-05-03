#include <iostream>
#include <memory>


class A: public std::enable_shared_from_this<A>
{
public:
    // конструктор
    A(int key): key(key) {}
    /* деструктор, должен автоматически вызываться после
       окончания программы при удалении дерева */
    ~A()
    {
        /* эту строку выводим на экран, чтобы было видно,
           что узел удалился */
        std::cout << "Destructor" << std::endl;
    }
    // добавление указателя на левый потомок
    void addLeft(std::shared_ptr<A> &lChild)
    {
        leftChild = lChild;
        leftChild->setParent(shared_from_this());
    }
    // добавление указателя на правый потомок
    void addRight(std::shared_ptr<A> &rChild)
    {
        rightChild = rChild;
        rightChild->setParent(shared_from_this());
    }
    // добавление указателя на родительский узел
    void setParent(std::shared_ptr<A> parent)
    {
        this->parent = parent;
    }
    std::shared_ptr<A> leftChild; // указатель на левый узел-потомок
    std::shared_ptr<A> rightChild; // указатель на левый узел-потомок
    std::weak_ptr<A> parent; // указатель на узел-родитель
    /* указатель на узел-родитель делаем weak_ptr, чтобы избежать
       циклических зависимостей, иначе дерево после окончания программы
       не удалится */

    int key; // переменная для хранения значения в узле дерева
};

// функция добавления узла в дерево
std::shared_ptr<A> insert(std::shared_ptr<A> node, int key)
{
    /* если место пустое (этот код выполняется, если мы нашли,
       куда вставлять новый узел. Рекурсивный поиск места для
       вставки происходит далее) */
    if (node == nullptr)
    {
        A a1(key);// TODO: создать экземпляр класса A, в конструктор передать key
        std::shared_ptr<A> ptr = &a1;// TODO: создать shared_ptr к созданному экземпляру
        return ptr;// TODO: вернуть этот shared_ptr
    }

    // рекурсивный поиск места для вставки и вставка, если нашли
    if (key < node->key)
    {
        /* TODO: рекурсивный вызов функции insert, функция возвращает
           shared_ptr на левый потомок к node */
        // TODO: добавить в node левый потомок с помощью функции addLeft
        // TODO: сделать node родительским узлом для левого потомка
    }
    else if (key > node->key)
    {
        /* TODO: рекурсивный вызов функции insert, функция возвращает
           shared_ptr на правый потомок к node */
        // TODO: добавить в node правый потомок с помощью функции addLeft
        // TODO: сделать node родительским узлом для правого потомка
    }

    return node;
}

// симметричный обход дерева
void inorder(std::shared_ptr<A> root)
{
    if (root != nullptr)
    {
        inorder(root->leftChild);
        std::cout << "Node " << root->key;
        if (root->parent.lock() == nullptr)
            std::cout << " Parent: NULL" << std::endl;
        else
            std::cout << " Parent:" << root->parent.lock()->key << std::endl;
        inorder(root->rightChild);
    }
}

int main()
{
    A* root = new A(50); // создаем корень дерева
    std::shared_ptr<A> rootPtr(root); // создаем shared_ptr на корень
    /* создаем следующее дерево:
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80
    */
    // для добавления каждого следующего узла вызываем функцию insert
    insert(rootPtr, 30);
    insert(rootPtr, 20);
    insert(rootPtr, 40);
    insert(rootPtr, 70);
    insert(rootPtr, 60);
    insert(rootPtr, 80);

    // выводим дерево на экран, симметричный обход
    inorder(rootPtr);

    /* Что должно получиться при выводе:
       Node 20 Parent: 30
       Node 30 Parent: 50
       Node 40 Parent: 30
       Node 50 Parent: NULL
       Node 60 Parent: 70
       Node 70 Parent: 50
       Node 80 Parent: 70
       Destructor
       Destructor
       Destructor
       Destructor
       Destructor
       Destructor
       Destructor
    */

    /* в конце программы все узлы автоматически удаляются,
       вызываются деструкторы */
    return 0;
}

