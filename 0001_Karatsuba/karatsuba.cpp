/********************************************************************************
 * Karatsuba multiplication for 2 large numbers
********************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

bool debug = false;

std::string sum(std::string const &s1, std::string const &s2) {
    std::string sum_string = ""; 
    int carry = 0;

    auto i1 = s1.rbegin(), i2=s2.rbegin();
    for (; i1 != s1.rend() && i2 != s2.rend() ; i1++, i2++) {
        int res = *i1 + *i2 - '0' - '0' + carry;
        carry = res/10;
        sum_string.append(std::to_string(res%10));
    }
    for( ; i1 != s1.rend() ; i1++ ) {
        int res = *i1 - '0' + carry;
        carry = res/10;
        sum_string.append(std::to_string(res%10));
    }
    for( ; i2 != s2.rend() ; i2++ ) {
        int res = *i2 - '0' + carry;
        carry = res/10;
        sum_string.append(std::to_string(res%10));
    }

    if (carry)
        sum_string.append(std::to_string(carry));
    
    std::string final_sum_string(sum_string.rbegin(), sum_string.rend());

    bool all_zeros = true;
    for(auto itr = final_sum_string.begin(); itr != final_sum_string.end(); itr++) {
        if (*itr != '0') {
            all_zeros = false;
            break;
        }
    }
    if (all_zeros)
        return "0";

    while (final_sum_string.at(0) == '0' && final_sum_string.size() > 0) {
        final_sum_string.erase(final_sum_string.begin());
    }
    if (debug) std::cout << s1 << " + " << s2 << " = " << final_sum_string << std::endl;
    return final_sum_string;
}

// assumes s1>s2
std::string difference(std::string const &s1, std::string const &s2) {
    std::string res;
    auto it1 = s1.rbegin();
    bool carry = false;
    for (auto it2=s2.rbegin(); it2 != s2.rend(); it2++, it1++) {
        // subtract *it2 from *it1 (*it1 - *it2)
        int a = (*it1 - '0'), b = (*it2 - '0');
        if (carry) {
            a--;
            carry = false;
        }
        if(debug) std::cout << "Subtracting a,b=" <<a<<","<<b<<" carry="<<carry;
        if (a < b) {
            // carry over
            a += 10;
            *(it1+1)--;
            carry = true;
        }
        int r = a-b;
        res.append(std::to_string(r));
        if(debug) std::cout << " res="<<res<<std::endl;
    }
    while (it1!=s1.rend()) {
        int a = *it1 - '0';
        if(debug) std::cout << "remainders a=" << a << " carry=" << carry;
        if (carry) {
            a--;
            if (a == -1) {
                a += 10;
                // carry stays true
            } else
                carry = false;
        }
        res.append(std::to_string(a));
        if(debug) std::cout << " res="<<res<<std::endl;
        it1++;
    }

    std::string final_sum_string(res.rbegin(), res.rend());

    bool all_zeros = true;
    for(auto itr = final_sum_string.begin(); itr != final_sum_string.end(); itr++) {
        if (*itr != '0') {
            all_zeros = false;
            break;
        }
    }
    if (all_zeros)
        return "0";

    while (final_sum_string.at(0) == '0' && final_sum_string.size() > 0) {
        final_sum_string.erase(final_sum_string.begin());
    }
    if(debug) std::cout << s1 << " - " << s2 << " = " << final_sum_string << std::endl;
    return final_sum_string;
}

void normalize_for_karatsuba(std::string &s, int l) {
    if (s.size() > l)
        return;
    if(debug) std::cout << "Normalized " << s;
    int diff = l - s.size(); // # of zeros to add
    std::string s1 = "";
    for (int i=0;i<diff;i++)
        s1 += "0";
    s1+=s;
    s = s1;
    if (debug) std::cout << " to " << s << std::endl;
}

// multiply 2 n-digit numbers in s1 and s2
std::string karatsuba_multiply(std::string &s1, std::string &s2) {

    auto l1 = s1.size();
    auto l2 = s2.size(); 

    if (l1 == 0 || l2 == 0)
        return std::string("0");
    
    if ((l1==1 || l1==2) && (l2==1 || l2==2)) {
        int n1 = std::stoi(s1), n2 = std::stoi(s2);
        std::string res = std::to_string(n1*n2);
        if(debug) std::cout << "karatsuba_multiply with base case: " << s1 << " * " << s2 << " = " << res << std::endl;
        return res;
    }
    int n = l1;
    if (l1 != l2) {
        if (l1>l2) {
            n=l1;
        }
        else {
            n=l2;
        }
    }
    if (n%2) n++;
    normalize_for_karatsuba(s2,n);
    normalize_for_karatsuba(s1,n);
    if (debug) std::cout << "karatsuba_multiply with n=" << n << " : " << s1 << " * " << s2 << std::endl;

    std::string a = s1.substr(0, n/2);
    std::string b = s1.substr(n/2, n-n/2);

    std::string c = s2.substr(0, n/2);
    std::string d = s2.substr(n/2, n-n/2);

    auto ac = karatsuba_multiply(a, c); // term 1
    auto bd = karatsuba_multiply(b, d); // term 2
    auto a_plus_b = sum(a, b);
    auto c_plus_d = sum(c, d);
    auto apb_times_cpd = karatsuba_multiply(a_plus_b, c_plus_d); // term 3
    auto gauss_term = difference(difference(apb_times_cpd, ac), bd);
    
    if(debug) {
    std::cout << "\ta+b = " << a_plus_b << " c+d = " << c_plus_d << " apb_times_cpd = " << apb_times_cpd << std::endl;
    std::cout << "\tac = " << ac << " bd = " << bd;
    std::cout << " gauss_term = " << gauss_term << std::endl;
    }

    for (int i=0; i<n; i++) {
        ac += "0";
        if (i < n/2)
            gauss_term += "0";
    }


    auto final_product = sum(sum(ac, gauss_term), bd);
    bool all_zeros = true;
    for(auto itr = final_product.begin(); itr != final_product.end(); itr++) {
        if (*itr != '0') {
            all_zeros = false;
            break;
        }
    }
    if (all_zeros)
        return "0";

    while (final_product.at(0) == '0' && final_product.size() > 0) {
        final_product.erase(final_product.begin());
    }
    if (debug) std::cout << "FINAL PRODUCT " << s1 << " * " << s2 << " = " << final_product << std::endl;
    return final_product;

} 

void test_karatsuba_multiply(const char *s1, const char *s2) {
    std::string str1(s1);
    std::string str2(s2);
    auto s = karatsuba_multiply(str1, str2);
} 

int main (int argc, char** argv) {
    
    // test_karatsuba_multiply("024", "126"); 
    // test_karatsuba_multiply("101", "07"); 
    // test_karatsuba_multiply("134", "46"); 
    // test_karatsuba_multiply("1234", "5678"); 
    // auto s3 = sum("1234567890", "1234567890");
    // auto s4 = sum("9999999999", "9999999999");
    std::string input_file = argv[1];
    std::ifstream inFile;
    inFile.open(input_file);

    std::string s1, s2;
    inFile >> s1 >> s2;

    if (debug) std::cout << "s1 = " << s1 << " s2 = " << s2 << std::endl;
    
    auto start = std::chrono::steady_clock::now();
    auto s3 = karatsuba_multiply(s1,s2);
    auto end = std::chrono::steady_clock::now();
    
    std::cout << s3 << std::endl;
    if (debug)
        std::cout << "Computed in " << std::chrono::duration_cast<
            std::chrono::microseconds>(end-start).count() << "us\n";

    // auto s5 = difference("68160000", "57895422");
    // auto s6 = difference(s5, "417942");

    return 0;
}