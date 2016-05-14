/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TEST_SUITE_H
#define LIBSIMDPP_TEST_TEST_SUITE_H

#include <vector>
#include <cstring>
#include <iosfwd>
#include <cstdint>

class TestResultsSet;

bool test_equal(const TestResultsSet& a, const char* a_arch,
                const TestResultsSet& b, const char* b_arch,
                std::ostream& err);

// Types of vector elements
enum VectorType : uint8_t {
    TYPE_INT8 = 0,
    TYPE_UINT8,
    TYPE_INT16,
    TYPE_UINT16,
    TYPE_UINT32,
    TYPE_INT32,
    TYPE_UINT64,
    TYPE_INT64,
    TYPE_FLOAT32,
    TYPE_FLOAT64
};

/** The class represents test results for certain instruction set. We later
    compare the results with other instruction sets and assume that all
    differences are errors. It's possible to set the precision of each test
    result so that the differencies less than the set precision are not
    interpreted as errors.
*/
class TestResultsSet {
public:

    // Holds one result vector
    struct Result {
        static const unsigned num_bytes = 32;

        Result(VectorType atype, unsigned alength, unsigned ael_size,
               const char* afile, unsigned aline, unsigned aseq,
               unsigned aprec_ulp, bool afp_zero_eq)
        {
            type = atype;
            file = afile;
            line = aline;
            seq = aseq;
            prec_ulp = aprec_ulp;
            fp_zero_eq = afp_zero_eq;
            length = alength;
            el_size = ael_size;
            data.resize(el_size*length);
        }

        VectorType type;
        unsigned line;
        unsigned seq;
        unsigned prec_ulp;
        bool fp_zero_eq;
        const char* file;
        unsigned length;
        unsigned el_size;

        void set(unsigned id, void* adata)
        {
            std::memcpy(data.data() + id*el_size, adata, el_size);
        }

        const void* d() const
        {
            return data.data();
        }

        std::vector<std::uint8_t> data;
    };

    /// Stores the results into the results set.
    Result& push(VectorType type, unsigned length, const char* file, unsigned line);

    /// Sets the allowed error in ULPs. Only meaningful for floating-point data.
    /// Affects all pushed data until the next call to @a unset_precision
    void set_precision(unsigned num_ulp)    { curr_precision_ulp_ = num_ulp; }
    void unset_precision()                  { curr_precision_ulp_ = 0; }

    /// Sets whether floating-point zero and negative zero are considered
    /// equal. Affects all pushed data until the next call to @a unset_fp_zero_equal
    void set_fp_zero_equal()                { curr_fp_zero_equal_ = true; }
    void unset_fp_zero_equal()              { curr_fp_zero_equal_ = false; }


    /// The name of the test case
    const char* name() const                { return name_; }

    /// Resets the sequence number
    void reset_seq()                        { seq_ = 1; }

    /// The number of results pushed to the test case
    std::size_t num_results() const;

    /** Allows synchronizing tests in cases when certain architectures do not
        execute the test in question. The function must be called before and
        after the block of tests that may not be executed. The call to this
        function must be executed regardless of architectures.

        The function resets the sequence number.
    */
    void sync_archs()                       { curr_results_section_++; reset_seq(); }

    const std::vector<std::vector<Result>>& get_results() const { return results_; }

private:
    friend class TestResults;
    friend bool test_equal(const TestResultsSet& a, const char* a_arch,
                           const TestResultsSet& b, const char* b_arch,
                           std::ostream& err);

    TestResultsSet(const char* name);

    static std::size_t size_for_type(VectorType t);
    static unsigned precision_for_result(const Result& res);

    const char* name_;
    unsigned seq_;
    unsigned curr_precision_ulp_;
    unsigned curr_fp_zero_equal_;

    unsigned curr_results_section_;
    std::vector<std::vector<Result>> results_;
};

class SeqTestSuite {
public:
    SeqTestSuite() : num_failure_(0), num_success_(0) {}

    unsigned num_failure() const { return num_failure_; }
    unsigned num_success() const { return num_success_; }

    void add_result(bool success)
    {
        if (success) {
            num_success_++;
        } else {
            num_failure_++;
        }
    }

    bool success() const { return num_failure_ == 0; }

private:
    unsigned num_failure_;
    unsigned num_success_;
};



#endif
