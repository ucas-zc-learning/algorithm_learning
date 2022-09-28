#include "RbTreeTest.h"

RbTreeTest::RbTreeTest()
{
    root = nullptr;
    obj = nullptr;
}

RbTreeTest::~RbTreeTest()
{}

/**
 * @brief 测试用例，见算法导论第三版习题13.3-2（依次插入41、38、31、12、19、8）
 *        与习题13.4-3（依次删除8、12、19、31、38、41）
 * 
 * @return TEST_OK 测试成功；TEST_FAIL 测试失败
 */
int RbTreeTest::TestCase()
{
    // 测试数据
    std::vector<int> _data = {41, 38, 31, 12, 19, 8};
    std::vector<int> _data_all = {38, 19, 41, 12, 31, 8};
    std::vector<int> _color = {1, 0, 1, 1, 1, 0};
    std::vector<int> _data_except_8 = {38, 19, 41, 12, 31};
    std::vector<int> _color_except_8 = {1, 0, 1, 1, 1};
    std::vector<int> _data_except_12 = {38, 19, 41, 31};
    std::vector<int> _color_except_12 = {1, 1, 1, 0};
    std::vector<int> _data_except_19 = {38, 31, 41};
    std::vector<int> _color_except_19 = {1, 1, 1};
    std::vector<int> _data_except_31 = {38, 41};
    std::vector<int> _color_except_31 = {1, 0};
    std::vector<int> _data_except_38 = {41};
    std::vector<int> _color_except_38 = {1};
    
    // 获取算法对象
    obj = new RbTree();

    std::vector<int>::iterator iter = _data.begin();
    for (; iter != _data.end(); ++iter) {
        NS_RBTREE::RbNode *p = new NS_RBTREE::RbNode();
        if (p == nullptr)
            return TEST_FAIL;

        p->key = *iter;
        obj->RbTreeInsert(root, p);
    }

    Level(_data_all, _color);

    if (TEST_FAIL == SearchAndDelete(8) 
        || TEST_FAIL == Level(_data_except_8, _color_except_8))
        return TEST_FAIL;

    if (TEST_FAIL == SearchAndDelete(12) 
        || TEST_FAIL == Level(_data_except_12, _color_except_12))
        return TEST_FAIL;

    if (TEST_FAIL == SearchAndDelete(19) 
        || TEST_FAIL == Level(_data_except_19, _color_except_19))
        return TEST_FAIL;

    if (TEST_FAIL == SearchAndDelete(31) 
        || TEST_FAIL == Level(_data_except_31, _color_except_31))
        return TEST_FAIL;

    if (TEST_FAIL == SearchAndDelete(38) 
        || TEST_FAIL == Level(_data_except_38, _color_except_38))
        return TEST_FAIL;

    return TEST_OK;
}

int RbTreeTest::Level(std::vector<int> _data, std::vector<int> _color)
{
    int front = 0;
    int rear = 0;
    NS_RBTREE::RbNode *q;
    NS_RBTREE::RbNode *que[MAX_SIZE];		                //定义一个循环队列，用来记录将要访问的层次上的结点
    
    if(root != NULL)
    {
        rear = (rear + 1) % MAX_SIZE;
        que[rear] = root;                                   //根结点入队
        std::vector<int>::iterator data_iter = _data.begin();
        std::vector<int>::iterator color_iter = _color.begin();

        while(front != rear)			                    //当队列不空的时候进行循环
        {
            front = (front + 1) % MAX_SIZE;
            q = que[front];				                    //队头结点出队
            
            if (data_iter == _data.end() || color_iter == _color.end()
                || *data_iter != q->key || *color_iter != q->color)
            {
                return TEST_FAIL;    
            }
            
            ++data_iter;
            ++color_iter;
            
            if(q->left != NULL)		                        //如果左子树不空，则左子树的根结点入队
            {
                rear = (rear + 1) % MAX_SIZE;
                que[rear] = q->left;
			}
            if(q->right != NULL)		                    //如果右子树不空，则右子树的根结点入队
            {
                rear = (rear + 1) % MAX_SIZE;
                que[rear] = q->right;
			}
        }
    }

    return TEST_OK;
}

// 查找结点并删除
int RbTreeTest::SearchAndDelete(int key)
{
    // 查找key的结点
    NS_RBTREE::RbNode *pDst = obj->RbTreeSearch(root, key);
    if (pDst == nullptr)
        return TEST_FAIL;

    // 删除该结点
    if (NS_RBTREE::FAIL == obj->RbTreeDelete(root, pDst))
        return TEST_FAIL;

    return TEST_OK;
}