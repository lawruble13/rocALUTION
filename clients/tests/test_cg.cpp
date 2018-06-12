/* ************************************************************************
 * Copyright 2018 Advanced Micro Devices, Inc.
 * ************************************************************************ */

#include "testing_cg.hpp"
#include "utility.hpp"

#include <gtest/gtest.h>

typedef std::tuple<int, std::string, unsigned int> cg_tuple;

int cg_size[] = {7, 63};
std::string cg_precond[] = {"None", "Chebyshev", "FSAI", "SPAI", "TNS", "Jacobi", "SGS", "ILU", "ILUT", "IC", "MCSGS", "MCILU"};
unsigned int cg_format[] = {1, 2, 4, 5, 6, 7};

class parameterized_cg : public testing::TestWithParam<cg_tuple>
{
    protected:
    parameterized_cg() {}
    virtual ~parameterized_cg() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

Arguments setup_cg_arguments(cg_tuple tup)
{
    Arguments arg;
    arg.size       = std::get<0>(tup);
    arg.precond    = std::get<1>(tup);
    arg.format     = std::get<2>(tup);
    return arg;
}

TEST_P(parameterized_cg, krylov_float)
{
    Arguments arg = setup_cg_arguments(GetParam());
    ASSERT_EQ(testing_cg<float>(arg), true);
}

TEST_P(parameterized_cg, krylov_double)
{
    Arguments arg = setup_cg_arguments(GetParam());
    ASSERT_EQ(testing_cg<double>(arg), true);
}

INSTANTIATE_TEST_CASE_P(cg,
                        parameterized_cg,
                        testing::Combine(testing::ValuesIn(cg_size),
                                         testing::ValuesIn(cg_precond),
                                         testing::ValuesIn(cg_format)));