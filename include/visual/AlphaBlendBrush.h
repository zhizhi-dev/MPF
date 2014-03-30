#pragma once
#include "Brush.h"
#include "BitmapData.h"

NS_MPF
NS_VSL

//Alpha混合画刷
class AlphaBlendBrush : public Brush
{
public:
	//创建 AlphaBlendBrush 的新实例
	MPF_API AlphaBlendBrush(std::shared_ptr<BitmapData<byte>> alpha, 
		std::shared_ptr<Brush> secondBrush) mnoexcept;

	//采样
	MPF_API virtual color_t TakeSample(float u, float v) const;

	//获取 Alpha 数据
	MPF_API std::shared_ptr<BitmapData<byte>> GetAlpha() const mnoexcept;
	//设置 Alpha 数据
	MPF_API void SetAlpha(std::shared_ptr<BitmapData<byte>> value) mnoexcept;
	//获取或设置 Alpha 数据
	mproperty(std::shared_ptr<BitmapData<byte>>, Alpha);

	//获取第二 Brush
	MPF_API std::shared_ptr<Brush> GetSecondBrush() const mnoexcept;
	//设置第二 Brush
	MPF_API void SetSecondBrush(std::shared_ptr<Brush> value) mnoexcept;
	//获取或设置第二 Brush
	mproperty(std::shared_ptr<Brush>, SecondBrush)

	//获取类型
	MPF_API DECLARE_GETTYPE(AlphaBlendBrush);
	MPF_API DECLARE_GETINSTANTTYPE(AlphaBlendBrush);
private:
	std::shared_ptr<BitmapData<byte>> alpha;
	std::shared_ptr<Brush> secondBrush;

	DECLARE_TYPE(AlphaBlendBrush)
};

NS_ED
NS_ED