/********************************************************************************
 * Quick Sort - Count number of comparisons 
********************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <assert.h>
#include <algorithm>

// #include <boost/log/core.hpp>
// #include <boost/log/trivial.hpp>
// #include <boost/log/expressions.hpp>
// 
// namespace logging = boost::log;

namespace {
    void print_vector(std::vector<int> &arr) {
        std::stringstream ss;
        for (auto &v : arr) {
            ss << v << " ";
        }
        //BOOST_LOG_TRIVIAL(trace) << ss.str(); 
    }

    enum pivot_choice_t { FIRST, MEDIAN_OF_THREE, LAST};
    pivot_choice_t pc = pivot_choice_t::FIRST;
    // start and end are always INCLUSIVE
    size_t choose_pivot(std::vector<int> arr, size_t start, size_t end) {
        assert (start <= end);
        switch (pc) {
            case pivot_choice_t::FIRST:
                return start;
            
            case pivot_choice_t::LAST:
                return end;
            
            case pivot_choice_t::MEDIAN_OF_THREE:
                // Random using 3 median rule
                assert (end >= (start+2));
                auto compute_m3_idx = [&]() -> size_t {
                    auto a = arr[start];
                    auto b = arr[(start+end)/2];
                    auto c = arr[end];
                    
                    auto x = a - b; 
                    auto y = b - c;
                    auto z = a - c;
  
                    // Checking if b is middle (x and y both are positive) 
                    if (x * y > 0) 
                        return (start+end)/2;
                    else if (x * z > 0) // Checking if c is middle then if a>c => a>b 
                        return end; 
                    else
                        return start;  
                };
                return compute_m3_idx(); 
        }
    }

    void quick_sort_partition(std::vector<int> &arr, size_t l, 
        size_t r, size_t &p) {
        assert(p>=l && p<=r);

        auto pval = arr[p];

        // Move the pivot to left most if its not at the left already
        if (l != p)
            std::swap(arr[l], arr[p]);

        // l position is pivot
        // l+1 to i-1 is <p
        // i to j-1 is >p
        // j to r is TBD

        auto i = l+1; 
        for (auto j=l+1; j<=r; j++) {
            if (arr[j] < pval) {
                std::swap(arr[j], arr[i++]);
            }
        }

        // l - pivot
        // l+1 to i-1 are <p
        // i to r are >p

        std::swap(arr[l], arr[i-1]);
        p = i-1;
    }

    int quick_sort_impl(std::vector<int> &arr, size_t start, size_t end) {
        //BOOST_LOG_TRIVIAL(info) << "Quick Sort Called with start = " << 
        //    start << " end = " << end; 

        if (start == end) {
            return 0;
        } else if (end == (start+1)) {
            if (arr[start] > arr[end]) 
                std::swap(arr[start], arr[end]);
            return 1;
        }

        auto p = choose_pivot(arr, start, end);
        assert(p>=start && p<=end);
        //BOOST_LOG_TRIVIAL(info) << "Partition around chosen pivot index = " << p; 

        quick_sort_partition(arr, start, end, p);
        //BOOST_LOG_TRIVIAL(trace) << "Post Partitioning"; 
        print_vector(arr);

        auto left  = (p!=start) ? quick_sort_impl(arr, start, p-1) : 0;
        auto right = (p!=end) ? quick_sort_impl(arr, p+1, end) : 0;

        return left+right+(end-start);

    }

    void quick_sort(std::vector<int> &arr) {
        auto arr1 = arr; 
        auto arr2 = arr;
        pc = pivot_choice_t::FIRST;
        auto comp_pc_first = quick_sort_impl(arr, 0, arr.size()-1);
        std::cout << comp_pc_first << std::endl;

        pc = pivot_choice_t::LAST;
        auto comp_pc_last = quick_sort_impl(arr1, 0, arr1.size()-1);
        std::cout << comp_pc_last << std::endl;
        
        pc = pivot_choice_t::MEDIAN_OF_THREE;
        auto comp_pc_random = quick_sort_impl(arr2, 0, arr.size()-1);
        std::cout << comp_pc_random << std::endl;
    }
}


int main (int argc, char **argv) {
    // logging::core::get()->set_filter
    // (
    //     // logging::trivial::severity >= logging::trivial::fatal
    //     logging::trivial::severity >= logging::trivial::info
    // );

    //BOOST_LOG_TRIVIAL(info) << "Reading Input file";
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
    
    //BOOST_LOG_TRIVIAL(info) << "Final count read = " << count ; 
    //BOOST_LOG_TRIVIAL(trace) << "Pre Sorting"; 
    print_vector(input_vector);

    quick_sort(input_vector);

    //BOOST_LOG_TRIVIAL(trace) << "Post Sorting"; 
    print_vector(input_vector);

    return 0;
}

