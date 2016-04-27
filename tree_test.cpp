#include<stdio.h>
#include<stack>
#include<queue>
using namespace std;

class TreeNode {
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	~TreeNode(){ 
		printf("desctructor %d\n", val);
		if(left != NULL) delete left;
		if(right != NULL) delete right;
	}
};

class Solution{
public:
	TreeNode* sortedArrayToBST(int nums[], int start, int end) {
		int n = end - start;
		if(n<=0) return NULL;
		if(n==1) return new TreeNode(nums[start]);
		int mid = (start + end)/2;
		TreeNode* root = new TreeNode(nums[mid]);
		root->left = sortedArrayToBST(nums, start, mid);
		root->right = sortedArrayToBST(nums, mid+1, end);
		return root;
	}
	void dfs_preOrder(TreeNode* root){
		TreeNode* node = root;
		//stack<TreeNode*> buf;
		queue<TreeNode*> buf;
		while(true){
			if(node != NULL){
				// visit node
				printf("%d ", node->val);
				if(node->right != NULL) buf.push(node->right);
				node = node->left;
			}
			else {
				if(buf.empty()) break;
				//node = buf.top();
				node = buf.front();
				buf.pop();
			}
		}
	}

	void dfs_inOrder(TreeNode* root){
		TreeNode* node = root;
		//stack<TreeNode*> buf;
		queue<TreeNode*> buf;
		while(true){
			if(node != NULL){
				buf.push(node);
				node = node->left;
			}
			else {
				if(buf.empty()) break;
				//node = buf.top();
				node = buf.front();
				buf.pop();
				// visit node
				printf("%d ", node->val);
				node = node->right;
			}
		}
	}
	void dfs_postOrder(TreeNode* root){
		TreeNode* lastVisitedNode = NULL;
		TreeNode* node = root;
		stack<TreeNode*> buf;
		//queue<TreeNode*> buf;
		while(true){
			if(node != NULL){
				buf.push(node);
				node = node->left;
			}
			else {
				if(buf.empty()) break;
				node = buf.top();// without pop
				//node = buf.front();// without pop
				if(node->right == NULL || node->right == lastVisitedNode) {
					buf.pop();
					// visit node
					printf("%d ", node->val);
					lastVisitedNode = node;
					node = NULL; // without modifying node
				}
				else node = node->right;
			}
		}
	}
	void bfs(TreeNode* root){
		TreeNode* node = root;
		//stack<TreeNode*> buf;
		queue<TreeNode*> buf;
		if(node != NULL) buf.push(node);
		while(true){
			if(buf.empty()) break;
			//node = buf.top();
			node = buf.front();
			buf.pop();
			// visit node
			printf("%d ", node->val);
			if(node->left != NULL) buf.push(node->left);
			if(node->right != NULL) buf.push(node->right);
		}
	}
	void rob_helper(TreeNode* root, int& ans, int& ans_left, int& ans_right){
		if(root == NULL) {
			ans = 0;
			ans_left = 0;
			ans_right = 0;
			return;
		}
		int ans_leftleft, ans_leftright, ans_rightleft, ans_rightright;
		rob_helper(root->left, ans_left, ans_leftleft, ans_leftright);
		rob_helper(root->right, ans_right, ans_rightleft, ans_rightright);

		int sum1 = root->val + ans_leftleft + ans_leftright + ans_rightleft + ans_rightright;
		int sum2 = 0 + ans_left + ans_right;
		ans = max(sum1, sum2);
	}
	int rob(TreeNode* root) {
		int ans, ans_left, ans_right;
		rob_helper(root, ans, ans_left, ans_right);
		return ans;
	}
	void fibonacci(int n, int& ans_n, int& ans_n_1){
		if(n==1) {
			ans_n_1 = 0;
			ans_n = 1;
			return;
		}
		int ans_n_2;
		fibonacci(n-1, ans_n_1, ans_n_2);
		ans_n = ans_n_1 + ans_n_2;
	}
};



int main(){
	int a[] = {-2,-1,3,5,7,9,11};
	//int a[] = {1};
	int len = sizeof(a)/sizeof(int);
	
	Solution s;
	TreeNode* root = s.sortedArrayToBST(a, 0, len);

	s.dfs_preOrder(root);
	printf("\n");
	s.dfs_inOrder(root);
	printf("\n");
	s.dfs_postOrder(root);
	printf("\n");

	s.bfs(root);
	printf("\n");

	printf("rob=%d\n", s.rob(root));
	int f, f_1;
	s.fibonacci(8,f,f_1);
	printf("fibonacci=%d\n", f);

	delete root;
	return 0;
}
