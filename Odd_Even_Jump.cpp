/*

You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.

You may jump forward from index i to index j (with i < j) in the following way:

During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
It may be the case that for some index i, there are no legal jumps.
A starting index is good if, starting from that index, you can reach the end of the array (index arr.length - 1) by jumping some number of times (possibly 0 or more than once).

Return the number of good starting indices.

 

Example 1:

Input: arr = [10,13,12,14,15]
Output: 2
Explanation: 
From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
From starting index i = 4, we have reached the end already.
In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
jumps.
Example 2:

Input: arr = [2,3,1,1,4]
Output: 3
Explanation: 
From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:
During our 1st jump (odd-numbered), we first jump to i = 1 because arr[1] is the smallest value in [arr[1], arr[2], arr[3], arr[4]] that is greater than or equal to arr[0].
During our 2nd jump (even-numbered), we jump from i = 1 to i = 2 because arr[2] is the largest value in [arr[2], arr[3], arr[4]] that is less than or equal to arr[1]. arr[3] is also the largest value, but 2 is a smaller index, so we can only jump to i = 2 and not i = 3
During our 3rd jump (odd-numbered), we jump from i = 2 to i = 3 because arr[3] is the smallest value in [arr[3], arr[4]] that is greater than or equal to arr[2].
We can't jump from i = 3 to i = 4, so the starting index i = 0 is not good.
In a similar manner, we can deduce that:
From starting index i = 1, we jump to i = 4, so we reach the end.
From starting index i = 2, we jump to i = 3, and then we can't jump anymore.
From starting index i = 3, we jump to i = 4, so we reach the end.
From starting index i = 4, we are already at the end.
In total, there are 3 different starting indices i = 1, i = 3, and i = 4, where we can reach the end with some
number of jumps.
Example 3:

Input: arr = [5,1,3,4,2]
Output: 3
Explanation: We can reach the end from starting indices 1, 2, and 4.
 

Constraints:

1 <= arr.length <= 2 * 104
0 <= arr[i] < 105

*/


/*
First try 

class Solution {
public:
    int oddJump(vector<int>& arr, int k){
        cout<<"Inside odd Jump with k = "<< k <<"\n";
        int n = arr.size();
        int nearest_max = INT_MAX;
        int min_index=INT_MAX;
        for(int i=k+1;i<n;i++){
            if(arr[i]>=arr[k] && arr[i]-arr[k]<=nearest_max){
                if(i<min_index || arr[i]<arr[min_index]){
                    nearest_max=arr[i]-arr[k];
                    min_index=i;
                }
            }
        }
        if(min_index==INT_MAX)
            return -1;
        return min_index;
    }
    
    int evenJump(vector<int>& arr, int k){
        cout<<"Inside even Jump with k = "<< k <<"\n";
        int n = arr.size();
        int nearest_min = INT_MIN;
        int min_index=INT_MAX;
        for(int i=k+1;i<n;i++){
            if(arr[i]<=arr[k] && arr[i]-arr[k]>=nearest_min){
                if(i<min_index || arr[i]>arr[min_index]){
                    nearest_min=arr[i]-arr[k];
                    min_index=i;
                }
            }
        }
        if(min_index==INT_MAX)
            return -1;
        return min_index;
    }
    
    
    int oddEvenJumps(vector<int>& arr) {
        
        int n = arr.size();
        int good=0;
        for(int i=0;i<n;i++){
            int j = i;
            cout<<j<<"\n";
            int jump_counter = 1;
            while(j!=n-1){
                cout<<jump_counter<<"\n";
                if(jump_counter%2==0){
                    int next_jump = evenJump(arr,j);
                    cout<<next_jump<<"\n";
                    if(next_jump==-1){
                        break;
                    }
                    else{
                        j=next_jump;
                        jump_counter++;
                    }
                }
                else{
                    int next_jump = oddJump(arr,j);
                    cout<<next_jump<<"\n";
                    if(next_jump==-1){
                        break;
                    }
                    else{
                        j=next_jump;
                        jump_counter++;
                    }
                }
            }
            if(j==n-1){
                good++;
                cout<<"Good Start\n";
            }
            cout<<"Next Start\n";
        }
        return good;
        
    }
};
*/

class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        if (A.size() <= 1) {
            if (A.size() == 1)
                return 1;
            return 0;
        }
        vector<bool> can_reach_end_even(A.size(), false); //If the next jump is even then can you reach the end?
        vector<bool> can_reach_end_odd(A.size(), false);  //If the next jump is odd then can you reach the end?
        can_reach_end_even[can_reach_end_even.size() - 1] = true; //Since it takes 0 more jumps to reach the end.
        can_reach_end_odd[can_reach_end_odd.size() - 1] = true;
        //m will always map a value of A[i] back to its index i
        map<int, int> m; //Note that we use map rather than unordered_map because we want the map's domain to be ordered by <
        m[A[A.size() - 1]] = A.size() - 1;
        for (int i = can_reach_end_odd.size() - 2; i >= 0; --i) {
            auto it = m.lower_bound(A[i]); //lower_bound() is on average an O(log(m.size())) operation.
            //Note that A[it->second] = it->first by definition of the map m.
			//We will first determine if we can reach the end of A if the next jump we perform is odd.
            int j = -1;//Assume that we can't reach the end. Indicated by making this value negative.
            if (it != m.end()) { //Then there is an A[j] >= A[i] with j > i.
                j = it->second; //A[j] is thus the smallest element of A[i+1], ... A[A.size() -1 ]
                                // that is >= A[i] (and it is the smallest such j). 
                if (can_reach_end_even[j])
                    can_reach_end_odd[i] = true;
            }
			//We will now determine if we can reach the end of A if the next jump we perform is even.
            j = -1;  //Start off assuming that we can't reach the end of A.
			//First check if the j we found above can be used again (this is only possible if A[j] = A[i]).
            if (it != m.end() && it->first == A[i]) { //Then there is an A[j] <= A[i] with j > i.
                j = it->second;
            } else if (it != m.begin()) { //Then there is an A[j] < A[i] with j > i.
                //Note that if execution reaches here then in particular, A's domain has no value equal to A[i].
                //Since std::map totally orders the domain in a binary tree and since the iterator "it"
                // is either m.end() or else its key is the smallest element > A[i], it follows that the
                // element immediately before the iterator "it" must be the greatest element < A[i] 
                //(which is also the greatest element <= A[i])
                --it;  
                j = it->second;
                //assert(A[j] < A[i]);
            }
            if (j >= 0) {
                if (can_reach_end_odd[j])
                    can_reach_end_even[i] = true;
            }
            //Note that if m[A[i]] already has some value then we overwrite it with i because 
            // i will be smaller than the current value of m[A[i]] and since 
            // as described in the problem statement, "you can only jump to the smallest such index j".
            m[A[i]] = i;
        }
        int count = 0;
		//The first jump from any index is always an odd jump (it is jump 1),
		// so count how many odd jumps reach the end.
        for (int i = 0; i < can_reach_end_odd.size(); ++i) {
            count += can_reach_end_odd[i];
        }
        return count;
    }
};
