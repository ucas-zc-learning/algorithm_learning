#include "RbTree.h"

RbTree::RbTree()
{}

RbTree::~RbTree() 
{}

/*
 *@brief 左旋
 *@prame root 根结点；cur当前结点（对应下图的x）
 *        px             px
 *        /              /
 *       x              y
 *      / \     *      / \
 *     lx  y          x  ry
 *        / \        / \
 *       ly ry      lx ly
 */
void RbTree::LeftRotate(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *cur)
{
    // 空指针判断
    if (root == nullptr || cur == nullptr) {
        return;
    }

    // 设置当前结点的右孩子，无右孩子直接返回
    NS_RBTREE::RbNode *cur_right = cur->right;
    if (cur_right == nullptr) {
        return;
    }

    // 当前结点的右指针指向当前结点右孩子的左结点
    // 当前结点右孩子的左结点如果存在，将其父指针指向当前结点
    cur->right = cur_right->left;
    if (cur_right->left != nullptr) {
        cur_right->left->parent = cur;
    }

    // 将当前结点父亲设置为当前结点右孩子的父亲
    cur_right->parent = cur->parent;

    // 如果当前结点父结点为nullptr（即当前结点为根结点）
    // 则将当前结点的右孩子设置为根结点
    if (cur->parent == nullptr) {
        root = cur_right;
    } else {
        // 当前结点为其父结点的左孩子
        // 则将当前结点的右孩子设置为当前结点父结点的左孩子
        if (cur == cur->parent->left) {
            cur->parent->left = cur_right;
        }
        // 当前结点为其父结点的右孩子
        // 则将当前结点的右孩子设置为当前结点父结点的右孩子
        else if (cur == cur->parent->right) {
            cur->parent->right = cur_right;
        }
    }

    // 将当前结点设置为当前结点右孩子的左孩子
    // 将当前结点的父指针指向当前结点右孩子
    cur_right->left = cur;
    cur->parent = cur_right;

    return;
}

/*
 *@brief 右旋
 *@prame root 根结点；cur当前结点（对应下图的x）
 *        px             px
 *        /              /
 *       x              y
 *      / \     *      / \
 *     y  rx          ly  x
 *    / \                / \
 *   ly ry              ry rx
 */
void RbTree::RightRotate(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *cur)
{
    // 空指针判断
    if (root == nullptr || cur == nullptr) {
        return;
    }

    // 设置当前结点的左孩子，无左孩子直接返回
    NS_RBTREE::RbNode *cur_left = cur->left;
    if (cur_left == nullptr) {
        return;
    }

    // 将当前结点左孩子的右孩子设置为当前结点的左孩子
    // 将当前结点左孩子的父指针指向当前结点
    cur->left = cur_left->right;
    if (cur_left->right != nullptr) {
        cur_left->right->parent = cur;
    }
  
    // 将当前结点左孩子的父指针指向当前结点的父结点
    cur_left->parent = cur->parent;

    // 如果当前结点的父指针为nullptr（即当前结点为根结点）
    // 则将当前结点设置为根结点
    if (cur->parent == nullptr) {
        root = cur_left;
    } else {
        // 当前结点为其父结点的左孩子
        // 则将当前结点的左孩子设置为当前结点父结点的左孩子
        if (cur == cur->parent->left) {
            cur->parent->left = cur_left;
        }
        // 当前结点为其父结点的右孩子
        // 则将当前结点的左孩子设置为当前结点父结点的右孩子
        else if(cur == cur->parent->right) {
            cur->parent->right = cur_left;
        }
    }

    // 将当前结点设置为当前结点左孩子的右孩子
    // 将当前结点的父指针指向当前结点左孩子
    cur_left->right = cur;
    cur->parent = cur_left;

    return;
}

/*
 * @prame 插入操作
 * @prame root 根结点；node 待插入结点
 * @return T_OK 成功；T_FAIL 失败
 */
int RbTree::RbTreeInsert(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *node)
{
    // 空指针判断
    if (node == nullptr) {
        return NS_RBTREE::FAIL;
    }

    NS_RBTREE::RbNode *pParent = nullptr;
    NS_RBTREE::RbNode *pNode = root;

    // 查找到插入位置
    while (pNode != nullptr) {
        pParent = pNode;
        if (node->key == pNode->key) {
            return NS_RBTREE::OK;
        } else if (node->key < pNode->key) {
            pNode = pNode->left;
        } else if (node->key > pNode->key) {
            pNode = pNode->right;
        }
    }

    // 设置插入结点的父指针
    node->parent = pParent;

    // 设置插入结点为父指针的孩子
    if (pParent != nullptr) {
        if (node->key < pParent->key) {
            pParent->left = node;
        } else if (node->key > pParent->key) {
            pParent->right = node;
        }
    } else {
        root = node;
        root->color = NS_RBTREE::BLACK;
        return NS_RBTREE::OK;
    }

    // 修正
    return RbTreeInsertFixUp(root, node);
}

/*
 * @brief 修正红黑树
 * @prame root 根结点；node 待插入结点
 * @return T_OK 成功；T_FAIL 失败
 */
int RbTree::RbTreeInsertFixUp(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *node)
{
    // 空指针判断
    if (root == nullptr || node == nullptr) {
        return NS_RBTREE::FAIL;
    }

    // 当父结点存在，且其为红色结点时开始修正
    NS_RBTREE::RbNode *pParent = nullptr;
    while (((pParent = node->parent) != nullptr) 
            && pParent->color == NS_RBTREE::RED)
    {
        // 设置祖父结点
        NS_RBTREE::RbNode *pGparent = pParent->parent;

        if (pGparent == nullptr)
            return NS_RBTREE::OK;

        // 父结点是祖父结点的左孩子
        if (pParent == pGparent->left) {
            // 叔叔结点存在，且其为红色结点
            NS_RBTREE::RbNode *pUncle = pGparent->right;
            if (pUncle != nullptr && pUncle->color == NS_RBTREE::RED)
            {
                // 将叔叔结点和父结点设置为黑色，祖父结点设置为红色
                pUncle->color = NS_RBTREE::BLACK;
                pParent->color = NS_RBTREE::BLACK;
                pGparent->color = NS_RBTREE::RED;

                // 且将当前结点设置为祖父结点
                node = pGparent;
                continue;
            }

            // 叔叔结点不存在或其为黑色结点，且自己是父结点的右孩子
            if (pParent->right == node) {
                // 以父结点为当前结点进行左旋
                LeftRotate(root, pParent);
                // 交换父结点与当前结点
                NS_RBTREE::RbNode *pTemp = pParent;
                pParent = node;
                node = pTemp;
            }

            // 设置父结点为黑色结点，祖父结点为红颜色
            pParent->color = NS_RBTREE::BLACK;
            pGparent->color = NS_RBTREE::RED;

            // 以祖父结点为当前结点进行右旋
            RightRotate(root, pGparent);
        }
        // 父结点是祖父结点的右孩子
        else if (pParent == pGparent->right) {
            // 叔叔结点存在，且其为红色结点
            NS_RBTREE::RbNode *pUncle = pGparent->left;
            if (pUncle != nullptr && pUncle->color == NS_RBTREE::RED)
            {
                // 将叔叔结点和父结点设置为黑色，祖父结点设置为红色
                pParent->color = NS_RBTREE::BLACK;
                pUncle->color = NS_RBTREE::BLACK;
                pGparent->color = NS_RBTREE::RED;

                // 且将当前结点设置为祖父结点
                node = pGparent;
                continue;
            }

            // 叔叔结点不存放或其为黑色结点
            // 当前结点为其父结点的左孩子
            if (pParent->left == node) {
                // 以父结点为当前结点进行右旋
                RightRotate(root, pParent);
                // 交换父结点与当前结点
                NS_RBTREE::RbNode *pTemp = pParent;
                pParent = node;
                node = pTemp;
            }

            // 设置父结点为黑色结点，祖父结点为红颜色
            pParent->color = NS_RBTREE::BLACK;
            pGparent->color = NS_RBTREE::RED;

            // 以祖父结点为当前结点进行右旋
            LeftRotate(root, pGparent);
        }
    }

    // 将根节点设置为黑色
    root->color = NS_RBTREE::BLACK;

    return NS_RBTREE::OK;
}

/*
 * @brief 红黑树查找
 * @prame root 根结点；key 查找键值
 * @return 查找结点地址
 */
NS_RBTREE::RbNode *RbTree::RbTreeSearch(NS_RBTREE::RbNode *root, int key)
{
    NS_RBTREE::RbNode *pNode = root;

    // 查找
    while (pNode != nullptr) {
        // 查找键值相等则找到，返回结点地址
        if (key == pNode->key) {
            return pNode;
        }
        // 查找键值比当前结点键值小，从左子树继续查找
        else if (key < pNode->key) {
            pNode = pNode->left;
        }
        // 查找键值比当前结点键值大，从右子树继续查找
        else if (key > pNode->key) {
            pNode = pNode->right;
        }
    }

    return nullptr;
}

/*
 * @brief 删除结点
 * @prame root 根结点；node 待删除结点
 * @return T_OK 成功；T_FAIL 失败
 */
int RbTree::RbTreeDelete(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *node)
{
    // 异常判断
    if (root == nullptr || node == nullptr) {
        return NS_RBTREE::FAIL;
    }

    // 变量声明
    int color;
    NS_RBTREE::RbNode *child = nullptr;
    NS_RBTREE::RbNode *parent = nullptr;

    // 当被删除结点的左右子树都不为空
    if (node->left != nullptr && node->right != nullptr)
    {
        // 取当前结点右子树的最左结点当作替换结点
        NS_RBTREE::RbNode *replace = node->right;
        while (replace->left != nullptr) {
            replace = replace->left;
        }

        // 被删除结点不是根结点时
        if (node->parent != nullptr) {
            if (node->parent->left == node) {
                node->parent->left = replace;
            } else if (node->parent->right == node) {
                node->parent->right = replace;
            }
        }
        // 被删除结点是根结点
        else 
        {
            root = replace;
        }

        // 取取代结点的右孩子（肯定不存在左孩子），即需要调整的结点
        child = replace->right;
        // 取取代结点的父结点 
        parent = replace->parent;
        // 取取代结点的颜色
        color = replace->color;

        // 被删除结点是它后继结点的父结点
        if (parent == node) {
            parent = replace;
        } else {
            if (child != nullptr) {
                child->parent = parent;
            }

            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
        }

        // 设置替换结点的父子关系以及颜色值
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        // 如果删除结点颜色是黑色，则需要修正
        if (color == NS_RBTREE::BLACK) {
            RbTreeDeleteFixUp(root, child, parent);
        }

        // 释放内存
        delete node;
        node = nullptr;
        
        return NS_RBTREE::OK;
    }

    // 取替换结点的子树（只能有一颗或者没有）
    if (node->left != nullptr) {
        child = node->left;
    } else {
        child = node->right;
    }

    // 取被删除结点的父结点和颜色值
    parent = node->parent;
    color = node->color;

    if (child != nullptr) {
        child->parent = parent;
    }

    if (parent != nullptr) {
        if (parent->left == node) {
            parent->left = child;
        } else if (parent->right == node) {
            parent->right = child;
        }
    } else {
        root = child;
    }

    // 删除黑色结点，修正
    if (color == NS_RBTREE::BLACK) {
        RbTreeDeleteFixUp(root, child, parent);
    }

    // 释放内存
    delete node;
    node = nullptr;

    return NS_RBTREE::OK;    
}

/*
 * @brief 删除结点后修正
 * @prame root 根结点；child 待修正结点；parent 修正结点的父结点
 * @return T_OK 成功；T_FAIL 失败
 */
int RbTree::RbTreeDeleteFixUp(NS_RBTREE::RbNode *&root, 
                NS_RBTREE::RbNode *child, NS_RBTREE::RbNode *parent)
{
    // 叔叔结点
    NS_RBTREE::RbNode *uncle;

    // 当待修正结点为空或其颜色为黑，且待修正结点不为根结点
    while ((child == nullptr || child->color == NS_RBTREE::BLACK) && child != root)
    {
        // 待修正结点是其父结点的左结点
        if (parent->left == child) {
            // 取叔叔结点
            uncle = parent->right;
            if (uncle == nullptr) {
                break;
            }

            // 叔叔结点是红色
            if (uncle->color == NS_RBTREE::RED) {
                uncle->color = NS_RBTREE::BLACK;
                parent->color = NS_RBTREE::RED;
                LeftRotate(root, parent);
                uncle = parent->right;
            }

            // 叔叔结点的左结点为空或者其左结点的颜色为黑
            // 且叔叔结点的右结点为空或者其右结点颜色为黑
            if ((uncle->left == nullptr || uncle->left->color == NS_RBTREE::BLACK) 
                    && (uncle->right == nullptr || uncle->right->color == NS_RBTREE::BLACK))
            {
                uncle->color = NS_RBTREE::RED;
                child = parent;
                parent = child->parent;
            }
            else
            {
                // 叔叔结点的右结点为空或者其颜色为黑色
                if (uncle->right == nullptr || uncle->right->color == NS_RBTREE::BLACK)
                {
                    uncle->left->color = NS_RBTREE::BLACK;
                    uncle->color = NS_RBTREE::RED;
                    RightRotate(root, uncle);
                    uncle = parent->right;
                }
               
                // 叔叔结点的右结点是红色，左结点任意颜色 
                uncle->color = parent->color;
                parent->color = NS_RBTREE::BLACK;
                uncle->right->color = NS_RBTREE::BLACK;
                RightRotate(root, parent);
                child = root;
                break;
            }
        }
        else
        {
            // 取叔叔结点
            uncle = parent->left;
            if (uncle == nullptr) {
                break;
            }

            // 叔叔结点是红色
            if (uncle->color == NS_RBTREE::RED) {
                uncle->color = NS_RBTREE::BLACK;
                parent->color = NS_RBTREE::RED;
                RightRotate(root, parent);
                uncle = parent->left;
            }

            // 叔叔结点的左结点为空或者其左结点的颜色为黑
            // 且叔叔结点的右结点为空或者其右结点颜色为黑
            if ((uncle->left == nullptr || uncle->left->color == NS_RBTREE::BLACK) 
                    && (uncle->right == nullptr || uncle->right->color == NS_RBTREE::BLACK))
            {
                uncle->color = NS_RBTREE::RED;
                child = parent;
                parent = child->parent;
            }
            else
            {
                // 叔叔结点的左结点为空或者其颜色为黑色
                if (uncle->left == nullptr || uncle->left->color == NS_RBTREE::BLACK)
                {
                    uncle->right->color = NS_RBTREE::BLACK;
                    uncle->color = NS_RBTREE::RED;
                    RightRotate(root, uncle);
                    uncle = parent->left;
                }
               
                // 叔叔结点的左结点是红色，右结点任意颜色 
                uncle->color = parent->color;
                parent->color = NS_RBTREE::BLACK;
                uncle->left->color = NS_RBTREE::BLACK;
                RightRotate(root, parent);
                child = root;
                break;
            }
        }
    }

    // 待修正结点不为空，将其颜色设置为黑色
    if (child != nullptr) {
        child->color = NS_RBTREE::BLACK;
    }

    return NS_RBTREE::OK;
}