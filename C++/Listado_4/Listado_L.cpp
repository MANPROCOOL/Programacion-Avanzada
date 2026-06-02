#include <cmath>

#include <cstdio>

#include <vector>

#include <iostream>

#include <algorithm>

using namespace std;

class Difference {
    private:
    vector<int> elements;
  
  	public:
  	int maximumDifference;

	// Add your code here

    Difference(vector<int> arr) {
        elements = arr;
    }

    void computeDifference(){

        int n = elements.size();
        for (int i = 0; i < n - 1; i++){
            for (int j = 0; j < n-1-i; j++) {
                if (elements[j] > elements[j+1]){
                    int temp = elements[j];
                    elements[j] = elements[j+1];
                    elements[j+1] = temp;
                }
            }
        }
        int menor = elements[0];
        int mayor = elements[elements.size() - 1];
        maximumDifference = abs(mayor - menor);
    }

}; // End of Difference class

int main() {
    int N;
    cin >> N;
    
    vector<int> a;
    
    for (int i = 0; i < N; i++) {
        int e;
        cin >> e;
        
        a.push_back(e);
    }
    
    Difference d(a);
    
    d.computeDifference();
    
    cout << d.maximumDifference;
    
    return 0;
}