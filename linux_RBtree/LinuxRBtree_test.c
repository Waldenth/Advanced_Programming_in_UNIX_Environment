/**
 * 测试Linux-2.6.39.4内核红黑树
*/
#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

/**
 * 宏函数container_of(ptr,type,member)
 * container_of()的作用:
 * 通过一个结构变量中一个成员的地址找到这个结构体变量的首地址
*/

//自己的红黑树结点
struct myType{
    struct rb_node myNode;
    int key; //结点key
};

//红黑树查找
struct myType *mySearch(struct rb_root *root,int key){
    struct rb_node *currentNode=root->rb_node;
    while(currentNode){
        struct myType *data=container_of(currentNode,struct myType,myNode);

        if(key<data->key)
            currentNode=currentNode->rb_left;
        else if(key>data->key)
            currentNode=currentNode->rb_right;
        else //找到了
            return data;
    }
    return NULL;
}

//红黑树插入
int myInsert(struct rb_root *root,struct myType*data){
    struct rb_node **tmp=&(root->rb_node);//tmp二级指针指向rbtree的根节点指针
    struct rb_node*parent=NULL;

    /**
     * 找到合适的位置插入data结点
    */
    while(*tmp){
        struct myType *this = container_of(*tmp,struct myType, myNode);

        parent=*tmp;
        if(data->key<this->key)
            tmp=&((*tmp)->rb_left);
        else if(data->key>this->key)
            tmp=&((*tmp)->rb_right);
        else //当前结点key等于查找key,该key所在结点就是插入结点
            return -1;
    }
    /* 找到位置,插入结点,重新平衡rbtree*/
    rb_link_node(&data->myNode,parent,tmp);
    rb_insert_color(&data->myNode,root);
    return 0;
}

//红黑树删除
void myDelete(struct rb_root *root,int key){
    struct myType*data=mySearch(root,key);
    if(!data){
        fprintf(stderr,"Not Found node, which's key is %d.\n",key);
        return;
    }
    rb_erase(&data->myNode,root);
    free(data);
}

//红黑树遍历,key升序
void myPrint_rbtree_AscendingOrder(struct rb_root *tree){
    struct rb_node*node;
    for(node=rb_first(tree);node;node=rb_next(node)){
        printf("%d ",rb_entry(node,struct myType,myNode)->key);
    }
    printf("\n");
}    

//先序遍历
void PreOrder(struct rb_node*node){
    if(node!=NULL){
        printf("%d ",rb_entry(node,struct myType,myNode)->key);
        PreOrder(node->rb_left);
        PreOrder(node->rb_right);
    }
}
void myPrint_rbtree_PreOrder(struct rb_root *tree){
    PreOrder(tree->rb_node);
    printf("\n");
}

//中序遍历
void InOrder(struct rb_node*node){
    if(node!=NULL){
        InOrder(node->rb_left);
        printf("%d ",rb_entry(node,struct myType,myNode)->key);
        InOrder(node->rb_right);
    }
}
void myPrint_rbtree_InOrder(struct rb_root*tree){
    InOrder(tree->rb_node);
    printf("\n");
}

    
int main(int argc,char*argv[]){    
    struct rb_root mytree=RB_ROOT;
    int i,ret,num;
    struct myType*tmp;
    //启动时没有指定树的结点个数
    if(argc<=1){
        fprintf(stderr,"Please input num of nodes,%s\n",argv[0]);
        exit(-1);
    }

    num=atoi(argv[1]);

    printf("Please enter %d integers as keys:\n",num);
    for(i=0;i<num;i++){
        tmp=malloc(sizeof(struct myType));
        if(!tmp)
            perror("Allocate dynamic memory!");
        scanf("%d",&tmp->key);
        ret=myInsert(&mytree,tmp);
        if(ret<0){
            fprintf(stderr,"The node which's key=%d already exists.\n",tmp->key);
            free(tmp);
        }
    }
    printf("\nThe first test:\n");
    printf("Ascending order traversal:\n\t");
    myPrint_rbtree_AscendingOrder(&mytree);
    printf("Preorder traversal:\n\t");
    myPrint_rbtree_PreOrder(&mytree);
    printf("Inorder traversal:\n\t");
    myPrint_rbtree_InOrder(&mytree);
    int target;
    printf("\nPlease input the key of the node that you want to delete:\t");
    scanf("%d",&target);
    myDelete(&mytree,target);
    printf("\nThe second test:\n");
    printf("Ascending order traversal:\n\t");
    myPrint_rbtree_AscendingOrder(&mytree);
    printf("Preorder traversal:\n\t");
    myPrint_rbtree_PreOrder(&mytree);
    printf("Inorder traversal:\n\t");
    myPrint_rbtree_InOrder(&mytree);
    
    return 0;
}