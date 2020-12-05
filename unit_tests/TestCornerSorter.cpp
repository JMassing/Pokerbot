#include <vector>

#include <opencv2/core.hpp>
#include <gtest/gtest.h>

#include "CornerSorter.hpp"

namespace UnitTest
{
    // Tests
	GTEST_TEST(Test_sortCorners, should_sort_points_clockwise_starting_lower_right )
	{
		std::vector< cv::Point2f > points{{-5,-5}, {5,5}, {5,-5}, {-5,5}};
        cv::Point2f center{0,0}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points,center);
        std::vector< cv::Point2f > expected_result = {{5,-5}, {-5,-5}, {-5,5}, {5,5}};
        EXPECT_EQ(sorted_points, expected_result);
    };
}