#include<stdio.h>
#include<vector>
#include <algorithm> // for min()
using namespace std;

class SegmentTree {
	class Segment {
		public:
			int start;
			int end;
			int val;
			Segment() : start(0), end(0), val(0){}
			Segment(const int& s, const int& e, const int& v) : start(s), end(e), val(v){}
			Segment(const Segment& t){
				start = t.start;
				end = t.end;
				val = t.val;
			}
			static int joinOperation(int segment1, int segment2){
				return segment1 + segment2;
				//return min(segment1, segment2);
			}
			Segment join (const Segment& t){
				return Segment(start, t.end, joinOperation(val, t.val));
			}
	};

	Segment* arr;
	int dataSize;
	int treeSize;

	int findLast(){
		int tree_size = treeSize;
		int mask = 0;
		while(tree_size > 1) {
			mask = mask*2 + 1;
			tree_size >>= 1;
		}
		return treeSize & mask;
	}
public:
	SegmentTree(const vector<int>& data) : arr(NULL), dataSize(data.size()), treeSize(2 * dataSize - 1){
		printf("constructor\n");
		arr = new Segment[treeSize];
		
		int tree_index = treeSize;
		int index = findLast();
		for(int i=0; i<dataSize; ++i) {
			arr[--tree_index] = Segment(index, index+1, data[index]);
			--index;
			if(index < 0) index = dataSize-1;
		}
		while(tree_index--){
			arr[tree_index] = arr[ leftIndex(tree_index) ].join( arr[ rightIndex(tree_index) ] );
		}
	}
	~SegmentTree() { 
		printf("destructor\n");
		delete [] arr; 
		arr = NULL;
	}
#define NULL_INDEX -1
	int checkNULL(int tree_index){ return (0 <= tree_index && tree_index < treeSize) ? tree_index : NULL_INDEX; }
	int leftIndex(int tree_index){ return checkNULL(2 * tree_index + 1); }
	int rightIndex(int tree_index){ return checkNULL(2 * tree_index + 2); }
	void traversal(){
#define BUFFER_SIZE 100
		char ans[BUFFER_SIZE];
		dfs_inOrder(0, 0, ans);
	}
	void dfs_inOrder(int tree_index, int level, char ans[]){
		if(tree_index == NULL_INDEX) return;
		// left
		ans[level] = 'l';
		dfs_inOrder(leftIndex(tree_index), level+1, ans);
		// visit
		for(int i=1; i<level; ++i) printf("%4c", (ans[i-1] != ans[i]) ? '|' : ' ');
		if(level > 0) printf("%4c", '|');
		printf("..%02d\n", arr[tree_index].val);
		// right
		ans[level] = 'r';
		dfs_inOrder(rightIndex(tree_index), level+1, ans);
	}
	int get(int start, int end){
		return getHelper(0, start, end);
	}
	int getHelper(int tree_index, const int& start, const int& end){
		int s = arr[tree_index].start, e = arr[tree_index].end;
		if(start == s && end == e) return arr[tree_index].val;
		// 2 outer case
		if(start < s) return getHelper(tree_index, s, end);
		if(end > e) return getHelper(tree_index, s, e);
		// 3 inner cases
		int left = leftIndex(tree_index), right = rightIndex(tree_index);
		int mid = arr[left].end;
		if(end <= mid) return getHelper(left, start, end);
		else if(start >= mid) return getHelper(right, start, end);
		else {
			int left_val = getHelper(left, start, mid);
			int right_val = getHelper(right, mid, end);
			return Segment::joinOperation(left_val, right_val);
		}
	}
	bool set(int pos, int val){
		return setHelper(0, pos, val);
	}
	bool setHelper(int tree_index, const int& pos, const int& val) {
		int s = arr[tree_index].start, e = arr[tree_index].end;
		if(s == pos && e == (pos+1)){
			arr[tree_index].val = val;
			return true;
		}
		// 2 outer case
		if(pos < s) return false;
		if(e <= pos) return false;
		// 3 inner cases
		int left = leftIndex(tree_index), right = rightIndex(tree_index);
		int mid = arr[left].end;
		bool ret;
		if(pos < mid) ret = setHelper(left, pos, val);
		else ret = setHelper(right, pos, val);
		arr[tree_index].val = Segment::joinOperation(arr[left].val, arr[right].val);
		return ret;
	}
};

int main(){
	int ptr[] = {1,8,2,6,9,-3,4,7,0,-5};
	int n = sizeof(ptr)/sizeof(int);
	vector<int> data(ptr, ptr+n);
	SegmentTree t(data);
	t.traversal();
	printf("get rturn %d\n", t.get(1,7));
	t.set(0, 100);
	t.traversal();
	printf("ending\n");
	return 0;
}
