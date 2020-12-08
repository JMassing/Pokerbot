#include <vector>

#include <opencv2/core.hpp>
#include <gtest/gtest.h>

#include "CornerSorter.hpp"
#include "TCoordsCalculator.hpp"
#include "PerspectiveCorrector.hpp"


// Test for PerspectiveCorrector and classes only used by it
namespace UnitTest
{
    // Test CornerSorter
	GTEST_TEST(Test_CornerSorter, should_sort_points_clockwise_starting_lower_right )
	{
		std::vector< cv::Point2f > points{{-5,-5}, {5,5}, {5,-5}, {-5,5}};
        cv::Point2f center{0,0}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points,center);
        std::vector< cv::Point2f > expected_result = {{5,-5}, {-5,-5}, {-5,5}, {5,5}};
        EXPECT_EQ(sorted_points, expected_result);
    };

	GTEST_TEST(Test_CornerSorter, should_return_points_if_size_smaller_4)
	{
		std::vector< cv::Point2f > points{{-5,-5}, {5,5}, {5,-5}};
        cv::Point2f center{0,0}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points,center);
        EXPECT_EQ(sorted_points, points);
    };

    //Test TCoordsCalculator with all possible card orientations
    GTEST_TEST(Test_TCoordsCalculator, card_is_horizontally_orientated_and_tilted_right)
	{
		std::vector< cv::Point2f > points{{100, 400}, {0, 100}, {500, 300}, {400, 0}};
        cv::Point2f center{250, 250}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points,center);
        detect::TCoordsCalculator coords_calc{};
        std::vector<cv::Point2f> coords = coords_calc.calc_coords(sorted_points, 200, 300, 5);         
        std::vector<cv::Point2f> expected_coords{ {195, 295}, {195, 5}, {5, 5}, {5, 295}};
        EXPECT_EQ(coords, expected_coords);
    };

    GTEST_TEST(Test_TCoordsCalculator, card_is_horizontally_orientated_and_tilted_left)
	{
		std::vector< cv::Point2f > points{{-100, 5}, {-110, 25}, {-70, 35}, {-60, 14}};
        cv::Point2f center{-85, 20}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points,center);
        detect::TCoordsCalculator coords_calc{};
        std::vector<cv::Point2f> coords = coords_calc.calc_coords(sorted_points, 200, 300, 5);         
        std::vector<cv::Point2f> expected_coords{{195, 295}, {195, 5}, {5, 5}, {5, 295}};
        EXPECT_EQ(coords, expected_coords);
    };

    GTEST_TEST(Test_TCoordsCalculator, card_is_almost_horizontal)
	{
		std::vector< cv::Point2f > points{{-50, 70}, {-49, 330}, {500, 330}, {499, 70}};
        cv::Point2f center{225, 205}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points, center);
        detect::TCoordsCalculator coords_calc{};
        std::vector<cv::Point2f> coords = coords_calc.calc_coords(sorted_points, 200, 300, 5);         
        std::vector<cv::Point2f> expected_coords{{195, 295}, {195, 5}, {5, 5}, {5, 295}};
        EXPECT_EQ(coords, expected_coords);
    };

    //Else Cases
    GTEST_TEST(Test_TCoordsCalculator, card_is_tilted_right)
	{
		std::vector< cv::Point2f > points{{-210, 420}, {30, 545}, {260, 144}, {15, 25}};
        cv::Point2f center{20, 280}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points, center);
        detect::TCoordsCalculator coords_calc{};
        std::vector<cv::Point2f> coords = coords_calc.calc_coords(sorted_points, 200, 300, 5);         
        std::vector<cv::Point2f> expected_coords{{195, 5}, {5, 5}, {5, 295}, {195, 295}};
        EXPECT_EQ(coords, expected_coords);
    };

    GTEST_TEST(Test_TCoordsCalculator, card_is_diamond_shaped_and_tilted_right)
	{
		std::vector< cv::Point2f > points{{19, 230}, {210, 380}, {410, 140}, {230, 0}};
        cv::Point2f center{220, 180}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points, center);
        detect::TCoordsCalculator coords_calc{};
        std::vector<cv::Point2f> coords = coords_calc.calc_coords(sorted_points, 200, 300, 5);         
        std::vector<cv::Point2f> expected_coords{{195, 5}, {5, 5}, {5, 295}, {195, 295}};
        EXPECT_EQ(coords, expected_coords);
    };

    GTEST_TEST(Test_TCoordsCalculator, card_is_tilted_left)
	{
		std::vector< cv::Point2f > points{{-30, 500}, {225, 370}, {42, 50}, {-200, 180}};
        cv::Point2f center{-86, 18}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points, center);
        detect::TCoordsCalculator coords_calc{};
        std::vector<cv::Point2f> coords = coords_calc.calc_coords(sorted_points, 200, 300, 5);         
        std::vector<cv::Point2f> expected_coords{{195, 5}, {5, 5}, {5, 295}, {195, 295}};
        EXPECT_EQ(coords, expected_coords);
    };

    GTEST_TEST(Test_TCoordsCalculator, card_is_diamond_shaped_and_tilted_left)
	{
		std::vector< cv::Point2f > points{{40, 490}, {240, 330}, {5, 70}, {-200, 220}};
        cv::Point2f center{13, 274}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points, center);
        detect::TCoordsCalculator coords_calc{};
        std::vector<cv::Point2f> coords = coords_calc.calc_coords(sorted_points, 200, 300, 5);         
        std::vector<cv::Point2f> expected_coords{{195, 5}, {5, 5}, {5, 295}, {195, 295}};
        EXPECT_EQ(coords, expected_coords);
    };

    GTEST_TEST(Test_TCoordsCalculator, card_is_upright)
	{
		std::vector< cv::Point2f > points{{-50, 0}, {-49, 500}, {300, 500}, {299, 0}};
        cv::Point2f center{175, 250}; 
        detect::CornerSorter sorter{};
        std::vector< cv::Point2f > sorted_points = sorter.sortCorners(points, center);
        detect::TCoordsCalculator coords_calc{};
        std::vector<cv::Point2f> coords = coords_calc.calc_coords(sorted_points, 200, 300, 5);         
        std::vector<cv::Point2f> expected_coords{{195, 5}, {5, 5}, {5, 295}, {195, 295}};
        EXPECT_EQ(coords, expected_coords);
    };

    //Test PerspectiveCorrector
    GTEST_TEST(Test_PerspectiveCorrector, warp_image_returns_true_if_exactly_4_points_and_images_are_not_empty)
	{
        //dummy points
		std::vector< cv::Point2f > points{{40, 490}, {240, 330}, {5, 70}, {-200, 220}};
        cv::Point2f center{13, 274}; 
        detect::PerspectiveCorrector p_cor{};
        //dummy images
        cv::Mat src(500, 1000, CV_8UC1, cv::Scalar(70));
        cv::Mat dst(500, 1000, CV_8UC1, cv::Scalar(70));
        EXPECT_TRUE(p_cor.warpImage(src, dst, points, center, 5));
    };

    GTEST_TEST(Test_PerspectiveCorrector, warp_image_returns_false_if_less_than_4_points)
	{
        //dummy points
		std::vector< cv::Point2f > points{{40, 490}, {240, 330}, {5, 70}};
        cv::Point2f center{13, 274}; 
        detect::PerspectiveCorrector p_cor{};
        //dummy images
        cv::Mat src(500, 1000, CV_8UC1, cv::Scalar(70));
        cv::Mat dst(500, 1000, CV_8UC1, cv::Scalar(70));
        EXPECT_FALSE(p_cor.warpImage(src, dst, points, center, 5));
    };

    GTEST_TEST(Test_PerspectiveCorrector, warp_image_returns_false_if_more_than_4_points)
	{
        //dummy points
		std::vector< cv::Point2f > points{{40, 490}, {240, 330}, {5, 70}, {-200, 220}, {0, 0}};
        cv::Point2f center{13, 274}; 
        detect::PerspectiveCorrector p_cor{};
        //dummy images
        cv::Mat src(500, 1000, CV_8UC1, cv::Scalar(70));
        cv::Mat dst(500, 1000, CV_8UC1, cv::Scalar(70));
        EXPECT_FALSE(p_cor.warpImage(src, dst, points, center, 5));
    };

        GTEST_TEST(Test_PerspectiveCorrector, warp_image_returns_false_if_dst_is_empty)
	{
        //dummy points
		std::vector< cv::Point2f > points{{40, 490}, {240, 330}, {5, 70}, {-200, 220}};
        cv::Point2f center{13, 274}; 
        detect::PerspectiveCorrector p_cor{};
        //dummy images
        cv::Mat src(500, 1000, CV_8UC1, cv::Scalar(70));
        cv::Mat dst{};
        EXPECT_FALSE(p_cor.warpImage(src, dst, points, center, 5));
    };

        GTEST_TEST(Test_PerspectiveCorrector, warp_image_returns_false_if_src_is_empty)
	{
        //dummy points
		std::vector< cv::Point2f > points{{40, 490}, {240, 330}, {5, 70}, {-200, 220}};
        cv::Point2f center{13, 274}; 
        detect::PerspectiveCorrector p_cor{};
        //dummy images
        cv::Mat src{};
        cv::Mat dst(500, 1000, CV_8UC1, cv::Scalar(70));
        EXPECT_FALSE(p_cor.warpImage(src, dst, points, center, 5));
    };
}