/*

You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.

We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.

Return the reformatted license key.

 

Example 1:

Input: s = "5F3Z-2e-9-w", k = 4
Output: "5F3Z-2E9W"
Explanation: The string s has been split into two parts, each part has 4 characters.
Note that the two extra dashes are not needed and can be removed.
Example 2:

Input: s = "2-5g-3-J", k = 2
Output: "2-5G-3J"
Explanation: The string s has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.
 

Constraints:

1 <= s.length <= 105
s consists of English letters, digits, and dashes '-'.
1 <= k <= 104

First try

class Solution {
    public String licenseKeyFormatting(String s, int k) {

        s = s.replace("-","").toUpperCase();
        if(s.length()<=k)
            return s.toUpperCase();
        int n = s.length()%k;
        
        if(n!=0){
            s = s.substring(0,n) + "-"+ s.substring(n);
            n=n+1;
        }
        while(n<s.length()){
            // System.out.println(n);
            n=n+k;
            if(n<s.length()){
                s = s.substring(0,n)+ "-" +s.substring(n);
                // System.out.println(s);
                n=n+1;
            }
        }
        // System.out.println(s);
        return s;
    }
}

*/


class Solution {
    public String licenseKeyFormatting(String s, int k) {
        String str = s.replace("-","");
        str = str.toUpperCase();
        int len = str.length();
        StringBuilder sb = new StringBuilder();
        for(int i=0; i<len; i++){
            sb.append(str.charAt(i));
        }
        for(int i=k; i<len; i+=k){
            sb.insert(len-i,"-");
        }
        return sb.toString();
    }
}