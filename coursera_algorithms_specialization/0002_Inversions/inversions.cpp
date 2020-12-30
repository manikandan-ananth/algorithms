/********************************************************************************
 * Count number of Inversions in a large array
********************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

bool debug = false;

// sorts through start to (end-1)
unsigned long long int merge_sort_and_count(std::vector<int> &arr, int start, int end) { 
    int n = end-start;
    if (n==1) {
        if (debug) {
            std::cout << "merge_sort_and_count with start=" << start << 
                " end=" << end << " inversion=" << 0 << std::endl;
        }
        return 0;
    }

    int middle = (start+end)/2;

    auto left_inversions = merge_sort_and_count(arr, start, middle);
    auto right_inversions = merge_sort_and_count(arr, middle, end);
    auto count_split_inv = [&]() -> unsigned long long int {
        std::vector<int> sorted_arr(n, -1);
        int i=start, j=middle;
        unsigned long long int inv_count = 0;
        for (auto k=0; k<n; k++) {
            if (i<middle && j<end) {
                if (arr[i] < arr[j]) {
                    // no inversions
                    sorted_arr[k] = arr[i++];
                } else {
                    // inversion case
                    sorted_arr[k] = arr[j++];
                    inv_count += (middle - i);
                }
            } else if (i<middle) {
                sorted_arr[k] = arr[i++];
            } else if (j<end) {
                sorted_arr[k] = arr[j++];
            }
        }
        for (auto k=0; k<n; k++) {
            arr[start+k] = sorted_arr[k];
        }
        return inv_count;
    };
    auto split = count_split_inv();

    unsigned long long int inversions = left_inversions + right_inversions + split;
    if (debug) {
        std::cout << "merge_sort_and_count with start=" << start << 
            " end=" << end << 
            " left=" << left_inversions <<
            " right=" << right_inversions <<
            " split=" << split <<
            " inversion=" << inversions << std::endl;
    }
    return inversions;
}

int main (int argc, char** argv) {
    
    std::string input_file = argv[1];
    std::ifstream inFile;
    inFile.open(input_file);
    std::string str;
    int count = 0;
    std::vector<int> input_vector;

    while(std::getline(inFile, str)) {
        int n = std::stoi(str);
        // std::cout << n << std::endl;
        input_vector.push_back(n);
        count++;
    }
    
    if (debug) {
        std::cout << "Final count read = " << count << std::endl << "Pre sorting: ";
        for (auto &v : input_vector) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    auto inv = merge_sort_and_count(input_vector, 0, input_vector.size());
    //if (debug) {
    //    std::cout << "Post sorting: ";
    //    for (auto &v : input_vector) {
    //        std::cout << v << " ";
    //    }
    //    std::cout << std::endl << "Inversion = " << inv << std::endl;
    //}
    std::ofstream ofile;
    ofile.open("output.txt");
    for (auto &v : input_vector) {
        ofile << v << "\n";
    }
    ofile.close();

    std::cout<<inv<<std::endl;

    return 0;
}