#pragma once

namespace templates{

    template<class T>
    struct RectangleCorners
    {
            T upper_left;
            T upper_right;
            T lower_left;
            T lower_right;

            RectangleCorners(): upper_left(0), upper_right(0), lower_right(0), lower_left(0) {};
            RectangleCorners(T ul, T ur, T lr, T ll): upper_left(ul), upper_right(ur), lower_right(lr), lower_left(ll) {};
            ~RectangleCorners(){};

            RectangleCorners(const RectangleCorners& other) = default;	
			RectangleCorners& operator=(const RectangleCorners& other) = default;
			RectangleCorners(RectangleCorners&& other) noexcept = default;
			RectangleCorners& operator=(RectangleCorners&& other) noexcept = default;
    };
}