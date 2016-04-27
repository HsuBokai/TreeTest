#include<iostream>
#include<iomanip> // for setw
#include<vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int get_jump(int num){
        if((num&(num+1))==0) return 0;
        int count = 1;
        while(num%2==1){
            num/=2;
            count++;
        }
        return count;
    }
    
    TreeNode* sortedListToBST(ListNode* head) {
        // jump     0 1 0 1 2 1 0 1 2 1 3 1 2 1 0 1 2 1 3 1 2 1 4 
        // num      1 2 3 4 5 6 7 8 9 101112131415
        // depth    1 2 2 3 3 3 3 4 4 4 4 4
        if(head==NULL) return NULL;
        TreeNode* root = new TreeNode(head->val);
        if(head->next==NULL) return root;
        int num = 1;
        int depth = 1;
        head = head->next;
        while(head!=NULL){
            if((num&(num+1))==0){
                TreeNode* temp = root;
                for(int i=1; i<depth; ++i) temp = temp->right;
                temp->right = new TreeNode(head->val);
                depth++;
            }
            else{
                int jump = get_jump(num);
                int count = depth - jump - 1;

		TreeNode* temp = root;
                for(int i=1; i<count; ++i) temp = temp->right;
		TreeNode* & ptr = (count==0) ? root : temp->right;

		TreeNode* r = ptr->right;
		ptr->right = r->left;
		r->left = ptr;
		ptr = r;

                for(int i=1; i<jump; ++i) r = r->right;
                r->right = new TreeNode(head->val);
	    }
            num++;
            head = head->next;
        }
        return root;
    }
};

void delete_tree(TreeNode* root){
	if(root==NULL) return;
	delete_tree(root->left);
	delete_tree(root->right);
	delete root;
}

#define length 7
void printnodemid(TreeNode* n, size_t rep, bool b = 1) {
      static vector<bool> trace;
      if(rep!=0) trace.push_back(b);
      if(n!=0) printnodemid(n->right, rep+1, 1);
      for(size_t i = 1; i < rep; ++i) {
         if(trace[i-1]!=trace[i]) cout<<setw(length)<<right<<"|";
	 else cout<<setw(length)<<right<<"";
      }
      if(rep!=0) cout<<setw(length)<<right<<"|";
      if(n==0) { 
         cout<<"-- NULL"<<"\n";  
	 trace.pop_back();
	 return; 
      }
      cout<<"-- "<<n->val<<"\n";
      printnodemid(n->left, rep+1, 0);
      trace.pop_back();
      if(rep==0) trace.clear();
   }



int main(){
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11};
	int s = sizeof(arr)/sizeof(int);
	ListNode* head = NULL;
	ListNode* temp = NULL;
	for(int i=0; i<s; ++i){
		temp = new ListNode(arr[s-i-1]);
		temp->next = head;
		head = temp;
	}

	Solution sol;
	TreeNode* root = sol.sortedListToBST(head);
	printnodemid(root, 0);

	delete_tree(root);

	for(int i=0; i<s; ++i){
		temp = head;
		head = head->next;
		delete temp;
	}
	return 0;
}
